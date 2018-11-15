/*
  TESTS/receiver/simple/main.cpp
  Spektrum receiver simple test
  D Evangelista, 2018

  Appears to be working, 11/15/2018 with SPM9745

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
char c;
int i;
int j; 
uint64_t now; 


int main(void){

  pc.printf("Spektrum library version ");
  pc.printf(SPEKTRUM_VERSION); 
  pc.printf("\r\nSpektrum receiver simple test\r\n");
  pc.printf("Be sure to connect orange to p13, gray to p14, blk to gnd\r\n");
  pc.printf("Receiver should have already been bound to transmitter DSMX 22ms\r\n");
  pc.printf("Printing about 22s of data now...\r\n");



  // loop to show 22s of receiver data
  for (i=0; i<1000; i++){
    now = rtos::Kernel::get_ms_count();
    
    pc.printf("%d ",i);
    if (rx.valid){
      pc.printf("%d %02x ",rx.fades,rx.system); 
      for (j=0; j<9; j++){ // my DX9 only has 9 channels
	pc.printf("%04d ",rx.channel[j]);
      }
      pc.printf("\r\n");
    }
    else
      pc.printf(" invalid\r\n");
    
    ThisThread::sleep_until(now+rx.period_ms); 
  }//for 22 s of data. 



  
  pc.printf("Successful (y/n)? ");
  pc.scanf(" %c",&c);
  TEST_ASSERT_EQUAL_MESSAGE('y',c,"receiver simple test failed.\r\n");

} // main() for TESTS/receiver/simple









