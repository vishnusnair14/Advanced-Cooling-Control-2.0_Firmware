
/* ********************************************* */
*** MESSAGES CODES (M CODES) EXPLANATION & DEF. ***
/* ********************************************* */

# main.cpp

void setup() {
    M104 -> [Serial Communication initiated]
    M101 -> [MCU I/O pin modes initiated]
    M102 -> [DS18B20 sensors initiated]
    M103 -> [unable to initiated DS18B20]
}

---------------------------------------------------------------

# PCF8547_IOEXP.h

(P201 -> [***])
void init_I2C_RELAY1_IEM() {
    #P203 -> [I2C_RELAY #1 I/O pins initiated]
    #P202 -> [Successfully initialised I2C_RELAY module #1]
    #P204 -> [I2C_RELAY #1 device error!]
    #P208 -> [I2C_RELAY #1 is Connected]
    #P209 -> [I2C_RELAY #1 is Disconnected]
}

void init_I2C_RELAY2_IEM() {
    #P206 -> [I2C_RELAY #2 I/O pins initiated] 
    #P205 -> [Successfully initialised I2C_RELAY module #2]
    #P207 -> [I2C_RELAY #2 device error!]
    #P210 -> [I2C_RELAY #2 is Connected]
    #P211 -> [I2C_RELAY #2 is Disconnected]
}

---------------------------------------------------------------

# Sensors.h

dsb18b20 :: bool init_sensor() {
    S102 -> [Pre-initialised DS18B20 sensors]
}
ds18b20 :: void GetTempByAddr() {
    S101 -> [Auto initialised DS18B20 sensors]
}

---------------------------------------------------------------

RelayControl.h

void relaySwitchControl(uint8_t _deviceID, bool _state) {
    #R0  -> [Undefined device]

    #R11 -> [PELTIER 1]
    #R12 -> [PELTIER 2]
    #R13 -> [PELTIER 3]
    #R14 -> [PELTIER 4]
    #R15 -> [AC BLOWER FAN]
    #R16 -> [RADIATOR FAN]
    #R17 -> [HS WATER PUMP]
    #R18 -> [CS WATER PUMP]

    #R21 -> [CABIN EXHAUST1 IN]
    #R22 -> [CABIN EXHAUST1 OUT]
    #R23 -> [CABIN EXHAUST2 IN]
    #R24 -> [CABIN EXHAUST2 OUT]
    #R25 -> [CABIN2 LIGHT]
    #R26 -> NOCP0
    #R27 -> NOCP1
    #R28 -> NOCP2


    An -> [switched ON]
    Bn -> [already switched ON]  
    Xf -> [switched OFF]
    Yf -> [already switched OFF]

    [example]: R11#An / R11#Yf
---------------------------------------------------------------
