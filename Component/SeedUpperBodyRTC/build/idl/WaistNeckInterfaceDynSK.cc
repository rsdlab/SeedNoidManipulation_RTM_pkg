// This file is generated by omniidl (C++ backend) - omniORB_4_1. Do not edit.

#include "WaistNeckInterface.hh"

OMNI_USING_NAMESPACE(omni)

static const char* _0RL_dyn_library_version = omniORB_4_1_dyn;

static ::CORBA::TypeCode::_Tracker _0RL_tcTrack(__FILE__);

static CORBA::PR_structMember _0RL_structmember_WaistNeck_mRETURN__ID[] = {
  {"id", CORBA::TypeCode::PR_long_tc()},
  {"comment", CORBA::TypeCode::PR_string_tc(0, &_0RL_tcTrack)}
};

#ifdef _0RL_tc_WaistNeck_mRETURN__ID
#  undef _0RL_tc_WaistNeck_mRETURN__ID
#endif
static CORBA::TypeCode_ptr _0RL_tc_WaistNeck_mRETURN__ID = CORBA::TypeCode::PR_struct_tc("IDL:WaistNeck/RETURN_ID:1.0", "RETURN_ID", _0RL_structmember_WaistNeck_mRETURN__ID, 2, &_0RL_tcTrack);

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace WaistNeck { 
  const ::CORBA::TypeCode_ptr _tc_RETURN_ID = _0RL_tc_WaistNeck_mRETURN__ID;
} 
#else
const ::CORBA::TypeCode_ptr WaistNeck::_tc_RETURN_ID = _0RL_tc_WaistNeck_mRETURN__ID;
#endif


static CORBA::PR_structMember _0RL_structmember_WaistNeck_mLimitValue[] = {
  {"upper", CORBA::TypeCode::PR_double_tc()},
  {"lower", CORBA::TypeCode::PR_double_tc()}
};

#ifdef _0RL_tc_WaistNeck_mLimitValue
#  undef _0RL_tc_WaistNeck_mLimitValue
#endif
static CORBA::TypeCode_ptr _0RL_tc_WaistNeck_mLimitValue = CORBA::TypeCode::PR_struct_tc("IDL:WaistNeck/LimitValue:1.0", "LimitValue", _0RL_structmember_WaistNeck_mLimitValue, 2, &_0RL_tcTrack);

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace WaistNeck { 
  const ::CORBA::TypeCode_ptr _tc_LimitValue = _0RL_tc_WaistNeck_mLimitValue;
} 
#else
const ::CORBA::TypeCode_ptr WaistNeck::_tc_LimitValue = _0RL_tc_WaistNeck_mLimitValue;
#endif


static CORBA::TypeCode_ptr _0RL_tc_WaistNeck_mDoubleSeq = CORBA::TypeCode::PR_alias_tc("IDL:WaistNeck/DoubleSeq:1.0", "DoubleSeq", CORBA::TypeCode::PR_sequence_tc(0, CORBA::TypeCode::PR_double_tc(), &_0RL_tcTrack), &_0RL_tcTrack);


#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace WaistNeck { 
  const ::CORBA::TypeCode_ptr _tc_DoubleSeq = _0RL_tc_WaistNeck_mDoubleSeq;
} 
#else
const ::CORBA::TypeCode_ptr WaistNeck::_tc_DoubleSeq = _0RL_tc_WaistNeck_mDoubleSeq;
#endif

static CORBA::TypeCode_ptr _0RL_tc_WaistNeck_mNeckPos = CORBA::TypeCode::PR_alias_tc("IDL:WaistNeck/NeckPos:1.0", "NeckPos", CORBA::TypeCode::PR_sequence_tc(0, CORBA::TypeCode::PR_double_tc(), &_0RL_tcTrack), &_0RL_tcTrack);


#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace WaistNeck { 
  const ::CORBA::TypeCode_ptr _tc_NeckPos = _0RL_tc_WaistNeck_mNeckPos;
} 
#else
const ::CORBA::TypeCode_ptr WaistNeck::_tc_NeckPos = _0RL_tc_WaistNeck_mNeckPos;
#endif

