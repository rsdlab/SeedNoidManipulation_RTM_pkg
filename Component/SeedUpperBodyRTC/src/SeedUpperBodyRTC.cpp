// -*- C++ -*-
/*!
 * @file  SeedUpperBodyRTC.cpp
 * @brief SeedUpperBodyRTC
 * @date $Date$
 *
 * $Id$
 */

#include "SeedUpperBodyRTC.h"

// Module specification
// <rtc-template block="module_spec">
static const char* seedupperbodyrtc_spec[] =
  {
    "implementation_id", "SeedUpperBodyRTC",
    "type_name",         "SeedUpperBodyRTC",
    "description",       "SeedUpperBodyRTC",
    "version",           "1.0.0",
    "vendor",            "rsdlab",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.port_name", "/dev/ttyUSB0",

    // Widget
    "conf.__widget__.port_name", "text",
    // Constraints

    "conf.__type__.port_name", "string",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
SeedUpperBodyRTC::SeedUpperBodyRTC(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_SeedUpperInterface_CommonPort("SeedUpperInterface_Common"),
    m_SeedUpperInterface_MiddlePort("SeedUpperInterface_Middle"),
    m_WaistInterfacePort("WaistInterface"),
    m_NeckInterfacePort("NeckInterface"),
    m_LifterPosePort("LifterPose")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
SeedUpperBodyRTC::~SeedUpperBodyRTC()
{
}



RTC::ReturnCode_t SeedUpperBodyRTC::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  m_SeedUpperInterface_CommonPort.registerProvider("SeedUpperInterface_Common", "SEED_UPPER::SeedUpperInterface_Common", m_SeedUpperInterface_Common);
  m_SeedUpperInterface_MiddlePort.registerProvider("SeedUpperInterface_Middle", "SEED_UPPER::SeedUpperInterface_Middle", m_SeedUpperInterface_Middle);
  m_WaistInterfacePort.registerProvider("WaistInterface", "WaistNeck::WaistInterface", m_WaistInterface);
  m_NeckInterfacePort.registerProvider("NeckInterface", "WaistNeck::NeckInterface", m_NeckInterface);
  
  // Set service consumers to Ports
  m_LifterPosePort.registerConsumer("LifterPose", "SeedNoid_Lifter::LifterPose", m_LifterPose);
  
  // Set CORBA Service Ports
  addPort(m_SeedUpperInterface_CommonPort);
  addPort(m_SeedUpperInterface_MiddlePort);
  addPort(m_WaistInterfacePort);
  addPort(m_NeckInterfacePort);
  addPort(m_LifterPosePort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("port_name", m_port_name, "/dev/ttyUSB0");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SeedUpperBodyRTC::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedUpperBodyRTC::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedUpperBodyRTC::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t SeedUpperBodyRTC::onActivated(RTC::UniqueId ec_id)
{
  m_SeedUpperInterface_Middle.setCompPtr(this);
  m_SeedUpperInterface_Common.setCompPtr(this);
  m_WaistInterface.setCompPtr(this);
  m_NeckInterface.setCompPtr(this);
  if (noid.OpenSerialPort(m_port_name.c_str())){
    std::cout << "Connect Error!" << std::endl;
    return RTC::RTC_ERROR;
  }
  noid.initPosition();
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SeedUpperBodyRTC::onDeactivated(RTC::UniqueId ec_id)
{
  noid.CloseSerialPort();
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SeedUpperBodyRTC::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SeedUpperBodyRTC::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedUpperBodyRTC::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedUpperBodyRTC::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedUpperBodyRTC::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedUpperBodyRTC::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

void SeedUpperBodyRTC::getLifterPos(double lifterPos[])
{
  SeedNoid_Lifter::LifterAngle currentLifterAngle;
  m_LifterPose->getLifterAngle(currentLifterAngle);
  lifterPos[0] = currentLifterAngle.bottom;
  lifterPos[1] = currentLifterAngle.top;
}

void SeedUpperBodyRTC::movePTPLifter(double lifterPos[])
{
  SeedNoid_Lifter::LifterAngle TargetLifterAngle;
  TargetLifterAngle.bottom = lifterPos[0]; 
  TargetLifterAngle.top = lifterPos[1];
  m_LifterPose->sendLifterAngle(TargetLifterAngle);
}

extern "C"
{
 
  void SeedUpperBodyRTCInit(RTC::Manager* manager)
  {
    coil::Properties profile(seedupperbodyrtc_spec);
    manager->registerFactory(profile,
                             RTC::Create<SeedUpperBodyRTC>,
                             RTC::Delete<SeedUpperBodyRTC>);
  }
  
};


