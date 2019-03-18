#include "SeedCommand.h"

SerialCom sc;
MecanumWheel meca;

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
SeedCommand::SeedCommand()
{
  //変数の初期化
  checkSum = 0;
  checkCount = 0;
  dataLength = 0;

  lifterLength = 0.25/*[m]*/;     //SEED-Noidのリフター1つの長さ(2つだと0.5[m])
  lifterAngleLimit = 85/*[deg]*/;     //SEED-Noidのリフターの可動範囲の上限として85[deg]以上にならないようにする

  calcLifterAngleTop = calcLifterAngleBottom = 0.0;
  lifterAngle = {0.0, 0.0};
  lifterTop = lifterBottom = 0;
  
  angularVelocity = {0.0, 0.0, 0.0, 0.0};
  currentEncoder = {0, 0, 0, 0};
  oldEncoder = {0, 0, 0, 0};
  diffEncoder = {0, 0, 0, 0};
  countEncoder = {0, 0, 0, 0};
  encoderData = {0, 0, 0, 0};

  isInitialize = false;
}

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
void SeedCommand::seedSetParam(const double wheelRadius,const double tread,const double wheelBase)
{
  //SEED-Noidのパラメータを設定する
  meca.setMobileRobotParam(wheelRadius, tread, wheelBase);
}

//=========================================================================
//接続開始関数
//SEED-Noidとの通信を開始する
//
//引数：
//port：接続されたポートの番号　例："/dev/ttyUSB0"
//baudrate：通信速度　デフォルト値：1000000
//
//返り値：
//なし
//=========================================================================
void SeedCommand::seedSerialOpen(const std::string portName, const int baudRate = 1000000)
{
  //シリアル通信を開始する
  if(sc.serialOpen(portName.c_str(),baudRate))
    {
      std::cout << "Connect!" << std::endl;
    }
  else
    {
      std::cout << "Connecr Error!" << std::endl;
    }
}

//=========================================================================
//接続終了関数
//SEED-Noidとの通信を終了する
//
//引数：
//なし
//
//返り値：
//true: 正常終了　false: 異常発生(表示されるエラー内容を参照)
//=========================================================================
void SeedCommand::seedSerialClose()
{
  //シリアル通信を終了する
  if(sc.serialClose())
    {
      std::cout << "Dis Connect!" << std::endl;
    }
  else
    {
      std::cout << "Dis Connece Error!" << std::endl;
    }
}

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
void SeedCommand::seedSendServo(unsigned char sendNo,unsigned short sendParam,unsigned char allMode = 1)
{
  checkSum = 0;
  //サーボモータすべてのON/OFFをする場合
  if(allMode)
    {
      //送信データサイズの指定
      dataLength = 68;
      mobileSendData.resize(dataLength);

      //送信データに値を格納
      mobileSendData[0] = 0xFD;
      mobileSendData[1] = 0xDF;
      mobileSendData[2] = 64;
      mobileSendData[3] = 0x21;
      mobileSendData[4] = 0x00;

      for(int i(5); i < 65; i+=2)
	{
	  mobileSendData[i] = 0x00;
	  mobileSendData[i+1] = sendParam;
	}

      mobileSendData[65] = 0x00;
      mobileSendData[66] = 0x00;
    }

  //1つのサーボモータのON/OFFをする場合
  else
    {
      //送信データサイズの指定
      dataLength = 8;
      mobileSendData.resize(dataLength);

      //送信データに値を格納
      mobileSendData[0] = 0xFD;
      mobileSendData[1] = 0xDF;
      mobileSendData[2] = 4;
      mobileSendData[3] = 0x21;
      mobileSendData[4] = sendNo;
      mobileSendData[5] = sendParam >> 8;
      mobileSendData[6] = sendParam;
    }
      
  //CheckSumの計算
  for(checkCount = 2;checkCount < dataLength-1;checkCount++)
    {
      checkSum += mobileSendData[checkCount];
    }
  mobileSendData[dataLength-1] = ~checkSum;

  /*
    for(int i(0);i < 68;i++)
    {
    std::cout << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(sendData[i]);
    }
    std::cout << std::endl;
  */  

  //データの送信
  sc.serialAsyncWrite(mobileSendData);
}

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
void SeedCommand::seedSendTruckSpeed(struct Velocity targetVelocity)
{
  //台車への速度入力から各ホイールの角速度を計算する
  meca.calcMecanumWheelKinematics(targetVelocity, angularVelocity);

  //送信データサイズの指定
  dataLength = 68;
  checkSum = 0;
  mobileSendData.resize(dataLength);

  //送信データに値を格納
  mobileSendData[0] = 0xFD;
  mobileSendData[1] = 0xDF;
  mobileSendData[2] = 64;
  mobileSendData[3] = 0x15;
  mobileSendData[4] = 0x00;

  for(int i(0);i < 4;i++)
    {
      mobileSendData[i+5] = 0x00;
    }

  /*[9],[10]:右前ホイール*/
  /*[11],[12]:右後ホイール*/
  /*[13],[14]:左前ホイール*/
  /*[15],[16]:左後ホイール*/
  mobileSendData[9] = static_cast<int>(-angularVelocity.rightFront) >> 8;
  mobileSendData[10] = static_cast<int>(-angularVelocity.rightFront);
  mobileSendData[11] = static_cast<int>(-angularVelocity.rightBack) >> 8;
  mobileSendData[12] = static_cast<int>(-angularVelocity.rightBack);
  mobileSendData[13] = static_cast<int>(angularVelocity.leftFront) >> 8;
  mobileSendData[14] = static_cast<int>(angularVelocity.leftFront);
  mobileSendData[15] = static_cast<int>(angularVelocity.leftBack) >> 8;
  mobileSendData[16] = static_cast<int>(angularVelocity.leftBack);

  for(unsigned int i(0);i < 50;i++)
    {
      mobileSendData[i+17] = 0x00;
    }

  //CheckSumの計算
  for(checkCount = 2;checkCount < dataLength-1;checkCount++)
    {
      checkSum += mobileSendData[checkCount];
    }
  mobileSendData[dataLength-1] = ~checkSum;

  /*
    for(int i(9);i < 17;i+=2)
    {
    printf("%d,%d 0x%02X%02X\n", i,i+1,sendData[i],sendData[i+1]);
    }
  */

  //データの送信
  sc.serialAsyncWrite(mobileSendData);
}

