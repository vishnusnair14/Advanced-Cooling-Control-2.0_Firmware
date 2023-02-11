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
#include <RelayControl.h>

#define PBT1 A0
#define PBT2 A1
#define CT1 A2
#define CT2 A3
//#define MAIN_POWER 3
#define EXHFAN_PWM_PIN 9
#define SOFT_REST_PIN 12

uint8_t pwm = 0;
double TEMP1, TEMP2, TEMP3, TEMP4;
String serialData;

ntc10k NTC10K;
ds18b20 DS18B20;

// UNO INITIAL SETUP:
void setup() {
  digitalWrite(SOFT_REST_PIN, HIGH);
  delay(100);

  pinMode(EXHFAN_PWM_PIN, OUTPUT);
  delay(100);
  analogWrite(EXHFAN_PWM_PIN, 0);
  delay(100);
  
  // initalize serial monitor:
  Serial.begin(9600);
  Serial.println("M104"); 
  delay(100);

  Serial.println(F("Initializing CPU Core..."));
  delay(2500);

  // MCU pin mode definition:
  pinMode(PBT1, INPUT);
  pinMode(PBT2, INPUT);
  pinMode(CT1, INPUT);
  pinMode(CT2, INPUT);
  pinMode(SOFT_REST_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println(F("M101"));   // M101: "MCU I/O pin modes initiated"
  delay(1000);

  // initialize DRCM1 device & pins:
  init_DRCM1_IEM();
  delay(1000);

  // initialize DRCM2 device & pins:
  init_DRCM2_IEM();
  delay(1000);
  

  if(DS18B20.init_sensor()) {
    Serial.println(F("M102"));   // M102: "DS18B20 sensors initiated"
    delay(750);
  }
  else { 
    Serial.println(F("M103"));  // M103: "Unable to initiated DS18B20"
    delay(750);
  }
}


void loop() {
  if(Serial.available()>0) {
    // reads arduino serial buffer until '\n':
    serialData = Serial.readStringUntil('\n');

    if(serialData == "A") {
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else if(serialData == "a") {
      digitalWrite(LED_BUILTIN, LOW);
    }
    else if(serialData == "r") {
      digitalWrite(SOFT_REST_PIN, LOW);
    }

    // decodes pwm value :
    // ex data:[s245] or [s122] | [pwm: 245, 122]
    if(serialData[0] == 's') {
      pwm = serialData.substring(1).toInt();
      //Serial.print("PWM: ") Serial.println(pwm);
      analogWrite(EXHFAN_PWM_PIN, pwm);
    }
  }

  TEMP1 = NTC10K.GetTemperature(analogRead(PBT2));  // NTC10K-S1 @peltier cool side [for thermoele.dev control]
  TEMP2 = NTC10K.GetTemperature(analogRead(PBT1));  // NTC10K-S2 @peltier hot side [for coolant fan control]
  TEMP3 = NTC10K.GetTemperature(analogRead(CT1));
  TEMP4 = NTC10K.GetTemperature(analogRead(CT2));
  // prints final temperature data on serial ~[in encoded format]:
  Serial.println((String)"T"+TEMP1+"A"+TEMP2+"B"+TEMP3+"C"+TEMP4+"D");
  
  PELTIER_CONTROL(TEMP1);
  delay(1000);
}
