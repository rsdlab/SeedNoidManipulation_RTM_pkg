// -*- C++ -*-
/*!
 * @file  SeedUpperBodyTestController.cpp
 * @brief SeedUpperBodyTestController
 * @date $Date$
 *
 * $Id$
 */

#include "SeedUpperBodyTestController.h"
#include <math.h>

// Module specification
// <rtc-template block="module_spec">
static const char* seedupperbodytestcontroller_spec[] =
  {
    "implementation_id", "SeedUpperBodyTestController",
    "type_name",         "SeedUpperBodyTestController",
    "description",       "SeedUpperBodyTestController",
    "version",           "1.0.0",
    "vendor",            "rsdlab",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
SeedUpperBodyTestController::SeedUpperBodyTestController(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_SeedUpperInterface_CommonPort("SeedUpperInterface_Common"),
    m_SeedUpperInterface_MiddlePort("SeedUpperInterface_Middle"),
    m_WaistInterfacePort("WaistInterface"),
    m_NeckInterfacePort("NeckInterface"),
    m_MotionPlanningInterfacePort("MotionPlanningInterface")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
SeedUpperBodyTestController::~SeedUpperBodyTestController()
{
}



RTC::ReturnCode_t SeedUpperBodyTestController::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  m_SeedUpperInterface_CommonPort.registerConsumer("SeedUpperInterface_Common", "SEED_UPPER::SeedUpperInterface_Common", m_SeedUpperInterface_Common);
  m_SeedUpperInterface_MiddlePort.registerConsumer("SeedUpperInterface_Middle", "SEED_UPPER::SeedUpperInterface_Middle", m_SeedUpperInterface_Middle);
  m_WaistInterfacePort.registerConsumer("WaistInterface", "WaistNeck::WaistInterface", m_WaistInterface);
  m_NeckInterfacePort.registerConsumer("NeckInterface", "WaistNeck::NeckInterface", m_NeckInterface);
  m_MotionPlanningInterfacePort.registerConsumer("MotionPlanningInterface", "Planning::MotionPlanningInterface", m_MotionPlanningInterface);
  
  // Set CORBA Service Ports
  addPort(m_SeedUpperInterface_CommonPort);
  addPort(m_SeedUpperInterface_MiddlePort);
  addPort(m_WaistInterfacePort);
  addPort(m_NeckInterfacePort);
  addPort(m_MotionPlanningInterfacePort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SeedUpperBodyTestController::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedUpperBodyTestController::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedUpperBodyTestController::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t SeedUpperBodyTestController::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SeedUpperBodyTestController::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SeedUpperBodyTestController::onExecute(RTC::UniqueId ec_id)
{
    int c;
  
  std::cout << "Please select a command" << std::endl;
  std::cout << "1 : Servo ON" << std::endl;
  std::cout << "2 : Servo OFF" << std::endl;
  std::cout << "3 : Control of the Right Arm" << std::endl;
  std::cout << "4 : Control of the Left Arm" << std::endl;
  std::cout << "5 : Control of the Neck" << std::endl;
  std::cout << "6 : Control of the Waist" << std::endl;
  std::cout << "7 : Get Current Angle" << std::endl;
  std::cout << "8 : Get Current End Effector Pos" << std::endl;
  std::cout << "9 : Motion Planning and Control" << std::endl;
  std::cout << "10 : End" << std::endl;

  std::cout << ">>";
  std::cin >> c; 
  std::cout << std::endl;

    //******************   サーボON   ******************************
  if(c == 1)
    {
      m_rid_upper=m_SeedUpperInterface_Common->servoON();
      if(m_rid_upper->id != 0){//Error
	std::cout<<"Servo ON ERROR"<<std::endl;
	std::cout<<m_rid_upper->comment<<std::endl<<std::endl;
      }
    }

  //******************   サーボOFF   ******************************
  else if(c == 2)
    {
      m_rid_upper=m_SeedUpperInterface_Common->servoOFF();
      if(m_rid_upper->id != 0){//Error
	std::cout<<"Servo OFF ERROR"<<std::endl;
	std::cout<<m_rid_upper->comment<<std::endl<<std::endl;
      }
    }

  //******************   右腕の制御   ******************************
  else if(c == 3)//右腕
    {
      int r; 
      std::cout << "1 : Move PTP Cartesian Abs" << std::endl;
      std::cout << "2 : Move PTP Joint Abs" << std::endl;
      std::cout << "3 : Close Gripper" << std::endl;
      std::cout << "4 : Open Gripper" << std::endl;
      std::cout << "5 : Move Gripper" << std::endl;
	    
      std::cout << ">>";
      std::cin >> r; 
      std::cout << std::endl;

      //******************   右腕アーム先端の移動   ********************
      if(r==1)
	{   
	  int w;
	  std::cout << "1 : Redundant Joint Manual Mode" << std::endl;
	  std::cout << "2 : Redundant Joint Automatic Calculation Mode" << std::endl;
	  
	  std::cout << ">>";
	  std::cin >> w; 
	  std::cout << std::endl;
	  if(!(w==1||w==2))
	    {
	      std::cout << "Input Error" << std::endl;
	      return RTC::RTC_OK;
	    }
	  std::cout << "Sample Pos" << std::endl;
	  std::cout << "roll=90 ,pitch=-90 ,yaw=0   ,X=700  ,Y=-200 ,Z=1000" << std::endl;
	  std::cout << "roll=35 ,pitch=0   ,yaw=90  ,X=700  ,Y=-200 ,Z=1000" << std::endl;
	  std::cout << "roll=0  ,pitch=-90 ,yaw=180 ,X=200  ,Y=700  ,Z=1000" << std::endl;
	  std::cout << "roll=35 ,pitch=0   ,yaw=180 ,X=200  ,Y=700  ,Z=1000" << std::endl;
	  std::cout << "roll=0  ,pitch=-90 ,yaw=0   ,X=-200 ,Y=-700 ,Z=1000" << std::endl;
	  std::cout << "roll=35 ,pitch=0   ,yaw=0   ,X=-200 ,Y=-700 ,Z=1000" << std::endl << std::endl;
	  
	  SEED_UPPER::CarPosWithLifterWaistElbow targetRightPos;
	  SEED_UPPER::EEPos targetRightPos_2;
	  double roll;
	  double pitch;
	  double yaw;
	  double calceerot[9];
	  
	  std::cout << "Enter the Rotation(yaw,pitch,roll)[deg]"<<std::endl;
	  std::cout<< "roll : ";
	  std::cin >> roll;
	  std::cout << "pitch : ";
	  std::cin >> pitch;
	  std::cout << "yaw : ";
	  std::cin >> yaw;
	  std::cout << std::endl; 
	  
	  std::cout << "Enter the Position[mm]" << std::endl;
	  std::cout << "X : "; 
	  std::cin >> targetRightPos.carPos[0][3];
	  std::cout << "Y : ";
	  std::cin >> targetRightPos.carPos[1][3];
	  std::cout << "Z : ";
	  std::cin >> targetRightPos.carPos[2][3];
	  std::cout << std::endl; 
	  targetRightPos_2.carPos[0][3] = targetRightPos.carPos[0][3];
	  targetRightPos_2.carPos[1][3] = targetRightPos.carPos[1][3];
	  targetRightPos_2.carPos[2][3] = targetRightPos.carPos[2][3];
	  
	  if(w==1)
	    {
	      std::cout << "Set Redundant Joint" << std::endl;
	      std::cout << "Lifter Bottom (0~85) : ";
	      std::cin >> targetRightPos.LifterPos.bottom;
	      std::cout << "Lifter Top    (0~85) : ";
	      std::cin >> targetRightPos.LifterPos.top;
	      std::cout << "Waist Yaw   (-90~90) : ";
	      std::cin >> targetRightPos.waistPos.yaw;
	      std::cout << "Waist Pitch (-9~+39) : ";
	      std::cin >> targetRightPos.waistPos.pitch;
	      std::cout << "Waist Roll  (-9~+9)  : ";
	      std::cin >> targetRightPos.waistPos.roll;
	    }

	  TransRot(calceerot,roll,pitch,yaw);

	  targetRightPos.carPos[0][0] = calceerot[0];
	  targetRightPos.carPos[0][1] = calceerot[1];
	  targetRightPos.carPos[0][2] = calceerot[2];
	  targetRightPos.carPos[1][0] = calceerot[3];
	  targetRightPos.carPos[1][1] = calceerot[4];
	  targetRightPos.carPos[1][2] = calceerot[5];
	  targetRightPos.carPos[2][0] = calceerot[6];
	  targetRightPos.carPos[2][1] = calceerot[7];
	  targetRightPos.carPos[2][2] = calceerot[8];
	  targetRightPos_2.carPos[0][0] = targetRightPos.carPos[0][0];
	  targetRightPos_2.carPos[0][1] = targetRightPos.carPos[0][1];
	  targetRightPos_2.carPos[0][2] = targetRightPos.carPos[0][2];
	  targetRightPos_2.carPos[1][0] = targetRightPos.carPos[1][0];
	  targetRightPos_2.carPos[1][1] = targetRightPos.carPos[1][1];
	  targetRightPos_2.carPos[1][2] = targetRightPos.carPos[1][2];
	  targetRightPos_2.carPos[2][0] = targetRightPos.carPos[2][0];
	  targetRightPos_2.carPos[2][1] = targetRightPos.carPos[2][1];
	  targetRightPos_2.carPos[2][2] = targetRightPos.carPos[2][2];
	  
	  targetRightPos.elbow = 0;
	  
	  if(w==1)
	    {
	      m_rid_upper = m_SeedUpperInterface_Middle->movePTPLIWARArmCartesianAbsSetRedunJoint(targetRightPos);
	      if(m_rid_upper->id != 0){//Error
		std::cout<<"movePTPLIWARArmCartesianAbsSetRedunJointtargetRightPos ERROR"<<std::endl;
		std::cout<<m_rid_upper->comment<<std::endl<<std::endl;
		return RTC::RTC_OK;
	      }
	    }
	  if(w==2)
	    {
	      m_rid_upper = m_SeedUpperInterface_Middle->movePTPLIWARArmCartesianAbs(targetRightPos_2);
	      if(m_rid_upper->id != 0){//Error
		std::cout<<"movePTPLIWARArmCartesianAbs ERROR"<<std::endl;
		std::cout<<m_rid_upper->comment<<std::endl<<std::endl;
		return RTC::RTC_OK;
	      }
	    }	  	  
	}
      
      //******************   右腕アーム関節の回転   ******************************
      else if(r==2)
	{
	  SEED_UPPER::JointPos targetPos;
	  targetPos.length(12);
	  std::cout << "Lifter Bottom   (0~85) : ";
	  std::cin >> targetPos[0];
	  std::cout << "Lifter Top      (0~85) : ";
	  std::cin >> targetPos[1];
	  std::cout << "Waist Yaw   (-120~120) : ";
	  std::cin >> targetPos[2];
	  std::cout << "Waist Pitch    (-9~39) : ";
	  std::cin >> targetPos[3];
	  std::cout << "Waist Roll      (-8~8) : ";
	  std::cin >> targetPos[4];
	  std::cout << "Shoulder Pitch(-20~89) : ";
	  std::cin >> targetPos[5];
	  std::cout << "Shoulder Roll   (0~90) : ";
	  std::cin >> targetPos[6];
	  std::cout << "Elbow Yaw   (-135~135) : ";
	  std::cin >> targetPos[7];
	  std::cout << "Elbow Pitch    (0~180) : ";
	  std::cin >> targetPos[8];
	  std::cout << "Wrist Yaw   (-135~135) : ";
	  std::cin >> targetPos[9];
	  std::cout << "Wrist Roll    (-80~40) : ";
	  std::cin >> targetPos[10];
	  std::cout << "Hand Yaw    (-180~180) : ";
	  std::cin >> targetPos[11];
      
	  m_rid_upper = m_SeedUpperInterface_Middle->movePTPLIWARArmJointAbs(targetPos);
	  if(m_rid_upper->id != 0){//Error
	    std::cout<<"movePTPLIWARArmJointAbs ERROR"<<std::endl;
	    std::cout<<m_rid_upper->comment<<std::endl<<std::endl;
	    return RTC::RTC_OK;
	  }
	}

      //******************   右腕アームグリッパ閉   ******************************
      else if(r==3)
	{
	  m_rid_upper=m_SeedUpperInterface_Middle->closeRightGripper();
	  if(m_rid_upper->id != 0){//Error
	    std::cout<<"closeGripper ERROR"<<std::endl;
	    std::cout<<m_rid_upper->comment<<std::endl<<std::endl;
	  }
	}

      //******************   右腕アームグリッパ開   ******************************
      else if(r==4)
	{
	  m_rid_upper=m_SeedUpperInterface_Middle->openRightGripper();
	  if(m_rid_upper->id != 0){//Error
	    std::cout<<"closeGripper ERROR"<<std::endl;
	    std::cout<<m_rid_upper->comment<<std::endl<<std::endl;
	  }
	}
      //******************   右腕アーム操作   ******************************
      else if(r==5)
	{
	  SEED_UPPER::ULONG angleRatio;
	  std::cout << "Set Ratio (0~100%)" << std::endl;
	  std::cout << ">>";
	  std::cin >> angleRatio;
	  m_rid_upper=m_SeedUpperInterface_Middle->moveRightGripper(angleRatio);
	  if(m_rid_upper->id != 0){//Error
	    std::cout<<"moveGripper ERROR"<<std::endl;
	    std::cout<<m_rid_upper->comment<<std::endl<<std::endl;
	  }
	}
      else 
	std::cout << "Input Error" << std::endl<<std::endl;
      
    }//else if(c==3)
  
  //******************   左腕の制御   ******************************
  else if(c == 4)
    {
      int l; 
      std::cout << "1 : Move PTP Cartesian Abs" << std::endl;
      std::cout << "2 : Move PTP Joint Abs" << std::endl;
      std::cout << "3 : Close Gripper" << std::endl;
      std::cout << "4 : Open Gripper" << std::endl;
      std::cout << "5 : Move Gripper" << std::endl;

      std::cout << ">>";
      std::cin >> l; 
      std::cout << std::endl; 

      //******************   左腕アーム先端の移動   ******************************
      if(l==1)
	{   
	  int w;
	  std::cout << "1 : Redundant Joint Manual Mode" << std::endl;
	  std::cout << "2 : Redundant Joint Automatic Calculation Mode" << std::endl;
	  
	  std::cout << ">>";
	  std::cin >> w; 
	  std::cout << std::endl;
	  if(!(w==1||w==2))
	    {
	      std::cout << "Input Error" << std::endl;
	      return RTC::RTC_OK;
	    }

	  std::cout << "Sample Pos" << std::endl;
	  std::cout << "roll=-90 ,pitch=-90 ,yaw=0   ,X=700  ,Y=200  ,Z=1000" << std::endl;
	  std::cout << "roll=-35 ,pitch=0   ,yaw=-90 ,X=700  ,Y=200  ,Z=1000" << std::endl;
	  std::cout << "roll=0   ,pitch=-90 ,yaw=0   ,X=-200 ,Y=700  ,Z=1000" << std::endl;
	  std::cout << "roll=-35 ,pitch=0   ,yaw=0   ,X=-200 ,Y=700  ,Z=1000" << std::endl;
	  std::cout << "roll=0   ,pitch=-90 ,yaw=180 ,X=200  ,Y=-700 ,Z=1000" << std::endl;
	  std::cout << "roll=-35 ,pitch=0   ,yaw=180 ,X=200  ,Y=-700 ,Z=1000" << std::endl << std::endl;
	  
	  SEED_UPPER::CarPosWithLifterWaistElbow targetLeftPos;
	  SEED_UPPER::EEPos targetLeftPos_2;
	  double roll;
	  double pitch;
	  double yaw;
	  double calceerot[9];
	  
	  std::cout << "Enter the Rotation(yaw,pitch,roll)[deg]"<<std::endl;
	  std::cout<< "roll : ";
	  std::cin >> roll;
	  std::cout << "pitch : ";
	  std::cin >> pitch;
	  std::cout << "yaw : ";
	  std::cin >> yaw;
	  std::cout << std::endl; 
	  
	  std::cout << "Enter the Position[mm]" << std::endl;
	  std::cout << "X : "; 
	  std::cin >> targetLeftPos.carPos[0][3];
	  std::cout << "Y : ";
	  std::cin >> targetLeftPos.carPos[1][3];
	  std::cout << "Z : ";
	  std::cin >> targetLeftPos.carPos[2][3];
	  std::cout << std::endl; 
	  targetLeftPos_2.carPos[0][3] = targetLeftPos.carPos[0][3];
	  targetLeftPos_2.carPos[1][3] = targetLeftPos.carPos[1][3];
	  targetLeftPos_2.carPos[2][3] = targetLeftPos.carPos[2][3];
	  
	  if(w==1)
	    {
	      std::cout << "Set Redundant Joint" << std::endl;
	      std::cout << "Lifter Bottom (0~85) : ";
	      std::cin >> targetLeftPos.LifterPos.bottom;
	      std::cout << "Lifter Top    (0~85) : ";
	      std::cin >> targetLeftPos.LifterPos.top;
	      std::cout << "Waist Yaw   (-90~90) : ";
	      std::cin >> targetLeftPos.waistPos.yaw;
	      std::cout << "Waist Pitch (-9~+39) : ";
	      std::cin >> targetLeftPos.waistPos.pitch;
	      std::cout << "Waist Roll  (-9~+9)  : ";
	      std::cin >> targetLeftPos.waistPos.roll;
	    }

	  TransRot(calceerot,roll,pitch,yaw);

	  targetLeftPos.carPos[0][0] = calceerot[0];
	  targetLeftPos.carPos[0][1] = calceerot[1];
	  targetLeftPos.carPos[0][2] = calceerot[2];
	  targetLeftPos.carPos[1][0] = calceerot[3];
	  targetLeftPos.carPos[1][1] = calceerot[4];
	  targetLeftPos.carPos[1][2] = calceerot[5];
	  targetLeftPos.carPos[2][0] = calceerot[6];
	  targetLeftPos.carPos[2][1] = calceerot[7];
	  targetLeftPos.carPos[2][2] = calceerot[8];
	  targetLeftPos_2.carPos[0][0] = targetLeftPos.carPos[0][0];
	  targetLeftPos_2.carPos[0][1] = targetLeftPos.carPos[0][1];
	  targetLeftPos_2.carPos[0][2] = targetLeftPos.carPos[0][2];
	  targetLeftPos_2.carPos[1][0] = targetLeftPos.carPos[1][0];
	  targetLeftPos_2.carPos[1][1] = targetLeftPos.carPos[1][1];
	  targetLeftPos_2.carPos[1][2] = targetLeftPos.carPos[1][2];
	  targetLeftPos_2.carPos[2][0] = targetLeftPos.carPos[2][0];
	  targetLeftPos_2.carPos[2][1] = targetLeftPos.carPos[2][1];
	  targetLeftPos_2.carPos[2][2] = targetLeftPos.carPos[2][2];
	  
	  targetLeftPos.elbow = 0;
	  
	  if(w==1)
	    {
	      m_rid_upper = m_SeedUpperInterface_Middle->movePTPLIWALArmCartesianAbsSetRedunJoint(targetLeftPos);
	      if(m_rid_upper->id != 0){//Error
		std::cout<<"movePTPLIWALArmCartesianAbsSetRedunJoint ERROR"<<std::endl;
		std::cout<<m_rid_upper->comment<<std::endl<<std::endl;
		return RTC::RTC_OK;
	      }
	    }
	  if(w==2)
	    {
	      m_rid_upper = m_SeedUpperInterface_Middle->movePTPLIWALArmCartesianAbs(targetLeftPos_2);
	      if(m_rid_upper->id != 0){//Error
		std::cout<<"movePTPLIWALArmCartesianAbs ERROR"<<std::endl;
		std::cout<<m_rid_upper->comment<<std::endl<<std::endl;
		return RTC::RTC_OK;
	      }
	    }	 
	}
      
      //******************   左腕アーム関節の移動   ******************************
      else if(l==2)
	{
	  SEED_UPPER::JointPos targetPos;
	  targetPos.length(12);
	  std::cout << "Lifter Bottom   (0~85) : ";
	  std::cin >> targetPos[0];
	  std::cout << "Lifter Top      (0~85) : ";
	  std::cin >> targetPos[1];
	  std::cout << "Waist Yaw   (-120~120) : ";
	  std::cin >> targetPos[2];
	  std::cout << "Waist Pitch    (-9~39) : ";
	  std::cin >> targetPos[3];
	  std::cout << "Waist Roll      (-8~8) : ";
	  std::cin >> targetPos[4];
	  std::cout << "Shoulder Pitch(-20~89) : ";
	  std::cin >> targetPos[5];
	  std::cout << "Shoulder Roll   (0~90) : ";
	  std::cin >> targetPos[6];
	  std::cout << "Elbow Yaw   (-135~135) : ";
	  std::cin >> targetPos[7];
	  std::cout << "Elbow Pitch    (0~180) : ";
	  std::cin >> targetPos[8];
	  std::cout << "Wrist Yaw   (-135~135) : ";
	  std::cin >> targetPos[9];
	  std::cout << "Wrist Roll    (-80~40) : ";
	  std::cin >> targetPos[10];
	  std::cout << "Hand Yaw    (-180~180) : ";
	  std::cin >> targetPos[11];
      
	  m_rid_upper = m_SeedUpperInterface_Middle->movePTPLIWALArmJointAbs(targetPos);
	  if(m_rid_upper->id != 0){//Error
	    std::cout<<"movePTPLIWARArmJointAbs ERROR"<<std::endl;
	    std::cout<<m_rid_upper->comment<<std::endl<<std::endl;
	    return RTC::RTC_OK;
	  }
	}
      //******************   左腕グリッパ閉   ******************************
      else if(l==3)
	{
	  m_rid_upper=m_SeedUpperInterface_Middle->closeLeftGripper();
	  if(m_rid_upper->id != 0){//Error
	    std::cout<<"closeGripper ERROR"<<std::endl;
	    std::cout<<m_rid_upper->comment<<std::endl<<std::endl;
	  }
	}
      //******************   左腕グリッパ開   ******************************
      else if(l==4)
	{
	  m_rid_upper=m_SeedUpperInterface_Middle->openLeftGripper();
	  if(m_rid_upper->id != 0){//Error
	    std::cout<<"closeGripper ERROR"<<std::endl;
	    std::cout<<m_rid_upper->comment<<std::endl<<std::endl;
	  }
	}
     //******************   左腕グリッパ操作   ******************************
      else if(l==5)
	{
	  SEED_UPPER::ULONG angleRatio;
	  std::cout << "Set Ratio (0~100%)" << std::endl;
	  std::cout << ">>";
	  std::cin >> angleRatio;
	  m_rid_upper=m_SeedUpperInterface_Middle->moveLeftGripper(angleRatio);
	  if(m_rid_upper->id != 0){//Error
	    std::cout<<"moveGripper ERROR"<<std::endl;
	    std::cout<<m_rid_upper->comment<<std::endl<<std::endl;
	  }
	}
      else 
	std::cout << "Input Error" << std::endl<<std::endl;
    }

  //******************   首の制御   ******************************
  else if(c == 5)//首の制御
    {
	  WaistNeck::NeckPos neckPoint;
	  neckPoint.length(3);
	  std::cout << "Set Neck Joint Pos" << std::endl;
	  std::cout << "Neck Yaw   (-90~+90) : ";
	  std::cin >> neckPoint[0];
	  std::cout << "Neck Pitch (-20~+60) : ";
	  std::cin >> neckPoint[1];
	  std::cout << "Neck Roll  (-20~+20) : ";
	  std::cin >> neckPoint[2];
	  
	  m_rid_neck=m_NeckInterface->movePTPNeckAbs(neckPoint);
	  if(m_rid_neck->id != 0){//Error
	    std::cout<<"movePTPNeckAbs ERROR"<<std::endl;
	    std::cout<<m_rid_neck->comment<<std::endl<<std::endl;
	  }
    }  
  
  //******************   腰の制御   ******************************
  else if(c == 6)
    {
	  WaistNeck::WaistPos waistPoint;
	  waistPoint.length(3);
	  std::cout << "Set Waist Joint Pos" << std::endl;
	  std::cout << "Waist Yaw   (-90~+90) : ";
	  std::cin >> waistPoint[0];
	  std::cout << "Waist Pitch (-9~+39)  : ";
	  std::cin >> waistPoint[1];
	  std::cout << "Waist Roll  (-9~+9)   : ";
	  std::cin >> waistPoint[2];
	  
	  m_rid_waist=m_WaistInterface->movePTPWaistAbs(waistPoint);
	  if(m_rid_waist->id != 0){//Error
	    std::cout<<"movePTPWaistAbs ERROR"<<std::endl;
	    std::cout<<m_rid_waist->comment<<std::endl<<std::endl;
	  }
    }

  //******************   現在角度の取得   ******************************
  else if(c == 7)
    {
      SEED_UPPER::Lifter lifterPos;
      SEED_UPPER::RPY waistPos;
      SEED_UPPER::RPY neckPos;
      SEED_UPPER::JointPos_var rightPosvar;
      SEED_UPPER::JointPos rightPos;
      SEED_UPPER::JointPos_var leftPosvar;
      SEED_UPPER::JointPos leftPos;
      rightPos.length(7);
      leftPos.length(7);
      m_rid_upper=m_SeedUpperInterface_Common->getFeedbackPosAllJoint(lifterPos,waistPos,neckPos,rightPosvar,leftPosvar);
      rightPos = rightPosvar;
      leftPos = leftPosvar;
      
      std::cout << "lifterPos.bottom = " << lifterPos.bottom << std::endl;
      std::cout << "lifterPos.top = " << lifterPos.top << std::endl;
      std::cout << "waistPos.yaw = " << waistPos.yaw << std::endl;
      std::cout << "waistPos.pitch = " << waistPos.pitch << std::endl;
      std::cout << "waistPos.roll = " << waistPos.roll << std::endl;
      std::cout << "neckPos.yaw = " << neckPos.yaw << std::endl;
      std::cout << "neckPos.pitch = " << neckPos.pitch << std::endl;
      std::cout << "neckPos.roll = " << neckPos.roll << std::endl;
      for(int i=0;i<7;i++)
	{
	  std::cout << "rightPos["<<i<<"] = " << rightPos[i] << std::endl;
	}
      for(int i=0;i<7;i++)
	{
	  std::cout << "leftPos["<<i<<"] = " << leftPos[i] << std::endl;
	}
    }
  
  //******************   先端座標の取得   ******************************
  else if(c == 8)
    {
      SEED_UPPER::CarPosWithLifterWaistElbow rightpos;
      m_rid_upper=m_SeedUpperInterface_Middle->getFeedbackPosLIWARCartesian(rightpos);
      SEED_UPPER::CarPosWithLifterWaistElbow leftpos;
      m_rid_upper=m_SeedUpperInterface_Middle->getFeedbackPosLIWALCartesian(leftpos);

      std::cout << "rightpos.carPos[0][0] = "<<rightpos.carPos[0][0]<<std::endl;
      std::cout << "rightpos.carPos[0][1] = "<<rightpos.carPos[0][1]<<std::endl;
      std::cout << "rightpos.carPos[0][2] = "<<rightpos.carPos[0][2]<<std::endl;
      std::cout << "rightpos.carPos[1][0] = "<<rightpos.carPos[1][0]<<std::endl;
      std::cout << "rightpos.carPos[1][1] = "<<rightpos.carPos[1][1]<<std::endl;
      std::cout << "rightpos.carPos[1][2] = "<<rightpos.carPos[1][2]<<std::endl;
      std::cout << "rightpos.carPos[2][0] = "<<rightpos.carPos[2][0]<<std::endl;
      std::cout << "rightpos.carPos[2][1] = "<<rightpos.carPos[2][1]<<std::endl;
      std::cout << "rightpos.carPos[2][2] = "<<rightpos.carPos[2][2]<<std::endl;
      std::cout << "rightpos.carPos[0][3] = "<<rightpos.carPos[0][3]<<std::endl;
      std::cout << "rightpos.carPos[1][3] = "<<rightpos.carPos[1][3]<<std::endl;
      std::cout << "rightpos.carPos[2][3] = "<<rightpos.carPos[2][3]<<std::endl;
      std::cout << "leftpos.carPos[0][0] = "<<leftpos.carPos[0][0]<<std::endl;
      std::cout << "leftpos.carPos[0][1] = "<<leftpos.carPos[0][1]<<std::endl;
      std::cout << "leftpos.carPos[0][2] = "<<leftpos.carPos[0][2]<<std::endl;
      std::cout << "leftpos.carPos[1][0] = "<<leftpos.carPos[1][0]<<std::endl;
      std::cout << "leftpos.carPos[1][1] = "<<leftpos.carPos[1][1]<<std::endl;
      std::cout << "leftpos.carPos[1][2] = "<<leftpos.carPos[1][2]<<std::endl;
      std::cout << "leftpos.carPos[2][0] = "<<leftpos.carPos[2][0]<<std::endl;
      std::cout << "leftpos.carPos[2][1] = "<<leftpos.carPos[2][1]<<std::endl;
      std::cout << "leftpos.carPos[2][2] = "<<leftpos.carPos[2][2]<<std::endl;
      std::cout << "leftpos.carPos[0][3] = "<<leftpos.carPos[0][3]<<std::endl;
      std::cout << "leftpos.carPos[1][3] = "<<leftpos.carPos[1][3]<<std::endl;
      std::cout << "leftpos.carPos[2][3] = "<<leftpos.carPos[2][3]<<std::endl;
    }

    else if(c == 9)
      {
	Planning::ManipPos planGoalPos;

	double eerot[9];
	double roll;
	double pitch;
	double yaw;
	double x;
	double y;
	double z;

	std::cout << "set rotation" << std::endl;
	std::cout << "roll = " ;
	std::cin >> roll;
	std::cout << "pitch = " ;
	std::cin >> pitch;
	std::cout << "yaw = " ;
	std::cin >> yaw;
	std::cout << "set position" << std::endl;
	std::cout << "x = " ;
	std::cin >> x;
	std::cout << "y = " ;
	std::cin >> y;
	std::cout << "z = " ;
	std::cin >> z;
  
	TransRot(eerot,roll,pitch,yaw);
 
	planGoalPos.rotation[0] = eerot[0];
	planGoalPos.rotation[1] = eerot[1];
	planGoalPos.rotation[2] = eerot[2];
	planGoalPos.rotation[3] = eerot[3];
	planGoalPos.rotation[4] = eerot[4];
	planGoalPos.rotation[5] = eerot[5];
	planGoalPos.rotation[6] = eerot[6];
	planGoalPos.rotation[7] = eerot[7];
	planGoalPos.rotation[8] = eerot[8];
	planGoalPos.position[0] = x;
	planGoalPos.position[1] = y;
	planGoalPos.position[2] = z;
	std::cout << "send target pos" << std::endl;
	m_MotionPlanningInterface->MotionGenerate(planGoalPos);
      }

    else if(c == 10)
      {
	std::cout << "END" << std::endl;
	std::cout << "Component Deactivate" << std::endl<<std::endl;
	deactivate(ec_id);
      }
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SeedUpperBodyTestController::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedUpperBodyTestController::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedUpperBodyTestController::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedUpperBodyTestController::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeedUpperBodyTestController::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/************************************************

	void TransRot(double eerot[],double roll,double pitch,double yaw)
	
	概要：ロールピッチヨー[deg]から先端姿勢の回転行列を求める

	引数：
　　　　　　　double eerot[]・・・計算した行列を格納する配列
                                 |0 1 2|
                                 |3 4 5|
                                 |6 7 8|
             double roll・・・ロール回転角度
             double pitch・・・ピッチ回転角度
             double yaw・・・ヨー回転角度

	戻り値：なし

*************************************************/
void SeedUpperBodyTestController::TransRot(double eerot[],double roll,double pitch,double yaw)
{
  //ロールピッチヨー　ロボット工学（遠山茂樹著）p25
  double Rrotx;
  double Rroty;
  double Rrotz;
  Rrotx = roll * M_PI / 180;
  Rroty = pitch * M_PI / 180;
  Rrotz = yaw * M_PI / 180;

  eerot[0] = cos(Rroty)*cos(Rrotz);
  eerot[1] = cos(Rrotz)*sin(Rroty)*sin(Rrotx)-sin(Rrotz)*cos(Rrotx);
  eerot[2] = cos(Rrotz)*sin(Rroty)*cos(Rrotx)+sin(Rrotz)*sin(Rrotx);
  eerot[3] = sin(Rrotz)*cos(Rroty);
  eerot[4] = sin(Rrotz)*sin(Rroty)*sin(Rrotx)+cos(Rrotz)*cos(Rrotx);
  eerot[5] = sin(Rrotz)*sin(Rroty)*cos(Rrotx)-cos(Rrotz)*sin(Rrotx);
  eerot[6] = -sin(Rroty);
  eerot[7] = cos(Rroty)*sin(Rrotx);
  eerot[8] = cos(Rroty)*cos(Rrotx);

}


/************************************************

        Frame Solve_Rot(double eerot[]);
	
	概要：先端姿勢の回転行列から、ロールピッチヨー[deg]を求める

	引数：
　　　　　　　double eerot[]・・・姿勢行列を格納する配列
                                 |0 1 2|
                                 |3 4 5|
                                 |6 7 8|

	戻り値：姿勢（ロールピッチヨー）

*************************************************/
Frame SeedUpperBodyTestController::Solve_Rot(double eerot[])
{
  Frame rotation;
  double phi;//φ
  double theta;//θ
  double psi;//ψ

  for(int i=0;i<9;i++)
    {
      if(eerot[i]>1)
	eerot[i] = 1;
      if(eerot[i]<-1)
	eerot[i] = -1;
    }

  psi = atan2(eerot[3], eerot[0]);
  theta =  atan2(-eerot[6], sqrt(eerot[7]*eerot[7]+eerot[8]*eerot[8]));
  phi = atan2(eerot[7], eerot[8]);  

  rotation.roll = phi*180/M_PI;
  rotation.pitch = theta*180/M_PI;
  rotation.yaw = psi*180/M_PI;

  return rotation;
}


extern "C"
{
 
  void SeedUpperBodyTestControllerInit(RTC::Manager* manager)
  {
    coil::Properties profile(seedupperbodytestcontroller_spec);
    manager->registerFactory(profile,
                             RTC::Create<SeedUpperBodyTestController>,
                             RTC::Delete<SeedUpperBodyTestController>);
  }
  
};


