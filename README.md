## SEED-Noid Manipulation RTM pkg

Author MeijoUniversity Robot System Design Laboratory

## Dependencies
OS : Ubuntu 16.04
RTM : OpenRTM-aist 1.1.2
FLANN : flann-1.8.4


## Install boost library

```
sudo apt install libboost-all-dev
```


## Install OpenRTM-aist

Please refer to the following URL

http://www2.meijo-u.ac.jp/~kohara/cms/openrtm-aist_temp_install

## Install rtshell
rtshell is the script to manage the RT component-based system.
It strongly recommends to install the rtshell

http://www2.meijo-u.ac.jp/~kohara/cms/technicalreport/ubuntu_rtshell_install_112


## Download FRANN library
FRANN library is used for path planning of manipulator.
If following zip file could not download, please check the version.
(In this manual, our development environment is listed at "Depndencies")

Download ZIP
http://www.cs.ubc.ca/research/flann/

Version 1.8.4 command (2019/03/18)
```
wget http://www.cs.ubc.ca/research/flann/uploads/FLANN/flann-1.8.4-src.zip
unzip flann-1.8.4-src.zip
cd flann-1.8.4-src
mkdir build
cd build
cmake ..
make
```

## Download
```
git clone https://github.com/rsdlab/SeedNoidManipulation_RTM_pkg
```

## Build component
In this part, the components are cloned to user home directory.
```
cd ~/SeedNoidManipulation_RTM_pkg/script
sh BuildComp.sh
```


## Execution
```
cd ~/SeedNoidManipulation_RTM_pkg/script
sh EXE.sh
```
Lifter serial port is set to ``/dev/ttyUSB0``

Upper serial port is set to ``/dev/ttyUSB1``

If you need to change the serial port, please change the configuration parameters by the RT System Editor.
or
Please modify the "rtc.conf" before activate the components.

## Activate
Please execute after connecting USB serial cable to target PC.

```
cd ~/SeedNoidManipulation_RTM_pkg/script
sh Activate.sh
```

You can operate SEED-Noid by using SeedUpperBodyTestController
This RTC can directly control SEED Noid upper body to input the following commands.
Detail information, please check the manual of SeedUpperBodyTestController

## Deactivate
Please execute after select a command 10 : End

```
cd ~/SeedNoidManipulation_RTM_pkg/script
sh Deactivate.sh
```

## Exit

```
cd ~/SeedNoidManipulation_RTM_pkg/script
sh exit.sh
```