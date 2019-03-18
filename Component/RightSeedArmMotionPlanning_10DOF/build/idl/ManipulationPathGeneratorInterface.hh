// This file is generated by omniidl (C++ backend)- omniORB_4_1. Do not edit.
#ifndef __ManipulationPathGeneratorInterface_hh__
#define __ManipulationPathGeneratorInterface_hh__

#ifndef __CORBA_H_EXTERNAL_GUARD__
#include <omniORB4/CORBA.h>
#endif

#ifndef  USE_stub_in_nt_dll
# define USE_stub_in_nt_dll_NOT_DEFINED_ManipulationPathGeneratorInterface
#endif
#ifndef  USE_core_stub_in_nt_dll
# define USE_core_stub_in_nt_dll_NOT_DEFINED_ManipulationPathGeneratorInterface
#endif
#ifndef  USE_dyn_stub_in_nt_dll
# define USE_dyn_stub_in_nt_dll_NOT_DEFINED_ManipulationPathGeneratorInterface
#endif



#ifndef __BasicDataType_hh_EXTERNAL_GUARD__
#define __BasicDataType_hh_EXTERNAL_GUARD__
#include "BasicDataType.hh"
#endif



#ifdef USE_stub_in_nt_dll
# ifndef USE_core_stub_in_nt_dll
#  define USE_core_stub_in_nt_dll
# endif
# ifndef USE_dyn_stub_in_nt_dll
#  define USE_dyn_stub_in_nt_dll
# endif
#endif

#ifdef _core_attr
# error "A local CPP macro _core_attr has already been defined."
#else
# ifdef  USE_core_stub_in_nt_dll
#  define _core_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _core_attr
# endif
#endif

#ifdef _dyn_attr
# error "A local CPP macro _dyn_attr has already been defined."
#else
# ifdef  USE_dyn_stub_in_nt_dll
#  define _dyn_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _dyn_attr
# endif
#endif





_CORBA_MODULE Manipulation