static CORBA::TypeCode_ptr _0RL_tc_WaistNeck_mWaistPos = CORBA::TypeCode::PR_alias_tc("IDL:WaistNeck/WaistPos:1.0", "WaistPos", CORBA::TypeCode::PR_sequence_tc(0, CORBA::TypeCode::PR_double_tc(), &_0RL_tcTrack), &_0RL_tcTrack);


#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace WaistNeck { 
  const ::CORBA::TypeCode_ptr _tc_WaistPos = _0RL_tc_WaistNeck_mWaistPos;
} 
#else
const ::CORBA::TypeCode_ptr WaistNeck::_tc_WaistPos = _0RL_tc_WaistNeck_mWaistPos;
#endif





static CORBA::TypeCode_ptr _0RL_tc_WaistNeck_mLimitSeq = CORBA::TypeCode::PR_alias_tc("IDL:WaistNeck/LimitSeq:1.0", "LimitSeq", CORBA::TypeCode::PR_sequence_tc(0, _0RL_tc_WaistNeck_mLimitValue, &_0RL_tcTrack), &_0RL_tcTrack);


#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace WaistNeck { 
  const ::CORBA::TypeCode_ptr _tc_LimitSeq = _0RL_tc_WaistNeck_mLimitSeq;
} 
#else
const ::CORBA::TypeCode_ptr WaistNeck::_tc_LimitSeq = _0RL_tc_WaistNeck_mLimitSeq;
#endif

static CORBA::TypeCode_ptr _0RL_tc_WaistNeck_mULONG = CORBA::TypeCode::PR_alias_tc("IDL:WaistNeck/ULONG:1.0", "ULONG", CORBA::TypeCode::PR_ulong_tc(), &_0RL_tcTrack);


#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace WaistNeck { 
  const ::CORBA::TypeCode_ptr _tc_ULONG = _0RL_tc_WaistNeck_mULONG;
} 
#else
const ::CORBA::TypeCode_ptr WaistNeck::_tc_ULONG = _0RL_tc_WaistNeck_mULONG;
#endif

static CORBA::PR_structMember _0RL_structmember_WaistNeck_mManipInfo[] = {
  {"manufactur", CORBA::TypeCode::PR_string_tc(0, &_0RL_tcTrack)},
  {"type", CORBA::TypeCode::PR_string_tc(0, &_0RL_tcTrack)},
  {"axisNum", _0RL_tc_WaistNeck_mULONG},
  {"cmdCycle", _0RL_tc_WaistNeck_mULONG}
};

#ifdef _0RL_tc_WaistNeck_mManipInfo
#  undef _0RL_tc_WaistNeck_mManipInfo
#endif
static CORBA::TypeCode_ptr _0RL_tc_WaistNeck_mManipInfo = CORBA::TypeCode::PR_struct_tc("IDL:WaistNeck/ManipInfo:1.0", "ManipInfo", _0RL_structmember_WaistNeck_mManipInfo, 4, &_0RL_tcTrack);

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace WaistNeck { 
  const ::CORBA::TypeCode_ptr _tc_ManipInfo = _0RL_tc_WaistNeck_mManipInfo;
} 
#else
const ::CORBA::TypeCode_ptr WaistNeck::_tc_ManipInfo = _0RL_tc_WaistNeck_mManipInfo;
#endif


#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace WaistNeck { 
  const ::CORBA::TypeCode_ptr _tc_NeckInterface = CORBA::TypeCode::PR_interface_tc("IDL:WaistNeck/NeckInterface:1.0", "NeckInterface", &_0RL_tcTrack);
} 
#else
const ::CORBA::TypeCode_ptr WaistNeck::_tc_NeckInterface = CORBA::TypeCode::PR_interface_tc("IDL:WaistNeck/NeckInterface:1.0", "NeckInterface", &_0RL_tcTrack);
#endif

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace WaistNeck { 
  const ::CORBA::TypeCode_ptr _tc_WaistInterface = CORBA::TypeCode::PR_interface_tc("IDL:WaistNeck/WaistInterface:1.0", "WaistInterface", &_0RL_tcTrack);
} 
#else
const ::CORBA::TypeCode_ptr WaistNeck::_tc_WaistInterface = CORBA::TypeCode::PR_interface_tc("IDL:WaistNeck/WaistInterface:1.0", "WaistInterface", &_0RL_tcTrack);
#endif

