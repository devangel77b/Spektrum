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



int main(){

  pc.printf("Spektrum receiver simple test\r\n");
  pc.printf("Be sure to connect orange to p13, gray to p14, blk to gnd\r\n");
  pc.printf("Receiver should have already been bound to transmitter\r\n");
  
  pc.printf("Successful (y/n)? ");
  pc.scanf(" %c",&c);
  TEST_ASSERT_EQUAL_MESSAGE('y',c,"receiver simple test failed.\r\n");

} // main() for TESTS/receiver/simple









