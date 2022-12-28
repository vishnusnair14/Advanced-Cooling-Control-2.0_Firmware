/*
[Part of ADVANCED COOLING CONTROL ALGORITHM]

Arduino compatible algorithm for accessing DS18B20
1-wire protocol supported temperature sensor data.

[vishnus_technologies (C) 2022]
--------------------------------------------------
*/

#include <Arduino.h>
#include <DallasTemperature.h>

#define ONEWIRE_PORT 2
byte deviceCount;
DeviceAddress sensorAddress;

OneWire oneWire(ONEWIRE_PORT);
DallasTemperature sensors(&oneWire);

void printAddress(DeviceAddress);

void getDeviceAddr() {
  // Locate all the devices on bus
  deviceCount = sensors.getDeviceCount();
  Serial.print("Found ");
  Serial.print(deviceCount, DEC);
  Serial.println(" devices.");

  Serial.println("Printing addresses...");
  for(int _device = 1;  _device <= deviceCount;  _device++) {
    Serial.print("Sensor ");
    Serial.print(_device);
    Serial.print(" : ");
    if(sensors.getAddress(sensorAddress, _device)) {
      printAddress(sensorAddress);
    }
    else {
      Serial.print("Address for sensor: ");
      Serial.print(_device);
      Serial.println(" not found");
    } 
 }
}

void printAddress(DeviceAddress deviceAddress) { 
  for (uint8_t i = 0; i < 8; i++) {
    Serial.print("0x");
    if (deviceAddress[i] < 0x10) Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
    if (i < 7) Serial.print(", ");
  }
  Serial.println("");
}

void setup(){
  getDeviceAddr();
}

