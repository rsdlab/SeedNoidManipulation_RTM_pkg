#ifndef _SEED_COMMAND_H_
#define _SEED_COMMAND_H_


#include <chrono>
#include <thread>
//SerialCom include
#include "SerialCom.h"
//MecanumWheel include
#include "MecanumWheel.h"

struct Lifter
{
  //Angle of Top Lifter in degrees
  double top;
  //Angle of Bottom Lifter in degrees
  double bottom;
};

class SeedCommand
{
 public:

  static const int ENCODER_THRESHOLD = 10000;

  bool isInitialize;

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
  SeedCommand();

  //=========================================================================
  //初期設定関数
  //SEED-Noidの台車パラメータを設定する
  //
  //引数：
  //wheelRadius：ホイールの半径[m]
  //tread：トレッド(左右ホイールの間隔)[m]
  //wheelBase：前後ホイールの間隔[m]
  //
  //返り値：
  //なし
  //=========================================================================
  void seedSetParam(const double wheelRadius,const double tread,const double wheelBase);

  //=========================================================================
  //初期設定関数
  //SEED-Noidとの通信を開始する
  //
  //引数：
  //port：接続されたポートの番号　例："/dev/ttyUSB0"
  //baudrate：通信速度　デフォルト値：1000000
  //
  //返り値：
  //なし
  //=========================================================================
  void seedSerialOpen(const std::string portName,int baudRate);

  //=========================================================================
  //初期設定関数
  //SEED-Noidとの通信を終了する
  //
  //引数：
  //なし
  //
  //返り値：
  //true: 正常終了　false: 異常発生(表示されるエラー内容を参照)
  //=========================================================================
  void seedSerialClose();

  //=========================================================================
  //サーボON/OFF関数
  //SEED-NoidのサーボモータのON/OFFを切り替える
  //
  //引数：
  //sendNo：ON/OFFを切り替えるサーボモータの指定
  //sendParam：ON/OFFの指定(0:サーボOFF, 1:サーボON)
  //allMode：サーボモータ単一か全てかの指定(0:選択したサーボモータON/OFFモード, 1:すべてのサーボモータON/OFFモード)
  //
  //返り値：
  //なし
  //=========================================================================
  void seedSendServo(unsigned char sendNo,unsigned short sendParam,unsigned char allMode);

  //=========================================================================
  //台車制御関数
  //SEED-Noid台車への速度入力から各ホイールの角速度を計算し，台車の制御をする
  //
  //引数：
  //targetVelocity：台車の目標速度 並進[m/s], 旋回[rad/s]
  //
  //返り値：
  //なし
  //=========================================================================
  void seedSendTruckSpeed(struct Velocity targetVelocity);

  //=========================================================================
  //オドメトリ計算関数
  //SEED-Noidからエンコーダ値を取得し，オドメトリを計算する
  //
  //引数：
  //odometryData：台車の位置・姿勢(ロボット座標系) 位置[m], 姿勢[rad]
  //
  //返り値：
  //true: 正常終了　false: 異常発生(表示されるエラー内容を参照)
  //=========================================================================
  bool seedCalcOdometry(struct Pose &odometryData);

  //=========================================================================
  //チェック関数
  //入力された角度[deg]がリフターの可動範囲であるかを確認する
  //
  //引数：
  //targetLifterAngle：各リフターの目標角度[deg]
  //
  //返り値：
  //true: 正常終了　false: 異常発生(表示されるエラー内容を参照)
  //=========================================================================
  bool CheckTargetAngle(struct Lifter targetLifterAngle);

  //=========================================================================
  //チェック関数
  //入力された位置[m]がリフターの可動範囲であるかを確認する
  //
  //引数：
  //targetLifterPose：リフターの目標姿勢[m]
  //
  //返り値：
  //true: 正常終了　false: 異常発生(表示されるエラー内容を参照)
  //=========================================================================
  bool CheckTargetPose(struct Pose targetLifterPose);

  //=========================================================================
  //リフター制御関数
  //SEED-Noidのリフターの順運動学を計算する
  //
  //引数：
  //targetLifterAngle：各リフターの目標角度[deg]
  //time：移動時間[ms]
  //
  //返り値：
  //なし
  //=========================================================================
  void seedMoveLifterForwardKinematics(struct Lifter targetLifterAngle,int time);

  //=========================================================================
  //リフター制御関数
  //SEED-Noidのリフターの逆運動学を計算する
  //
  //引数：
  //targetLifterAngle：リフターの目標姿勢[m]
  //time：移動時間[ms]
  //
  //返り値：
  //なし
  //=========================================================================
  void seedMoveLifterInverseKinematics(struct Pose targetLifterPose,int time);

  //=========================================================================
  //リフター角度取得関数
  //SEED-Noidのリフターの現在の角度を取得する
  //
  //引数：
  //currentLifterAngle：各リフターの現在角度[deg]
  //
  //返り値：
  //なし
  //=========================================================================
  bool seedGetLifterAngle(struct Lifter &currentLifterAngle);

  //=========================================================================
  //リフター姿勢取得関数
  //SEED-Noidのリフターの現在の姿勢を取得する
  //
  //引数：
  //currentLifterPose：リフターの姿勢[m]
  //
  //返り値：
  //なし
  //=========================================================================
  bool seedGetLifterPose(struct Pose &currentLifterPose);

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
  void resetParam();

 private:

  unsigned int checkSum,checkCount,dataLength;
  double lifterLength,calcLifterAngleTop,calcLifterAngleBottom;
  struct Lifter lifterAngle;
  int lifterAngleLimit,lifterTop,lifterBottom;
  struct Wheel_double angularVelocity;
  struct Wheel_int currentEncoder,oldEncoder,diffEncoder,countEncoder,encoderData;

  std::vector<unsigned char> mobileSendData;
  std::vector<unsigned char> mobileReceiveData;

  std::vector<unsigned char> lifterSendData;
  std::vector<unsigned char> lifterReceiveData;

};

#endif     //_SEED_COMMAND_H_
