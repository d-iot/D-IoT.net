#include "DIoT2560PRO.h"
#include <avr/pgmspace.h>
#include <Sodaq_dataflash.h>
#include <TinyGPS++.h> 
#include <MPU6050.h> 
#include <avr/wdt.h>  
#include <Wire.h>
TinyGPSPlus gps;


#include <SPI.h> 
MPU6050 mpu;
#define RetOk   "OK"
#define RetERR  "ERR"
#define OKRN     F("OK\r\n") 
#define CTRLZ    F("\x1A") 
#define CR       F("\r") 
#define LF       F("\n") 
#define CRLF     F("\r\n") 
#define GsmSerial Serial3
#define RN       F("\r\n") 
#define PrmsChr ','
extern int BPercent;
extern int BVoltage;
extern int ChargeState;
extern float temp,humid;
extern String model;
extern String Retval;
extern int Datetimesaat2;
extern String GsmTmp,GsmTmp2;
extern int16_t mpu_ax, mpu_ay, mpu_az; 
//extern  GsmSendAT(String CmdAT, String  EndChar, long tmout, String Waitval);
//extern String StrExtract(String Data, String Tag1, String Tag2);
//extern GsmPowerState();
extern int GsmPower;
extern String ipAddress;
extern unsigned long periodicsend;
extern String port;
//extern String SplitString(String data, char separator, int index);
extern int net;
extern void InitDiot();
extern String imei;
extern String token;
extern String  gettoken();
extern void PrepareSocket();
extern int initOk;
extern int mdetect;
void DIoTPRO::call(String number)
{
   Retval = number + " Calling...";
   Serial.println("");
   Serial.println(Retval);
   Retval += GsmSendAT("ATD" + number + ";", RN, 2000, OKRN);
   GsmSendAT("AT+QAUDCH=2", RN, 2000, OKRN);
   delay(2000);
   delay(500);
  
}



String DIoTPRO::GsmSendAT(String CmdAT, String  EndChar, long tmout, String Waitval)
{
  // Serial.print(CmdAT + EndChar);
  String Retval = RetERR;
  if (CmdAT.length() > 0)
  {
    GsmSerial.flush();
    for (int i = 0; i < (signed int)CmdAT.length(); i++)
    {
      GsmSerial.print(CmdAT[i]);
    }
    GsmSerial.print(EndChar);
  }
  String GsmRetval = "";
  unsigned long stop = millis() + tmout;
  while (millis() < stop || GsmSerial.available())
  {
    while (GsmSerial.available())
    {
      GsmRetval += (char)GsmSerial.read();
    }
    if (GsmRetval.indexOf(Waitval) > 0) { stop = millis() - 10; Retval = RetOk; }
    if (GsmRetval.indexOf(F("ERROR")) > 0) { stop = millis() - 10; Retval = RetERR; }
  }
  GsmTmp = GsmRetval;
  if (GsmTmp2 == "")
    GsmTmp2 = GsmRetval;
  return Retval;
}
String DIoTPRO:: GsmSendAT2Data(String CmdAT, String EndChar, long tmout, String Waitval, String& Data, String GetValStart, String GetValEnd)
{
  //wdt_reset();
  if (tmout > 5000) { wdt_disable(); }
  String AtCmdStatus = RetERR;
  String Retval = AtCmdStatus;
  if (CmdAT.length() > 0)
  {
    GsmSerial.flush();
    GsmSerial.print(CmdAT + EndChar);
  }

  GsmTmp = "";
  unsigned long stop = millis() + tmout;


  while (millis() < stop)
  {
    while (GsmSerial.available())
    {
      GsmTmp += (char)GsmSerial.read();
    }
    if (GsmTmp.indexOf(F("ERROR")) > 0) { stop = millis() - 10; AtCmdStatus = RetERR; }
    if (GsmTmp.indexOf(Waitval, GsmTmp.indexOf(GetValEnd)) > 0) { stop = millis() - 10; AtCmdStatus = RetOk; }
  }
  if (AtCmdStatus == RetOk)
  {
    Data = StrExtract(GsmTmp, GetValStart, GetValEnd);
  }
  else { Data = ""; GsmTmp = ""; }
  Retval = AtCmdStatus;
  return Retval;
}

