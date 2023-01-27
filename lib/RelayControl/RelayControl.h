/*
[Part of ADVANCED COOLING CONTROL ALGORITHM]

Controlling algorithm for temperature based Relay Control Systems
-----------------------------------------------------------------

Controls device control relay modules. These systems are used for controlling (ON/OFF)
thermoelectric devices, coolants, exhausts etc... based only on thermal sensor values.
Mainly it control two independent RCS(s), named RCS-1, RCS-2.
-> DRCM-1 controls all coolant fans, radiator, exhausts, based on the tempsensor-1 @A0, 
-> DRCM-2 controls all thermoelectric devices systems, based on tempsensor-2 @A1

[vishnus_technologies (C) 2022]
--------------------------------------------------------------------------------------
*/

#include <Arduino.h>

// device to pin mapping [DRCM#1]:
#define PELTIER1 PE1
#define PELTIER2 PE2
#define PELTIER3 PE3
#define PELTIER4 PE4
#define AC_BLOWERFAN AC_BFAN
#define RADIATOR_FAN RAD_FAN
#define HS_WATERPUMP HSWP
#define CS_WATERPUMP CSWP

// device to pin mapping [DRCM#2]:
#define CABINEXHAUST1_IN CEXAH1_IN
#define CABINEXHAUST1_OUT CEXAH1_OUT
#define CABINEXHAUST2_IN CEXAH2_IN
#define CABINEXHAUST2_OUT CEXAH2_OUT
#define CABIN_LIGHT CAB_LIGHT
#define NOCPA NOCP0  // Un-occupied ports: #1
#define NOCPB NOCP1  //                    #2
#define NOCPC NOCP2  //                    #3

// relay states:
#define TRIGG_RELAY LOW
#define RELEASE_RELAY HIGH

// temperature constants:
#define LOW_TEMP 14
#define MEDIAN_TEMP 22
#define HIGH_TEMP 32


// RELAY SWITCHING CONTROL SECTION (RSCS):
void relaySwitchControl(uint8_t _deviceID, bool _state) {
  String _deviceName = "";

  // check with DRCM #1 pin ID's:
  if(_deviceID == PE1) _deviceName = "R11";
  else if(_deviceID == PE2) _deviceName = "R12";
  else if(_deviceID == PE3) _deviceName = "R13";
  else if(_deviceID == PE4) _deviceName = "R14";
  else if(_deviceID == AC_BFAN) _deviceName = "R15";
  else if(_deviceID == RAD_FAN) _deviceName = "R16";
  else if(_deviceID == HSWP) _deviceName = "R17";
  else if(_deviceID == CSWP) _deviceName = "R18";
  // check with DRCM #2 pin ID's:
  else if(_deviceID == CEXAH1_IN) _deviceName = "R21";
  else if(_deviceID == CEXAH1_OUT) _deviceName = "R22";
  else if(_deviceID == CEXAH2_IN) _deviceName = "R23";
  else if(_deviceID == CEXAH2_OUT) _deviceName = "R24";
  else if(_deviceID == CAB_LIGHT) _deviceName = "R25";
  else if(_deviceID == NOCP0) _deviceName = "R26";
  else if(_deviceID == NOCP1) _deviceName = "R27"; 
  else if(_deviceID == NOCP2) _deviceName = "R28"; 
 // else no ID match [ID: R0]
  else _deviceName = "R0";

  // @_state: ON/1/HIGH
  if(_state == TRIGG_RELAY) {
    if(digitalRead(_deviceID)!=_state) {
      digitalWrite(_deviceID, TRIGG_RELAY);
      Serial.print(_deviceName);
      Serial.println(F(":An#"));
    }
    else if(digitalRead(_deviceID) == _state) {
      Serial.print(_deviceName);
      Serial.println(F(":Bn#"));
    }
  }
  // @_state: OFF/0/LOW
  else if(_state == RELEASE_RELAY) {
    if(digitalRead(_deviceID) != _state) {
      digitalWrite(_deviceID, RELEASE_RELAY);
      Serial.print(_deviceName);
      Serial.println(":Xf#");
    }
    else if(digitalRead(_deviceID) == _state) {
      Serial.print(_deviceName);
      Serial.println(":Yf#");
    }
  }
}

// [RCS-1] Thermoelectric devices control:
// (for NTC-S1 @peltier cool side)
void PELTIER_CONTROL(int _temp1) {
  if(_temp1<LOW_TEMP) {
    relaySwitchControl(PELTIER1, RELEASE_RELAY);
    relaySwitchControl(PELTIER2, RELEASE_RELAY);
  }
  else if(_temp1>MEDIAN_TEMP) { 
    relaySwitchControl(PELTIER1, TRIGG_RELAY);
    relaySwitchControl(PELTIER2, RELEASE_RELAY);
  }
  else if(_temp1>HIGH_TEMP) {
    relaySwitchControl(PELTIER1, TRIGG_RELAY);
    relaySwitchControl(PELTIER2, TRIGG_RELAY);
  }
}


/*
// [RCS-2] Coolant fans control:
// (for NTC-S2 @peltier hot side)
void RAD_FAN_CONTROL(int _temp0) {
  if(_temp0<20) {
    relaySwitchControl(FLOOD_COOLANT_FAN, RELEASE_RELAY);
  }
  else if(_temp0>45) {
    relaySwitchControl(FLOOD_COOLANT_FAN, TRIGG_RELAY);
  }
}
*/
