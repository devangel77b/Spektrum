#include "mbed.h"
#include "rtos.h"

#include "spektrum.h"


spektrum::Spektrum(PinName tx, PinName rx): _receiver(tx, rx){
  _receiver.baud(SPEKTRUM_BAUD); // Spektrum uses 125000 8N1 or 115200 8N1
} // Spektrum(tx, rx) constructor

spektrum::~Spektrum(){
} // ~Spektrum() destructor

void bind(int bind_mode = SPEKTRUM_INT_DSMX_11MS){
  debug("Spektrum: bind() not yet implemented");
}
