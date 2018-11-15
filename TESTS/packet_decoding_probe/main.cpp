/*
After I got the baud rate and packet read framed correctly, I tried 
parsing it. There appear to be differences with what the Spektrum Serial
Receiver format says. For example, the first two bytes are reverse (MSB LSB) 
rather than "first" byte is system, "second" byte is fades - they really mean
that LSB is system, MSB is fades... the other 14 bytes then parse OK as 
specified in the manual (two different ways shown below both work). 
 */

#include "mbed.h"
#include "rtos.h"

#define PACKET_SIZE 16

Serial pc(USBTX,USBRX,115200);

int main(void){
  unsigned char buf[PACKET_SIZE] = {0x00, 0xa2, 0x0b, 0xfe,
				    0x01, 0x64, 0x14, 0x00,
				    0x26, 0xaa, 0x1c, 0x02,
				    0x31, 0x56, 0x29, 0x56};

  pc.printf("fades: %02x\r\n",buf[0]);
  pc.printf("system: %02x\r\n",buf[1]);

  for (int i=0; i<7; i++){
    int msb = buf[2*i+2];
    int lsb = buf[2*i+2+1];
    int data = (msb<<8) | lsb;
    //int chanid = (data & 0x7800) >>11; // works
    int chanid = (buf[2*i+2] & 0x78) >> 3; // also works
    //int servopos = data & 0x07ff; // works
    int servopos = ((buf[2*i+2] << 8) | (buf[2*i+2+1])) & 0x07ff; // also works
    pc.printf("%02x%02x: channel %d got %04d\r\n",msb,lsb,chanid,servopos);
  }
  
  
  return 0; 
}
