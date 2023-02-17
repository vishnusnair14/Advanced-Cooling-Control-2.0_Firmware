/*
[Part of ADVANCED COOLING CONTROL ALGORITHM]

Independent device control algorithm
------------------------------------

Library for controlling different types independent
devices. Like thermo-devices, cooling devices, Exhausts
and many more... This algorithm contains several 
function for several device controls. (Those func. helps
in controlling particularly that devices)

[vishnus_technologies (C) 2022]
-------------------------------------------------------
*/

#include <Arduino.h>
#include <RelayControl.h>

/* temperature state constants:
LOW_TEMP 14
MEDIAN_TEMP 22
HIGH_TEMP 32  */

// [RCS-1] Thermoelectric devices control:
// (for NTC-S1 @peltier cool side thermistor)
void PELTIER_CONTROL(int _temp0) {
  if(_temp0 < LOW_TEMP) {
    relaySwitchControl(PELTIER1, RELEASE_RELAY);
    relaySwitchControl(PELTIER2, RELEASE_RELAY);
  }
  else if(_temp0 > MEDIAN_TEMP) { 
    relaySwitchControl(PELTIER1, TRIGG_RELAY);
    relaySwitchControl(PELTIER2, RELEASE_RELAY);
  }
  else if(_temp0 > HIGH_TEMP) {
    relaySwitchControl(PELTIER1, TRIGG_RELAY);
    relaySwitchControl(PELTIER2, TRIGG_RELAY);
  }
}

// [RCS-2] Radiator fans control:
// (for NTC-S2 @peltier hot side)
void RAD_FAN_CONTROL(int _temp1) {
  if(_temp1 < LOW_TEMP) {
    relaySwitchControl(RADIATOR_FAN, RELEASE_RELAY);
  }
  else if(_temp1 > MEDIAN_TEMP) {
    relaySwitchControl(RADIATOR_FAN, TRIGG_RELAY);
  }
}