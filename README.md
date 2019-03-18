## SEED-Noid Manipulation RTM pkg

\author MeijoUniversity Robot System Design Laboratory

## Dependencies


## Install boost library

```
sudo apt install libboost-all-dev
```


## Install OpenRTM-aist

Please refer to the following URL

http://www2.meijo-u.ac.jp/~kohara/cms/openrtm-aist_temp_install

## Install rtshell
rtshecll is the script to manage the RT component-based system.
It strongly recommends to install the rtshell

http://www2.meijo-u.ac.jp/~kohara/cms/technicalreport/ubuntu_rtshell_install_112


## Download FRANN library
FRANN library is used for path planning of manipulator.
If following zip file could not download, please check the version.
(In this manual, our development environment is listed at "Depndencies")

Download ZIP
http://www.cs.ubc.ca/research/flann/

```
cd flann-x.y.z-src
mkdir build
cd build
cmake ..
make
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

```
Please select a command
1 : Servo ON
2 : Servo OFF
3 : Control of the Right Arm
4 : Control of the Left Arm
5 : Control of the Neck
6 : Control of the Waist
7 : Get Current Angle
8 : Get Current End Effector Pos
9 : Motion Planning and Control
10 : End
```

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
