// -*-C++-*-
/*!
 * @file  MatrixInterfaceSVC_impl.h
 * @brief Service implementation header of MatrixInterface.idl
 *
 */

#include "BasicDataTypeSkel.h"
#include "ExtendedDataTypesSkel.h"

#include "MatrixInterfaceSkel.h"

#include "SeedLifterEyeLinkKinematics.h"

/********* includeファイル *********/
//数学定数の使用
#define _USE_MATH_DEFINES
#include <math.h>
#include "ikfast.h"
#include "lifterUnit2Kinematics.h"

#ifndef MATRIXINTERFACESVC_IMPL_H
#define MATRIXINTERFACESVC_IMPL_H

class SeedLifterEyeLinkKinematics;

/*!
 * @class TransformationMatrix_transformationInterfaceSVC_impl
 * Example class implementing IDL interface TransformationMatrix::transformationInterface
 */
class TransformationMatrix_transformationInterfaceSVC_impl
 : public virtual POA_TransformationMatrix::transformationInterface,
   public virtual PortableServer::RefCountServantBase
{
 private:
   // Make sure all instances are built on the heap by making the
   // destructor non-public
   //virtual ~TransformationMatrix_transformationInterfaceSVC_impl();
  SeedLifterEyeLinkKinematics* m_rtcPtr;
  
 public:
  /*!
   * @brief standard constructor
   */
   TransformationMatrix_transformationInterfaceSVC_impl();
  /*!
   * @brief destructor
   */
   virtual ~TransformationMatrix_transformationInterfaceSVC_impl();

   // attributes and operations
   ::CORBA::Long getMatrix(TransformationMatrix::transformationMat& Matrix);
  void setCompPtr(SeedLifterEyeLinkKinematics* ptr){m_rtcPtr=ptr;}

};



#endif // MATRIXINTERFACESVC_IMPL_H


