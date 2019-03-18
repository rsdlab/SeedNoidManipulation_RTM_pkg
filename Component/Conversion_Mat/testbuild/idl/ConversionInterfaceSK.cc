// This file is generated by omniidl (C++ backend)- omniORB_4_1. Do not edit.

#include "ConversionInterface.hh"
#include <omniORB4/IOP_S.h>
#include <omniORB4/IOP_C.h>
#include <omniORB4/callDescriptor.h>
#include <omniORB4/callHandle.h>
#include <omniORB4/objTracker.h>


OMNI_USING_NAMESPACE(omni)

static const char* _0RL_library_version = omniORB_4_1;



_init_in_def_( const ::CORBA::Long ConversionMatrix::OK = 0; )

_init_in_def_( const ::CORBA::Long ConversionMatrix::NG = -1; )

void
ConversionMatrix::rotationMat::operator>>= (cdrStream &_n) const
{
  R11 >>= _n;
  R12 >>= _n;
  R13 >>= _n;
  R21 >>= _n;
  R22 >>= _n;
  R23 >>= _n;
  R31 >>= _n;
  R32 >>= _n;
  R33 >>= _n;

}

void
ConversionMatrix::rotationMat::operator<<= (cdrStream &_n)
{
  (::CORBA::Double&)R11 <<= _n;
  (::CORBA::Double&)R12 <<= _n;
  (::CORBA::Double&)R13 <<= _n;
  (::CORBA::Double&)R21 <<= _n;
  (::CORBA::Double&)R22 <<= _n;
  (::CORBA::Double&)R23 <<= _n;
  (::CORBA::Double&)R31 <<= _n;
  (::CORBA::Double&)R32 <<= _n;
  (::CORBA::Double&)R33 <<= _n;

}

void
ConversionMatrix::transformationMat::operator>>= (cdrStream &_n) const
{
  (const rotationMat&) rotation >>= _n;
  (const RTC::Vector3D&) translates >>= _n;

}

void
ConversionMatrix::transformationMat::operator<<= (cdrStream &_n)
{
  (rotationMat&)rotation <<= _n;
  (RTC::Vector3D&)translates <<= _n;

}

ConversionMatrix::conversionInterface_ptr ConversionMatrix::conversionInterface_Helper::_nil() {
  return ::ConversionMatrix::conversionInterface::_nil();
}

::CORBA::Boolean ConversionMatrix::conversionInterface_Helper::is_nil(::ConversionMatrix::conversionInterface_ptr p) {
  return ::CORBA::is_nil(p);

}

void ConversionMatrix::conversionInterface_Helper::release(::ConversionMatrix::conversionInterface_ptr p) {
  ::CORBA::release(p);
}

void ConversionMatrix::conversionInterface_Helper::marshalObjRef(::ConversionMatrix::conversionInterface_ptr obj, cdrStream& s) {
  ::ConversionMatrix::conversionInterface::_marshalObjRef(obj, s);
}

ConversionMatrix::conversionInterface_ptr ConversionMatrix::conversionInterface_Helper::unmarshalObjRef(cdrStream& s) {
  return ::ConversionMatrix::conversionInterface::_unmarshalObjRef(s);
}

void ConversionMatrix::conversionInterface_Helper::duplicate(::ConversionMatrix::conversionInterface_ptr obj) {
  if( obj && !obj->_NP_is_nil() )  omni::duplicateObjRef(obj);
}

ConversionMatrix::conversionInterface_ptr
ConversionMatrix::conversionInterface::_duplicate(::ConversionMatrix::conversionInterface_ptr obj)
{
  if( obj && !obj->_NP_is_nil() )  omni::duplicateObjRef(obj);
  return obj;
}

ConversionMatrix::conversionInterface_ptr
ConversionMatrix::conversionInterface::_narrow(::CORBA::Object_ptr obj)
{
  if( !obj || obj->_NP_is_nil() || obj->_NP_is_pseudo() ) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_realNarrow(_PD_repoId);
  return e ? e : _nil();
}


ConversionMatrix::conversionInterface_ptr
ConversionMatrix::conversionInterface::_unchecked_narrow(::CORBA::Object_ptr obj)
{
  if( !obj || obj->_NP_is_nil() || obj->_NP_is_pseudo() ) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_uncheckedNarrow(_PD_repoId);
  return e ? e : _nil();
}

ConversionMatrix::conversionInterface_ptr
ConversionMatrix::conversionInterface::_nil()
{
#ifdef OMNI_UNLOADABLE_STUBS
  static _objref_conversionInterface _the_nil_obj;
  return &_the_nil_obj;
#else
  static _objref_conversionInterface* _the_nil_ptr = 0;
  if( !_the_nil_ptr ) {
    omni::nilRefLock().lock();
    if( !_the_nil_ptr ) {
      _the_nil_ptr = new _objref_conversionInterface;
      registerNilCorbaObject(_the_nil_ptr);
    }
    omni::nilRefLock().unlock();
  }
  return _the_nil_ptr;
#endif
}

const char* ConversionMatrix::conversionInterface::_PD_repoId = "IDL:ConversionMatrix/conversionInterface:1.0";


ConversionMatrix::_objref_conversionInterface::~_objref_conversionInterface() {
  
}


ConversionMatrix::_objref_conversionInterface::_objref_conversionInterface(omniIOR* ior, omniIdentity* id) :
   omniObjRef(::ConversionMatrix::conversionInterface::_PD_repoId, ior, id, 1)
   
   
{
  _PR_setobj(this);
}

