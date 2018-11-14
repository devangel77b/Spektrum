#include "mbed.h"
#include "rtos.h"

#include "spektrum.h"

/* Spektrum is used for a working connection to a Spektrum Satellite receiver
   @param(tx) is the orange wire, 3.3V supply pin (should be held high normally)
   @param(rx) is the gray wire, rx pin from the receiver
   The black wire should be connected to ground. 

   The receiver should first be bound using a BindPlug object. 
*/
Spektrum::Spektrum(PinName tx, PinName rx): _receiver(tx, rx){
  _receiver.baud(SPEKTRUM_BAUD); // Spektrum uses 125000 8N1 or 115200 8N1
} // Spektrum(tx, rx) constructor

Spektrum::~Spektrum(){
} // ~Spektrum() destructor






/* BindPlug is used to bind a Spektrum Satellite receiver
   @param(tx) is the orange wire, 3.3V supply pin, here used as a DigitalOut
   @param(rx) is the gray wire, rx pin, here used as a DigitalOut
   @param(mode) is the mode, e.g. internal or external, DSM2 or DSMX, 11 or 22ms
   The black wire should be connected to ground.

   Default mode is internal, DSMX, 11 ms. Once created, this object will 
   send a number of falling pulses over the 3.3V supply pin to trigger 
   the satellite receiver to go into bind mode. 
*/
BindPlug::BindPlug(PinName tx, PinName rx, int mode): _3Vpin(tx),_datapin(rx){
  int i; // counter
  
  // within 200 ms of applying power, supply a bunch of falling pulses
  // according to table in Spektrum docs, most likely 9 pulses for
  // internal mode, DSMX, 11 ms.
  _3Vpin = 0;
  _datapin = 0; 
  wait(1);
  _3Vpin = 1; 
  _datapin = 1;
  wait_ms(72);
  debug("pulse ");
  for(i=0; i<mode; i++){
    debug("%d ",i);
    wait_us(116);
    _datapin = 0; // this is the falling pulse
    wait_us(116);
    _datapin = 1; 
  }
  debug("\r\n"); 
} // BindPlug(bind, mode) constructor

BindPlug::~BindPlug(){
} // ~BindPlug() destructor







SpektrumTestDevice::SpektrumTestDevice(PinName tx, PinName rx): _receiver(tx,rx){
  _receiver.baud(SPEKTRUM_BAUD);
} // SpektrumTestDevice(tx, rx) constructor

SpektrumTestDevice::~SpektrumTestDevice(){
} // ~SpektrumTestDevice() destructor
