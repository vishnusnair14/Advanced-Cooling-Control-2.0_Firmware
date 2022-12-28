main.cpp
1. M101 -> "[MCU I/O pin modes initiated]"
2. M102 -> "[initiated DS18B20]"
3. M103 -> "[unable to initiated DS18B20]"

---------------------------------------------------------------

PCF8547_IOEXP.h
1. P201 -> "[Initializing PCF8574 module]"
2. P202 -> "[Successfully initialised PCF8574 module]"
3. P203 -> "[PCF8574 I/O pins initiated]"
4. P204 -> "[PCF8574 device error!]"

---------------------------------------------------------------

Sensors.h
1. S101 -> "[auto initialised DS18B20 sensors]"
2. S102 -> "[Pre-initialised DS18B20 sensors]"

---------------------------------------------------------------

RelayControl.h
1. R11 -> "MAIN POWER"
2. R12 -> "PELTIER 1"
3. R13 -> "PELTIER 2"
4. R14 -> "FLOOD COOLANT FAN"
5. R15 -> "CS PUMP"
6. R16 -> "HS PUMP"
7. R17 -> "CABIN_EXHAUST1"
8. R18 -> "CABIN_EXHAUST2"
9. R0 -> "Undefined device"

1. A  -> "switched ON"
2. B -> "already switched ON"
3. X -> "switched OFF"
4. Y -> "already switched OFF"

EX: R11#A / R11#Y
---------------------------------------------------------------