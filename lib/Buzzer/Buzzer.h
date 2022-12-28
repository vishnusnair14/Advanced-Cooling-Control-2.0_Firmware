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

#include <Arduino.h>

// buzzer connected on arduino I/O pin 4 
#define buzzerPin 4


void normalBeep(uint16_t _freq, uint8_t _duration, uint16_t _interval);
void emergencyBeep(uint16_t _freq, uint8_t _duration, uint16_t _interval);
void criticalBeep(uint16_t _freq, uint8_t _duration, uint16_t _interval);

// normalBeep(uint16_t frequency, uint16_t delay(ms))
void normalBeep(uint16_t _freq, uint8_t _duration, uint16_t _interval) {
  if(_duration == 0) { _duration = 4; }
  for(uint8_t rec = 0; rec < _duration; rec ++) {
    tone(buzzerPin, _freq);
    delay(_interval);
    noTone(buzzerPin);
    delay(_interval);
  }
}

// emergencyBeep(uint16_t frequency, uint16_t delay(ms))
void emergencyBeep(uint16_t _freq, uint8_t _duration, uint16_t _interval) {
  if(_duration == 0) { _duration = 7; }
  for(uint8_t rec = 0; rec < _duration; rec ++) {
    tone(buzzerPin, _freq);
    delay(_interval);
    noTone(buzzerPin);
    delay(_interval);
  }
}

// criticalBeep(uint16_t frequency, uint16_t delay(ms))
void criticalBeep(uint16_t _freq, uint8_t _duration, uint16_t _interval) {
  if(_duration == 0) { _duration = 15; }
  for(uint8_t rec = 0; rec < _duration; rec ++) {
    tone(buzzerPin, _freq);
    delay(_interval);
    noTone(buzzerPin);
    delay(_interval);
  }
}
