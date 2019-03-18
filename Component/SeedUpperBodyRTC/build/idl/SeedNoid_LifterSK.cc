// This file is generated by omniidl (C++ backend)- omniORB_4_1. Do not edit.

#include "SeedNoid_Lifter.hh"
#include <omniORB4/IOP_S.h>
#include <omniORB4/IOP_C.h>
#include <omniORB4/callDescriptor.h>
#include <omniORB4/callHandle.h>
#include <omniORB4/objTracker.h>


OMNI_USING_NAMESPACE(omni)

static const char* _0RL_library_version = omniORB_4_1;



void
SeedNoid_Lifter::LifterAngle::operator>>= (cdrStream &_n) const
{
  top >>= _n;
  bottom >>= _n;

}

void
SeedNoid_Lifter::LifterAngle::operator<<= (cdrStream &_n)
{
  (::CORBA::Double&)top <<= _n;
  (::CORBA::Double&)bottom <<= _n;

}

void
SeedNoid_Lifter::LimitValue::operator>>= (cdrStream &_n) const
{
  upper >>= _n;
  lower >>= _n;

}

void
SeedNoid_Lifter::LimitValue::operator<<= (cdrStream &_n)
{
  (::CORBA::Double&)upper <<= _n;
  (::CORBA::Double&)lower <<= _n;

}

SeedNoid_Lifter::LifterPose_ptr SeedNoid_Lifter::LifterPose_Helper::_nil() {
  return ::SeedNoid_Lifter::LifterPose::_nil();
}

::CORBA::Boolean SeedNoid_Lifter::LifterPose_Helper::is_nil(::SeedNoid_Lifter::LifterPose_ptr p) {
  return ::CORBA::is_nil(p);

}

void SeedNoid_Lifter::LifterPose_Helper::release(::SeedNoid_Lifter::LifterPose_ptr p) {
  ::CORBA::release(p);
}

void SeedNoid_Lifter::LifterPose_Helper::marshalObjRef(::SeedNoid_Lifter::LifterPose_ptr obj, cdrStream& s) {
  ::SeedNoid_Lifter::LifterPose::_marshalObjRef(obj, s);
}

SeedNoid_Lifter::LifterPose_ptr SeedNoid_Lifter::LifterPose_Helper::unmarshalObjRef(cdrStream& s) {
  return ::SeedNoid_Lifter::LifterPose::_unmarshalObjRef(s);
}

void SeedNoid_Lifter::LifterPose_Helper::duplicate(::SeedNoid_Lifter::LifterPose_ptr obj) {
  if( obj && !obj->_NP_is_nil() )  omni::duplicateObjRef(obj);
}

SeedNoid_Lifter::LifterPose_ptr
SeedNoid_Lifter::LifterPose::_duplicate(::SeedNoid_Lifter::LifterPose_ptr obj)
{
  if( obj && !obj->_NP_is_nil() )  omni::duplicateObjRef(obj);
  return obj;
}

SeedNoid_Lifter::LifterPose_ptr
SeedNoid_Lifter::LifterPose::_narrow(::CORBA::Object_ptr obj)
{
  if( !obj || obj->_NP_is_nil() || obj->_NP_is_pseudo() ) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_realNarrow(_PD_repoId);
  return e ? e : _nil();
}


SeedNoid_Lifter::LifterPose_ptr
SeedNoid_Lifter::LifterPose::_unchecked_narrow(::CORBA::Object_ptr obj)
{
  if( !obj || obj->_NP_is_nil() || obj->_NP_is_pseudo() ) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_uncheckedNarrow(_PD_repoId);
  return e ? e : _nil();
}

SeedNoid_Lifter::LifterPose_ptr
SeedNoid_Lifter::LifterPose::_nil()
{
#ifdef OMNI_UNLOADABLE_STUBS
  static _objref_LifterPose _the_nil_obj;
  return &_the_nil_obj;
#else
  static _objref_LifterPose* _the_nil_ptr = 0;
  if( !_the_nil_ptr ) {
    omni::nilRefLock().lock();
    if( !_the_nil_ptr ) {
      _the_nil_ptr = new _objref_LifterPose;
      registerNilCorbaObject(_the_nil_ptr);
    }
    omni::nilRefLock().unlock();
  }
  return _the_nil_ptr;
#endif
}

const char* SeedNoid_Lifter::LifterPose::_PD_repoId = "IDL:SeedNoid_Lifter/LifterPose:1.0";


SeedNoid_Lifter::_objref_LifterPose::~_objref_LifterPose() {
  
}


SeedNoid_Lifter::_objref_LifterPose::_objref_LifterPose(omniIOR* ior, omniIdentity* id) :
   omniObjRef(::SeedNoid_Lifter::LifterPose::_PD_repoId, ior, id, 1)
   
   
{
  _PR_setobj(this);
}

