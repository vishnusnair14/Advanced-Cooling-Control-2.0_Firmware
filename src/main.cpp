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
------------------------------------------------------------------------
*/

#include <Arduino.h>
#include <PCF8547_IOEXP.h>
#include <Sensors.h>
#include <RelayControl.h>

#define PBT1 A0
#define PBT2 A1
#define CT1 A2
#define CT2 A3
#define mainPower 3
#define ExhaustFanPWMPin 9
#define softResetPin 12

double TEMP1, TEMP2, TEMP3, TEMP4;
uint8_t pwm = 0;
String serialData;

ntc10k NTC;
ds18b20 DS18B20;

// @PROGRMA ONCE BLOCK:
void setup() {
  digitalWrite(softResetPin, HIGH);
  delay(100);
  Serial.begin(9600);
  Serial.println("");
  Serial.println("M104");
  delay(1000);
  Serial.println(F("Initializing CPU Core..."));
  delay(2500);

  // MCU pin mode definition:
  pinMode(mainPower, OUTPUT);
  pinMode(softResetPin, OUTPUT);
  pinMode(PBT1, INPUT);
  pinMode(PBT2, INPUT);
  pinMode(CT1, INPUT);
  pinMode(CT2, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("M101");   // M101: "MCU I/O pin modes initiated"

  // initialize PCF8574 device & pins:
  Init_PCF8574Module();
  delay(1000);

  if(DS18B20.init_sensor()) {
    Serial.println(F("M102"));   // M102: "DS18B20 sensors initiated"
    delay(750);
  }
  else { 
    Serial.println(F("M103"));  // M103: "Unable to initiated DS18B20"
    delay(750);
  }
  
  // switch ON main power:
  switchRelay(mainPower, HIGH);
}


void loop() {
  /*
  while (Serial.available() > 0) {
    static char message[MAX_MESSAGE_LENGTH];
    static unsigned int message_pos = 0;
    char inByte = Serial.read();

    if ( inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1) ) {
      message[message_pos] = inByte;
      message_pos++;
    }
    else 
    {
      message[message_pos] = '\0';
      Serial.println(message);
      if(message[0] == 's') 
      {
        for(int y=0;y<12;y++)
        {
          if(message[y] == 'd')
          {
            LastMIndex = y; 
            MEssage = (String)message;
            pwm = MEssage.substring(1,LastMIndex).toInt();
            Serial.print("RPM: "); Serial.println(pwm);
            if(pwm>=0) {
              analogWrite(ExhaustFanPWMPin, pwm);
            }
            }
          }
        }
      else if(message[0] == 'r') {
        Serial.print("> PWM: "); Serial.println(pwm);
        digitalWrite(softResetPin, LOW);
      }
     else if(message[0] == 'A'){
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else if(message[0] == 'a'){
      digitalWrite(LED_BUILTIN, LOW);
      message_pos = 0;
    }
  }
  }
 */
  if(Serial.available()>0){
    // reads arduino serial buffer until '\n':
    serialData = Serial.readStringUntil('\n');

    if(serialData == "A") {
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else if(serialData == "a") {
      digitalWrite(LED_BUILTIN, LOW);
    }
    else if(serialData == "r") {
      digitalWrite(softResetPin, LOW);
    }

    // decodes pwm value from software:
    // ex data:[s245d] or [s122d] | [pwm: 245, 122]
    if(serialData[0] == 's') {
      pwm = serialData.substring(1,serialData.indexOf('d')).toInt();
      //Serial.print("PWM: ") Serial.println(pwm);
      analogWrite(ExhaustFanPWMPin, pwm);
    }
  }

  TEMP1 = NTC.GetTemperature(analogRead(PBT2));  // NTC-S1 @peltier cool side [for thermoele.dev control]
  TEMP2 = NTC.GetTemperature(analogRead(PBT1));  // NTC-S2 @peltier hot side [for coolant fan control]
  TEMP3 = NTC.GetTemperature(analogRead(CT1));
  TEMP4 = NTC.GetTemperature(analogRead(CT2));
  Serial.println((String)"T"+TEMP1+"A"+TEMP2+"B"+TEMP3+"C"+TEMP4+"D");
  
  NTC_CS(TEMP1);
  NTC_HS(TEMP2);
  delay(1000);
}
