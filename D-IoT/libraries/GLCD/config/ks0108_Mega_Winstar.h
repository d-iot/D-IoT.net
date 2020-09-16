/*
 * ks0108_Mega.h - User specific configuration for Arduino GLCD library
 *
 * Use this file to set io pins
 *
 * The configuration below uses a single port for data 
 * and has the same wiring as the mega config from the previous ks0108 library 
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
#define glcd_PinConfigName "ks0108-Mega"

/*********************************************************/
/*  Configuration for assigning LCD bits to Arduino Pins */
/*********************************************************/
/*
 * Pins used for Commands
 */
//                     MEGA  LCDINFI		LCDPIN
//						--	  --			------	------


#define glcdCSEL1       32	//CS1 Bit		01
#define glcdCSEL2       31	//CS2 Bit		02
 							//GND			03		GND
							//+5			04		5V
							//V0/NC			05		POD ORTA
#define glcdDI          33	//RS-DI			06
#define glcdRW          34	//R/W    		07
#define glcdEN          35	//EN			08
#define glcdData0Pin    36	//D0			09  
#define glcdData1Pin    37	//D1			10
#define glcdData2Pin    38	//D2			11
#define glcdData3Pin    39	//D3			12
#define glcdData4Pin    40	//D4			13
#define glcdData5Pin    41	//D5			14
#define glcdData6Pin    42	//D6			15
#define glcdData7Pin    43	//D7			16
							//RST			17  
							//VEE			18		PODSOL
							//A+			19		3.3V
							//A-			20		GND
							//			PODSAÐ		+5V

		// Reset Bit  - uncomment the next line if reset is connected to an output pin
		//#define glcdRES         27    // Reset Bit

		#if NBR_CHIP_SELECT_PINS > 2
		#define glcdCSEL3     22   // third chip select if needed
		#endif

		#if NBR_CHIP_SELECT_PINS > 3
		#define glcdCSEL4     23   // fourth chip select if needed
		#endif






#endif //GLCD_PIN_CONFIG_H