void*
SeedNoid_Lifter::_objref_LifterPose::_ptrToObjRef(const char* id)
{
  if( id == ::SeedNoid_Lifter::LifterPose::_PD_repoId )
    return (::SeedNoid_Lifter::LifterPose_ptr) this;
  
  if( id == ::CORBA::Object::_PD_repoId )
    return (::CORBA::Object_ptr) this;

  if( omni::strMatch(id, ::SeedNoid_Lifter::LifterPose::_PD_repoId) )
    return (::SeedNoid_Lifter::LifterPose_ptr) this;
  
  if( omni::strMatch(id, ::CORBA::Object::_PD_repoId) )
    return (::CORBA::Object_ptr) this;

  return 0;
}

// Proxy call descriptor class. Mangled signature:
//  _cSeedNoid__Lifter_mRETURN__VALUE_i_cSeedNoid__Lifter_mLifterAngle
class _0RL_cd_6272dc9557a58e30_00000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_6272dc9557a58e30_00000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  SeedNoid_Lifter::LifterAngle arg_0_;
  const SeedNoid_Lifter::LifterAngle* arg_0;
  SeedNoid_Lifter::RETURN_VALUE result;
};

void _0RL_cd_6272dc9557a58e30_00000000::marshalArguments(cdrStream& _n)
{
  (const SeedNoid_Lifter::LifterAngle&) *arg_0 >>= _n;

}

void _0RL_cd_6272dc9557a58e30_00000000::unmarshalArguments(cdrStream& _n)
{
  (SeedNoid_Lifter::LifterAngle&)arg_0_ <<= _n;
  arg_0 = &arg_0_;

}

void _0RL_cd_6272dc9557a58e30_00000000::marshalReturnedValues(cdrStream& _n)
{
  result >>= _n;

}

void _0RL_cd_6272dc9557a58e30_00000000::unmarshalReturnedValues(cdrStream& _n)
{
  (SeedNoid_Lifter::RETURN_VALUE&)result <<= _n;

}

const char* const _0RL_cd_6272dc9557a58e30_00000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_6272dc9557a58e30_10000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_6272dc9557a58e30_00000000* tcd = (_0RL_cd_6272dc9557a58e30_00000000*)cd;
  SeedNoid_Lifter::_impl_LifterPose* impl = (SeedNoid_Lifter::_impl_LifterPose*) svnt->_ptrToInterface(SeedNoid_Lifter::LifterPose::_PD_repoId);
  tcd->result = impl->sendLifterAngle(*tcd->arg_0);


}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter::_objref_LifterPose::sendLifterAngle(const ::SeedNoid_Lifter::LifterAngle& targetLifterAngle)
{
  _0RL_cd_6272dc9557a58e30_00000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_10000000, "sendLifterAngle", 16);
  _call_desc.arg_0 = &(::SeedNoid_Lifter::LifterAngle&) targetLifterAngle;

  _invoke(_call_desc);
  return _call_desc.result;


}
// Proxy call descriptor class. Mangled signature:
//  _cSeedNoid__Lifter_mRETURN__VALUE_i_cRTC_mPoint3D
class _0RL_cd_6272dc9557a58e30_20000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_6272dc9557a58e30_20000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  RTC::Point3D arg_0_;
  const RTC::Point3D* arg_0;
  SeedNoid_Lifter::RETURN_VALUE result;
};

void _0RL_cd_6272dc9557a58e30_20000000::marshalArguments(cdrStream& _n)
{
  (const RTC::Point3D&) *arg_0 >>= _n;

}

void _0RL_cd_6272dc9557a58e30_20000000::unmarshalArguments(cdrStream& _n)
{
  (RTC::Point3D&)arg_0_ <<= _n;
  arg_0 = &arg_0_;

}

void _0RL_cd_6272dc9557a58e30_20000000::marshalReturnedValues(cdrStream& _n)
{
  result >>= _n;

}

void _0RL_cd_6272dc9557a58e30_20000000::unmarshalReturnedValues(cdrStream& _n)
{
  (SeedNoid_Lifter::RETURN_VALUE&)result <<= _n;

}

