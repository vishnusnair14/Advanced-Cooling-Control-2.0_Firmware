/*
# main.cpp

ADVANCED COOLING CONTROL ALGORITHM (For Ender-3 PRO)
----------------------------------------------------

This is an intelligent algorithm, specially desgined for 3d printers
(Ender-3 PRO). This algorithm adds more saftey to your printer.By
installing this software/algorithm you can leave your printer unattended.
It has several advanced saftey features. You can run your printer for
high temperature prints also. Has advanced saftey for the stepper motor
too, also for the print head. Make sures motor looses not steps. Cool :)

[vishnus_technologies (C) 2022]
[20-DECEMBER-2022 08:46PM]
-------------------------------------------------------------------------
*/

#include <Arduino.h>
#include <PCF8547_IOEXP.h>
#include <Sensors.h>
#include <Control.h>
#include <SerialDecode.h>

#define PCEB1 A0   // PCEB - Peltier CoolEnd Block
#define PCEB2 A1
#define PHEB1 A2   // PHEB - Peltier HotEnd Block
#define PHEB2 A3
#define SOFT_REST_PIN 8
#define AC_BFAN_PWM_PIN 9

double TEMP1, TEMP2, TEMP3, TEMP4;
String readBuffer;

ntc10k NTC10K;
ds18b20 DS18B20;

// MP INITIAL SETUP:
void setup() {
  digitalWrite(SOFT_REST_PIN, HIGH);
  delay(100);

  pinMode(AC_BFAN_PWM_PIN, OUTPUT);
  delay(100);
  analogWrite(AC_BFAN_PWM_PIN, 0);
  relaySwitchControl(AC_BLOWERFAN, RELEASE_RELAY);
  delay(100);
  
  // initalize serial monitor:
  Serial.begin(9600);
  Serial.println("M104"); 
  delay(100);

  Serial.println(F("Initializing CPU Core..."));
  delay(2500);

  // MCU pin mode definition:
  pinMode(PCEB1, INPUT);
  pinMode(PCEB2, INPUT);
  pinMode(PHEB1, INPUT);
  pinMode(PHEB2, INPUT);
  pinMode(SOFT_REST_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println(F("M101"));   // M101: "MCU I/O pin modes initiated"
  delay(1000);

  // initialize I2C_RELAY1 device & pins:
  init_I2C_RELAY();

  /*
  if(DS18B20.init_sensor()) {
    Serial.println(F("M102"));   // M102: "DS18B20 sensors initiated"
    delay(750);
  }
  else { 
    Serial.println(F("M103"));  // M103: "Unable to initiated DS18B20"
    delay(750);
  } */
}
 
void loop() {
  if(Serial.available() > 0) {
    // reads arduino serial buffer until '\n':
    readBuffer = Serial.readStringUntil('\n');

    if(readBuffer == "A") {
      relaySwitchControl(LED_BUILTIN, TRIGG_RELAY);
    }
    else if(readBuffer == "a") {
      relaySwitchControl(LED_BUILTIN, RELEASE_RELAY);
    }
    else if(readBuffer == "r") {
      digitalWrite(SOFT_REST_PIN, LOW);
    }

    // decodes devices commands:
    if(readBuffer[0] == 'D') {
      DecodeDevCmd(readBuffer);
    } 
    
    // decode pwm value:
    if(readBuffer[0] == 'S') {
      DecodePwmVal(readBuffer, 4, AC_BFAN_PWM_PIN);
    }
  }

  TEMP1 = NTC10K.GetTemperature(analogRead(PCEB1));  // @peltier cool side [for thermoele.dev control]
  //TEMP2 = NTC10K.GetTemperature(analogRead(PCEB2));  
  TEMP3 = NTC10K.GetTemperature(analogRead(PHEB1));  // @peltier hot side [for radiator fan control]
  TEMP4 = NTC10K.GetTemperature(analogRead(PHEB2));

  // prints final temperature data on serial ~[in encoded format]:
  Serial.println((String)"T"+TEMP1+"A"+TEMP2+"B"+TEMP3+"C"+TEMP4+"D");
  
  //PELTIER_CONTROL(TEMP1);
  //RAD_FAN_CONTROL(TEMP2);
  delay(1000);
}
