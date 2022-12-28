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

// mapping of peltier sensors:
#define PBT1 A0  //PBT: Peltier Block Temperature(1)(2)
#define PBT2 A1
#define CT1 A2
#define CT2 A3
#define main_power 3

char stdata;
double TEMP1, TEMP2, TEMP3, TEMP4;

ntc10k NTC;
ds18b20 DS18B20;

// @PROGRMA ONCE BLOCK:
void setup() {
  Serial.begin(9600);
  Serial.println("M104");
  delay(1000);
  Serial.println("Initializing CPU Core...");
  delay(2500);

  // MCU pin mode definition:
  pinMode(main_power, OUTPUT);
  pinMode(PBT1, INPUT);
  pinMode(PBT2, INPUT);
  pinMode(CT1, INPUT);
  pinMode(CT2, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("M101");

  // initialize PCF8574 device & pins:
  Init_PCF8574Module(); 

  if(DS18B20.init_sensor()) {
    Serial.println(F("M102")); 
  }
  else { 
    Serial.println(F("M103")); 
  }
  
  // switch ON main power:
  switchRelay(main_power, HIGH);
}


void loop() {
  if(Serial.available()>0){
    stdata = Serial.read();
    if(stdata == 'A'){
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else if(stdata == 'a'){
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
  TEMP1 = NTC.GetTemperature(analogRead(PBT2));  // NTC-S1 @peltier cool side [for thermoele.dev control]
  TEMP2 = NTC.GetTemperature(analogRead(PBT1));  // NTC-S2 @peltier hot side [for coolant fan control]
  TEMP3 = NTC.GetTemperature(analogRead(CT1));
  TEMP4 = NTC.GetTemperature(analogRead(CT2));
  Serial.println((String)"T"+String(TEMP1)+"A"+String(TEMP2)+"B"+String(TEMP3)+"C"+String(TEMP4)+"D");
  
  NTC_CS(TEMP1);
  NTC_HS(TEMP2);
  delay(1000);
}
