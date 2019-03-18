// -*-C++-*-
/*!
 * @file  MarkerObstacleSVC_impl.cpp
 * @brief Service implementation code of MarkerObstacle.idl
 *
 */

#include "MarkerObstacleSVC_impl.h"
#include <iostream>

/*
 * Example implementational code for IDL interface Obstacle::ObstacleInterface
 */
Obstacle_ObstacleInterfaceSVC_impl::Obstacle_ObstacleInterfaceSVC_impl()
{
  // Please add extra constructor code here.
}


Obstacle_ObstacleInterfaceSVC_impl::~Obstacle_ObstacleInterfaceSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
void Obstacle_ObstacleInterfaceSVC_impl::getDisplayShelfObstacle(Obstacle::AABBSeq_out obastacleData)
{
  std::cout << "getDisplayShelfObstacle" << std::endl;
  obastacleData = new Obstacle::AABBSeq;
  obastacleData->length(AABBList.length());
  int length = AABBList.length();
  for(int i=0;i<length;i++)
    {
      (*obastacleData)[i].center.x = AABBList[i].center.x;
      (*obastacleData)[i].center.y = AABBList[i].center.y;
      (*obastacleData)[i].center.z = AABBList[i].center.z;
      (*obastacleData)[i].rx = AABBList[i].rx;
      (*obastacleData)[i].ry = AABBList[i].ry;
      (*obastacleData)[i].rz = AABBList[i].rz;
    }

  std::cout << "Success" << std::endl;
}



// End of example implementational code



