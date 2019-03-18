// -*- C++ -*-
/*!
 * @file  SeedUpperBodyRTC.h
 * @brief SeedUpperBodyRTC
 * @date  $Date$
 *
 * $Id$
 */

#ifndef SEEDUPPERBODYRTC_H
#define SEEDUPPERBODYRTC_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">
#include "SeedUpperInterface_CommonSVC_impl.h"
#include "SeedUpperInterface_MiddleLevelSVC_impl.h"
#include "WaistNeckInterfaceSVC_impl.h"

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">
#include "SeedNoid_LifterStub.h"

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="port_stub_h">
// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

using namespace RTC;

#include "LibSeednoidUpper.h"

/*!
 * @class SeedUpperBodyRTC
 * @brief SeedUpperBodyRTC
 *
 */
class SeedUpperBodyRTC
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  SeedUpperBodyRTC(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~SeedUpperBodyRTC();

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   * formaer rtc_init_entry() 
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onInitialize();

  /***
   *
   * The finalize action (on ALIVE->END transition)
   * formaer rtc_exiting_entry()
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onFinalize();

  /***
   *
   * The startup action when ExecutionContext startup
   * former rtc_starting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

  /***
   *
   * The shutdown action when ExecutionContext stop
   * former rtc_stopping_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

  /***
   *
   * The activated action (Active state entry action)
   * former rtc_active_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

  /***
   *
   * The deactivated action (Active state exit action)
   * former rtc_active_exit()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  /***
   *
   * The execution action that is invoked periodically
   * former rtc_active_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  /***
   *
   * The aborting action when main logic error occurred.
   * former rtc_aborting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

  /***
   *
   * The error action in ERROR state
   * former rtc_error_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

  /***
   *
   * The reset action that is invoked resetting
   * This is same but different the former rtc_init_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

  /***
   *
   * The action that is invoked when execution context's rate is changed
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);
  void getLifterPos(double lifterPos[]);
  void movePTPLifter(double lifterPos[]);

  SeedUpper noid;
  void readAllJointAngle(Frame* nowWaistPos,Frame* nowNeckPos,double nowRightJointPos[],double nowLeftJointPos[])
  {
    Frame WaistPos;
    Frame NeckPos;
    noid.readAllJointAngle(&WaistPos,&NeckPos,nowRightJointPos,nowLeftJointPos);
    nowWaistPos->yaw = WaistPos.yaw;
    nowWaistPos->pitch = WaistPos.pitch;
    nowWaistPos->roll = WaistPos.roll;
    nowNeckPos->yaw = NeckPos.yaw;
    nowNeckPos->pitch = NeckPos.pitch;
    nowNeckPos->roll = NeckPos.roll;
  }
  Frame readNeckJointAngle()
  {
    Frame NeckPos;
    NeckPos = noid.readNeckJointAngle();
    return NeckPos;
  }
  Frame readWaistJointAngle()
  {
    Frame WaistPos;
    WaistPos = noid.readWaistJointAngle();
    return WaistPos;
  }
  void ServoON()
  {
    int torque = 1;
    noid.ServoOnOff(torque);
  }
  void ServoOFF()
  {
    int torque = 0;
    noid.ServoOnOff(torque);
  }
  void CloseRightGripper()
  {
    noid.CloseRightGripper();
  }
  void OpenRightGripper()
  {
    noid.OpenRightGripper();
  }
  void MoveRightGripper(int ratio)
  {
    noid.MoveRightGripper(ratio);
  }
  void setRightHandCurrent(int ratio)
  {
    noid.setRightHandCurrent(ratio);
  }
  void CloseLeftGripper()
  {
    noid.CloseLeftGripper();
  }
  void OpenLeftGripper()
  {
    noid.OpenLeftGripper();
  }
  void MoveLeftGripper(int ratio)
  {
    noid.MoveLeftGripper(ratio);
  }
  void setLeftHandCurrent(int ratio)
  {
    noid.setLeftHandCurrent(ratio);
  }
  int Solve_LIWARArmIkSetRedun(double eerot[],double eetrans[],double elbow,Frame targetWaistPos,double targetLifterPos[],double nowJointPos[],double iksol[])
  {
    int ret = noid.Solve_LIWARArmIkSetRedun(eerot,eetrans,elbow,targetWaistPos,targetLifterPos,nowJointPos,iksol);
    return ret;
  }
  int Solve_LIWALArmIkSetRedun(double eerot[],double eetrans[],double elbow,Frame targetWaistPos,double targetLifterPos[],double nowJointPos[],double iksol[])
  {
    int ret = noid.Solve_LIWALArmIkSetRedun(eerot,eetrans,elbow,targetWaistPos,targetLifterPos,nowJointPos,iksol);
    return ret;
  }
  int Solve_LIWARArmIk(double eerot[],double eetrans[],double nowJointPos[],double iksol[])
  {
    int ret = noid.Solve_LIWARArmIk(eerot,eetrans,nowJointPos,iksol);
    return ret;
  }
  int Solve_LIWALArmIk(double eerot[],double eetrans[],double nowJointPos[],double iksol[])
  {
    int ret = noid.Solve_LIWALArmIk(eerot,eetrans,nowJointPos,iksol);
    return ret;
  }
  void Solve_LIWARArmFk(double eerot[9],double eetrans[3], double joint[])
  {
    noid.Solve_LIWARArmFk(eerot,eetrans,joint);
  }
  void Solve_LIWALArmFk(double eerot[9],double eetrans[3], double joint[])
  {
    noid.Solve_LIWALArmFk(eerot,eetrans,joint);
  }
  void setRightJointAngle(double JointPos[])
  {
    noid.setRightJointAngle(JointPos);
  }
  void setLeftJointAngle(double JointPos[])
  {
    noid.setLeftJointAngle(JointPos);
  }
  void setWaistJointAngle(Frame pos)
  {
    noid.setWaistJointAngle(pos);
  }
  void setNeckJointAngle(Frame pos)
  {
    noid.setNeckJointAngle(pos);
  }
  void SeedAction(int movetime)
  {
    noid.SeedAction(movetime);
  }

 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">
  /*!
   * 
   * - Name:  port_name
   * - DefaultValue: /dev/ttyUSB0
   */
  std::string m_port_name;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  /*!
   */
  RTC::CorbaPort m_SeedUpperInterface_CommonPort;
  /*!
   */
  RTC::CorbaPort m_SeedUpperInterface_MiddlePort;
  /*!
   */
  RTC::CorbaPort m_WaistInterfacePort;
  /*!
   */
  RTC::CorbaPort m_NeckInterfacePort;
  /*!
   */
  RTC::CorbaPort m_LifterPosePort;
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  /*!
   */
  SEED_UPPER_SeedUpperInterface_CommonSVC_impl m_SeedUpperInterface_Common;
  /*!
   */
  SEED_UPPER_SeedUpperInterface_MiddleSVC_impl m_SeedUpperInterface_Middle;
  /*!
   */
  WaistNeck_WaistInterfaceSVC_impl m_WaistInterface;
  /*!
   */
  WaistNeck_NeckInterfaceSVC_impl m_NeckInterface;
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  /*!
   */
  RTC::CorbaConsumer<SeedNoid_Lifter::LifterPose> m_LifterPose;
  
  // </rtc-template>

 private:
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>  

  
};


extern "C"
{
  DLL_EXPORT void SeedUpperBodyRTCInit(RTC::Manager* manager);
};

#endif // SEEDUPPERBODYRTC_H