const char* const _0RL_cd_6272dc9557a58e30_20000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_6272dc9557a58e30_30000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_6272dc9557a58e30_20000000* tcd = (_0RL_cd_6272dc9557a58e30_20000000*)cd;
  SeedNoid_Lifter::_impl_LifterPose* impl = (SeedNoid_Lifter::_impl_LifterPose*) svnt->_ptrToInterface(SeedNoid_Lifter::LifterPose::_PD_repoId);
  tcd->result = impl->sendLifterPose(*tcd->arg_0);


}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter::_objref_LifterPose::sendLifterPose(const ::RTC::Point3D& targetLifterPose)
{
  _0RL_cd_6272dc9557a58e30_20000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_30000000, "sendLifterPose", 15);
  _call_desc.arg_0 = &(::RTC::Point3D&) targetLifterPose;

  _invoke(_call_desc);
  return _call_desc.result;


}
// Proxy call descriptor class. Mangled signature:
//  _cSeedNoid__Lifter_mRETURN__VALUE_o_cSeedNoid__Lifter_mLifterAngle
class _0RL_cd_6272dc9557a58e30_40000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_6272dc9557a58e30_40000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  
  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  SeedNoid_Lifter::LifterAngle arg_0_;
  SeedNoid_Lifter::LifterAngle* arg_0;
  SeedNoid_Lifter::RETURN_VALUE result;
};

void _0RL_cd_6272dc9557a58e30_40000000::marshalReturnedValues(cdrStream& _n)
{
  result >>= _n;
  (const SeedNoid_Lifter::LifterAngle&) *arg_0 >>= _n;

}

void _0RL_cd_6272dc9557a58e30_40000000::unmarshalReturnedValues(cdrStream& _n)
{
  (SeedNoid_Lifter::RETURN_VALUE&)result <<= _n;
  (SeedNoid_Lifter::LifterAngle&)*arg_0 <<= _n;

}

const char* const _0RL_cd_6272dc9557a58e30_40000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_6272dc9557a58e30_50000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_6272dc9557a58e30_40000000* tcd = (_0RL_cd_6272dc9557a58e30_40000000*)cd;
  SeedNoid_Lifter::_impl_LifterPose* impl = (SeedNoid_Lifter::_impl_LifterPose*) svnt->_ptrToInterface(SeedNoid_Lifter::LifterPose::_PD_repoId);
  tcd->result = impl->getLifterAngle(*tcd->arg_0);


}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter::_objref_LifterPose::getLifterAngle(::SeedNoid_Lifter::LifterAngle& currentLifterAngle)
{
  _0RL_cd_6272dc9557a58e30_40000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_50000000, "getLifterAngle", 15);
  _call_desc.arg_0 = &(::SeedNoid_Lifter::LifterAngle&) currentLifterAngle;

  _invoke(_call_desc);
  return _call_desc.result;


}
// Proxy call descriptor class. Mangled signature:
//  _cSeedNoid__Lifter_mRETURN__VALUE_o_cRTC_mPoint3D
class _0RL_cd_6272dc9557a58e30_60000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_6272dc9557a58e30_60000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  
  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  RTC::Point3D arg_0_;
  RTC::Point3D* arg_0;
  SeedNoid_Lifter::RETURN_VALUE result;
};

void _0RL_cd_6272dc9557a58e30_60000000::marshalReturnedValues(cdrStream& _n)
{
  result >>= _n;
  (const RTC::Point3D&) *arg_0 >>= _n;

}

void _0RL_cd_6272dc9557a58e30_60000000::unmarshalReturnedValues(cdrStream& _n)
{
  (SeedNoid_Lifter::RETURN_VALUE&)result <<= _n;
  (RTC::Point3D&)*arg_0 <<= _n;

}

const char* const _0RL_cd_6272dc9557a58e30_60000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_6272dc9557a58e30_70000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_6272dc9557a58e30_60000000* tcd = (_0RL_cd_6272dc9557a58e30_60000000*)cd;
  SeedNoid_Lifter::_impl_LifterPose* impl = (SeedNoid_Lifter::_impl_LifterPose*) svnt->_ptrToInterface(SeedNoid_Lifter::LifterPose::_PD_repoId);
  tcd->result = impl->getLifterPose(*tcd->arg_0);


}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter::_objref_LifterPose::getLifterPose(::RTC::Point3D& currentLifterPose)
{
  _0RL_cd_6272dc9557a58e30_60000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_70000000, "getLifterPose", 14);
  _call_desc.arg_0 = &(::RTC::Point3D&) currentLifterPose;

  _invoke(_call_desc);
  return _call_desc.result;


}
// Proxy call descriptor class. Mangled signature:
//  _cSeedNoid__Lifter_mRETURN__VALUE_o_cSeedNoid__Lifter_mLimitSeq
class _0RL_cd_6272dc9557a58e30_80000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_6272dc9557a58e30_80000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  
  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  SeedNoid_Lifter::LimitSeq_var arg_0;
  SeedNoid_Lifter::RETURN_VALUE result;
};

