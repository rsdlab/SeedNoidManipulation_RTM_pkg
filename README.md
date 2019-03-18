## SEED-Noid Manipulation RTM pkg

\autor MeijoUniversity Robot System Design Laboratory


## Install dependent library

```
sudo apt install libboost-all-dev
```


## Install OpenRTM-aist

http://www2.meijo-u.ac.jp/~kohara/cms/openrtm-aist_temp_install

## Download FRANN library

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

If you need to change the serial port, change the configuration parameters in the RT System Editor

## Activate
Please execute after connecting USB serial

```
cd ~/SeedNoidManipulation_RTM_pkg/script
sh Activate.sh
```

You can operate SEED-Noid using SeedUpperBodyTestController

SeedUpperBodyTestController terminal

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