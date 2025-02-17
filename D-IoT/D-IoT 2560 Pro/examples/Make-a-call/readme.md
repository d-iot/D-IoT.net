
<h2> 1. REQUIREMENT EQUIPMENT </h2>
 
**1. D-IoT 2560 PRO DEVELOPMENT BOARD** 

![1](https://user-images.githubusercontent.com/61791991/93344175-08f09e80-f83a-11ea-9570-6cdc7eafe63a.png)

 
    The D-IoT 2560 Pro Development Board is an Atmel ATmega2560 processor based development board.
    There are GSM/GNSS, Bluetooth, CanBus, SD Card, LDR, Temperature-Humidity, Relay, Optocoupler,
    Buzzer, Led, 3D Accelerometer Sensors on it. D-IoT 2560 Pro Development Board is cloud-based and 
    development card integrated with IoT platform. (portal.d-iot.net) 
                         
 
**2.NEXTION DISPLAY** 

 ![2](https://user-images.githubusercontent.com/61791991/93344271-24f44000-f83a-11ea-961c-706e9995f14e.png)
 
 
     NEXTION is available in various LCD display sizes including 2.4”, 2.8”, 3.2”, 3.5”, 4.3”, 5.0”, 7.0”.
     NEXTION Editor software offers an easy way to create the perfect touch user interface, even for beginners.
     In this project, we will use Nextion Basic Model NX8048T070 (7.0”). 
        
 
**3. USB CABLE**                                            

![3](https://user-images.githubusercontent.com/61791991/93344341-3a696a00-f83a-11ea-94e6-6a0f0a2c4ef7.png)

 
**4. USB to TTL** 

 ![4](https://user-images.githubusercontent.com/61791991/93344359-43f2d200-f83a-11ea-9dd6-9b0a6ce1f74b.png)
 
 
**5. PHONE CHARGER (5V DC 0.5A) 1 PCS** 


![5](https://user-images.githubusercontent.com/61791991/93344384-4ead6700-f83a-11ea-90f9-0abbfb9099a6.png)

 
 
**6. MICRO SD CARD WITH ADAPTER 1 PCS** 


 ![6](https://user-images.githubusercontent.com/61791991/93344421-5a992900-f83a-11ea-8f74-3318582872ef.png)

 
<h2> 2.CONNECTIONS </h2>
 
**1. UPLOADING TFT FILE TO THE NEXTION HMI DISPLAY MODULE** 

 ![7](https://user-images.githubusercontent.com/61791991/93344439-6127a080-f83a-11ea-9285-939ed2061c67.png)
 
**2. USING THE NEXTION HMI DISPLAY MODULE WITH D-IOT 2560 PRO** 
 
 
 ![8](https://user-images.githubusercontent.com/61791991/93344525-743a7080-f83a-11ea-8320-1fc5e81d146c.png)

 
 
<h2> 3.NEXTION EDITOR DOWNLOAD </h2>
 
**1. Go to Nextion website and download the Nextion Editor 1.61.2 by clicking on “EXE Download”.** 


 ![9](https://user-images.githubusercontent.com/61791991/93344557-7ac8e800-f83a-11ea-9edf-0133f372d6e5.png)

 
 

**2. Click on “Next” button to start installation.** 

![10](https://user-images.githubusercontent.com/61791991/93344638-92a06c00-f83a-11ea-8762-f722c505ad53.png)


 
**3. Click the “Next” button.**

 ![11](https://user-images.githubusercontent.com/61791991/93344664-9a601080-f83a-11ea-81df-1ee9561a02e9.png)

 

**4. Click the “Install” button.** 

![12](https://user-images.githubusercontent.com/61791991/93345784-e52e5800-f83b-11ea-9337-900c11bc986a.png)

 

 
**5. You will see the shortcut on your PC desktop and the Nextion Editor starts automatically after installation is done.** 

 ![13-1](https://user-images.githubusercontent.com/61791991/93345956-19097d80-f83c-11ea-81ad-5370a7c932f0.png) ![13](https://user-images.githubusercontent.com/61791991/93345821-f1b2b080-f83b-11ea-96d6-705ac106da97.png)

 
<h2> 4.CODE </h2>
 
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
 
 
![14](https://user-images.githubusercontent.com/61791991/93346307-82898c00-f83c-11ea-86fc-39cb908c9a28.png)


   Retval = GsmSendAT("ATA", RN, 2000, OKRN)  the command is the AT command to be used to answer the call. 
   
   
![15](https://user-images.githubusercontent.com/61791991/93346365-92a16b80-f83c-11ea-9187-2666898d6a2f.png)


   Retval += GsmSendAT("ATH", RN, 2000, OKRN)  the command is the AT command to be used to reject the call. 
 
 
 
<h2> 5. USING THE NEXTION EDITOR</h2>
 
 
 ![16](https://user-images.githubusercontent.com/61791991/93346708-ee6bf480-f83c-11ea-9367-cb563838d8eb.png)


 
1. Main Menu including new, save, debug etc. 2. Toolbox has interface options in a very simple way you can add pictures, text, buttons, slider and there are more. 3. Picture Library; The picture used in Nextion the screen should be installed in advance. You can use the backgrounds and images uploaded here as you wish.   Font library; Fonts in specific sizes and styles are created and then configured for a particular screen. You can use the font file is added. 4. You can increase or decrease the number of pages. It allows you to easily change between pages. 5. Attributes, including text size, color, value, type  etc. 
 
 
 
 
Open Nextion, you download the NEXTION MOBILE-PHONE-CERTIFICATE select the file and examine the project develops as you wish. 

![17](https://user-images.githubusercontent.com/61791991/93346780-00e62e00-f83d-11ea-8140-538c40777431.png)
 
❖ Press to “New” file. The name write from your want in the created file. 
 
 ![18](https://user-images.githubusercontent.com/61791991/93346817-0c395980-f83d-11ea-9155-4a4ad18255c2.png)
 
❖  As shown above the model  of your screen select. 

![19](https://user-images.githubusercontent.com/61791991/93346845-15c2c180-f83d-11ea-9954-d84d105b2678.png)

 
❖ As shown above, adjust the direction of your screen. 


![20](https://user-images.githubusercontent.com/61791991/93346912-283cfb00-f83d-11ea-8b8d-8d8f206e09af.png)

 
 
❖ As shown above,follow the steps. 
 
 
 
❖ As shown below as an example; if you want to upload an image, click the “Picture” option in the “Toolbox” section. You can set the size etc in the “Attribute”, and section by pressing on the “p0” tab on the screen. In the “Attribute” section, select the browse feature on the pic tab and the picture select uploaded in the “Picture” library here. 
 
 
  ![21](https://user-images.githubusercontent.com/61791991/93346951-37bc4400-f83d-11ea-96ef-79c0f141ce1f.png)
  

 
 
❖ As shown below upload picture to your screen. 

 ![22](https://user-images.githubusercontent.com/61791991/93346993-44409c80-f83d-11ea-8c88-07d10926a8ac.png)
 
 ![23](https://user-images.githubusercontent.com/61791991/93347079-57ec0300-f83d-11ea-92fb-014864cfd4b2.png)

 
 
❖ Press the “Compile” and then press the “Debug”. The preview page is open. 

![24](https://user-images.githubusercontent.com/61791991/93347100-60443e00-f83d-11ea-969a-b5b2d82be876.png)


 
 
❖ Programs tab enter a variable. 


![25](https://user-images.githubusercontent.com/61791991/93347132-689c7900-f83d-11ea-9f4f-c851053b33e4.png)


 
❖ According to the feature you use to write your code in each button  “Touch Event Press” and “Touch Release Events” tab. 
 
<h4> 6.UPLOAD PROGRAM FOR D-IoT 2560 PRO DEVELOPMENT BOARD </h4>
 
The D-IoT 2560PRO Development Board connects to your computer with the USB cable as shown in the picture and download the program.

![26](https://user-images.githubusercontent.com/61791991/93347668-02fcbc80-f83e-11ea-8198-3f1272d8effc.png)
 
❖ Primarily, “Arduino/Genuino Mega or Mega 2560” select the card in the tools section. Check as shown below.  
 
 ![27](https://user-images.githubusercontent.com/61791991/93348230-9f26c380-f83e-11ea-8d17-5081e38fbfac.png)

 
❖ As shown below install. 
 
 ![28](https://user-images.githubusercontent.com/61791991/93348253-a64dd180-f83e-11ea-9eaf-a1e0dacfb56b.png)
 
<h2> 7.NEXTION SCREEN WALLPAPER </h2>

![29](https://user-images.githubusercontent.com/61791991/93348289-afd73980-f83e-11ea-97eb-d17ce8ea53e4.png)
 
Reach the codes this link.
