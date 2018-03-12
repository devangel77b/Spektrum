#ifndef SPEKTRUM_H
#define SPEKTRUM_H

#include "mbed.h"

class Spektrum{
 public:
  Spektrum(PinName tx, PinName rx);

  

 private:
  Serial receiver;
}

#endif