void _0RL_cd_6272dc9557a58e30_80000000::marshalReturnedValues(cdrStream& _n)
{
  result >>= _n;
  (const SeedNoid_Lifter::LimitSeq&) arg_0 >>= _n;

}

void _0RL_cd_6272dc9557a58e30_80000000::unmarshalReturnedValues(cdrStream& _n)
{
  (SeedNoid_Lifter::RETURN_VALUE&)result <<= _n;
  arg_0 = new SeedNoid_Lifter::LimitSeq;
  (SeedNoid_Lifter::LimitSeq&)arg_0 <<= _n;

}

const char* const _0RL_cd_6272dc9557a58e30_80000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_6272dc9557a58e30_90000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_6272dc9557a58e30_80000000* tcd = (_0RL_cd_6272dc9557a58e30_80000000*)cd;
  SeedNoid_Lifter::_impl_LifterPose* impl = (SeedNoid_Lifter::_impl_LifterPose*) svnt->_ptrToInterface(SeedNoid_Lifter::LifterPose::_PD_repoId);
  tcd->result = impl->getSoftLimitLifter(tcd->arg_0.out());


}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter::_objref_LifterPose::getSoftLimitLifter(::SeedNoid_Lifter::LimitSeq_out softLimit)
{
  _0RL_cd_6272dc9557a58e30_80000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_90000000, "getSoftLimitLifter", 19);


  _invoke(_call_desc);
  softLimit = _call_desc.arg_0._retn();
  return _call_desc.result;


}
// Proxy call descriptor class. Mangled signature:
//  _cSeedNoid__Lifter_mRETURN__VALUE_i_cSeedNoid__Lifter_mLimitSeq
class _0RL_cd_6272dc9557a58e30_a0000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_6272dc9557a58e30_a0000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  SeedNoid_Lifter::LimitSeq_var arg_0_;
  const SeedNoid_Lifter::LimitSeq* arg_0;
  SeedNoid_Lifter::RETURN_VALUE result;
};

void _0RL_cd_6272dc9557a58e30_a0000000::marshalArguments(cdrStream& _n)
{
  (const SeedNoid_Lifter::LimitSeq&) *arg_0 >>= _n;

}

void _0RL_cd_6272dc9557a58e30_a0000000::unmarshalArguments(cdrStream& _n)
{
  arg_0_ = new SeedNoid_Lifter::LimitSeq;
  (SeedNoid_Lifter::LimitSeq&)arg_0_ <<= _n;
  arg_0 = &arg_0_.in();

}

void _0RL_cd_6272dc9557a58e30_a0000000::marshalReturnedValues(cdrStream& _n)
{
  result >>= _n;

}

void _0RL_cd_6272dc9557a58e30_a0000000::unmarshalReturnedValues(cdrStream& _n)
{
  (SeedNoid_Lifter::RETURN_VALUE&)result <<= _n;

}

const char* const _0RL_cd_6272dc9557a58e30_a0000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_6272dc9557a58e30_b0000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_6272dc9557a58e30_a0000000* tcd = (_0RL_cd_6272dc9557a58e30_a0000000*)cd;
  SeedNoid_Lifter::_impl_LifterPose* impl = (SeedNoid_Lifter::_impl_LifterPose*) svnt->_ptrToInterface(SeedNoid_Lifter::LifterPose::_PD_repoId);
  tcd->result = impl->setSoftLimitLifter(*tcd->arg_0);


}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter::_objref_LifterPose::setSoftLimitLifter(const ::SeedNoid_Lifter::LimitSeq& softLimit)
{
  _0RL_cd_6272dc9557a58e30_a0000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_b0000000, "setSoftLimitLifter", 19);
  _call_desc.arg_0 = &(::SeedNoid_Lifter::LimitSeq&) softLimit;

  _invoke(_call_desc);
  return _call_desc.result;


}
// Proxy call descriptor class. Mangled signature:
//  _cSeedNoid__Lifter_mRETURN__VALUE_o_cSeedNoid__Lifter_mDoubleSeq
class _0RL_cd_6272dc9557a58e30_c0000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_6272dc9557a58e30_c0000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  
  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  SeedNoid_Lifter::DoubleSeq_var arg_0;
  SeedNoid_Lifter::RETURN_VALUE result;
};

void _0RL_cd_6272dc9557a58e30_c0000000::marshalReturnedValues(cdrStream& _n)
{
  result >>= _n;
  (const SeedNoid_Lifter::DoubleSeq&) arg_0 >>= _n;

}

void _0RL_cd_6272dc9557a58e30_c0000000::unmarshalReturnedValues(cdrStream& _n)
{
  (SeedNoid_Lifter::RETURN_VALUE&)result <<= _n;
  arg_0 = new SeedNoid_Lifter::DoubleSeq;
  (SeedNoid_Lifter::DoubleSeq&)arg_0 <<= _n;

}

