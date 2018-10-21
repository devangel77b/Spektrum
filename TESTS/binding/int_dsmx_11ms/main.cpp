/*
  TESTS/binding/int_dsmx_11ms/main.cpp
  Spektrum binding test, internal DSMX 11ms
  D Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "spektrum.h"
#include "unity.h"

Serial pc(USBTX, USBRX); 
BindPlug bind_Plug(p13, p14, SPEKTRUM_INT_DSMX_11MS);
char c;



int main(){

  pc.printf("Spektrum binding test, internal DSMX 11ms\n\r");
  pc.printf("Be sure to connect orange to p13, gray to p14, blk to gnd\n\r");
  pc.printf("Should see blinking light, transmitter should attempt bind\n\r");
  pc.printf("Was binding successful (y/n)?\n\r");
  pc.scanf("%c",&c);

  TEST_ASSERT_TRUE_MESSAGE((c != 'n'),"Binding test failed.\n\r");

} // main() for TESTS/binding/int_dsmx_11ms









