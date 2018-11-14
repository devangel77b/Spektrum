#include "mbed.h"
#include "rtos.h"

#include "spektrum.h"

/* Spektrum is used for a working connection to a Spektrum Satellite receiver
   @param(tx) is the orange wire, 3.3V supply pin (should be held high normally)
   @param(rx) is the gray wire, rx pin from the receiver
   The black wire should be connected to ground. 

   The receiver should first be bound using a BindPlug object. 
*/
Spektrum::Spektrum(PinName tx, PinName rx, PinName rx_led): _receiver(tx, rx), _rx_led(rx_led){
  _receiver.baud(SPEKTRUM_BAUD); // Spektrum uses 125000 8N1 or 115200 8N1

  _rx_thread.start(callback(this,&Spektrum::_rx_callback)); 
} // Spektrum(tx, rx) constructor

Spektrum::~Spektrum(){
} // ~Spektrum() destructor

void Spektrum::_rx_callback(void){
  unsigned char c;        // character read 
  unsigned int i;         // for loop counter
  unsigned int channelid; // for unpacking channel id 
  unsigned int servopos;  // for unpacking servo position data
  
  // setup
  debug("Spektrum rx_thread started\r\n");

  // loop
  while(1){
    if (_receiver.readable()){
	c = _receiver.getc();
	switch(_state){

	case 0: // idle, waiting for start
	  if ((c==SPEKTRUM_22MS_2048_DSMX) || (c==SPEKTRUM_11MS_2048_DSMX))
	    system = c; 
	    _state = 1;
	  break;

	case 1: // got 0xa2 or 0xb2, get fades next
	  fades = c;
	  _state = 2;
	  break;

	default:
	  _data[_state-2] = c;
	  _state++;
	  if (_state == SPEKTRUM_NUM_BYTES_IN_FRAME-1){

	    for (i=0; i<SPEKTRUM_SERVOS; i++){
	      channelid = (_data[2*i] & SPEKTRUM_MASK_2048_CHANID_MSB) >> 3;
	      servopos = ((_data[2*i] << 8) | _data[2*i+1]) & SPEKTRUM_MASK_2048_SXPOS;
	      if ((channelid >= 0) && (channelid < SPEKTRUM_CHANNELS))
		channel[channelid] = servopos;
	    } // unpack data into channels

	    // output data is now valid
	    // set some flags LATER

	    _state = 0; // reset state machine to idle
	  }// if complete packet received
	} // switch(_state)
    } // if readable
  } // while(1)
} // _rx_callback() 





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






/*
// LATER
SpektrumTestDevice::SpektrumTestDevice(PinName tx, PinName rx): _receiver(tx,rx){
  _receiver.baud(SPEKTRUM_BAUD);
} // SpektrumTestDevice(tx, rx) constructor

SpektrumTestDevice::~SpektrumTestDevice(){
} // ~SpektrumTestDevice() destructor
*/
