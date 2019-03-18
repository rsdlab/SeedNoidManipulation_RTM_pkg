
#!bin/sh

export HOST="localhost"

echo ""
echo "Connect RT Component" 
echo ""

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
