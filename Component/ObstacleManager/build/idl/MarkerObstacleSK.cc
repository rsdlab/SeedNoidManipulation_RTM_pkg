// This file is generated by omniidl (C++ backend)- omniORB_4_1. Do not edit.

#include "MarkerObstacle.hh"
#include <omniORB4/IOP_S.h>
#include <omniORB4/IOP_C.h>
#include <omniORB4/callDescriptor.h>
#include <omniORB4/callHandle.h>
#include <omniORB4/objTracker.h>


OMNI_USING_NAMESPACE(omni)

static const char* _0RL_library_version = omniORB_4_1;



void
Obstacle::Point3D::operator>>= (cdrStream &_n) const
{
  x >>= _n;
  y >>= _n;
  z >>= _n;

}

void
Obstacle::Point3D::operator<<= (cdrStream &_n)
{
  (::CORBA::Float&)x <<= _n;
  (::CORBA::Float&)y <<= _n;
  (::CORBA::Float&)z <<= _n;

}

void
Obstacle::AABB::operator>>= (cdrStream &_n) const
{
  (const Point3D&) center >>= _n;
  rx >>= _n;
  ry >>= _n;
  rz >>= _n;

}

void
Obstacle::AABB::operator<<= (cdrStream &_n)
{
  (Point3D&)center <<= _n;
  (::CORBA::Float&)rx <<= _n;
  (::CORBA::Float&)ry <<= _n;
  (::CORBA::Float&)rz <<= _n;

}

Obstacle::ObstacleInterface_ptr Obstacle::ObstacleInterface_Helper::_nil() {
  return ::Obstacle::ObstacleInterface::_nil();
}

::CORBA::Boolean Obstacle::ObstacleInterface_Helper::is_nil(::Obstacle::ObstacleInterface_ptr p) {
  return ::CORBA::is_nil(p);

}

void Obstacle::ObstacleInterface_Helper::release(::Obstacle::ObstacleInterface_ptr p) {
  ::CORBA::release(p);
}

void Obstacle::ObstacleInterface_Helper::marshalObjRef(::Obstacle::ObstacleInterface_ptr obj, cdrStream& s) {
  ::Obstacle::ObstacleInterface::_marshalObjRef(obj, s);
}

Obstacle::ObstacleInterface_ptr Obstacle::ObstacleInterface_Helper::unmarshalObjRef(cdrStream& s) {
  return ::Obstacle::ObstacleInterface::_unmarshalObjRef(s);
}

void Obstacle::ObstacleInterface_Helper::duplicate(::Obstacle::ObstacleInterface_ptr obj) {
  if( obj && !obj->_NP_is_nil() )  omni::duplicateObjRef(obj);
}

Obstacle::ObstacleInterface_ptr
Obstacle::ObstacleInterface::_duplicate(::Obstacle::ObstacleInterface_ptr obj)
{
  if( obj && !obj->_NP_is_nil() )  omni::duplicateObjRef(obj);
  return obj;
}

Obstacle::ObstacleInterface_ptr
Obstacle::ObstacleInterface::_narrow(::CORBA::Object_ptr obj)
{
  if( !obj || obj->_NP_is_nil() || obj->_NP_is_pseudo() ) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_realNarrow(_PD_repoId);
  return e ? e : _nil();
}


Obstacle::ObstacleInterface_ptr
Obstacle::ObstacleInterface::_unchecked_narrow(::CORBA::Object_ptr obj)
{
  if( !obj || obj->_NP_is_nil() || obj->_NP_is_pseudo() ) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_uncheckedNarrow(_PD_repoId);
  return e ? e : _nil();
}

Obstacle::ObstacleInterface_ptr
Obstacle::ObstacleInterface::_nil()
{
#ifdef OMNI_UNLOADABLE_STUBS
  static _objref_ObstacleInterface _the_nil_obj;
  return &_the_nil_obj;
#else
  static _objref_ObstacleInterface* _the_nil_ptr = 0;
  if( !_the_nil_ptr ) {
    omni::nilRefLock().lock();
    if( !_the_nil_ptr ) {
      _the_nil_ptr = new _objref_ObstacleInterface;
      registerNilCorbaObject(_the_nil_ptr);
    }
    omni::nilRefLock().unlock();
  }
  return _the_nil_ptr;
#endif
}

const char* Obstacle::ObstacleInterface::_PD_repoId = "IDL:Obstacle/ObstacleInterface:1.0";


Obstacle::_objref_ObstacleInterface::~_objref_ObstacleInterface() {
  
}


