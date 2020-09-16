#include <doxygen.h>
#include <NexButton.h>
#include <NexCheckbox.h>
#include <NexConfig.h>
#include <NexCrop.h>
#include <NexDualStateButton.h>
#include <NexGauge.h>
#include <NexGpio.h>
#include <NexHardware.h>
#include <NexHotspot.h>
#include <NexNumber.h>
#include <NexObject.h>
#include <NexPage.h>
#include <NexPicture.h>
#include <NexProgressBar.h>
#include <NexRadio.h>
#include <NexRtc.h>
#include <NexScrolltext.h>
#include <NexSlider.h>
#include <NexText.h>
#include <NexTimer.h>
#include <Nextion.h>
#include <NexTouch.h>
#include <NexUpload.h>
#include <NexVariable.h>
#include <NexWaveform.h>
#include "Nextion.h"
#include "DIoT2560PRO.h"
DIoTPRO DIoTPRO;
NexNumber n0=NexNumber(0,1,"n0");
NexNumber n1=NexNumber(0,2,"n1");
NexNumber n2=NexNumber(0,15,"n2");
uint32_t numbervalue=0;
uint32_t numbervalue2=0;
uint32_t numbervalue3=0;
int lat2=0;
int lng2=0;
float latt2=0;
float lngg2=0;
String control1;
String control2;
uint32_t button = 0;
uint32_t button2 = 0;
uint32_t button3=0;
uint32_t button4=0;
int timevalue=0;
//.uint32_t numbervalue=0;
int flag=0;
String deneme[30];
#include <avr/pgmspace.h>
#include <Sodaq_dataflash.h>
//#include <TinyGPS++.h> 
//#include <MPU6050.h> 
#include <avr/wdt.h>  
#include <Wire.h>
#include <SPI.h>
#define PinGsmDtr         4
#define PinGsmPower       A15
#define PinGsmRI          2
#define PinMpuInterrupt   3
#define PinDflashSs       46
#define PinBuzzer         48
#define PinLed            13
#define PinBuzzer         48
#define PinRelay          34
#define PinOpto           32
#define PinButton         37
#define PinLdr            A13
#define PinCan_Cs         30

#define CAN_ID_PID        0x7DF
int can_inited = 0;
unsigned char can_pid_input;
unsigned char can_getpid = 0;
char mesaj="";
#define RetOk           "OK"
#define RetERR          "ERR"
#define OKRN            F("OK\r\n") 
#define CTRLZ           F("\x1A") 
#define CR              F("\r") 
#define LF              F("\n") 
#define CRLF            F("\r\n") 
#define GsmSerial Serial3
#define RN              F("\r\n") 
#define PrmsChr ','

String GsmTmp, GsmTmp2;
int16_t mpu_ax, mpu_ay, mpu_az;                                     //axis definition
int initOk = 0;
int mdetect = 0;
int temp;
float humid;
String Datetime = "";
String Datetimeyear="";
String Datetimemonth="";
String Datetimeday="";
String Datetimetime="";
int Datetimetime2=0;
String speed="";
String height="";
String lang="";
String lati="";
String temperature2="";
int GsmPower = 0;
int net = 0;
String token = "";
String imei = "";
String device = "";
String model = "2560pro";
String ipAddress = "95.173.179.216";
String port = "34344";
int BPercent;
int BVoltage;
int ChargeState;
//TinyGPSPlus gps; //ok
int x=0;
uint32_t value=0;
unsigned long periodicsend = 0;
unsigned long nextsend = millis();
String temperature;
//unsigned long zaman = millis() + 10000;
int btncnt = 0;
String Retval;
String Prm1 = "";                                     //your phone number 
int s=0;
int test=0;
char buffer[100] = {0};
void setup() {
  Serial2.begin(9600);
  dbSerialPrintln("setup begin");
  nexInit();
  dbSerialPrintln("setup done");
  SPI.begin();
  Wire.begin();
  Serial.begin(57600);
  GsmSerial.begin(57600);
  pinMode(PinBuzzer,OUTPUT);
  pinMode(PinGsmRI,INPUT_PULLUP);
  Wire.setClock(400000);                                              //set clock speed for I2C bus to maximum allowed for HDC1080
    DIoTPRO.StartMpu();
}
void loop() {


   n0.getValue(&numbervalue);
   n1.getValue(&numbervalue2);
   n2.getValue(&numbervalue3);

if(numbervalue3==1)
{ 
  control1=String(numbervalue);
  control2=String(numbervalue2);
  Prm1="0"+control1+""+control2;
   Serial.println(Prm1);

DIoTPRO.GsmReadSerial();
  delay(100);
  
  if (periodicsend > 0 && millis() > nextsend&& GsmPower == 1 && net == 1 && GsmTmp != "" && GsmTmp2 != "")
  {
    GsmTmp = ""; GsmTmp2 = "OK";
    nextsend = millis() + (periodicsend * 1000);
  }
  else if (periodicsend > 0 && millis() > nextsend&& GsmPower == 0) {
    DIoTPRO.InitDiot();
  }
  else if (periodicsend > 0 && millis() > nextsend&& net == 0)
    DIoTPRO.PrepareSocket();
    Retval = Prm1 + " Calling...";                                      //make a call
    Serial.println("");
    Serial.println(Retval);
    Retval += DIoTPRO.GsmSendAT("ATD" + Prm1 + ";", RN, 2000, OKRN);
    DIoTPRO.GsmSendAT("AT+QAUDCH=2", RN, 2000, OKRN);
    delay(2000);
    delay(500);   
// Retval = GsmSendAT("ATA", RN, 2000, OKRN);                                 //answer the call
// Retval += GsmSendAT("ATH", RN, 2000, OKRN);                                //reject the call 

 //******************YOUR PHONE IS RINGING*****************//  
 /*
  if(s==1)
  { digitalWrite(PinBuzzer,HIGH);
  delay(250);
  digitalWrite(PinBuzzer,LOW);
  delay(20);
   digitalWrite(PinBuzzer,HIGH);
  delay(150);
 digitalWrite(PinBuzzer,LOW);
  digitalWrite(PinBuzzer,HIGH);
  delay(250);
  digitalWrite(PinBuzzer,LOW);
  delay(20);
   digitalWrite(PinBuzzer,HIGH);
  delay(150);
 digitalWrite(PinBuzzer,LOW);
 test++;
 if(test>4)
 {
 s=0;
 } 
 }
*/

}
}
