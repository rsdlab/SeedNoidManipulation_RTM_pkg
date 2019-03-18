// -*- C++ -*-
/*!
 * @file  RightSeedArmMotionPlanning.cpp
 * @brief RightSeedArmMotionPlanning
 * @date $Date$
 *
 * $Id$
 */

#include "RightSeedArmMotionPlanning.h"

// Module specification
// <rtc-template block="module_spec">
static const char* rightseedarmmotionplanning_spec[] =
  {
    "implementation_id", "RightSeedArmMotionPlanning",
    "type_name",         "RightSeedArmMotionPlanning",
    "description",       "RightSeedArmMotionPlanning",
    "version",           "1.0.0",
    "vendor",            "VenderName",
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
RightSeedArmMotionPlanning::RightSeedArmMotionPlanning(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_MotionPlanningInterfacePort("MotionPlanningInterface"),
    m_PathAndMotionGeneratorInterfacePort("PathAndMotionGeneratorInterface"),
    m_ObstacleInterfacePort("ObstacleInterface"),
    m_conversionInterfacePort("conversionInterface"),
    m_SeedUpperInterface_CommonPort("SeedUpperInterface_Common"),
    m_SeedUpperInterface_MiddlePort("SeedUpperInterface_Middle")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
RightSeedArmMotionPlanning::~RightSeedArmMotionPlanning()
{
}



RTC::ReturnCode_t RightSeedArmMotionPlanning::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  m_MotionPlanningInterfacePort.registerProvider("MotionPlanningInterface", "Planning::MotionPlanningInterface", m_MotionPlanningInterface);
  
  // Set service consumers to Ports
  m_PathAndMotionGeneratorInterfacePort.registerConsumer("PathGeneratorInterface", "Manipulation::PathGeneratorInterface", m_PathGeneratorInterface);
  m_ObstacleInterfacePort.registerConsumer("ObstacleInterface", "Obstacle::ObstacleInterface", m_ObstacleInterface);
  m_conversionInterfacePort.registerConsumer("conversionInterface", "ConversionMatrix::conversionInterface", m_conversionInterface);
  m_SeedUpperInterface_CommonPort.registerConsumer("SeedUpperInterface_Common", "SEED_UPPER::SeedUpperInterface_Common", m_SeedUpperInterface_Common);
  m_SeedUpperInterface_MiddlePort.registerConsumer("SeedUpperInterface_Middle", "SEED_UPPER::SeedUpperInterface_Middle", m_SeedUpperInterface_Middle);
  
  // Set CORBA Service Ports
  addPort(m_MotionPlanningInterfacePort);
  addPort(m_PathAndMotionGeneratorInterfacePort);
  addPort(m_ObstacleInterfacePort);
  addPort(m_conversionInterfacePort);
  addPort(m_SeedUpperInterface_CommonPort);
  addPort(m_SeedUpperInterface_MiddlePort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RightSeedArmMotionPlanning::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RightSeedArmMotionPlanning::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RightSeedArmMotionPlanning::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t RightSeedArmMotionPlanning::onActivated(RTC::UniqueId ec_id)
{
  std::cout << "Act" << std::endl;
  sleep(1);
  m_MotionPlanningInterface.setCompPtr(this);
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RightSeedArmMotionPlanning::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RightSeedArmMotionPlanning::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RightSeedArmMotionPlanning::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RightSeedArmMotionPlanning::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RightSeedArmMotionPlanning::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RightSeedArmMotionPlanning::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RightSeedArmMotionPlanning::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

void RightSeedArmMotionPlanning::getSeedCurrentJoint(double lifter[], double Waistpos[], double Rightpos[], double Leftpos[])
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


int RightSeedArmMotionPlanning::solveRightArmIk(SEED_UPPER::CarPosWithLifterWaistElbow goalPos, double nowRightJointPos[], double solRightJointPos[])
{
  std::cout << "solveLIWARArmIkSetRedunJoint" << std::endl;
  SEED_UPPER::JointPos nowPos;
  SEED_UPPER::JointPos_var ikSol_var;
  SEED_UPPER::JointPos ikSol;
  nowPos.length(12);
  for(int i=0;i<12;i++)
    {
      nowPos[i] = nowRightJointPos[i];
    }
  m_rid_upper = m_SeedUpperInterface_Middle->solveLIWARArmIkSetRedunJoint(goalPos,nowPos,ikSol_var);
  if(m_rid_upper->id != 0){//Error
    std::cout<<"solveLIWARArmIkSetRedunJoint ERROR"<<std::endl;
    std::cout<<m_rid_upper->comment<<std::endl<<std::endl;
    return -1;
  }
  ikSol = ikSol_var;
  return 0;
}


int RightSeedArmMotionPlanning::ConversionMat(Mat inMat,Mat* OutMat)
{
  std::cout << "ConversionMat" << std::endl;
  ConversionMatrix::transformationMat setInMat,setOutMat;
  setInMat.rotation.R11 = inMat.Rotation[0];
  setInMat.rotation.R12 = inMat.Rotation[1];
  setInMat.rotation.R13 = inMat.Rotation[2];
  setInMat.rotation.R21 = inMat.Rotation[3];
  setInMat.rotation.R22 = inMat.Rotation[4];
  setInMat.rotation.R23 = inMat.Rotation[5];
  setInMat.rotation.R31 = inMat.Rotation[6];
  setInMat.rotation.R32 = inMat.Rotation[7];
  setInMat.rotation.R33 = inMat.Rotation[8];
  setInMat.translates.x = inMat.Position[0];
  setInMat.translates.y = inMat.Position[1];
  setInMat.translates.z = inMat.Position[2];
  m_conversionInterface->getConvertionMat(setInMat,setOutMat);
  OutMat->Rotation[0] = setOutMat.rotation.R11;
  OutMat->Rotation[1] = setOutMat.rotation.R12;
  OutMat->Rotation[2] = setOutMat.rotation.R13;
  OutMat->Rotation[3] = setOutMat.rotation.R21;
  OutMat->Rotation[4] = setOutMat.rotation.R22;
  OutMat->Rotation[5] = setOutMat.rotation.R23;
  OutMat->Rotation[6] = setOutMat.rotation.R31;
  OutMat->Rotation[7] = setOutMat.rotation.R32;
  OutMat->Rotation[8] = setOutMat.rotation.R33;
  OutMat->Position[0] = setOutMat.translates.x;
  OutMat->Position[1] = setOutMat.translates.y;
  OutMat->Position[2] = setOutMat.translates.z;

  return 0;
}

int RightSeedArmMotionPlanning::PathGenerate(std::vector<TenDOF> trajectory)
{
  std::cout << "PathGenerate" << std::endl;
  int pathSize = trajectory.size();
  Manipulation::JointAngleSeq goalManipPos;
  Manipulation::JointAngleSeq startManipPos;
  Manipulation::ViaPosSeq viaPos;
  goalManipPos.length(12);
  startManipPos.length(12);
  std::cout << "trajectory.size() = " << pathSize << std::endl;
  startManipPos[0] = trajectory[0].theta1;
  startManipPos[1] = trajectory[0].theta2;
  startManipPos[2] = trajectory[0].theta3;
  startManipPos[3] = trajectory[0].theta4;
  startManipPos[4] = 0;
  startManipPos[5] = trajectory[0].theta5;
  startManipPos[6] = trajectory[0].theta6;
  startManipPos[7] = 0;
  startManipPos[8] = trajectory[0].theta7;
  startManipPos[9] = trajectory[0].theta8;
  startManipPos[10] = trajectory[0].theta9;
  startManipPos[11] = trajectory[0].theta10;
  
  viaPos.length(pathSize-2);//startとgoal除く
  for(int j=0;j<pathSize-2;j++)
    {
      viaPos[j].length(12);
      viaPos[j][0] = 0;
      viaPos[j][1] = 0;
      viaPos[j][2] = 0;
      viaPos[j][3] = 0;
      viaPos[j][4] = 0;
      viaPos[j][5] = 0;
      viaPos[j][6] = 0;
      viaPos[j][7] = 0;
      viaPos[j][8] = 0;
      viaPos[j][9] = 0;
      viaPos[j][10] = 0;
      viaPos[j][11] = 0;
    }

  goalManipPos[0] = 0;
  goalManipPos[1] = 0;
  goalManipPos[2] = 0;
  goalManipPos[3] = 0;
  goalManipPos[4] = 0;
  goalManipPos[5] = 0;
  goalManipPos[6] = 0;
  goalManipPos[7] = 0;
  goalManipPos[8] = 0;
  goalManipPos[9] = 0;
  goalManipPos[10] = 0;
  goalManipPos[11] = 0;

  //startのぶんだけオフセット
  for(int i=1;i<pathSize;i++)
    {

      if(i==pathSize-1)
	{
	  goalManipPos[0] = trajectory[i].theta1;
	  goalManipPos[1] = trajectory[i].theta2;
	  goalManipPos[2] = trajectory[i].theta3;
	  goalManipPos[3] = trajectory[i].theta4;
	  goalManipPos[4] = 0;
	  goalManipPos[5] = trajectory[i].theta5;
	  goalManipPos[6] = trajectory[i].theta6;
	  goalManipPos[7] = 0;
	  goalManipPos[8] = trajectory[i].theta7;
	  goalManipPos[9] = trajectory[i].theta8;
	  goalManipPos[10] = trajectory[i].theta9;
	  goalManipPos[11] = trajectory[i].theta10;
	}
      else
	{
	  viaPos[i-1][0] = trajectory[i].theta1;
	  viaPos[i-1][1] = trajectory[i].theta2;
	  viaPos[i-1][2] = trajectory[i].theta3;
	  viaPos[i-1][3] = trajectory[i].theta4;
	  viaPos[i-1][4] = 0;
	  viaPos[i-1][5] = trajectory[i].theta5;
	  viaPos[i-1][6] = trajectory[i].theta6;
	  viaPos[i-1][7] = 0;
	  viaPos[i-1][8] = trajectory[i].theta7;
	  viaPos[i-1][9] = trajectory[i].theta8;
	  viaPos[i-1][10] = trajectory[i].theta9;
	  viaPos[i-1][11] = trajectory[i].theta10;
	}
    }
    
    m_rid_manip=m_PathGeneratorInterface->JointSpaceGenerateRightArmViaMotion(viaPos,goalManipPos);
    if(m_rid_manip->id != 0){//Error
      std::cout<<"JointSpaceGenerateRightArmViaMotion ERROR"<<std::endl;
      std::cout<<m_rid_manip->comment<<std::endl<<std::endl;
      return RTC::RTC_OK;
    }
  
  return 0;
  
}

int RightSeedArmMotionPlanning::getObstacle(std::vector<AABB>& aabb)
{
  std::cout << "getObstacle" << std::endl;
  Obstacle::AABBSeq_var setAABBvar;
  Obstacle::AABBSeq setAABB;
  std::vector<AABB> setaabb;
  m_ObstacleInterface->getDisplayShelfObstacle(setAABBvar);
  setAABB = setAABBvar;
  int aabbLength = setAABB.length();
  std::cout << "setAABB.length() = " << aabbLength << std::endl;
  aabb.resize(aabbLength);
  for(int i=0;i<aabbLength;i++)
    {
      aabb[i].center.x = setAABB[i].center.x;
      aabb[i].center.y = setAABB[i].center.y;
      aabb[i].center.z = setAABB[i].center.z;
      aabb[i].rx = setAABB[i].rx;
      aabb[i].ry = setAABB[i].ry;
      aabb[i].rz = setAABB[i].rz;
      std::cout << "aabb["<<i<<"].center.x = " << aabb[i].center.x << std::endl;
      std::cout << "aabb["<<i<<"].center.y = " << aabb[i].center.y << std::endl;
      std::cout << "aabb["<<i<<"].center.z = " << aabb[i].center.z << std::endl;
      std::cout << "aabb["<<i<<"].rx = " << aabb[i].rx << std::endl;
      std::cout << "aabb["<<i<<"].ry = " << aabb[i].ry << std::endl;
      std::cout << "aabb["<<i<<"].rz = " << aabb[i].rz << std::endl;
    }
  return 0;
}


extern "C"
{
 
  void RightSeedArmMotionPlanningInit(RTC::Manager* manager)
  {
    coil::Properties profile(rightseedarmmotionplanning_spec);
    manager->registerFactory(profile,
                             RTC::Create<RightSeedArmMotionPlanning>,
                             RTC::Delete<RightSeedArmMotionPlanning>);
  }
  
};


