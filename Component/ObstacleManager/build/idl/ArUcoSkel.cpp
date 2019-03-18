// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file ArUcoSkel.cpp 
 * @brief ArUco server skeleton wrapper
 * @date Mon Mar 18 16:11:03 2019 
 *
 */

#include "ArUcoSkel.h"

#if defined ORB_IS_TAO
#  include "ArUcoC.cpp"
#  include "ArUcoS.cpp"
#elif defined ORB_IS_OMNIORB
#  include "ArUcoSK.cc"
#  include "ArUcoDynSK.cc"
#elif defined ORB_IS_MICO
#  include "ArUco.cc"
#  include "ArUco_skel.cc"
#elif defined ORB_IS_ORBIT2
#  include "ArUco-cpp-stubs.cc"
#  include "ArUco-cpp-skels.cc"
#elif defined ORB_IS_RTORB
#  include "OpenRTM-aist-decls.h"
#  include "ArUco-common.c"
#  include "ArUco-stubs.c"
#  include "ArUco-skels.c"
#  include "ArUco-skelimpl.c"
#else
#  error "NO ORB defined"
#endif

// end of ArUcoSkel.cpp
