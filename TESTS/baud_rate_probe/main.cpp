/*
I did this to check if the LPC1768 was happy at 125000. 
It appears unhappy at 125000 and works better at 115200. 
 */

#include "mbed.h"
#include "rtos.h"

Serial pc(USBTX,USBRX,115200);

Serial receiver(p13,p14,115200);
unsigned char c; 

int main(void){
  pc.printf("hello\r\n");
  
  while(1){
    c = receiver.getc();

    if ((c==0xa2) || (c==0xb2))
      pc.printf("start\r\n");
  }
}
