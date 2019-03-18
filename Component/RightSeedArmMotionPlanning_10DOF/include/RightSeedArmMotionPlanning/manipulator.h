#ifndef __MANIPULATOR_H__
#define __MANIPULATOR_H__

#define _USE_MATH_DEFINES

#include <iostream>
#include <stdio.h>
#include <math.h>
#include "Collision.h"
#include "ikfast.h"
#include "seednoid_ikfast.h"
#include <math.h>
#include "LibSeednoidUpperUnit1.h" 

#define DOF 10
#define LinkNum 6
#define LINK1 1366.4
#define LINK2 246.812
#define LINK3 279.642
#define LINK4 122.4


typedef struct{
  float theta1;
  float theta2;
  float theta3;
  float theta4;
}fourDOF;

typedef struct{
  float theta1;
  float theta2;
  float theta3;
  float theta4;
  float theta5;
  float theta6;
}SixDOF;

typedef struct{
  float theta1;
  float theta2;
  float theta3;
  float theta4;
  float theta5;
  float theta6;
  float theta7;
  float theta8;
}EightDOF;

typedef struct{
  float theta1;
  float theta2;
  float theta3;
  float theta4;
  float theta5;
  float theta6;
  float theta7;
  float theta8;
  float theta9;
  float theta10;
}TenDOF;

typedef struct{
  float theta1;
  float theta2;
  float theta3;
  float theta4;
  float theta5;
  float theta6;
  float theta7;
  float theta8;
  float theta9;
  float theta10;
}TwelveDOF;

class Manipulator{
 private:
  
  //private変数の宣言
  
  //private関数の定義
  
 public:
  //コンストラクタ
  Manipulator();
  void CalcManipLinkPos(fourDOF J,SegLine manip[LinkNum]);
  void CalcManipLinkPos_ten(TenDOF J,SegLine manip[LinkNum]);
  void CalcManipLinkPos_ten_Lifter(TenDOF J,SegLine manip[LinkNum],double Lifter_bottom,double Lifter_top);

  
};

#endif//__MANIPULATOR_H__
