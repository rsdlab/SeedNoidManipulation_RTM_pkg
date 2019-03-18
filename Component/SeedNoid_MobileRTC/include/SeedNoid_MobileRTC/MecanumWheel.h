#ifndef _MECANUM_WHEEL_H_
#define _MECANUM_WHEEL_H_

//Include
#include <iostream>
#include <stdio.h>
#include <cmath>

struct Wheel_int
{
  //Right front wheel parameter 
  int rightFront;
  //Right back wheel parameter
  int rightBack;
  //Left front wheel parameter
  int leftFront;
  //Left Back wheel parameter
  int leftBack;
};

struct Wheel_double
{
  //Right front wheel parameter 
  double rightFront;
  //Right back wheel parameter
  double rightBack;
  //Left front wheel parameter
  double leftFront;
  //Left Back wheel parameter
  double leftBack;
};

struct Velocity
{
  //Velocity along the x axis in metres per second
  double vx;
  //Velocity along the y axis in metres per second
  double vy;
  //Yaw velocity in radians per second
  double va;
};

struct Pose
{
  //X coordinate in metres
  double x;
  //Y coordinate in metres
  double y;
  //Z coordinate in metres
  double z;
  //Heading in dadians
  double heading;
};


class MecanumWheel
{
 public:

  bool isInitialized;

  //=========================================================================
  //コンストラクタ
  //プログラムの最初で呼び出す関数
  //
  //引数：
  //なし
  //
  //返り値：
  //なし
  //
  //=========================================================================
  MecanumWheel();

  //=========================================================================
  //初期設定関数
  //メカナムホイール台車のパラメータを設定する
  //
  //引数：
  //wheelRadius：ホイールの半径
  //tread：トレッド(左右ホイールの間隔)
  //wheelBase：前後ホイールの間隔
  //
  //返り値：
  //なし
  //=========================================================================
  void setMobileRobotParam(double wheelRadius, double tread, double wheelBase);
  
  //=========================================================================
  //運動学計算関数
  //移動台車への速度入力から各ホイールの角速度を計算する
  //
  //引数：
  //targetVelocity：台車の目標速度
  //&angularVelocity：各ホイールの回転角速度
  //
  //返り値：
  //なし
  //=========================================================================
  void calcMecanumWheelKinematics(struct Velocity targetVelocity, struct Wheel_double &angularVelocity);

  //=========================================================================
  //オドメトリ計算関数
  //エンコーダ値からオドメトリを計算する
  //
  //引数：
  //encoder：エンコーダ値
  //&odometry：オドメトリ 位置[m], 姿勢[rad]
  //
  //返り値：
  //なし
  //=========================================================================
  void calcMecanumWheelOdometry(struct Wheel_int encoder, struct Pose &odometry);
  
  //=========================================================================
  //リセット関数
  //変数をリセットする
  //
  //引数：
  //なし
  //
  //返り値：
  //なし
  //=========================================================================
  void resetParam();
  
 private:
  
  double wheelRadiusParam,treadParam,wheelBaseParam;
  struct Pose currentPose;
  struct Wheel_int oldEncoder;
  struct Wheel_int deltaEncoder;

};

#endif     //_MECANUM_WHEEL_H_
