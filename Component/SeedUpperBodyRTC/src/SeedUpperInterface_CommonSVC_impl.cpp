// -*-C++-*-
/*!
 * @file  SeedUpperInterface_CommonSVC_impl.cpp
 * @brief Service implementation code of SeedUpperInterface_Common.idl
 *
 */

#include "SeedUpperInterface_CommonSVC_impl.h"
#include "seedUpper_ReturnID.h"
/*
 * Example implementational code for IDL interface SEED_UPPER::SeedUpperInterface_Common
 */
SEED_UPPER_SeedUpperInterface_CommonSVC_impl::SEED_UPPER_SeedUpperInterface_CommonSVC_impl()
{
  // Please add extra constructor code here.
}


SEED_UPPER_SeedUpperInterface_CommonSVC_impl::~SEED_UPPER_SeedUpperInterface_CommonSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_CommonSVC_impl::getFeedbackPosAllJoint(SEED_UPPER::Lifter& lifterPos, SEED_UPPER::RPY& WaistPos, SEED_UPPER::RPY& NeckPos, SEED_UPPER::JointPos_out rightPos, SEED_UPPER::JointPos_out leftPos)
{
  std::cout << "getFeedbackPosAllJoint" << std::endl;

  Frame nowWaistPos;
  Frame nowNeckPos;
  double nowLifterPos[2];
  double nowRightJointPos[7];
  double nowLeftJointPos[7];
  rightPos = new SEED_UPPER::JointPos;
  rightPos->length(7);
  leftPos = new SEED_UPPER::JointPos;
  leftPos->length(7);

  m_rtcPtr->getLifterPos(nowLifterPos);
  m_rtcPtr->readAllJointAngle(&nowWaistPos,&nowNeckPos,nowRightJointPos,nowLeftJointPos);

  lifterPos.bottom = nowLifterPos[0];
  lifterPos.top = nowLifterPos[1];
  WaistPos.yaw = nowWaistPos.yaw;
  WaistPos.pitch = nowWaistPos.pitch;
  WaistPos.roll = nowWaistPos.roll;
  NeckPos.yaw = nowNeckPos.yaw;
  NeckPos.pitch = nowNeckPos.pitch;
  NeckPos.roll = nowNeckPos.roll;

  for (int i = 0; i<7; i++)
    {
      (*rightPos)[i] = nowRightJointPos[i];
      //std::cout << "nowRightpos[" << i << "] = " << (*pos)[i] << "[°]" << std::endl;
    }

  for (int i = 0; i<7; i++)
    {
      (*leftPos)[i] = nowLeftJointPos[i];
      //std::cout << "nowLeftpos[" << i << "] = " << (*pos)[i] << "[°]" << std::endl;
    }
  
  std::cout << "Success" << std::endl << std::endl;

  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_CommonSVC_impl::getFeedbackPosLIWARArm(SEED_UPPER::JointPos_out pos)
{
  std::cout << "getFeedbackPosLIWARArm" << std::endl;
  
  Frame nowWaistPos;
  Frame nowNeckPos;
  double nowLifterPos[2];
  double nowRightJointPos[7];
  double nowLeftJointPos[7];
  pos = new SEED_UPPER::JointPos;
  pos->length(12);

  m_rtcPtr->getLifterPos(nowLifterPos);
  m_rtcPtr->readAllJointAngle(&nowWaistPos,&nowNeckPos,nowRightJointPos,nowLeftJointPos);

  (*pos)[0] = nowLifterPos[0];
  (*pos)[1] = nowLifterPos[1];
  (*pos)[2] = nowWaistPos.yaw;
  (*pos)[3] = nowWaistPos.pitch;
  (*pos)[4] = nowWaistPos.roll;
  for (int i = 0; i<7; i++)
    {
      (*pos)[i+5] = nowRightJointPos[i];
      //std::cout << "nowRightpos[" << i << "] = " << (*pos)[i] << "[°]" << std::endl;
    }
  
  std::cout << "Success" << std::endl << std::endl;

  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_CommonSVC_impl::getFeedbackPosLIWALArm(SEED_UPPER::JointPos_out pos)
{
  std::cout << "getFeedbackPosLIWALArm" << std::endl;
  
  Frame nowWaistPos;
  Frame nowNeckPos;
  double nowLifterPos[2];
  double nowRightJointPos[7];
  double nowLeftJointPos[7];
  pos = new SEED_UPPER::JointPos;
  pos->length(12);

  m_rtcPtr->getLifterPos(nowLifterPos);
  m_rtcPtr->readAllJointAngle(&nowWaistPos,&nowNeckPos,nowRightJointPos,nowLeftJointPos);

  (*pos)[0] = nowLifterPos[0];
  (*pos)[1] = nowLifterPos[1];
  (*pos)[2] = nowWaistPos.yaw;
  (*pos)[3] = nowWaistPos.pitch;
  (*pos)[4] = nowWaistPos.roll;
  for (int i = 0; i<7; i++)
    {
      (*pos)[i+5] = nowLeftJointPos[i];
      //std::cout << "nowLeftpos[" << i << "] = " << (*pos)[i] << "[°]" << std::endl;
    }
  
  std::cout << "Success" << std::endl << std::endl;

  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_CommonSVC_impl::getManipInfo(SEED_UPPER::ManipInfo_out mInfo)
{
  std::cout << "getManipInfo" << std::endl;
  
  mInfo = new SEED_UPPER::ManipInfo;
  mInfo->manufactur = "Hardware：(株)THK  Software：Meijo University robot systems design laboratory";
  mInfo->type = "SeedNoid";
  mInfo->cmdCycle = 20;
  mInfo->axisNum = 22;
  
  std::cout << " manufactur : " << mInfo->manufactur << std::endl;
  std::cout << " type       : " << mInfo->type << std::endl;
  std::cout << " axisNum    : " << mInfo->axisNum << std::endl;
  std::cout << " cmdCycle   : " << mInfo->cmdCycle << std::endl;

  std::cout << "Success" << std::endl << std::endl;
  
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_CommonSVC_impl::getLIWARArmInfo(SEED_UPPER::ManipInfo_out mInfo)
{
  std::cout << "getLIWARArmInfo" << std::endl;
  
  mInfo = new SEED_UPPER::ManipInfo;
  mInfo->manufactur = "Hardware：(株)THK  Software：Meijo University robot systems design laboratory";
  mInfo->type = "Seed_LifterWaistRightArm";
  mInfo->cmdCycle = 20;
  mInfo->axisNum = 12;
  mInfo->isGripper = true;

  
  std::cout << " manufactur : " << mInfo->manufactur << std::endl;
  std::cout << " type       : " << mInfo->type << std::endl;
  std::cout << " axisNum    : " << mInfo->axisNum << std::endl;
  std::cout << " cmdCycle   : " << mInfo->cmdCycle << std::endl;
  std::cout << " isGripper  : " << mInfo->isGripper << std::endl;

  std::cout << "Success" << std::endl << std::endl;
  
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_CommonSVC_impl::getLIWALArmInfo(SEED_UPPER::ManipInfo_out mInfo)
{
  std::cout << "getLIWALArmInfo" << std::endl;
  
  mInfo = new SEED_UPPER::ManipInfo;
  mInfo->manufactur = "Hardware：(株)THK  Software：Meijo University robot systems design laboratory";
  mInfo->type = "Seed_WaistRightArm";
  mInfo->cmdCycle = 20;
  mInfo->axisNum = 12;
  mInfo->isGripper = true;

  std::cout << " manufactur : " << mInfo->manufactur << std::endl;
  std::cout << " type       : " << mInfo->type << std::endl;
  std::cout << " axisNum    : " << mInfo->axisNum << std::endl;
  std::cout << " cmdCycle   : " << mInfo->cmdCycle << std::endl;
  std::cout << " isGripper  : " << mInfo->isGripper << std::endl;

  std::cout << "Success" << std::endl << std::endl;
  
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_CommonSVC_impl::getSoftLimitJoint(SEED_UPPER::LimitSeq_out softLimit)
{
  std::cout<<"getSoftLimitJoint"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_CommonSVC_impl::getState(SEED_UPPER::ULONG& state)
{
  std::cout<<"getState"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_CommonSVC_impl::servoOFF()
{
  std::cout << "ServoOFF (SERVO_OFF)" << std::endl;
  
  m_rtcPtr->ServoOFF();
  
  std::cout << "Success" << std::endl << std::endl;
  
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_CommonSVC_impl::servoON()
{
  std::cout << "ServoON (SERVO_ON)" << std::endl;
  
  m_rtcPtr->ServoON();
  
  std::cout << "Success" << std::endl << std::endl;
  
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_CommonSVC_impl::setSoftLimitJoint(const SEED_UPPER::LimitSeq& softLimit)
{
  std::cout<<"setSoftLimitJoint"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}


// End of example implementational code



