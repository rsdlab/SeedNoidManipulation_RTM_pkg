// -*- C++ -*-
/*!
 * @file  ObstacleManager.cpp
 * @brief ObstacleManager
 * @date $Date$
 *
 * $Id$
 */

#include "ObstacleManager.h"

// Module specification
// <rtc-template block="module_spec">
static const char* obstaclemanager_spec[] =
  {
    "implementation_id", "ObstacleManager",
    "type_name",         "ObstacleManager",
    "description",       "ObstacleManager",
    "version",           "1.0.0",
    "vendor",            "VenderName",
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
ObstacleManager::ObstacleManager(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_Marker_DataIn("Marker_Data", m_Marker_Data),
    m_Obstacle_DataPort("Obstacle_Data")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
ObstacleManager::~ObstacleManager()
{
}



RTC::ReturnCode_t ObstacleManager::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("Marker_Data", m_Marker_DataIn);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  m_Obstacle_DataPort.registerProvider("ObstacleInterface", "Obstacle::ObstacleInterface", m_ObstacleInterface);
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  addPort(m_Obstacle_DataPort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ObstacleManager::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ObstacleManager::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ObstacleManager::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t ObstacleManager::onActivated(RTC::UniqueId ec_id)
{
  MarkerPos = Eigen::MatrixXd(4,4);
  relAABB_A = Eigen::MatrixXd(4,4);
  relAABB_B = Eigen::MatrixXd(4,4);
  relAABB_C = Eigen::MatrixXd(4,4);
  relAABB_D = Eigen::MatrixXd(4,4);
  relAABB_E = Eigen::MatrixXd(4,4);
  calcAABB_A = Eigen::MatrixXd(4,4);
  calcAABB_B = Eigen::MatrixXd(4,4);
  calcAABB_C = Eigen::MatrixXd(4,4);
  calcAABB_D = Eigen::MatrixXd(4,4);
  calcAABB_E = Eigen::MatrixXd(4,4);
 
  m_ObstacleInterface.AABBList.length(0);
  setRelPos();
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ObstacleManager::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ObstacleManager::onExecute(RTC::UniqueId ec_id)
{
    if(m_Marker_DataIn.isNew())
    {
      m_Marker_DataIn.read();
      int length=m_Marker_Data.ids.length();

      for(int i=0;i<length;i++)
	{
	  if(m_Marker_Data.ids[i]==100)
	    {
	      AABBNum = 5;
	      m_ObstacleInterface.AABBList.length(AABBNum);
	      //右シェルフ
	      m_ObstacleInterface.AABBList[0].rx = 100;
	      m_ObstacleInterface.AABBList[0].ry = 205;
	      m_ObstacleInterface.AABBList[0].rz = 770;
	      //左シェルフ
	      m_ObstacleInterface.AABBList[1].rx = 100;
	      m_ObstacleInterface.AABBList[1].ry = 205;
	      m_ObstacleInterface.AABBList[1].rz = 770;
	      //棚板上
	      m_ObstacleInterface.AABBList[2].rx = 470;
	      m_ObstacleInterface.AABBList[2].ry = 235;
	      m_ObstacleInterface.AABBList[2].rz = 50;
	      //棚板中
	      m_ObstacleInterface.AABBList[3].rx = 470;
	      m_ObstacleInterface.AABBList[3].ry = 235;
	      m_ObstacleInterface.AABBList[3].rz = 50;
	      //棚板下
	      m_ObstacleInterface.AABBList[4].rx = 470;
	      m_ObstacleInterface.AABBList[4].ry = 235;
	      m_ObstacleInterface.AABBList[4].rz = 50;
  
	      MarkerPos(0,0) = m_Marker_Data.rotations[i].R11;
	      MarkerPos(0,1) = m_Marker_Data.rotations[i].R12;
	      MarkerPos(0,2) = m_Marker_Data.rotations[i].R13;
	      MarkerPos(1,0) = m_Marker_Data.rotations[i].R21;
	      MarkerPos(1,1) = m_Marker_Data.rotations[i].R22;
	      MarkerPos(1,2) = m_Marker_Data.rotations[i].R23;
	      MarkerPos(2,0) = m_Marker_Data.rotations[i].R31;
	      MarkerPos(2,1) = m_Marker_Data.rotations[i].R32;
	      MarkerPos(2,2) = m_Marker_Data.rotations[i].R33;
	      MarkerPos(0,3) = m_Marker_Data.translates[i].x*1000;
	      MarkerPos(1,3) = m_Marker_Data.translates[i].y*1000;
	      MarkerPos(2,3) = m_Marker_Data.translates[i].z*1000;
	      MarkerPos(3,0) = 0;
	      MarkerPos(3,1) = 0;
	      MarkerPos(3,2) = 0;
	      MarkerPos(3,3) = 1;

	      calcAABB_A = MarkerPos*relAABB_A;
	      calcAABB_B = MarkerPos*relAABB_B;
	      calcAABB_C = MarkerPos*relAABB_C;
	      calcAABB_D = MarkerPos*relAABB_D;
	      calcAABB_E = MarkerPos*relAABB_E;

	      m_ObstacleInterface.AABBList[0].center.x = calcAABB_A(0,3);
	      m_ObstacleInterface.AABBList[0].center.y = calcAABB_A(1,3);
	      m_ObstacleInterface.AABBList[0].center.z = calcAABB_A(2,3);
	      m_ObstacleInterface.AABBList[1].center.x = calcAABB_B(0,3);
	      m_ObstacleInterface.AABBList[1].center.y = calcAABB_B(1,3);
	      m_ObstacleInterface.AABBList[1].center.z = calcAABB_B(2,3);
	      m_ObstacleInterface.AABBList[2].center.x = calcAABB_C(0,3);
	      m_ObstacleInterface.AABBList[2].center.y = calcAABB_C(1,3);
	      m_ObstacleInterface.AABBList[2].center.z = calcAABB_C(2,3);
	      m_ObstacleInterface.AABBList[3].center.x = calcAABB_D(0,3);
	      m_ObstacleInterface.AABBList[3].center.y = calcAABB_D(1,3);
	      m_ObstacleInterface.AABBList[3].center.z = calcAABB_D(2,3);
	      m_ObstacleInterface.AABBList[4].center.x = calcAABB_E(0,3);
	      m_ObstacleInterface.AABBList[4].center.y = calcAABB_E(1,3);
	      m_ObstacleInterface.AABBList[4].center.z = calcAABB_E(2,3);

	    }
	      
	}
    }
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ObstacleManager::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ObstacleManager::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ObstacleManager::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ObstacleManager::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ObstacleManager::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

void ObstacleManager::setRelPos()
{
  relAABB_A(0,0) = 1;
  relAABB_A(0,1) = 0;
  relAABB_A(0,2) = 0;
  relAABB_A(1,0) = 0;
  relAABB_A(1,1) = 1;
  relAABB_A(1,2) = 0;
  relAABB_A(2,0) = 0;
  relAABB_A(2,1) = 0;
  relAABB_A(2,2) = 1;
  relAABB_A(0,3) = 460;
  relAABB_A(1,3) = 650;
  relAABB_A(2,3) = 235;
  relAABB_A(3,0) = 0;
  relAABB_A(3,1) = 0;
  relAABB_A(3,2) = 0;
  relAABB_A(3,3) = 1;
  
  relAABB_B(0,0) = 1;
  relAABB_B(0,1) = 0;
  relAABB_B(0,2) = 0;
  relAABB_B(1,0) = 0;
  relAABB_B(1,1) = 1;
  relAABB_B(1,2) = 0;
  relAABB_B(2,0) = 0;
  relAABB_B(2,1) = 0;
  relAABB_B(2,2) = 1;
  relAABB_B(0,3) = -460;
  relAABB_B(1,3) = 650;
  relAABB_B(2,3) = 235;
  relAABB_B(3,0) = 0;
  relAABB_B(3,1) = 0;
  relAABB_B(3,2) = 0;
  relAABB_B(3,3) = 1;

  relAABB_C(0,0) = 1;
  relAABB_C(0,1) = 0;
  relAABB_C(0,2) = 0;
  relAABB_C(1,0) = 0;
  relAABB_C(1,1) = 1;
  relAABB_C(1,2) = 0;
  relAABB_C(2,0) = 0;
  relAABB_C(2,1) = 0;
  relAABB_C(2,2) = 1;
  relAABB_C(0,3) = 0;
  relAABB_C(1,3) = 270;
  relAABB_C(2,3) = 235;
  relAABB_C(3,0) = 0;
  relAABB_C(3,1) = 0;
  relAABB_C(3,2) = 0;
  relAABB_C(3,3) = 1;

  relAABB_D(0,0) = 1;
  relAABB_D(0,1) = 0;
  relAABB_D(0,2) = 0;
  relAABB_D(1,0) = 0;
  relAABB_D(1,1) = 1;
  relAABB_D(1,2) = 0;
  relAABB_D(2,0) = 0;
  relAABB_D(2,1) = 0;
  relAABB_D(2,2) = 1;
  relAABB_D(0,3) = 0;
  relAABB_D(1,3) = 620;
  relAABB_D(2,3) = 235;
  relAABB_D(3,0) = 0;
  relAABB_D(3,1) = 0;
  relAABB_D(3,2) = 0;
  relAABB_D(3,3) = 1;

  relAABB_E(0,0) = 1;
  relAABB_E(0,1) = 0;
  relAABB_E(0,2) = 0;
  relAABB_E(1,0) = 0;
  relAABB_E(1,1) = 1;
  relAABB_E(1,2) = 0;
  relAABB_E(2,0) = 0;
  relAABB_E(2,1) = 0;
  relAABB_E(2,2) = 1;
  relAABB_E(0,3) = 0;
  relAABB_E(1,3) = 1020;
  relAABB_E(2,3) = 235;
  relAABB_E(3,0) = 0;
  relAABB_E(3,1) = 0;
  relAABB_E(3,2) = 0;
  relAABB_E(3,3) = 1;
  /*
  //カメラ座標系
  relAABB[0].center.x = 460;
  relAABB[0].center.y = 650;
  relAABB[0].center.z = -235;

  relAABB[1].center.x = -460;
  relAABB[1].center.y = 650;
  relAABB[1].center.z = -235;

  relAABB[2].center.x = 0;
  relAABB[2].center.y = 330;
  relAABB[2].center.z = -235;

  relAABB[3].center.x = 0;
  relAABB[3].center.y = 130;
  relAABB[3].center.z = -235;

  relAABB[4].center.x = 0;
  relAABB[4].center.y = 400;
  relAABB[4].center.z = -435;
  
  relAABB[5].center.x = 0;
  relAABB[5].center.y = 0;
  relAABB[5].center.z = 0;
  */
}



extern "C"
{
 
  void ObstacleManagerInit(RTC::Manager* manager)
  {
    coil::Properties profile(obstaclemanager_spec);
    manager->registerFactory(profile,
                             RTC::Create<ObstacleManager>,
                             RTC::Delete<ObstacleManager>);
  }
  
};


