#!/bin/sh

COM="gnome-terminal -e"
export HOST="localhost"

echo ""
echo "Execution of SeedNoid Manipulation RT Component"
echo ""

$COM "../Component/ObstacleManager/build/src/ObstacleManagerComp -f ../Component/ObstacleManager/rtc.conf"
$COM "../Component/RightSeedArmMotionPlanning_10DOF/build/src/RightSeedArmMotionPlanningComp -f ../Component/RightSeedArmMotionPlanning_10DOF/rtc.conf"
$COM "../Component/SeedLifterEyeLinkKinematics/build/src/SeedLifterEyeLinkKinematicsComp -f ../Component/SeedLifterEyeLinkKinematics/rtc.conf"
$COM "../Component/SeedNoid_MobileRTC/build/src/SeedNoid_MobileRTCComp -f ../Component/SeedNoid_MobileRTC/rtc.conf"
$COM "../Component/SeedArmPathGenerator/build/src/SeedArmPathGeneratorComp -f ../Component/SeedArmPathGenerator/rtc.conf"
$COM "../Component/SeedUpperBodyRTC/build/src/SeedUpperBodyRTCComp -f ../Component/SeedUpperBodyRTC/rtc.conf"
$COM "../Component/SeedUpperBodyTestController/build/src/SeedUpperBodyTestControllerComp -f ../Component/SeedUpperBodyTestController/rtc.conf"
cd ../Component/Conversion_Mat/
$COM "build/src/Conversion_MatComp"


rtcon $HOST/SeedUpperBodyTestController0.rtc:MotionPlanningInterface $HOST/RightSeedArmMotionPlanning0.rtc:MotionPlanningInterface
rtcon $HOST/RightSeedArmMotionPlanning0.rtc:PathAndMotionGeneratorInterface $HOST/SeedArmPathGenerator0.rtc:PathGeneratorInterface
rtcon $HOST/RightSeedArmMotionPlanning0.rtc:ObstacleInterface $HOST/ObstacleManager0.rtc:Obstacle_Data
rtcon $HOST/RightSeedArmMotionPlanning0.rtc:conversionInterface $HOST/Conversion_Mat0.rtc:Conversion_Interface
rtcon $HOST/RightSeedArmMotionPlanning0.rtc:SeedUpperInterface_Common $HOST/SeedUpperBodyRTC0.rtc:SeedUpperInterface_Common
rtcon $HOST/RightSeedArmMotionPlanning0.rtc:SeedUpperInterface_Middle $HOST/SeedUpperBodyRTC0.rtc:SeedUpperInterface_Middle

rtcon $HOST/SeedNoid_MobileRTC0.rtc:lifterPose $HOST/SeedUpperBodyRTC0.rtc:LifterPose

rtcon $HOST/SeedArmPathGenerator0.rtc:SeedUpperInterface_Common $HOST/SeedUpperBodyRTC0.rtc:SeedUpperInterface_Common
rtcon $HOST/SeedArmPathGenerator0.rtc:SeedUpperInterface_Middle $HOST/SeedUpperBodyRTC0.rtc:SeedUpperInterface_Middle

rtcon $HOST/Conversion_Mat0.rtc:Transformation_Interface $HOST/SeedLifterEyeLinkKinematics0.rtc:Transformation_Interface
rtcon $HOST/SeedUpperBodyRTC0.rtc:SeedUpperInterface_Common $HOST/SeedLifterEyeLinkKinematics0.rtc:SeedUpperInterface_Common

rtcon $HOST/SeedUpperBodyTestController0.rtc:SeedUpperInterface_Common $HOST/SeedUpperBodyRTC0.rtc:SeedUpperInterface_Common
rtcon $HOST/SeedUpperBodyTestController0.rtc:SeedUpperInterface_Middle $HOST/SeedUpperBodyRTC0.rtc:SeedUpperInterface_Middle
rtcon $HOST/SeedUpperBodyTestController0.rtc:WaistInterface $HOST/SeedUpperBodyRTC0.rtc:WaistInterface
rtcon $HOST/SeedUpperBodyTestController0.rtc:NeckInterface $HOST/SeedUpperBodyRTC0.rtc:NeckInterface

rtconf $HOST/SeedUpperBodyRTC0.rtc set port_name "/dev/ttyUSB1"
