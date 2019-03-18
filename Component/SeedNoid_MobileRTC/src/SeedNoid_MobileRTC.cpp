// -*- C++ -*-
/*!
 * @file  SeedNoid_MobileRTC.cpp
 * @brief SeedNoid Mobile component
 * @date $Date$
 *
 * $Id$
 */

#include "SeedNoid_MobileRTC.h"

// Module specification
// <rtc-template block="module_spec">
static const char* seednoid_mobilertc_spec[] =
  {
    "implementation_id", "SeedNoid_MobileRTC",
    "type_name",         "SeedNoid_MobileRTC",
    "description",       "SeedNoid Mobile component",
    "version",           "1.2.0",
    "vendor",            "rsdlab",
    "category",          "SeedNoid",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.debug", "0",
    "conf.default.PortName", "/dev/ttyUSB0",
    "conf.default.WheelRadiusParam", "0.076",
    "conf.default.TreadParam", "0.39",
    "conf.default.WheelBaseParam", "0.453",

    // Widget
    "conf.__widget__.debug", "text",
    "conf.__widget__.PortName", "text",
    "conf.__widget__.WheelRadiusParam", "text",
    "conf.__widget__.TreadParam", "text",
    "conf.__widget__.WheelBaseParam", "text",
    // Constraints

    "conf.__type__.debug", "int",
    "conf.__type__.PortName", "string",
    "conf.__type__.WheelRadiusParam", "double",
    "conf.__type__.TreadParam", "double",
    "conf.__type__.WheelBaseParam", "double",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
SeedNoid_MobileRTC::SeedNoid_MobileRTC(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_targetVelocityIn("targetVelocity", m_targetVelocity),
    m_currentPoseOut("currentPose", m_currentPose),
    m_lifterPosePort("lifterPose")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
SeedNoid_MobileRTC::~SeedNoid_MobileRTC()
{
}



RTC::ReturnCode_t SeedNoid_MobileRTC::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("targetVelocity", m_targetVelocityIn);
  
  // Set OutPort buffer
  addOutPort("currentPose", m_currentPoseOut);
  
  // Set service provider to Ports
  m_lifterPosePort.registerProvider("LifterPose", "SeedNoid_Lifter::LifterPose", m_LifterPose);
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  addPort(m_lifterPosePort);
  m_LifterPose.setRTC(this);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("debug", m_debug, "0");
  bindParameter("PortName", m_PortName, "/dev/ttyUSB0");
  bindParameter("WheelRadiusParam", m_WheelRadiusParam, "0.076");
  bindParameter("TreadParam", m_TreadParam, "0.39");
  bindParameter("WheelBaseParam", m_WheelBaseParam, "0.453");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SeedNoid_MobileRTC::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedNoid_MobileRTC::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedNoid_MobileRTC::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t SeedNoid_MobileRTC::onActivated(RTC::UniqueId ec_id)
{
  //----------Set Seednoid Param----------
  SC.seedSetParam(m_WheelRadiusParam,m_TreadParam,m_WheelBaseParam);

  //----------Set Seednoid Param----------
  SC.resetParam();

  //----------Open Serial Port----------
  SC.seedSerialOpen(m_PortName,1000000);
 
  //----------Servo ON----------
  SC.seedSendServo(0,1,1);

  while(!m_targetVelocityIn.isEmpty())
    {
      m_targetVelocityIn.read();
    }
  m_targetVelocity = {0,0,0};
  
  truckVelocity = {0,0,0};
  odometryData = {0,0,0,0};
  
  LifterAngle = {0,0};
  LifterPose = {0,0};
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SeedNoid_MobileRTC::onDeactivated(RTC::UniqueId ec_id)
{
  //----------Servo OFF----------
  SC.seedSendServo(0,0,1);

  //----------Close Serial Port----------
  SC.seedSerialClose();
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SeedNoid_MobileRTC::onExecute(RTC::UniqueId ec_id)
{
  if(m_targetVelocityIn.isNew())
    {
      m_targetVelocityIn.read();
      
      truckVelocity.vx = m_targetVelocity.data.vx;
      truckVelocity.vy = m_targetVelocity.data.vy;
      truckVelocity.va = m_targetVelocity.data.va;
      
      //----------Send Speed----------
      SC.seedSendTruckSpeed(truckVelocity);

      //----------Check Odometry----------
      SC.seedCalcOdometry(odometryData);
  
      m_currentPose.data.position.x = odometryData.x;
      m_currentPose.data.position.y = odometryData.y;
      m_currentPose.data.heading = odometryData.heading;
    }

  m_currentPoseOut.write();
  
  if(m_debug)
    {
      std::cout << "PositionX : " << odometryData.x << " [m] " << std::endl;
      std::cout << "PositionY : " << odometryData.y << " [m] " << std::endl;
      std::cout << "Direction : " << odometryData.heading << " [rsd] " << std::endl;
    }

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SeedNoid_MobileRTC::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedNoid_MobileRTC::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedNoid_MobileRTC::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedNoid_MobileRTC::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedNoid_MobileRTC::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void SeedNoid_MobileRTCInit(RTC::Manager* manager)
  {
    coil::Properties profile(seednoid_mobilertc_spec);
    manager->registerFactory(profile,
                             RTC::Create<SeedNoid_MobileRTC>,
                             RTC::Delete<SeedNoid_MobileRTC>);
  }
  
};


