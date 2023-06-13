
#include <Arduino.h>


/* Device ID's of all hardware devices connceted to
   PCF8574 expansion modules. */ 


// [@name: I2C_RELAY #1, @address: 0x25]
#define PELTIER1 101
#define PELTIER2 102
#define PELTIER3 103
#define PELTIER4 104
#define AC_BLOWERFAN 105
#define RADIATOR_FAN 106
#define HS_WATERPUMP 107
#define CS_WATERPUMP 108

// [@name: I2C_RELAY #2, @address: 0x38]
#define CABINEXHAUST1_IN 201
#define CABINEXHAUST1_OUT 202
#define CABINEXHAUST2_IN 203
#define CABINEXHAUST2_OUT 204
#define CABIN2_LIGHT 205
#define NOCP0 206
#define NOCP1 207
#define NOCP2 208