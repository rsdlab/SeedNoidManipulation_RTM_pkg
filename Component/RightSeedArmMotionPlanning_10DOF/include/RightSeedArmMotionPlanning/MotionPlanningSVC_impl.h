// -*-C++-*-
/*!
 * @file  MotionPlanningSVC_impl.h
 * @brief Service implementation header of MotionPlanning.idl
 *
 */

#include "BasicDataTypeSkel.h"
#include "ExtendedDataTypesSkel.h"

#include "MotionPlanningSkel.h"

#include "RightSeedArmMotionPlanning.h"

#ifndef MOTIONPLANNINGSVC_IMPL_H
#define MOTIONPLANNINGSVC_IMPL_H

#include "LibSeednoidUpperUnit1.h"
#include "Collision.h"
#include "manipulator.h"
#include "ikfast.h"
#include "seednoid_ikfast.h"
#define _USE_MATH_DEFINES
#include<iostream>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <sys/time.h>
#include <math.h>
#include <flann/flann.hpp>

class RightSeedArmMotionPlanning;

/*!
 * @class Planning_MotionPlanningInterfaceSVC_impl
 * Example class implementing IDL interface Planning::MotionPlanningInterface
 */
class Planning_MotionPlanningInterfaceSVC_impl
 : public virtual POA_Planning::MotionPlanningInterface,
   public virtual PortableServer::RefCountServantBase
{
 private:
   // Make sure all instances are built on the heap by making the
   // destructor non-public
   //virtual ~Planning_MotionPlanningInterfaceSVC_impl();
 RightSeedArmMotionPlanning* m_rtcPtr;
  int ObstacleNum;
  std::vector<AABB> aabb;
 public:
  /*!
   * @brief standard constructor
   */
   Planning_MotionPlanningInterfaceSVC_impl();
  /*!
   * @brief destructor
   */
   virtual ~Planning_MotionPlanningInterfaceSVC_impl();

   // attributes and operations
   ::CORBA::Long MotionGenerate_Joint(const Planning::theta& q_goal);
   ::CORBA::Long MotionGenerate(const Planning::ManipPos& EEfPos);
   void setCompPtr(RightSeedArmMotionPlanning* ptr){m_rtcPtr=ptr;}
   int CollisionCheck(TenDOF joint, double lifterBottom, double lifterTop, std::vector<AABB> aabb, int ObNum);
};



#endif // MOTIONPLANNINGSVC_IMPL_H


