// -*-C++-*-
/*!
 * @file  SeedUpperInterface_MiddleLevelSVC_impl.cpp
 * @brief Service implementation code of SeedUpperInterface_MiddleLevel.idl
 *
 */

#include "SeedUpperInterface_MiddleLevelSVC_impl.h"
#include "seedUpper_ReturnID.h"

/*
 * Example implementational code for IDL interface SEED_UPPER::SeedUpperInterface_Middle
 */
SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::SEED_UPPER_SeedUpperInterface_MiddleSVC_impl()
{
  // Please add extra constructor code here.
  m_SeedUpperInterface_Common.getManipInfo(mInfovar);
  mInfo = mInfovar;
  m_speedRatioCartesian = 50;
  m_speedRatioJoint = 25;
  m_maxSpeedJoint.length(20);
  for(unsigned int i=0;i<20;i++){
    m_maxSpeedJoint[i] = 60;//deg/s
  }
}


SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::~SEED_UPPER_SeedUpperInterface_MiddleSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::closeRightGripper()
{
  std::cout << "closeRightGripper" << std::endl;
  m_rtcPtr->CloseRightGripper();
  std::cout << "Success" << std::endl << std::endl;
  
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::openRightGripper()
{
  std::cout << "openRightGripper" << std::endl;
  m_rtcPtr->OpenRightGripper();
  std::cout << "Success" << std::endl << std::endl;
  
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::moveRightGripper(SEED_UPPER::ULONG angleRatio)
{
  std::cout << "moveRightGripper" << std::endl;
  double move;
  
  move = (double)angleRatio;
  
  if (angleRatio>0 && angleRatio <= 100){
    m_rtcPtr->MoveRightGripper(move);
  }
  else{
    std::cout << "ERROR : angleRatio Wrong Value" << std::endl;
    RETURNID_VALUE_ERR;
  }
  std::cout << "Success" << std::endl << std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::closeLeftGripper()
{
  std::cout << "closeLeftGripper" << std::endl;
  m_rtcPtr->CloseLeftGripper();
  std::cout << "Success" << std::endl << std::endl;
  
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::openLeftGripper()
{
  std::cout << "openLeftGripper" << std::endl;
  m_rtcPtr->OpenLeftGripper();
  std::cout << "Success" << std::endl << std::endl;
  
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::moveLeftGripper(SEED_UPPER::ULONG angleRatio)
{
  std::cout << "moveLeftGripper" << std::endl;
  double move;
  
  move = (double)angleRatio;
  
  if (angleRatio>0 && angleRatio <= 100){
    m_rtcPtr->MoveLeftGripper(move);
  }
  else{
    std::cout << "ERROR : angleRatio Wrong Value" << std::endl;
    RETURNID_VALUE_ERR;
  }
  std::cout << "Success" << std::endl << std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::setRightGraspForce(SEED_UPPER::ULONG forceRatio)
{
  std::cout<<"setRightGraspForce"<<std::endl;
  int ratio = (int)forceRatio;
  m_forceRatio = forceRatio;
  m_rtcPtr->setRightHandCurrent(ratio);
  std::cout<<"Success"<<std::endl<<std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::getRightGraspForce(SEED_UPPER::ULONG& forceRatio)
{
  std::cout<<"getGraspForce"<<std::endl;
  forceRatio = m_forceRatio;
  std::cout<<"Success"<<std::endl<<std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::setLeftGraspForce(SEED_UPPER::ULONG forceRatio)
{
  std::cout<<"setLeftGraspForce"<<std::endl;
  int ratio = (int)forceRatio;
  m_forceRatio = forceRatio;
  m_rtcPtr->setLeftHandCurrent(ratio);
  std::cout<<"Success"<<std::endl<<std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::getLeftGraspForce(SEED_UPPER::ULONG& forceRatio)
{
  std::cout<<"getLeftGraspForce"<<std::endl;
  forceRatio = m_forceRatio;
  std::cout<<"Success"<<std::endl<<std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::getFeedbackPosLIWARCartesian(SEED_UPPER::CarPosWithLifterWaistElbow& pos)
{
  std::cout<<"getFeedbackPosLIWARCartesian"<<std::endl;
  Frame nowWaistPos;
  Frame nowNeckPos;
  double nowLifterPos[2];
  double nowRightJointPos[7];
  double nowLeftJointPos[7];

  m_rtcPtr->getLifterPos(nowLifterPos);
  m_rtcPtr->readAllJointAngle(&nowWaistPos,&nowNeckPos,nowRightJointPos,nowLeftJointPos);

  double joint[12];
  joint[0] = nowLifterPos[0];
  joint[1] = nowLifterPos[1];
  joint[2] = nowWaistPos.yaw;
  joint[3] = nowWaistPos.pitch;
  joint[4] = nowWaistPos.roll;
  for(int i=0;i<7;i++)
    {
      joint[i+5] = nowRightJointPos[i];
    }

  double eerot[9];
  double eetrans[3];
  m_rtcPtr->Solve_LIWARArmFk(eerot,eetrans,joint);

  pos.carPos[0][0] = eerot[0];
  pos.carPos[0][1] = eerot[1];
  pos.carPos[0][2] = eerot[2];
  
  pos.carPos[1][0] = eerot[3];
  pos.carPos[1][1] = eerot[4];
  pos.carPos[1][2] = eerot[5];

  pos.carPos[2][0] = eerot[6];
  pos.carPos[2][1] = eerot[7];
  pos.carPos[2][2] = eerot[8];

  pos.carPos[0][3] = eetrans[0];
  pos.carPos[1][3] = eetrans[1];
  pos.carPos[2][3] = eetrans[2];

  std::cout<<"Success"<<std::endl<<std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::getFeedbackPosLIWALCartesian(SEED_UPPER::CarPosWithLifterWaistElbow& pos)
{
  std::cout<<"getFeedbackPosLIWALCartesian"<<std::endl;
  Frame nowWaistPos;
  Frame nowNeckPos;
  double nowLifterPos[2];
  double nowRightJointPos[7];
  double nowLeftJointPos[7];

  m_rtcPtr->getLifterPos(nowLifterPos);
  m_rtcPtr->readAllJointAngle(&nowWaistPos,&nowNeckPos,nowRightJointPos,nowLeftJointPos);

  double joint[12];
  joint[0] = nowLifterPos[0];
  joint[1] = nowLifterPos[1];
  joint[2] = nowWaistPos.yaw;
  joint[3] = nowWaistPos.pitch;
  joint[4] = nowWaistPos.roll;
  for(int i=0;i<7;i++)
    {
      joint[i+5] = nowLeftJointPos[i];
    }

  double eerot[9];
  double eetrans[3];
  m_rtcPtr->Solve_LIWALArmFk(eerot,eetrans,joint);

  pos.carPos[0][0] = eerot[0];
  pos.carPos[0][1] = eerot[1];
  pos.carPos[0][2] = eerot[2];
  
  pos.carPos[1][0] = eerot[3];
  pos.carPos[1][1] = eerot[4];
  pos.carPos[1][2] = eerot[5];

  pos.carPos[2][0] = eerot[6];
  pos.carPos[2][1] = eerot[7];
  pos.carPos[2][2] = eerot[8];

  pos.carPos[0][3] = eetrans[0];
  pos.carPos[1][3] = eetrans[1];
  pos.carPos[2][3] = eetrans[2];

  std::cout<<"Success"<<std::endl<<std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::setMaxSpeedCartesian(const SEED_UPPER::CartesianSpeed& speed)
{
  std::cout<<"setMaxSpeedCartesian"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::setMaxSpeedJoint(const SEED_UPPER::DoubleSeq& speed)
{
  std::cout<<"setMaxSpeedJoint"<<std::endl;
  
  m_maxSpeedJointFlag = true;

  for(unsigned int i=0;i<20;i++){
    m_maxSpeedJoint[i] = speed[i];
  }

  std::cout << "Success" << std::endl << std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::getMaxSpeedCartesian(SEED_UPPER::CartesianSpeed& speed)
{
  std::cout<<"getMaxSpeedCartesian"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::getMaxSpeedJoint(SEED_UPPER::DoubleSeq_out speed)
{
  std::cout<<"getMaxSpeedJoint"<<std::endl;
  speed = new SEED_UPPER::DoubleSeq;
  speed->length(20);
  for(unsigned int i=0;i<20;i++){
    speed[i] = m_maxSpeedJoint[i];
  }
  std::cout << "Success" << std::endl << std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::setSpeedCartesian(SEED_UPPER::ULONG spdRatio)
{
  std::cout<<"setSpeedCartesian"<<std::endl;
  
  if(spdRatio >= 0 && spdRatio <= 100){
    m_speedRatioCartesian = spdRatio;
  }else{
    std::cout<<"ERROR : Wrong Value"<<std::endl<<std::endl;
    RETURNID_VALUE_ERR;
  }
  
  std::cout<<"Success"<<std::endl<<std::endl;
  
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::setSpeedJoint(SEED_UPPER::ULONG spdRatio)
{
  std::cout<<"setSpeedJoint"<<std::endl;
  
  if(spdRatio >= 0 && spdRatio <= 100){
    m_speedRatioJoint = spdRatio;
  }
  else{
    std::cout<<"ERROR : Wrong Value"<<std::endl<<std::endl;
    RETURNID_VALUE_ERR;
  }
  
  std::cout<<"Success"<<std::endl<<std::endl;
  
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::getSpeedCartesian(SEED_UPPER::ULONG& spdRatio)
{
  std::cout<<"getSpeedCartesian"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::getSpeedJoint(SEED_UPPER::ULONG& spdRatio)
{
  std::cout<<"getSpeedJoint"<<std::endl;
  spdRatio = m_speedRatioJoint;
  std::cout<<"Success"<<std::endl<<std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::setSoftLimitCartesian(const SEED_UPPER::LimitValue& xLimit, const SEED_UPPER::LimitValue& yLimit, const SEED_UPPER::LimitValue& zLimit)
{
  std::cout<<"setSoftLimitCartesian"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::getSoftLimitCartesian(SEED_UPPER::LimitValue& xLimit, SEED_UPPER::LimitValue& yLimit, SEED_UPPER::LimitValue& zLimit)
{
  std::cout<<"getSoftLimitCartesian"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::moveLinearLIWARArmCartesianAbsSetRedunJoint(const SEED_UPPER::CarPosWithLifterWaistElbow& carPoint)
{
  std::cout<<"moveLinearLIWARArmCartesianAbsSetRedunJoint"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::moveLinearLIWARArmCartesianRelSetRedunJoint(const SEED_UPPER::CarPosWithLifterWaistElbow& carPoint)
{
  std::cout<<"moveLinearLIWARArmCartesianRelSetRedunJoint"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::movePTPLIWARArmCartesianAbsSetRedunJoint(const SEED_UPPER::CarPosWithLifterWaistElbow& carPoint)
{
  std::cout<<"movePTPLIWARArmCartesianAbsSetRedunJoint"<<std::endl;
  
  double eerot[9];//姿勢
  double eetrans[3];//座標
  double iksol[12];
  double elbow;
  double targetLifterPos[2];
  double nowJointPos[12];
  double rotationLength[12];
  double maxMoveJoint;
  double maxMoveJointNumber;
  int movetime;
  Frame targetWaistPos;
  double targetRightJointPos[7];
  
  Frame nowWaistPos;
  Frame nowNeckPos;
  double nowLifterPos[2];
  double nowRightJointPos[7];
  double nowLeftJointPos[7];

  m_rtcPtr->getLifterPos(nowLifterPos);
  m_rtcPtr->readAllJointAngle(&nowWaistPos,&nowNeckPos,nowRightJointPos,nowLeftJointPos);
  
  //姿勢の入力
  eerot[0]=carPoint.carPos[0][0];
  eerot[1]=carPoint.carPos[0][1];
  eerot[2]=carPoint.carPos[0][2];
  
  eerot[3]=carPoint.carPos[1][0];
  eerot[4]=carPoint.carPos[1][1];
  eerot[5]=carPoint.carPos[1][2];
  
  eerot[6]=carPoint.carPos[2][0];
  eerot[7]=carPoint.carPos[2][1];
  eerot[8]=carPoint.carPos[2][2];

  for(int j=0;j<9;j++){
    printf("eerot[%d] = %f\n",j,eerot[j]);
  }

  //座標の入力 関数への入力は[mm]だがikfastは[m]のため変換
  eetrans[0]=carPoint.carPos[0][3];
  eetrans[1]=carPoint.carPos[1][3];
  eetrans[2]=carPoint.carPos[2][3];

  for(int i=0;i<3;i++){
    printf("eetrans[%d] = %f\n",i,eetrans[i]);
  }

  nowJointPos[0] = nowLifterPos[0];
  nowJointPos[1] = nowLifterPos[1];
  nowJointPos[2] = nowWaistPos.yaw;
  nowJointPos[3] = nowWaistPos.pitch;
  nowJointPos[4] = nowWaistPos.roll;
  
  for(int d=0;d<7;d++)
    {
      nowJointPos[d+5] = nowRightJointPos[d];
    }

  elbow = carPoint.elbow;
  targetLifterPos[0] = carPoint.LifterPos.bottom;
  targetLifterPos[1] = carPoint.LifterPos.top;
  targetWaistPos.yaw = carPoint.waistPos.yaw;
  targetWaistPos.pitch = carPoint.waistPos.pitch;
  targetWaistPos.roll = carPoint.waistPos.roll;
  
  int ret = m_rtcPtr->Solve_LIWARArmIkSetRedun(eerot,eetrans,elbow,targetWaistPos,targetLifterPos,nowJointPos,iksol);
  if(!ret)
    {
      //現在値と目標値で最も離れている関節がm_maxSpeedJointになるように計算
      rotationLength[0] = fabs(iksol[0]-nowLifterPos[0]);
      rotationLength[1] = fabs(iksol[1]-nowLifterPos[1]);
      rotationLength[2] = fabs(iksol[2]-nowWaistPos.yaw);
      rotationLength[3] = fabs(iksol[3]-nowWaistPos.pitch);
      rotationLength[4] = fabs(iksol[4]-nowWaistPos.roll);
      for(int k=0;k<7;k++)
	{
	  rotationLength[k+5] = fabs(iksol[k+5]-nowRightJointPos[k]);
	}
      maxMoveJoint = rotationLength[0];
      maxMoveJointNumber = 0;
      for(int j=0;j<10;j++)
	{
	  if(maxMoveJoint<rotationLength[j+1]){
	    maxMoveJoint = rotationLength[j+1];
	    maxMoveJointNumber = j+1;
	  }
	}
      movetime = ((maxMoveJoint/m_maxSpeedJoint[maxMoveJointNumber])*1000)*(100/(double)m_speedRatioJoint);
      
      for(int d=0;d<7;d++)
	{
	  targetRightJointPos[d] = iksol[d+5];
	}
      m_rtcPtr->setWaistJointAngle(targetWaistPos);
      m_rtcPtr->setRightJointAngle(targetRightJointPos);
      m_rtcPtr->movePTPLifter(targetLifterPos);
      m_rtcPtr->SeedAction(movetime);
    }
  else
    RETURNID_NG;
  
  std::cout << "Success" <<std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::movePTPLIWARArmCartesianRelSetRedunJoint(const SEED_UPPER::CarPosWithLifterWaistElbow& carPoint)
{
  std::cout<<"movePTPLIWARArmCartesianRelSetRedunJoint"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::moveLinearLIWARArmCartesianAbs(const SEED_UPPER::EEPos& carPoint)
{
  std::cout<<"moveLinearLIWARArmCartesianAbs"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::moveLinearLIWARArmCartesianRel(const SEED_UPPER::EEPos& carPoint)
{
  std::cout<<"moveLinearLIWARArmCartesianRel"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::movePTPLIWARArmCartesianAbs(const SEED_UPPER::EEPos& carPoint)
{
  std::cout<<"movePTPLIWARArmCartesianAbs"<<std::endl;
  
  double eerot[9];//姿勢
  double eetrans[3];//座標
  double iksol[12];
  double targetLifterPos[2];
  double nowJointPos[12];
  double rotationLength[12];
  double maxMoveJoint;
  double maxMoveJointNumber;
  int movetime;
  Frame targetWaistPos;
  double targetRightJointPos[7];
  
  Frame nowWaistPos;
  Frame nowNeckPos;
  double nowLifterPos[2];
  double nowRightJointPos[7];
  double nowLeftJointPos[7];

  m_rtcPtr->getLifterPos(nowLifterPos);
  m_rtcPtr->readAllJointAngle(&nowWaistPos,&nowNeckPos,nowRightJointPos,nowLeftJointPos);
  
  //姿勢の入力
  eerot[0]=carPoint.carPos[0][0];
  eerot[1]=carPoint.carPos[0][1];
  eerot[2]=carPoint.carPos[0][2];
  
  eerot[3]=carPoint.carPos[1][0];
  eerot[4]=carPoint.carPos[1][1];
  eerot[5]=carPoint.carPos[1][2];
  
  eerot[6]=carPoint.carPos[2][0];
  eerot[7]=carPoint.carPos[2][1];
  eerot[8]=carPoint.carPos[2][2];

  for(int j=0;j<9;j++){
    printf("eerot[%d] = %f\n",j,eerot[j]);
  }

  //座標の入力 関数への入力は[mm]だがikfastは[m]のため変換
  eetrans[0]=carPoint.carPos[0][3];
  eetrans[1]=carPoint.carPos[1][3];
  eetrans[2]=carPoint.carPos[2][3];

  for(int i=0;i<3;i++){
    printf("eetrans[%d] = %f\n",i,eetrans[i]);
  }

  nowJointPos[0] = nowLifterPos[0];
  nowJointPos[1] = nowLifterPos[1];
  nowJointPos[2] = nowWaistPos.yaw;
  nowJointPos[3] = nowWaistPos.pitch;
  nowJointPos[4] = nowWaistPos.roll;
  
  for(int d=0;d<7;d++)
    {
      nowJointPos[d+5] = nowRightJointPos[d];
    }
  
  int ret = m_rtcPtr->Solve_LIWARArmIk(eerot,eetrans,nowJointPos,iksol);
  if(!ret)
    {

      //現在値と目標値で最も離れている関節がm_maxSpeedJointになるように計算
      rotationLength[0] = fabs(iksol[0]-nowLifterPos[0]);
      rotationLength[1] = fabs(iksol[1]-nowLifterPos[1]);
      rotationLength[2] = fabs(iksol[2]-nowWaistPos.yaw);
      rotationLength[3] = fabs(iksol[3]-nowWaistPos.pitch);
      rotationLength[4] = fabs(iksol[4]-nowWaistPos.roll);
      for(int k=0;k<7;k++)
	{
	  rotationLength[k+5] = fabs(iksol[k+5]-nowRightJointPos[k]);
	}

      maxMoveJoint = rotationLength[0];
      maxMoveJointNumber = 0;
      for(int j=0;j<10;j++)
	{
	  if(maxMoveJoint<rotationLength[j+1]){
	    maxMoveJoint = rotationLength[j+1];
	    maxMoveJointNumber = j+1;
	  }
	}
      movetime = ((maxMoveJoint/m_maxSpeedJoint[maxMoveJointNumber])*1000)*(100/(double)m_speedRatioJoint);
      //std::cout << "movetime = " <<movetime<< std::endl;
      
      targetLifterPos[0] = iksol[0];
      targetLifterPos[1] = iksol[1];
      targetWaistPos.yaw = iksol[2];
      targetWaistPos.pitch = iksol[3];
      targetWaistPos.roll = iksol[4];
      for(int d=0;d<7;d++)
	{
	  targetRightJointPos[d] = iksol[d+5];
	}
      m_rtcPtr->setWaistJointAngle(targetWaistPos);
      m_rtcPtr->setRightJointAngle(targetRightJointPos);
      m_rtcPtr->movePTPLifter(targetLifterPos);
      m_rtcPtr->SeedAction(movetime);
    }
  else
    RETURNID_NG;
  
  std::cout << "Success" <<std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::movePTPLIWARArmCartesianRel(const SEED_UPPER::EEPos& carPoint)
{
  std::cout<<"moveLinearLIWARArmCartesianRel"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::movePTPLIWARArmJointAbs(const SEED_UPPER::JointPos& jointPoint)
{
  std::cout<<"movePTPLIWARArmJointAbs"<<std::endl;
  
  double targetLifterPos[2];
  double rotationLength[12];
  double maxMoveJoint;
  double maxMoveJointNumber;
  int movetime;
  Frame targetWaistPos;
  double targetRightJointPos[7];
  
  Frame nowWaistPos;
  Frame nowNeckPos;
  double nowLifterPos[2];
  double nowRightJointPos[7];
  double nowLeftJointPos[7];

  m_rtcPtr->getLifterPos(nowLifterPos);
  m_rtcPtr->readAllJointAngle(&nowWaistPos,&nowNeckPos,nowRightJointPos,nowLeftJointPos);
  
  targetLifterPos[0] = (double)jointPoint[0];
  targetLifterPos[1] = (double)jointPoint[1];
  targetWaistPos.yaw = (double)jointPoint[2];
  targetWaistPos.pitch = (double)jointPoint[3];
  targetWaistPos.roll = (double)jointPoint[4];
  for(int i=0;i<7;i++)
    {
      targetRightJointPos[i] = jointPoint[i+5];
    }
  
  //現在値と目標値で最も離れている関節がm_maxSpeedJointになるように計算
  rotationLength[0] = fabs(targetLifterPos[0]-nowLifterPos[0]);
  rotationLength[1] = fabs(targetLifterPos[1]-nowLifterPos[1]);
  rotationLength[2] = fabs(targetWaistPos.yaw-nowWaistPos.yaw);
  rotationLength[3] = fabs(targetWaistPos.pitch-nowWaistPos.pitch);
  rotationLength[4] = fabs(targetWaistPos.roll-nowWaistPos.roll);
  for(int k=0;k<7;k++)
    {
      rotationLength[k+5] = fabs(targetRightJointPos[k]-nowRightJointPos[k]);
    }
  
  maxMoveJoint = rotationLength[0];
  maxMoveJointNumber = 0;
  for(int j=0;j<10;j++)
    {
      if(maxMoveJoint<rotationLength[j+1]){
	maxMoveJoint = rotationLength[j+1];
	maxMoveJointNumber = j+1;
      }
    }
  movetime = ((maxMoveJoint/m_maxSpeedJoint[maxMoveJointNumber])*1000)*(100/(double)m_speedRatioJoint);
  //std::cout << "movetime = " << movetime << std::endl; 
  m_rtcPtr->setWaistJointAngle(targetWaistPos);
  m_rtcPtr->setRightJointAngle(targetRightJointPos);
  m_rtcPtr->movePTPLifter(targetLifterPos);
  m_rtcPtr->SeedAction(movetime);

  
  std::cout << "Success" <<std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::movePTPLIWARArmJointRel(const SEED_UPPER::JointPos& jointPoint)
{
  std::cout<<"movePTPLIWARArmJointRel"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::moveLinearLIWALArmCartesianAbsSetRedunJoint(const SEED_UPPER::CarPosWithLifterWaistElbow& carPoint)
{
  std::cout<<"moveLinearLIWALArmCartesianAbsSetRedunJoint"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::moveLinearLIWALArmCartesianRelSetRedunJoint(const SEED_UPPER::CarPosWithLifterWaistElbow& carPoint)
{
  std::cout<<"moveLinearLIWALArmCartesianRelSetRedunJoint"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::movePTPLIWALArmCartesianAbsSetRedunJoint(const SEED_UPPER::CarPosWithLifterWaistElbow& carPoint)
{
  std::cout<<"movePTPLIWALArmCartesianAbsSetRedunJoint"<<std::endl;
  
  double eerot[9];//姿勢
  double eetrans[3];//座標
  double iksol[12];
  double elbow;
  double lifter[2];
  double nowJointPos[12];
  double rotationLength[12];
  double maxMoveJoint;
  double maxMoveJointNumber;
  int movetime;
  Frame WaistPos;
  double setLeftJointPos[7];
  
  Frame nowWaistPos;
  Frame nowNeckPos;
  double nowLifterPos[2];
  double nowRightJointPos[7];
  double nowLeftJointPos[7];

  m_rtcPtr->getLifterPos(nowLifterPos);
  m_rtcPtr->readAllJointAngle(&nowWaistPos,&nowNeckPos,nowRightJointPos,nowLeftJointPos);
  
  //姿勢の入力
  eerot[0]=carPoint.carPos[0][0];
  eerot[1]=carPoint.carPos[0][1];
  eerot[2]=carPoint.carPos[0][2];
  
  eerot[3]=carPoint.carPos[1][0];
  eerot[4]=carPoint.carPos[1][1];
  eerot[5]=carPoint.carPos[1][2];
  
  eerot[6]=carPoint.carPos[2][0];
  eerot[7]=carPoint.carPos[2][1];
  eerot[8]=carPoint.carPos[2][2];

  for(int j=0;j<9;j++){
    printf("eerot[%d] = %f\n",j,eerot[j]);
  }

  //座標の入力 関数への入力は[mm]だがikfastは[m]のため変換
  eetrans[0]=carPoint.carPos[0][3];
  eetrans[1]=carPoint.carPos[1][3];
  eetrans[2]=carPoint.carPos[2][3];

  for(int i=0;i<3;i++){
    printf("eetrans[%d] = %f\n",i,eetrans[i]);
  }

  nowJointPos[0] = nowLifterPos[0];
  nowJointPos[1] = nowLifterPos[1];
  nowJointPos[2] = nowWaistPos.yaw;
  nowJointPos[3] = nowWaistPos.pitch;
  nowJointPos[4] = nowWaistPos.roll;
  
  for(int d=0;d<7;d++)
    {
      nowJointPos[d+5] = nowLeftJointPos[d];
    }

  elbow = carPoint.elbow;
  lifter[0] = carPoint.LifterPos.bottom;
  lifter[1] = carPoint.LifterPos.top;
  WaistPos.yaw = carPoint.waistPos.yaw;
  WaistPos.pitch = carPoint.waistPos.pitch;
  WaistPos.roll = carPoint.waistPos.roll;
  
  int ret = m_rtcPtr->Solve_LIWALArmIkSetRedun(eerot,eetrans,elbow,WaistPos,lifter, nowJointPos,iksol);
  if(!ret)
    {
      //現在値と目標値で最も離れている関節がm_maxSpeedJointになるように計算
      rotationLength[0] = fabs(iksol[0]-nowLifterPos[0]);
      rotationLength[1] = fabs(iksol[1]-nowLifterPos[1]);
      rotationLength[2] = fabs(iksol[2]-nowWaistPos.yaw);
      rotationLength[3] = fabs(iksol[3]-nowWaistPos.pitch);
      rotationLength[4] = fabs(iksol[4]-nowWaistPos.roll);
      for(int k=0;k<7;k++)
	{
	  rotationLength[k+5] = fabs(iksol[k+5]-nowLeftJointPos[k]);
	}
      maxMoveJoint = rotationLength[0];
      maxMoveJointNumber = 0;
      for(int j=0;j<10;j++)
	{
	  if(maxMoveJoint<rotationLength[j+1]){
	    maxMoveJoint = rotationLength[j+1];
	    maxMoveJointNumber = j+1;
	  }
	}
      movetime = ((maxMoveJoint/m_maxSpeedJoint[maxMoveJointNumber])*1000)*(100/(double)m_speedRatioJoint);

      for(int d=0;d<7;d++)
	{
	  setLeftJointPos[d] = iksol[d+5];
	}
      m_rtcPtr->setWaistJointAngle(WaistPos);
      m_rtcPtr->setLeftJointAngle(setLeftJointPos);
      m_rtcPtr->movePTPLifter(lifter);
      m_rtcPtr->SeedAction(movetime);
    }
  else
    RETURNID_NG;
  
  std::cout << "Success" <<std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::movePTPLIWALArmCartesianRelSetRedunJoint(const SEED_UPPER::CarPosWithLifterWaistElbow& carPoint)
{
  std::cout<<"movePTPLIWALArmCartesianRelSetRedunJoint"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::moveLinearLIWALArmCartesianAbs(const SEED_UPPER::EEPos& carPoint)
{
  std::cout<<"moveLinearLIWALArmCartesianAbs"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::moveLinearLIWALArmCartesianRel(const SEED_UPPER::EEPos& carPoint)
{
  std::cout<<"moveLinearLIWALArmCartesianRel"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::movePTPLIWALArmCartesianAbs(const SEED_UPPER::EEPos& carPoint)
{
  std::cout<<"movePTPLIWALArmCartesianAbs"<<std::endl;
  
  double eerot[9];//姿勢
  double eetrans[3];//座標
  double iksol[12];
  double targetLifterPos[2];
  double nowJointPos[12];
  double rotationLength[12];
  double maxMoveJoint;
  double maxMoveJointNumber;
  int movetime;
  Frame targetWaistPos;
  double targetRightJointPos[7];
  
  Frame nowWaistPos;
  Frame nowNeckPos;
  double nowLifterPos[2];
  double nowRightJointPos[7];
  double nowLeftJointPos[7];

  m_rtcPtr->getLifterPos(nowLifterPos);
  m_rtcPtr->readAllJointAngle(&nowWaistPos,&nowNeckPos,nowRightJointPos,nowLeftJointPos);
  
  //姿勢の入力
  eerot[0]=carPoint.carPos[0][0];
  eerot[1]=carPoint.carPos[0][1];
  eerot[2]=carPoint.carPos[0][2];
  
  eerot[3]=carPoint.carPos[1][0];
  eerot[4]=carPoint.carPos[1][1];
  eerot[5]=carPoint.carPos[1][2];
  
  eerot[6]=carPoint.carPos[2][0];
  eerot[7]=carPoint.carPos[2][1];
  eerot[8]=carPoint.carPos[2][2];

  for(int j=0;j<9;j++){
    printf("eerot[%d] = %f\n",j,eerot[j]);
  }

  //座標の入力 関数への入力は[mm]だがikfastは[m]のため変換
  eetrans[0]=carPoint.carPos[0][3];
  eetrans[1]=carPoint.carPos[1][3];
  eetrans[2]=carPoint.carPos[2][3];

  for(int i=0;i<3;i++){
    printf("eetrans[%d] = %f\n",i,eetrans[i]);
  }

  nowJointPos[0] = nowLifterPos[0];
  nowJointPos[1] = nowLifterPos[1];
  nowJointPos[2] = nowWaistPos.yaw;
  nowJointPos[3] = nowWaistPos.pitch;
  nowJointPos[4] = nowWaistPos.roll;
  
  for(int d=0;d<7;d++)
    {
      nowJointPos[d+5] = nowRightJointPos[d];
    }
  
  int ret = m_rtcPtr->Solve_LIWALArmIk(eerot,eetrans,nowJointPos,iksol);
  if(!ret)
    {
      //現在値と目標値で最も離れている関節がm_maxSpeedJointになるように計算
      rotationLength[0] = fabs(iksol[0]-nowLifterPos[0]);
      rotationLength[1] = fabs(iksol[1]-nowLifterPos[1]);
      rotationLength[2] = fabs(iksol[2]-nowWaistPos.yaw);
      rotationLength[3] = fabs(iksol[3]-nowWaistPos.pitch);
      rotationLength[4] = fabs(iksol[4]-nowWaistPos.roll);
      for(int k=0;k<7;k++)
	{
	  rotationLength[k+5] = fabs(iksol[k+5]-nowRightJointPos[k]);
	}
      maxMoveJoint = rotationLength[0];
      maxMoveJointNumber = 0;
      for(int j=0;j<10;j++)
	{
	  if(maxMoveJoint<rotationLength[j+1]){
	    maxMoveJoint = rotationLength[j+1];
	    maxMoveJointNumber = j+1;
	  }
	}
      movetime = ((maxMoveJoint/m_maxSpeedJoint[maxMoveJointNumber])*1000)*(100/(double)m_speedRatioJoint);

      targetLifterPos[0] = iksol[0];
      targetLifterPos[1] = iksol[1];
      targetWaistPos.yaw = iksol[2];
      targetWaistPos.pitch = iksol[3];
      targetWaistPos.roll = iksol[4];
      for(int d=0;d<7;d++)
	{
	  targetRightJointPos[d] = iksol[d+5];
	}
      m_rtcPtr->setWaistJointAngle(targetWaistPos);
      m_rtcPtr->setLeftJointAngle(targetRightJointPos);
      m_rtcPtr->movePTPLifter(targetLifterPos);
      m_rtcPtr->SeedAction(movetime);
    }
  else
    RETURNID_NG;
  
  std::cout << "Success" <<std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::movePTPLIWALArmCartesianRel(const SEED_UPPER::EEPos& carPoint)
{
  std::cout<<"movePTPLIWALArmCartesianRel"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::movePTPLIWALArmJointAbs(const SEED_UPPER::JointPos& jointPoint)
{
    std::cout<<"movePTPLIWALArmJointAbs"<<std::endl;
  
  double targetLifterPos[2];
  double rotationLength[12];
  double maxMoveJoint;
  double maxMoveJointNumber;
  int movetime;
  Frame targetWaistPos;
  double targetLeftJointPos[7];
  
  Frame nowWaistPos;
  Frame nowNeckPos;
  double nowLifterPos[2];
  double nowRightJointPos[7];
  double nowLeftJointPos[7];

  m_rtcPtr->getLifterPos(nowLifterPos);
  m_rtcPtr->readAllJointAngle(&nowWaistPos,&nowNeckPos,nowRightJointPos,nowLeftJointPos);
  
  targetLifterPos[0] = (double)jointPoint[0];
  targetLifterPos[1] = (double)jointPoint[1];
  targetWaistPos.yaw = (double)jointPoint[2];
  targetWaistPos.pitch = (double)jointPoint[3];
  targetWaistPos.roll = (double)jointPoint[4];
  for(int i=0;i<7;i++)
    {
      targetLeftJointPos[i] = jointPoint[i+5];
    }
  
  //現在値と目標値で最も離れている関節がm_maxSpeedJointになるように計算
  rotationLength[0] = fabs(targetLifterPos[0]-nowLifterPos[0]);
  rotationLength[1] = fabs(targetLifterPos[1]-nowLifterPos[1]);
  rotationLength[2] = fabs(targetWaistPos.yaw-nowWaistPos.yaw);
  rotationLength[3] = fabs(targetWaistPos.pitch-nowWaistPos.pitch);
  rotationLength[4] = fabs(targetWaistPos.roll-nowWaistPos.roll);
  for(int k=0;k<7;k++)
    {
      rotationLength[k+5] = fabs(targetLeftJointPos[k]-nowLeftJointPos[k]);
    }
  
  maxMoveJoint = rotationLength[0];
  maxMoveJointNumber = 0;
  for(int j=0;j<10;j++)
    {
      if(maxMoveJoint<rotationLength[j+1]){
	maxMoveJoint = rotationLength[j+1];
	maxMoveJointNumber = j+1;
      }
    }
  movetime = ((maxMoveJoint/m_maxSpeedJoint[maxMoveJointNumber])*1000)*(100/(double)m_speedRatioJoint);

  m_rtcPtr->setWaistJointAngle(targetWaistPos);
  m_rtcPtr->setLeftJointAngle(targetLeftJointPos);
  m_rtcPtr->movePTPLifter(targetLifterPos);
  m_rtcPtr->SeedAction(movetime);

  
  std::cout << "Success" <<std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::movePTPLIWALArmJointRel(const SEED_UPPER::JointPos& jointPoint)
{
  std::cout<<"moveLinearLIWALArmCartesianRel"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::moveLinearLifterDualArmCartesianAbsSetRedunJoint(const SEED_UPPER::Lifter& lifterPos, const SEED_UPPER::RPY& waistPos, const SEED_UPPER::CarPosWithElbow& rightCarPoint, const SEED_UPPER::CarPosWithElbow& leftCarPoint)
{
  std::cout<<"moveLinearLifterDualArmCartesianAbsSetRedunJoint"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::moveLinearLifterDualArmCartesianRelSetRedunJoint(const SEED_UPPER::Lifter& lifterPos, const SEED_UPPER::RPY& waistPos, const SEED_UPPER::CarPosWithElbow& rightCarPoint, const SEED_UPPER::CarPosWithElbow& leftCarPoint)
{
  std::cout<<"moveLinearLifterDualArmCartesianRelSetRedunJoint"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::movePTPLifterDualArmCartesianAbsSetRedunJoint(const SEED_UPPER::Lifter& lifterPos, const SEED_UPPER::RPY& waistPos, const SEED_UPPER::CarPosWithElbow& rightCarPoint, const SEED_UPPER::CarPosWithElbow& leftCarPoint)
{
  std::cout<<"movePTPLifterDualArmCartesianAbsSetRedunJoint"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::movePTPLifterDualArmCartesianRelSetRedunJoint(const SEED_UPPER::Lifter& lifterPos, const SEED_UPPER::RPY& waistPos, const SEED_UPPER::CarPosWithElbow& rightCarPoint, const SEED_UPPER::CarPosWithElbow& leftCarPoint)
{
  std::cout<<"movePTPLifterDualArmCartesianRelSetRedunJoint"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::moveLinearLifterDualArmCartesianAbs(const SEED_UPPER::EEPos& rightCarPoint, const SEED_UPPER::EEPos& leftCarPoint)
{
  std::cout<<"moveLinearLifterDualArmCartesianAbs"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::moveLinearLifterDualArmCartesianRel(const SEED_UPPER::EEPos& rightCarPoint, const SEED_UPPER::EEPos& leftCarPoint)
{
  std::cout<<"moveLinearLifterDualArmCartesianRel"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::movePTPLifterDualArmCartesianAbs(const SEED_UPPER::EEPos& rightCarPoint, const SEED_UPPER::EEPos& leftCarPoint)
{
  std::cout<<"movePTPLifterDualArmCartesianAbs"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::movePTPLifterDualArmCartesianRel(const SEED_UPPER::EEPos& rightCarPoint, const SEED_UPPER::EEPos& leftCarPoint)
{
  std::cout<<"movePTPLifterDualArmCartesianRel"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::movePTPLifterDualArmJointAbs(const SEED_UPPER::Lifter& lifterPos, const SEED_UPPER::RPY& waistPos, const SEED_UPPER::JointPos& rightJointPoint, const SEED_UPPER::JointPos& leftJointPoint)
{
  std::cout<<"movePTPLifterDualArmJointAbs"<<std::endl;
  
  double targetLifterPos[2];
  double rotationLength[19];
  double maxMoveJoint;
  double maxMoveJointNumber;
  int movetime;
  Frame targetWaistPos;
  double targetRightJointPos[7];
  double targetLeftJointPos[7];
    
  Frame nowWaistPos;
  Frame nowNeckPos;
  double nowLifterPos[2];
  double nowRightJointPos[7];
  double nowLeftJointPos[7];

  m_rtcPtr->getLifterPos(nowLifterPos);
  m_rtcPtr->readAllJointAngle(&nowWaistPos,&nowNeckPos,nowRightJointPos,nowLeftJointPos);
  
  targetLifterPos[0] = (double)lifterPos.bottom;
  targetLifterPos[1] = (double)lifterPos.top;
  targetWaistPos.yaw = (double)waistPos.yaw;
  targetWaistPos.pitch = (double)waistPos.pitch;
  targetWaistPos.roll = (double)waistPos.roll;
  for(int i=0;i<7;i++)
    {
      targetRightJointPos[i] = rightJointPoint[i+5];
    }
  for(int i=0;i<7;i++)
    {
      targetLeftJointPos[i] = leftJointPoint[i+5];
    }
  
  //現在値と目標値で最も離れている関節がm_maxSpeedJointになるように計算
  rotationLength[0] = fabs(targetLifterPos[0]-nowLifterPos[0]);
  rotationLength[1] = fabs(targetLifterPos[1]-nowLifterPos[1]);
  rotationLength[2] = fabs(targetWaistPos.yaw-nowWaistPos.yaw);
  rotationLength[3] = fabs(targetWaistPos.pitch-nowWaistPos.pitch);
  rotationLength[4] = fabs(targetWaistPos.roll-nowWaistPos.roll);
  for(int k=0;k<7;k++)
    {
      rotationLength[k+5] = fabs(targetRightJointPos[k]-nowRightJointPos[k]);
    }
  for(int k=0;k<7;k++)
    {
      rotationLength[k+12] = fabs(targetRightJointPos[k]-nowRightJointPos[k]);
    }  
  maxMoveJoint = rotationLength[0];
  maxMoveJointNumber = 0;
  for(int j=0;j<17;j++)
    {
      if(maxMoveJoint<rotationLength[j+1]){
	maxMoveJoint = rotationLength[j+1];
	maxMoveJointNumber = j+1;
      }
    }
  movetime = ((maxMoveJoint/m_maxSpeedJoint[maxMoveJointNumber])*1000)*(100/(double)m_speedRatioJoint);

  m_rtcPtr->setWaistJointAngle(targetWaistPos);
  m_rtcPtr->setRightJointAngle(targetRightJointPos);
  m_rtcPtr->setLeftJointAngle(targetLeftJointPos);
  m_rtcPtr->movePTPLifter(targetLifterPos);
  m_rtcPtr->SeedAction(movetime);

  
  std::cout << "Success" <<std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::movePTPLifterDualArmJointRel(const SEED_UPPER::Lifter& lifterPos, const SEED_UPPER::RPY& waistPos, const SEED_UPPER::JointPos& rightJointPoint, const SEED_UPPER::JointPos& leftJointPoint)
{
  std::cout<<"movePTPLifterDualArmJointRel"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::movePTPLIWARArmJointAbsCmdCycle(const SEED_UPPER::JointPos& jointPoint)
{
  std::cout<<"movePTPLIWARArmJointAbsCmdCycle"<<std::endl;
  
  double targetLifterPos[2];
  int movetime;
  Frame targetWaistPos;
  double targetRightJointPos[7];

  for(int i=0;i<10;i++){
  std::cout << "jointPoint["<<i<<"] = " << jointPoint[i] << std::endl;
  }
  targetLifterPos[0] = (double)jointPoint[0];
  targetLifterPos[1] = (double)jointPoint[1];
  targetWaistPos.yaw = (double)jointPoint[2];
  targetWaistPos.pitch = (double)jointPoint[3];
  targetWaistPos.roll = (double)jointPoint[4];
  for(int i=0;i<7;i++)
    {
      targetRightJointPos[i] = jointPoint[i+5];
    }

  //std::cout << "mInfo.cmdCycle = " <<mInfo.cmdCycle<< std::endl; 
  movetime = 1000/mInfo.cmdCycle;

  m_rtcPtr->setWaistJointAngle(targetWaistPos);
  m_rtcPtr->setRightJointAngle(targetRightJointPos);
  m_rtcPtr->movePTPLifter(targetLifterPos);
  m_rtcPtr->SeedAction(movetime);

  
  std::cout << "Success" <<std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::movePTPLIWALArmJointAbsCmdCycle(const SEED_UPPER::JointPos& jointPoint)
{
  std::cout<<"movePTPLIWALArmJointAbs"<<std::endl;
  
  double targetLifterPos[2];
  int movetime;
  Frame targetWaistPos;
  double targetLeftJointPos[7];
  
  targetLifterPos[0] = (double)jointPoint[0];
  targetLifterPos[1] = (double)jointPoint[1];
  targetWaistPos.yaw = (double)jointPoint[2];
  targetWaistPos.pitch = (double)jointPoint[3];
  targetWaistPos.roll = (double)jointPoint[4];
  for(int i=0;i<7;i++)
    {
      targetLeftJointPos[i] = jointPoint[i+5];
    }
  
  movetime = 1000/mInfo.cmdCycle;

  m_rtcPtr->setWaistJointAngle(targetWaistPos);
  m_rtcPtr->setLeftJointAngle(targetLeftJointPos);
  m_rtcPtr->movePTPLifter(targetLifterPos);
  m_rtcPtr->SeedAction(movetime);

  
  std::cout << "Success" <<std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::movePTPDualArmJointAbsCmdCycle(const SEED_UPPER::Lifter& lifterPos, const SEED_UPPER::RPY& waistPos, const SEED_UPPER::JointPos& rightJointPoint, const SEED_UPPER::JointPos& leftJointPoint)
{
  std::cout<<"movePTPDualArmJointAbsCmdCycle"<<std::endl;
  
  double targetLifterPos[2];
  int movetime;
  Frame targetWaistPos;
  double targetRightJointPos[7];
  double targetLeftJointPos[7];
  
  targetLifterPos[0] = (double)lifterPos.bottom;
  targetLifterPos[1] = (double)lifterPos.top;
  targetWaistPos.yaw = (double)waistPos.yaw;
  targetWaistPos.pitch = (double)waistPos.pitch;
  targetWaistPos.roll = (double)waistPos.roll;
  for(int i=0;i<7;i++)
    {
      targetRightJointPos[i] = rightJointPoint[i];
    }
    for(int i=0;i<7;i++)
    {
      targetLeftJointPos[i] = leftJointPoint[i];
    }
  
  movetime = 1000/mInfo.cmdCycle;

  m_rtcPtr->setWaistJointAngle(targetWaistPos);
  m_rtcPtr->setRightJointAngle(targetRightJointPos);
  m_rtcPtr->setLeftJointAngle(targetLeftJointPos);
  m_rtcPtr->movePTPLifter(targetLifterPos);
  m_rtcPtr->SeedAction(movetime);

  
  std::cout << "Success" <<std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::solveLIWARArmIkSetRedunJoint(const SEED_UPPER::CarPosWithLifterWaistElbow& carPoint, const SEED_UPPER::JointPos& nowJointPos, SEED_UPPER::JointPos_out jointPoint)
{
  std::cout << "solveLIWARArmIkSetRedunJoint" <<std::endl;
  double eerot[9];
  double eetrans[3];
  double elbow;
  Frame WaistPos;
  double lifter[2];
  double setNowJointPos[12];
  double iksol[12];

  eerot[0]=carPoint.carPos[0][0];
  eerot[1]=carPoint.carPos[0][1];
  eerot[2]=carPoint.carPos[0][2];
  
  eerot[3]=carPoint.carPos[1][0];
  eerot[4]=carPoint.carPos[1][1];
  eerot[5]=carPoint.carPos[1][2];
  
  eerot[6]=carPoint.carPos[2][0];
  eerot[7]=carPoint.carPos[2][1];
  eerot[8]=carPoint.carPos[2][2];

  eetrans[0]=carPoint.carPos[0][3];
  eetrans[1]=carPoint.carPos[1][3];
  eetrans[2]=carPoint.carPos[2][3];

  lifter[0] = carPoint.LifterPos.bottom;
  lifter[1] = carPoint.LifterPos.top;

  WaistPos.yaw = carPoint.waistPos.yaw;
  WaistPos.pitch = carPoint.waistPos.pitch;
  WaistPos.roll = carPoint.waistPos.roll;

  elbow = 0;

  for(int i=0;i<12;i++)
    {
      setNowJointPos[i] = nowJointPos[i];
    }


  int ret = m_rtcPtr->Solve_LIWARArmIkSetRedun(eerot,eetrans,elbow,WaistPos,lifter,setNowJointPos,iksol);

  if(ret!=0)
    {
      //可動範囲外の解
      RETURNID_NG;
    }

  jointPoint = new SEED_UPPER::JointPos;
  jointPoint->length(12);
  
  for(int i=0;i<12;i++)
    {
      (*jointPoint)[i] = iksol[i];
    }
  
  std::cout << "Success" <<std::endl;
  RETURNID_OK;
  
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::solveLIWALArmIkSetRedunJoint(const SEED_UPPER::CarPosWithLifterWaistElbow& carPoint, const SEED_UPPER::JointPos& nowJointPos, SEED_UPPER::JointPos_out jointPoint)
{
  std::cout << "solveLIWALArmIkSetRedunJoint" <<std::endl;
  double eerot[9];
  double eetrans[3];
  double elbow;
  Frame WaistPos;
  double lifter[2];
  double setNowJointPos[12];
  double iksol[12];

  eerot[0]=carPoint.carPos[0][0];
  eerot[1]=carPoint.carPos[0][1];
  eerot[2]=carPoint.carPos[0][2];
  
  eerot[3]=carPoint.carPos[1][0];
  eerot[4]=carPoint.carPos[1][1];
  eerot[5]=carPoint.carPos[1][2];
  
  eerot[6]=carPoint.carPos[2][0];
  eerot[7]=carPoint.carPos[2][1];
  eerot[8]=carPoint.carPos[2][2];

  eetrans[0]=carPoint.carPos[0][3];
  eetrans[1]=carPoint.carPos[1][3];
  eetrans[2]=carPoint.carPos[2][3];

  lifter[0] = carPoint.LifterPos.bottom;
  lifter[1] = carPoint.LifterPos.top;

  WaistPos.yaw = carPoint.waistPos.yaw;
  WaistPos.pitch = carPoint.waistPos.pitch;
  WaistPos.roll = carPoint.waistPos.roll;

  elbow = 0;

  for(int i=0;i<12;i++)
    {
      setNowJointPos[i] = nowJointPos[i];
    }


  int ret = m_rtcPtr->Solve_LIWALArmIkSetRedun(eerot,eetrans,elbow,WaistPos,lifter,setNowJointPos,iksol);

  if(ret!=0)
    {
      //可動範囲外の解
      RETURNID_NG;
    }

  jointPoint = new SEED_UPPER::JointPos;
  jointPoint->length(12);
  
  for(int i=0;i<12;i++)
    {
      (*jointPoint)[i] = iksol[i];
    }
  
  std::cout << "Success" <<std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::solveLIWARArmIk(const SEED_UPPER::EEPos& carPoint, const SEED_UPPER::JointPos& nowJointPos, SEED_UPPER::JointPos_out jointPoint)
{
  std::cout << "solveLIWARArmIk" <<std::endl;
  double eerot[9];
  double eetrans[3];
  double setNowJointPos[12];
  double iksol[12];
  
  eerot[0]=carPoint.carPos[0][0];
  eerot[1]=carPoint.carPos[0][1];
  eerot[2]=carPoint.carPos[0][2];
  
  eerot[3]=carPoint.carPos[1][0];
  eerot[4]=carPoint.carPos[1][1];
  eerot[5]=carPoint.carPos[1][2];
  
  eerot[6]=carPoint.carPos[2][0];
  eerot[7]=carPoint.carPos[2][1];
  eerot[8]=carPoint.carPos[2][2];

  eetrans[0]=carPoint.carPos[0][3];
  eetrans[1]=carPoint.carPos[1][3];
  eetrans[2]=carPoint.carPos[2][3];

  for(int i=0;i<12;i++)
    {
      setNowJointPos[i] = nowJointPos[i];
    }

  int ret = m_rtcPtr->Solve_LIWARArmIk(eerot,eetrans,setNowJointPos,iksol);

  if(ret!=0)
    {
      //可動範囲外の解
      RETURNID_NG;
    }
    
  jointPoint = new SEED_UPPER::JointPos;
  jointPoint->length(12);

  for(int i=0;i<12;i++)
    {
      (*jointPoint)[i] = iksol[i];
    }

  //delete jointPoint;
  std::cout << "Success" <<std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::solveLIWALArmIk(const SEED_UPPER::EEPos& carPoint, const SEED_UPPER::JointPos& nowJointPos, SEED_UPPER::JointPos_out jointPoint)
{
  std::cout << "solveLIWARArmIk" <<std::endl;
  double eerot[9];
  double eetrans[3];
  double setNowJointPos[12];
  double iksol[12];
  
  eerot[0]=carPoint.carPos[0][0];
  eerot[1]=carPoint.carPos[0][1];
  eerot[2]=carPoint.carPos[0][2];
  
  eerot[3]=carPoint.carPos[1][0];
  eerot[4]=carPoint.carPos[1][1];
  eerot[5]=carPoint.carPos[1][2];
  
  eerot[6]=carPoint.carPos[2][0];
  eerot[7]=carPoint.carPos[2][1];
  eerot[8]=carPoint.carPos[2][2];

  eetrans[0]=carPoint.carPos[0][3];
  eetrans[1]=carPoint.carPos[1][3];
  eetrans[2]=carPoint.carPos[2][3];

  for(int i=0;i<12;i++)
    {
      setNowJointPos[i] = nowJointPos[i];
    }

  int ret = m_rtcPtr->Solve_LIWALArmIk(eerot,eetrans,setNowJointPos,iksol);

  if(ret!=0)
    {
      //可動範囲外の解
      RETURNID_NG;
    }
    
  jointPoint = new SEED_UPPER::JointPos;
  jointPoint->length(12);

  for(int i=0;i<12;i++)
    {
      (*jointPoint)[i] = iksol[i];
    }

  std::cout << "Success" <<std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::solveLIWARArmFk(const SEED_UPPER::JointPos& jointPoint, SEED_UPPER::EEPos& carPoint)
{
  std::cout << "solveLIWARArmFk" <<std::endl;
  double eerot[9];
  double eetrans[3];
  double joint[12];
  for(int i=0;i<12;i++)
    {
      joint[i] = jointPoint[i];
    }
  m_rtcPtr->Solve_LIWARArmFk(eerot,eetrans,joint);

  carPoint.carPos[0][0] = eerot[0];
  carPoint.carPos[0][1] = eerot[1];
  carPoint.carPos[0][2] = eerot[2];
  
  carPoint.carPos[1][0] = eerot[3];
  carPoint.carPos[1][1] = eerot[4];
  carPoint.carPos[1][2] = eerot[5];

  carPoint.carPos[2][0] = eerot[6];
  carPoint.carPos[2][1] = eerot[7];
  carPoint.carPos[2][2] = eerot[8];

  carPoint.carPos[0][3] = eetrans[0];
  carPoint.carPos[1][3] = eetrans[1];
  carPoint.carPos[2][3] = eetrans[2];

  std::cout << "Success" <<std::endl;
  RETURNID_OK;
}

SEED_UPPER::RETURN_ID* SEED_UPPER_SeedUpperInterface_MiddleSVC_impl::solveLIWALArmFk(const SEED_UPPER::JointPos& jointPoint, SEED_UPPER::EEPos& carPoint)
{
  std::cout << "solveLIWALArmFk" <<std::endl;
  double eerot[9];
  double eetrans[3];
  double joint[12];
  for(int i=0;i<12;i++)
    {
      joint[i] = jointPoint[i];
    }
  m_rtcPtr->Solve_LIWALArmFk(eerot,eetrans,joint);

  carPoint.carPos[0][0] = eerot[0];
  carPoint.carPos[0][1] = eerot[1];
  carPoint.carPos[0][2] = eerot[2];
  
  carPoint.carPos[1][0] = eerot[3];
  carPoint.carPos[1][1] = eerot[4];
  carPoint.carPos[1][2] = eerot[5];

  carPoint.carPos[2][0] = eerot[6];
  carPoint.carPos[2][1] = eerot[7];
  carPoint.carPos[2][2] = eerot[8];

  carPoint.carPos[0][3] = eetrans[0];
  carPoint.carPos[1][3] = eetrans[1];
  carPoint.carPos[2][3] = eetrans[2];

  std::cout << "Success" <<std::endl;
  RETURNID_OK;
}



// End of example implementational code