_CORBA_MODULE_BEG

  struct RETURN_ID {
    typedef _CORBA_ConstrType_Variable_Var<RETURN_ID> _var_type;

    
    ::CORBA::Long id;

    ::CORBA::String_member comment;

  

    void operator>>= (cdrStream &) const;
    void operator<<= (cdrStream &);
  };

  typedef RETURN_ID::_var_type RETURN_ID_var;

  typedef _CORBA_ConstrType_Variable_OUT_arg< RETURN_ID,RETURN_ID_var > RETURN_ID_out;

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_RETURN_ID;

  struct WaistPos {
    typedef _CORBA_ConstrType_Fix_Var<WaistPos> _var_type;

    
    ::CORBA::Double roll;

    ::CORBA::Double pitch;

    ::CORBA::Double yaw;

  

    void operator>>= (cdrStream &) const;
    void operator<<= (cdrStream &);
  };

  typedef WaistPos::_var_type WaistPos_var;

  typedef WaistPos& WaistPos_out;

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_WaistPos;

  struct LifterPos {
    typedef _CORBA_ConstrType_Fix_Var<LifterPos> _var_type;

    
    ::CORBA::Double bottom;

    ::CORBA::Double top;

  

    void operator>>= (cdrStream &) const;
    void operator<<= (cdrStream &);
  };

  typedef LifterPos::_var_type LifterPos_var;

  typedef LifterPos& LifterPos_out;

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_LifterPos;

  _CORBA_MODULE_VARINT const ::CORBA::Long OK _init_in_decl_( = 0 );

  _CORBA_MODULE_VARINT const ::CORBA::Long NG _init_in_decl_( = -1 );

  _CORBA_MODULE_VARINT const ::CORBA::Long STATUS_ERR _init_in_decl_( = -2 );

  _CORBA_MODULE_VARINT const ::CORBA::Long VALUE_ERR _init_in_decl_( = -3 );

  _CORBA_MODULE_VARINT const ::CORBA::Long NOT_SV_ON_ERR _init_in_decl_( = -4 );

  _CORBA_MODULE_VARINT const ::CORBA::Long FULL_MOTION_QUEUE_ERR _init_in_decl_( = -5 );

  _CORBA_MODULE_VARINT const ::CORBA::Long NOT_IMPLEMENTED _init_in_decl_( = -6 );

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_JointAngleSeq;

  class JointAngleSeq_var;

  class JointAngleSeq : public _CORBA_Unbounded_Sequence_w_FixSizeElement< ::CORBA::Double, 8, 8 >  {
  public:
    typedef JointAngleSeq_var _var_type;
    inline JointAngleSeq() {}
    inline JointAngleSeq(const JointAngleSeq& _s)
      : _CORBA_Unbounded_Sequence_w_FixSizeElement< ::CORBA::Double, 8, 8 > (_s) {}

    inline JointAngleSeq(_CORBA_ULong _max)
      : _CORBA_Unbounded_Sequence_w_FixSizeElement< ::CORBA::Double, 8, 8 > (_max) {}
    inline JointAngleSeq(_CORBA_ULong _max, _CORBA_ULong _len, ::CORBA::Double* _val, _CORBA_Boolean _rel=0)
      : _CORBA_Unbounded_Sequence_w_FixSizeElement< ::CORBA::Double, 8, 8 > (_max, _len, _val, _rel) {}

  

    inline JointAngleSeq& operator = (const JointAngleSeq& _s) {
      _CORBA_Unbounded_Sequence_w_FixSizeElement< ::CORBA::Double, 8, 8 > ::operator=(_s);
      return *this;
    }
  };

  class JointAngleSeq_out;

  class JointAngleSeq_var {
  public:
    inline JointAngleSeq_var() : _pd_seq(0) {}
    inline JointAngleSeq_var(JointAngleSeq* _s) : _pd_seq(_s) {}
    inline JointAngleSeq_var(const JointAngleSeq_var& _s) {
      if( _s._pd_seq )  _pd_seq = new JointAngleSeq(*_s._pd_seq);
      else              _pd_seq = 0;
    }
    inline ~JointAngleSeq_var() { if( _pd_seq )  delete _pd_seq; }
      
    inline JointAngleSeq_var& operator = (JointAngleSeq* _s) {
      if( _pd_seq )  delete _pd_seq;
      _pd_seq = _s;
      return *this;
    }
    inline JointAngleSeq_var& operator = (const JointAngleSeq_var& _s) {
      if( _s._pd_seq ) {
        if( !_pd_seq )  _pd_seq = new JointAngleSeq;
        *_pd_seq = *_s._pd_seq;
      } else if( _pd_seq ) {
        delete _pd_seq;
        _pd_seq = 0;
      }
      return *this;
    }
    inline ::CORBA::Double& operator [] (_CORBA_ULong _s) {
      return (*_pd_seq)[_s];
    }

  

    inline JointAngleSeq* operator -> () { return _pd_seq; }
    inline const JointAngleSeq* operator -> () const { return _pd_seq; }
#if defined(__GNUG__)
    inline operator JointAngleSeq& () const { return *_pd_seq; }
#else
    inline operator const JointAngleSeq& () const { return *_pd_seq; }
    inline operator JointAngleSeq& () { return *_pd_seq; }
#endif
      
    inline const JointAngleSeq& in() const { return *_pd_seq; }
    inline JointAngleSeq&       inout()    { return *_pd_seq; }
    inline JointAngleSeq*&      out() {
      if( _pd_seq ) { delete _pd_seq; _pd_seq = 0; }
      return _pd_seq;
    }
    inline JointAngleSeq* _retn() { JointAngleSeq* tmp = _pd_seq; _pd_seq = 0; return tmp; }
      
    friend class JointAngleSeq_out;
    
  private:
    JointAngleSeq* _pd_seq;
  };

  class JointAngleSeq_out {
  public:
    inline JointAngleSeq_out(JointAngleSeq*& _s) : _data(_s) { _data = 0; }
    inline JointAngleSeq_out(JointAngleSeq_var& _s)
      : _data(_s._pd_seq) { _s = (JointAngleSeq*) 0; }
    inline JointAngleSeq_out(const JointAngleSeq_out& _s) : _data(_s._data) {}
    inline JointAngleSeq_out& operator = (const JointAngleSeq_out& _s) {
      _data = _s._data;
      return *this;
    }
    inline JointAngleSeq_out& operator = (JointAngleSeq* _s) {
      _data = _s;
      return *this;
    }
    inline operator JointAngleSeq*&()  { return _data; }
    inline JointAngleSeq*& ptr()       { return _data; }
    inline JointAngleSeq* operator->() { return _data; }

    inline ::CORBA::Double& operator [] (_CORBA_ULong _i) {
      return (*_data)[_i];
    }

  

    JointAngleSeq*& _data;

  private:
    JointAngleSeq_out();
    JointAngleSeq_out& operator=(const JointAngleSeq_var&);
  };

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_ViaPosSeq;

  class ViaPosSeq_var;

  class ViaPosSeq : public _CORBA_Unbounded_Sequence< JointAngleSeq >  {
  public:
    typedef ViaPosSeq_var _var_type;
    inline ViaPosSeq() {}
    inline ViaPosSeq(const ViaPosSeq& _s)
      : _CORBA_Unbounded_Sequence< JointAngleSeq > (_s) {}

    inline ViaPosSeq(_CORBA_ULong _max)
      : _CORBA_Unbounded_Sequence< JointAngleSeq > (_max) {}
    inline ViaPosSeq(_CORBA_ULong _max, _CORBA_ULong _len, JointAngleSeq* _val, _CORBA_Boolean _rel=0)
      : _CORBA_Unbounded_Sequence< JointAngleSeq > (_max, _len, _val, _rel) {}

  

    inline ViaPosSeq& operator = (const ViaPosSeq& _s) {
      _CORBA_Unbounded_Sequence< JointAngleSeq > ::operator=(_s);
      return *this;
    }
  };

  class ViaPosSeq_out;

  class ViaPosSeq_var {
  public:
    inline ViaPosSeq_var() : _pd_seq(0) {}
    inline ViaPosSeq_var(ViaPosSeq* _s) : _pd_seq(_s) {}
    inline ViaPosSeq_var(const ViaPosSeq_var& _s) {
      if( _s._pd_seq )  _pd_seq = new ViaPosSeq(*_s._pd_seq);
      else              _pd_seq = 0;
    }
    inline ~ViaPosSeq_var() { if( _pd_seq )  delete _pd_seq; }
      
    inline ViaPosSeq_var& operator = (ViaPosSeq* _s) {
      if( _pd_seq )  delete _pd_seq;
      _pd_seq = _s;
      return *this;
    }
    inline ViaPosSeq_var& operator = (const ViaPosSeq_var& _s) {
      if( _s._pd_seq ) {
        if( !_pd_seq )  _pd_seq = new ViaPosSeq;
        *_pd_seq = *_s._pd_seq;
      } else if( _pd_seq ) {
        delete _pd_seq;
        _pd_seq = 0;
      }
      return *this;
    }
    inline JointAngleSeq& operator [] (_CORBA_ULong _s) {
      return (*_pd_seq)[_s];
    }

  

    inline ViaPosSeq* operator -> () { return _pd_seq; }
    inline const ViaPosSeq* operator -> () const { return _pd_seq; }
#if defined(__GNUG__)
    inline operator ViaPosSeq& () const { return *_pd_seq; }
#else
    inline operator const ViaPosSeq& () const { return *_pd_seq; }
    inline operator ViaPosSeq& () { return *_pd_seq; }
#endif
      
    inline const ViaPosSeq& in() const { return *_pd_seq; }
    inline ViaPosSeq&       inout()    { return *_pd_seq; }
    inline ViaPosSeq*&      out() {
      if( _pd_seq ) { delete _pd_seq; _pd_seq = 0; }
      return _pd_seq;
    }
    inline ViaPosSeq* _retn() { ViaPosSeq* tmp = _pd_seq; _pd_seq = 0; return tmp; }
      
    friend class ViaPosSeq_out;
    
  private:
    ViaPosSeq* _pd_seq;
  };

  class ViaPosSeq_out {
  public:
    inline ViaPosSeq_out(ViaPosSeq*& _s) : _data(_s) { _data = 0; }
    inline ViaPosSeq_out(ViaPosSeq_var& _s)
      : _data(_s._pd_seq) { _s = (ViaPosSeq*) 0; }
    inline ViaPosSeq_out(const ViaPosSeq_out& _s) : _data(_s._data) {}
    inline ViaPosSeq_out& operator = (const ViaPosSeq_out& _s) {
      _data = _s._data;
      return *this;
    }
    inline ViaPosSeq_out& operator = (ViaPosSeq* _s) {
      _data = _s;
      return *this;
    }
    inline operator ViaPosSeq*&()  { return _data; }
    inline ViaPosSeq*& ptr()       { return _data; }
    inline ViaPosSeq* operator->() { return _data; }

    inline JointAngleSeq& operator [] (_CORBA_ULong _i) {
      return (*_data)[_i];
    }

  

    ViaPosSeq*& _data;

  private:
    ViaPosSeq_out();
    ViaPosSeq_out& operator=(const ViaPosSeq_var&);
  };

  struct DualUpperJoint {
    typedef _CORBA_ConstrType_Variable_Var<DualUpperJoint> _var_type;

    
    JointAngleSeq right;

    JointAngleSeq left;

    WaistPos waist;

    LifterPos lifter;

  

    void operator>>= (cdrStream &) const;
    void operator<<= (cdrStream &);
  };

  typedef DualUpperJoint::_var_type DualUpperJoint_var;

  typedef _CORBA_ConstrType_Variable_OUT_arg< DualUpperJoint,DualUpperJoint_var > DualUpperJoint_out;

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_DualUpperJoint;

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_ViaDualUpperJointSeq;

  class ViaDualUpperJointSeq_var;

  class ViaDualUpperJointSeq : public _CORBA_Unbounded_Sequence< DualUpperJoint >  {
  public:
    typedef ViaDualUpperJointSeq_var _var_type;
    inline ViaDualUpperJointSeq() {}
    inline ViaDualUpperJointSeq(const ViaDualUpperJointSeq& _s)
      : _CORBA_Unbounded_Sequence< DualUpperJoint > (_s) {}

    inline ViaDualUpperJointSeq(_CORBA_ULong _max)
      : _CORBA_Unbounded_Sequence< DualUpperJoint > (_max) {}
    inline ViaDualUpperJointSeq(_CORBA_ULong _max, _CORBA_ULong _len, DualUpperJoint* _val, _CORBA_Boolean _rel=0)
      : _CORBA_Unbounded_Sequence< DualUpperJoint > (_max, _len, _val, _rel) {}

  

    inline ViaDualUpperJointSeq& operator = (const ViaDualUpperJointSeq& _s) {
      _CORBA_Unbounded_Sequence< DualUpperJoint > ::operator=(_s);
      return *this;
    }
  };

  class ViaDualUpperJointSeq_out;

  class ViaDualUpperJointSeq_var {
  public:
    inline ViaDualUpperJointSeq_var() : _pd_seq(0) {}
    inline ViaDualUpperJointSeq_var(ViaDualUpperJointSeq* _s) : _pd_seq(_s) {}
    inline ViaDualUpperJointSeq_var(const ViaDualUpperJointSeq_var& _s) {
      if( _s._pd_seq )  _pd_seq = new ViaDualUpperJointSeq(*_s._pd_seq);
      else              _pd_seq = 0;
    }
    inline ~ViaDualUpperJointSeq_var() { if( _pd_seq )  delete _pd_seq; }
      
    inline ViaDualUpperJointSeq_var& operator = (ViaDualUpperJointSeq* _s) {
      if( _pd_seq )  delete _pd_seq;
      _pd_seq = _s;
      return *this;
    }
    inline ViaDualUpperJointSeq_var& operator = (const ViaDualUpperJointSeq_var& _s) {
      if( _s._pd_seq ) {
        if( !_pd_seq )  _pd_seq = new ViaDualUpperJointSeq;
        *_pd_seq = *_s._pd_seq;
      } else if( _pd_seq ) {
        delete _pd_seq;
        _pd_seq = 0;
      }
      return *this;
    }
    inline DualUpperJoint& operator [] (_CORBA_ULong _s) {
      return (*_pd_seq)[_s];
    }

  

    inline ViaDualUpperJointSeq* operator -> () { return _pd_seq; }
    inline const ViaDualUpperJointSeq* operator -> () const { return _pd_seq; }
#if defined(__GNUG__)
    inline operator ViaDualUpperJointSeq& () const { return *_pd_seq; }
#else
    inline operator const ViaDualUpperJointSeq& () const { return *_pd_seq; }
    inline operator ViaDualUpperJointSeq& () { return *_pd_seq; }
#endif
      
    inline const ViaDualUpperJointSeq& in() const { return *_pd_seq; }
    inline ViaDualUpperJointSeq&       inout()    { return *_pd_seq; }
    inline ViaDualUpperJointSeq*&      out() {
      if( _pd_seq ) { delete _pd_seq; _pd_seq = 0; }
      return _pd_seq;
    }
    inline ViaDualUpperJointSeq* _retn() { ViaDualUpperJointSeq* tmp = _pd_seq; _pd_seq = 0; return tmp; }
      
    friend class ViaDualUpperJointSeq_out;
    
  private:
    ViaDualUpperJointSeq* _pd_seq;
  };

  class ViaDualUpperJointSeq_out {
  public:
    inline ViaDualUpperJointSeq_out(ViaDualUpperJointSeq*& _s) : _data(_s) { _data = 0; }
    inline ViaDualUpperJointSeq_out(ViaDualUpperJointSeq_var& _s)
      : _data(_s._pd_seq) { _s = (ViaDualUpperJointSeq*) 0; }
    inline ViaDualUpperJointSeq_out(const ViaDualUpperJointSeq_out& _s) : _data(_s._data) {}
    inline ViaDualUpperJointSeq_out& operator = (const ViaDualUpperJointSeq_out& _s) {
      _data = _s._data;
      return *this;
    }
    inline ViaDualUpperJointSeq_out& operator = (ViaDualUpperJointSeq* _s) {
      _data = _s;
      return *this;
    }
    inline operator ViaDualUpperJointSeq*&()  { return _data; }
    inline ViaDualUpperJointSeq*& ptr()       { return _data; }
    inline ViaDualUpperJointSeq* operator->() { return _data; }

    inline DualUpperJoint& operator [] (_CORBA_ULong _i) {
      return (*_data)[_i];
    }

  

    ViaDualUpperJointSeq*& _data;

  private:
    ViaDualUpperJointSeq_out();
    ViaDualUpperJointSeq_out& operator=(const ViaDualUpperJointSeq_var&);
  };

