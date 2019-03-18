// This file is generated by omniidl (C++ backend)- omniORB_4_1. Do not edit.

#include "SeedUpperInterface_DataType.hh"
#include <omniORB4/IOP_S.h>
#include <omniORB4/IOP_C.h>
#include <omniORB4/callDescriptor.h>
#include <omniORB4/callHandle.h>
#include <omniORB4/objTracker.h>


OMNI_USING_NAMESPACE(omni)

static const char* _0RL_library_version = omniORB_4_1;



void
SEED_UPPER::LimitValue::operator>>= (cdrStream &_n) const
{
  upper >>= _n;
  lower >>= _n;

}

void
SEED_UPPER::LimitValue::operator<<= (cdrStream &_n)
{
  (::CORBA::Double&)upper <<= _n;
  (::CORBA::Double&)lower <<= _n;

}

void
SEED_UPPER::RPY::operator>>= (cdrStream &_n) const
{
  roll >>= _n;
  pitch >>= _n;
  yaw >>= _n;

}

void
SEED_UPPER::RPY::operator<<= (cdrStream &_n)
{
  (::CORBA::Double&)roll <<= _n;
  (::CORBA::Double&)pitch <<= _n;
  (::CORBA::Double&)yaw <<= _n;

}

void
SEED_UPPER::Lifter::operator>>= (cdrStream &_n) const
{
  bottom >>= _n;
  top >>= _n;

}

void
SEED_UPPER::Lifter::operator<<= (cdrStream &_n)
{
  (::CORBA::Double&)bottom <<= _n;
  (::CORBA::Double&)top <<= _n;

}

void
SEED_UPPER::RETURN_ID::operator>>= (cdrStream &_n) const
{
  id >>= _n;
  _n.marshalString(comment,0);

}

void
SEED_UPPER::RETURN_ID::operator<<= (cdrStream &_n)
{
  (::CORBA::Long&)id <<= _n;
  comment = _n.unmarshalString(0);

}

_init_in_def_( const ::CORBA::Long SEED_UPPER::OK = 0; )

_init_in_def_( const ::CORBA::Long SEED_UPPER::NG = -1; )

_init_in_def_( const ::CORBA::Long SEED_UPPER::STATUS_ERR = -2; )

_init_in_def_( const ::CORBA::Long SEED_UPPER::VALUE_ERR = -3; )

_init_in_def_( const ::CORBA::Long SEED_UPPER::NOT_SV_ON_ERR = -4; )

_init_in_def_( const ::CORBA::Long SEED_UPPER::FULL_MOTION_QUEUE_ERR = -5; )

_init_in_def_( const ::CORBA::Long SEED_UPPER::NOT_IMPLEMENTED = -6; )

void
SEED_UPPER::TimedJointPos::operator>>= (cdrStream &_n) const
{
  (const RTC::Time&) tm >>= _n;
  (const JointPos&) pos >>= _n;

}

void
SEED_UPPER::TimedJointPos::operator<<= (cdrStream &_n)
{
  (RTC::Time&)tm <<= _n;
  (JointPos&)pos <<= _n;

}

