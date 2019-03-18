// -*-C++-*-
/*!
 * @file  MarkerObstacleSVC_impl.h
 * @brief Service implementation header of MarkerObstacle.idl
 *
 */

#include "BasicDataTypeSkel.h"
#include "ExtendedDataTypesSkel.h"

#include "MarkerObstacleSkel.h"

#ifndef MARKEROBSTACLESVC_IMPL_H
#define MARKEROBSTACLESVC_IMPL_H
 
/*!
 * @class Obstacle_ObstacleInterfaceSVC_impl
 * Example class implementing IDL interface Obstacle::ObstacleInterface
 */
class Obstacle_ObstacleInterfaceSVC_impl
 : public virtual POA_Obstacle::ObstacleInterface,
   public virtual PortableServer::RefCountServantBase
{
 private:
   // Make sure all instances are built on the heap by making the
   // destructor non-public
   //virtual ~Obstacle_ObstacleInterfaceSVC_impl();

 public:
  /*!
   * @brief standard constructor
   */
   Obstacle_ObstacleInterfaceSVC_impl();
  /*!
   * @brief destructor
   */
   virtual ~Obstacle_ObstacleInterfaceSVC_impl();

   // attributes and operations
  void getDisplayShelfObstacle(Obstacle::AABBSeq_out obastacleData);
  Obstacle::AABBSeq AABBList;
};



#endif // MARKEROBSTACLESVC_IMPL_H


