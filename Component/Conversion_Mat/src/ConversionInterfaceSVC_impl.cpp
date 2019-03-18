// -*-C++-*-
/*!
 * @file  ConversionInterfaceSVC_impl.cpp
 * @brief Service implementation code of ConversionInterface.idl
 *
 */

#include "ConversionInterfaceSVC_impl.h"

/*
 * Example implementational code for IDL interface ConversionMatrix::conversionInterface
 */
ConversionMatrix_conversionInterfaceSVC_impl::ConversionMatrix_conversionInterfaceSVC_impl()
{
  // Please add extra constructor code here.
}


ConversionMatrix_conversionInterfaceSVC_impl::~ConversionMatrix_conversionInterfaceSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
::CORBA::Long ConversionMatrix_conversionInterfaceSVC_impl::getConvertionMat(const ConversionMatrix::transformationMat& InMat, ConversionMatrix::transformationMat& OutMat)
{
  std::cout<<"getConvertionMat is called"<<std::endl;
  TransformationMatrix::transformationMat TTMat;

  std::cout<<"Call m_rtcPtr->getMatrix"<<std::endl;
  m_rtcPtr->getMatrix(TTMat);

  ConversionMatrix::transformationMat CTMat;

  CTMat.rotation.R11 = TTMat.rotation.R11;
  CTMat.rotation.R12 = TTMat.rotation.R12;
  CTMat.rotation.R13 = TTMat.rotation.R13;
  CTMat.rotation.R21 = TTMat.rotation.R21;
  CTMat.rotation.R22 = TTMat.rotation.R22;
  CTMat.rotation.R23 = TTMat.rotation.R23;
  CTMat.rotation.R31 = TTMat.rotation.R31;
  CTMat.rotation.R32 = TTMat.rotation.R32;
  CTMat.rotation.R33 = TTMat.rotation.R33;
  CTMat.translates=TTMat.translates;

  std::cout<<"TTMat2CTMat"<<std::endl;
  
  cv::Mat CV_InMat=cv::Mat::zeros(cv::Size(4,4),CV_32F);
  cv::Mat CV_CTMat=cv::Mat::zeros(cv::Size(4,4),CV_32F);
  cv::Mat CV_OutMat=cv::Mat::zeros(cv::Size(4,4),CV_32F);

  std::cout<<"InMat copy"<<std::endl;
  ConversionMatrix::transformationMat InMat_cp=InMat;

  std::cout<<"ConversionIdlMat2cvMat start"<<std::endl;
  ConversionIdlMat2cvMat(CTMat,CV_CTMat);
  std::cout<<"CTMat"<<std::endl;
  std::cout<<CV_CTMat<<std::endl;
  std::cout<<"CTMat_inv"<<std::endl;
  std::cout<<CV_CTMat.inv()<<std::endl;
  ConversionIdlMat2cvMat(InMat_cp,CV_InMat);
  std::cout<<"InMat"<<std::endl;
  std::cout<<CV_InMat<<std::endl;
  cv::Mat CV_CTMat_inv=CV_CTMat.inv();

  std::cout<<"CalibrationMat"<<std::endl;
  std::cout<<CalibrationMat<<std::endl;
  
  std::cout<<"CV_OutMat=CV_InMat*CV_CTMat.inv() start"<<std::endl;
  //CV_OutMat=CV_InMat*CV_CTMat.inv();
  //CV_OutMat=CV_CTMat.inv()*CV_InMat;
  //CV_OutMat=CV_CTMat*CalibrationMat*CV_InMat;
  CV_OutMat=CV_CTMat*CalibrationMat;
  std::cout<<"CV_OutMat=CV_InMat*CV_CTMat.inv() start"<<std::endl;

  CV_OutMat=CV_OutMat*CV_InMat;
  
  std::cout<<"cvMat2ConversionIdlMat start"<<std::endl;
  std::cout<<CV_OutMat<<std::endl;

  cvMat2ConversionIdlMat(CV_OutMat,OutMat);

  return 1;
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  #warning "Code missing in function <::CORBA::Long ConversionMatrix_conversionInterfaceSVC_impl::getConvertionMat(const ConversionMatrix::transformationMat& InMat, ConversionMatrix::transformationMat& OutMat)>"
#endif
  return 0;
}
void ConversionMatrix_conversionInterfaceSVC_impl::ConversionIdlMat2cvMat(ConversionMatrix::transformationMat& ConversionIdl_Mat,cv::Mat& OpenCV_Mat)
{
  OpenCV_Mat.at<float>(0,0)=ConversionIdl_Mat.rotation.R11;
  OpenCV_Mat.at<float>(0,1)=ConversionIdl_Mat.rotation.R12;
  OpenCV_Mat.at<float>(0,2)=ConversionIdl_Mat.rotation.R13;
  OpenCV_Mat.at<float>(1,0)=ConversionIdl_Mat.rotation.R21;
  OpenCV_Mat.at<float>(1,1)=ConversionIdl_Mat.rotation.R22;
  OpenCV_Mat.at<float>(1,2)=ConversionIdl_Mat.rotation.R23;
  OpenCV_Mat.at<float>(2,0)=ConversionIdl_Mat.rotation.R31;
  OpenCV_Mat.at<float>(2,1)=ConversionIdl_Mat.rotation.R32;
  OpenCV_Mat.at<float>(2,2)=ConversionIdl_Mat.rotation.R33;
  OpenCV_Mat.at<float>(0,3)=ConversionIdl_Mat.translates.x;
  OpenCV_Mat.at<float>(1,3)=ConversionIdl_Mat.translates.y;
  OpenCV_Mat.at<float>(2,3)=ConversionIdl_Mat.translates.z;
  OpenCV_Mat.at<float>(3,3)=1.0;
}

void ConversionMatrix_conversionInterfaceSVC_impl::cvMat2ConversionIdlMat(cv::Mat& OpenCV_Mat,ConversionMatrix::transformationMat& ConversionIdl_Mat)
{
  ConversionIdl_Mat.rotation.R11=OpenCV_Mat.at<float>(0,0);
  ConversionIdl_Mat.rotation.R12=OpenCV_Mat.at<float>(0,1);
  ConversionIdl_Mat.rotation.R13=OpenCV_Mat.at<float>(0,2);
  ConversionIdl_Mat.rotation.R21=OpenCV_Mat.at<float>(1,0);
  ConversionIdl_Mat.rotation.R22=OpenCV_Mat.at<float>(1,1);
  ConversionIdl_Mat.rotation.R23=OpenCV_Mat.at<float>(1,2);
  ConversionIdl_Mat.rotation.R31=OpenCV_Mat.at<float>(2,0);
  ConversionIdl_Mat.rotation.R32=OpenCV_Mat.at<float>(2,1);
  ConversionIdl_Mat.rotation.R33=OpenCV_Mat.at<float>(2,2);
  ConversionIdl_Mat.translates.x=OpenCV_Mat.at<float>(0,3);
  ConversionIdl_Mat.translates.y=OpenCV_Mat.at<float>(1,3);
  ConversionIdl_Mat.translates.z=OpenCV_Mat.at<float>(2,3);
  
}


// End of example implementational code



