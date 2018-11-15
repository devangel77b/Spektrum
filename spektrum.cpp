/*
  spektrum.cpp
  Implementation file for Spektrum serial receiver mbed library
  Dennis Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"

#include "spektrum.h"






/** Spektrum is used for a working connection to a Spektrum Satellite receiver
    @param(tx), orange wire, 3.3V supply pin (should be held high normally)
    @param(rx), gray wire, rx pin from the receiver
    The black wire should be connected to ground. 

    The receiver should first be bound using a BindPlug object. 
*/
Spektrum::Spektrum(PinName tx, PinName rx):
  _rx(tx, rx, SPEKTRUM_BAUD){
  
  // receiver uses e.g. p13, p14 and 115200 baud. 
  _rx.set_blocking(false); // want receiver to not block
  period_ms = 11; // start with 11ms period.

  // initialize public variables... 
  system = 0; // should be 0xa2 or 0xb2 for DSMX modes
  fades = 0;
  for (int i=0; i<SPEKTRUM_CHANNELS; i++){
    channel[i] = 0; 
    pulsewidth[i] = 0;
  }
  valid = false; 

  // start the packet reading thread
  _packet_thread.start(callback(this,&Spektrum::_packet_callback)); 
} // Spektrum(tx, rx) constructor




/** Destructor for Spektrum object 
 */
Spektrum::~Spektrum(){
} // ~Spektrum() destructor



/** Private callback for when a packet is received
 */
void Spektrum::_packet_callback(void){
  // local variables
  int count; // used to get error code -11 or num of bytes _rx.read()
  uint64_t now; // for getting 11 or 22 ms period via ThisThread::sleep_until()
  unsigned int i; // counter for for loop
  unsigned int data; // for assembling 2 bytes into uint16_t
  unsigned int chanid; // for decoding channel ID with mask 0x7800
  unsigned int servopos; // for decoding servo value with mask 0x07ff
  
  // setup
  debug("Spektrum::_packet_thread started\r\n");

  // loop
  _rx.sync(); // flush buffer
  while(1){
    now = rtos::Kernel::get_ms_count(); // for timing
    count = _rx.read(_buf,SPEKTRUM_PACKET_SIZE); // try to read packet
    
    if (count == SPEKTRUM_PACKET_SIZE){
      // got a full sized packet
      if (_buf[1] == SPEKTRUM_22MS_2048_DSMX){
	period_ms = 22; 
	valid = true;
      } // got 22ms packets
      else if (_buf[1] == SPEKTRUM_11MS_2048_DSMX){
	period_ms = 11;
	valid = true;
      } // got 11ms packets
      else
	// if system is not 0xa2 or 0xb2, treat as invalid
	valid = false;
    } // if count == 16
    else {
      // count wasn't 16 so some kind of error
      valid = false;
      _rx.sync(); // not getting enough bytes, so sync()
    }

    if (valid){
      // got a valid packet so parse it 
      fades = _buf[0];
      system = _buf[1];
      for (i=0; i<SPEKTRUM_SERVOS; i++){
	data = (_buf[2*i+2]<<8) | _buf[2*i+2+1];
	chanid = (data & SPEKTRUM_MASK_2048_CHANID) >> 11;
	servopos = data & SPEKTRUM_MASK_2048_SXPOS;
	channel[chanid] = servopos;
	pulsewidth[chanid] = SPEKTRUM_COUNT2US(servopos); 
      } // for each servo in packet
    } // if(valid)

    ThisThread::sleep_until(now+period_ms); // sleep to get right rate
  } // while(1)
} // _packet_callback() 









/** BindPlug is used to bind a Spektrum Satellite receiver
    @param(tx), orange wire, 3.3V supply pin, here used as a DigitalOut
    @param(rx), gray wire, rx pin, here used as a DigitalOut
    @param(mode) is mode, e.g. internal or external, DSM2 or DSMX, 11 or 22ms
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

/** Destructor for BindPlug object
 */
BindPlug::~BindPlug(){
} // ~BindPlug() destructor






/* LATER
SpektrumTestDevice::SpektrumTestDevice(PinName tx, PinName rx): _receiver(tx,rx){
  _receiver.baud(SPEKTRUM_BAUD);
} // SpektrumTestDevice(tx, rx) constructor

SpektrumTestDevice::~SpektrumTestDevice(){
} // ~SpektrumTestDevice() destructor
*/
