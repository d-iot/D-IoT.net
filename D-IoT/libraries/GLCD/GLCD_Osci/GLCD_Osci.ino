/*
 This Code is Designed by Prasad Pandit
 www.vhdlcodes.com
 Please keep this header if you are using this code for non-commercial use.
 For using it commercially or posting it on your website contact Author on
 Email: prasadp4009@gmail.com
 
 Instructions:
 Add the glcd folder in your libraries folder in Arduino folder
 It should be like Arduino>libraries>glcd
 
 You need to make changes in pin numbers according to your module.
 You can do that by editing in header files in glcd>config folder.
 I have made changes in k1080_mega.h as per my own needs.
 
 Please make sure to connect a 10K or 5K POT at Analog pin2.
 
  The circuit:
  See the inlcuded documentation in glcd/doc directory for how to wire
  up the glcd module. glcd/doc/GLCDref.htm can be viewed in your browser
  by clicking on the file.
 
 */

// include the library header
#include <glcd.h>
#include "config/ks0108_Arduino.h"
//#include "fonts/allFonts.h"
#include "fonts/Verdana_digits_24.h"

int sig_v[113];
void setup() {
  // Initialize the GLCD 
 GLCD.Init();
 GLCD.ClearScreen();
//delay(1000); 
//  GLCD.SelectFont(Verdana24);
GLCD.DrawVLine(5, 2, 54, BLACK);
GLCD.DrawVLine(1, 2, 54, BLACK);
GLCD.print("123456789012345678902315456");

//  GLCD.CursorToXY(82,57);
// GLCD.CursorToXY( 0,2);
// GLCD.print("5V");
// GLCD.CursorToXY(0,46);
// GLCD.print("0V");
// GLCD.DrawHLine(0, 54, 127, BLACK);
// GLCD.DrawHLine(11, 53, 3, BLACK);
// GLCD.DrawHLine(11, 26, 3, BLACK);
// GLCD.DrawHLine(11, 0, 3, BLACK);
// GLCD.CursorToXY(0,57);
// GLCD.print("Ti/Div:");
// 
// GLCD.DrawVLine(78, 55, 8, BLACK);
//  GLCD.CursorToXY(82,57);

// // Serial.begin(9600);
//
// // Select the font for the default text area
  }

void loop() {



  }