static void _0RL_WaistNeck_mRETURN__ID_marshal_fn(cdrStream& _s, void* _v)
{
  WaistNeck::RETURN_ID* _p = (WaistNeck::RETURN_ID*)_v;
  *_p >>= _s;
}
static void _0RL_WaistNeck_mRETURN__ID_unmarshal_fn(cdrStream& _s, void*& _v)
{
  WaistNeck::RETURN_ID* _p = new WaistNeck::RETURN_ID;
  *_p <<= _s;
  _v = _p;
}
static void _0RL_WaistNeck_mRETURN__ID_destructor_fn(void* _v)
{
  WaistNeck::RETURN_ID* _p = (WaistNeck::RETURN_ID*)_v;
  delete _p;
}

void operator<<=(::CORBA::Any& _a, const WaistNeck::RETURN_ID& _s)
{
  WaistNeck::RETURN_ID* _p = new WaistNeck::RETURN_ID(_s);
  _a.PR_insert(_0RL_tc_WaistNeck_mRETURN__ID,
               _0RL_WaistNeck_mRETURN__ID_marshal_fn,
               _0RL_WaistNeck_mRETURN__ID_destructor_fn,
               _p);
}
void operator<<=(::CORBA::Any& _a, WaistNeck::RETURN_ID* _sp)
{
  _a.PR_insert(_0RL_tc_WaistNeck_mRETURN__ID,
               _0RL_WaistNeck_mRETURN__ID_marshal_fn,
               _0RL_WaistNeck_mRETURN__ID_destructor_fn,
               _sp);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, WaistNeck::RETURN_ID*& _sp)
{
  return _a >>= (const WaistNeck::RETURN_ID*&) _sp;
}
::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, const WaistNeck::RETURN_ID*& _sp)
{
  void* _v;
  if (_a.PR_extract(_0RL_tc_WaistNeck_mRETURN__ID,
                    _0RL_WaistNeck_mRETURN__ID_unmarshal_fn,
                    _0RL_WaistNeck_mRETURN__ID_marshal_fn,
                    _0RL_WaistNeck_mRETURN__ID_destructor_fn,
                    _v)) {
    _sp = (const WaistNeck::RETURN_ID*)_v;
    return 1;
  }
  return 0;
}

static void _0RL_WaistNeck_mLimitValue_marshal_fn(cdrStream& _s, void* _v)
{
  WaistNeck::LimitValue* _p = (WaistNeck::LimitValue*)_v;
  *_p >>= _s;
}
static void _0RL_WaistNeck_mLimitValue_unmarshal_fn(cdrStream& _s, void*& _v)
{
  WaistNeck::LimitValue* _p = new WaistNeck::LimitValue;
  *_p <<= _s;
  _v = _p;
}
static void _0RL_WaistNeck_mLimitValue_destructor_fn(void* _v)
{
  WaistNeck::LimitValue* _p = (WaistNeck::LimitValue*)_v;
  delete _p;
}

void operator<<=(::CORBA::Any& _a, const WaistNeck::LimitValue& _s)
{
  WaistNeck::LimitValue* _p = new WaistNeck::LimitValue(_s);
  _a.PR_insert(_0RL_tc_WaistNeck_mLimitValue,
               _0RL_WaistNeck_mLimitValue_marshal_fn,
               _0RL_WaistNeck_mLimitValue_destructor_fn,
               _p);
}
void operator<<=(::CORBA::Any& _a, WaistNeck::LimitValue* _sp)
{
  _a.PR_insert(_0RL_tc_WaistNeck_mLimitValue,
               _0RL_WaistNeck_mLimitValue_marshal_fn,
               _0RL_WaistNeck_mLimitValue_destructor_fn,
               _sp);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, WaistNeck::LimitValue*& _sp)
{
  return _a >>= (const WaistNeck::LimitValue*&) _sp;
}
::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, const WaistNeck::LimitValue*& _sp)
{
  void* _v;
  if (_a.PR_extract(_0RL_tc_WaistNeck_mLimitValue,
                    _0RL_WaistNeck_mLimitValue_unmarshal_fn,
                    _0RL_WaistNeck_mLimitValue_marshal_fn,
                    _0RL_WaistNeck_mLimitValue_destructor_fn,
                    _v)) {
    _sp = (const WaistNeck::LimitValue*)_v;
    return 1;
  }
  return 0;
}

