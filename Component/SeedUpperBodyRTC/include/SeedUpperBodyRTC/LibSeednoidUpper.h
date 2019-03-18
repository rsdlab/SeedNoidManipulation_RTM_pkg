//LibSeedonoidUpperUnit1.h
#ifndef __LIBSEEDNOIDUPPERUNIT1_H__
#define __LIBSEEDNOIDUPPERUNIT1_H__


//_USE_SERIALCOM_BOOST  シリアル通信にboostを使用する。



//数学定数の使用
#define _USE_MATH_DEFINES

//SerialComBoostの使用
#define _USE_SERIALCOM_BOOST


/********* includeファイル *********/
//#include <cmath>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include "ikfast.h"
#include "seednoid_ikfast.h"
#include <fstream>
#include "Eigen/Dense"
#include "Eigen/LU"
#include "RedundancyResolution.h"

#ifdef _USE_SERIALCOM_BOOST
#include "SerialCom.h"
#else
#include <sys/types.h>
 #include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <termios.h>
#include <unistd.h>
#endif

typedef unsigned char uchar;
typedef unsigned int uint;

#define SEND_DATALENGTH 60
#define SEED_FREEDOM 30
#define ARM_FREEDOM 7

//腕関節の可動範囲[deg]
//アーム第1軸モータの可動範囲
#define	Angle1_LimitMax	89
#define	Angle1_LimitMin	-20
//アーム第2軸モータの可動範囲
#define	Angle2_LimitMax	90
#define	Angle2_LimitMin 0
//アーム第3軸モータの可動範囲
#define	Angle3_LimitMax	135
#define	Angle3_LimitMin	-135
//アーム第4軸モータの可動範囲
#define	Angle4_LimitMax	180
#define	Angle4_LimitMin	0
//アーム第5軸モータの可動範囲
#define Angle5_LimitMax 135
#define Angle5_LimitMin -135
//アーム第6軸モータの可動範囲
#define Angle6_LimitMax 40
#define Angle6_LimitMin -80
//アーム第7軸モータの可動範囲
#define Angle7_LimitMax 180
#define Angle7_LimitMin -180
//アーム肘分解時αモータの可動範囲
#define Angle4a_LimitMax 90
#define Angle4a_LimitMin 0
//アーム肘分解時bモータの可動範囲
#define Angle4b_LimitMax 90
#define Angle4b_LimitMin 0
//頭ロール（左右）の可動範囲
#define NeckRoll_LimitMax 20
#define NeckRoll_LimitMin -20
//頭ピッチ（前後）の可動範囲
#define NeckPitch_LimitMax 45
#define NeckPitch_LimitMin -20
//頭ヨー（回転）の可動範囲
#define NeckYaw_LimitMax 120
#define NeckYaw_LimitMin -120
//腰ロール（左右）の可動範囲
#define WaistRoll_LimitMax 8
#define WaistRoll_LimitMin -8
//腰ピッチ（前後）の可動範囲
#define WaistPitch_LimitMax 39
#define WaistPitch_LimitMin -9
//腰ヨー（回転）の可動範囲
#define WaistYaw_LimitMax 120
#define WaistYaw_LimitMin -120

//ハンドの可動範囲
#define HAND_LIMITMAX 0
#define HAND_LIMITMIN 1800

//リフターパラメータ
#define LIFTER_L1 250
#define LIFTER_L2 250
#define MOBILE_LIFTER_Z 415


//ジョイントリミットの構造体
typedef struct
{
  short Upper;
  short Lower;
}JLimit;

//ロールピッチヨー
typedef struct
{
  double roll;
  double pitch;
  double yaw;
}Frame;

class SeedUpper{
 private:
  
  //private変数の宣言
  int noidJointPos[SEED_FREEDOM];
  JLimit SeedArmJointLimit[ARM_FREEDOM];
  JLimit SeedNeckJointLimit[3];
  JLimit SeedWaistJointLimit[3];
  double ReadAngle[SEED_FREEDOM];
  double NowAngle[SEED_FREEDOM];
  double RightArmSetJointPos[ARM_FREEDOM];
  double LeftArmSetJointPos[ARM_FREEDOM];
  double NeckSetJointPos[3];
  double WaistSetJointPos[3];
  int NeedCancelScriptRightHand;
  int NeedCancelScriptLeftHand;
  //シリアル通信
  char *dev;
  //std::vector<unsigned char> sendData;
  std::vector<unsigned char> actionSendData;
  std::vector<unsigned char> readSendData;
  std::vector<unsigned char> receiveData;
#ifndef _USE_SERIALCOM_BOOST
  int fd;
  struct termios newtio;
#endif
  
