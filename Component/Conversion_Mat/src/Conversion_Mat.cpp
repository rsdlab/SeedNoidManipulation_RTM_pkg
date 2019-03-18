// -*- C++ -*-
/*!
 * @file  Conversion_Mat.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "Conversion_Mat.h"

// Module specification
// <rtc-template block="module_spec">
static const char* conversion_mat_spec[] =
  {
    "implementation_id", "Conversion_Mat",
    "type_name",         "Conversion_Mat",
    "description",       "ModuleDescription",
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
Conversion_Mat::Conversion_Mat(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_Conversion_InterfacePort("Conversion_Interface"),
    m_Transformation_InterfacePort("Transformation_Interface")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Conversion_Mat::~Conversion_Mat()
{
}



RTC::ReturnCode_t Conversion_Mat::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  m_Conversion_InterfacePort.registerProvider("conversionInterface", "ConversionMatrix::conversionInterface", m_conversionInterface);
  
  // Set service consumers to Ports
  m_Transformation_InterfacePort.registerConsumer("transformationInterface", "TransformationMatrix::transformationInterface", m_transformationInterface);
  
  // Set CORBA Service Ports
  addPort(m_Conversion_InterfacePort);
  addPort(m_Transformation_InterfacePort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Conversion_Mat::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Conversion_Mat::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Conversion_Mat::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t Conversion_Mat::onActivated(RTC::UniqueId ec_id)
{
  m_conversionInterface.setCompPtr(this);
  std::string FileName="test.yml";
  if(fs.open(FileName,cv::FileStorage::READ))
    {
      std::cout<<"Read File"<<std::endl;
      fs["handeye_matrix"] >>m_conversionInterface.CalibrationMat;
    }
  else
    {
      std::cout<<"Can't Open"<<std::endl;
      uint8_t data[]={1,0,0,0,
	      0,1,0,0,
	      0,0,1,0,
	      0,0,0,1};
      m_conversionInterface.CalibrationMat=cv::Mat(4, 4, CV_8UC1, data);
    }
  std::cout<<m_conversionInterface.CalibrationMat<<std::endl;
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Conversion_Mat::onDeactivated(RTC::UniqueId ec_id)
{
  
  std::cout<<"m_conversionInterface.CalibrationMat"<<std::endl;
  std::cout<<m_conversionInterface.CalibrationMat<<std::endl;
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Conversion_Mat::onExecute(RTC::UniqueId ec_id)
{

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Conversion_Mat::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Conversion_Mat::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Conversion_Mat::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Conversion_Mat::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Conversion_Mat::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

void Conversion_Mat::getMatrix(TransformationMatrix::transformationMat& Matrix)
{
  std::cout<<"Conversion_Mat::getMatrix"<<std::endl;
  std::cout<<Matrix.rotation.R11<<" "<<Matrix.rotation.R12<<" "<<Matrix.rotation.R13<<std::endl;
  std::cout<<m_transformationInterface->getMatrix(Matrix)<<std::endl;
  std::cout<<"Conversion_Mat::getMatrix End"<<std::endl;

}


extern "C"
{
 
  void Conversion_MatInit(RTC::Manager* manager)
  {
    coil::Properties profile(conversion_mat_spec);
    manager->registerFactory(profile,
                             RTC::Create<Conversion_Mat>,
                             RTC::Delete<Conversion_Mat>);
  }
  
};