//=========================================================================
//オドメトリ計算関数
//SEED-Noidからエンコーダ値を取得し，オドメトリを計算する
//
//引数：
//odometryData：台車の位置・姿勢(ロボット座標系) 位置[m], 姿勢[rad]
//
//返り値：
//なし
//=========================================================================
bool SeedCommand::seedCalcOdometry(struct Pose &odometryData)
{
  //送信データサイズの指定
  checkSum = 0;
  dataLength = 6;
  mobileSendData.resize(dataLength);

  //送信データに値を格納
  mobileSendData[0] = 0xFD;
  mobileSendData[1] = 0xDF;
  mobileSendData[2] = 2;
  mobileSendData[3] = 0x41;
  mobileSendData[4] = 0x00;

  //CheckSumの計算
  for(checkCount = 2;checkCount < dataLength-1;checkCount++)
    {
      checkSum += mobileSendData[checkCount];
    }
  mobileSendData[dataLength-1] = ~checkSum;

  //受信したが読んでないデータ・書いたが送信していないデータをフラッシュ
  sc.flushSerialPort();
  //データの送信
  sc.serialAsyncWrite(mobileSendData);
  
  //データの受信
  sc.serialAsyncRead(mobileReceiveData,68,1);

  /*
  std::cout << "sendData:";
  for(int i(0);i < 6;++i)
    {
      std::cout << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(sendData[i]);
    }
  std::cout << std::endl;
  std::cout << "receiveData:";
  for(int i(0);i < 68;++i)
    {
      std::cout << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(receiveData[i]);
    }
  std::cout << std::endl;
  */

  //受信データがズレていないか確認
  if(mobileReceiveData[0] == 0xDF && (mobileReceiveData[3] == 0x15 || mobileReceiveData[3] == 0x41))
    {
      //Get encoder value of each wheels[deg]
      currentEncoder.rightFront = (static_cast<int>(mobileReceiveData[9] << 8) | (static_cast<int>(mobileReceiveData[10])));     //Right front wheel Hexadecimal angle data
      currentEncoder.rightBack = (static_cast<int>(mobileReceiveData[11] << 8) | (static_cast<int>(mobileReceiveData[12])));     //Right rear wheel Hexadecimal angle data
      currentEncoder.leftFront = (static_cast<int>(mobileReceiveData[13] << 8) | (static_cast<int>(mobileReceiveData[14])));     //Left front wheel Hexadecimal angle data
      currentEncoder.leftBack = (static_cast<int>(mobileReceiveData[15] << 8) | (static_cast<int>(mobileReceiveData[16])));     //Left rear wheel Hexadecimal angle data
    
      //エンコーダに値が残っている場合
      if(!isInitialize)
	{
	  oldEncoder = currentEncoder;
	  isInitialize = true;
	}
    }
  else
    {
      return false;
    }

  //Encoder difference calculation
  diffEncoder.rightFront = currentEncoder.rightFront - oldEncoder.rightFront;
  diffEncoder.rightBack = currentEncoder.rightBack - oldEncoder.rightBack;
  diffEncoder.leftFront = currentEncoder.leftFront - oldEncoder.leftFront;
  diffEncoder.leftBack = currentEncoder.leftBack - oldEncoder.leftBack;
    
  //Assignment of encoder value
  oldEncoder.rightFront = currentEncoder.rightFront;
  oldEncoder.rightBack = currentEncoder.rightBack;
  oldEncoder.leftFront = currentEncoder.leftFront;
  oldEncoder.leftBack = currentEncoder.leftBack;

  //エンコーダは27204まで行くとデータが0に戻ってしまうので，そのタイミングでカウンタを変化させる
  //Count encoder cycle(27204)
  //Right front wheel count
  if(diffEncoder.rightFront > 10000/*ENCODER_THRESHOLD*/)
    {
      countEncoder.rightFront --;
    }
  else if(diffEncoder.rightFront < -10000/*-ENCODER_THRESHOLD*/)
    {
      countEncoder.rightFront ++;
    }
  //Right rear wheel count
  if(diffEncoder.rightBack > 10000/*ENCODER_THRESHOLD*/)
    {
      countEncoder.rightBack --;
    }
  else if(diffEncoder.rightBack < -10000/*-ENCODER_THRESHOLD*/)
    {
      countEncoder.rightBack ++;
    }
  //Left front wheel count
  if(diffEncoder.leftFront > 10000/*ENCODER_THRESHOLD*/)
    {
      countEncoder.leftFront --; 
    }
  else if(diffEncoder.leftFront < -10000/*-ENCODER_THRESHOLD*/)
    {    
      countEncoder.leftFront ++;
    }
  //Left rear wheel count
  if(diffEncoder.leftBack > 10000/*ENCODER_THRESHOLD*/)
    {
      countEncoder.leftBack --;
    }
  else if(diffEncoder.leftBack < -10000/*-ENCODER_THRESHOLD*/)
    {
      countEncoder.leftBack ++;
    }
    
  //Calculate degrees of wheel rotation angle [deg]
  encoderData.rightFront = currentEncoder.rightFront + 27204 * countEncoder.rightFront;     //Right front wheel rotation angle data
  encoderData.rightBack = currentEncoder.rightBack + 27204 * countEncoder.rightBack;     //Right rear wheel roration angle data
  encoderData.leftFront = currentEncoder.leftFront + 27204 * countEncoder.leftFront;     //Left ftonr wheel rotation angle data
  encoderData.leftBack = currentEncoder.leftBack + 27204 * countEncoder.leftBack;     //Left rear wheel roration angle data
  
  //Adjustment of rotation direction
  encoderData.rightFront = - encoderData.rightFront;
  encoderData.rightBack = - encoderData.rightBack;

  //エンコーダ値からオドメトリを計算
  meca.calcMecanumWheelOdometry(encoderData, odometryData);

  return true;
}

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
bool SeedCommand::CheckTargetAngle(struct Lifter targetLifterAngle)
{
  //可動範囲内か確認
  if(targetLifterAngle.top < 0 || 90 < targetLifterAngle.top || targetLifterAngle.bottom < 0 || 90 < targetLifterAngle.bottom)
    {
      return false;
    }

  return true;
}

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
bool SeedCommand::CheckTargetPose(struct Pose targetLifterPose)
{
  //Determination of movable range of lifter
  //Lifter top
  if(targetLifterPose.z >= lifterLength)
    {
      if((pow((0.0 - targetLifterPose.x),2) + pow((lifterLength - targetLifterPose.z),2)) <= pow(lifterLength,2))
	{
	  return true;
	}
      
      else
	{
	  return false;
	}
    }
  
  //Lifter under
  else if(0 <= targetLifterPose.z && targetLifterPose.z < lifterLength)
    {
      //Front direction
      if(0 <= targetLifterPose.x && targetLifterPose.x <= lifterLength)
	{
	  if((pow((lifterLength - targetLifterPose.x),2) + pow((0.0 - targetLifterPose.z),2)) >= pow(lifterLength,2))
	    {
	      return true;
	    }
	  
	  else
	    {
	      return false;
	    }
	}
      
      //Back direction
      else if(targetLifterPose.x < 0 && -lifterLength <= targetLifterPose.x)
	{
	  if((pow((-lifterLength - targetLifterPose.x),2) + pow((0.0 - targetLifterPose.z),2)) >= pow(lifterLength,2))
	    {
	      return true;
	    }
	  
	  else
	    {
	      return false;
	    }
	}
      
      else
	{
	  return false;
	}
    }
  
  else
    {
      return false;
    }
}

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
void SeedCommand::seedMoveLifterForwardKinematics(struct Lifter targetLifterAngle,int time = 3000)
{
  //リフター可動範囲の確認
  if(!CheckTargetAngle(targetLifterAngle))
    {
      std::cout << "Out of calculation range" << std::endl;
    }
  else{
    //リフターの可動範囲を制限
    if(85 < targetLifterAngle.top && targetLifterAngle.top <= 90)
      {
	targetLifterAngle.top = 85;
      }

    if(85 < targetLifterAngle.bottom && targetLifterAngle.bottom <= 90)
      {
	targetLifterAngle.bottom = 85;
      }

    //リフターの角度から送信するデータの値を計算
    lifterTop = (int)((0.0000000000189750997846207 * std::pow(targetLifterAngle.top,6) - 0.00000000720603482440296 * std::pow(targetLifterAngle.top,5) + 0.00000121514687201341 * std::pow(targetLifterAngle.top,4) - 0.000131421951692801 * std::pow(targetLifterAngle.top,3) + 0.00697190814844362 * std::pow(targetLifterAngle.top,2) + 0.617198185427696 * targetLifterAngle.top - 0.00145630350050144) * 100);
    lifterBottom = (int)((0.0000000000189750997846207 * std::pow(targetLifterAngle.bottom,6) - 0.00000000720603482440296 * std::pow(targetLifterAngle.bottom,5) + 0.00000121514687201341 * std::pow(targetLifterAngle.bottom,4) - 0.000131421951692801 * std::pow(targetLifterAngle.bottom,3) + 0.00697190814844362 * std::pow(targetLifterAngle.bottom,2) + 0.617198185427696 * targetLifterAngle.bottom - 0.00145630350050144) * 100);

    //送信データサイズの指定
    dataLength = 68;
    lifterSendData.resize(dataLength);
    checkSum = 0;

    //送信データに値を格納
    lifterSendData[0] = 0xFD;
    lifterSendData[1] = 0xDF;
    lifterSendData[2] = 64;
    lifterSendData[3] = 0x14;
    lifterSendData[4] = 0x00;
    lifterSendData[5] = static_cast<int>(lifterBottom) >> 8;
    lifterSendData[6] = static_cast<int>(lifterBottom);
    lifterSendData[7] = static_cast<int>(lifterTop) >> 8;
    lifterSendData[8] = static_cast<int>(lifterTop);

    for(int i(0);i < 56;i++)
      {
	lifterSendData[i+9] = 0x00;
      }

    lifterSendData[65] = static_cast<int>(time / 10) >> 8;
    lifterSendData[66] = static_cast<int>(time / 10);

    //CheckSumの計算
    for(checkCount = 2;checkCount < dataLength-1;checkCount++)
      {
	checkSum += lifterSendData[checkCount];
      }
    lifterSendData[dataLength-1] = ~checkSum;

    //データの送信
    sc.serialAsyncWrite(lifterSendData);
  }
}

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
void SeedCommand::seedMoveLifterInverseKinematics(struct Pose targetLifterPose,int time = 3000)
{
  //リフター可動範囲の確認
  if(!CheckTargetPose(targetLifterPose))
    {
      std::cout << "Out of calculation range" << std::endl;
    }
  else
    {
      //各リフターの目標角度[rad]の計算
      calcLifterAngleTop = std::acos((std::pow(targetLifterPose.x,2) + std::pow(targetLifterPose.z,2) - 2 * std::pow(lifterLength,2)) / (2 * std::pow(lifterLength,2)));

      if((calcLifterAngleTop * 180 / M_PI) > 0)
	{
	  calcLifterAngleTop = -calcLifterAngleTop;
	}

      calcLifterAngleBottom = std::asin(-(((targetLifterPose.x * lifterLength * std::sin(calcLifterAngleTop)) - (targetLifterPose.z * (lifterLength + lifterLength * std::cos(calcLifterAngleTop)))) / (std::pow((lifterLength + lifterLength * std::cos(calcLifterAngleTop)),2) + std::pow(lifterLength,2) * std::pow(std::sin(calcLifterAngleTop),2))));

      //Change Radian to Degree
      calcLifterAngleTop = (calcLifterAngleTop * 180 / M_PI);
      calcLifterAngleBottom = (calcLifterAngleBottom * 180 / M_PI);

      if(calcLifterAngleBottom < 90 || 180 < calcLifterAngleBottom)
	{
	  calcLifterAngleBottom = 180 - calcLifterAngleBottom;
	}
  
      lifterAngle.bottom = calcLifterAngleBottom - 90;
      lifterAngle.top = 0 - (calcLifterAngleTop + (calcLifterAngleBottom - 90));

      //リフターの可動範囲を制限
      if(85 < lifterAngle.top && lifterAngle.top <= 90)
	{
	  lifterAngle.top = 85;
	}

      if(85 < lifterAngle.bottom && lifterAngle.bottom <= 90)
	{
	  lifterAngle.bottom = 85;
	}
      
      //リフターの角度から送信するデータの値を計算
      lifterTop = (int)((0.0000000000189750997846207 * std::pow(lifterAngle.top,6) - 0.00000000720603482440296 * std::pow(lifterAngle.top,5) + 0.00000121514687201341 * std::pow(lifterAngle.top,4) - 0.000131421951692801 * std::pow(lifterAngle.top,3) + 0.00697190814844362 * std::pow(lifterAngle.top,2) + 0.617198185427696 * lifterAngle.top - 0.00145630350050144) * 100);
      lifterBottom = (int)((0.0000000000189750997846207 * std::pow(lifterAngle.bottom,6) - 0.00000000720603482440296 * std::pow(lifterAngle.bottom,5) + 0.00000121514687201341 * std::pow(lifterAngle.bottom,4) - 0.000131421951692801 * std::pow(lifterAngle.bottom,3) + 0.00697190814844362 * std::pow(lifterAngle.bottom,2) + 0.617198185427696 * lifterAngle.bottom - 0.00145630350050144) * 100);

      //送信データサイズの指定
      dataLength = 68;
      lifterSendData.resize(dataLength);
      checkSum = 0;

      //送信データに値を格納
      lifterSendData[0] = 0xFD;
      lifterSendData[1] = 0xDF;
      lifterSendData[2] = 64;
      lifterSendData[3] = 0x14;
      lifterSendData[4] = 0x00;
      lifterSendData[5] = static_cast<int>(lifterBottom) >> 8;
      lifterSendData[6] = static_cast<int>(lifterBottom);
      lifterSendData[7] = static_cast<int>(lifterTop) >> 8;
      lifterSendData[8] = static_cast<int>(lifterTop);

      for(int i(0);i < 56;i++)
	{
	  lifterSendData[i+9] = 0x00;
	}

      lifterSendData[65] = static_cast<int>(time / 10) >> 8;
      lifterSendData[66] = static_cast<int>(time / 10);

      //CheckSumの計算
      for(checkCount = 2;checkCount < dataLength-1;checkCount++)
	{
	  checkSum += lifterSendData[checkCount];
	}
      lifterSendData[dataLength-1] = ~checkSum;

      //データの送信
      sc.serialAsyncWrite(lifterSendData);
    }
}

