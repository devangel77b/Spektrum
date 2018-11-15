/*
  Spektrum receiver passthru test for Sailbot
  D Evangelista, 2018

  Appears to be working 11/15/2018 with SPM9745
  NB: The specification for Spektrum Remote Receiver Interfacing,
  rev A, 12 Apr 2016, has a note about servo position ranges:
  "A full range of servo position data ranges from 0-1024 or 0-2045 depending
  on the bind type. These limits are equivalent to a +/-150% travel setting
  in AirWare. This full range translates to a range of 1194us which when 
  applied to a pwm servo signal equals 903-2097us. At +/-100% travel, the
  data range is equivalent to a servo position data range of approximately 
  341 to 1707 which translated to pwm equals 1102 us to 1898 us."
*/

#include "mbed.h"
#include "rtos.h"
#include "spektrum.h"

Serial pc(USBTX, USBRX, 115200);
Spektrum rx(p13, p14);
PwmOut mainsail(p21);
PwmOut rudder(p22);


int main(void){
  int i=0; // a counter for for loop
  uint64_t now; // for timing the loop to be 11 or 22ms

  // setup
  pc.printf("Spektrum library version ");
  pc.printf(SPEKTRUM_VERSION);
  pc.printf("\r\nSpektrum receiver passthru test for Sailbot\r\n");
  pc.printf("Be sure to connect orange to p13, gray to p14, blk to gnd\r\n");
  pc.printf("Receiver should have already been bound to transmitter DSMX 22ms\r\n");

  pc.printf("Initializing PwmOut objects for mainsail p21 and rudder p22\r\n");
  mainsail.period_ms(20); mainsail.pulsewidth_us(1500); // amidships
  rudder.period_ms(20); rudder.pulsewidth_us(1500); // amidships

  pc.printf("Now starting while(1) loop...\r\n");
  while(1){
    now = rtos::Kernel::get_ms_count();
    
    if (rx.valid){
      // display on screen? may be too slow for 22 ms update rate
      pc.printf("%d. mainsail %4d, rudder %4d\r\n",
		i++, 
		rx.pulsewidth[0], // DX9 channel 0 throttle
		rx.pulsewidth[3]); // DX9 channel 3 rudder

      // set pwms 
      mainsail.pulsewidth_us(rx.pulsewidth[0]);
      rudder.pulsewidth_us(rx.pulsewidth[3]);
    } // if valid
    else {
      pc.printf("%d. invalid\r\n",i);
    } // not valid
    
    ThisThread::sleep_until(now+rx.period_ms); 
  }//for
  
} // main()