const char* const _0RL_cd_6272dc9557a58e30_c0000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_6272dc9557a58e30_d0000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_6272dc9557a58e30_c0000000* tcd = (_0RL_cd_6272dc9557a58e30_c0000000*)cd;
  SeedNoid_Lifter::_impl_LifterPose* impl = (SeedNoid_Lifter::_impl_LifterPose*) svnt->_ptrToInterface(SeedNoid_Lifter::LifterPose::_PD_repoId);
  tcd->result = impl->getMaxSpeedLifter(tcd->arg_0.out());


}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter::_objref_LifterPose::getMaxSpeedLifter(::SeedNoid_Lifter::DoubleSeq_out speed)
{
  _0RL_cd_6272dc9557a58e30_c0000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_d0000000, "getMaxSpeedLifter", 18);


  _invoke(_call_desc);
  speed = _call_desc.arg_0._retn();
  return _call_desc.result;


}
// Proxy call descriptor class. Mangled signature:
//  _cSeedNoid__Lifter_mRETURN__VALUE_o_cdouble
class _0RL_cd_6272dc9557a58e30_e0000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_6272dc9557a58e30_e0000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  
  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  ::CORBA::Double arg_0;
  SeedNoid_Lifter::RETURN_VALUE result;
};

void _0RL_cd_6272dc9557a58e30_e0000000::marshalReturnedValues(cdrStream& _n)
{
  result >>= _n;
  arg_0 >>= _n;

}

void _0RL_cd_6272dc9557a58e30_e0000000::unmarshalReturnedValues(cdrStream& _n)
{
  (SeedNoid_Lifter::RETURN_VALUE&)result <<= _n;
  (::CORBA::Double&)arg_0 <<= _n;

}

const char* const _0RL_cd_6272dc9557a58e30_e0000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_6272dc9557a58e30_f0000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_6272dc9557a58e30_e0000000* tcd = (_0RL_cd_6272dc9557a58e30_e0000000*)cd;
  SeedNoid_Lifter::_impl_LifterPose* impl = (SeedNoid_Lifter::_impl_LifterPose*) svnt->_ptrToInterface(SeedNoid_Lifter::LifterPose::_PD_repoId);
  tcd->result = impl->getMinAccelTimeLifter(tcd->arg_0);


}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter::_objref_LifterPose::getMinAccelTimeLifter(::CORBA::Double& aclTime)
{
  _0RL_cd_6272dc9557a58e30_e0000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_f0000000, "getMinAccelTimeLifter", 22);


  _invoke(_call_desc);
  aclTime = _call_desc.arg_0;
  return _call_desc.result;


}
// Proxy call descriptor class. Mangled signature:
//  _cSeedNoid__Lifter_mRETURN__VALUE
class _0RL_cd_6272dc9557a58e30_01000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_6272dc9557a58e30_01000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  
  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  SeedNoid_Lifter::RETURN_VALUE result;
};

void _0RL_cd_6272dc9557a58e30_01000000::marshalReturnedValues(cdrStream& _n)
{
  result >>= _n;

}

void _0RL_cd_6272dc9557a58e30_01000000::unmarshalReturnedValues(cdrStream& _n)
{
  (SeedNoid_Lifter::RETURN_VALUE&)result <<= _n;

}

const char* const _0RL_cd_6272dc9557a58e30_01000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_6272dc9557a58e30_11000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_6272dc9557a58e30_01000000* tcd = (_0RL_cd_6272dc9557a58e30_01000000*)cd;
  SeedNoid_Lifter::_impl_LifterPose* impl = (SeedNoid_Lifter::_impl_LifterPose*) svnt->_ptrToInterface(SeedNoid_Lifter::LifterPose::_PD_repoId);
  tcd->result = impl->pause();


}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter::_objref_LifterPose::pause()
{
  _0RL_cd_6272dc9557a58e30_01000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_11000000, "pause", 6);


  _invoke(_call_desc);
  return _call_desc.result;


}
// Local call call-back function.
static void
_0RL_lcfn_6272dc9557a58e30_21000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_6272dc9557a58e30_01000000* tcd = (_0RL_cd_6272dc9557a58e30_01000000*)cd;
  SeedNoid_Lifter::_impl_LifterPose* impl = (SeedNoid_Lifter::_impl_LifterPose*) svnt->_ptrToInterface(SeedNoid_Lifter::LifterPose::_PD_repoId);
  tcd->result = impl->resume();


}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter::_objref_LifterPose::resume()
{
  _0RL_cd_6272dc9557a58e30_01000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_21000000, "resume", 7);


  _invoke(_call_desc);
  return _call_desc.result;


}
// Local call call-back function.
static void
_0RL_lcfn_6272dc9557a58e30_31000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_6272dc9557a58e30_01000000* tcd = (_0RL_cd_6272dc9557a58e30_01000000*)cd;
  SeedNoid_Lifter::_impl_LifterPose* impl = (SeedNoid_Lifter::_impl_LifterPose*) svnt->_ptrToInterface(SeedNoid_Lifter::LifterPose::_PD_repoId);
  tcd->result = impl->stop();


}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter::_objref_LifterPose::stop()
{
  _0RL_cd_6272dc9557a58e30_01000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_31000000, "stop", 5);


  _invoke(_call_desc);
  return _call_desc.result;


}
// Proxy call descriptor class. Mangled signature:
//  _cSeedNoid__Lifter_mRETURN__VALUE_i_cdouble
class _0RL_cd_6272dc9557a58e30_41000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_6272dc9557a58e30_41000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  ::CORBA::Double arg_0;
  SeedNoid_Lifter::RETURN_VALUE result;
};

