#!/bin/sh

#SeedUpperBodyRTCのbuild
cd ../Component/SeedUpperBodyRTC/
mkdir build
cd build
cmake ..
make -j4

#Conversion_Matのbuild
cd ../../Conversion_Mat/
mkdir build
cd build
cmake ..
make -j4

#SeedLifterEyeLinkKinematicsのbuild
cd ../../SeedLifterEyeLinkKinematics/
mkdir build
cd build
cmake ..
make -j4

#ObstacleManagerのbuild
cd ../../ObstacleManager/
mkdir build
cd build
cmake ..
make -j4

#SeedNoid_MobileRTCのbuild
cd ../../SeedNoid_MobileRTC/
mkdir build
cd build
cmake ..
make -j4

#RightSeedArmMotionPlanning_10DOFのbuild
cd ../../RightSeedArmMotionPlanning_10DOF/
mkdir build
cd build
cmake ..
make -j4

#SeedArmPathGeneratorのbuild
cd ../../SeedArmPathGenerator/
mkdir build
cd build
cmake ..
make -j4

#SeedUpperBodyTestControllerのbuild
cd ../../SeedUpperBodyTestController/
mkdir build
cd build
cmake ..
make -j4
