//******************************************************************************
// IRremote
// Version 2.0.1 June, 2015
// Copyright 2009 Ken Shirriff
// For details, see http://arcfn.com/2009/08/multi-protocol-infrared-remote-library.html
//
// Modified by Paul Stoffregen <paul@pjrc.com> to support other boards and timers
//
// Interrupt code based on NECIRrcv by Joe Knapp
// http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1210243556
// Also influenced by http://zovirl.com/2008/11/12/building-a-universal-remote-with-an-arduino/
//
// JVC and Panasonic protocol added by Kristian Lauszus (Thanks to zenwheel and other people at the original blog post)
// Whynter A/C ARC-110WD added by Francesco Meschia
//******************************************************************************

#ifndef IRremoteint_h
#define IRremoteint_h

//------------------------------------------------------------------------------
// Include the Arduino header
//
#include <Arduino.h>

//------------------------------------------------------------------------------
// Information for the Interrupt Service Routine
//
#define RAWBUF  101  ///< Maximum length of raw duration buffer. Must be odd.

/**
 * This struct is used to communicate with the ISR (interrupt service routine).
 */
typedef struct {
    // The fields are ordered to reduce memory over caused by struct-padding
    uint8_t rcvstate;        ///< State Machine state
    uint8_t recvpin;         ///< Pin connected to IR data from detector
    uint8_t blinkpin;
    uint8_t blinkflag;       ///< true -> enable blinking of pin on IR processing
    uint8_t rawlen;          ///< counter of entries in rawbuf
    unsigned int timer;           ///< State timer, counts 50uS ticks.
    unsigned int rawbuf[RAWBUF];  ///< raw data
    uint8_t overflow;        ///< Raw buffer overflow occurred
} irparams_t;

// ISR State-Machine : Receiver States
#define IR_REC_STATE_IDLE      2
#define IR_REC_STATE_MARK      3
#define IR_REC_STATE_SPACE     4
#define IR_REC_STATE_STOP      5
#define IR_REC_STATE_OVERFLOW  6

/**
 * Allow all parts of the code access to the ISR data
 * NB. The data can be changed by the ISR at any time, even mid-function
 * Therefore we declare it as "volatile" to stop the compiler/CPU caching it
 */
#ifdef IR_GLOBAL
volatile irparams_t  irparams;
#else
extern volatile irparams_t irparams;
#endif

//------------------------------------------------------------------------------
// Defines for setting and clearing register bits
//
#ifndef cbi
#define cbi(sfr, bit)  (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
#define sbi(sfr, bit)  (_SFR_BYTE(sfr) |= _BV(bit))
#endif

//------------------------------------------------------------------------------
// Pulse parms are ((X*50)-100) for the Mark and ((X*50)+100) for the Space.
// First MARK is the one after the long gap
// Pulse parameters in uSec
//

/**
 * When received, marks  tend to be too long and
 * spaces tend to be too short.
 * To compensate for this, MARK_EXCESS is subtracted from all marks,
 * and added to all spaces.
 */
#define MARK_EXCESS    100

/** Relative tolerance (in percent) for some comparisons on measured data. */
#define TOLERANCE       25

/** Lower tolerance for comparison of measured data */
#define LTOL            (1.0 - (TOLERANCE/100.))

/** Upper tolerance for comparison of measured data */
#define UTOL            (1.0 + (TOLERANCE/100.))

/** Minimum gap between IR transmissions, in microseconds */
#define _GAP            5000

/** Minimum gap between IR transmissions, in USECPERTICK */
#define GAP_TICKS       (_GAP/USECPERTICK)

#define TICKS_LOW(us)   ((int)(((us)*LTOL/USECPERTICK)))
#define TICKS_HIGH(us)  ((int)(((us)*UTOL/USECPERTICK + 1)))

//------------------------------------------------------------------------------
// IR detector output is active low
//
#define MARK   0 ///< Sensor output for a mark ("flash")
#define SPACE  1 ///< Sensor output for a space ("gap")

// All board specific stuff have been moved to its own file, included here.
#include "IRremoteBoardDefs.h"

#endif
