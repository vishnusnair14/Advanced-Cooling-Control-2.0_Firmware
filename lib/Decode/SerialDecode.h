/*
[Part of ADVANCED COOLING CONTROL ALGORITHM]

Serial device command decode library
------------------------------------

[vishnus_technologies (C) 2022]
--------------------------------------------
*/

#include <Arduino.h>

uint8_t pwmVal = 0;
uint8_t dev_ID;


/* *** DEVICE COMMANDS DECODE SECTION *** */

// Decodes standalone hardware control commands from serial readbuffer 
// data and convert into hardware relay device control commands
void DecodeDevCmd(String _serialData) {
  // @switching state: ON
  if(_serialData[1] == 'N') {
    dev_ID = _serialData.substring(2).toInt();
    switch (dev_ID) {
      case PELTIER1:
        relaySwitchControl(PELTIER1, TRIGG_RELAY);
        break;
      case PELTIER2:
        relaySwitchControl(PELTIER2, TRIGG_RELAY);
        break;
      case PELTIER3:
        relaySwitchControl(PELTIER3, TRIGG_RELAY);
        break;
      case PELTIER4:
        relaySwitchControl(PELTIER4, TRIGG_RELAY);
        break;
      case AC_BLOWERFAN:
        relaySwitchControl(AC_BLOWERFAN, TRIGG_RELAY);
        break;
      case RADIATOR_FAN:
        relaySwitchControl(RADIATOR_FAN, TRIGG_RELAY);
        break;
      case HS_WATERPUMP:
        relaySwitchControl(HS_WATERPUMP, TRIGG_RELAY);
        break;
      case CS_WATERPUMP:
        relaySwitchControl(CS_WATERPUMP, TRIGG_RELAY);
        break;
      /*
      case 109:
        I2C_RELAY1.selectNone();
        break;
      */
      
      // I2C_RELAY #1 ID's starts here:
      case CABINEXHAUST1_IN:
        relaySwitchControl(CABINEXHAUST1_IN, TRIGG_RELAY);
        break;
      case CABINEXHAUST1_OUT:
        relaySwitchControl(CABINEXHAUST1_OUT, TRIGG_RELAY);
        break;
      case CABINEXHAUST2_IN:
        relaySwitchControl(CABINEXHAUST2_IN, TRIGG_RELAY);
        break;
      case CABINEXHAUST2_OUT:
        relaySwitchControl(CABINEXHAUST2_OUT, TRIGG_RELAY);
        break;
      case CABIN2_LIGHT:
        relaySwitchControl(CABIN2_LIGHT, TRIGG_RELAY);
        break;
      case NOCP0:
        relaySwitchControl(NOCP0, TRIGG_RELAY);
        break;
      case NOCP1:
        relaySwitchControl(NOCP1, TRIGG_RELAY);
        break;
      case NOCP2:
        relaySwitchControl(NOCP2, TRIGG_RELAY);
        break;
      /*
      case 209:
        I2C_RELAY2.selectNone();
        break;
      */
      default:
        // define M-code later
        break;
    }
  }
  // @switching state: OFF
  else if (_serialData[1] == 'F') {
    dev_ID = _serialData.substring(2).toInt();
    switch (dev_ID) {
      case PELTIER1:
        relaySwitchControl(PELTIER1, RELEASE_RELAY);
        break;
      case PELTIER2:
        relaySwitchControl(PELTIER2, RELEASE_RELAY);
        break;
      case PELTIER3:
        relaySwitchControl(PELTIER3, RELEASE_RELAY);
        break;
      case PELTIER4:
        relaySwitchControl(PELTIER4, RELEASE_RELAY);
        break;
      case AC_BLOWERFAN:
        relaySwitchControl(AC_BLOWERFAN, RELEASE_RELAY);
        break;
      case RADIATOR_FAN:
        relaySwitchControl(RADIATOR_FAN, RELEASE_RELAY);
        break;
      case HS_WATERPUMP:
        relaySwitchControl(HS_WATERPUMP, RELEASE_RELAY);
        break;
      case CS_WATERPUMP:
        relaySwitchControl(CS_WATERPUMP, RELEASE_RELAY);
        break;
      /*
      case 109:
        I2C_RELAY1.selectAll();
        break;
      */

      // I2C_RELAY #1 ID's starts here:
      case CABINEXHAUST1_IN:
        relaySwitchControl(CABINEXHAUST1_IN, RELEASE_RELAY);
        break;
      case CABINEXHAUST1_OUT:
        relaySwitchControl(CABINEXHAUST1_OUT, RELEASE_RELAY);
        break;
      case CABINEXHAUST2_IN:
        relaySwitchControl(CABINEXHAUST2_IN, RELEASE_RELAY);
        break;
      case CABINEXHAUST2_OUT:
        relaySwitchControl(CABINEXHAUST2_OUT, RELEASE_RELAY);
        break;
      case CABIN2_LIGHT:
        relaySwitchControl(CABIN2_LIGHT, RELEASE_RELAY);
        break;
      case NOCP0:
        relaySwitchControl(NOCP0, RELEASE_RELAY);
        break;
      case NOCP1:
        relaySwitchControl(NOCP1, RELEASE_RELAY);
        break;
      case NOCP2:
        relaySwitchControl(NOCP2, RELEASE_RELAY);
        break;
      /*
      case 209:
        I2C_RELAY2.selectAll();
        break;
      */
      default:
        // define M-code later
        break;
    }
  }
}


/* *** PWM DECODE SECTION *** */

// Decodes PWM commands and convert pwmVal value from serial 
// readbuffer and write to respective PWM_PIN
void DecodePwmVal(String _serialData, uint8_t I2C_PIN, uint8_t PWM_PIN) {
  pwmVal = _serialData.substring(1).toInt();

  if(pwmVal == 0)
  { 
    // Serial.print("PWM: ") Serial.println(pwmVal);
    if(I2C_RELAY1.read(I2C_PIN) != RELEASE_RELAY ) {
      relaySwitchControl(AC_BLOWERFAN, RELEASE_RELAY);
    }
    analogWrite(PWM_PIN, pwmVal);
  }
  else if(pwmVal > 0)
  {
    if(I2C_RELAY1.read(I2C_PIN) == RELEASE_RELAY) {
      relaySwitchControl(AC_BLOWERFAN, TRIGG_RELAY); 
    }
    analogWrite(PWM_PIN, pwmVal);
  }
}
