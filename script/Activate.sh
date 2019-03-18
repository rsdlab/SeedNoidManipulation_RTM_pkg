#!bin/sh

export HOST="localhost"

rtact $HOST/SeedUpperBodyRTC0.rtc
rtact $HOST/SeedLifterEyeLinkKinematics0.rtc
rtact $HOST/Conversion_Mat0.rtc
rtact $HOST/ObstacleManager0.rtc
rtact $HOST/SeedArmPathGenerator0.rtc
rtact $HOST/SeedNoid_MobileRTC0.rtc
rtact $HOST/SeedUpperBodyTestController0.rtc
rtact $HOST/RightSeedArmMotionPlanning0.rtc