//=========================================================================
//リフター角度取得関数
//SEED-Noidのリフターの現在の角度を取得する
//
//引数：
//&currentLifterAngle：各リフターの現在角度[deg]
//
//返り値：
//なし
//=========================================================================
bool SeedCommand::seedGetLifterAngle(struct Lifter &currentLifterAngle)
{
  //送信データサイズの指定
  checkSum = 0;
  dataLength = 6;
  lifterSendData.resize(dataLength);

  //送信データに値を格納
  lifterSendData[0] = 0xFD;
  lifterSendData[1] = 0xDF;
  lifterSendData[2] = 2;
  lifterSendData[3] = 0x41;
  lifterSendData[4] = 0x00;

  //CheckSumの計算
  for(checkCount = 2;checkCount < dataLength-1;checkCount++)
    {
      checkSum += lifterSendData[checkCount];
    }
  lifterSendData[dataLength-1] = ~checkSum;

  //受信したが読んでないデータ・書いたが送信していないデータをフラッシュ
  sc.flushSerialPort();
  //データの送信
  sc.serialAsyncWrite(lifterSendData);

  //データの受信
  sc.serialAsyncRead(lifterReceiveData,68,1);

  //受信データがズレていないか確認
  if(lifterReceiveData[0] == 0xDF && lifterReceiveData[3] == 0x41)
    {
      //Get encoder value of each lifters
      //Lifter Top Hexadecimal angle data [deg]
      lifterBottom = (static_cast<int>(lifterReceiveData[5] << 8) | (static_cast<int>(lifterReceiveData[6])));
      //Lifter Bottom Hexadecimal angle data [deg]
      lifterTop = (static_cast<int>(lifterReceiveData[7] << 8) | (static_cast<int>(lifterReceiveData[8])));
    }
  else
    {
      return false;
    }
  //0が65535になる場合
  if(lifterTop > 60000)
    {
      lifterTop = 0;
    }
  if(lifterBottom > 60000)
    {
      lifterBottom = 0;
    }

  //リフターの現在の角度を計算
  currentLifterAngle.top = -0.000000000320705477365596 * std::pow((lifterTop/100),6) + 0.000000101518057737948 * std::pow((lifterTop/100),5) - 0.0000109692918783821 * std::pow((lifterTop/100),4) + 0.000649565749313297 * std::pow((lifterTop/100),3) - 0.0205117592049646 * std::pow((lifterTop/100),2) + 1.59004309387819 * (lifterTop/100) + 0.025539887312334;
  currentLifterAngle.bottom = -0.000000000320705477365596 * std::pow((lifterBottom/100),6) + 0.000000101518057737948 * std::pow((lifterBottom/100),5) - 0.0000109692918783821 * std::pow((lifterBottom/100),4) + 0.000649565749313297 * std::pow((lifterBottom/100),3) - 0.0205117592049646 * std::pow((lifterBottom/100),2) + 1.59004309387819 * (lifterBottom/100) + 0.025539887312334;

  //std::cout << "currentLifterAngle.top = " << currentLifterAngle.top << std::endl;
  //std::cout << "currentLifterAngle.bottom = " << currentLifterAngle.bottom << std::endl;
  return true;
}