String DIoTPRO::StrExtract(String Data, String Tag1, String Tag2)
{
  String Retval = "";
  int First = Data.indexOf(Tag1);
  int FirstLen = Tag1.length();
  int Last = Data.indexOf(Tag2, First + FirstLen);

  if (Last > 0 && First >= 0 && Last > First) //if (Last > 0 && First >= 0)
  {
    Retval = Data.substring(First + FirstLen, Last);
  }
  return Retval;
}

int DIoTPRO::GsmPowerOff()
{
  Serial.println(F("Gsm Power Off... "));

  if (GsmPowerState() == 1)
  {
    Serial.println(F("Wait 13 Second"));
    digitalWrite(A15, HIGH);
    delay(850);
    digitalWrite(A15, LOW);
    delay(12000);
    GsmPower = 0;
  }
  Serial.println(F("Gsm Power is Off"));
  return GsmPower;
}
int DIoTPRO:: GsmPowerState()
{
  for (int i = 0; i < 10; i++)
  {
    GsmPower = (GsmSendAT(F("AT"), CR, 250, OKRN) == RetOk) ? 1 : 0;
    if (GsmPower == 1)
      break;
  }
  Serial.println(F("GsmPower:"));
  Serial.print(String(GsmPower));
  return GsmPower;

}

