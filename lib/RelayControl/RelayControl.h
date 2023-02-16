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
    // check with I2C_RELAY #1 pin ID's:
    if(_deviceID == 11) { _relayID = "R11"; _deviceID = 0; }
    else if(_deviceID == 12) { _relayID = "R12"; _deviceID = 1; }
    else if(_deviceID == 13) { _relayID = "R13"; _deviceID = 2; }
    else if(_deviceID == 14) { _relayID = "R14"; _deviceID = 3; }
    else if(_deviceID == 15) { _relayID = "R15"; _deviceID = 4; }
    else if(_deviceID == 16) { _relayID = "R16"; _deviceID = 5; }
    else if(_deviceID == 17) { _relayID = "R17"; _deviceID = 6; }
    else if(_deviceID == 18) {_relayID = "R18"; _deviceID = 7; }
   // check with I2C_RELAY #2 pin ID's:
    else if(_deviceID == 21) { _relayID = "R21"; _deviceID = 0; }
    else if(_deviceID == 22) { _relayID = "R22"; _deviceID = 1; }
    else if(_deviceID == 23) { _relayID = "R23"; _deviceID = 2; }
    else if(_deviceID == 24) { _relayID = "R24"; _deviceID = 3; }
    else if(_deviceID == 25) { _relayID = "R25"; _deviceID = 4; }
    else if(_deviceID == 26) { _relayID = "R26"; _deviceID = 5; }
    else if(_deviceID == 27) { _relayID = "R27"; _deviceID = 6; }
    else if(_deviceID == 28) { _relayID = "R28"; _deviceID = 7; }
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