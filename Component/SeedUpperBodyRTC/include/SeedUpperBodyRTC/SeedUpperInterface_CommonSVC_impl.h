// -*-C++-*-
/*!
 * @file  SeedUpperInterface_CommonSVC_impl.h
 * @brief Service implementation header of SeedUpperInterface_Common.idl
 *
 */

#include "SeedUpperInterface_DataTypeSkel.h"
#include "BasicDataTypeSkel.h"

#include "SeedUpperInterface_CommonSkel.h"

#include "SeedUpperBodyRTC.h"

#ifndef SEEDUPPERINTERFACE_COMMONSVC_IMPL_H
#define SEEDUPPERINTERFACE_COMMONSVC_IMPL_H

#include "LibSeednoidUpper.h"

class SeedUpperBodyRTC;

/*!
 * @class SEED_UPPER_SeedUpperInterface_CommonSVC_impl
 * Example class implementing IDL interface SEED_UPPER::SeedUpperInterface_Common
 */
class SEED_UPPER_SeedUpperInterface_CommonSVC_impl
 : public virtual POA_SEED_UPPER::SeedUpperInterface_Common,
   public virtual PortableServer::RefCountServantBase
{
 private:
   // Make sure all instances are built on the heap by making the
   // destructor non-public
   //virtual ~SEED_UPPER_SeedUpperInterface_CommonSVC_impl();
  SeedUpperBodyRTC* m_rtcPtr;
  
 public:
  /*!
   * @brief standard constructor
   */
   SEED_UPPER_SeedUpperInterface_CommonSVC_impl();
  /*!
   * @brief destructor
   */
   virtual ~SEED_UPPER_SeedUpperInterface_CommonSVC_impl();

   // attributes and operations
   SEED_UPPER::RETURN_ID* getFeedbackPosAllJoint(SEED_UPPER::Lifter& lifterPos, SEED_UPPER::RPY& WaistPos, SEED_UPPER::RPY& NeckPos, SEED_UPPER::JointPos_out rightPos, SEED_UPPER::JointPos_out leftPos);
   SEED_UPPER::RETURN_ID* getFeedbackPosLIWARArm(SEED_UPPER::JointPos_out pos);
   SEED_UPPER::RETURN_ID* getFeedbackPosLIWALArm(SEED_UPPER::JointPos_out pos);
   SEED_UPPER::RETURN_ID* getManipInfo(SEED_UPPER::ManipInfo_out mInfo);
   SEED_UPPER::RETURN_ID* getLIWARArmInfo(SEED_UPPER::ManipInfo_out mInfo);
   SEED_UPPER::RETURN_ID* getLIWALArmInfo(SEED_UPPER::ManipInfo_out mInfo);
   SEED_UPPER::RETURN_ID* getSoftLimitJoint(SEED_UPPER::LimitSeq_out softLimit);
   SEED_UPPER::RETURN_ID* getState(SEED_UPPER::ULONG& state);
   SEED_UPPER::RETURN_ID* servoOFF();
   SEED_UPPER::RETURN_ID* servoON();
   SEED_UPPER::RETURN_ID* setSoftLimitJoint(const SEED_UPPER::LimitSeq& softLimit);
  void setCompPtr(SeedUpperBodyRTC* ptr){m_rtcPtr=ptr;}
};



#endif // SEEDUPPERINTERFACE_COMMONSVC_IMPL_H


