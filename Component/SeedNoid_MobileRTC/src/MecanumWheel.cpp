#include "MecanumWheel.h"

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
MecanumWheel::MecanumWheel()
{
  //変数の初期化
  currentPose = {0.0, 0.0, 0.0, 0.0};
  oldEncoder = {0, 0, 0, 0};
  deltaEncoder = {0, 0, 0, 0};

  isInitialized = false;
}

//=========================================================================
//初期設定関数
//メカナムホイール台車のパラメータを設定する
//
//引数：
//wheelRadius：ホイールの半径[m]
//tread：トレッド(左右ホイールの間隔)[m]
//wheelBase：前後ホイールの間隔[m]
//
//返り値：
//なし
//=========================================================================
void MecanumWheel::setMobileRobotParam(double wheelRadius, double tread, double wheelBase)
{
  wheelRadiusParam = wheelRadius;
  treadParam = tread;
  wheelBaseParam = wheelBase;
}

//=========================================================================
//運動学計算関数
//移動台車への速度入力から各ホイールの角速度を計算する
//
//引数：
//targetVelocity：台車の目標速度 並進[m/s], 旋回[rad/s]
//&angularVelocity：各ホイールの回転角速度[rpm]
//
//返り値：
//なし
//=========================================================================
void MecanumWheel::calcMecanumWheelKinematics(struct Velocity targetVelocity, struct Wheel_double &angularVelocity)
{
  //各ホイールの角速度を計算
  angularVelocity.rightFront = 60 * (targetVelocity.vx + targetVelocity.vy + ((treadParam / 2) + (wheelBaseParam / 2)) * targetVelocity.va) / wheelRadiusParam;     //Right front wheel angular velocity
  angularVelocity.rightBack = 60 * (targetVelocity.vx - targetVelocity.vy + ((treadParam / 2) + (wheelBaseParam / 2)) * targetVelocity.va) / wheelRadiusParam;     //Right Back wheel angular velocity
  angularVelocity.leftFront = 60 * (targetVelocity.vx - targetVelocity.vy - ((treadParam / 2) + (wheelBaseParam / 2)) * targetVelocity.va) / wheelRadiusParam;     //Left right wheel angular velocity
  angularVelocity.leftBack = 60 * (targetVelocity.vx + targetVelocity.vy - ((treadParam / 2) + (wheelBaseParam / 2)) * targetVelocity.va) / wheelRadiusParam;     //Left Back wheel angular velocity
}

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
void MecanumWheel::calcMecanumWheelOdometry(struct Wheel_int encoder, struct Pose &odometry)
{
  //エンコーダに値が残っている場合
  if(!isInitialized)
    {
      oldEncoder = encoder;
      isInitialized = true;
    }

  //前回のエンコーダ値との差を計算
  deltaEncoder.rightFront = encoder.rightFront - oldEncoder.rightFront;
  deltaEncoder.rightBack = encoder.rightBack - oldEncoder.rightBack;
  deltaEncoder.leftFront = encoder.leftFront - oldEncoder.leftFront;
  deltaEncoder.leftBack = encoder.leftBack - oldEncoder.leftBack;

  //移動量の計算
  //前方の移動量
  double forward = static_cast<double>((2 * M_PI * wheelRadiusParam * (deltaEncoder.rightFront + deltaEncoder.rightBack + deltaEncoder.leftFront + deltaEncoder.leftBack) / 360) / 4);
  //側方の移動量
  double lateral = static_cast<double>((2 * M_PI * wheelRadiusParam * (deltaEncoder.rightFront - deltaEncoder.rightBack - deltaEncoder.leftFront + deltaEncoder.leftBack) / 360) / 4);
  //旋回量
  double rotate = static_cast<double>((2 * M_PI * wheelRadiusParam * (deltaEncoder.rightFront + deltaEncoder.rightBack - deltaEncoder.leftFront - deltaEncoder.leftBack) / 360) / (4 * ((treadParam / 2 ) + (wheelBaseParam / 2))));
    
  //オドメトリによる現在位置の計算
  //x軸位置(ロボット座標系)
  currentPose.x += (forward * std::cos(currentPose.heading + rotate) - lateral * std::sin(currentPose.heading + rotate));
  //y軸位置(ロボット座標系)
  currentPose.y += (forward * std::sin(currentPose.heading + rotate) + lateral * std::cos(currentPose.heading + rotate));
  //姿勢(ロボット座標系)
  currentPose.heading += rotate;
  
  //姿勢を(-PI < currentPose.heading < PI)内の値に変換
  if(currentPose.heading < -M_PI)
    {
      currentPose.heading += 2 * M_PI;
    }
  else if(currentPose.heading > M_PI)
    {
      currentPose.heading -= 2 * M_PI;
    }

  //参照渡しの変数に計算した現在位置データを格納
  odometry = currentPose;

  //次の計算の為に現在の値を格納
  oldEncoder = encoder;
}

//=========================================================================
//リセット関数
//変数内のデータをリセットする
//
//引数：
//なし
//
//返り値：
//なし
//=========================================================================
void MecanumWheel::resetParam()
{
  //変数内のデータをリセットする
  currentPose = {0.0, 0.0, 0.0, 0.0};

  isInitialized = false;
}
