#include "mbed.h"
#include "rtos.h"

#include "spektrum.h"


Spektrum::Spektrum(PinName tx, PinName rx): _receiver(tx, rx){
  _receiver.baud(SPEKTRUM_BAUD); // Spektrum uses 125000 8N1 or 115200 8N1
} // Spektrum(tx, rx) constructor

Spektrum::~Spektrum(){
} // ~Spektrum() destructor



/* BindPlug is used to bind a Spektrum Satellite receiver
   @param(tx) is the (unused) tx pin
   @param(rx) is the rx pin, here used as a DigitalOut
   @param(mode) is the mode, e.g. internal or external, DSM2 or DSMX, 11 or 22ms
*/
BindPlug::BindPlug(PinName tx, PinName rx, int mode): _bindpin(rx){
  int i; // counter
  
  // within 200 ms of applying power, supply a bunch of falling pulses
  _bindpin = 1;
  Thread::wait(5);
  for(i=0; i<mode; i++){
    Thread::wait(5);
    _bindpin = 0; // this is the falling pulse
    Thread::wait(5);
    _bindpin = 1; 
  }
  
} // BindPlug(bind, mode) constructor

BindPlug::~BindPlug(){
} // ~BindPlug() destructor



SpektrumTestDevice::SpektrumTestDevice(PinName tx, PinName rx): _receiver(tx,rx){
  _receiver.baud(SPEKTRUM_BAUD);
} // SpektrumTestDevice(tx, rx) constructor

SpektrumTestDevice::~SpektrumTestDevice(){
} // ~SpektrumTestDevice() destructor