 //private関数の定義
  void serialWrite(std::vector<unsigned char> sendData);
  void serialRead(int length);
  void serialFlush();
  uchar calcCheckSum(std::vector<unsigned char> sendData, int Datasize);
  int Solve_WRArm_VirtualIk(double eerot[9], double eetrans[3], double elbow, Frame WaistPos, double nowJointPos[], double iksol[]);
  int Solve_WLArm_VirtualIk(double eerot[9],double eetrans[3], double elbow, Frame WaistPos, double nowJointPos[], double iksol[]);
  int Solve_WRArm_RealIk(double eerot[9],double eetrans[3], double elbow, double elbow_a, Frame WaistPos, double nowJointPos[], double iksol[]);
  int Solve_WLArm_RealIk(double eerot[9],double eetrans[3], double elbow, double elbow_a, Frame WaistPos, double nowJointPos[], double iksol[]);
  int Solve_WRArm_RealFk(double eerot[9],double eetrans[3], double joint[]);
  int Solve_WLArm_RealFk(double eerot[9],double eetrans[3], double joint[]);
  
 public:
 //コンストラクタ
 SeedUpper();
 
 // シリアル通信関数
 int OpenSerialPort(const char *SERIAL_PORT);
 void CloseSerialPort();
 int ReadServoAngle(double ReadServoAngle[]);


 //変数セット関数
 int setRightJointAngle(double JointPos[]);
 int setLeftJointAngle(double JointPos[]);
 int setNeckJointAngle(Frame pos);
 int setWaistJointAngle(Frame pos); 

 void getRightJointAngle(double JointPos[]);
 void getLeftJointAngle(double JointPos[]);
 Frame getNeckJointAngle();
 Frame getWaistJointAngle(); 

 void readAllJointAngle(Frame* WaistPos, Frame* NeckPos, double RightJointPos[], double LeftJointPos[]);
 void readRightJointAngle(double JointPos[]);
 void readLeftJointAngle(double JointPos[]);
 Frame readNeckJointAngle();
 Frame readWaistJointAngle();

 //一定の実行周期で角度を取り続けるための関数
 int ReadServoAngleAndSetNowAngle();
 void notReadGetNowRightJointAngle(double JointPos[]);
 void notReadGetNowLeftJointAngle(double JointPos[]);
 Frame notReadGetNowNeckJointAngle();
 Frame notReadGetNowWaistJointAngle(); 
 
  //Seednoidに関する関数
  void initPosition();
  void ServoOnOff(int torque);
  void RightArmServoOnOff(int torque);
  void RightGripperServoOnOff(int torque);
  void LeftArmServoOnOff(int torque);
  void LeftGripperServoOnOff(int torque);
  void SeedAction(int mtime);
  void OpenRightGripper();
  void CloseRightGripper();
  void MoveRightGripper(int angleRatio);
  void OpenLeftGripper();
  void CloseLeftGripper();
  void MoveLeftGripper(int angleRatio);
  void TransRot(double eerot[],double roll,double pitch,double yaw);
  Frame Solve_Rot(double eerot[]);
  int Solve_RightArmIk(double eerot[9],double eetrans[3], double elbow, double nowJointPos[], double iksol[]);
  int Solve_LeftArmIk(double eerot[9],double eetrans[3], double elbow, double nowJointPos[], double iksol[]);
  int Solve_RightArmFk(double eerot[9],double eetrans[3],double joint[]);
  int Solve_LeftArmFk(double eerot[9],double eetrans[3],double joint[]);
  int Solve_WRArmIk(double eerot[9], double eetrans[3], double elbow, Frame WaistPos, double nowJointPos[], double iksol[]);
  int Solve_WLArmIk(double eerot[9],double eetrans[3], double elbow, Frame WaistPos, double nowJointPos[], double iksol[]); 
  int Solve_WRArmFk(double eerot[9],double eetrans[3], double joint[]);
  int Solve_WLArmFk(double eerot[9],double eetrans[3], double joint[]);
  int Solve_LIWARArmIkSetRedun(double eerot[9],double eetrans[3], double elbow, Frame WaistPos, double lifter[], double nowJointPos[], double iksol[]);
  int Solve_LIWALArmIkSetRedun(double eerot[9],double eetrans[3], double elbow, Frame WaistPos, double lifter[], double nowJointPos[], double iksol[]);
  int Solve_LIWARArmIk(double eerot[9],double eetrans[3], double nowJointPos[], double iksol[]);
  int Solve_LIWALArmIk(double eerot[9],double eetrans[3], double nowJointPos[], double iksol[]);
  int Solve_LIWARArmFk(double eerot[9],double eetrans[3], double joint[]);
  int Solve_LIWALArmFk(double eerot[9],double eetrans[3], double joint[]);
  int Solve_Lifter_Fk(double eetrans[3], double joint[]);
  void setRightHandCurrent(int CurrentRate);
  void setLeftHandCurrent(int CurrentRate);
  void cancelScriptRightHand();
  void cancelScriptLeftHand();

  
};
#ifdef _USE_SERIALCOM_BOOST
//extern SerialCom usc;
#endif
//extern SeedUpper noid;

#endif//__LIBSEEDNOIDUPPERUNIT1_H__