//=========================================================================
//リフター姿勢取得関数
//SEED-Noidのリフターの現在の姿勢を取得する
//
//引数：
//&currentLifterPose：リフターの姿勢[m]
//
//返り値：
//なし
//=========================================================================
bool SeedCommand::seedGetLifterPose(struct Pose &currentLifterPose)
{
  //リフターの現在の角度を計算
  if(!seedGetLifterAngle(lifterAngle))
    {
      return false;
    }
  else
    {
      //Change Degree to Radian
      lifterAngle.top = lifterAngle.top * M_PI / 180;
      lifterAngle.bottom = lifterAngle.bottom * M_PI / 180;

      //リフターの現在の姿勢を計算
      currentLifterPose.x = lifterLength * sin(lifterAngle.top) - lifterLength * sin(lifterAngle.bottom);
      currentLifterPose.y = 0;
      currentLifterPose.z = lifterLength * cos(lifterAngle.top) + lifterLength * cos(lifterAngle.bottom);

      return true;
    }
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
void SeedCommand::resetParam()
{
  //変数内のデータをリセットする
  isInitialize = false;
  
  angularVelocity = {0,0,0,0};
  currentEncoder = {0,0,0,0};
  oldEncoder = {0,0,0,0};
  diffEncoder = {0,0,0,0};
  countEncoder = {0,0,0,0};
  encoderData = {0,0,0,0};

  meca.resetParam();
}