void _0RL_cd_6272dc9557a58e30_41000000::marshalArguments(cdrStream& _n)
{
  arg_0 >>= _n;

}

void _0RL_cd_6272dc9557a58e30_41000000::unmarshalArguments(cdrStream& _n)
{
  (::CORBA::Double&)arg_0 <<= _n;

}

void _0RL_cd_6272dc9557a58e30_41000000::marshalReturnedValues(cdrStream& _n)
{
  result >>= _n;

}

void _0RL_cd_6272dc9557a58e30_41000000::unmarshalReturnedValues(cdrStream& _n)
{
  (SeedNoid_Lifter::RETURN_VALUE&)result <<= _n;

}

const char* const _0RL_cd_6272dc9557a58e30_41000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_6272dc9557a58e30_51000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_6272dc9557a58e30_41000000* tcd = (_0RL_cd_6272dc9557a58e30_41000000*)cd;
  SeedNoid_Lifter::_impl_LifterPose* impl = (SeedNoid_Lifter::_impl_LifterPose*) svnt->_ptrToInterface(SeedNoid_Lifter::LifterPose::_PD_repoId);
  tcd->result = impl->setAccelTimeLifter(tcd->arg_0);


}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter::_objref_LifterPose::setAccelTimeLifter(::CORBA::Double aclTime)
{
  _0RL_cd_6272dc9557a58e30_41000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_51000000, "setAccelTimeLifter", 19);
  _call_desc.arg_0 = aclTime;

  _invoke(_call_desc);
  return _call_desc.result;


}
// Proxy call descriptor class. Mangled signature:
//  _cSeedNoid__Lifter_mRETURN__VALUE_i_cSeedNoid__Lifter_mDoubleSeq
class _0RL_cd_6272dc9557a58e30_61000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_6272dc9557a58e30_61000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  SeedNoid_Lifter::DoubleSeq_var arg_0_;
  const SeedNoid_Lifter::DoubleSeq* arg_0;
  SeedNoid_Lifter::RETURN_VALUE result;
};

void _0RL_cd_6272dc9557a58e30_61000000::marshalArguments(cdrStream& _n)
{
  (const SeedNoid_Lifter::DoubleSeq&) *arg_0 >>= _n;

}

void _0RL_cd_6272dc9557a58e30_61000000::unmarshalArguments(cdrStream& _n)
{
  arg_0_ = new SeedNoid_Lifter::DoubleSeq;
  (SeedNoid_Lifter::DoubleSeq&)arg_0_ <<= _n;
  arg_0 = &arg_0_.in();

}

void _0RL_cd_6272dc9557a58e30_61000000::marshalReturnedValues(cdrStream& _n)
{
  result >>= _n;

}

void _0RL_cd_6272dc9557a58e30_61000000::unmarshalReturnedValues(cdrStream& _n)
{
  (SeedNoid_Lifter::RETURN_VALUE&)result <<= _n;

}

