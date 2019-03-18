// -*-C++-*-
/*!
 * @file  ManipulationPathGeneratorInterfaceSVC_impl.h
 * @brief Service implementation header of ManipulationPathGeneratorInterface.idl
 *
 */

#include "BasicDataTypeSkel.h"

#include "ManipulationPathGeneratorInterfaceSkel.h"

#include "SeedArmPathGenerator.h"

#ifndef MANIPULATIONPATHGENERATORINTERFACESVC_IMPL_H
#define MANIPULATIONPATHGENERATORINTERFACESVC_IMPL_H

//アーム第1軸モータの可動範囲
#define	Angle1_LimitMax	85
#define	Angle1_LimitMin	0
//アーム第2軸モータの可動範囲
#define	Angle2_LimitMax	85
#define	Angle2_LimitMin 0
//アーム第3軸モータの可動範囲
#define	Angle3_LimitMax	120
#define	Angle3_LimitMin -120
//アーム第4軸モータの可動範囲
#define	Angle4_LimitMax	39
#define	Angle4_LimitMin -9
//アーム第5軸モータの可動範囲
#define	Angle5_LimitMax	8
#define	Angle5_LimitMin -8
//アーム第6軸モータの可動範囲
#define	Angle6_LimitMax	89
#define	Angle6_LimitMin	-20
//アーム第7軸モータの可動範囲
#define	Angle7_LimitMax	90
#define	Angle7_LimitMin 0
//アーム第8軸モータの可動範囲
#define	Angle8_LimitMax	135
#define	Angle8_LimitMin	-135
//アーム第9軸モータの可動範囲
#define	Angle9_LimitMax	180
#define	Angle9_LimitMin	0
//アーム第10軸モータの可動範囲
#define Angle10_LimitMax 135
#define Angle10_LimitMin -135
//アーム第11軸モータの可動範囲
#define Angle11_LimitMax 40
#define Angle11_LimitMin -80
//アーム第12軸モータの可動範囲
#define Angle12_LimitMax 180
#define Angle12_LimitMin -180


class SeedArmPathGenerator;

typedef struct
{
  double Upper;
  double Lower;
}Limit;

/*!
 * @class Manipulation_PathGeneratorInterfaceSVC_impl
 * Example class implementing IDL interface Manipulation::PathGeneratorInterface
 */
class Manipulation_PathGeneratorInterfaceSVC_impl
 : public virtual POA_Manipulation::PathGeneratorInterface,
   public virtual PortableServer::RefCountServantBase
{
 private:
   // Make sure all instances are built on the heap by making the
   // destructor non-public
   //virtual ~Manipulation_PathGeneratorInterfaceSVC_impl();
  SeedArmPathGenerator* m_rtcPtr;
  Limit SeedArmJointLimit[12];
  
 public:
  /*!
   * @brief standard constructor
   */
   Manipulation_PathGeneratorInterfaceSVC_impl();
  /*!
   * @brief destructor
   */
   virtual ~Manipulation_PathGeneratorInterfaceSVC_impl();

   // attributes and operations
   Manipulation::RETURN_ID* JointSpaceGenerateRightArmMotion(const Manipulation::JointAngleSeq& goalJointPos);
   Manipulation::RETURN_ID* JointSpaceGenerateRightArmViaMotion(const Manipulation::ViaPosSeq& viaJointPos, const Manipulation::JointAngleSeq& goalJointPos);
   Manipulation::RETURN_ID* JointSpaceGenerateLeftArmMotion(const Manipulation::JointAngleSeq& goalJointPos);
   Manipulation::RETURN_ID* JointSpaceGenerateLeftArmViaMotion(const Manipulation::ViaPosSeq& viaJointPos, const Manipulation::JointAngleSeq& goalJointPos);
   Manipulation::RETURN_ID* JointSpaceGenerateDualArmMotion(const Manipulation::DualUpperJoint& goalJointPos);
   Manipulation::RETURN_ID* JointSpaceGenerateDualArmViaMotion(const Manipulation::ViaDualUpperJointSeq& viaJointPos, const Manipulation::DualUpperJoint& goalJointPos);
  void setCompPtr(SeedArmPathGenerator* ptr){m_rtcPtr=ptr;}

};



#endif // MANIPULATIONPATHGENERATORINTERFACESVC_IMPL_H