int DIoTPRO::GsmPowerOn()
{



  if (GsmPower == 0)
  {

    GsmSerial.flush();
    digitalWrite(A15, HIGH);
    delay(1000);
    digitalWrite(A15, LOW);

    GsmPower = GsmPowerState();
  }
  return GsmPower;
} 
String DIoTPRO::CmdHandler(String CmdStr)
{

  if (!Serial.available() && CmdStr == "")
    return "";

  String SerialStr = "";

  if (CmdStr != "")
  {
    SerialStr = CmdStr;
  }
  else
  {
    unsigned long stop = millis() + 50;
    while (millis() < stop || Serial.available())
    {
      while (Serial.available())
      {
        SerialStr += (char)Serial.read();
      }
    }
  }


  int tcpcmd = 0;
  if (SerialStr.indexOf("TCP,") > 0)
  {
    SerialStr = SerialStr.substring(5);
    tcpcmd = 1;
  }

  Serial.println("Cmd:" + SerialStr);



  
  String Retval;
  if (periodicsend > 0 && GsmTmp2 == "") {
    GsmTmp2 = "OK";
  }
  String Cmd = SerialStr.substring(0, 2);
  String Prm1 = SplitString(SerialStr, ',', 1);
  String Prm2 = SplitString(SerialStr, ',', 2);
  String Prm3 = SplitString(SerialStr, ',', 3);
  String Prm4 = SplitString(SerialStr, ',', 4);
  String Prm5 = SplitString(SerialStr, ',', 5);
  //Buzzer(10);



  if (SerialStr.substring(0, 2) == "AT")
  {
    GsmSerial.print(SerialStr);
    String GsmRetval;
    unsigned long stop = millis() + 3000;
    while (millis() < stop)
    {
      while (GsmSerial.available())
      {
        int val = GsmSerial.read();
        GsmRetval += (char)val;
      }
      if (GsmRetval.indexOf(OKRN) > 0) { stop = millis() - 10; }

    }
    Serial.println(GsmRetval);
  }
  else if ((" " + SerialStr).indexOf("+QBT") > 0)
  {
    if ((SerialStr).indexOf("\"pair\"") > 0)
    {
      GsmSendAT("AT+QBTPAIRCNF=1", RN, 2000, OKRN);

    }
    if ((SerialStr).indexOf("\"conn\"") > 0)
    {
      GsmSendAT("AT+QBTACPT=1,1", RN, 2000, OKRN);



    }


  }
  else if ((" " + SerialStr).indexOf("RDY") > 0 || SerialStr.indexOf("CFUN") > 0 || SerialStr.indexOf("CPIN") > 0 || SerialStr.indexOf("Ready") > 0 || SerialStr.indexOf("READY") > 0)
  {
    Serial.println(F("  Gsm Module Starting Process..."));


    if (SerialStr.indexOf("MS Ready") > 0)
    {
      delay(1000);
      Serial.println(F(">>>>>>Gsm Module Started<<<<<<"));



    }
  }
  else if ((" " + SerialStr).indexOf("CONNECT OK") > 0)
  {
    Serial.println(F("Tcp Socket Connected"));
    net = 1;


  }
  else if ((" " + SerialStr).indexOf("CLOSED") > 0)
  {
    Serial.println("Tcp Socket Closed");
    net = 0;
    //LedOn(100);
  
    digitalWrite(13, HIGH);
  }
  else if ((" " + SerialStr).indexOf("CONNECT FAIL") > 0)
  {
      digitalWrite(13, HIGH);
  }
  else if (Cmd == "00")
  {
    //ShowMenu();
  }
  else if (Cmd == "01")
  {
   // DP.GsmPowerOn();
    //InitializeGsm();
  }
  else if (Cmd == "02"){}
   // InitializeGsm(){}
  else if (Cmd == "03"){}
    //DP.GsmPowerOff(){}
  else if (Cmd == "04"){}
   // GpsPowerOn();
  else if (Cmd == "05")
  {}
 //   GpsPowerOff();
  else if (Cmd == "06")
  {
   // Retval = DP.GsmSendAT("ATA", RN, 2000, OKRN);
  }
  else if (Cmd == "07")
  {
   // Retval = Prm1 + " Calling...";
    //Serial.println(Retval);
    //Retval += DP.GsmSendAT("ATD" + Prm1 + ";", RN, 2000, OKRN);
    //DP.GsmSendAT("AT+QAUDCH=2", RN, 2000, OKRN);


  }
  else if (Cmd == "08")
  {
   // Retval = " End Call ...";
    //Retval += DP.GsmSendAT("ATH", RN, 2000, OKRN);

  }

  else if (Cmd == "09")
  {
   
  }
  else if (Cmd == "10")
  {
   // Retval = DP.GsmSendAT("AT+CMGL=\"ALL\"\r\n", RN, 2000, OKRN) + ";" + GsmTmp;

  }

  
  else if (SerialStr.indexOf("token=") > 0)
  {
  
  }






  /////////////////////sil
  else if (SerialStr.indexOf("3337") > 0)
  {
    
  }
  /////////////////////sil
  Serial.println(Retval);

  if (tcpcmd == 1)

  return Retval;

}

void DIoTPRO::SendTcpData(String Message)
{
  GsmSendAT(F("AT+QISEND"), CR, 900, F(">"));
  GsmSendAT(Message + RN, CTRLZ, 5000, "SEND OK\r\n");


}
void DIoTPRO:: btsend(String btret, String conid)
{
  GsmSendAT("AT+QSPPSEND=" + conid + "," + btret.length(), CRLF, 1500, ">");
  GsmSendAT(btret, CTRLZ, 5000, OKRN);
}