#ifndef __Manipulation_mPathGeneratorInterface__
#define __Manipulation_mPathGeneratorInterface__

  class PathGeneratorInterface;
  class _objref_PathGeneratorInterface;
  class _impl_PathGeneratorInterface;
  
  typedef _objref_PathGeneratorInterface* PathGeneratorInterface_ptr;
  typedef PathGeneratorInterface_ptr PathGeneratorInterfaceRef;

  class PathGeneratorInterface_Helper {
  public:
    typedef PathGeneratorInterface_ptr _ptr_type;

    static _ptr_type _nil();
    static _CORBA_Boolean is_nil(_ptr_type);
    static void release(_ptr_type);
    static void duplicate(_ptr_type);
    static void marshalObjRef(_ptr_type, cdrStream&);
    static _ptr_type unmarshalObjRef(cdrStream&);
  };

  typedef _CORBA_ObjRef_Var<_objref_PathGeneratorInterface, PathGeneratorInterface_Helper> PathGeneratorInterface_var;
  typedef _CORBA_ObjRef_OUT_arg<_objref_PathGeneratorInterface,PathGeneratorInterface_Helper > PathGeneratorInterface_out;

#endif

  // interface PathGeneratorInterface
  class PathGeneratorInterface {
  public:
    // Declarations for this interface type.
    typedef PathGeneratorInterface_ptr _ptr_type;
    typedef PathGeneratorInterface_var _var_type;

    static _ptr_type _duplicate(_ptr_type);
    static _ptr_type _narrow(::CORBA::Object_ptr);
    static _ptr_type _unchecked_narrow(::CORBA::Object_ptr);
    
    static _ptr_type _nil();

    static inline void _marshalObjRef(_ptr_type, cdrStream&);

    static inline _ptr_type _unmarshalObjRef(cdrStream& s) {
      omniObjRef* o = omniObjRef::_unMarshal(_PD_repoId,s);
      if (o)
        return (_ptr_type) o->_ptrToObjRef(_PD_repoId);
      else
        return _nil();
    }

    static _core_attr const char* _PD_repoId;

    // Other IDL defined within this scope.
    
  };

  class _objref_PathGeneratorInterface :
    public virtual ::CORBA::Object,
    public virtual omniObjRef
  {
  public:
    RETURN_ID* JointSpaceGenerateRightArmMotion(const ::Manipulation::JointAngleSeq& goalJointPos);
    RETURN_ID* JointSpaceGenerateRightArmViaMotion(const ::Manipulation::ViaPosSeq& viaJointPos, const ::Manipulation::JointAngleSeq& goalJointPos);
    RETURN_ID* JointSpaceGenerateLeftArmMotion(const ::Manipulation::JointAngleSeq& goalJointPos);
    RETURN_ID* JointSpaceGenerateLeftArmViaMotion(const ::Manipulation::ViaPosSeq& viaJointPos, const ::Manipulation::JointAngleSeq& goalJointPos);
    RETURN_ID* JointSpaceGenerateDualArmMotion(const ::Manipulation::DualUpperJoint& goalJointPos);
    RETURN_ID* JointSpaceGenerateDualArmViaMotion(const ::Manipulation::ViaDualUpperJointSeq& viaJointPos, const ::Manipulation::DualUpperJoint& goalJointPos);

    inline _objref_PathGeneratorInterface()  { _PR_setobj(0); }  // nil
    _objref_PathGeneratorInterface(omniIOR*, omniIdentity*);

  protected:
    virtual ~_objref_PathGeneratorInterface();

    
  private:
    virtual void* _ptrToObjRef(const char*);

    _objref_PathGeneratorInterface(const _objref_PathGeneratorInterface&);
    _objref_PathGeneratorInterface& operator = (const _objref_PathGeneratorInterface&);
    // not implemented

    friend class PathGeneratorInterface;
  };

  class _pof_PathGeneratorInterface : public _OMNI_NS(proxyObjectFactory) {
  public:
    inline _pof_PathGeneratorInterface() : _OMNI_NS(proxyObjectFactory)(PathGeneratorInterface::_PD_repoId) {}
    virtual ~_pof_PathGeneratorInterface();

    virtual omniObjRef* newObjRef(omniIOR*,omniIdentity*);
    virtual _CORBA_Boolean is_a(const char*) const;
  };

  class _impl_PathGeneratorInterface :
    public virtual omniServant
  {
  public:
    virtual ~_impl_PathGeneratorInterface();

    virtual RETURN_ID* JointSpaceGenerateRightArmMotion(const ::Manipulation::JointAngleSeq& goalJointPos) = 0;
    virtual RETURN_ID* JointSpaceGenerateRightArmViaMotion(const ::Manipulation::ViaPosSeq& viaJointPos, const ::Manipulation::JointAngleSeq& goalJointPos) = 0;
    virtual RETURN_ID* JointSpaceGenerateLeftArmMotion(const ::Manipulation::JointAngleSeq& goalJointPos) = 0;
    virtual RETURN_ID* JointSpaceGenerateLeftArmViaMotion(const ::Manipulation::ViaPosSeq& viaJointPos, const ::Manipulation::JointAngleSeq& goalJointPos) = 0;
    virtual RETURN_ID* JointSpaceGenerateDualArmMotion(const ::Manipulation::DualUpperJoint& goalJointPos) = 0;
    virtual RETURN_ID* JointSpaceGenerateDualArmViaMotion(const ::Manipulation::ViaDualUpperJointSeq& viaJointPos, const ::Manipulation::DualUpperJoint& goalJointPos) = 0;
    
  public:  // Really protected, workaround for xlC
    virtual _CORBA_Boolean _dispatch(omniCallHandle&);

  private:
    virtual void* _ptrToInterface(const char*);
    virtual const char* _mostDerivedRepoId();
    
  };


  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_PathGeneratorInterface;

