#include "Collision.h"

Collision::Collision()
{

}

int Collision::ColDecSegLineAABB(SegLine S,AABB A)
{

  const float EPSILON = 1.175494e-37;
  /*
  std::cout << "S.a.x = " << S.a.x << std::endl;
  std::cout << "S.a.y = " << S.a.y << std::endl;
  std::cout << "S.a.z = " << S.a.z << std::endl;
  std::cout << "S.b.x = " << S.b.x << std::endl;
  std::cout << "S.b.y = " << S.b.y << std::endl;
  std::cout << "S.b.z = " << S.b.z << std::endl;
  std::cout << "A.center.x = " << A.center.x << std::endl;
  std::cout << "A.center.y = " << A.center.y << std::endl;
  std::cout << "A.center.z = " << A.center.z << std::endl;
  std::cout << "A.rx = " << A.rx << std::endl;
  std::cout << "A.ry = " << A.ry << std::endl;
  std::cout << "A.rz = " << A.rz << std::endl;
  */
  COLISION_Vector3D m;//線分の中点
  m.x = (S.a.x+S.b.x)*0.5;
  m.y = (S.a.y+S.b.y)*0.5;
  m.z = (S.a.z+S.b.z)*0.5;

  COLISION_Vector3D d;//線分の長さの半分のベクトル
  d.x = S.b.x - m.x;
  d.y = S.b.y - m.y;
  d.z = S.b.z - m.z;

  //ボックスと線分を原点まで平行移動
  m.x = m.x - A.center.x;
  m.y = m.y - A.center.y;
  m.z = m.z - A.center.z;

  //ワールド座標系が分離軸であるか試す
  float adx = fabsf(d.x);
  float ady = fabsf(d.y);
  float adz = fabsf(d.z);
  if(fabsf(m.x) > A.rx + adx)
    return 0;
  if(fabsf(m.y) > A.ry + ady)
    return 0;
  if(fabsf(m.z) > A.rz + adz)
    return 0;

  //線分が座標軸に平行（あるいはそれに近い状態）の時に
  //イプシロンの項を追加して演算の誤りの影響を弱める
  adx += EPSILON;
  ady += EPSILON;
  adz += EPSILON;

  //線分の方向ベクトルの外積を座標軸に対して試す
  if(fabsf(m.y*d.z - m.z*d.y) > A.ry*adz + A.rz*ady)
    return 0;
  if(fabsf(m.z*d.x - m.x*d.z) > A.rx*adz + A.rz*adx)
    return 0;
  if(fabsf(m.x*d.y - m.y*d.x) > A.rx*ady + A.ry*adx)
    return 0;

  return 1;//Collision
  
}

int Collision::ColDecCapsuleAABB(Capsule C,AABB A)
{
  return 0;
}