void DIoTPRO::GsmReadSerial()
{

  if (GsmSerial.available())
  {
    String SerialStr = "";
    int SerialData = 0;
    unsigned long stop = millis() + 10;



    while (millis() < stop)
    {
      while (GsmSerial.available())
      {
        GsmTmp2 = "";
        SerialData = GsmSerial.read();
        SerialStr += (char)SerialData;
        stop = millis() + 20;

        if (SerialData == -1) {
          stop = millis() + 250;  GsmTmp2 = "OK";
        }

      }
    }

    if ((SerialStr).indexOf("\"recv\"") > 0)
    {
      String Btd = "";
      String conid = SerialStr.substring(SerialStr.length() - 3, SerialStr.length() - 2);
      GsmSendAT2Data("AT+QSPPREAD=" + conid + ",1500", CR, 6000, OKRN, Btd, F("+QSPPREAD: "), OKRN);

      Btd = SplitString(Btd, '\n', 1);

      if (Btd.substring(0, 2) == "00")
      {


      }
      else
        btsend(CmdHandler(Btd), conid);

    }
    else
      CmdHandler(SerialStr);
  }
}
String DIoTPRO::SplitString(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
void DIoTPRO::GpsPowerOn()
{
  GsmSendAT(F("AT+QGNSSC=1"), CR, 3000, OKRN);
}
void DIoTPRO::GpsPowerOff()
{
  GsmSendAT(F("AT+QGNSSC=0"), CR, 3000, OKRN);

}

String DIoTPRO::SendSms(String Number, String Msg)
{
  Serial.println(F("Sms sending"));
  GsmSendAT("AT+CMGS=\"" + Number + "\"", CR, 1500, F(">"));
  GsmSendAT2Data(Msg, CTRLZ, 5000, OKRN, GsmTmp, F("+CMGS: "), RN);

  return GsmTmp + String(PrmsChr) + Number;
}
void DIoTPRO::SocketInit() {

  delay(3000);
  
  Serial.println(F("Sending SocketInit....:"));
  //  Serial.print(Message);

  GsmTmp = "";
}

void DIoTPRO::InitializeGsm()
{
  if (GsmPower != 1)
  {
    Serial.println(F("!Gsm Power Off"));
    InitDiot();
    return;
  }

  //GsmSendAT(F("AT+CMEE=2"), CR, 3000, OKRN);
  //GsmSendAT(F("AT+IPR=57600;&W"), CR, 3000, OKRN);
  GsmSendAT(F("AT+CSQ"), CR, 3000, OKRN);
  GsmSendAT(F("AT+GSN"), CR, 3000, OKRN);
  GsmSendAT(F("AT+QCCID"), CR, 3000, OKRN);
  GsmSendAT(F("ATE0&w"), CR, 3000, OKRN);
  GsmSendAT(F("AT+CNMI=2,1,2,0,0"), CR, 3000, OKRN);
  GsmSendAT(F("AT+CSCS=\"8859-1\""), CR, 3000, OKRN);
  GsmSendAT(F("AT+CMGF=1"), CR, 3000, OKRN);
  GsmSendAT(F("AT+QIFGCNT=0"), CR, 3000, OKRN);
  //GsmSendAT(F("AT+QSCLK=1"), CR, 3000, OKRN);
  GsmSendAT(F("AT+QMGDA=\"DEL ALL\""), CR, 3000, OKRN);
  GsmSendAT(F("AT+CMEE=1;&W"), CR, 3000, OKRN);
  GsmSendAT(F("AT&W"), CR, 3000, OKRN);
  GsmSendAT(F("AT+QBTPWR=1"), CR, 3000, OKRN);

  GsmSendAT("AT+QBTNAME=\"D-Iot\"", CR, 5000, OKRN);
  GsmSendAT(F("AT+QBTVISB=1"), CR, 3000, OKRN);
  GsmSendAT2Data(F("AT+GSN"), CR, 1000, OKRN, imei, LF, CR);  //imei  
  GpsPowerOn();

}

void DIoTPRO::InitDiot() {
token = gettoken();

  int gps = GsmPowerState();
  if (gps == 0) {

    GsmPowerOn();
    InitializeGsm();
    delay(31000);
    PrepareSocket();
    initOk = 1;
  }
  else if (net == 0) {
    PrepareSocket();
    initOk = 1;

  }
  else {
    initOk = 0;
    digitalWrite(13, HIGH);
    Serial.println(F("Cannot connect internet"));
  }


}
String DIoTPRO::gettoken()
{
  String Retval = "";
  int len = eeprom_read_byte(10);


  for (int i = 11; i < 11 + len; i++)
  {
    Retval += String((char)eeprom_read_byte(i));
  }

  return Retval;
}

boolean DIoTPRO::isValidNumber(String str) {
  for (byte i = 0; i < str.length(); i++)
  {
    if (isDigit(str.charAt(i))) return true;
  }
  return false;
}
void DIoTPRO::PrepareSocket() {

  if (net == 0) {
  
  String ope;   
  GsmSerial.print(F("AT+QSPN\r\n")); 
  unsigned long stop = millis() + 2500;
  while (millis() < stop)
  {
    while (GsmSerial.available())
    {
      int val = GsmSerial.read();
        ope += (char)val;
        }
    if (ope.indexOf(OKRN) > 0) { stop = millis() - 10; }

  }   if(ope.indexOf("elekom")!=-1 || ope.indexOf("urkcell")!=-1)
      CmdHandler("13,internet,,,");
      else   if (ope.indexOf("odafone") != -1)
      CmdHandler("13,internet,vodafone,vodafone,");
      else
        CmdHandler("13,internet,,,");
    GsmTmp = "";
    CmdHandler("14," + ipAddress + "," + port);
    delay(7000);
    if (GsmTmp.indexOf("OK") > -1 || GsmTmp.indexOf("ALREADY") > -1) {
      net = 1;
    
      initOk = 1;
      SocketInit();


    }
    else {
      delay(1000);
      InitDiot();
    }

  }
  else
    SocketInit();
}
void DIoTPRO::StartMpu()
{
  mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_16G);
  delay(500);
  mpu.setAccelPowerOnDelay(MPU6050_DELAY_3MS);
  mpu.setIntFreeFallEnabled(false);
  mpu.setIntZeroMotionEnabled(false);
  mpu.setIntMotionEnabled(true);
  mpu.setDHPFMode(MPU6050_DHPF_RESET);
  mpu.setMotionDetectionThreshold(3);
  mpu.setMotionDetectionDuration(2);
  mpu.setZeroMotionDetectionThreshold(4);
  mpu.setZeroMotionDetectionDuration(2);

 // attachInterrupt(digitalPinToInterrupt(3), MotionDetect, LOW);
}
void DIoTPRO::mpu_getxyz()
{
  Vector rawGyro = mpu.readRawGyro();
  Vector normGyro = mpu.readNormalizeGyro();
  mpu_ax = rawGyro.XAxis;
  mpu_ay = rawGyro.YAxis;
  mpu_az = rawGyro.ZAxis;
}
void DIoTPRO::MotionDetect()
{
  if (mdetect == 1)
    Serial.println(F("Motion Detected!"));
}