_CORBA_MODULE_END



_CORBA_MODULE POA_Manipulation
_CORBA_MODULE_BEG

  class PathGeneratorInterface :
    public virtual Manipulation::_impl_PathGeneratorInterface,
    public virtual ::PortableServer::ServantBase
  {
  public:
    virtual ~PathGeneratorInterface();

    inline ::Manipulation::PathGeneratorInterface_ptr _this() {
      return (::Manipulation::PathGeneratorInterface_ptr) _do_this(::Manipulation::PathGeneratorInterface::_PD_repoId);
    }
  };

_CORBA_MODULE_END



_CORBA_MODULE OBV_Manipulation
_CORBA_MODULE_BEG

_CORBA_MODULE_END





#undef _core_attr
#undef _dyn_attr

extern void operator<<=(::CORBA::Any& _a, const Manipulation::RETURN_ID& _s);
extern void operator<<=(::CORBA::Any& _a, Manipulation::RETURN_ID* _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, Manipulation::RETURN_ID*& _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const Manipulation::RETURN_ID*& _sp);

extern void operator<<=(::CORBA::Any& _a, const Manipulation::WaistPos& _s);
extern void operator<<=(::CORBA::Any& _a, Manipulation::WaistPos* _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, Manipulation::WaistPos*& _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const Manipulation::WaistPos*& _sp);