static void _0RL_WaistNeck_mDoubleSeq_marshal_fn(cdrStream& _s, void* _v)
{
  WaistNeck::DoubleSeq* _p = (WaistNeck::DoubleSeq*)_v;
  *_p >>= _s;
}
static void _0RL_WaistNeck_mDoubleSeq_unmarshal_fn(cdrStream& _s, void*& _v)
{
  WaistNeck::DoubleSeq* _p = new WaistNeck::DoubleSeq;
  *_p <<= _s;
  _v = _p;
}
static void _0RL_WaistNeck_mDoubleSeq_destructor_fn(void* _v)
{
  WaistNeck::DoubleSeq* _p = (WaistNeck::DoubleSeq*)_v;
  delete _p;
}

void operator<<=(::CORBA::Any& _a, const WaistNeck::DoubleSeq& _s)
{
  WaistNeck::DoubleSeq* _p = new WaistNeck::DoubleSeq(_s);
  _a.PR_insert(_0RL_tc_WaistNeck_mDoubleSeq,
               _0RL_WaistNeck_mDoubleSeq_marshal_fn,
               _0RL_WaistNeck_mDoubleSeq_destructor_fn,
               _p);
}
void operator<<=(::CORBA::Any& _a, WaistNeck::DoubleSeq* _sp)
{
  _a.PR_insert(_0RL_tc_WaistNeck_mDoubleSeq,
               _0RL_WaistNeck_mDoubleSeq_marshal_fn,
               _0RL_WaistNeck_mDoubleSeq_destructor_fn,
               _sp);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, WaistNeck::DoubleSeq*& _sp)
{
  return _a >>= (const WaistNeck::DoubleSeq*&) _sp;
}
::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, const WaistNeck::DoubleSeq*& _sp)
{
  void* _v;
  if (_a.PR_extract(_0RL_tc_WaistNeck_mDoubleSeq,
                    _0RL_WaistNeck_mDoubleSeq_unmarshal_fn,
                    _0RL_WaistNeck_mDoubleSeq_marshal_fn,
                    _0RL_WaistNeck_mDoubleSeq_destructor_fn,
                    _v)) {
    _sp = (const WaistNeck::DoubleSeq*)_v;
    return 1;
  }
  return 0;
}

static void _0RL_WaistNeck_mNeckPos_marshal_fn(cdrStream& _s, void* _v)
{
  WaistNeck::NeckPos* _p = (WaistNeck::NeckPos*)_v;
  *_p >>= _s;
}
static void _0RL_WaistNeck_mNeckPos_unmarshal_fn(cdrStream& _s, void*& _v)
{
  WaistNeck::NeckPos* _p = new WaistNeck::NeckPos;
  *_p <<= _s;
  _v = _p;
}
static void _0RL_WaistNeck_mNeckPos_destructor_fn(void* _v)
{
  WaistNeck::NeckPos* _p = (WaistNeck::NeckPos*)_v;
  delete _p;
}

