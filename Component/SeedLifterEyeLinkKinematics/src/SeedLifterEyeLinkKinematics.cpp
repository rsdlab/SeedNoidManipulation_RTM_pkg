// -*- C++ -*-
/*!
 * @file  SeedLifterEyeLinkKinematics.cpp
 * @brief SeedLifterEyeLinkKinematics
 * @date $Date$
 *
 * $Id$
 */

#include "SeedLifterEyeLinkKinematics.h"

// Module specification
// <rtc-template block="module_spec">
static const char* seedliftereyelinkkinematics_spec[] =
  {
    "implementation_id", "SeedLifterEyeLinkKinematics",
    "type_name",         "SeedLifterEyeLinkKinematics",
    "description",       "SeedLifterEyeLinkKinematics",
    "version",           "1.0.0",
    "vendor",            "rsdlab",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
SeedLifterEyeLinkKinematics::SeedLifterEyeLinkKinematics(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_Transformation_InterfacePort("Transformation_Interface"),
    m_SeedUpperInterface_CommonPort("SeedUpperInterface_Common")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
SeedLifterEyeLinkKinematics::~SeedLifterEyeLinkKinematics()
{
}



RTC::ReturnCode_t SeedLifterEyeLinkKinematics::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  m_Transformation_InterfacePort.registerProvider("transformationInterface", "TransformationMatrix::transformationInterface", m_transformationInterface);
  
  // Set service consumers to Ports
  m_SeedUpperInterface_CommonPort.registerConsumer("SeedUpperInterface_Common", "SEED_UPPER::SeedUpperInterface_Common", m_SeedUpperInterface_Common);
  
  // Set CORBA Service Ports
  addPort(m_Transformation_InterfacePort);
  addPort(m_SeedUpperInterface_CommonPort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SeedLifterEyeLinkKinematics::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedLifterEyeLinkKinematics::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedLifterEyeLinkKinematics::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t SeedLifterEyeLinkKinematics::onActivated(RTC::UniqueId ec_id)
{
  m_transformationInterface.setCompPtr(this);
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SeedLifterEyeLinkKinematics::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SeedLifterEyeLinkKinematics::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SeedLifterEyeLinkKinematics::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedLifterEyeLinkKinematics::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedLifterEyeLinkKinematics::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedLifterEyeLinkKinematics::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedLifterEyeLinkKinematics::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

void SeedLifterEyeLinkKinematics::getSeedCurrentJoint(double lifterPos[],double waistPos[],double neckPos[])
{
  std::cout << "getSeedCurrentJoint" << std::endl;
  SEED_UPPER::Lifter nowLifterPos;
  SEED_UPPER::RPY nowWaistPos;
  SEED_UPPER::RPY nowNeckPos;
  SEED_UPPER::JointPos_var nowRightPosvar;
  SEED_UPPER::JointPos nowRightPos;
  SEED_UPPER::JointPos_var nowLeftPosvar;
  SEED_UPPER::JointPos nowLeftPos;
  nowRightPos.length(7);
  nowLeftPos.length(7);
  m_rid_upper=m_SeedUpperInterface_Common->getFeedbackPosAllJoint(nowLifterPos,nowWaistPos,nowNeckPos,nowRightPosvar,nowLeftPosvar);
  nowRightPos = nowRightPosvar;
  nowLeftPos = nowLeftPosvar;
  lifterPos[0] = nowLifterPos.bottom;
  lifterPos[1] = nowLifterPos.top;
  waistPos[0] = nowWaistPos.yaw;
  waistPos[1] = nowWaistPos.pitch;
  waistPos[2] = nowWaistPos.roll;
  neckPos[0] = nowNeckPos.yaw;
  neckPos[1] = nowNeckPos.pitch;
  neckPos[2] = nowNeckPos.roll;
  
}

extern "C"
{
 
  void SeedLifterEyeLinkKinematicsInit(RTC::Manager* manager)
  {
    coil::Properties profile(seedliftereyelinkkinematics_spec);
    manager->registerFactory(profile,
                             RTC::Create<SeedLifterEyeLinkKinematics>,
                             RTC::Delete<SeedLifterEyeLinkKinematics>);
  }
  
};


