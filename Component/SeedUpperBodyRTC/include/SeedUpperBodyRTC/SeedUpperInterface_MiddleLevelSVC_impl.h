// -*-C++-*-
/*!
 * @file  SeedUpperInterface_MiddleLevelSVC_impl.h
 * @brief Service implementation header of SeedUpperInterface_MiddleLevel.idl
 *
 */

#include "SeedUpperInterface_DataTypeSkel.h"
#include "BasicDataTypeSkel.h"

#include "SeedUpperInterface_MiddleLevelSkel.h"

#include "SeedUpperBodyRTC.h"

#ifndef SEEDUPPERINTERFACE_MIDDLELEVELSVC_IMPL_H
#define SEEDUPPERINTERFACE_MIDDLELEVELSVC_IMPL_H

#include "SeedUpperInterface_CommonSVC_impl.h"
#include "LibSeednoidUpper.h"

class SeedUpperBodyRTC;

/*!
 * @class SEED_UPPER_SeedUpperInterface_MiddleSVC_impl
 * Example class implementing IDL interface SEED_UPPER::SeedUpperInterface_Middle
 */
class SEED_UPPER_SeedUpperInterface_MiddleSVC_impl
 : public virtual POA_SEED_UPPER::SeedUpperInterface_Middle,
   public virtual PortableServer::RefCountServantBase
{
 private:
   // Make sure all instances are built on the heap by making the
   // destructor non-public
   //virtual ~SEED_UPPER_SeedUpperInterface_MiddleSVC_impl();
  SEED_UPPER_SeedUpperInterface_CommonSVC_impl m_SeedUpperInterface_Common;
  SeedUpperBodyRTC* m_rtcPtr;
  SEED_UPPER::ManipInfo_var mInfovar;
  SEED_UPPER::ManipInfo mInfo;
  SEED_UPPER::JointPos m_nowRightPos;
  SEED_UPPER::JointPos m_nowLeftPos;
  SEED_UPPER::JointPos m_nowNeckPos;
  SEED_UPPER::JointPos m_nowWaistPos;
  bool m_maxSpeedJointFlag,m_maxSpeedCartesianFlag,m_softLimitCartesianFlag;
  SEED_UPPER::CartesianSpeed m_maxSpeedCartesian;
  SEED_UPPER::DoubleSeq m_maxSpeedJoint;
  SEED_UPPER::LimitValue m_xLimit, m_yLimit, m_zLimit;
  SEED_UPPER::ULONG m_speedRatioCartesian,m_speedRatioJoint,m_forceRatio;
  SEED_UPPER::RETURN_ID_var m_rid_seed;
  
 public:
  /*!
   * @brief standard constructor
   */
   SEED_UPPER_SeedUpperInterface_MiddleSVC_impl();
  /*!
   * @brief destructor
   */
   virtual ~SEED_UPPER_SeedUpperInterface_MiddleSVC_impl();

   // attributes and operations
   SEED_UPPER::RETURN_ID* closeRightGripper();
   SEED_UPPER::RETURN_ID* openRightGripper();
   SEED_UPPER::RETURN_ID* moveRightGripper(SEED_UPPER::ULONG angleRatio);
   SEED_UPPER::RETURN_ID* closeLeftGripper();
   SEED_UPPER::RETURN_ID* openLeftGripper();
   SEED_UPPER::RETURN_ID* moveLeftGripper(SEED_UPPER::ULONG angleRatio);
   SEED_UPPER::RETURN_ID* setRightGraspForce(SEED_UPPER::ULONG forceRatio);
   SEED_UPPER::RETURN_ID* getRightGraspForce(SEED_UPPER::ULONG& forceRatio);
   SEED_UPPER::RETURN_ID* setLeftGraspForce(SEED_UPPER::ULONG forceRatio);
   SEED_UPPER::RETURN_ID* getLeftGraspForce(SEED_UPPER::ULONG& forceRatio);
   SEED_UPPER::RETURN_ID* getFeedbackPosLIWARCartesian(SEED_UPPER::CarPosWithLifterWaistElbow& pos);
   SEED_UPPER::RETURN_ID* getFeedbackPosLIWALCartesian(SEED_UPPER::CarPosWithLifterWaistElbow& pos);
   SEED_UPPER::RETURN_ID* setMaxSpeedCartesian(const SEED_UPPER::CartesianSpeed& speed);
   SEED_UPPER::RETURN_ID* setMaxSpeedJoint(const SEED_UPPER::DoubleSeq& speed);
   SEED_UPPER::RETURN_ID* getMaxSpeedCartesian(SEED_UPPER::CartesianSpeed& speed);
   SEED_UPPER::RETURN_ID* getMaxSpeedJoint(SEED_UPPER::DoubleSeq_out speed);
   SEED_UPPER::RETURN_ID* setSpeedCartesian(SEED_UPPER::ULONG spdRatio);
   SEED_UPPER::RETURN_ID* setSpeedJoint(SEED_UPPER::ULONG spdRatio);
   SEED_UPPER::RETURN_ID* getSpeedCartesian(SEED_UPPER::ULONG& spdRatio);
   SEED_UPPER::RETURN_ID* getSpeedJoint(SEED_UPPER::ULONG& spdRatio);
   SEED_UPPER::RETURN_ID* setSoftLimitCartesian(const SEED_UPPER::LimitValue& xLimit, const SEED_UPPER::LimitValue& yLimit, const SEED_UPPER::LimitValue& zLimit);
   SEED_UPPER::RETURN_ID* getSoftLimitCartesian(SEED_UPPER::LimitValue& xLimit, SEED_UPPER::LimitValue& yLimit, SEED_UPPER::LimitValue& zLimit);
   SEED_UPPER::RETURN_ID* moveLinearLIWARArmCartesianAbsSetRedunJoint(const SEED_UPPER::CarPosWithLifterWaistElbow& carPoint);
   SEED_UPPER::RETURN_ID* moveLinearLIWARArmCartesianRelSetRedunJoint(const SEED_UPPER::CarPosWithLifterWaistElbow& carPoint);
   SEED_UPPER::RETURN_ID* movePTPLIWARArmCartesianAbsSetRedunJoint(const SEED_UPPER::CarPosWithLifterWaistElbow& carPoint);
   SEED_UPPER::RETURN_ID* movePTPLIWARArmCartesianRelSetRedunJoint(const SEED_UPPER::CarPosWithLifterWaistElbow& carPoint);
   SEED_UPPER::RETURN_ID* moveLinearLIWARArmCartesianAbs(const SEED_UPPER::EEPos& carPoint);
   SEED_UPPER::RETURN_ID* moveLinearLIWARArmCartesianRel(const SEED_UPPER::EEPos& carPoint);
   SEED_UPPER::RETURN_ID* movePTPLIWARArmCartesianAbs(const SEED_UPPER::EEPos& carPoint);
   SEED_UPPER::RETURN_ID* movePTPLIWARArmCartesianRel(const SEED_UPPER::EEPos& carPoint);
   SEED_UPPER::RETURN_ID* movePTPLIWARArmJointAbs(const SEED_UPPER::JointPos& jointPoint);
   SEED_UPPER::RETURN_ID* movePTPLIWARArmJointRel(const SEED_UPPER::JointPos& jointPoint);
   SEED_UPPER::RETURN_ID* moveLinearLIWALArmCartesianAbsSetRedunJoint(const SEED_UPPER::CarPosWithLifterWaistElbow& carPoint);
   SEED_UPPER::RETURN_ID* moveLinearLIWALArmCartesianRelSetRedunJoint(const SEED_UPPER::CarPosWithLifterWaistElbow& carPoint);
   SEED_UPPER::RETURN_ID* movePTPLIWALArmCartesianAbsSetRedunJoint(const SEED_UPPER::CarPosWithLifterWaistElbow& carPoint);
   SEED_UPPER::RETURN_ID* movePTPLIWALArmCartesianRelSetRedunJoint(const SEED_UPPER::CarPosWithLifterWaistElbow& carPoint);
   SEED_UPPER::RETURN_ID* moveLinearLIWALArmCartesianAbs(const SEED_UPPER::EEPos& carPoint);
   SEED_UPPER::RETURN_ID* moveLinearLIWALArmCartesianRel(const SEED_UPPER::EEPos& carPoint);
   SEED_UPPER::RETURN_ID* movePTPLIWALArmCartesianAbs(const SEED_UPPER::EEPos& carPoint);
   SEED_UPPER::RETURN_ID* movePTPLIWALArmCartesianRel(const SEED_UPPER::EEPos& carPoint);
   SEED_UPPER::RETURN_ID* movePTPLIWALArmJointAbs(const SEED_UPPER::JointPos& jointPoint);
   SEED_UPPER::RETURN_ID* movePTPLIWALArmJointRel(const SEED_UPPER::JointPos& jointPoint);
   SEED_UPPER::RETURN_ID* moveLinearLifterDualArmCartesianAbsSetRedunJoint(const SEED_UPPER::Lifter& lifterPos, const SEED_UPPER::RPY& waistPos, const SEED_UPPER::CarPosWithElbow& rightCarPoint, const SEED_UPPER::CarPosWithElbow& leftCarPoint);
   SEED_UPPER::RETURN_ID* moveLinearLifterDualArmCartesianRelSetRedunJoint(const SEED_UPPER::Lifter& lifterPos, const SEED_UPPER::RPY& waistPos, const SEED_UPPER::CarPosWithElbow& rightCarPoint, const SEED_UPPER::CarPosWithElbow& leftCarPoint);
   SEED_UPPER::RETURN_ID* movePTPLifterDualArmCartesianAbsSetRedunJoint(const SEED_UPPER::Lifter& lifterPos, const SEED_UPPER::RPY& waistPos, const SEED_UPPER::CarPosWithElbow& rightCarPoint, const SEED_UPPER::CarPosWithElbow& leftCarPoint);
   SEED_UPPER::RETURN_ID* movePTPLifterDualArmCartesianRelSetRedunJoint(const SEED_UPPER::Lifter& lifterPos, const SEED_UPPER::RPY& waistPos, const SEED_UPPER::CarPosWithElbow& rightCarPoint, const SEED_UPPER::CarPosWithElbow& leftCarPoint);
   SEED_UPPER::RETURN_ID* moveLinearLifterDualArmCartesianAbs(const SEED_UPPER::EEPos& rightCarPoint, const SEED_UPPER::EEPos& leftCarPoint);
   SEED_UPPER::RETURN_ID* moveLinearLifterDualArmCartesianRel(const SEED_UPPER::EEPos& rightCarPoint, const SEED_UPPER::EEPos& leftCarPoint);
   SEED_UPPER::RETURN_ID* movePTPLifterDualArmCartesianAbs(const SEED_UPPER::EEPos& rightCarPoint, const SEED_UPPER::EEPos& leftCarPoint);
   SEED_UPPER::RETURN_ID* movePTPLifterDualArmCartesianRel(const SEED_UPPER::EEPos& rightCarPoint, const SEED_UPPER::EEPos& leftCarPoint);
   SEED_UPPER::RETURN_ID* movePTPLifterDualArmJointAbs(const SEED_UPPER::Lifter& lifterPos, const SEED_UPPER::RPY& waistPos, const SEED_UPPER::JointPos& rightJointPoint, const SEED_UPPER::JointPos& leftJointPoint);
   SEED_UPPER::RETURN_ID* movePTPLifterDualArmJointRel(const SEED_UPPER::Lifter& lifterPos, const SEED_UPPER::RPY& waistPos, const SEED_UPPER::JointPos& rightJointPoint, const SEED_UPPER::JointPos& leftJointPoint);
   SEED_UPPER::RETURN_ID* movePTPLIWARArmJointAbsCmdCycle(const SEED_UPPER::JointPos& jointPoint);
   SEED_UPPER::RETURN_ID* movePTPLIWALArmJointAbsCmdCycle(const SEED_UPPER::JointPos& jointPoint);
   SEED_UPPER::RETURN_ID* movePTPDualArmJointAbsCmdCycle(const SEED_UPPER::Lifter& lifterPos, const SEED_UPPER::RPY& waistPos, const SEED_UPPER::JointPos& rightJointPoint, const SEED_UPPER::JointPos& leftJointPoint);
   SEED_UPPER::RETURN_ID* solveLIWARArmIkSetRedunJoint(const SEED_UPPER::CarPosWithLifterWaistElbow& carPoint, const SEED_UPPER::JointPos& nowJointPos, SEED_UPPER::JointPos_out jointPoint);
   SEED_UPPER::RETURN_ID* solveLIWALArmIkSetRedunJoint(const SEED_UPPER::CarPosWithLifterWaistElbow& carPoint, const SEED_UPPER::JointPos& nowJointPos, SEED_UPPER::JointPos_out jointPoint);
   SEED_UPPER::RETURN_ID* solveLIWARArmIk(const SEED_UPPER::EEPos& carPoint, const SEED_UPPER::JointPos& nowJointPos, SEED_UPPER::JointPos_out jointPoint);
   SEED_UPPER::RETURN_ID* solveLIWALArmIk(const SEED_UPPER::EEPos& carPoint, const SEED_UPPER::JointPos& nowJointPos, SEED_UPPER::JointPos_out jointPoint);
   SEED_UPPER::RETURN_ID* solveLIWARArmFk(const SEED_UPPER::JointPos& jointPoint, SEED_UPPER::EEPos& carPoint);
   SEED_UPPER::RETURN_ID* solveLIWALArmFk(const SEED_UPPER::JointPos& jointPoint, SEED_UPPER::EEPos& carPoint);
  void setCompPtr(SeedUpperBodyRTC* ptr){m_rtcPtr=ptr;}
};



#endif // SEEDUPPERINTERFACE_MIDDLELEVELSVC_IMPL_H


