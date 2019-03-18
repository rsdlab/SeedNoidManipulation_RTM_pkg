// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file MatrixInterfaceSkel.h 
 * @brief MatrixInterface server skeleton header wrapper code
 * @date Mon Mar 18 16:09:59 2019 
 *
 */

#ifndef _MATRIXINTERFACESKEL_H
#define _MATRIXINTERFACESKEL_H



#include <rtm/config_rtc.h>
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#if   defined ORB_IS_TAO
#  include "MatrixInterfaceC.h"
#  include "MatrixInterfaceS.h"
#elif defined ORB_IS_OMNIORB
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#    undef USE_stub_in_nt_dll
#  endif
#  include "MatrixInterface.hh"
#elif defined ORB_IS_MICO
#  include "MatrixInterface.h"
#elif defined ORB_IS_ORBIT2
#  include "/MatrixInterface-cpp-stubs.h"
#  include "/MatrixInterface-cpp-skels.h"
#elif defined ORB_IS_RTORB
#  include "MatrixInterface.h"
#else
#  error "NO ORB defined"
#endif

#endif // _MATRIXINTERFACESKEL_H
