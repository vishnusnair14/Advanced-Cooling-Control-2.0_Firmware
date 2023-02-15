/*
[Part of ADVANCED COOLING CONTROL ALGORITHM]

PCF8574 I/O expander, external arduino UNO compatible library
-------------------------------------------------------------

Setup library for PCF8574 I/O Expansion modules.
Each module controls two different 'Device Relay Control Blocks',
~(controls two PCF8574 modues, total (8*2) 16 I/O pins).

(I2C Protocol based) For scanning address of the available 
connected PCF8574 I2C modules and to initiate its pins in
arduino environment.

[vishnus_technologies (C) 2022]
-----------------------------------------------------------------
*/

#include <PCF8574.h>
#include <Wire.h>
#include <Buzzer.h>

// pin mapping [PCF8574 1: DRCM#1]
#define PE1 P0
#define PE2 P1
#define PE3 P2
#define PE4 P3
#define AC_BFAN P4
#define RAD_FAN P5
#define HSWP P6
#define CSWP P7

// pin mapping [PCF8574 2: DRCM#2]
#define CEXAH1_IN P0
#define CEXAH1_OUT P1
#define CEXAH2_IN P2
#define CEXAH2_OUT P3
#define CAB_LIGHT P4
#define NOCP0 P5
#define NOCP1 P6
#define NOCP2 P7

/* ------------------------------------
change your PCF8574's address accordingly:
[PCF8574 8-BIT ADDRESS TABLE]
1. 000 = 0x20 (by default)
2. 001 = 0x21
3. 010 = 0x22
4. 011 = 0x23
5. 100 = 0x24
6. 101 = 0x25
7. 110 = 0x26
8. 111 = 0x27
--------------------------------------- */

// define PCF8574 addresses:
#define DRCM1_IOEXP_ADDR 0x20  // DRCM #1
#define DRCM2_IOEXP_ADDR 0x39  // DRCM #2

// Initiates PCF8574 class
PCF8574 DRCM1(DRCM1_IOEXP_ADDR);
PCF8574 DRCM2(DRCM2_IOEXP_ADDR);

// pin initiator/beginner for PCF8574 [DRCM#1]:
void init_DRCM1_IEM() {
  DRCM1.pinMode(PE1, OUTPUT);
  DRCM1.pinMode(PE2, OUTPUT);
  DRCM1.pinMode(PE3, OUTPUT);
  DRCM1.pinMode(PE4, OUTPUT);
  DRCM1.pinMode(AC_BFAN, OUTPUT);
  DRCM1.pinMode(RAD_FAN, OUTPUT);
  DRCM1.pinMode(HSWP, OUTPUT);
  DRCM1.pinMode(CSWP, OUTPUT);
  Serial.println(F("P203"));   // P203: "DRCM1 I/O pins initiated"
  if (DRCM1.begin()) { 
    Serial.println(F("P202"));   // P202: "Successfully initialised DRCM module #1"
    normalBeep(4500, 4, 250);
  }
  else { 
    Serial.println(F("P204"));  // P204: "DRCM#1 device error!"
  }
}

// pin initiator/beginner for PCF8574 [DRCM#2]:
void init_DRCM2_IEM() {
  DRCM2.pinMode(CEXAH1_IN, OUTPUT);
  DRCM2.pinMode(CEXAH1_OUT, OUTPUT);
  DRCM2.pinMode(CEXAH2_IN, OUTPUT);
  DRCM2.pinMode(CEXAH2_OUT, OUTPUT);
  DRCM2.pinMode(CAB_LIGHT, OUTPUT);
  DRCM2.pinMode(NOCP0, OUTPUT);
  DRCM2.pinMode(NOCP1, OUTPUT);
  DRCM2.pinMode(NOCP2, OUTPUT);
  Serial.println(F("P206"));   // P204: "DRCM2 I/O pins initiated"
  if (DRCM2.begin()){
    Serial.println(F("P205"));  // P205: "Successfully initialised DRCM module #2"
    normalBeep(4500, 4, 250);
  }
  else {
    Serial.println(F("P207"));  // P204: "DRCM#2 device error!"
  }
}