extern void operator<<=(::CORBA::Any& _a, const Manipulation::LifterPos& _s);
extern void operator<<=(::CORBA::Any& _a, Manipulation::LifterPos* _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, Manipulation::LifterPos*& _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const Manipulation::LifterPos*& _sp);

void operator<<=(::CORBA::Any& _a, const Manipulation::JointAngleSeq& _s);
void operator<<=(::CORBA::Any& _a, Manipulation::JointAngleSeq* _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, Manipulation::JointAngleSeq*& _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const Manipulation::JointAngleSeq*& _sp);

void operator<<=(::CORBA::Any& _a, const Manipulation::ViaPosSeq& _s);
void operator<<=(::CORBA::Any& _a, Manipulation::ViaPosSeq* _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, Manipulation::ViaPosSeq*& _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const Manipulation::ViaPosSeq*& _sp);

extern void operator<<=(::CORBA::Any& _a, const Manipulation::DualUpperJoint& _s);
extern void operator<<=(::CORBA::Any& _a, Manipulation::DualUpperJoint* _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, Manipulation::DualUpperJoint*& _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const Manipulation::DualUpperJoint*& _sp);

void operator<<=(::CORBA::Any& _a, const Manipulation::ViaDualUpperJointSeq& _s);
void operator<<=(::CORBA::Any& _a, Manipulation::ViaDualUpperJointSeq* _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, Manipulation::ViaDualUpperJointSeq*& _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const Manipulation::ViaDualUpperJointSeq*& _sp);

