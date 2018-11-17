/*
  TESTS/binding/ext_dsmx_22ms/main.cpp
  Spektrum binding test, external DSMX 22ms
  D Evangelista, 2018
  Expected failure when using satellite receiver as the only receiver
*/

#include "mbed.h"
#include "rtos.h"
#include "Spektrum.h"
#include "unity.h"

Serial pc(USBTX, USBRX); 
BindPlug bind_Plug(p13, p14, SPEKTRUM_EXT_DSMX_22MS);
char c;



int main(){

  pc.printf("Spektrum library version ");
  pc.printf(SPEKTRUM_VERSION); 
  pc.printf("\r\nSpektrum binding test, external DSMX 22ms\r\n");
  pc.printf("Be sure to connect orange to p13, gray to p14, blk to gnd\r\n");
  pc.printf("Should see blinking light, transmitter should attempt bind\r\n");
  pc.printf("KNOWNFAIL when using a single receiver\r\n"); 
  pc.printf("Was binding successful (y/n)? ");
  pc.scanf(" %c",&c);

  TEST_ASSERT_EQUAL_MESSAGE('y',c,"Binding test failed.\r\n");

} // main() for TESTS/binding/ext_dsmx_22ms









