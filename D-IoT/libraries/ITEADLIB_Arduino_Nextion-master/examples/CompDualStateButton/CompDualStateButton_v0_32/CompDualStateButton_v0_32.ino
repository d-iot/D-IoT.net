
#include "Nextion.h"
#include "SoftwareSerial.h"

SoftwareSerial HMISerial(2,2);

NexDSButton bt0 = NexDSButton(0, 15, "b0");
NexText t0 = NexText(0, 2, "t0");
uint32_t butondurum=0;


char buffer[100] = {0};

NexTouch *nex_listen_list[] = 
{
    &bt0,
    NULL
};

void bt0PopCallback(void *ptr)
{
    uint32_t dual_state;
    NexDSButton *btn = (NexDSButton *)ptr;
    dbSerialPrintln("b0PopCallback");
    dbSerialPrint("ptr=");
    dbSerialPrintln((uint32_t)ptr); 
    memset(buffer, 0, sizeof(buffer));
    bt0.getValue(&dual_state);
    if(dual_state) 
    {
        t0.setText("HI! OPEN STATE");
    }
    else
    {
        t0.setText("HI! OFF STATE");
    }
}

void setup(void)
{    
  dbSerialPrintln("setup begin");
    /* Set the baudrate which is for debug and communicate with Nextion screen. */
    nexInit();

    /* Register the pop event callback function of the dual state button component. */
    bt0.attachPop(bt0PopCallback, &bt0);
    
    dbSerialPrintln("setup done");
    pinMode(4,OUTPUT); 
}

void loop(void)
{   
     bt0.getValue(&butondurum);

     delay(200);

     if(butondurum==1)
     {
      digitalWrite(4,HIGH);
      delay(500);
      }

      else  if(butondurum==0)
     {
      digitalWrite(4,LOW);
      delay(500);
      }
 
}












