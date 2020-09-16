/*
 * ks0108_Arduino.h - User specific configuration for Arduino GLCD library
 *
 * Use this file to set io pins
 * This version is for a standard ks0108 display
 * connected using the default Arduino wiring
 *
*/

#if defined (__AVR__)
// Workaround for http://gcc.gnu.org/bugzilla/show_bug.cgi?id=34734
// to prevent: warning: only initialized variables can be placed into program memory area
#ifdef PROGMEM
#undef PROGMEM
#define PROGMEM __attribute__((section(".progmem.data")))
#endif
#endif

#ifndef GLCD_PIN_CONFIG_H
#define GLCD_PIN_CONFIG_H

/*
 * define name for pin configuration
 */
#define glcd_PinConfigName "ks0108-Arduino"

/*********************************************************/
/*  Configuration for assigning LCD bits to Arduino Pins */
/*********************************************************/


//                          //UNO	LCDINFO		LCDPIN
//						--	  --	--------	------
#define glcdCSEL1       PIN_C1  //A1	CS1 Bit		01
#define glcdCSEL2       PIN_C2  //A2	CS2 Bit		02
								//--	GND			03
								//--	+5			04
								//--	POD ORTA	05
#define glcdDI          PIN_C3  //A3	RS-DI		06
#define glcdRW          PIN_C4  //A4	R/W Bit		07
#define glcdEN          PIN_C5  //A5	EN Bit		08
#define glcdData0Pin    PIN_D2	//02	D0			09
#define glcdData1Pin    PIN_D3	//03	D1			10
#define glcdData2Pin    PIN_D4	//04	D2			11
#define glcdData3Pin    PIN_D5	//05	D3			12
#define glcdData4Pin    PIN_D6	//06	D4			13
#define glcdData5Pin    PIN_D7	//07	D5			14
#define glcdData6Pin    PIN_B0	//08	D6			15
#define glcdData7Pin    PIN_B1	//09	D7			16
								//--	RST			17  
								//--	VEE			18
								//--	A+			19
								//--	A-			20
// Reset Bit  - uncomment the next line if reset is connected to an output pin
//#define glcdRES         27    // Reset Bit
#if NBR_CHIP_SELECT_PINS > 2
#define glcdCSEL3     3   // third chip select if needed
#endif

#if NBR_CHIP_SELECT_PINS > 3
#define glcdCSEL4     2  // fourth chip select if needed
#endif

#endif //GLCD_PIN_CONFIG_H