void operator<<=(::CORBA::Any& _a, const WaistNeck::NeckPos& _s)
{
  WaistNeck::NeckPos* _p = new WaistNeck::NeckPos(_s);
  _a.PR_insert(_0RL_tc_WaistNeck_mNeckPos,
               _0RL_WaistNeck_mNeckPos_marshal_fn,
               _0RL_WaistNeck_mNeckPos_destructor_fn,
               _p);
}
void operator<<=(::CORBA::Any& _a, WaistNeck::NeckPos* _sp)
{
  _a.PR_insert(_0RL_tc_WaistNeck_mNeckPos,
               _0RL_WaistNeck_mNeckPos_marshal_fn,
               _0RL_WaistNeck_mNeckPos_destructor_fn,
               _sp);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, WaistNeck::NeckPos*& _sp)
{
  return _a >>= (const WaistNeck::NeckPos*&) _sp;
}
::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, const WaistNeck::NeckPos*& _sp)
{
  void* _v;
  if (_a.PR_extract(_0RL_tc_WaistNeck_mNeckPos,
                    _0RL_WaistNeck_mNeckPos_unmarshal_fn,
                    _0RL_WaistNeck_mNeckPos_marshal_fn,
                    _0RL_WaistNeck_mNeckPos_destructor_fn,
                    _v)) {
    _sp = (const WaistNeck::NeckPos*)_v;
    return 1;
  }
  return 0;
}

static void _0RL_WaistNeck_mWaistPos_marshal_fn(cdrStream& _s, void* _v)
{
  WaistNeck::WaistPos* _p = (WaistNeck::WaistPos*)_v;
  *_p >>= _s;
}
static void _0RL_WaistNeck_mWaistPos_unmarshal_fn(cdrStream& _s, void*& _v)
{
  WaistNeck::WaistPos* _p = new WaistNeck::WaistPos;
  *_p <<= _s;
  _v = _p;
}
static void _0RL_WaistNeck_mWaistPos_destructor_fn(void* _v)
{
  WaistNeck::WaistPos* _p = (WaistNeck::WaistPos*)_v;
  delete _p;
}

void operator<<=(::CORBA::Any& _a, const WaistNeck::WaistPos& _s)
{
  WaistNeck::WaistPos* _p = new WaistNeck::WaistPos(_s);
  _a.PR_insert(_0RL_tc_WaistNeck_mWaistPos,
               _0RL_WaistNeck_mWaistPos_marshal_fn,
               _0RL_WaistNeck_mWaistPos_destructor_fn,
               _p);
}
void operator<<=(::CORBA::Any& _a, WaistNeck::WaistPos* _sp)
{
  _a.PR_insert(_0RL_tc_WaistNeck_mWaistPos,
               _0RL_WaistNeck_mWaistPos_marshal_fn,
               _0RL_WaistNeck_mWaistPos_destructor_fn,
               _sp);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, WaistNeck::WaistPos*& _sp)
{
  return _a >>= (const WaistNeck::WaistPos*&) _sp;
}
::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, const WaistNeck::WaistPos*& _sp)
{
  void* _v;
  if (_a.PR_extract(_0RL_tc_WaistNeck_mWaistPos,
                    _0RL_WaistNeck_mWaistPos_unmarshal_fn,
                    _0RL_WaistNeck_mWaistPos_marshal_fn,
                    _0RL_WaistNeck_mWaistPos_destructor_fn,
                    _v)) {
    _sp = (const WaistNeck::WaistPos*)_v;
    return 1;
  }
  return 0;
}

static void _0RL_WaistNeck_mLimitSeq_marshal_fn(cdrStream& _s, void* _v)
{
  WaistNeck::LimitSeq* _p = (WaistNeck::LimitSeq*)_v;
  *_p >>= _s;
}
static void _0RL_WaistNeck_mLimitSeq_unmarshal_fn(cdrStream& _s, void*& _v)
{
  WaistNeck::LimitSeq* _p = new WaistNeck::LimitSeq;
  *_p <<= _s;
  _v = _p;
}
static void _0RL_WaistNeck_mLimitSeq_destructor_fn(void* _v)
{
  WaistNeck::LimitSeq* _p = (WaistNeck::LimitSeq*)_v;
  delete _p;
}