const char* const _0RL_cd_6272dc9557a58e30_61000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_6272dc9557a58e30_71000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_6272dc9557a58e30_61000000* tcd = (_0RL_cd_6272dc9557a58e30_61000000*)cd;
  SeedNoid_Lifter::_impl_LifterPose* impl = (SeedNoid_Lifter::_impl_LifterPose*) svnt->_ptrToInterface(SeedNoid_Lifter::LifterPose::_PD_repoId);
  tcd->result = impl->setMaxSpeedLifter(*tcd->arg_0);


}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter::_objref_LifterPose::setMaxSpeedLifter(const ::SeedNoid_Lifter::DoubleSeq& speed)
{
  _0RL_cd_6272dc9557a58e30_61000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_71000000, "setMaxSpeedLifter", 18);
  _call_desc.arg_0 = &(::SeedNoid_Lifter::DoubleSeq&) speed;

  _invoke(_call_desc);
  return _call_desc.result;


}
// Local call call-back function.
static void
_0RL_lcfn_6272dc9557a58e30_81000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_6272dc9557a58e30_41000000* tcd = (_0RL_cd_6272dc9557a58e30_41000000*)cd;
  SeedNoid_Lifter::_impl_LifterPose* impl = (SeedNoid_Lifter::_impl_LifterPose*) svnt->_ptrToInterface(SeedNoid_Lifter::LifterPose::_PD_repoId);
  tcd->result = impl->setMinAccelTimeLifter(tcd->arg_0);


}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter::_objref_LifterPose::setMinAccelTimeLifter(::CORBA::Double aclTime)
{
  _0RL_cd_6272dc9557a58e30_41000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_81000000, "setMinAccelTimeLifter", 22);
  _call_desc.arg_0 = aclTime;

  _invoke(_call_desc);
  return _call_desc.result;


}
// Proxy call descriptor class. Mangled signature:
//  _cSeedNoid__Lifter_mRETURN__VALUE_i_cunsigned_plong
class _0RL_cd_6272dc9557a58e30_91000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_6272dc9557a58e30_91000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  SeedNoid_Lifter::ULONG arg_0;
  SeedNoid_Lifter::RETURN_VALUE result;
};

void _0RL_cd_6272dc9557a58e30_91000000::marshalArguments(cdrStream& _n)
{
  arg_0 >>= _n;

}

void _0RL_cd_6272dc9557a58e30_91000000::unmarshalArguments(cdrStream& _n)
{
  (SeedNoid_Lifter::ULONG&)arg_0 <<= _n;

}

void _0RL_cd_6272dc9557a58e30_91000000::marshalReturnedValues(cdrStream& _n)
{
  result >>= _n;

}

void _0RL_cd_6272dc9557a58e30_91000000::unmarshalReturnedValues(cdrStream& _n)
{
  (SeedNoid_Lifter::RETURN_VALUE&)result <<= _n;

}

const char* const _0RL_cd_6272dc9557a58e30_91000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_6272dc9557a58e30_a1000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_6272dc9557a58e30_91000000* tcd = (_0RL_cd_6272dc9557a58e30_91000000*)cd;
  SeedNoid_Lifter::_impl_LifterPose* impl = (SeedNoid_Lifter::_impl_LifterPose*) svnt->_ptrToInterface(SeedNoid_Lifter::LifterPose::_PD_repoId);
  tcd->result = impl->setSpeedLifter(tcd->arg_0);


}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter::_objref_LifterPose::setSpeedLifter(::SeedNoid_Lifter::ULONG spdRatio)
{
  _0RL_cd_6272dc9557a58e30_91000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_a1000000, "setSpeedLifter", 15);
  _call_desc.arg_0 = spdRatio;

  _invoke(_call_desc);
  return _call_desc.result;


}
// Proxy call descriptor class. Mangled signature:
//  _cSeedNoid__Lifter_mRETURN__VALUE_o_cunsigned_plong
class _0RL_cd_6272dc9557a58e30_b1000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_6272dc9557a58e30_b1000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  
  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  SeedNoid_Lifter::ULONG arg_0;
  SeedNoid_Lifter::RETURN_VALUE result;
};

void _0RL_cd_6272dc9557a58e30_b1000000::marshalReturnedValues(cdrStream& _n)
{
  result >>= _n;
  arg_0 >>= _n;

}

void _0RL_cd_6272dc9557a58e30_b1000000::unmarshalReturnedValues(cdrStream& _n)
{
  (SeedNoid_Lifter::RETURN_VALUE&)result <<= _n;
  (SeedNoid_Lifter::ULONG&)arg_0 <<= _n;

}

const char* const _0RL_cd_6272dc9557a58e30_b1000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_6272dc9557a58e30_c1000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_6272dc9557a58e30_b1000000* tcd = (_0RL_cd_6272dc9557a58e30_b1000000*)cd;
  SeedNoid_Lifter::_impl_LifterPose* impl = (SeedNoid_Lifter::_impl_LifterPose*) svnt->_ptrToInterface(SeedNoid_Lifter::LifterPose::_PD_repoId);
  tcd->result = impl->getSpeedLifter(tcd->arg_0);


}