void DIoTPRO::GMT(int gmtvalue)
{
  if( gmtvalue==24)
{Datetimesaat2=0;  }
else if( gmtvalue==25)
{Datetimesaat2=1;  }
else if(Datetimesaat2==26)
{Datetimesaat2=2;  }
else if( gmtvalue==27)
{Datetimesaat2=3;  }
else if(gmtvalue==28)
{Datetimesaat2=4;  }
else if(gmtvalue==29)
{Datetimesaat2=5;  }
else if(gmtvalue==30)
{Datetimesaat2=6;  }
else if(gmtvalue==31)
{Datetimesaat2=7;  }
else if(gmtvalue==32)
{Datetimesaat2=8;  }
else if(gmtvalue==33)
{Datetimesaat2=9;  }
else if(gmtvalue==34)
{Datetimesaat2=10;  }
else if(gmtvalue==35)
{Datetimesaat2=11;  }
else if(gmtvalue==36)
{Datetimesaat2=12;}
else if(gmtvalue==37)
{Datetimesaat2=13;}
else if(gmtvalue==38)
{Datetimesaat2=14;}
else if(gmtvalue==39)
{Datetimesaat2=15;}
else if(gmtvalue==40)
{Datetimesaat2=16;  }
else if(gmtvalue==41)
{Datetimesaat2=17;   }
else if(gmtvalue==42)
{Datetimesaat2=18;   }
else if(gmtvalue==43)
{Datetimesaat2=19;  }
else if(gmtvalue==44)
{Datetimesaat2=20;  }
else if(gmtvalue==45)
{Datetimesaat2=21;  }
else if(gmtvalue==46)
{Datetimesaat2=22;   }
else if(gmtvalue==47)
{Datetimesaat2=23;  }
else if(gmtvalue==48)
{Datetimesaat2=24;  }
}

