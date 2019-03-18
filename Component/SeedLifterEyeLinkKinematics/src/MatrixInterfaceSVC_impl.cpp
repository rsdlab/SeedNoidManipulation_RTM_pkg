// -*-C++-*-
/*!
 * @file  MatrixInterfaceSVC_impl.cpp
 * @brief Service implementation code of MatrixInterface.idl
 *
 */

#include "MatrixInterfaceSVC_impl.h"

/*
 * Example implementational code for IDL interface TransformationMatrix::transformationInterface
 */
TransformationMatrix_transformationInterfaceSVC_impl::TransformationMatrix_transformationInterfaceSVC_impl()
{
  // Please add extra constructor code here.
}


TransformationMatrix_transformationInterfaceSVC_impl::~TransformationMatrix_transformationInterfaceSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
::CORBA::Long TransformationMatrix_transformationInterfaceSVC_impl::getMatrix(TransformationMatrix::transformationMat& Matrix)
{
  std::cout << "getMatrix" << std::endl;
  double LifterPos[2];
  double WaistPos[3];
  double NeckPos[3];
  std::cout << "getSeedCurrentJoint" << std::endl;
  m_rtcPtr->getSeedCurrentJoint(LifterPos,WaistPos,NeckPos);


  std::cout << "NeckPos[0] = " << NeckPos[0] << std::endl;
  std::cout << "NeckPos[1] = " << NeckPos[1] << std::endl;
  std::cout << "NeckPos[2] = " << NeckPos[2] << std::endl;
  std::cout << "WaistPos[0] = " << WaistPos[0] << std::endl;
  std::cout << "WaistPos[1] = " << WaistPos[1] << std::endl;
  std::cout << "WaistPos[2] = " << WaistPos[2] << std::endl;

  std::cout << "Solve FK" <<std::endl;

  double ikjoint[8];
  double calceerot[9];
  double calceetrans[3];
  ikjoint[0] = WaistPos[0]*M_PI/180;
  ikjoint[1] = WaistPos[1]*M_PI/180;
  ikjoint[2] = WaistPos[2]*M_PI/180;
  ikjoint[3] = NeckPos[0]*M_PI/180;
  ikjoint[4] = NeckPos[1]*M_PI/180;
  ikjoint[5] = NeckPos[2]*M_PI/180;
  ikjoint[6] = -90*M_PI/180;//カメラ座標変換
  ikjoint[7] = 90*M_PI/180; //カメラ座標変換

  ComputeFk(ikjoint,calceetrans,calceerot);
  //for(int j=0;j<7;j++)
  //  {
  //    std::cout << "right_ik_joint["<<j<<"] = "<<ikjoint[j]<<std::endl;
  //  }

  double LifterEEtrans[3];
  LIFTER_KINEMA::Solve_Lifter_Fk(LifterEEtrans,LifterPos);
  
  Matrix.rotation.R11 = calceerot[0];
  Matrix.rotation.R12 = calceerot[1];
  Matrix.rotation.R13 = calceerot[2];
  Matrix.rotation.R21 = calceerot[3];
  Matrix.rotation.R22 = calceerot[4];
  Matrix.rotation.R23 = calceerot[5];
  Matrix.rotation.R31 = calceerot[6];
  Matrix.rotation.R32 = calceerot[7];
  Matrix.rotation.R33 = calceerot[8];
  Matrix.translates.x = calceetrans[0]*1000 + LifterEEtrans[0];
  Matrix.translates.y = calceetrans[1]*1000 + LifterEEtrans[1];
  Matrix.translates.z = calceetrans[2]*1000 + LifterEEtrans[2];

  std::cout << "| " << Matrix.rotation.R11 << "  " << Matrix.rotation.R12 << "  " << Matrix.rotation.R13 << "  " << Matrix.translates.x << "|" << std::endl;
  std::cout << "| " << Matrix.rotation.R21 << "  " << Matrix.rotation.R22 << "  " << Matrix.rotation.R23 << "  " << Matrix.translates.y << "|" << std::endl;
  std::cout << "| " << Matrix.rotation.R31 << "  " << Matrix.rotation.R32 << "  " << Matrix.rotation.R33 << "  " << Matrix.translates.z << "|" << std::endl;

  std::cout << "Success" << std::endl;

  return 0;
}



// End of example implementational code