void operator<<=(::CORBA::Any& _a, Manipulation::PathGeneratorInterface_ptr _s);
void operator<<=(::CORBA::Any& _a, Manipulation::PathGeneratorInterface_ptr* _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, Manipulation::PathGeneratorInterface_ptr& _s);



inline void
Manipulation::PathGeneratorInterface::_marshalObjRef(::Manipulation::PathGeneratorInterface_ptr obj, cdrStream& s) {
  omniObjRef::_marshal(obj->_PR_getobj(),s);
}




#ifdef   USE_stub_in_nt_dll_NOT_DEFINED_ManipulationPathGeneratorInterface
# undef  USE_stub_in_nt_dll
# undef  USE_stub_in_nt_dll_NOT_DEFINED_ManipulationPathGeneratorInterface
#endif
#ifdef   USE_core_stub_in_nt_dll_NOT_DEFINED_ManipulationPathGeneratorInterface
# undef  USE_core_stub_in_nt_dll
# undef  USE_core_stub_in_nt_dll_NOT_DEFINED_ManipulationPathGeneratorInterface
#endif
#ifdef   USE_dyn_stub_in_nt_dll_NOT_DEFINED_ManipulationPathGeneratorInterface
# undef  USE_dyn_stub_in_nt_dll
# undef  USE_dyn_stub_in_nt_dll_NOT_DEFINED_ManipulationPathGeneratorInterface
#endif

#endif  // __ManipulationPathGeneratorInterface_hh__
