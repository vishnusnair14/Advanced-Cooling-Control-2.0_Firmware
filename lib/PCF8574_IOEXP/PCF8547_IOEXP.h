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

// pin mapping [PCF8574 1: I2C_RELAY #1]
#define PELTIER1 0
#define PELTIER2 1
#define PELTIER3 2
#define PELTIER4 3
#define AC_BLOWERFAN 4
#define RADIATOR_FAN 5
#define HS_WATERPUMP 6
#define CS_WATERPUMP 7

// pin mapping [PCF8574 2: I2C_RELAY #2]
#define CABINEXHAUST1_IN 0
#define CABINEXHAUST1_OUT 1
#define CABINEXHAUST2_IN 2
#define CABINEXHAUST2_OUT 3
#define CABIN2_LIGHT 4
#define NOCP0 5
#define NOCP1 6
#define NOCP2 7

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
#define I2C_RELAY1_ADDR 0x20  // I2C_RELAY  #1
#define I2C_RELAY2_ADDR 0x38  // I2C_RELAY  #2

// Initiates PCF8574 class
PCF8574 I2C_RELAY1(I2C_RELAY1_ADDR);
PCF8574 I2C_RELAY2(I2C_RELAY2_ADDR);

// pin initiator/beginner for PCF8574 [I2C_RELAY #1]:
void init_I2C_RELAY1_IEM() {
  pinMode(PELTIER1, OUTPUT);
  pinMode(PELTIER2, OUTPUT);
  pinMode(PELTIER3, OUTPUT);
  pinMode(PELTIER4, OUTPUT);
  pinMode(AC_BLOWERFAN, OUTPUT);
  pinMode(RADIATOR_FAN, OUTPUT);
  pinMode(HS_WATERPUMP, OUTPUT);
  pinMode(CS_WATERPUMP, OUTPUT);
  Serial.println(F("P203"));   // P203: "I2C_RELAY #1 I/O pins initiated"
  if(I2C_RELAY1.begin()) { 
    Serial.println(F("P202"));   // P202: "Successfully initialised I2C_RELAY #1"
  }
  else if(!I2C_RELAY1.begin()) {
    Serial.println(F("P204"));  // P204: "I2C_RELAY #1 device error!"
  }

  if(I2C_RELAY1.isConnected()) {
    Serial.println(F("P208")); // P208: "I2C RELAY #1 is connected"
  }
  else if(!I2C_RELAY1.isConnected()) {
    Serial.println(F("P209")); // P209: "I2C RELAY #1 is disconnected"
  }
  I2C_RELAY1.selectAll();   // initially release all relays [I2C_RELAY #1]
  }

// pin initiator/beginner for PCF8574 [I2C_RELAY #2]:
void init_I2C_RELAY2_IEM() {
  pinMode(CABINEXHAUST1_IN, OUTPUT);
  pinMode(CABINEXHAUST1_OUT, OUTPUT);
  pinMode(CABINEXHAUST2_IN, OUTPUT);
  pinMode(CABINEXHAUST2_OUT, OUTPUT);
  pinMode(CABIN2_LIGHT, OUTPUT);
  pinMode(NOCP0, OUTPUT);
  pinMode(NOCP1, OUTPUT);
  pinMode(NOCP2, OUTPUT);
  Serial.println(F("P206"));   // P204: "I2C_RELAY2 I/O pins initiated"
  if(I2C_RELAY2.begin()){
    Serial.println(F("P205"));  // P205: "Successfully initialised I2C_RELAY #2"
  }
  else {
    Serial.println(F("P207"));  // P204: "I2C_RELAY #2 device error!"
  }

  if(I2C_RELAY2.isConnected()) {
    Serial.println(F("P210")); // P208: "I2C RELAY #2 is connected"
  }
  else if(!I2C_RELAY2.isConnected()) {
    Serial.println(F("P211")); // P209: "I2C RELAY #2 is disconnected"
  }
  I2C_RELAY2.selectAll();   //initially release all relays [I2C_RELAY #2]
}
