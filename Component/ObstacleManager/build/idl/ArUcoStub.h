// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file ArUcoStub.h 
 * @brief ArUco client stub header wrapper code
 * @date Mon Mar 18 16:11:03 2019 
 *
 */

#ifndef _ARUCOSTUB_H
#define _ARUCOSTUB_H



#include <rtm/config_rtc.h>
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#if   defined ORB_IS_TAO
#  include "ArUcoC.h"
#elif defined ORB_IS_OMNIORB
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#    undef USE_stub_in_nt_dll
#  endif
#  include "ArUco.hh"
#elif defined ORB_IS_MICO
#  include "ArUco.h"
#elif defined ORB_IS_ORBIT2
#  include "ArUco-cpp-stubs.h"
#elif defined ORB_IS_RTORB
#  include "ArUco.h"
#else
#  error "NO ORB defined"
#endif

#endif // _ARUCOSTUB_H
