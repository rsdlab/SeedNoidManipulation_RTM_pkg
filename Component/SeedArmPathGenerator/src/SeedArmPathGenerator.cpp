// -*- C++ -*-
/*!
 * @file  SeedArmPathGenerator.cpp
 * @brief SeedArmPathGenerator
 * @date $Date$
 *
 * $Id$
 */

#include "SeedArmPathGenerator.h"
#include <math.h>

// Module specification
// <rtc-template block="module_spec">
static const char* seedarmpathgenerator_spec[] =
  {
    "implementation_id", "SeedArmPathGenerator",
    "type_name",         "SeedArmPathGenerator",
    "description",       "SeedArmPathGenerator",
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
SeedArmPathGenerator::SeedArmPathGenerator(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_PathGeneratorInterfacePort("PathGeneratorInterface"),
    m_SeedUpperInterface_CommonPort("SeedUpperInterface_Common"),
    m_SeedUpperInterface_MiddlePort("SeedUpperInterface_Middle")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
SeedArmPathGenerator::~SeedArmPathGenerator()
{
}



RTC::ReturnCode_t SeedArmPathGenerator::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  m_PathGeneratorInterfacePort.registerProvider("PathGeneratorInterface", "Manipulation::PathGeneratorInterface", m_PathGeneratorInterface);
  
  // Set service consumers to Ports
  m_SeedUpperInterface_CommonPort.registerConsumer("SeedUpperInterface_Common", "SEED_UPPER::SeedUpperInterface_Common", m_SeedUpperInterface_Common);
  m_SeedUpperInterface_MiddlePort.registerConsumer("SeedUpperInterface_Middle", "SEED_UPPER::SeedUpperInterface_Middle", m_SeedUpperInterface_Middle);
  
  // Set CORBA Service Ports
  addPort(m_PathGeneratorInterfacePort);
  addPort(m_SeedUpperInterface_CommonPort);
  addPort(m_SeedUpperInterface_MiddlePort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SeedArmPathGenerator::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedArmPathGenerator::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedArmPathGenerator::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t SeedArmPathGenerator::onActivated(RTC::UniqueId ec_id)
{
  sleep(1);
  m_PathGeneratorInterface.setCompPtr(this);
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SeedArmPathGenerator::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SeedArmPathGenerator::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SeedArmPathGenerator::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedArmPathGenerator::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedArmPathGenerator::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedArmPathGenerator::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedArmPathGenerator::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

void SeedArmPathGenerator::getSeedCurrentJoint(double lifter[], double Waistpos[], double Rightpos[], double Leftpos[])
{
  std::cout << "getSeedCurrentJoint" << std::endl;
  SEED_UPPER::Lifter lifterPos;
  SEED_UPPER::RPY waistPos;
  SEED_UPPER::RPY neckPos;
  SEED_UPPER::JointPos_var rightPosvar;
  SEED_UPPER::JointPos rightPos;
  SEED_UPPER::JointPos_var leftPosvar;
  SEED_UPPER::JointPos leftPos;
  rightPos.length(7);
  leftPos.length(7);
  m_rid_upper=m_SeedUpperInterface_Common->getFeedbackPosAllJoint(lifterPos,waistPos,neckPos,rightPosvar,leftPosvar);
  rightPos = rightPosvar;
  leftPos = leftPosvar;

  lifter[0] = lifterPos.bottom;
  lifter[1] = lifterPos.top;
  Waistpos[0] = waistPos.yaw;
  Waistpos[1] = waistPos.pitch;
  Waistpos[2] = waistPos.roll;
 
  for(int g=0;g<7;g++){
    Rightpos[g] = rightPos[g];
  }
  for(int g=0;g<7;g++){
    Leftpos[g] = leftPos[g];
  }

  std::cout << "Success" << std::endl;
}

double SeedArmPathGenerator::getcmdCycle()
{
  std::cout << "getcmdCycle" << std::endl;
  SEED_UPPER::ManipInfo_var minfovar;
  SEED_UPPER::ManipInfo minfo;
  m_SeedUpperInterface_Common->getManipInfo(minfovar);
  minfo=minfovar;
  std::cout << "Success" << std::endl;
  return minfo.cmdCycle;
}

double SeedArmPathGenerator::getMaxSpeedJoint()
{
  std::cout << "getMaxSpeedJoint" << std::endl;
  SEED_UPPER::DoubleSeq_var maxSpeedvar;
  SEED_UPPER::DoubleSeq maxSpeed;
  maxSpeed.length(20);
  m_SeedUpperInterface_Middle->getMaxSpeedJoint(maxSpeedvar);
  maxSpeed=maxSpeedvar;
  std::cout << "Success" << std::endl;
  return maxSpeed[0];
}

double SeedArmPathGenerator::getSpeedRatioJoint()
{
  std::cout << "getSpeedRatioJoint" << std::endl;
  SEED_UPPER::ULONG spdRatio;
  m_SeedUpperInterface_Middle->getSpeedJoint(spdRatio);
  std::cout << "Success" << std::endl;
  return spdRatio;
}

void SeedArmPathGenerator::movePTPLIWARJointAbs(double jointPos[])
{
  SEED_UPPER::JointPos targetPos;
  targetPos.length(12);
  for(int i=0;i<12;i++)
    {
      targetPos[i] = jointPos[i];
      //std::cout << "inPos["<<i<<"] = " << jointPos[i] << std::endl;
      //std::cout << "sendPos["<<i<<"] = " << targetPos[i] << std::endl;
    }
  m_rid_upper = m_SeedUpperInterface_Middle->movePTPLIWARArmJointAbsCmdCycle(targetPos);
  if(m_rid_upper->id != 0){//Error
    std::cout<<"movePTPLIWARArmJointAbs ERROR"<<std::endl;
    std::cout<<m_rid_upper->comment<<std::endl<<std::endl;
  }
}
void SeedArmPathGenerator::movePTPLIWALJointAbs(double jointPos[])
{
  SEED_UPPER::JointPos targetPos;
  targetPos.length(12);
  for(int i=0;i<12;i++)
    {
      targetPos[i] = jointPos[i];
    }
  m_rid_upper = m_SeedUpperInterface_Middle->movePTPLIWALArmJointAbsCmdCycle(targetPos);
  if(m_rid_upper->id != 0){//Error
    std::cout<<"movePTPLIWARArmJointAbs ERROR"<<std::endl;
    std::cout<<m_rid_upper->comment<<std::endl<<std::endl;
  }
}
void SeedArmPathGenerator::movePTPDualJointAbs(double lifter[], double waist[], double right[], double left[])
{
  SEED_UPPER::Lifter lifterPos;
  SEED_UPPER::RPY waistPos;
  SEED_UPPER::JointPos rightPos;
  SEED_UPPER::JointPos leftPos;
  rightPos.length(7);
  leftPos.length(7);
  lifterPos.bottom = lifter[0];
  lifterPos.top = lifter[1];
  waistPos.yaw = waist[0];
  waistPos.pitch = waist[1];
  waistPos.roll = waist[2];
  for(int i=0;i<7;i++)
    {
      rightPos[i] = right[i];
      leftPos[i] = left[i];
    }
  
  m_rid_upper = m_SeedUpperInterface_Middle->movePTPDualArmJointAbsCmdCycle(lifterPos, waistPos,rightPos,leftPos);
  if(m_rid_upper->id != 0){//Error
    std::cout<<"movePTPLIWARArmJointAbs ERROR"<<std::endl;
    std::cout<<m_rid_upper->comment<<std::endl<<std::endl;
  }
}

void SeedArmPathGenerator::TransRot(double eerot[],double roll,double pitch,double yaw)
{
  //ロールピッチヨー　ロボット工学（遠山茂樹著）p25
  double Rrotx;
  double Rroty;
  double Rrotz;
  Rrotx = roll * M_PI / 180;
  Rroty = pitch * M_PI / 180;
  Rrotz = yaw * M_PI / 180;

  eerot[0] = cos(Rroty)*cos(Rrotz);
  eerot[1] = cos(Rrotz)*sin(Rroty)*sin(Rrotx)-sin(Rrotz)*cos(Rrotx);
  eerot[2] = cos(Rrotz)*sin(Rroty)*cos(Rrotx)+sin(Rrotz)*sin(Rrotx);
  eerot[3] = sin(Rrotz)*cos(Rroty);
  eerot[4] = sin(Rrotz)*sin(Rroty)*sin(Rrotx)+cos(Rrotz)*cos(Rrotx);
  eerot[5] = sin(Rrotz)*sin(Rroty)*cos(Rrotx)-cos(Rrotz)*sin(Rrotx);
  eerot[6] = -sin(Rroty);
  eerot[7] = cos(Rroty)*sin(Rrotx);
  eerot[8] = cos(Rroty)*cos(Rrotx);

}

Frame SeedArmPathGenerator::Solve_Rot(double eerot[])
{
  Frame rotation;
  double phi;//φ
  double theta;//θ
  double psi;//ψ

  for(int i=0;i<9;i++)
    {
      if(eerot[i]>1)
	eerot[i] = 1;
      if(eerot[i]<-1)
	eerot[i] = -1;
    }

  psi = atan2(eerot[3], eerot[0]);
  theta =  atan2(-eerot[6], sqrt(eerot[7]*eerot[7]+eerot[8]*eerot[8]));
  phi = atan2(eerot[7], eerot[8]);
  
  rotation.roll = phi*180/M_PI;
  rotation.pitch = theta*180/M_PI;
  rotation.yaw = psi*180/M_PI;

  return rotation;
}

extern "C"
{
 
  void SeedArmPathGeneratorInit(RTC::Manager* manager)
  {
    coil::Properties profile(seedarmpathgenerator_spec);
    manager->registerFactory(profile,
                             RTC::Create<SeedArmPathGenerator>,
                             RTC::Delete<SeedArmPathGenerator>);
  }
  
};


