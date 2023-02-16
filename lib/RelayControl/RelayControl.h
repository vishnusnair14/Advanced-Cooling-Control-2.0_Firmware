/*
[Part of ADVANCED COOLING CONTROL ALGORITHM]

Control algorithm for Temperature based Relay Control Systems
-------------------------------------------------------------

Controls device control relay modules. These systems are used for controlling (ON/OFF)
thermoelectric devices, coolants, exhausts etc... based only on thermal sensor values.
Mainly it control two independent RCS(s), named RCS-1, RCS-2.
-> DRCM-1 controls all coolant fans, radiator, exhausts, based on the tempsensor-1 @A0, 
-> DRCM-2 controls all thermoelectric devices systems, based on tempsensor-2 @A1

[vishnus_technologies (C) 2022]
--------------------------------------------------------------------------------------
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
  // check with DRCM #1 pin ID's:
  if(_deviceID == 0) _relayID = "R11";
  else if(_deviceID == 1) _relayID = "R12";
  else if(_deviceID == 2) _relayID = "R13";
  else if(_deviceID == 3) _relayID = "R14";
  else if(_deviceID == 4) _relayID = "R15";
  else if(_deviceID == 5) _relayID = "R16";
  else if(_deviceID == 6) _relayID = "R17";
  else if(_deviceID == 7) _relayID = "R18";

  // check with DRCM #2 pin ID's:
  else if(_deviceID == 0) _relayID = "R21";
  else if(_deviceID == 1) _relayID = "R22";
  else if(_deviceID == 2) _relayID = "R23";
  else if(_deviceID == 3) _relayID = "R24";
  else if(_deviceID == 4) _relayID = "R25";
  else if(_deviceID == 5) _relayID = "R26";
  else if(_deviceID == 6) _relayID = "R27"; 
  else if(_deviceID == 7) _relayID = "R28"; 

 // else if no ID matches [?set=ID:=R0]
  else _relayID = "R0";

  int _DEVNAM_UINT8 = _relayID.substring(1, 3).toInt(); 

  if(_DEVNAM_UINT8 > 10 and _DEVNAM_UINT8 < 19) {
    // @_state: 1/HIGH
    if(_state == TRIGG_RELAY) {
      if(I2C_RELAY1.read(_deviceID) != _state) {
        I2C_RELAY1.write(_deviceID, TRIGG_RELAY); 
        Serial.print(_relayID);
        Serial.println(F(":An#"));
      }
      else if(I2C_RELAY1.read(_deviceID) == _state) {
        Serial.print(_relayID);
        Serial.println(F(":Bn#"));
      }
    }
    // @_state: 0/LOW
    else if(_state == RELEASE_RELAY) {
      if(I2C_RELAY1.read(_deviceID) != _state) {
        I2C_RELAY1.write(_deviceID, RELEASE_RELAY); 
        Serial.print(_relayID);
        Serial.println(":Xf#");
      }
      else if(I2C_RELAY1.read(_deviceID) == _state) {
        Serial.print(_relayID);
        Serial.println(":Yf#");
      }
    }
  }
  
  else if(_DEVNAM_UINT8 > 20 and _DEVNAM_UINT8 < 29) {
    // @_state: 1/HIGH
    if(_state == TRIGG_RELAY) {
      if(I2C_RELAY2.read(_deviceID) != _state) {
        I2C_RELAY2.write(_deviceID, TRIGG_RELAY); 
        Serial.print(_relayID);
        Serial.println(F(":An#"));
      }
      else if(I2C_RELAY2.read(_deviceID) == _state) {
        Serial.print(_relayID);
        Serial.println(F(":Bn#"));
      }
    }
    // @_state: 0/LOW
    else if(_state == RELEASE_RELAY) {
      if(I2C_RELAY2.read(_deviceID) != _state) {
        I2C_RELAY2.write(_deviceID, RELEASE_RELAY); 
        Serial.print(_relayID);
        Serial.println(":Xf#");
      }
      else if(I2C_RELAY2.read(_deviceID) == _state) {
        Serial.print(_relayID);
        Serial.println(":Yf#");
      }
    }
  }

  else {
        // @_state: 1/HIGH
    if(_state == TRIGG_RELAY) {
      if(digitalRead(_deviceID) != _state) {
        digitalWrite(_deviceID, TRIGG_RELAY); 
        Serial.print(_relayID);
        Serial.println(F(":An#"));
      }
      else if(digitalRead(_deviceID) == _state) {
        Serial.print(_relayID);
        Serial.println(F(":Bn#"));
      }
    }
    // @_state: 0/LOW
    else if(_state == RELEASE_RELAY) {
      if(digitalRead(_deviceID) != _state) {
        digitalWrite(_deviceID, RELEASE_RELAY); 
        Serial.print(_relayID);
        Serial.println(":Xf#");
      }
      else if(digitalRead(_deviceID) == _state) {
        Serial.print(_relayID);
        Serial.println(":Yf#");
      }
    }
  }
}