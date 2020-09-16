#ifndef DIoT2560PRO_h
#define DIoT2560PRO_h
#include "Arduino.h"
#include <avr/wdt.h>  

class DIoTPRO
{
public:
void call(String number);  
String GsmSendAT(String CmdAT, String  EndChar, long tmout, String Waitval);
String GsmSendAT2Data(String CmdAT, String EndChar, long tmout, String Waitval, String& Data, String GetValStart, String GetValEnd);
String StrExtract(String Data, String Tag1, String Tag2);
int GsmPowerOff();
int GsmPowerState();
int GsmPowerOn();
String CmdHandler(String CmdStr);
void SendTcpData(String Message);
void btsend(String btret, String conid);
String SplitString(String data, char separator, int index);
void GsmReadSerial();
void GpsPowerOn();
void GpsPowerOff();
String SendSms(String Number, String Msg);
void SocketInit();
void InitializeGsm();
void InitDiot();
String gettoken();
boolean isValidNumber(String str);
void PrepareSocket();
void StartMpu();
void MotionDetect();
void mpu_getxyz();
void GMT(int gmtvalue);
String  GetBatteryVoltage();
void reg();
String savedeviceid(String did);
String readdeviceid();
String savetoken(String token);

//void ReadTempHumid();

private:
};

#endif;