void*
ConversionMatrix::_objref_conversionInterface::_ptrToObjRef(const char* id)
{
  if( id == ::ConversionMatrix::conversionInterface::_PD_repoId )
    return (::ConversionMatrix::conversionInterface_ptr) this;
  
  if( id == ::CORBA::Object::_PD_repoId )
    return (::CORBA::Object_ptr) this;

  if( omni::strMatch(id, ::ConversionMatrix::conversionInterface::_PD_repoId) )
    return (::ConversionMatrix::conversionInterface_ptr) this;
  
  if( omni::strMatch(id, ::CORBA::Object::_PD_repoId) )
    return (::CORBA::Object_ptr) this;

  return 0;
}

// Proxy call descriptor class. Mangled signature:
//  _clong_i_cConversionMatrix_mtransformationMat_o_cConversionMatrix_mtransformationMat
class _0RL_cd_790062e9b1575976_00000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_790062e9b1575976_00000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  ConversionMatrix::transformationMat arg_0_;
  const ConversionMatrix::transformationMat* arg_0;
  ConversionMatrix::transformationMat arg_1_;
  ConversionMatrix::transformationMat* arg_1;
  ::CORBA::Long result;
};

void _0RL_cd_790062e9b1575976_00000000::marshalArguments(cdrStream& _n)
{
  (const ConversionMatrix::transformationMat&) *arg_0 >>= _n;

}

void _0RL_cd_790062e9b1575976_00000000::unmarshalArguments(cdrStream& _n)
{
  (ConversionMatrix::transformationMat&)arg_0_ <<= _n;
  arg_0 = &arg_0_;

}

void _0RL_cd_790062e9b1575976_00000000::marshalReturnedValues(cdrStream& _n)
{
  result >>= _n;
  (const ConversionMatrix::transformationMat&) *arg_1 >>= _n;

}

void _0RL_cd_790062e9b1575976_00000000::unmarshalReturnedValues(cdrStream& _n)
{
  (::CORBA::Long&)result <<= _n;
  (ConversionMatrix::transformationMat&)*arg_1 <<= _n;

}

const char* const _0RL_cd_790062e9b1575976_00000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_790062e9b1575976_10000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_790062e9b1575976_00000000* tcd = (_0RL_cd_790062e9b1575976_00000000*)cd;
  ConversionMatrix::_impl_conversionInterface* impl = (ConversionMatrix::_impl_conversionInterface*) svnt->_ptrToInterface(ConversionMatrix::conversionInterface::_PD_repoId);
  tcd->result = impl->getConvertionMat(*tcd->arg_0, *tcd->arg_1);


}

::CORBA::Long ConversionMatrix::_objref_conversionInterface::getConvertionMat(const ::ConversionMatrix::transformationMat& InMat, ::ConversionMatrix::transformationMat& OutMat)
{
  _0RL_cd_790062e9b1575976_00000000 _call_desc(_0RL_lcfn_790062e9b1575976_10000000, "getConvertionMat", 17);
  _call_desc.arg_0 = &(::ConversionMatrix::transformationMat&) InMat;
  _call_desc.arg_1 = &(::ConversionMatrix::transformationMat&) OutMat;

  _invoke(_call_desc);
  return _call_desc.result;


}
ConversionMatrix::_pof_conversionInterface::~_pof_conversionInterface() {}


omniObjRef*
ConversionMatrix::_pof_conversionInterface::newObjRef(omniIOR* ior, omniIdentity* id)
{
  return new ::ConversionMatrix::_objref_conversionInterface(ior, id);
}


::CORBA::Boolean
ConversionMatrix::_pof_conversionInterface::is_a(const char* id) const
{
  if( omni::ptrStrMatch(id, ::ConversionMatrix::conversionInterface::_PD_repoId) )
    return 1;
  
  return 0;
}

const ConversionMatrix::_pof_conversionInterface _the_pof_ConversionMatrix_mconversionInterface;

ConversionMatrix::_impl_conversionInterface::~_impl_conversionInterface() {}


::CORBA::Boolean
ConversionMatrix::_impl_conversionInterface::_dispatch(omniCallHandle& _handle)
{
  const char* op = _handle.operation_name();

  if( omni::strMatch(op, "getConvertionMat") ) {

    _0RL_cd_790062e9b1575976_00000000 _call_desc(_0RL_lcfn_790062e9b1575976_10000000, "getConvertionMat", 17, 1);
    _call_desc.arg_1 = &_call_desc.arg_1_;
    _handle.upcall(this,_call_desc);
    return 1;
  }


  return 0;
}

void*
ConversionMatrix::_impl_conversionInterface::_ptrToInterface(const char* id)
{
  if( id == ::ConversionMatrix::conversionInterface::_PD_repoId )
    return (::ConversionMatrix::_impl_conversionInterface*) this;
  
  if( id == ::CORBA::Object::_PD_repoId )
    return (void*) 1;

  if( omni::strMatch(id, ::ConversionMatrix::conversionInterface::_PD_repoId) )
    return (::ConversionMatrix::_impl_conversionInterface*) this;
  
  if( omni::strMatch(id, ::CORBA::Object::_PD_repoId) )
    return (void*) 1;
  return 0;
}

const char*
ConversionMatrix::_impl_conversionInterface::_mostDerivedRepoId()
{
  return ::ConversionMatrix::conversionInterface::_PD_repoId;
}

POA_ConversionMatrix::conversionInterface::~conversionInterface() {}
