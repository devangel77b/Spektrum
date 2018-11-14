/*
  TESTS/receiver/simple/main.cpp
  Spektrum receiver test
  D Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "spektrum.h"
#include "unity.h"

Serial pc(USBTX, USBRX);
Spektrum receiver(p13, p14); 
char c;
int i; 


int main(void){

  pc.printf("Spektrum receiver simple test\r\n");
  pc.printf("Be sure to connect orange to p13, gray to p14, blk to gnd\r\n");
  pc.printf("Receiver should have already been bound to transmitter DSMX 22ms\r\n");
  pc.printf("Echoing about 22s of data now...\r\n");

  for (i=0; i<1000; i++){
    pc.printf("%d. system %x, fades %d, channel %04d %04d %04d %04d %04d %04d %04d %04d %04d\r\n",
	      i, receiver.system, receiver.fades,
	      receiver.channel[0], receiver.channel[1], receiver.channel[2],
	      receiver.channel[3], receiver.channel[4], receiver.channel[5],
	      receiver.channel[6], receiver.channel[7], receiver.channel[8]);
    ThisThread::sleep_for(22); 
  }//for
  
  pc.printf("Successful (y/n)? ");
  pc.scanf(" %c",&c);
  TEST_ASSERT_EQUAL_MESSAGE('y',c,"receiver simple test failed.\r\n");

} // main() for TESTS/receiver/simple