Obstacle::_objref_ObstacleInterface::_objref_ObstacleInterface(omniIOR* ior, omniIdentity* id) :
   omniObjRef(::Obstacle::ObstacleInterface::_PD_repoId, ior, id, 1)
   
   
{
  _PR_setobj(this);
}

void*
Obstacle::_objref_ObstacleInterface::_ptrToObjRef(const char* id)
{
  if( id == ::Obstacle::ObstacleInterface::_PD_repoId )
    return (::Obstacle::ObstacleInterface_ptr) this;
  
  if( id == ::CORBA::Object::_PD_repoId )
    return (::CORBA::Object_ptr) this;

  if( omni::strMatch(id, ::Obstacle::ObstacleInterface::_PD_repoId) )
    return (::Obstacle::ObstacleInterface_ptr) this;
  
  if( omni::strMatch(id, ::CORBA::Object::_PD_repoId) )
    return (::CORBA::Object_ptr) this;

  return 0;
}

// Proxy call descriptor class. Mangled signature:
//  void_o_cObstacle_mAABBSeq
class _0RL_cd_2bb1f5c74612eaca_00000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_2bb1f5c74612eaca_00000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  
  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  Obstacle::AABBSeq_var arg_0;
};

void _0RL_cd_2bb1f5c74612eaca_00000000::marshalReturnedValues(cdrStream& _n)
{
  (const Obstacle::AABBSeq&) arg_0 >>= _n;

}

void _0RL_cd_2bb1f5c74612eaca_00000000::unmarshalReturnedValues(cdrStream& _n)
{
  arg_0 = new Obstacle::AABBSeq;
  (Obstacle::AABBSeq&)arg_0 <<= _n;

}

const char* const _0RL_cd_2bb1f5c74612eaca_00000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_2bb1f5c74612eaca_10000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_2bb1f5c74612eaca_00000000* tcd = (_0RL_cd_2bb1f5c74612eaca_00000000*)cd;
  Obstacle::_impl_ObstacleInterface* impl = (Obstacle::_impl_ObstacleInterface*) svnt->_ptrToInterface(Obstacle::ObstacleInterface::_PD_repoId);
  impl->getDisplayShelfObstacle(tcd->arg_0.out());


}

void Obstacle::_objref_ObstacleInterface::getDisplayShelfObstacle(::Obstacle::AABBSeq_out obastacleData)
{
  _0RL_cd_2bb1f5c74612eaca_00000000 _call_desc(_0RL_lcfn_2bb1f5c74612eaca_10000000, "getDisplayShelfObstacle", 24);


  _invoke(_call_desc);
  obastacleData = _call_desc.arg_0._retn();


}
Obstacle::_pof_ObstacleInterface::~_pof_ObstacleInterface() {}


omniObjRef*
Obstacle::_pof_ObstacleInterface::newObjRef(omniIOR* ior, omniIdentity* id)
{
  return new ::Obstacle::_objref_ObstacleInterface(ior, id);
}


::CORBA::Boolean
Obstacle::_pof_ObstacleInterface::is_a(const char* id) const
{
  if( omni::ptrStrMatch(id, ::Obstacle::ObstacleInterface::_PD_repoId) )
    return 1;
  
  return 0;
}

const Obstacle::_pof_ObstacleInterface _the_pof_Obstacle_mObstacleInterface;

Obstacle::_impl_ObstacleInterface::~_impl_ObstacleInterface() {}


::CORBA::Boolean
Obstacle::_impl_ObstacleInterface::_dispatch(omniCallHandle& _handle)
{
  const char* op = _handle.operation_name();

  if( omni::strMatch(op, "getDisplayShelfObstacle") ) {

    _0RL_cd_2bb1f5c74612eaca_00000000 _call_desc(_0RL_lcfn_2bb1f5c74612eaca_10000000, "getDisplayShelfObstacle", 24, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }


  return 0;
}

void*
Obstacle::_impl_ObstacleInterface::_ptrToInterface(const char* id)
{
  if( id == ::Obstacle::ObstacleInterface::_PD_repoId )
    return (::Obstacle::_impl_ObstacleInterface*) this;
  
  if( id == ::CORBA::Object::_PD_repoId )
    return (void*) 1;

  if( omni::strMatch(id, ::Obstacle::ObstacleInterface::_PD_repoId) )
    return (::Obstacle::_impl_ObstacleInterface*) this;
  
  if( omni::strMatch(id, ::CORBA::Object::_PD_repoId) )
    return (void*) 1;
  return 0;
}

const char*
Obstacle::_impl_ObstacleInterface::_mostDerivedRepoId()
{
  return ::Obstacle::ObstacleInterface::_PD_repoId;
}

POA_Obstacle::ObstacleInterface::~ObstacleInterface() {}

