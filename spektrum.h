#ifndef SPEKTRUM_H
#define SPEKTRUM_H

#include "mbed.h"
#include "rtos.h"

// bind modes
#define SPEKTRUM_INT_DSMX_22MS 7
#define SPEKTRUM_EXT_DSMX_22MS 8
#define SPEKTRUM_INT_DSMX_11MS 9
#define SPEKTRUM_EXT_DSMX_11MS 10
// DSM2 bind modes not recommended, not implemented

// field definitions
// #define SPEKTRUM_MASK_1024_CHANID 0xfc00
// #define SPEKTRUM_MASK_1024_SXPOS 0x03ff
#define SPEKTRUM_MASK_2048_CHANID 0x7800
#define SPEKTRUM_MASK_2048_SXPOS 0x07ff

// allowable system field values
// #define SPEKTRUM_22MS_1024_DSM2 0x01
// #define SPEKTRUM_11MS_2048_DSM2 0x12
#define SPEKTRUM_22MS_2048_DSMX 0xa2
#define SPEKTRUM_11MS_2048_DSMX 0xb2

#define SPEKTRUM_BAUD 125000




class Spektrum{

public:
unsigned int fades = 0;
unsigned int system = SPEKTRUM_22MS_2048_DSMX;
unsigned int servo[7];
Bool is_bound = false;

Spektrum(PinName tx, PinName rx); // constructor

~Spektrum(); // destructor

void bind(int bind_mode = SPEKTRUM_INT_DSMX_11MS); 

private:
Serial _receiver;

};

#endif
