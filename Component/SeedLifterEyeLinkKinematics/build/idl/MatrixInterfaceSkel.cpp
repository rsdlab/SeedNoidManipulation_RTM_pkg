// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file MatrixInterfaceSkel.cpp 
 * @brief MatrixInterface server skeleton wrapper
 * @date Mon Mar 18 16:10:25 2019 
 *
 */

#include "MatrixInterfaceSkel.h"

#if defined ORB_IS_TAO
#  include "MatrixInterfaceC.cpp"
#  include "MatrixInterfaceS.cpp"
#elif defined ORB_IS_OMNIORB
#  include "MatrixInterfaceSK.cc"
#  include "MatrixInterfaceDynSK.cc"
#elif defined ORB_IS_MICO
#  include "MatrixInterface.cc"
#  include "MatrixInterface_skel.cc"
#elif defined ORB_IS_ORBIT2
#  include "MatrixInterface-cpp-stubs.cc"
#  include "MatrixInterface-cpp-skels.cc"
#elif defined ORB_IS_RTORB
#  include "OpenRTM-aist-decls.h"
#  include "MatrixInterface-common.c"
#  include "MatrixInterface-stubs.c"
#  include "MatrixInterface-skels.c"
#  include "MatrixInterface-skelimpl.c"
#else
#  error "NO ORB defined"
#endif

// end of MatrixInterfaceSkel.cpp
