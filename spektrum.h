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
// first two only used in DSM2 which are not implemented
#define SPEKTRUM_MASK_2048_CHANID 0x7800
#define SPEKTRUM_MASK_2048_SXPOS 0x07ff

// allowable system field values
// #define SPEKTRUM_22MS_1024_DSM2 0x01
// #define SPEKTRUM_11MS_2048_DSM2 0x12
#define SPEKTRUM_22MS_2048_DSMX 0xa2
#define SPEKTRUM_11MS_2048_DSMX 0xb2

#define SPEKTRUM_BAUD 125000
// Spektrum baud is 125000, but if this doesn't work 115200 should work too. 



class Spektrum{
 public:
  unsigned int fades; 
  unsigned int system; 
  unsigned int servo[7];
  bool is_bound;
  Spektrum(PinName tx, PinName rx); // constructor
  ~Spektrum(); // destructor

 private:
  Serial _receiver;
};





class BindPlug{
 public:
  int mode; 
  BindPlug(PinName tx, PinName rx, int mode = SPEKTRUM_INT_DSMX_11MS);
  ~BindPlug();
  void bind();

 private:
  DigitalOut _3Vpin;
  DigitalOut _datapin;
};


class SpektrumTestDevice{
 public:
  unsigned int fades;
  unsigned int servo[7];
  SpektrumTestDevice(PinName tx, PinName rx);
  ~SpektrumTestDevice();

 private:
  Serial _receiver; 
};


#endif
