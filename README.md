# spektrum

### Dennis Evangelista
This library provides mbed support for Spektrum serial receivers. So far, the library has been tested on a [Spektrum SPM9745 DSMX remote receiver](https://www.horizonhobby.com/SPM9745?KPID=SPM9745&CAWELAID=320011980001425764&CAGPSPN=pla&CAAGID=37619207031&CATCI=pla-518519028442&gclid=CjwKCAiAz7TfBRAKEiwAz8fKOFgsklymSCgwfoY6IgzJ0decXHqctabFSpUVYezkrSFwuWUkJqiS4RoCbcwQAvD_BwE), and will probably be tested on a SPM9645 in the near future. 

## Obtaining the library
Source code is revision controlled using Git and hosted in a Github repository.
```bash
git clone ssh://git@github.com/devangel77b/spektrum.git
git pull
```
The ```dev``` branch is bleeding edge; ```master``` branch is reasonably up to date. 

## Using the library
The main part of the library are two classes for ```Spektrum``` (receiver) and ```BindPlug```, which allows binding a transmitter to the receiver. In addition, a convenience macro for converting 0-2048 values to PwmOut pulsewidths (600-2100us, centered at 900us) is provided (```SPEKTRUM_COUNT2US()```). 

## Note on servo position (0-2048) and pwm pulse width
The specification for Spektrum Remote Receiver Interfacing, rev A, 12 Apr 2016, has a note about servo position ranges:

> A full range of servo position data ranges from 0-1024 or 0-2045 depending on the bind type. These limits are equivalent to a +/-150% travel setting in AirWare. This full range translates to a range of 1194us which when applied to a pwm servo signal equals 903-2097us. At +/-100% travel, the data range is equivalent to a servo position data range of approximately 341 to 1707 which translated to pwm equals 1102 us to 1898 us.

## Contributors
D Evangelista

## Acknowledgements and references
1. The code is based on an earlier Spektrum code by M Nentwig, [https://os.mbed.com/users/offroad/code/spektRx/], however, that code appears to have used an earlier version of Spektrum standard that appears no longer to cover the serial Satellite and DSMX quad race receivers. 

2. "Spektrum Remote Receiver Interfacing", rev A, dtd 12 Apr 2016 [https://www.spektrumrc.com/ProdInfo/Files/Remote%20Receiver%20Interfacing%20Rev%20A.pdf], however, there are some slight differences between what is described there and what was observed when probing a SPM9745 DSMX remote receiver.  

