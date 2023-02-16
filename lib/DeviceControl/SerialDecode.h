/*
[Part of ADVANCED COOLING CONTROL ALGORITHM]

[vishnus_technologies (C) 2022]
--------------------------------------------
*/

#include <Arduino.h>

uint8_t pwm = 0;
uint8_t dev_ID;

/* *** DEVICE COMMANDS DECODE SECTION *** */
void deviceCommandDecode(String _serialData) {
  // @switching state: ON
  if(_serialData[1] == 'O') {
    dev_ID = _serialData.substring(2).toInt();
    switch (dev_ID) {
      case 11:
        relaySwitchControl(PELTIER1, TRIGG_RELAY);
        break;
      case 12:
        relaySwitchControl(PELTIER2, TRIGG_RELAY);
        break;
      case 13:
        relaySwitchControl(PELTIER3, TRIGG_RELAY);
        break;
      case 14:
        relaySwitchControl(PELTIER4, TRIGG_RELAY);
        break;
      case 15:
        relaySwitchControl(AC_BLOWERFAN, TRIGG_RELAY);
        break;
      case 16:
        relaySwitchControl(RADIATOR_FAN, TRIGG_RELAY);
        break;
      case 17:
        relaySwitchControl(HS_WATERPUMP, TRIGG_RELAY);
        break;
      case 18:
        relaySwitchControl(CS_WATERPUMP, TRIGG_RELAY);
        break;
      // I2C_RELAY #2 ID's starts here:
      case 21:
        relaySwitchControl(CABINEXHAUST1_IN, TRIGG_RELAY);
        break;
      case 22:
        relaySwitchControl(CABINEXHAUST1_OUT, TRIGG_RELAY);
        break;
      case 23:
        relaySwitchControl(CABINEXHAUST2_IN, TRIGG_RELAY);
        break;
      case 24:
        relaySwitchControl(CABINEXHAUST2_OUT, TRIGG_RELAY);
        break;
      case 25:
        relaySwitchControl(CABIN2_LIGHT, TRIGG_RELAY);
        break;
      case 26:
        relaySwitchControl(NOCP0, TRIGG_RELAY);
        break;
      case 27:
        relaySwitchControl(NOCP1, TRIGG_RELAY);
        break;
      case 28:
        relaySwitchControl(NOCP2, TRIGG_RELAY);
        break;
      default:
        // define M-code later
        break;
    }
  }
  // @switching state: OFF
  else if (_serialData[1] == 'F') {
    dev_ID = _serialData.substring(2).toInt();
    switch (dev_ID) {
      case 11:
        relaySwitchControl(PELTIER1, RELEASE_RELAY);
        break;
      case 12:
        relaySwitchControl(PELTIER2, RELEASE_RELAY);
        break;
      case 13:
        relaySwitchControl(PELTIER3, RELEASE_RELAY);
        break;
      case 14:
        relaySwitchControl(PELTIER4, RELEASE_RELAY);
        break;
      case 15:
        relaySwitchControl(AC_BLOWERFAN, RELEASE_RELAY);
        break;
      case 16:
        relaySwitchControl(RADIATOR_FAN, RELEASE_RELAY);
        break;
      case 17:
        relaySwitchControl(HS_WATERPUMP, RELEASE_RELAY);
        break;
      case 18:
        relaySwitchControl(CS_WATERPUMP, RELEASE_RELAY);
        break;
      // I2C_RELAY #2 ID's starts here:
      case 21:
        relaySwitchControl(CABINEXHAUST1_IN, RELEASE_RELAY);
        break;
      case 22:
        relaySwitchControl(CABINEXHAUST1_OUT, RELEASE_RELAY);
        break;
      case 23:
        relaySwitchControl(CABINEXHAUST2_IN, RELEASE_RELAY);
        break;
      case 24:
        relaySwitchControl(CABINEXHAUST2_OUT, RELEASE_RELAY);
        break;
      case 25:
        relaySwitchControl(CABIN2_LIGHT, RELEASE_RELAY);
        break;
      case 26:
        relaySwitchControl(NOCP0, RELEASE_RELAY);
        break;
      case 27:
        relaySwitchControl(NOCP1, RELEASE_RELAY);
        break;
      case 28:
        relaySwitchControl(NOCP2, RELEASE_RELAY);
        break;
      default:
        // define M-code later
        break;
    }
  }
}

/* *** PWM DECODE SECTION *** */
void pwmDecode(String _serialData, uint8_t ACBFanPwmPin) {
  pwm = _serialData.substring(1).toInt();
  if(pwm == 0) { 
    // Serial.print("PWM: ") Serial.println(pwm);
    relaySwitchControl(AC_BLOWERFAN, RELEASE_RELAY);
    analogWrite(ACBFanPwmPin, pwm);
  }
  else if(pwm > 0) {
    if(I2C_RELAY1.read(AC_BLOWERFAN) == HIGH) {
      relaySwitchControl(AC_BLOWERFAN, TRIGG_RELAY); 
    }
    analogWrite(ACBFanPwmPin, pwm);
  }
}