SeedNoid_Lifter::RETURN_VALUE SeedNoid_Lifter::_objref_LifterPose::getSpeedLifter(::SeedNoid_Lifter::ULONG& spdRatio)
{
  _0RL_cd_6272dc9557a58e30_b1000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_c1000000, "getSpeedLifter", 15);


  _invoke(_call_desc);
  spdRatio = _call_desc.arg_0;
  return _call_desc.result;


}
SeedNoid_Lifter::_pof_LifterPose::~_pof_LifterPose() {}


omniObjRef*
SeedNoid_Lifter::_pof_LifterPose::newObjRef(omniIOR* ior, omniIdentity* id)
{
  return new ::SeedNoid_Lifter::_objref_LifterPose(ior, id);
}


::CORBA::Boolean
SeedNoid_Lifter::_pof_LifterPose::is_a(const char* id) const
{
  if( omni::ptrStrMatch(id, ::SeedNoid_Lifter::LifterPose::_PD_repoId) )
    return 1;
  
  return 0;
}

const SeedNoid_Lifter::_pof_LifterPose _the_pof_SeedNoid__Lifter_mLifterPose;

SeedNoid_Lifter::_impl_LifterPose::~_impl_LifterPose() {}


::CORBA::Boolean
SeedNoid_Lifter::_impl_LifterPose::_dispatch(omniCallHandle& _handle)
{
  const char* op = _handle.operation_name();

  if( omni::strMatch(op, "sendLifterAngle") ) {

    _0RL_cd_6272dc9557a58e30_00000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_10000000, "sendLifterAngle", 16, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "sendLifterPose") ) {

    _0RL_cd_6272dc9557a58e30_20000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_30000000, "sendLifterPose", 15, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "getLifterAngle") ) {

    _0RL_cd_6272dc9557a58e30_40000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_50000000, "getLifterAngle", 15, 1);
    _call_desc.arg_0 = &_call_desc.arg_0_;
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "getLifterPose") ) {

    _0RL_cd_6272dc9557a58e30_60000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_70000000, "getLifterPose", 14, 1);
    _call_desc.arg_0 = &_call_desc.arg_0_;
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "getSoftLimitLifter") ) {

    _0RL_cd_6272dc9557a58e30_80000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_90000000, "getSoftLimitLifter", 19, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "setSoftLimitLifter") ) {

    _0RL_cd_6272dc9557a58e30_a0000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_b0000000, "setSoftLimitLifter", 19, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "getMaxSpeedLifter") ) {

    _0RL_cd_6272dc9557a58e30_c0000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_d0000000, "getMaxSpeedLifter", 18, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "getMinAccelTimeLifter") ) {

    _0RL_cd_6272dc9557a58e30_e0000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_f0000000, "getMinAccelTimeLifter", 22, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "pause") ) {

    _0RL_cd_6272dc9557a58e30_01000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_11000000, "pause", 6, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "resume") ) {

    _0RL_cd_6272dc9557a58e30_01000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_21000000, "resume", 7, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "stop") ) {

    _0RL_cd_6272dc9557a58e30_01000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_31000000, "stop", 5, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "setAccelTimeLifter") ) {

    _0RL_cd_6272dc9557a58e30_41000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_51000000, "setAccelTimeLifter", 19, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "setMaxSpeedLifter") ) {

    _0RL_cd_6272dc9557a58e30_61000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_71000000, "setMaxSpeedLifter", 18, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "setMinAccelTimeLifter") ) {

    _0RL_cd_6272dc9557a58e30_41000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_81000000, "setMinAccelTimeLifter", 22, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "setSpeedLifter") ) {

    _0RL_cd_6272dc9557a58e30_91000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_a1000000, "setSpeedLifter", 15, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "getSpeedLifter") ) {

    _0RL_cd_6272dc9557a58e30_b1000000 _call_desc(_0RL_lcfn_6272dc9557a58e30_c1000000, "getSpeedLifter", 15, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }


  return 0;
}

void*
SeedNoid_Lifter::_impl_LifterPose::_ptrToInterface(const char* id)
{
  if( id == ::SeedNoid_Lifter::LifterPose::_PD_repoId )
    return (::SeedNoid_Lifter::_impl_LifterPose*) this;
  
  if( id == ::CORBA::Object::_PD_repoId )
    return (void*) 1;

  if( omni::strMatch(id, ::SeedNoid_Lifter::LifterPose::_PD_repoId) )
    return (::SeedNoid_Lifter::_impl_LifterPose*) this;
  
  if( omni::strMatch(id, ::CORBA::Object::_PD_repoId) )
    return (void*) 1;
  return 0;
}

const char*
SeedNoid_Lifter::_impl_LifterPose::_mostDerivedRepoId()
{
  return ::SeedNoid_Lifter::LifterPose::_PD_repoId;
}

POA_SeedNoid_Lifter::LifterPose::~LifterPose() {}

