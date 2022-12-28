/*
[Part of ADVANCED COOLING CONTROL ALGORITHM]

PCF8574 I/O expander external arduino compatible library
--------------------------------------------------------

(I2C Protocol based) For scanning address of the available 
connected PCF8574 I2C modules and to initiate its pins in
arduino environment.

[vishnus_technologies (C) 2022]
----------------------------------------------------------
*/

#include <PCF8574.h>
#include <Wire.h>
#include <Buzzer.h>

// pin mapping:
#define PE1 P0
#define PE2 P1
#define FCF P2
#define CSWP P3
#define HSWP P4
#define CEXAH1 P5
#define CEXAH2 P6
int nDevices;

/* ------------------------------------
set your PCF8574's address accordingly:
[PCF8574 8-BIT ADDRESS TABLE]
1. 000 = 0x20 (by default)
2. 001 = 0x21
3. 010 = 0x22
4. 011 = 0x23
5. 100 = 0x24
6. 101 = 0x25
7. 110 = 0x26
8. 111 = 0x27
---------------------------------------
define PCF8574's module address below:  */
#define PCF8574_DEVICE_ADDRESS 0x21

// starts PCF8574 class
PCF8574 pcf8574(PCF8574_DEVICE_ADDRESS);

// pin initiator for PCF8574:
void Init_PCF8574Module() {
  pcf8574.pinMode(PE1, OUTPUT);
  pcf8574.pinMode(PE2, OUTPUT);
  pcf8574.pinMode(FCF, OUTPUT);
  pcf8574.pinMode(CSWP, OUTPUT);
  pcf8574.pinMode(HSWP, OUTPUT);
  Serial.println(F("P203"));   // P203: "PCF8574 I/O pins initiated"
  if (pcf8574.begin()) { 
    // PCF8574 pin mode definition:
    Serial.println(F("P202"));   // P202: "Successfully initialised PCF8574 module"
    normalBeep(4500, 4, 250);  
  }
  else { 
    Serial.println(F("P204"));  // P204: "PCF8574 device error!"
  }
}
