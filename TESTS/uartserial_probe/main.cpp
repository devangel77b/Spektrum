/*
Since asynchronous serial API in regular mbed Serial object did not want to 
work right, I tried using UARTSerial to gain better access to protected
things like sync() and set_blocking(). This also gives me a read() method
that will try to read into a buffer PACKET_SIZE bytes and return the number
gotten. With some tweaking, this seems to work for getting updates at 22ms
and getting the framing right. If a packet is lost (short some bytes) then 
I have it flush the buffer using sync() to get back in sync. 

If the transmitter is off, the reads return -11 (error code). 
This could be used to do a Timeout function in our final Spektrum receiver API.

I tested this by running it for an hour to see if it got into oddly framed
craziness but it appears steadily doing
16: 00 a2 0bfd 01 64 14 00 26 aa 1c 02 31 56 29 56
which I then had the packet_decoding_probe code decode for me. 
 */
#include "mbed.h"
#include "rtos.h"

#define PACKET_SIZE 16

Serial pc(USBTX,USBRX,115200);
UARTSerial receiver(p13,p14,115200);


int main(void){
  int count;
  uint64_t now;
  unsigned char buf[PACKET_SIZE];
  int i; 
  
  pc.printf("UARTSerial test code\r\n");
  
  receiver.set_blocking(false); // set to not blocking
  receiver.sync(); // flush buffer
  while(1){
    now = rtos::Kernel::get_ms_count();
    count = receiver.read(buf,PACKET_SIZE);
    if (count){
      pc.printf("%2d: ",count);
      for (i=0; i<count; i++)
	pc.printf("%02x ",buf[i]);
      pc.printf("\r\n");
      
      if (count != PACKET_SIZE) 
	receiver.sync(); // flush buffer to avoid framing errors
    }
    else
      pc.printf("%2d\r\n",count);
    
    ThisThread::sleep_until(now+22); 
  }
  
  return 0;
} // main()

