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
// EXT(ernal) bind modes don't really work on solitary satellite receiver

// field definitions
// #define SPEKTRUM_MASK_1024_CHANID 0xfc00
// #define SPEKTRUM_MASK_1024_SXPOS 0x03ff
// first two only used in DSM2 which are not implemented
#define SPEKTRUM_MASK_2048_CHANID 0x7800
#define SPEKTRUM_MASK_2048_CHANID_MSB 0x78
#define SPEKTRUM_MASK_2048_SXPOS 0x07ff

// allowable system field values
// #define SPEKTRUM_22MS_1024_DSM2 0x01
// #define SPEKTRUM_11MS_2048_DSM2 0x12
#define SPEKTRUM_22MS_2048_DSMX 0xa2
#define SPEKTRUM_11MS_2048_DSMX 0xb2

#define SPEKTRUM_BAUD 115200
// Spektrum baud is supposed to be 125000
// but the LPC1768 seems not to support nonstandard baud rates.

#define SPEKTRUM_SERVOS 7
#define SPEKTRUM_PACKET_SIZE 16
#define SPEKTRUM_CHANNELS 16
#define SPEKTRUM_COUNT2US(x) (x*600/1024+900)

class Spektrum{
 public:
  unsigned int fades; 
  unsigned int system; 
  unsigned int channel[SPEKTRUM_CHANNELS];
  unsigned int pulsewidth[SPEKTRUM_CHANNELS]; 
  bool valid;  // TODO switch to EventFlags?
  unsigned int period_ms; 
  Spektrum(PinName tx, PinName rx); // constructor
  ~Spektrum(); // destructor

 private:
  UARTSerial _rx;
  unsigned char _buf[SPEKTRUM_PACKET_SIZE]; 
  Thread _packet_thread;
  void _packet_callback(void); 
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

/* LATER
class SpektrumTestDevice{
 public:
  unsigned int fades;
  unsigned int servo[7];
  SpektrumTestDevice(PinName tx, PinName rx);
  ~SpektrumTestDevice();

 private:
  Serial _receiver; 
};
*/

#endif