String  DIoTPRO::GetBatteryVoltage()
{
  //CBC = 0, 100, 4395     QADC = 1, 1846 -

  String Msg = "";
  GsmSendAT2Data("AT+CBC", RN, 3000, OKRN, GsmTmp, F("+CBC:"), RN);

  int QVoltage = SplitString(GsmTmp + ",", ',', 2).toInt();
  ChargeState = 0;
  GsmSendAT2Data("AT+QADC?", RN, 3000, OKRN, GsmTmp, F("+QADC:"), RN);
  BVoltage = SplitString(GsmTmp + ",", ',', 1).toInt() * 2;
  BPercent = map(BVoltage, 3500, 4200, 0, 100);
  if (QVoltage > 4250)
    ChargeState = 1;
  if (BPercent < 0)
    BPercent = 0;
  if (BPercent > 100)
    BPercent = 100;

  String Retval = "";
  Retval = "Charge State     :" + String(ChargeState) + "\r\n";
  Retval += "Battery Voltage :" + String(BVoltage) + "\r\n";
  Retval += "Battery %             :" + String(BPercent);

  return Retval;

}

void DIoTPRO::reg()
{
     GsmSendAT2Data(F("AT+GSN"), CR, 1000, OKRN, imei, LF, CR);  //imei  
     delay(500);
  Serial.println("imei"+imei);
  String url = "https://portal.d-iot.net/reg.aspx?imei=" + imei + "&model=" + model;

  if (GsmSendAT("AT+QHTTPURL=" + String(url.length()) + ",30", CR, 8000, "CONNECT") == RetOk)
  {
    GsmTmp = "";
    GsmSendAT(url, RN, 5000, "OK");

    GsmSendAT("AT+QHTTPGET=60", RN, 5000, OKRN); 
    GsmSendAT2Data("AT+QHTTPREAD=30", RN, 5000, "OK\r\n", GsmTmp, "CONNECT\r\n", OKRN);
    GsmTmp += ",";
    String did = SplitString(GsmTmp, ',', 0);
    String token = SplitString(GsmTmp, ',', 1);

    savedeviceid(did);
    Serial.println("Device Id Saved:" + readdeviceid());


    //token
    int tokenlen = token.length();

    eeprom_write_byte(10, token.length());


    for (int i = 0; i < token.length(); i++)
    {
      eeprom_write_byte(i + 11, token.charAt(i));
    }
    Serial.println("Token Id Saved :" + gettoken());

    //token
  }
  else
  {
    Serial.println(F("Cant connected"));
  }
}
String DIoTPRO::savedeviceid(String did)
{
  String Retval = "";
  if (did.length() > 10)

    Retval = "Device Id (" + did + ") Max Length is 10";
  else
  {

    did = "0000000000" + did;
    did = did.substring(did.length() - 10);

    for (int i = 0; i < 10; i++)
    {
      eeprom_write_byte(i, did.substring(i, i + 1).toInt());
    }
    Retval = did;
  }
  return Retval;
}
String DIoTPRO::readdeviceid()
{
  String Retval = "";
  String did = "";
  for (int i = 0; i < 10; i++)
  {
    did += String((int)eeprom_read_byte(i));
  }

  did = String(atol(did.c_str()));
  Retval = did;
  return Retval;
}


String DIoTPRO::savetoken(String token) {

   //token
    int tokenlen = token.length();

    eeprom_write_byte(10, token.length());


    for (int i = 0; i < token.length(); i++)
    {
      eeprom_write_byte(i + 11, token.charAt(i));
    }
    Serial.println("Token Id Saved :" + gettoken());

    token = gettoken();
}

/*
void DP::ReadTempHumid()
{
  tempsensor.readTempHumid();
  temp = tempsensor.getTemp() - 7;
  humid = tempsensor.getRelativeHumidity();
}*/
