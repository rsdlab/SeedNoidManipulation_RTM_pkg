// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file MotionPlanningSkel.h 
 * @brief MotionPlanning server skeleton header wrapper code
 * @date Mon Mar 18 16:16:00 2019 
 *
 */

#ifndef _MOTIONPLANNINGSKEL_H
#define _MOTIONPLANNINGSKEL_H



#include <rtm/config_rtc.h>
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#if   defined ORB_IS_TAO
#  include "MotionPlanningC.h"
#  include "MotionPlanningS.h"
#elif defined ORB_IS_OMNIORB
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#    undef USE_stub_in_nt_dll
#  endif
#  include "MotionPlanning.hh"
#elif defined ORB_IS_MICO
#  include "MotionPlanning.h"
#elif defined ORB_IS_ORBIT2
#  include "/MotionPlanning-cpp-stubs.h"
#  include "/MotionPlanning-cpp-skels.h"
#elif defined ORB_IS_RTORB
#  include "MotionPlanning.h"
#else
#  error "NO ORB defined"
#endif

#endif // _MOTIONPLANNINGSKEL_H