void operator<<=(::CORBA::Any& _a, const WaistNeck::LimitSeq& _s)
{
  WaistNeck::LimitSeq* _p = new WaistNeck::LimitSeq(_s);
  _a.PR_insert(_0RL_tc_WaistNeck_mLimitSeq,
               _0RL_WaistNeck_mLimitSeq_marshal_fn,
               _0RL_WaistNeck_mLimitSeq_destructor_fn,
               _p);
}
void operator<<=(::CORBA::Any& _a, WaistNeck::LimitSeq* _sp)
{
  _a.PR_insert(_0RL_tc_WaistNeck_mLimitSeq,
               _0RL_WaistNeck_mLimitSeq_marshal_fn,
               _0RL_WaistNeck_mLimitSeq_destructor_fn,
               _sp);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, WaistNeck::LimitSeq*& _sp)
{
  return _a >>= (const WaistNeck::LimitSeq*&) _sp;
}
::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, const WaistNeck::LimitSeq*& _sp)
{
  void* _v;
  if (_a.PR_extract(_0RL_tc_WaistNeck_mLimitSeq,
                    _0RL_WaistNeck_mLimitSeq_unmarshal_fn,
                    _0RL_WaistNeck_mLimitSeq_marshal_fn,
                    _0RL_WaistNeck_mLimitSeq_destructor_fn,
                    _v)) {
    _sp = (const WaistNeck::LimitSeq*)_v;
    return 1;
  }
  return 0;
}

static void _0RL_WaistNeck_mManipInfo_marshal_fn(cdrStream& _s, void* _v)
{
  WaistNeck::ManipInfo* _p = (WaistNeck::ManipInfo*)_v;
  *_p >>= _s;
}
static void _0RL_WaistNeck_mManipInfo_unmarshal_fn(cdrStream& _s, void*& _v)
{
  WaistNeck::ManipInfo* _p = new WaistNeck::ManipInfo;
  *_p <<= _s;
  _v = _p;
}
static void _0RL_WaistNeck_mManipInfo_destructor_fn(void* _v)
{
  WaistNeck::ManipInfo* _p = (WaistNeck::ManipInfo*)_v;
  delete _p;
}

void operator<<=(::CORBA::Any& _a, const WaistNeck::ManipInfo& _s)
{
  WaistNeck::ManipInfo* _p = new WaistNeck::ManipInfo(_s);
  _a.PR_insert(_0RL_tc_WaistNeck_mManipInfo,
               _0RL_WaistNeck_mManipInfo_marshal_fn,
               _0RL_WaistNeck_mManipInfo_destructor_fn,
               _p);
}
void operator<<=(::CORBA::Any& _a, WaistNeck::ManipInfo* _sp)
{
  _a.PR_insert(_0RL_tc_WaistNeck_mManipInfo,
               _0RL_WaistNeck_mManipInfo_marshal_fn,
               _0RL_WaistNeck_mManipInfo_destructor_fn,
               _sp);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, WaistNeck::ManipInfo*& _sp)
{
  return _a >>= (const WaistNeck::ManipInfo*&) _sp;
}
::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, const WaistNeck::ManipInfo*& _sp)
{
  void* _v;
  if (_a.PR_extract(_0RL_tc_WaistNeck_mManipInfo,
                    _0RL_WaistNeck_mManipInfo_unmarshal_fn,
                    _0RL_WaistNeck_mManipInfo_marshal_fn,
                    _0RL_WaistNeck_mManipInfo_destructor_fn,
                    _v)) {
    _sp = (const WaistNeck::ManipInfo*)_v;
    return 1;
  }
  return 0;
}

static void _0RL_WaistNeck_mNeckInterface_marshal_fn(cdrStream& _s, void* _v)
{
  omniObjRef* _o = (omniObjRef*)_v;
  omniObjRef::_marshal(_o, _s);
}
static void _0RL_WaistNeck_mNeckInterface_unmarshal_fn(cdrStream& _s, void*& _v)
{
  omniObjRef* _o = omniObjRef::_unMarshal(WaistNeck::NeckInterface::_PD_repoId, _s);
  _v = _o;
}
static void _0RL_WaistNeck_mNeckInterface_destructor_fn(void* _v)
{
  omniObjRef* _o = (omniObjRef*)_v;
  if (_o)
    omni::releaseObjRef(_o);
}

