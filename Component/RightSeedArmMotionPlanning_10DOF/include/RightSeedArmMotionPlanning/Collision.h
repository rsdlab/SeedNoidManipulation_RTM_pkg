#ifndef __COLLISIONDETECTION_H__
#define __COLLISIONDETECTION_H__

#include <iostream>
#include <stdio.h>
#include <math.h>


typedef struct{
  float roll;
  float pitch;
  float yaw;
}RPY;

typedef struct{
  float x;
  float y;
  float z;
}COLISION_Point3D;

typedef struct{
  float x;
  float y;
  float z;
}COLISION_Vector3D;

typedef struct{
  COLISION_Point3D center;
  float rx;//半径
  float ry;
  float rz;
}AABB;

typedef struct{
  COLISION_Point3D center;
  float radius;
}Sphere;

typedef struct{
  COLISION_Point3D center;
  RPY R;
  COLISION_Vector3D radius;
}OBB;

typedef struct{
  COLISION_Point3D a;
  COLISION_Point3D b;
  float radius;
}Capsule;

typedef struct{
  COLISION_Point3D a;
  COLISION_Point3D b;
}SegLine;

class Collision{
 private:
  
  //private変数の宣言
  
  //private関数の定義
  
 public:
  //コンストラクタ
  Collision();
  int ColDecSegLineAABB(SegLine S,AABB A);
  int ColDecCapsuleAABB(Capsule C,AABB A);

  
};





#endif//__COLLISIONDETECTION_H__
