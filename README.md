# spektrum
### Dennis Evangelista
This library provides mbed support for Spektrum serial receivers. 

## Obtaining the library
Source code is revision controlled using Git and hosted in a Github repository.
```bash
git clone ssh://git@github.com/devangel77b/spektrum.git
git pull
```
The ```dev``` branch is bleeding edge; ```master``` branch is reasonably up to date. 

## Using the library
The main part of the library are two classes for Spektrum (receiver) and BindPlug, which allows binding a transmitter to the receiver. In addition, a convenience function for converting 0-2048 values to PwmOut pulsewidths (600-2100us, centered at 900us) is provided (```spektrum_us()```). 

## Contributors
D Evangelista

## Acknowledgements
The code is based on an earlier Spektrum code by (that german guy). 