void operator<<=(::CORBA::Any& _a, WaistNeck::NeckInterface_ptr _o)
{
  WaistNeck::NeckInterface_ptr _no = WaistNeck::NeckInterface::_duplicate(_o);
  _a.PR_insert(WaistNeck::_tc_NeckInterface,
               _0RL_WaistNeck_mNeckInterface_marshal_fn,
               _0RL_WaistNeck_mNeckInterface_destructor_fn,
               _no->_PR_getobj());
}
void operator<<=(::CORBA::Any& _a, WaistNeck::NeckInterface_ptr* _op)
{
  _a.PR_insert(WaistNeck::_tc_NeckInterface,
               _0RL_WaistNeck_mNeckInterface_marshal_fn,
               _0RL_WaistNeck_mNeckInterface_destructor_fn,
               (*_op)->_PR_getobj());
  *_op = WaistNeck::NeckInterface::_nil();
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, WaistNeck::NeckInterface_ptr& _o)
{
  void* _v;
  if (_a.PR_extract(WaistNeck::_tc_NeckInterface,
                    _0RL_WaistNeck_mNeckInterface_unmarshal_fn,
                    _0RL_WaistNeck_mNeckInterface_marshal_fn,
                    _0RL_WaistNeck_mNeckInterface_destructor_fn,
                    _v)) {
    omniObjRef* _r = (omniObjRef*)_v;
    if (_r)
      _o = (WaistNeck::NeckInterface_ptr)_r->_ptrToObjRef(WaistNeck::NeckInterface::_PD_repoId);
    else
      _o = WaistNeck::NeckInterface::_nil();
    return 1;
  }
  return 0;
}

static void _0RL_WaistNeck_mWaistInterface_marshal_fn(cdrStream& _s, void* _v)
{
  omniObjRef* _o = (omniObjRef*)_v;
  omniObjRef::_marshal(_o, _s);
}
static void _0RL_WaistNeck_mWaistInterface_unmarshal_fn(cdrStream& _s, void*& _v)
{
  omniObjRef* _o = omniObjRef::_unMarshal(WaistNeck::WaistInterface::_PD_repoId, _s);
  _v = _o;
}
static void _0RL_WaistNeck_mWaistInterface_destructor_fn(void* _v)
{
  omniObjRef* _o = (omniObjRef*)_v;
  if (_o)
    omni::releaseObjRef(_o);
}

void operator<<=(::CORBA::Any& _a, WaistNeck::WaistInterface_ptr _o)
{
  WaistNeck::WaistInterface_ptr _no = WaistNeck::WaistInterface::_duplicate(_o);
  _a.PR_insert(WaistNeck::_tc_WaistInterface,
               _0RL_WaistNeck_mWaistInterface_marshal_fn,
               _0RL_WaistNeck_mWaistInterface_destructor_fn,
               _no->_PR_getobj());
}
void operator<<=(::CORBA::Any& _a, WaistNeck::WaistInterface_ptr* _op)
{
  _a.PR_insert(WaistNeck::_tc_WaistInterface,
               _0RL_WaistNeck_mWaistInterface_marshal_fn,
               _0RL_WaistNeck_mWaistInterface_destructor_fn,
               (*_op)->_PR_getobj());
  *_op = WaistNeck::WaistInterface::_nil();
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, WaistNeck::WaistInterface_ptr& _o)
{
  void* _v;
  if (_a.PR_extract(WaistNeck::_tc_WaistInterface,
                    _0RL_WaistNeck_mWaistInterface_unmarshal_fn,
                    _0RL_WaistNeck_mWaistInterface_marshal_fn,
                    _0RL_WaistNeck_mWaistInterface_destructor_fn,
                    _v)) {
    omniObjRef* _r = (omniObjRef*)_v;
    if (_r)
      _o = (WaistNeck::WaistInterface_ptr)_r->_ptrToObjRef(WaistNeck::WaistInterface::_PD_repoId);
    else
      _o = WaistNeck::WaistInterface::_nil();
    return 1;
  }
  return 0;
}

