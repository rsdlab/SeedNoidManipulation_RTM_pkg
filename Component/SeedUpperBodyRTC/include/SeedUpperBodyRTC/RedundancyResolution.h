//RedundancyResolution.h
#ifndef __REDUNDANCYRESOLUTION_H__
#define __REDUNDANCYRESOLUTION_H__

#define _USE_MATH_DEFINES

#include <iostream>
#include <stdio.h>
#include "LibSeednoidUpper.h"
#include <time.h>
#include <vector>
#include <algorithm>
#include <sys/time.h>
#include <math.h>
#include <flann/flann.hpp>

#define REDUN_DOF 4
 
typedef struct{
  
  float theta1;
  float theta2;
  float theta3;
  float theta4;

}REDUN_fourDOF;

class Redundancy{
 private:
  
 public:
  Redundancy();

  int getRightRedundantJoint(double eerot[9], double eetrans[3], double nowJoint[4], double redundancyJoint[], double endEEtrans[]);
  int getLeftRedundantJoint(double eerot[9], double eetrans[3], double nowJoint[4], double redundancyJoint[], double endEEtrans[]);

};


#endif//__REDUNDANCYRESOLUTION_H__
