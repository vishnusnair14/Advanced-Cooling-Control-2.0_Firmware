/*
[Part of ADVANCED COOLING CONTROL ALGORITHM]

Temperature control library
---------------------------

Sensor control library for all types of temperature sensors. Contain several 
functions for converting analog signals and converting it into temperature 
values. Recieves analog voltages from different sensors [NTC10k, DS18B20], 
This library also supports with one-wire protocol sensors. Respective functions
returns temperature(in C) based on respective analog signals recieved. 

[vishnus_technologies (C) 2022]
-------------------------------------------------------------------------------
*/

#include <OneWire.h>
#include <DallasTemperature.h>
#include <DS18B20_AddressMap.h>

#define ONEWIRE_PORT 2  // for DS18B20 devices
#define RT0 10000
#define B 3977 
#define VCC 5
#define R 10000

// sensor address mapping:
// (X_MOT_SA -> x motor sensor address)
#define X_MOT_SA x_addr
#define Y_MOT_SA y_addr
#define Z_MOT_SA z_addr
#define E_MOT_SA e_addr

OneWire oneWire(ONEWIRE_PORT);	
DallasTemperature sensors(&oneWire);

bool DS_INIT_FLAG = false;
float tempC, DTEMP_X, DTEMP_Y, DTEMP_Z, DTEMP_E;
double T0 = 25 + 273.15;


// NTC10k sensor class:
class ntc10k {
  public : bool init_sensor() {
    return EXIT_SUCCESS;
  }

  public : float GetTemperature(float Tdata) {
    float Ctemp, RT, VR, ln;
    Tdata = (5.00/1023.00)*Tdata;
    VR = VCC-Tdata;
    RT = Tdata/(VR/R);
    ln = log(RT/RT0);
    Ctemp = (1/((ln/B)+(1/T0)));
    Ctemp = Ctemp-273.15;  
    return Ctemp;
  }
};


// DS18B20 1-wire sensor class:
class ds18b20 {
  public : bool init_sensor() {
    sensors.begin();
    DS_INIT_FLAG = true;
    Serial.println("S102");   // S102: "Pre-initialised DS18B20 sensors"
    return true;
  }

  public : void GetTempByAddr() {
    if(DS_INIT_FLAG == true) {
      sensors.requestTemperatures();
      DTEMP_X = getTemp(X_MOT_SA);
      DTEMP_Y = getTemp(Y_MOT_SA);
      DTEMP_Z = getTemp(Z_MOT_SA);
      DTEMP_E = getTemp(E_MOT_SA);
      Serial.println((String)"D"+DTEMP_X+"X"+DTEMP_Y+"Y"+DTEMP_Z+"Z"+DTEMP_E+"E");
    }
    else {
      init_sensor();
      Serial.println(F("S101"));  // S101: "Auto initialised DS18B20 sensors"
    }
  }

  private : float getTemp(DeviceAddress deviceAddress) {
    tempC = sensors.getTempC(deviceAddress);
    return tempC;
}
};
