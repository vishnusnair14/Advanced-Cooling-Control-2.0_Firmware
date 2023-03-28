/*
[Part of ADVANCED COOLING CONTROL ALGORITHM]

Intelli control algorithm for Relay Control Systems
---------------------------------------------------

Controls device control relay modules. These systems are used for controlling (ON/OFF)
thermoelectric devices, coolants, exhausts etc... based only on thermal sensor values.
Mainly it control two independent RCS(s), named RCS-1, RCS-2.
-> DRCM-1 controls all coolant fans, radiator, exhausts, based on the tempsensor-1 @A0, 
-> DRCM-2 controls all thermoelectric devices systems, based on tempsensor-2 @A1

[vishnus_technologies (C) 2022]
---------------------------------------------------------------------------------------
*/

#include <Arduino.h>

// relay states:
#define TRIGG_RELAY LOW
#define RELEASE_RELAY HIGH

// temperature state constants:
#define LOW_TEMP 14
#define MEDIAN_TEMP 22
#define HIGH_TEMP 32

// RELAY SWITCHING CONTROL SECTION (RSCS):
void relaySwitchControl(uint8_t _deviceID, bool _state) {
  String _relayID = "";
  uint8_t _devicePin;

  // check with I2C_RELAY #1 pin ID's:
  if(_deviceID == 101) { _relayID = "R11"; _devicePin = 0; }   // [R11 - R18: for ]
  else if(_deviceID == 102) { _relayID = "R12"; _devicePin = 1; }
  else if(_deviceID == 103) { _relayID = "R13"; _devicePin = 2; }
  else if(_deviceID == 104) { _relayID = "R14"; _devicePin = 3; }
  else if(_deviceID == 105) { _relayID = "R15"; _devicePin = 4; }   
  else if(_deviceID == 106) { _relayID = "R16"; _devicePin = 5; }
  else if(_deviceID == 107) { _relayID = "R17"; _devicePin = 6; }
  else if(_deviceID == 108) { _relayID = "R18"; _devicePin = 7; } 
  // check match with I2C_RELAY #2 pin ID's:
  else if(_deviceID == 201) { _relayID = "R21"; _devicePin = 0; }
  else if(_deviceID == 202) { _relayID = "R22"; _devicePin = 1; }
  else if(_deviceID == 203) { _relayID = "R23"; _devicePin = 2; }
  else if(_deviceID == 204) { _relayID = "R24"; _devicePin = 3; }
  else if(_deviceID == 205) { _relayID = "R25"; _devicePin = 4; }
  else if(_deviceID == 206) { _relayID = "R26"; _devicePin = 5; }
  else if(_deviceID == 207) { _relayID = "R27"; _devicePin = 6; }
  else if(_deviceID == 208) { _relayID = "R28"; _devicePin = 7; }
  // if _deviceID were arduino digital pin itself:
  else if(_deviceID >= 0 and _deviceID <= 13) {
    _relayID = "R1";    // [R1: for devices conn. to arduino digital pins directly]
    _devicePin = _deviceID; 
  }
  else {
    _relayID = "R0";
  }

  uint8_t IO_PinBatch = _relayID.substring(1, 3).toInt(); 

  if(IO_PinBatch >= 11 and IO_PinBatch <= 18) {    // for I2C_RELAY #1 I/O pins. ID:[10 - 19]
    // @_state: 1/HIGH
    if(_state == TRIGG_RELAY) {
      if(I2C_RELAY1.read(_devicePin) != _state) {
        I2C_RELAY1.write(_devicePin, TRIGG_RELAY); 
        Serial.print(_relayID);
        Serial.println(F(":An#"));  // decode command (for softwareDecodeEngine).
      }
      else if(I2C_RELAY1.read(_devicePin) == _state) {
        Serial.print(_relayID);
        Serial.println(F(":Bn#"));
      }
    }
    // @_state: 0/LOW
    else if(_state == RELEASE_RELAY) {
      if(I2C_RELAY1.read(_devicePin) != _state) {
        I2C_RELAY1.write(_devicePin, RELEASE_RELAY); 
        Serial.print(_relayID);
        Serial.println(":Xf#");
      }
      else if(I2C_RELAY1.read(_devicePin) == _state) {
        Serial.print(_relayID);
        Serial.println(":Yf#");
      }
    }
  }

  else if(IO_PinBatch > 20 and IO_PinBatch < 29) {   // for I2C_RELAY #2 I/O pins. ID:[20 - 29]
    // @_state: 1/HIGH
    if(_state == TRIGG_RELAY) {
      if(I2C_RELAY2.read(_devicePin) != _state) {
        I2C_RELAY2.write(_devicePin, TRIGG_RELAY); 
        Serial.print(_relayID);
        Serial.println(F(":An#"));
      }
      else if(I2C_RELAY2.read(_devicePin) == _state) {
        Serial.print(_relayID);
        Serial.println(F(":Bn#"));
      }
    }
    // @_state: 0/LOW
    else if(_state == RELEASE_RELAY) {
      if(I2C_RELAY2.read(_devicePin) != _state) {
        I2C_RELAY2.write(_devicePin, RELEASE_RELAY); 
        Serial.print(_relayID);
        Serial.println(":Xf#");
      }
      else if(I2C_RELAY2.read(_devicePin) == _state) {
        Serial.print(_relayID);
        Serial.println(":Yf#");
      }
    }
  }

  else if(IO_PinBatch >= 0 and IO_PinBatch <= 13) {   // for arduino digital pins. Pins:[0 - 13]
        // @_state: 1/HIGH
    if(_state == TRIGG_RELAY) {
      if(digitalRead(_devicePin) != _state) {
        digitalWrite(_devicePin, TRIGG_RELAY); 
        Serial.print(_relayID);
        Serial.println(F(":An#"));
      }
      else if(digitalRead(_devicePin) == _state) {
        Serial.print(_relayID);
        Serial.println(F(":Bn#"));
      }
    }
    // @_state: 0/LOW
    else if(_state == RELEASE_RELAY) {
      if(digitalRead(_devicePin) != _state) {
        digitalWrite(_devicePin, RELEASE_RELAY); 
        Serial.print(_relayID);
        Serial.println(":Xf#");
      }
      else if(digitalRead(_devicePin) == _state) {
        Serial.print(_relayID);
        Serial.println(":Yf#");
      }
    }
  }
}