
<h4> 1. REQUIREMENT EQUIPMENT </h1>
 
1. D-IoT 2560 PRO DEVELOPMENT BOARD 
 
                         The D-IoT 2560 Pro Development Board is an Atmel ATmega2560 processor based development board. There are GSM/GNSS, Bluetooth, CanBus, SD Card, LDR, Temperature-Humidity, Relay, Optocoupler, Buzzer, Led, 3D Accelerometer Sensors on it. D-IoT 2560 Pro Development Board is cloud-based and development card integrated with IoT platform. (portal.d-iot.net) 
 
2.NEXTION DISPLAY 
 
 
        NEXTION is available in various LCD display sizes including 2.4”, 2.8”, 3.2”, 3.5”, 4.3”, 5.0”, 7.0”. NEXTION Editor software offers an easy way to create the perfect touch user interface, even for beginners. In this project, we will use Nextion Basic Model NX8048T070 (7.0”). 
 
3. USB CABLE                                            
 
 
4. USB to TTL 
 
 
5. PHONE CHARGER (5V DC 0.5A) 1 PCS 
 
 
 
6. MICRO SD CARD WITH ADAPTER 1 PCS 
 
 
2.CONNECTIONS 
 
1. UPLOADING TFT FILE TO THE NEXTION HMI DISPLAY MODULE 
 
2. USING THE NEXTION HMI DISPLAY MODULE WITH D-IOT 2560 PRO 
 
 
 
3.NEXTION EDITOR DOWNLOAD 
 
1. Go to Nextion website and download the Nextion Editor 1.61.2 by clicking on “EXE Download”. 
 
 
2. Click on “Next” button to start installation. 
 
3. Click the “Next” button.
 
4. Click the “Install” button. 
 
 
5. You will see the shortcut on your PC desktop and the Nextion Editor starts automatically after installation is done. 
 
           
 
 
4.CODE 
 
We have attached the ITEADLIB_Arduino_Nextion library. This library is configured for Arduino MEGA2560 by default. First of all, ITEADLIB_Arduino_Nextion library Download and add to libraries in your PC. For example;   C:\Users\MyPC\Documents\Arduino\libraries or C:\Program Files (x86)\Arduino\libraries.  Find ITEADLIB_Arduino_Nextion library in this link. Install the library in Arduino IDE program file on your computer. Reach the codes this link. 
 
 
 
 
Codes for Making a call: 
 
if(numberdeger3==1){  
  control=String(numbervalue); 
  control2=String(numbervalue2); 
  Prm1=""; 
  Prm1="0"+control1+""+control2; 
  Serial.println(Prm1); 
   Retval = Prm1 + " Calling..."; 
   Serial.println(""); 
   Serial.println(Retval); 
   Retval += GsmSendAT("ATD" + Prm1 + ";", RN, 2000, OKRN); 
   GsmSendAT("AT+QAUDCH=2", RN, 2000, OKRN); 
   delay(2000); 
   delay(500); 
} 
 
 
Retval = GsmSendAT("ATA", RN, 2000, OKRN); 
   Retval = GsmSendAT("ATA", RN, 2000, OKRN)  the command is the AT command to be used to answer the call. 
Retval += GsmSendAT("ATH", RN, 2000, OKRN); 
   Retval += GsmSendAT("ATH", RN, 2000, OKRN)  the command is the AT command to be used to reject the call. 
 
 
 
5. USING THE NEXTION EDITOR 
 
 
 
1. Main Menu including new, save, debug etc. 2. Toolbox has interface options in a very simple way you can add pictures, text, buttons, slider and there are more. 3. Picture Library; The picture used in Nextion the screen should be installed in advance. You can use the backgrounds and images uploaded here as you wish.   Font library; Fonts in specific sizes and styles are created and then configured for a particular screen. You can use the font file is added. 4. You can increase or decrease the number of pages. It allows you to easily change between pages. 5. Attributes, including text size, color, value, type  etc. 
 
 
 
 
Open Nextion, you download the NEXTION MOBILE-PHONE-CERTIFICATE select the file and examine the project develops as you wish. 
 
❖ Press to “New” file. The name write from your want in the created file. 
 
❖  As shown above the model  of your screen select. 

 
❖ As shown above, adjust the direction of your screen. 
 
 
❖ As shown above,follow the steps. 
 
 
 
 
❖ As shown below as an example; if you want to upload an image, click the “Picture” option in the “Toolbox” section. You can set the size etc in the “Attribute”, and section by pressing on the “p0” tab on the screen. In the “Attribute” section, select the browse feature on the pic tab and the picture select uploaded in the “Picture” library here. 
 
 
 
 
 
❖ As shown below upload picture to your screen. 
 
 
❖ Press the “Compile” and then press the “Debug”. The preview page is open. 
 
 
❖ Programs tab enter a variable. 
 
❖ According to the feature you use to write your code in each button  “Touch Event Press” and “Touch Release Events” tab. 
 
6.UPLOAD PROGRAM FOR D-IoT 2560 PRO DEVELOPMENT BOARD     The D-IoT 2560PRO Development Board connects to your computer with the USB cable as shown in the picture and download the program.
 
❖ Primarily, “Arduino/Genuino Mega or Mega 2560” select the card in the tools section. Check as shown below.  
 
 
❖ As shown below install. 
 
 
 
7.NEXTION SCREEN WALLPAPER 
 
Reach the codes this link.
