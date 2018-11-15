/*
  TESTS/receiver/passthru/main.cpp
  Spektrum receiver pass thru test
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
#include "unity.h"

Serial pc(USBTX, USBRX, 115200);
Spektrum rx(p13, p14);
PwmOut throttle(p21);
PwmOut aileron(p22);
PwmOut elevator(p23);
PwmOut rudder(p24);
char c;
int i;
uint64_t now; 


int main(void){

  pc.printf("Spektrum library version ");
  pc.printf(SPEKTRUM_VERSION);
  pc.printf("\r\nSpektrum receiver passthru test\r\n");
  pc.printf("Be sure to connect orange to p13, gray to p14, blk to gnd\r\n");
  pc.printf("Receiver should have already been bound to transmitter DSMX 22ms\r\n");

  pc.printf("Initializing PwmOut objects for throttle, aileron, elevator, rudder\r\n");
  throttle.period_ms(20); throttle.pulsewidth_us(900); 
  aileron.period_ms(20); aileron.pulsewidth_us(900); 
  elevator.period_ms(20); elevator.pulsewidth_us(900); 
  rudder.period_ms(20); rudder.pulsewidth_us(900);  

  pc.printf("Printing 1000 frames of data now...\r\n");
  for (i=0; i<1000; i++){
    now = rtos::Kernel::get_ms_count();
    
    if (rx.valid){
      // display on screen? may be too slow for 22 ms update rate
      pc.printf("%d. THR %4d AIL %4d ELE %4d RUD %4d\r\n",
		i, 
		rx.pulsewidth[0],
		rx.pulsewidth[1],
		rx.pulsewidth[2],
		rx.pulsewidth[3]);

      // set pwms 
      throttle.pulsewidth_us(rx.pulsewidth[0]);
      aileron.pulsewidth_us(rx.pulsewidth[1]);
      elevator.pulsewidth_us(rx.pulsewidth[2]);
      rudder.pulsewidth_us(rx.pulsewidth[3]);
    } // if valid
    else {
      pc.printf("%d. invalid\r\n",i);
    } // not valid
    
    ThisThread::sleep_until(now+rx.period_ms); 
  }//for
  
  pc.printf("Successful (y/n)? ");
  pc.scanf(" %c",&c);
  TEST_ASSERT_EQUAL_MESSAGE('y',c,"receiver passthru test failed.\r\n");

} // main() for TESTS/receiver/passthru









