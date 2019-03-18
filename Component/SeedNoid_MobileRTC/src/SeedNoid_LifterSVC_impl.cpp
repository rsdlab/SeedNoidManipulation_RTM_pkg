// -*-C++-*-
/*!
 * @file  SeedNoid_LifterSVC_impl.cpp
 * @brief Service implementation code of SeedNoid_Lifter.idl
 *
 */

#include "SeedNoid_LifterSVC_impl.h"

/*
 * Example implementational code for IDL interface SeedNoid_Lifter::LifterPose
 */
SeedNoid_Lifter_LifterPoseSVC_impl::SeedNoid_Lifter_LifterPoseSVC_impl()
{
  m_speedRatioLifter = 50; /* [%] */
  int lifterJointNum = 2;
  m_maxSpeedLifter.length(lifterJointNum);
  for(int i(0); i < lifterJointNum; i++)
    {
      m_maxSpeedLifter[i] = 30; /* [deg/s] */
    }
}


SeedNoid_Lifter_LifterPoseSVC_impl::~SeedNoid_Lifter_LifterPoseSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter_LifterPoseSVC_impl::sendLifterAngle(const SeedNoid_Lifter::LifterAngle& targetLifterAngle)
{
  SeedNoid_Lifter::RETURN_VALUE result;
  
  std::cout << "sendLifterAngle" << std::endl; 
    
  if(!m_pRTC->CheckAngle(m_pRTC->LifterAngle))
    {
      std::cout << "Out of calculation range" << std::endl;

      result = SeedNoid_Lifter::RETURN_NOT_FOUND;
    }
  else
    {
      std::cout << "Range of movement" << std::endl;

      SeedNoid_Lifter::LifterAngle_var currentLifterAnglevar;
      SeedNoid_Lifter::LifterAngle currentLifterAngle;
      getLifterAngle(currentLifterAnglevar);
      currentLifterAngle = currentLifterAnglevar;
      //現在値と目標値で最も離れている関節がm_maxSpeedJointになるように計算
      rotationLength[0] = fabs(targetLifterAngle.top - currentLifterAngle.top);
      rotationLength[1] = fabs(targetLifterAngle.bottom - currentLifterAngle.bottom);
      maxMoveJoint = rotationLength[0];
      maxMoveJointNumber = 0;
      for(int j(0); j < 2; j++)
	{
	  if(maxMoveJoint < rotationLength[j])
	    {
	      maxMoveJoint = rotationLength[j];
	      maxMoveJointNumber = j;
	    }
	}
      moveTime = static_cast<int>(((maxMoveJoint / m_maxSpeedLifter[maxMoveJointNumber]) * 1000) * (100 / (double)m_speedRatioLifter));
      std::cout << "movetime = " << moveTime << std::endl;
      m_pRTC->LifterAngle.top = targetLifterAngle.top;
      m_pRTC->LifterAngle.bottom = targetLifterAngle.bottom;
      m_pRTC->moveLifterForwardKinematics(m_pRTC->LifterAngle, moveTime);
      
      result = SeedNoid_Lifter::RETURN_MOVE_OK;
    }

  return result;
}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter_LifterPoseSVC_impl::sendLifterPose(const RTC::Point3D& targetLifterPose)
{
  SeedNoid_Lifter::RETURN_VALUE result;
  
  std::cout << "sendLifterPose" << std::endl;
  
  m_pRTC->LifterPose.x = targetLifterPose.x;
  m_pRTC->LifterPose.z = targetLifterPose.z;

  if(!m_pRTC->CheckPose(m_pRTC->LifterPose))
    {
      std::cout << "Out of calculation range" << std::endl;

      result = SeedNoid_Lifter::RETURN_OUT_OF_RANGE;
    }
  else
    {
      std::cout << "Range of movement" << std::endl;

      //===========一旦保留=========
      //現在角度と目標角度の差から動作速度を決定するプログラムがかけていないため
      double lifterAngleTop,lifterAngleUnder,calcLifterAngleTop,calcLifterAngleUnder,lifterLength;
      lifterLength = 0.25;
      calcLifterAngleTop = std::acos((std::pow(targetLifterPose.x,2) + std::pow(targetLifterPose.z,2) - 2 * std::pow(lifterLength,2)) / (2 * std::pow(lifterLength,2)));

      if((calcLifterAngleTop * 180 / M_PI) > 0)
	{
	  calcLifterAngleTop = -calcLifterAngleTop;
	}

      calcLifterAngleUnder = std::asin(-(((targetLifterPose.x * lifterLength * std::sin(calcLifterAngleTop)) - (targetLifterPose.z * (lifterLength + lifterLength * std::cos(calcLifterAngleTop)))) / (std::pow((lifterLength + lifterLength * std::cos(calcLifterAngleTop)),2) + std::pow(lifterLength,2) * std::pow(std::sin(calcLifterAngleTop),2))));

      //Change Radian to Degree
      calcLifterAngleTop = (calcLifterAngleTop * 180 / M_PI);
      calcLifterAngleUnder = (calcLifterAngleUnder * 180 / M_PI);
  
      if(calcLifterAngleUnder < 90 || 180 < calcLifterAngleUnder)
	{
	  calcLifterAngleUnder = 180 - calcLifterAngleUnder;
	}
  
      lifterAngleUnder = calcLifterAngleUnder - 90;
      lifterAngleTop = 0 - (calcLifterAngleTop + (calcLifterAngleUnder - 90));

      if(85 < lifterAngleTop && lifterAngleTop <= 90)
	{
	  lifterAngleTop = 85;
	}

      if(85 < lifterAngleUnder && lifterAngleUnder <= 90)
	{
	  lifterAngleUnder = 85;
	}
      //m_pRTC->LifterAngle.top =lifterAngleTop;
      //m_pRTC->LifterAngle.bottom = lifterAngleTop;
            
      SeedNoid_Lifter::LifterAngle targetLifterAngle;
      targetLifterAngle.top = lifterAngleTop;
      targetLifterAngle.bottom = lifterAngleUnder;
      sendLifterAngle(targetLifterAngle);
      //m_pRTC->moveLifterReverseKinematics(m_pRTC->targetLifterPose);

      //=====================================================

      result = SeedNoid_Lifter::RETURN_MOVE_OK;
    }
  
  return result;
}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter_LifterPoseSVC_impl::getLifterAngle(SeedNoid_Lifter::LifterAngle& currentLifterAngle)
{
  std::cout << "getLifterAngle" << std::endl;
  //set return value
  SeedNoid_Lifter::RETURN_VALUE result = SeedNoid_Lifter::RETURN_OK;

  m_pRTC->currentLifterAngle();

  currentLifterAngle.top = m_pRTC->LifterAngle.top;
  currentLifterAngle.bottom = m_pRTC->LifterAngle.bottom;

  std::cout << "Success" << std::endl;
  return result;
}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter_LifterPoseSVC_impl::getLifterPose(RTC::Point3D& currentLifterPose)
{
  std::cout << "getLifterPose" << std::endl;
  //set return value
  SeedNoid_Lifter::RETURN_VALUE result = SeedNoid_Lifter::RETURN_OK;

  m_pRTC->currentLifterPose();

  currentLifterPose.x = m_pRTC->LifterPose.x;
  currentLifterPose.z = m_pRTC->LifterPose.z;

  std::cout << "Success" << std::endl;
  
  return result;
}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter_LifterPoseSVC_impl::getSoftLimitLifter(SeedNoid_Lifter::LimitSeq_out softLimit)
{
  //set return value
  SeedNoid_Lifter::RETURN_VALUE result = SeedNoid_Lifter::RETURN_OK;
  return result;
}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter_LifterPoseSVC_impl::setSoftLimitLifter(const SeedNoid_Lifter::LimitSeq& softLimit)
{
  //set return value
  SeedNoid_Lifter::RETURN_VALUE result = SeedNoid_Lifter::RETURN_OK;
  return result;
}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter_LifterPoseSVC_impl::getMaxSpeedLifter(SeedNoid_Lifter::DoubleSeq_out speed)
{
  //set return value
  SeedNoid_Lifter::RETURN_VALUE result = SeedNoid_Lifter::RETURN_OK;
  return result;
}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter_LifterPoseSVC_impl::getMinAccelTimeLifter(::CORBA::Double& aclTime)
{
  //set return value
  SeedNoid_Lifter::RETURN_VALUE result = SeedNoid_Lifter::RETURN_OK;
  return result;
}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter_LifterPoseSVC_impl::pause()
{
  //set return value
  SeedNoid_Lifter::RETURN_VALUE result = SeedNoid_Lifter::RETURN_OK;
  return result;
}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter_LifterPoseSVC_impl::resume()
{
  //set return value
  SeedNoid_Lifter::RETURN_VALUE result = SeedNoid_Lifter::RETURN_OK;
  return result;
}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter_LifterPoseSVC_impl::stop()
{
  //set return value
  SeedNoid_Lifter::RETURN_VALUE result = SeedNoid_Lifter::RETURN_OK;
  return result;
}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter_LifterPoseSVC_impl::setAccelTimeLifter(::CORBA::Double aclTime)
{
  //set return value
  SeedNoid_Lifter::RETURN_VALUE result = SeedNoid_Lifter::RETURN_OK;
  return result;
}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter_LifterPoseSVC_impl::setMaxSpeedLifter(const SeedNoid_Lifter::DoubleSeq& speed)
{
  //set return value
  SeedNoid_Lifter::RETURN_VALUE result = SeedNoid_Lifter::RETURN_OK;
  
  std::cout << "setMaxSpeedLifter" << std::endl;

  for(unsigned int i(0); i < speed.length(); i++)
    {
      m_maxSpeedLifter[i] = speed[i];
    }
  
  std::cout << "Success" << std::endl << std::endl;
  
  return result;
}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter_LifterPoseSVC_impl::setMinAccelTimeLifter(::CORBA::Double aclTime)
{
  //set return value
  SeedNoid_Lifter::RETURN_VALUE result = SeedNoid_Lifter::RETURN_OK;
  return result;
}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter_LifterPoseSVC_impl::setSpeedLifter(SeedNoid_Lifter::ULONG spdRatio)
{
  //set return value
  SeedNoid_Lifter::RETURN_VALUE result = SeedNoid_Lifter::RETURN_OK;
  
  std::cout << "setSpeedLifter" << std::endl;
  
  if(spdRatio >= 0 && spdRatio <= 100)
    {
      m_speedRatioLifter = spdRatio;
    }
  else
    {
      std::cout << "ERROR : Wrong Value" << std::endl;
      result = SeedNoid_Lifter::RETURN_INVALID_PARAMETER;
    }
  
  std::cout << "Success" <<std::endl;
  
  return result;
}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter_LifterPoseSVC_impl::getSpeedLifter(SeedNoid_Lifter::ULONG& spdRatio)
{
  //set return value
  SeedNoid_Lifter::RETURN_VALUE result = SeedNoid_Lifter::RETURN_OK;

  std::cout << "getSpeedLifter" << std::endl;
  spdRatio = m_speedRatioLifter;
  std::cout << "Success" << std::endl;
  
  return result;
}



// End of example implementational code



