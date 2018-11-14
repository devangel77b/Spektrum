/*
  TESTS/receiver/passthru/main.cpp
  Spektrum receiver pass thru test
  D Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "spektrum.h"
#include "unity.h"

Serial pc(USBTX, USBRX);
Spektrum receiver(p13, p14);
PwmOut throttle(p21);
PwmOut aileron(p22);
PwmOut elevator(p23);
PwmOut rudder(p24);
char c;
int i; 


int main(void){

  pc.printf("Spektrum receiver passthru test\r\n");
  pc.printf("Be sure to connect orange to p13, gray to p14, blk to gnd\r\n");
  pc.printf("Receiver should have already been bound to transmitter DSMX 22ms\r\n");
  pc.printf("Echoing about 22s of data now...\r\n");

  throttle.period_ms(20); throttle.pulsewidth_us(900); 
  aileron.period_ms(20); aileron.pulsewidth_us(900); 
  elevator.period_ms(20); elevator.pulsewidth_us(900); 
  rudder.period_ms(20); rudder.pulsewidth_us(900);  
  

  for (i=0; i<1000; i++){
    if (receiver.valid){
      // display on screen? may be too slow for 22 ms update rate
      pc.printf("%d. THR %4d AIL %4d ELE %4d RUD %4d\r\n",
		i, 
		receiver.channel[0], receiver.channel[1],
		receiver.channel[2], receiver.channel[3]);

      // set pwms 
      throttle.pulsewidth_us(spektrum_us(receiver.channel[0]));
      aileron.pulsewidth_us(spektrum_us(receiver.channel[1]));
      elevator.pulsewidth_us(spektrum_us(receiver.channel[2]));
      rudder.pulsewidth_us(spektrum_us(receiver.channel[3]));
    } // if valid
    else {
      pc.printf("%d. no data!\r\n",i);
    } // not valid
    
    ThisThread::sleep_for(22); 
  }//for
  
  pc.printf("Successful (y/n)? ");
  pc.scanf(" %c",&c);
  TEST_ASSERT_EQUAL_MESSAGE('y',c,"receiver passthru test failed.\r\n");

} // main() for TESTS/receiver/passthru









