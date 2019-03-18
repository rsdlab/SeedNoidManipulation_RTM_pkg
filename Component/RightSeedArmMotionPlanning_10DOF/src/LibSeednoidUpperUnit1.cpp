
#include "LibSeednoidUpperUnit1.h"

//グローバル宣言
#ifdef _USE_SERIALCOM_BOOST
SerialCom usc;
#endif
SeedUpper noid;
Redundancy redun;

SeedUpper::SeedUpper()
{
  for (int i = 0; i<SEED_FREEDOM; i++){
	  noidJointPos[i] = 32767;
	  ReadAngle[i] = 0;
  }
  SeedArmJointLimit[0].Upper = Angle1_LimitMax;
  SeedArmJointLimit[0].Lower = Angle1_LimitMin;
  SeedArmJointLimit[1].Upper = Angle2_LimitMax;
  SeedArmJointLimit[1].Lower = Angle2_LimitMin;
  SeedArmJointLimit[2].Upper = Angle3_LimitMax;
  SeedArmJointLimit[2].Lower = Angle3_LimitMin;
  SeedArmJointLimit[3].Upper = Angle4_LimitMax;
  SeedArmJointLimit[3].Lower = Angle4_LimitMin;
  SeedArmJointLimit[4].Upper = Angle5_LimitMax;
  SeedArmJointLimit[4].Lower = Angle5_LimitMin;
  SeedArmJointLimit[5].Upper = Angle6_LimitMax;
  SeedArmJointLimit[5].Lower = Angle6_LimitMin;
  SeedArmJointLimit[6].Upper = Angle7_LimitMax;
  SeedArmJointLimit[6].Lower = Angle7_LimitMin;
  SeedNeckJointLimit[0].Upper = NeckYaw_LimitMax;
  SeedNeckJointLimit[0].Lower = NeckYaw_LimitMin;
  SeedNeckJointLimit[1].Upper = NeckPitch_LimitMax;
  SeedNeckJointLimit[1].Lower = NeckPitch_LimitMin;
  SeedNeckJointLimit[2].Upper = NeckRoll_LimitMax;
  SeedNeckJointLimit[2].Lower = NeckRoll_LimitMin;
  SeedWaistJointLimit[0].Upper = WaistYaw_LimitMax;
  SeedWaistJointLimit[0].Lower = WaistYaw_LimitMin;
  SeedWaistJointLimit[1].Upper = WaistPitch_LimitMax;
  SeedWaistJointLimit[1].Lower = WaistPitch_LimitMin;
  SeedWaistJointLimit[2].Upper = WaistRoll_LimitMax;
  SeedWaistJointLimit[2].Lower = WaistRoll_LimitMin;
  
  for(int j=0;j<7;j++){
    if(j==3)
      RightArmSetJointPos[j] = 180;
    else
      RightArmSetJointPos[j] = 0;
  }
  for(int k=0;k<7;k++){
    if(k==3)
      LeftArmSetJointPos[k] = 180;
    else
      LeftArmSetJointPos[k] = 0;
  }
  
  NeckSetJointPos[0] = 0;
  NeckSetJointPos[1] = 0;
  NeckSetJointPos[2] = 0;
  WaistSetJointPos[0] = 0;
  WaistSetJointPos[1] = 0;
  WaistSetJointPos[2] = 0;

  NeedCancelScriptRightHand = 0;
  NeedCancelScriptLeftHand = 0;

#ifndef _USE_SERIALCOM_BOOST
  fd = 0;
  bzero(&newtio, sizeof(newtio)); //initialize
#endif
}

/************************************************
	int OpenSerialPort(const char *SERIAL_PORT)

	概要：シリアル通信を開始する

	引数：const char *SERIAL_PORT・・・ポート名
	
	戻り値：なし

*************************************************/
int SeedUpper::OpenSerialPort(const char *SERIAL_PORT)
{
#ifdef _USE_SERIALCOM_BOOST
  dev = (char*)SERIAL_PORT;
  if(usc.serialOpen(dev,1000000))
    {
      std::cout<<"Open COM Port:"<<dev<<std::endl;
      return 0;
    }
  else
    {
      std::cout<<"Cannot Open expected COM Port!"<<std::endl;
      return -1;
    }
#else
  dev = (char*)SERIAL_PORT;
  fd = open(dev, O_RDWR | O_NOCTTY );
  if(fd < 0){
    std::cout<<"Cannot Open expected COM Port!"<<std::endl;
    return -1;
  }
  else{
    std::cout<<"Open COM Port:"<<dev<<std::endl;
  }
  
  newtio.c_cflag = B1000000 | CS8 | CREAD | CLOCAL;
  
  newtio.c_cc[VTIME] = 10;
  newtio.c_cc[VMIN] = 10;
  newtio.c_lflag = 0;
  newtio.c_iflag = IGNPAR;
  newtio.c_oflag = 0;
  
  tcflush(fd, TCIOFLUSH);
  tcsetattr(fd, TCSANOW, &newtio);
  
  return 0;

#endif
}

 /************************************************

	int CloseSerialPort()

	概要：シリアル通信を終了する

	引数：なし
	
	戻り値：なし

*************************************************/
void SeedUpper::CloseSerialPort()
{
#ifdef _USE_SERIALCOM_BOOST
    if(usc.serialClose())
    {
      std::cout << "Close COM Port:"<< dev << std::endl;
    }
  else
    {
      std::cout << "Dis Connece Error!" << std::endl;
    }
#else
  std::cout<<"Close COM Port:"<<dev<<std::endl;
  close(fd);
#endif
}

/************************************************

	void serialWrite(uchar *buf, int length)

	概要：シリアル通信でデータを送信する

	引数：
              *buf・・・送るデータの配列
              length・・・データの長さ
	
	戻り値：なし

*************************************************/
void SeedUpper::serialWrite(std::vector<unsigned char> sendData)
{
#ifdef _USE_SERIALCOM_BOOST
  //usc.flushSerialPort();
  usc.serialAsyncWrite(sendData);
  //usc.serialAsyncWrite(sendData);
#else
  int length;
  length = sendData.size();
  uchar buf[length];
  for(int i=0;i<length;i++)
    {
      buf[i] = sendData[i];
    }
  write(fd, buf, length);
  tcflush(fd, TCOFLUSH);
#endif
}


/************************************************

	void serialRead(uchar *recv)

	概要：シリアル通信でデータを送信する

	引数：
              *recv・・・受け取るデータの配列
            
	
	戻り値：なし

*************************************************/
void SeedUpper::serialRead(int length)
{
#ifdef _USE_SERIALCOM_BOOST
  receiveData.resize(length);
  usc.serialAsyncRead(receiveData,length);
  //usc.serialRead(receiveData,length);
#else
  receiveData.resize(length);
  uchar buf[length];
  read(fd, buf, length);
  for(int i=0;i<length;i++)
    {
      receiveData[i] = buf[i];
    }
#endif
  //for(int h=0;h<68;h++){
  //  printf("receiveData[%d] = %x\n",h,receiveData[h]);
  //}
}

/************************************************

	void serialFlush()

	概要：シリアル通信でデータを送信する

	引数：
              *recv・・・受け取るデータの配列
            
	
	戻り値：なし

*************************************************/
void SeedUpper::serialFlush()
{
#ifdef _USE_SERIALCOM_BOOST
  usc.flushSerialPort();
  //std::cout << "flushSerialPort()" << std::endl;
#else
  tcflush(fd, TCOFLUSH);
  //std::cout << "flushSerialPort()" << std::endl;
#endif
}

/************************************************

	char calcCheckSum(char *buf, int Datasize)

	概要：チェックサムを計算する

	引数：
              *buf・・・送るデータの配列
              Datasize・・・データの数
	
	戻り値：計算結果

*************************************************/
uchar SeedUpper::calcCheckSum(std::vector<unsigned char> sendData, int dataLength)
{
  int checkSum = 0;
  int checkCount = 0;
  for(checkCount = 2;checkCount < dataLength-1;checkCount++)
    {
      checkSum += sendData[checkCount];
    }
  return 0xff &    (~checkSum);
}


/************************************************

       void ReadServoAngle(int id, double ReadAngle)

       概要：サーボのAngle値を受け取る

       引数：
             id・・・サーボのID

       戻り値：なし

*************************************************/
int SeedUpper::ReadServoAngle(double ReadServoAngle[])
{
  int i = 5;  //skip4byte
  int j = 0;
  //uchar buf[6] = {0};
  //uchar recv[68] = {0};
  int dataLength = 6;
  readSendData.resize(dataLength);

  uchar Hex_high;
  uchar Hex_low;
  readSendData[0] = 0xfd;
  readSendData[1] = 0xdf;
  readSendData[2] = 0x02;
  readSendData[3] = 0x41;
  readSendData[4] = 0x00;//全軸指令
  readSendData[5] = calcCheckSum(readSendData ,dataLength);

  for(int k=0;k<10;k++)
    {
      serialFlush();
      serialWrite(readSendData);//,sizeof(buf));
      usleep(1000*10);
      serialRead(68);
      
      if(receiveData[0] == 0xDF && receiveData[1] == 0xFD)
	{
	  //for(int h=0;h<6;h++){
	  //  printf("readSendData[%d] = %x\n",h,readSendData[h]);
	  //}
	  if(receiveData[3] == 0x14)
	    {
#ifdef _USE_SERIALCOM_BOOST
	      usc.flushSerialPort();
	      //std::cout << "flushSerialPort()" << std::endl;
#else
	      tcflush(fd, TCOFLUSH);
	      //std::cout << "flushSerialPort()" << std::endl;
#endif
	      continue;
	    }
	  
	  for(i=5;i<65;i=i+2)
	    {
	      Hex_high = receiveData[i];
	      Hex_low = receiveData[i+1];
	      ReadServoAngle[j] = (Hex_high<<8)|(Hex_low);
	      j++;
	    }
	  //for(int h=0;h<68;h++){
	  //  printf("recv[%d] = %x\n",h,recv[h]);
	  //}
	  for(int l=0;l<30;l++){
	    if(ReadServoAngle[l]>50000)//noidJointPosがマイナスだが下位8ビットしかreadできないため
	      {
		ReadServoAngle[l] = ReadServoAngle[l]-65536;
	      }
	    //printf("ReadServoAngle[%d] = %f\n",l,ReadServoAngle[l]);
	  }
	  return 0;
	}
      else
	{
	  //std::cout << "receiveData[0] == 0xDFではない" << std::endl;
#ifdef _USE_SERIALCOM_BOOST
	      usc.flushSerialPort();
	      //std::cout << "flushSerialPort()" << std::endl;
#else
	      tcflush(fd, TCOFLUSH);
	      //std::cout << "flushSerialPort()" << std::endl;
#endif
	  usleep(1000*10);
	}
    }
  std::cout << "10回連続でDFFD読み取り失敗" << std::endl;
  return -1;
  
}

/************************************************

       void ReadServoAngleAndSetNowPos()

       概要：サーボのAngle値を受け取り，変数に格納する

       引数：なし

       戻り値：なし

*************************************************/
int SeedUpper::ReadServoAngleAndSetNowAngle()
{
  int i = 5;  //skip4byte
  int j = 0;
  int dataLength = 6;
  readSendData.resize(dataLength);

  uchar Hex_high;
  uchar Hex_low;
  readSendData[0] = 0xfd;
  readSendData[1] = 0xdf;
  readSendData[2] = 0x02;
  readSendData[3] = 0x41;
  readSendData[4] = 0x00;//全軸指令
  readSendData[5] = calcCheckSum(readSendData ,dataLength);

  for(int k=0;k<10;k++)
    {
      //for(int h=0;h<6;h++){
      //  printf("readSendData[%d] = %x\n",h,readSendData[h]);
      //}
      serialFlush();
      serialWrite(readSendData);
      usleep(10000);
      serialRead(68);
      if(receiveData[0] == 0xDF && receiveData[1] == 0xFD)
	{
	  if(receiveData[3] == 0x14)
	    {
#ifdef _USE_SERIALCOM_BOOST
	      usc.flushSerialPort();
	      //std::cout << "flushSerialPort()" << std::endl;
#else
	      tcflush(fd, TCOFLUSH);
	      //std::cout << "flushSerialPort()" << std::endl;
#endif
	      continue;
	    }
		  
	  for(i=5;i<65;i=i+2)
	    {
	      Hex_high = receiveData[i];
	      Hex_low = receiveData[i+1];
	      NowAngle[j] = (Hex_high<<8)|(Hex_low);
	      j++;
	    }
	  //for(int h=0;h<68;h++){
	  //  printf("recv[%d] = %x\n",h,recv[h]);
	  //}
	  for(int l=0;l<30;l++){
	    if(NowAngle[l]>50000)//noidJointPosがマイナスだが下位8ビットしかreadできないため
	      {
		NowAngle[l] = NowAngle[l]-65536;
	      }
	    //printf("NowAngle[%d] = %f\n",l,NowAngle[l]);
	  }
	  return 0;
	}
      else
	{
#ifdef _USE_SERIALCOM_BOOST
	  usc.flushSerialPort();
	  //std::cout << "flushSerialPort()" << std::endl;
#else
	  tcflush(fd, TCOFLUSH);
	  //std::cout << "flushSerialPort()" << std::endl;
#endif
	  usleep(1000*10);
	}
    }
  std::cout << "10回連続でDFFD読み取り失敗" << std::endl;
  return -1;

}

/************************************************

      void SeedAction()

      概要：Seednoid全身の関節を動作させる

      引数：なし

      戻り値：なし

*************************************************/
void SeedUpper::SeedAction(int msectime)
{
  int i = 5;  //skip4byte
  int j = 0;
  int dataLength = 68;
  actionSendData.resize(dataLength);
  int movetime;
  movetime = msectime / 10;
  actionSendData[0] = 0xfd;
  actionSendData[1] = 0xdf;
  actionSendData[2] = 0x40;
  actionSendData[3] = 0x14;
  actionSendData[4] = 0x00;
  for(i=5;i<65;i=i+2)
    {
      actionSendData[i] = (noidJointPos[j]>>8) & 0xff;
      actionSendData[i+1] = (noidJointPos[j]) & 0xff;
      j++;
    }
  actionSendData[65] = (movetime>>8) & 0xff;
  actionSendData[66] = (movetime) & 0xff;//動作時間
  actionSendData[67] = calcCheckSum(actionSendData, dataLength);

  
  //for(int h=0;h<68;h++){
  //  printf("actionSendData[%d] = %x\n",h,actionSendData[h]);
  //}
  //usc.flushSerialPort();
  serialWrite(actionSendData);
  usleep(800*10);
  serialRead(68);
  
}

/************************************************

	void initPosition()

	概要：全身を初期位置に移動する

	引数：なし
	
	戻り値：なし

*************************************************/
void SeedUpper::initPosition()
{
  for (int k = 0; k<SEED_FREEDOM; k++){
    noidJointPos[k] = 0;
    if(k==6)
      {
	noidJointPos[k] = 42.4260 * 100;//180°　右肘ピッチ
      }
    if(k==11)
      {
	noidJointPos[k] = 32767;//0x7fff RightHand
      }
    if(k==21)
      {
	noidJointPos[k] = 42.4260 * 100;//180° 左肘ピッチ
      }
    if(k==26)
      {
	noidJointPos[k] = 32767;//0x7fff LeftHand
      }
  }
  std::cout << "init position" << std::endl;
}

/************************************************

      void ServoOnOff(int torque)

      概要：Seednoid全身のサーボONOFFさせる

      引数：
            int truque・・・トルク(1…ON,0…OFF)

      戻り値：なし

*************************************************/
void SeedUpper::ServoOnOff(int torque)
{
  std::vector<unsigned char> sendData;
  int i = 5;  //skip4byte
  int dataLength = 68;
  sendData.resize(dataLength);
  sendData[0] = 0xfd;
  sendData[1] = 0xdf;
  sendData[2] = 0x40;
  sendData[3] = 0x21;
  sendData[4] = 0x00;
  for(i=5;i<65;i=i+2)
    {
      sendData[i] = 0x00;
      sendData[i+1] = torque & 0xff;
    }
  sendData[65] = 0x00;
  sendData[66] = 0x00;
  sendData[67] = calcCheckSum(sendData, dataLength);
  
  
  //for(int j=0;j<68;j++)
  //  {
  //    printf("byte:%d  ",j);
  //    printf("buf[%d] = %x\n",j,sendData[j]);
  //  }
  
    
  serialWrite(sendData); 
  

}


/************************************************

      void RightArmServoOnOff(int torque)

      概要：Seednoid右腕のサーボONOFFさせる

      引数：
            int truque・・・トルク(1…ON,0…OFF)

      戻り値：なし

*************************************************/
void SeedUpper::RightArmServoOnOff(int torque)
{
  std::vector<unsigned char> sendData;
  
  int dataLength = 8;

  for(int ID=4; ID<11; ID++)
  {
  
  sendData.resize(dataLength);

  sendData[0] = 0xfd;
  sendData[1] = 0xdf;
  sendData[2] = 0x04;
  sendData[3] = 0x21;
  sendData[4] = ID & 0xff;
  sendData[5] = 0x00;
  sendData[6] = torque & 0xff;
  sendData[7] = calcCheckSum(sendData, dataLength);

  serialWrite(sendData);

  }

  //right wrist yaw ID=13
  
  sendData.resize(dataLength);

  sendData[0] = 0xfd;
  sendData[1] = 0xdf;
  sendData[2] = 0x04;
  sendData[3] = 0x21;
  sendData[4] = 13 & 0xff;
  sendData[5] = 0x00;
  sendData[6] = torque & 0xff;
  sendData[7] = calcCheckSum(sendData, dataLength);

  serialWrite(sendData);
 
}

/************************************************

      void RightGripperServoOnOff(int torque)

      概要：Seednoid右ハンドのサーボONOFFさせる

      引数：
            int truque・・・トルク(1…ON,0…OFF)

      戻り値：なし

*************************************************/
void SeedUpper::RightGripperServoOnOff(int torque)
{
  std::vector<unsigned char> sendData;
  
  int dataLength = 8;

  sendData.resize(dataLength);

  sendData[0] = 0xfd;
  sendData[1] = 0xdf;
  sendData[2] = 0x04;
  sendData[3] = 0x21;
  sendData[4] = 12 & 0xff;
  sendData[5] = 0x00;
  sendData[6] = torque & 0xff;
  sendData[7] = calcCheckSum(sendData, dataLength);

  serialWrite(sendData);
 
}

/************************************************

      void LeftArmServoOnOff(int torque)

      概要：Seednoid左腕のサーボONOFFさせる

      引数：
            int truque・・・トルク(1…ON,0…OFF)

      戻り値：なし

*************************************************/
void SeedUpper::LeftArmServoOnOff(int torque)
{
  std::vector<unsigned char> sendData;
  
  int dataLength = 8;

  for(int ID=19; ID<26; ID++)
  {
  
  sendData.resize(dataLength);

  sendData[0] = 0xfd;
  sendData[1] = 0xdf;
  sendData[2] = 0x04;
  sendData[3] = 0x21;
  sendData[4] = ID & 0xff;
  sendData[5] = 0x00;
  sendData[6] = torque & 0xff;
  sendData[7] = calcCheckSum(sendData, dataLength);

  serialWrite(sendData);

  }


  //left wrist yaw ID=28
  sendData.resize(dataLength);

  sendData[0] = 0xfd;
  sendData[1] = 0xdf;
  sendData[2] = 0x04;
  sendData[3] = 0x21;
  sendData[4] = 28 & 0xff;
  sendData[5] = 0x00;
  sendData[6] = torque & 0xff;
  sendData[7] = calcCheckSum(sendData, dataLength);

  serialWrite(sendData);
  
}

/************************************************

      void LeftGripperServoOnOff(int torque)

      概要：Seednoid左ハンドのサーボONOFFさせる

      引数：
            int truque・・・トルク(1…ON,0…OFF)

      戻り値：なし

*************************************************/

void SeedUpper::LeftGripperServoOnOff(int torque)
{
  std::vector<unsigned char> sendData;
  
  int dataLength = 8;

  sendData.resize(dataLength);

  sendData[0] = 0xfd;
  sendData[1] = 0xdf;
  sendData[2] = 0x04;
  sendData[3] = 0x21;
  sendData[4] = 27 & 0xff;
  sendData[5] = 0x00;
  sendData[6] = torque & 0xff;
  sendData[7] = calcCheckSum(sendData, dataLength);

  serialWrite(sendData);
 
}


/************************************************

      int setRightJointAngle(double JointPos[])

      概要：関節角度を入力するとSeednoid用の値に変換してnoidJointPos[]に書き込む(右腕のみ)

      引数：
            double JointPos[]・・・関節角度
                       JointPos[0]:肩ピッチ
                       JointPos[1]:肩ロール
                       JointPos[2]:肘ヨー
                       JointPos[3]:肘ピッチ
                       JointPos[4]:手首ヨー
                       JointPos[5]:手首ピッチ
                       JointPos[6]:手首ロール
      戻り値：なし

*************************************************/
int SeedUpper::setRightJointAngle(double JointPos[])
{
  //回転軸は指令値＝角度[deg]*100　，　直動軸は指令値＝ストローク100
  //JointPos[5]を手首ピッチ、JointPos[6]を手首ロールとする
  //ikfastで解いているモデルではJoint6がピッチ方向、Joint7がロール方向
  double right_tekubi_pitch;
  double right_tekubi_roll;

  //可動範囲の確認
  for(int i=0;i<ARM_FREEDOM;i++){
    if(JointPos[i]>SeedArmJointLimit[i].Upper||JointPos[i]<SeedArmJointLimit[i].Lower){
      std::cout << "ERROR : アーム可動範囲外の値が入力されました" << std::endl;     
      return -1;
    }
  }

  for(int j=0;j<ARM_FREEDOM;j++){
    RightArmSetJointPos[j] = JointPos[j];
  }

  right_tekubi_pitch = 0;//0.0000000000119321033088815*pow(JointPos[5], 6) - 0.00000000122667833182821*pow(JointPos[5], 5) + 0.0000000979913022045031*pow(JointPos[5], 4) - 0.0000139362174275126*pow(JointPos[5], 3) - 0.00055892898307397*pow(JointPos[5], 2) + 0.381998345402461*JointPos[5] - 0.000232762524552399; 
  
  right_tekubi_roll = -0.00000000000242706361579019*pow(JointPos[5], 6) - 0.000000000150602156255316*pow(JointPos[5], 5) + 0.0000000441727505516505*pow(JointPos[5], 4) - 0.00000506344248396719*pow(JointPos[5], 3) - 0.000440082138183015*pow(JointPos[5], 2) + 0.164385338238193*JointPos[5] + 0.000065167914236719;
  
  //右腕
  //肩ピッチ 
  noidJointPos[3] = (int)((-0.0000000000933971256927911*pow(JointPos[0], 6) + 0.0000000369034355317591*pow(JointPos[0], 5) - 0.00000574010042392163*pow(JointPos[0], 4) + 0.000374322804691228*pow(JointPos[0], 3) - 0.00458523350688013*pow(JointPos[0], 2) - 0.813300679027264*JointPos[0] - 0.210097776915891) * 100);
  //肩ロール
  noidJointPos[4] = (int)((-0.00000000000144055370388495*pow(JointPos[1], 6) + 0.000000000182601565812401*pow(JointPos[1], 5) + 0.000000119733377434983*pow(JointPos[1], 4) - 0.0000496157543636855*pow(JointPos[1], 3) + 0.00443296595449283*pow(JointPos[1], 2) + 0.461225592698611*JointPos[1] + 0.0000210183716262691) * 100);
  //肘ヨー
  noidJointPos[5] = (int)(JointPos[2]*100);
  //肘ピッチ
  noidJointPos[6] = (int)((0.00000000000049111019804115*pow(JointPos[3], 6) - 0.000000000390702276724364*pow(JointPos[3], 5) + 0.000000130488756156302*pow(JointPos[3], 4) - 0.0000234826685847622*pow(JointPos[3], 3) + 0.00161963481365035*pow(JointPos[3], 2) + 0.261403325221181*JointPos[3] - 42.4326561880471) * 100);
  //手首ヨー
  noidJointPos[7] = (int)(JointPos[4]*100);
  //手首ピッチ＆ロール
  noidJointPos[8] = (int)((right_tekubi_roll + right_tekubi_pitch) * 100);
  noidJointPos[9] = (int)((right_tekubi_roll - right_tekubi_pitch) * 100);
  noidJointPos[12] = (int)(JointPos[6]*100);
  //printf("JointPos[0] = %f[°]\n", JointPos[0]);
  //printf("JointPos[1] = %f[°]\n", JointPos[1]);
  //printf("JointPos[2] = %f[°]\n", JointPos[2]);
  //printf("JointPos[3] = %f[°]\n", JointPos[3]);
  //printf("JointPos[4] = %f[°]\n", JointPos[4]);
  //printf("JointPos[5] = %f[°]\n", JointPos[5]);
  //printf("JointPos[6] = %f[°]\n", JointPos[6]);
  //printf("noidJointPos[3] = %d\n", noidJointPos[3]);
  //printf("noidJointPos[4] = %d\n", noidJointPos[4]);
  //printf("noidJointPos[5] = %d\n", noidJointPos[5]);
  //printf("noidJointPos[6] = %d\n", noidJointPos[6]);
  //printf("noidJointPos[7] = %d\n", noidJointPos[7]);
  //printf("noidJointPos[8] = %d\n", noidJointPos[8]);
  //printf("noidJointPos[9] = %d\n", noidJointPos[9]);
  
  return 0;
}


/************************************************

      int setLeftJointAngle(double JointPos[])

      概要：関節角度を入力するとSeednoid用の値に変換してnoidJointPos[]に書き込む(左腕のみ)

      引数：
            double JointPos[]・・・関節角度
                       JointPos[0]:肩ピッチ
                       JointPos[1]:肩ロール
                       JointPos[2]:肘ヨー
                       JointPos[3]:肘ピッチ
                       JointPos[4]:手首ヨー
                       JointPos[5]:手首ピッチ
                       JointPos[6]:手首ロール
      戻り値：なし

*************************************************/
int SeedUpper::setLeftJointAngle(double JointPos[])
{
  //回転軸は指令値＝角度[deg]*100　，　直動軸は指令値＝ストローク100
  //JointPos[5]を手首ピッチ、JointPos[6]を手首ロールとする
  //ikfastで解いているモデルではJoint6がピッチ方向、Joint7がロール方向
  double left_tekubi_pitch;
  double left_tekubi_roll;

  //可動範囲の確認
  for(int i=0;i<ARM_FREEDOM;i++){
    if(JointPos[i]>SeedArmJointLimit[i].Upper||JointPos[i]<SeedArmJointLimit[i].Lower){
      std::cout << "ERROR : アーム可動範囲外の値が入力されました" << std::endl;     
      return -1;
    }
  }

  for(int j=0;j<ARM_FREEDOM;j++){
    LeftArmSetJointPos[j] = JointPos[j];
  }

  left_tekubi_pitch = 0;//0.0000000000119321033088815*pow(JointPos[5], 6) - 0.00000000122667833182821*pow(JointPos[5], 5) + 0.0000000979913022045031*pow(JointPos[5], 4) - 0.0000139362174275126*pow(JointPos[5], 3) - 0.00055892898307397*pow(JointPos[5], 2) + 0.381998345402461*JointPos[5] - 0.000232762524552399;
  
  left_tekubi_roll = -0.00000000000242706361579019*pow(JointPos[5], 6) - 0.000000000150602156255316*pow(JointPos[5], 5) + 0.0000000441727505516505*pow(JointPos[5], 4) - 0.00000506344248396719*pow(JointPos[5], 3) - 0.000440082138183015*pow(JointPos[5], 2) + 0.164385338238193*JointPos[5] + 0.000065167914236719;
  
  //左腕
  //肩ピッチ 
  noidJointPos[18] = (int)((-0.0000000000933971256927911*pow(JointPos[0], 6) + 0.0000000369034355317591*pow(JointPos[0], 5) - 0.00000574010042392163*pow(JointPos[0], 4) + 0.000374322804691228*pow(JointPos[0], 3) - 0.00458523350688013*pow(JointPos[0], 2) - 0.813300679027264*JointPos[0] - 0.210097776915891) * 100);
  //肩ロール
  noidJointPos[19] = (int)((-0.0000000000018923323872504*pow(JointPos[1], 6) + 0.000000000313119551120788*pow(JointPos[1], 5) + 0.000000105806520878104*pow(JointPos[1], 4) - 0.0000494102868628943*pow(JointPos[1], 3) + 0.00456617193276543*pow(JointPos[1], 2) + 0.452293247948546*JointPos[1] + 0.000399823795305565) * 100);
	//肘ヨー
  noidJointPos[20] = (int)(JointPos[2]*100);
  //肘ピッチ
  noidJointPos[21] = (int)((0.00000000000049111019804115*pow(JointPos[3], 6) - 0.000000000390702276724364*pow(JointPos[3], 5) + 0.000000130488756156302*pow(JointPos[3], 4) - 0.0000234826685847622*pow(JointPos[3], 3) + 0.00161963481365035*pow(JointPos[3], 2) + 0.261403325221181*JointPos[3] - 42.4326561880471) * 100);
  //手首ヨー
  noidJointPos[22] = (int)(JointPos[4]*100);
  //手首ピッチ＆ロール
  noidJointPos[23] = (int)((left_tekubi_roll + left_tekubi_pitch) * 100);
  noidJointPos[24] = (int)((left_tekubi_roll - left_tekubi_pitch) * 100);
  noidJointPos[27] = (int)(JointPos[6]*100);
  //printf("JointPos[0] = %f[°]\n", JointPos[0]);
  //printf("JointPos[1] = %f[°]\n", JointPos[1]);
  //printf("JointPos[2] = %f[°]\n", JointPos[2]);
  //printf("JointPos[3] = %f[°]\n", JointPos[3]);
  //printf("JointPos[4] = %f[°]\n", JointPos[4]);
  //printf("JointPos[5] = %f[°]\n", JointPos[5]);
  //printf("JointPos[6] = %f[°]\n", JointPos[6]);
  //printf("noidJointPos[18] = %d\n", noidJointPos[18]);
  //printf("noidJointPos[19] = %d\n", noidJointPos[19]);
  //printf("noidJointPos[20] = %d\n", noidJointPos[20]);
  //printf("noidJointPos[21] = %d\n", noidJointPos[21]);
  //printf("noidJointPos[22] = %d\n", noidJointPos[22]);
  //printf("noidJointPos[23] = %d\n", noidJointPos[23]);
  //printf("noidJointPos[24] = %d\n", noidJointPos[24]);
 
  return 0;
}


/************************************************

        void setNeckJointAngle(double roll,double pitch,double yaw)

	概要：関節角度を入力するとSeednoid用の値に変換してnoidJointPos[]に書き込む(首のみ)

	引数：
              roll・・・顔ロール方向
              pitch・・・顔ピッチ方向
              yaw・・・	顔ヨー方向
  
	戻り値：なし

*************************************************/
int SeedUpper::setNeckJointAngle(Frame pos)
{
  double neck_roll;
  double neck_pitch;

  //可動範囲の確認
  if(pos.yaw>SeedNeckJointLimit[0].Upper||pos.yaw<SeedNeckJointLimit[0].Lower||
     pos.pitch>SeedNeckJointLimit[1].Upper||pos.pitch<SeedNeckJointLimit[1].Lower||
     pos.roll>SeedNeckJointLimit[2].Upper||pos.roll<SeedNeckJointLimit[2].Lower){
    std::cout << "ERROR : アーム可動範囲外の値が入力されました" << std::endl;     
    return -1;
  }
  
  NeckSetJointPos[0] = pos.yaw;
  NeckSetJointPos[1] = pos.pitch;
  NeckSetJointPos[2] = pos.roll;
  
  neck_roll = -0.0000000000400086550261108*pow(pos.roll, 6) - 0.00000000163908662510759*pow(pos.roll, 5) + 0.000000218863322087176*pow(pos.roll, 4) - 0.0000226736637258251*pow(pos.roll, 3) + 0.000274072986861718*pow(pos.roll, 2) + 0.385430061655752*pos.roll - 0.0000533826671356152;
  neck_pitch = -0.00000000000275160912121836*pow(pos.pitch, 6) + 0.000000000355176744460707*pow(pos.pitch, 5) + 0.0000000294452607359653*pow(pos.pitch, 4) - 0.0000111256314356441*pow(pos.pitch, 3) + 0.000411998083208204*pow(pos.pitch, 2) + 0.169074232321956*pos.pitch - 0.000185818175493513;

  noidJointPos[0] = (int)(pos.yaw*100);
  noidJointPos[1] = (int)((neck_pitch+neck_roll)*100);
  noidJointPos[2] = (int)((neck_pitch-neck_roll)*100);

  return 0;
}

/************************************************

        void setWaistJointAngle(double roll,double pitch,double yaw)

	概要：関節角度を入力するとSeednoid用の値に変換してnoidJointPos[]に書き込む(腰のみ)

	引数：
              roll・・・腰ロール方向
              pitch・・・腰ピッチ方向
              yaw・・・	腰ヨー方向
  
	戻り値：なし

*************************************************/
int SeedUpper::setWaistJointAngle(Frame pos)
{
  double waist_roll;
  double waist_pitch;

  //可動範囲の確認
  if(pos.yaw>SeedWaistJointLimit[0].Upper||pos.yaw<SeedWaistJointLimit[0].Lower||
     pos.pitch>SeedWaistJointLimit[1].Upper||pos.pitch<SeedWaistJointLimit[1].Lower||
     pos.roll>SeedWaistJointLimit[2].Upper||pos.roll<SeedWaistJointLimit[2].Lower){
    std::cout << "ERROR : アーム可動範囲外の値が入力されました" << std::endl;     
    return -1;
  }

  WaistSetJointPos[0] = pos.yaw;
  WaistSetJointPos[1] = pos.pitch;
  WaistSetJointPos[2] = pos.roll;

  waist_roll=0.0000000662755569313944*pow(pos.roll,6) - 0.000000669306194467367*pow(pos.roll,5) + 0.00000348293585972215*pow(pos.roll,4) - 0.000128728565186975*pow(pos.roll,3) + 0.00519581250091505*pow(pos.roll,2) + 0.78075913026441*pos.roll - 0.000190689301689417;
  waist_pitch=0.000000000174315032894223*pow(pos.pitch,6) - 0.0000000306996127789894*pow(pos.pitch,5) + 0.00000257454371696726*pow(pos.pitch,4) - 0.000159480493435595*pow(pos.pitch,3) + 0.00671690503845524*pow(pos.pitch,2) + 0.668272456505489*pos.pitch - 0.0000551434847361771;  

  noidJointPos[10] = (int)((waist_pitch+waist_roll)*100);
  noidJointPos[15] = (int)(pos.yaw*100);
  noidJointPos[25] = (int)((waist_pitch-waist_roll)*100);

  return 0;

}

/************************************************

      int getRightJointAngle(double JointPos[])

      概要：Seednoidクラスに格納されている右腕の関節値を入手する

      引数：
            double JointPos[]・・・関節角度
                       JointPos[0]:肩ピッチ
                       JointPos[1]:肩ロール
                       JointPos[2]:肘ヨー
                       JointPos[3]:肘ピッチ
                       JointPos[4]:手首ヨー
                       JointPos[5]:手首ピッチ
                       JointPos[6]:手首ロール
      戻り値：なし

*************************************************/
void SeedUpper::getRightJointAngle(double JointPos[])
{
  JointPos[0] = RightArmSetJointPos[0];
  JointPos[1] = RightArmSetJointPos[1];
  JointPos[2] = RightArmSetJointPos[2];
  JointPos[3] = RightArmSetJointPos[3];
  JointPos[4] = RightArmSetJointPos[4];
  JointPos[5] = RightArmSetJointPos[5];
  JointPos[6] = RightArmSetJointPos[6];
}

/************************************************

      int getLeftJointAngle(double JointPos[])

      概要：Seednoidクラスに格納されている左腕の関節値を入手する

      引数：
            double JointPos[]・・・関節角度
                       JointPos[0]:肩ピッチ
                       JointPos[1]:肩ロール
                       JointPos[2]:肘ヨー
                       JointPos[3]:肘ピッチ
                       JointPos[4]:手首ヨー
                       JointPos[5]:手首ピッチ
                       JointPos[6]:手首ロール
      戻り値：なし

*************************************************/
void SeedUpper::getLeftJointAngle(double JointPos[])
{
  JointPos[0] = LeftArmSetJointPos[0];
  JointPos[1] = LeftArmSetJointPos[1];
  JointPos[2] = LeftArmSetJointPos[2];
  JointPos[3] = LeftArmSetJointPos[3];
  JointPos[4] = LeftArmSetJointPos[4];
  JointPos[5] = LeftArmSetJointPos[5];
  JointPos[6] = LeftArmSetJointPos[6];
}

/************************************************

      Frame getNeckJointAngle()

      概要：Seednoidクラスに格納されている首の関節値を入手する

      引数：なし

      戻り値：首の関節値（ロールピッチヨー）

*************************************************/
Frame SeedUpper::getNeckJointAngle()
{
  Frame pos;
  pos.yaw = NeckSetJointPos[0];
  pos.pitch = NeckSetJointPos[1];
  pos.roll = NeckSetJointPos[2];

  return pos;
}

/************************************************

      Frame getWaistJointAngle()

      概要：Seednoidクラスに格納されている腰の関節値を入手する

      引数：なし

      戻り値：腰の関節値（ロールピッチヨー）

*************************************************/
Frame SeedUpper::getWaistJointAngle()
{
  Frame pos;
  pos.yaw = WaistSetJointPos[0];
  pos.pitch = WaistSetJointPos[1];
  pos.roll = WaistSetJointPos[2];

  return pos;
}


/************************************************

        void readAllJointAngle(Frame* Waist, Frame* Neck, double JointPos[], double JointPos[])

	概要：SeedNoidの全関節の関節値を読み取り、度数法にしてJointPos[]に格納する

	引数：
             Frame Waist・・・腰の角度
             Frame Neck・・・首の角度
             double RightJointPos[]・・・右腕関節角度を格納する配列
             double LeftJointPos[]・・・左腕関節角度を格納する配列
  
	戻り値：なし

*************************************************/
void SeedUpper::readAllJointAngle(Frame* WaistPos, Frame* NeckPos, double RightJointPos[], double LeftJointPos[])
{
  ReadServoAngle(ReadAngle);
  double rightSeedPos[ARM_FREEDOM + 1];  
  double right_tekubi_roll;
  double right_tekubi_pitch;
  for(int i=0;i<7;i++)
    {
      rightSeedPos[i] = ReadAngle[i+3]/100;
    }
  rightSeedPos[7] = ReadAngle[12]/100;//hand_yaw

  right_tekubi_roll = (rightSeedPos[5]+rightSeedPos[6])/2;
  right_tekubi_pitch = (rightSeedPos[5]-rightSeedPos[6])/2;

  RightJointPos[0] = -0.0000000360742099675144*pow(rightSeedPos[0],6) - 0.00000335029464179319*pow(rightSeedPos[0],5) - 0.00011218800655908*pow(rightSeedPos[0],4) - 0.00233475809141627*pow(rightSeedPos[0],3) - 0.0186432996555008*pow(rightSeedPos[0],2) - 1.19872714942747*rightSeedPos[0] + 0.0949926824675345;
  RightJointPos[1] = -0.000000000354630781337906*pow(rightSeedPos[1],6) + 0.000000199502568021259*pow(rightSeedPos[1],5) - 0.0000210173078869502*pow(rightSeedPos[1],4)+ 0.00115615351342058*pow(rightSeedPos[1],3) - 0.0341767232930579*pow(rightSeedPos[1],2) + 2.13718074203643*rightSeedPos[1] + 0.0200412424164824;
  RightJointPos[2] = rightSeedPos[2];
  RightJointPos[3] = 0.000000043014640453698*pow(rightSeedPos[3],6) + 0.0000070130668059876*pow(rightSeedPos[3],5) + 0.000453246553025867*pow(rightSeedPos[3],4) + 0.0157916727949889*pow(rightSeedPos[3],3) + 0.351768178778908*pow(rightSeedPos[3],2) + 8.53645519252888*rightSeedPos[3] + 179.751943668045;
  RightJointPos[4] = rightSeedPos[4];
  //JointPos[5] = 0.0000000076130666215590*pow(tekubi_pitch,6) + 0.000000924066482006935*pow(tekubi_pitch,5) + 0.00000131244076205541*pow(tekubi_pitch,4) + 0.000728273149380743*pow(tekubi_pitch,3) + 0.0100270726910353*pow(tekubi_pitch,2) + 2.61783801995595*tekubi_pitch + 0.000608125079554439;
  RightJointPos[5] = -0.000048567427779922*pow(right_tekubi_roll,6) - 0.000817764063177491*pow(right_tekubi_roll,5) - 0.00207898347213374*pow(right_tekubi_roll,4) + 0.0305395339240331*pow(right_tekubi_roll,3) + 0.16505173242366*pow(right_tekubi_roll,2) + 5.96539837081825*right_tekubi_roll - 0.155636878020886; 
  RightJointPos[6] = rightSeedPos[7];

  double leftSeedPos[ARM_FREEDOM + 1];  
  double left_tekubi_roll;
  //double tekubi_pitch;
  for(int i=0;i<ARM_FREEDOM;i++)
    {
      leftSeedPos[i] = ReadAngle[i+18]/100;
    }
  leftSeedPos[7] = ReadAngle[27]/100;//hand_yaw
  
  left_tekubi_roll = (leftSeedPos[5]+leftSeedPos[6])/2;
  //tekubi_pitch = (leftSeedPos[5]-leftSeedPos[6])/2;

  LeftJointPos[0] = -0.0000000360742099675144*pow(leftSeedPos[0],6) - 0.00000335029464179319*pow(leftSeedPos[0],5) - 0.00011218800655908*pow(leftSeedPos[0],4) - 0.00233475809141627*pow(leftSeedPos[0],3) - 0.0186432996555008*pow(leftSeedPos[0],2) - 1.19872714942747*leftSeedPos[0] + 0.0949926824675345;
  LeftJointPos[1] = -0.00000000069708744505903*pow(leftSeedPos[1],6) + 0.000000252742056838784*pow(leftSeedPos[1],5) - 0.0000245454691594205*pow(leftSeedPos[1],4) + 0.00128199329537892*pow(leftSeedPos[1],3) - 0.0370077199622756*pow(leftSeedPos[1],2) + 2.17693328140012*leftSeedPos[1] + 0.020900383242406;
  LeftJointPos[2] = leftSeedPos[2];
  LeftJointPos[3] = 0.000000043014640453698*pow(leftSeedPos[3],6) + 0.0000070130668059876*pow(leftSeedPos[3],5) + 0.000453246553025867*pow(leftSeedPos[3],4) + 0.0157916727949889*pow(leftSeedPos[3],3) + 0.351768178778908*pow(leftSeedPos[3],2) + 8.53645519252888*leftSeedPos[3] + 179.751943668045;
  LeftJointPos[4] = leftSeedPos[4];
  //JointPos[5] = 0.0000000076130666215590*pow(tekubi_pitch,6) + 0.000000924066482006935*pow(tekubi_pitch,5) + 0.00000131244076205541*pow(tekubi_pitch,4) + 0.000728273149380743*pow(tekubi_pitch,3) + 0.0100270726910353*pow(tekubi_pitch,2) + 2.61783801995595*tekubi_pitch + 0.000608125079554439;
  LeftJointPos[5] = -0.000048567427779922*pow(left_tekubi_roll,6) - 0.000817764063177491*pow(left_tekubi_roll,5) - 0.00207898347213374*pow(left_tekubi_roll,4) + 0.0305395339240331*pow(left_tekubi_roll,3) + 0.16505173242366*pow(left_tekubi_roll,2) + 5.96539837081825*left_tekubi_roll - 0.155636878020886;
  LeftJointPos[6] = leftSeedPos[7];

  double neckSeedPos[3];
  double neck_roll;
  double neck_pitch;
  for(int i=0;i<3;i++)
    {
      neckSeedPos[i] = ReadAngle[i]/100;
    }
  neck_roll = (neckSeedPos[1]-neckSeedPos[2])/2;
  neck_pitch = (neckSeedPos[1]+neckSeedPos[2])/2;
  
  NeckPos->roll = -0.0000000967906101934091*pow(neck_roll,6) + 0.00000275344283291901*pow(neck_roll,5) - 0.0000345131388448596*pow(neck_roll,4) + 0.00102581137967788*pow(neck_roll,3) - 0.00479308003951673*pow(neck_roll,2) + 2.59463403218453*neck_roll + 0.00014693282153511;
  NeckPos->pitch = -0.00000221465847261015*pow(neck_pitch,6) + 0.000100142608257954*pow(neck_pitch,5) - 0.00135773530086106*pow(neck_pitch,4) + 0.0171252717519687*pow(neck_pitch,3) - 0.0862191168583828*pow(neck_pitch,2) + 5.91142349775356*neck_pitch + 0.00275500404667073; 
  NeckPos->yaw = neckSeedPos[0];

  double waistSeedPos[3];
  double waist_roll;
  double waist_pitch;
  
  waistSeedPos[0] = ReadAngle[10]/100;
  waistSeedPos[1] = ReadAngle[15]/100;
  waistSeedPos[2] = ReadAngle[25]/100;
    
  waist_roll = (waistSeedPos[0]-waistSeedPos[2])/2;
  waist_pitch = (waistSeedPos[0]+waistSeedPos[2])/2;
  
  WaistPos->roll = -0.000000884979920900975*pow(waist_roll,6) + 0.00000876698606313831*pow(waist_roll,5) - 0.0000291619590011077*pow(waist_roll,4) + 0.000447649797955574*pow(waist_roll,3) - 0.0108892557527606*pow(waist_roll,2) + 1.28118533903592*waist_roll + 0.000161740014248277;
  WaistPos->pitch = -0.0000000187560450677637*pow(waist_pitch,6) + 0.00000183293729446015*pow(waist_pitch,5) - 0.0000717423204159852*pow(waist_pitch,4) + 0.00156523105429672*pow(waist_pitch,3) - 0.0241571731447025*pow(waist_pitch,2) + 1.49856262998118*waist_pitch + 0.00835796796454664; 
  WaistPos->yaw = waistSeedPos[1];


}


/************************************************

        void readRightJointAngle(double JointPos[])

	概要：SeedNoidの右腕の関節値を読み取り、度数法にしてJointPos[]に格納する

	引数：
             double JointPos[]・・・関節角度を格納する配列
  
	戻り値：なし

*************************************************/
void SeedUpper::readRightJointAngle(double JointPos[])
{
  ReadServoAngle(ReadAngle);
  double SeedPos[ARM_FREEDOM + 1];  
  double tekubi_roll;
  double tekubi_pitch;
  for(int i=0;i<7;i++)
    {
      SeedPos[i] = ReadAngle[i+3]/100;
    }
  SeedPos[7] = ReadAngle[12]/100;//hand_yaw

  tekubi_roll = (SeedPos[5]+SeedPos[6])/2;
  tekubi_pitch = (SeedPos[5]-SeedPos[6])/2;

  JointPos[0] = -0.0000000360742099675144*pow(SeedPos[0],6) - 0.00000335029464179319*pow(SeedPos[0],5) - 0.00011218800655908*pow(SeedPos[0],4) - 0.00233475809141627*pow(SeedPos[0],3) - 0.0186432996555008*pow(SeedPos[0],2) - 1.19872714942747*SeedPos[0] + 0.0949926824675345;
  JointPos[1] = -0.000000000354630781337906*pow(SeedPos[1],6) + 0.000000199502568021259*pow(SeedPos[1],5) - 0.0000210173078869502*pow(SeedPos[1],4)+ 0.00115615351342058*pow(SeedPos[1],3) - 0.0341767232930579*pow(SeedPos[1],2) + 2.13718074203643*SeedPos[1] + 0.0200412424164824;
  JointPos[2] = SeedPos[2];
  JointPos[3] = 0.000000043014640453698*pow(SeedPos[3],6) + 0.0000070130668059876*pow(SeedPos[3],5) + 0.000453246553025867*pow(SeedPos[3],4) + 0.0157916727949889*pow(SeedPos[3],3) + 0.351768178778908*pow(SeedPos[3],2) + 8.53645519252888*SeedPos[3] + 179.751943668045;
  JointPos[4] = SeedPos[4];
  //JointPos[5] = 0.0000000076130666215590*pow(tekubi_pitch,6) + 0.000000924066482006935*pow(tekubi_pitch,5) + 0.00000131244076205541*pow(tekubi_pitch,4) + 0.000728273149380743*pow(tekubi_pitch,3) + 0.0100270726910353*pow(tekubi_pitch,2) + 2.61783801995595*tekubi_pitch + 0.000608125079554439;
  JointPos[5] = -0.000048567427779922*pow(tekubi_roll,6) - 0.000817764063177491*pow(tekubi_roll,5) - 0.00207898347213374*pow(tekubi_roll,4) + 0.0305395339240331*pow(tekubi_roll,3) + 0.16505173242366*pow(tekubi_roll,2) + 5.96539837081825*tekubi_roll - 0.155636878020886; 
  JointPos[6] = SeedPos[7];

  for(int i=0;i<ARM_FREEDOM;i++)
    {
      std::cout << "RightArmJointPos["<<i<<"] = "<<JointPos[i] << "[°]" <<std::endl;
    }

}


/************************************************

        void readLeftJointAngle(double JointPos[])

	概要：SeedNoidの左腕の関節値を読み取り、度数法にしてJointPos[]に格納する

	引数：
             double JointPos[]・・・関節角度を格納する配列
  
	戻り値：なし

*************************************************/
void SeedUpper::readLeftJointAngle(double JointPos[])
{
  ReadServoAngle(ReadAngle);
  double SeedPos[ARM_FREEDOM + 1];  
  double tekubi_roll;
  //double tekubi_pitch;
  for(int i=0;i<ARM_FREEDOM;i++)
    {
      SeedPos[i] = ReadAngle[i+18]/100;
    }
  SeedPos[7] = ReadAngle[27]/100;//hand_yaw
  
  tekubi_roll = (SeedPos[5]+SeedPos[6])/2;
  //tekubi_pitch = (SeedPos[5]-SeedPos[6])/2;

  JointPos[0] = -0.0000000360742099675144*pow(SeedPos[0],6) - 0.00000335029464179319*pow(SeedPos[0],5) - 0.00011218800655908*pow(SeedPos[0],4) - 0.00233475809141627*pow(SeedPos[0],3) - 0.0186432996555008*pow(SeedPos[0],2) - 1.19872714942747*SeedPos[0] + 0.0949926824675345;
  JointPos[1] = -0.00000000069708744505903*pow(SeedPos[1],6) + 0.000000252742056838784*pow(SeedPos[1],5) - 0.0000245454691594205*pow(SeedPos[1],4) + 0.00128199329537892*pow(SeedPos[1],3) - 0.0370077199622756*pow(SeedPos[1],2) + 2.17693328140012*SeedPos[1] + 0.020900383242406;
  JointPos[2] = SeedPos[2];
  JointPos[3] = 0.000000043014640453698*pow(SeedPos[3],6) + 0.0000070130668059876*pow(SeedPos[3],5) + 0.000453246553025867*pow(SeedPos[3],4) + 0.0157916727949889*pow(SeedPos[3],3) + 0.351768178778908*pow(SeedPos[3],2) + 8.53645519252888*SeedPos[3] + 179.751943668045;
  JointPos[4] = SeedPos[4];
  //JointPos[5] = 0.0000000076130666215590*pow(tekubi_pitch,6) + 0.000000924066482006935*pow(tekubi_pitch,5) + 0.00000131244076205541*pow(tekubi_pitch,4) + 0.000728273149380743*pow(tekubi_pitch,3) + 0.0100270726910353*pow(tekubi_pitch,2) + 2.61783801995595*tekubi_pitch + 0.000608125079554439;
  JointPos[5] = -0.000048567427779922*pow(tekubi_roll,6) - 0.000817764063177491*pow(tekubi_roll,5) - 0.00207898347213374*pow(tekubi_roll,4) + 0.0305395339240331*pow(tekubi_roll,3) + 0.16505173242366*pow(tekubi_roll,2) + 5.96539837081825*tekubi_roll - 0.155636878020886;
  JointPos[6] = SeedPos[7];

  for(int i=0;i<ARM_FREEDOM;i++)
    {
      std::cout << "LeftArmJointPos["<<i<<"] = "<<JointPos[i] << "[°]" <<std::endl;
    }

}


/************************************************

        Frame readNeckJointAngle()

	概要：SeedNoidの首の関節値を読み取り、度数法にしてFrame構造体に格納する

	引数：
             なし
  
	戻り値：首の関節角度(roll,pitch,yaw)

*************************************************/
Frame SeedUpper::readNeckJointAngle()
{
  ReadServoAngle(ReadAngle);
  Frame pos;  
  double SeedPos[3];
  double neck_roll;
  double neck_pitch;
  for(int i=0;i<3;i++)
    {
      SeedPos[i] = ReadAngle[i]/100;
    }
  neck_roll = (SeedPos[1]-SeedPos[2])/2;
  neck_pitch = (SeedPos[1]+SeedPos[2])/2;
  
  pos.roll = -0.0000000967906101934091*pow(neck_roll,6) + 0.00000275344283291901*pow(neck_roll,5) - 0.0000345131388448596*pow(neck_roll,4) + 0.00102581137967788*pow(neck_roll,3) - 0.00479308003951673*pow(neck_roll,2) + 2.59463403218453*neck_roll + 0.00014693282153511;
  pos.pitch = -0.00000221465847261015*pow(neck_pitch,6) + 0.000100142608257954*pow(neck_pitch,5) - 0.00135773530086106*pow(neck_pitch,4) + 0.0171252717519687*pow(neck_pitch,3) - 0.0862191168583828*pow(neck_pitch,2) + 5.91142349775356*neck_pitch + 0.00275500404667073; 
  pos.yaw = SeedPos[0];

  std::cout << "NeckPos.roll = " <<pos.roll << "[°]" << std::endl;
  std::cout << "NeckPos.pitch = " <<pos.pitch << "[°]"<< std::endl;
  std::cout << "NeckPos.yaw = " <<pos.yaw << "[°]" << std::endl;

  return pos;

}


/************************************************

        Frame readWaistJointAngle()

	概要：SeedNoidの腰の関節値を読み取り、度数法にしてFrame構造体に格納する

	引数：
             なし
  
	戻り値：腰の関節角度(roll,pitch,yaw)

*************************************************/
Frame SeedUpper::readWaistJointAngle()
{
  ReadServoAngle(ReadAngle);
  Frame pos;  
  double SeedPos[3];
  double waist_roll;
  double waist_pitch;
  
  SeedPos[0] = ReadAngle[10]/100;
  SeedPos[1] = ReadAngle[15]/100;
  SeedPos[2] = ReadAngle[25]/100;
    
  waist_roll = (SeedPos[0]-SeedPos[2])/2;
  waist_pitch = (SeedPos[0]+SeedPos[2])/2;
  
  pos.roll = -0.000000884979920900975*pow(waist_roll,6) + 0.00000876698606313831*pow(waist_roll,5) - 0.0000291619590011077*pow(waist_roll,4) + 0.000447649797955574*pow(waist_roll,3) - 0.0108892557527606*pow(waist_roll,2) + 1.28118533903592*waist_roll + 0.000161740014248277;
  pos.pitch = -0.0000000187560450677637*pow(waist_pitch,6) + 0.00000183293729446015*pow(waist_pitch,5) - 0.0000717423204159852*pow(waist_pitch,4) + 0.00156523105429672*pow(waist_pitch,3) - 0.0241571731447025*pow(waist_pitch,2) + 1.49856262998118*waist_pitch + 0.00835796796454664; 
  pos.yaw = SeedPos[1];

  std::cout << "WaistPos.roll = " <<pos.roll << "[°]" << std::endl;
  std::cout << "WaistPos.pitch = " <<pos.pitch << "[°]" << std::endl;
  std::cout << "WaistPos.yaw = " <<pos.yaw << "[°]" << std::endl;

  return pos;
}


/************************************************

        void notReadGetNowRightJointAngle(double JointPos[])

	概要： ReadServoAngleAndSetNowAngle()で読み取った右腕のNowAngleを取得する

	引数：
             double JointPos[]・・・関節角度を格納する配列
  
	戻り値：なし

*************************************************/
void SeedUpper::notReadGetNowRightJointAngle(double JointPos[])
{
  double SeedPos[ARM_FREEDOM + 1];  
  double tekubi_roll;
  //double tekubi_pitch;
  for(int i=0;i<ARM_FREEDOM;i++)
    {
      SeedPos[i] = NowAngle[i+3]/100;
    }
  SeedPos[7] = NowAngle[12]/100;//hand_yaw

  tekubi_roll = (SeedPos[5]+SeedPos[6])/2;
  //tekubi_pitch = (SeedPos[5]-SeedPos[6])/2;

  JointPos[0] = -0.0000000360742099675144*pow(SeedPos[0],6) - 0.00000335029464179319*pow(SeedPos[0],5) - 0.00011218800655908*pow(SeedPos[0],4) - 0.00233475809141627*pow(SeedPos[0],3) - 0.0186432996555008*pow(SeedPos[0],2) - 1.19872714942747*SeedPos[0] + 0.0949926824675345;
  JointPos[1] = -0.00000000069708744505903*pow(SeedPos[1],6) + 0.000000252742056838784*pow(SeedPos[1],5) - 0.0000245454691594205*pow(SeedPos[1],4) + 0.00128199329537892*pow(SeedPos[1],3) - 0.0370077199622756*pow(SeedPos[1],2) + 2.17693328140012*SeedPos[1] + 0.020900383242406;
  JointPos[2] = SeedPos[2];
  JointPos[3] = 0.000000043014640453698*pow(SeedPos[3],6) + 0.0000070130668059876*pow(SeedPos[3],5) + 0.000453246553025867*pow(SeedPos[3],4) + 0.0157916727949889*pow(SeedPos[3],3) + 0.351768178778908*pow(SeedPos[3],2) + 8.53645519252888*SeedPos[3] + 179.751943668045;
  JointPos[4] = SeedPos[4];
  //JointPos[5] = 0.0000000338503162167214*pow(tekubi_pitch,6) + 0.00000102621995010632*pow(tekubi_pitch,5) - 0.00000402410074364352*pow(tekubi_pitch,4) + 0.000710999018203095*pow(tekubi_pitch,3) + 0.0101874649864333*pow(tekubi_pitch,2) + 2.61843261952329*tekubi_pitch + 0.000658034453859403;
  JointPos[5] = -0.000048567427779922*pow(tekubi_roll,6) - 0.000817764063177491*pow(tekubi_roll,5) - 0.00207898347213374*pow(tekubi_roll,4) + 0.0305395339240331*pow(tekubi_roll,3) + 0.16505173242366*pow(tekubi_roll,2) + 5.96539837081825*tekubi_roll - 0.155636878020886;
  JointPos[6] = SeedPos[7];
  
  for(int k=0;k<ARM_FREEDOM;k++)
    {
      std::cout << "nowRightJointPos["<<k<<"]= " << JointPos[k] << std::endl;
    }
}

/************************************************

        void notReadGetNowLeftJointAngle(double JointPos[])

	概要：ReadServoAngleAndSetNowAngle()で読み取った左腕のNowAngleを取得する

	引数：
             double JointPos[]・・・関節角度を格納する配列
  
	戻り値：なし

*************************************************/
void SeedUpper::notReadGetNowLeftJointAngle(double JointPos[])
{
  double SeedPos[ARM_FREEDOM + 1];  
  double tekubi_roll;
  //double tekubi_pitch;
  for(int i=0;i<ARM_FREEDOM;i++)
    {
      SeedPos[i] = NowAngle[i+18]/100;
    }
  SeedPos[7] = NowAngle[27]/100;

  tekubi_roll = (SeedPos[5]+SeedPos[6])/2;
  //tekubi_pitch = (SeedPos[5]-SeedPos[6])/2;

  JointPos[0] = -0.0000000360742099675144*pow(SeedPos[0],6) - 0.00000335029464179319*pow(SeedPos[0],5) - 0.00011218800655908*pow(SeedPos[0],4) - 0.00233475809141627*pow(SeedPos[0],3) - 0.0186432996555008*pow(SeedPos[0],2) - 1.19872714942747*SeedPos[0] + 0.0949926824675345;
  JointPos[1] = -0.00000000069708744505903*pow(SeedPos[1],6) + 0.000000252742056838784*pow(SeedPos[1],5) - 0.0000245454691594205*pow(SeedPos[1],4) + 0.00128199329537892*pow(SeedPos[1],3) - 0.0370077199622756*pow(SeedPos[1],2) + 2.17693328140012*SeedPos[1] + 0.020900383242406;
  JointPos[2] = SeedPos[2];
  JointPos[3] = 0.000000043014640453698*pow(SeedPos[3],6) + 0.0000070130668059876*pow(SeedPos[3],5) + 0.000453246553025867*pow(SeedPos[3],4) + 0.0157916727949889*pow(SeedPos[3],3) + 0.351768178778908*pow(SeedPos[3],2) + 8.53645519252888*SeedPos[3] + 179.751943668045;
  JointPos[4] = SeedPos[4];
  //JointPos[5] = 0.0000000338503162167214*pow(tekubi_pitch,6) + 0.00000102621995010632*pow(tekubi_pitch,5) - 0.00000402410074364352*pow(tekubi_pitch,4) + 0.000710999018203095*pow(tekubi_pitch,3) + 0.0101874649864333*pow(tekubi_pitch,2) + 2.61843261952329*tekubi_pitch + 0.000658034453859403;
  JointPos[5] = -0.000048567427779922*pow(tekubi_roll,6) - 0.000817764063177491*pow(tekubi_roll,5) - 0.00207898347213374*pow(tekubi_roll,4) + 0.0305395339240331*pow(tekubi_roll,3) + 0.16505173242366*pow(tekubi_roll,2) + 5.96539837081825*tekubi_roll - 0.155636878020886;
  JointPos[6] = SeedPos[7];

    for(int k=0;k<ARM_FREEDOM;k++)
    {
      std::cout << "nowLeftJointPos["<<k<<"]= " << JointPos[k] << std::endl;
    }
    
}


/************************************************

        Frame notReadGetNowNeckJointAngle()

	概要：ReadServoAngleAndSetNowAngle()で読み取った首のNowAngleを取得する

	引数：
             なし
  
	戻り値：首の関節角度(roll,pitch,yaw)

*************************************************/
Frame SeedUpper::notReadGetNowNeckJointAngle()
{
  Frame pos;  
  double SeedPos[3];
  double neck_roll;
  double neck_pitch;
  for(int i=0;i<3;i++)
    {
      SeedPos[i] = NowAngle[i]/100;
    }
  neck_roll = (SeedPos[1]-SeedPos[2])/2;
  neck_pitch = (SeedPos[1]+SeedPos[2])/2;
  
  pos.roll = -0.0000000967906101934091*pow(neck_roll,6) + 0.00000275344283291901*pow(neck_roll,5) - 0.0000345131388448596*pow(neck_roll,4) + 0.00102581137967788*pow(neck_roll,3) - 0.00479308003951673*pow(neck_roll,2) + 2.59463403218453*neck_roll + 0.00014693282153511;
  pos.pitch = -0.00000221465847261015*pow(neck_pitch,6) + 0.000100142608257954*pow(neck_pitch,5) - 0.00135773530086106*pow(neck_pitch,4) + 0.0171252717519687*pow(neck_pitch,3) - 0.0862191168583828*pow(neck_pitch,2) + 5.91142349775356*neck_pitch + 0.00275500404667073; 
  pos.yaw = SeedPos[0];

  return pos;

}

/************************************************

        Frame notReadGetNowWaistJointAngle()

	概要：ReadServoAngleAndSetNowAngle()で読み取った腰のNowAngleを取得する

	引数：
             なし
  
	戻り値：腰の関節角度(roll,pitch,yaw)

*************************************************/
Frame SeedUpper::notReadGetNowWaistJointAngle()
{
  Frame pos;  
  double SeedPos[3];
  double waist_roll;
  double waist_pitch;
  
  SeedPos[0] = NowAngle[10]/100;
  SeedPos[1] = NowAngle[15]/100;
  SeedPos[2] = NowAngle[25]/100;
    
  waist_roll = (SeedPos[0]-SeedPos[2])/2;
  waist_pitch = (SeedPos[0]+SeedPos[2])/2;
  
  pos.roll = -0.000000884979920900975*pow(waist_roll,6) + 0.00000876698606313831*pow(waist_roll,5) - 0.0000291619590011077*pow(waist_roll,4) + 0.000447649797955574*pow(waist_roll,3) - 0.0108892557527606*pow(waist_roll,2) + 1.28118533903592*waist_roll + 0.000161740014248277;
  pos.pitch = -0.0000000187560450677637*pow(waist_pitch,6) + 0.00000183293729446015*pow(waist_pitch,5) - 0.0000717423204159852*pow(waist_pitch,4) + 0.00156523105429672*pow(waist_pitch,3) - 0.0241571731447025*pow(waist_pitch,2) + 1.49856262998118*waist_pitch + 0.00835796796454664; 
  pos.yaw = SeedPos[1];

  return pos;
}


/************************************************

      void OpenRightGripper()

      概要：Seednoid右腕のハンドを開く

      引数：なし

      戻り値：なし

*************************************************/
void SeedUpper::OpenRightGripper()
{
  noidJointPos[11]=32767;//0x7fff
  
  std::vector<unsigned char> sendData;
  int dataLength = 8;
  sendData.resize(dataLength);
  sendData[0] = 0xfd;
  sendData[1] = 0xdf;
  sendData[2] = 0x04;
  sendData[3] = 0x22;
  sendData[4] = 0x0c;
  sendData[5] = 0x00;
  sendData[6] = 0x03;
  sendData[7] = calcCheckSum(sendData, dataLength);
  
  serialWrite(sendData);

  NeedCancelScriptRightHand = 1;
  
}

/************************************************

      void CloseRightGripper()

      概要：Seednoid右腕のハンドを閉じる

      引数：なし

      戻り値：なし

*************************************************/
void SeedUpper::CloseRightGripper()
{
  noidJointPos[11]=32767;//0x7fff

  std::vector<unsigned char> sendData;
  int dataLength = 8;
  sendData.resize(dataLength);
  sendData[0] = 0xfd;
  sendData[1] = 0xdf;
  sendData[2] = 0x04;
  sendData[3] = 0x22;
  sendData[4] = 0x0c;
  sendData[5] = 0x00;
  sendData[6] = 0x02;
  sendData[7] = calcCheckSum(sendData, dataLength);
  
  serialWrite(sendData);

  NeedCancelScriptRightHand = 1;
  
}

/************************************************

      void MoveRightGripper()

      概要：Seednoid右腕のハンドを閉じる

      引数：なし

      戻り値：なし

*************************************************/
void SeedUpper::MoveRightGripper(int angleRatio)
{

  if(NeedCancelScriptRightHand)
    {
      cancelScriptRightHand();
      usleep(10000);
      NeedCancelScriptRightHand = 0;
    }
  double calc = (HAND_LIMITMIN*(100-angleRatio))/100;
  noidJointPos[11]=(int)(calc);
  SeedAction(3000); 
}

/************************************************

      void OpenLeftGripper()

      概要：Seednoid右腕のハンドを開く

      引数：なし

      戻り値：なし

*************************************************/
void SeedUpper::OpenLeftGripper()
{
  noidJointPos[26]=32767;//0x7fff

  std::vector<unsigned char> sendData;
  int dataLength = 8;
  sendData.resize(dataLength);
  sendData[0] = 0xfd;
  sendData[1] = 0xdf;
  sendData[2] = 0x04;
  sendData[3] = 0x22;
  sendData[4] = 0x1b;
  sendData[5] = 0x00;
  sendData[6] = 0x03;
  sendData[7] = calcCheckSum(sendData, dataLength);
  
  serialWrite(sendData);

  NeedCancelScriptLeftHand = 1;
}

/************************************************

      void CloseLeftGripper()

      概要：Seednoid右腕のハンドを閉じる

      引数：なし

      戻り値：なし

*************************************************/
void SeedUpper::CloseLeftGripper()
{
  noidJointPos[26]=32767;//0x7fff

  std::vector<unsigned char> sendData;
  int dataLength = 8;
  sendData.resize(dataLength);
  sendData[0] = 0xfd;
  sendData[1] = 0xdf;
  sendData[2] = 0x04;
  sendData[3] = 0x22;
  sendData[4] = 0x1b;
  sendData[5] = 0x00;
  sendData[6] = 0x02;
  sendData[7] = calcCheckSum(sendData, dataLength);
  
  serialWrite(sendData);

  NeedCancelScriptLeftHand = 1;
}

/************************************************

      void MoveLeftGripper()

      概要：Seednoid左腕のハンドを操作する

      引数：なし

      戻り値：なし

*************************************************/
void SeedUpper::MoveLeftGripper(int angleRatio)
{

  if(NeedCancelScriptLeftHand)
    {
      cancelScriptLeftHand();
      usleep(10000);
      NeedCancelScriptLeftHand = 0;
    }
  double calc = (HAND_LIMITMIN*(100-angleRatio))/100;
  noidJointPos[26]=(int)(calc);
  SeedAction(3000); 
}



/************************************************

        void setRightHandCurrent(int CurrentRate)

	概要：ハンドの最大電流を設定する

	引数：
              int CurrentRate・・・最大電流0~100[%] 100%で1.5A
	
	戻り値：なし

*************************************************/
void SeedUpper::setRightHandCurrent(int CurrentRate)
{
  if(0>CurrentRate||CurrentRate>100){
    std::cout << "Error CurrentRate Wrong Value" <<std::endl;
  }
  else{
    std::vector<unsigned char> sendData;
    //uchar buf[8] = {0};
    int dataLength = 8;
    sendData.resize(dataLength);
    sendData[0] = 0xfd;
    sendData[1] = 0xdf;
    sendData[2] = 0x04;
    sendData[3] = 0x01;
    sendData[4] = 0x0c;
    sendData[5] = CurrentRate & 0xff;
    sendData[6] = CurrentRate & 0xff;
    sendData[7] = calcCheckSum(sendData, dataLength);
    
    serialWrite(sendData); 
  }
}

/************************************************

        void setLeftHandCurrent(int CurrentRate)

	概要：ハンドの最大電流を設定する

	引数：
              int CurrentRate・・・最大電流0~100[%] 100%で1.5A
	
	戻り値：なし

*************************************************/
void SeedUpper::setLeftHandCurrent(int CurrentRate)
{
  if(0>CurrentRate||CurrentRate>100){
    std::cout << "Error CurrentRate Wrong Value" <<std::endl;
  }
  else{
    std::vector<unsigned char> sendData;
    //uchar buf[8] = {0};
    int dataLength = 8;
    sendData.resize(dataLength);
    sendData[0] = 0xfd;
    sendData[1] = 0xdf;
    sendData[2] = 0x04;
    sendData[3] = 0x01;
    sendData[4] = 0x1b;
    sendData[5] = CurrentRate & 0xff;
    sendData[6] = CurrentRate & 0xff;
    sendData[7] = calcCheckSum(sendData, dataLength);
    
    serialWrite(sendData); 
  }
}


/************************************************

        void cancelScriptRightHand()

	概要：スクリプトをキャンセルする

	引数：なし
	
	戻り値：なし

*************************************************/
void SeedUpper::cancelScriptRightHand()
{
  //uchar buf[8] = { 0 };
  std::vector<unsigned char> sendData;
  int dataLength = 8;
  sendData.resize(dataLength);
  sendData[0] = 0xfd;
  sendData[1] = 0xdf;
  sendData[2] = 0x04;
  sendData[3] = 0x22;
  sendData[4] = 0x0c;
  sendData[5] = 0x00;
  sendData[6] = 0x04;
  sendData[7] = calcCheckSum(sendData, dataLength);
  std::cout << "cancelScript"<< std::endl;
  serialWrite(sendData);
}


/************************************************

        void cancelScriptLeftHand()

	概要：スクリプトをキャンセルする

	引数：なし
	
	戻り値：なし

*************************************************/
void SeedUpper::cancelScriptLeftHand()
{
  //uchar buf[8] = { 0 };
  std::vector<unsigned char> sendData;
  int dataLength = 8;
  sendData.resize(dataLength);
  sendData[0] = 0xfd;
  sendData[1] = 0xdf;
  sendData[2] = 0x04;
  sendData[3] = 0x22;
  sendData[4] = 0x1b;
  sendData[5] = 0x00;
  sendData[6] = 0x04;
  sendData[7] = calcCheckSum(sendData, dataLength);
  std::cout << "cancelScript" << std::endl;
  serialWrite(sendData);
}


/************************************************

	void TransRot(double eerot[],double roll,double pitch,double yaw)
	
	概要：ロールピッチヨー[deg]から先端姿勢の回転行列を求める

	引数：
　　　　　　　double eerot[]・・・計算した行列を格納する配列
                                 |0 1 2|
                                 |3 4 5|
                                 |6 7 8|
             double roll・・・ロール回転角度
             double pitch・・・ピッチ回転角度
             double yaw・・・ヨー回転角度

	戻り値：なし

*************************************************/
void SeedUpper::TransRot(double eerot[],double roll,double pitch,double yaw)
{

  //ロールピッチヨー　ロボット工学（遠山茂樹著）p25
  double Rrotx;
  double Rroty;
  double Rrotz;
  Rrotx = roll * M_PI / 180;
  Rroty = pitch * M_PI / 180;// -M_PI/2;
  Rrotz = yaw * M_PI / 180;
  eerot[0] = cos(Rroty)*cos(Rrotz);
  eerot[1] = cos(Rrotz)*sin(Rroty)*sin(Rrotx)-sin(Rrotz)*cos(Rrotx);
  eerot[2] = cos(Rrotz)*sin(Rroty)*cos(Rrotx)+sin(Rrotz)*sin(Rrotx);
  eerot[3] = sin(Rrotz)*cos(Rroty);
  eerot[4] = sin(Rrotz)*sin(Rroty)*sin(Rrotx)+cos(Rrotz)*cos(Rrotx);
  eerot[5] = sin(Rrotz)*sin(Rroty)*cos(Rrotx)-cos(Rrotz)*sin(Rrotx);
  eerot[6] = -sin(Rroty);
  eerot[7] = cos(Rroty)*sin(Rrotx);
  eerot[8] = cos(Rroty)*cos(Rrotx);
  //std::cout << "Rrotx = " << Rrotx << std::endl;
  //std::cout << "Rroty = " << Rroty << std::endl;
  //std::cout << "Rrotz = " << Rrotz << std::endl;

  //オイラー角　ロボット工学（遠山茂樹著）p25
  //double z_phi;//φ
  //double y_theta;//θ
  //double z_psi;//ψ
  //z_phi = yaw * M_PI / 180;
  //y_theta = pitch * M_PI / 180;
  //z_psi = roll * M_PI / 180;
  //eerot[0] = cos(z_phi)*cos(y_theta)*cos(z_psi)-sin(z_phi)*sin(z_psi);
  //eerot[1] = -cos(z_psi)*cos(y_theta)*sin(z_psi)-sin(z_phi)*cos(z_psi);
  //eerot[2] = cos(z_phi)*sin(y_theta);
  //eerot[3] = sin(z_phi)*cos(y_theta)*cos(z_psi)+cos(z_phi)*sin(z_psi);
  //eerot[4] = -sin(z_phi)*cos(y_theta)*sin(z_psi)+cos(z_phi)*cos(z_psi);
  //eerot[5] = sin(z_phi)*sin(y_theta);
  //eerot[6] = -sin(y_theta)*cos(z_psi);
  //eerot[7] = sin(y_theta)*sin(z_psi);
  //eerot[8] = cos(y_theta);

  // for(int j=0;j<9;j++){
  //  printf("eerot[%d] = %f\n",j,eerot[j]);
  //}
}

/************************************************

        Frame Solve_Rot(double eerot[]);
	
	概要：先端姿勢の回転行列から、ロールピッチヨー[deg]を求める

	引数：
　　　　　　　double eerot[]・・・姿勢行列を格納する配列
                                 |0 1 2|
                                 |3 4 5|
                                 |6 7 8|

	戻り値：姿勢（ロールピッチヨー）

*************************************************/
Frame SeedUpper::Solve_Rot(double eerot[])
{
  Frame rotation;
  double phi;//φ
  double theta;//θ
  double psi;//ψ

  for(int i=0;i<9;i++)
    {
      if(eerot[i]>1)
	eerot[i] = 1;
      if(eerot[i]<-1)
	eerot[i] = -1;
    }

  psi = atan2(eerot[3], eerot[0]);
  theta =  atan2(-eerot[6], sqrt(eerot[7]*eerot[7]+eerot[8]*eerot[8]));
  phi = atan2(eerot[7], eerot[8]);  

  //phi = atan2(eerot[3], eerot[0]);
  //theta =  asin(-eerot[6]);
  //psi = atan2(eerot[7], eerot[8]);  

  rotation.roll = phi*180/M_PI;
  rotation.pitch = theta*180/M_PI;
  rotation.yaw = psi*180/M_PI;

  return rotation;
}


/************************************************

	int Solve_RightArmIk(double eerot[9],double eetrans[3], double elbow,double nowJointPos[], double iksol[])
	
	概要：Seednoid右腕の逆運動学を計算する

	引数：
             double eerot[9]・・・先端姿勢の行列
             double eetrans[3]・・・先端座標(x,y,z)[mm]
             double elbow・・・冗長肘の関節角度
             double nowJointPos・・・現在関節角度
             double iksol[]・・・計算角度を格納する配列

	戻り値：IKが計算できれば0，計算できなければ-1

*************************************************/
int SeedUpper::Solve_RightArmIk(double eerot[9], double eetrans[3], double elbow, double nowJointPos[], double iksol[])
{
  std::cout << "Solve_RightArmIk" << std::endl;
  int ret;
  std::vector<IkReal> free_joint;
  int NumSolutions = 0;
  int phase = 0;
  std::vector<int> LimitSolNum;
  std::vector<std::vector<double> > sol;
  int numSolve = 0;//可動範囲内の解の数
  std::vector<double> min;
  double calceetrans[3];
  LimitSolNum.push_back(1);
  free_joint.push_back(1);
  free_joint[0] = elbow*M_PI/180;
  //free_joint[1] = 0;
  //calceetrans[0] = eerot[0]/1000;
  //calceetrans[1] = eerot[1]/1000;
  //calceetrans[2] = eerot[2]/1000;
  eetrans[0] = eetrans[0]/1000;
  eetrans[1] = eetrans[1]/1000;
  eetrans[2] = eetrans[2]/1000;
  //std::cout << "eetrans[0] = " << eetrans[0] << std::endl;
  //std::cout << "eetrans[1] = " << eetrans[1] << std::endl;
  //std::cout << "eetrans[2] = " << eetrans[2] << std::endl;

  ret = IKFAST_VIRTUAL::right_ik_solve(eerot,eetrans,sol,free_joint,&NumSolutions);
  if(!ret)
    {
      //printf("IK計算完了0~Angle3_LimitMin-1\n");
      for(int k=0;k<NumSolutions;k++)
	{
	  if(sol[k][0]*180/M_PI<Angle1_LimitMax&&sol[k][0]*180/M_PI>Angle1_LimitMin&&
	     sol[k][1]*180/M_PI<Angle2_LimitMax&&sol[k][1]*180/M_PI>Angle2_LimitMin&&
	     sol[k][2]*180/M_PI<Angle3_LimitMax&&sol[k][2]*180/M_PI>Angle3_LimitMin&&
	     sol[k][3]*180/M_PI<Angle4_LimitMax&&sol[k][3]*180/M_PI>Angle4_LimitMin&&
	     sol[k][4]*180/M_PI<Angle5_LimitMax&&sol[k][4]*180/M_PI>Angle5_LimitMin&&
	     sol[k][5]*180/M_PI<Angle6_LimitMax&&sol[k][5]*180/M_PI>Angle6_LimitMin&&
	     sol[k][6]*180/M_PI<Angle7_LimitMax&&sol[k][6]*180/M_PI>Angle7_LimitMin)
	    {
	      LimitSolNum[numSolve] = k;
	      numSolve++;
	    }
	}//end for(int k=0;k<NumSolutions;k++)

      if(numSolve==0){//可動範囲内の解がない
	//std::cout << "与えられた位置姿勢ではIKが解けません(解が可動範囲外)" << std::endl;
	return -1;
      }
      //std::cout << "可動範囲内の解の数は"<<l<<"個"<<std::endl;
    }
  else
    {
      //std::cout << "与えられた位置姿勢ではIKが解けません" << std::endl;
      return -1;
    }
        
      //現在値から近い解を選択する
      int MinAveNum=0;
      int MinAve;
      double diffJointPos[numSolve][7];
      for(int n=0;n<numSolve;n++){
	for(int a=0;a<ARM_FREEDOM;a++){
	  diffJointPos[n][a] = (nowJointPos[a]*M_PI/180) - sol[LimitSolNum[n]][a];
	}//end for(int a=0;a<ARM_FREEDOM;a++)
      }//end for(int n=0;n<l;n++)
      double Average[numSolve];
      for(int av=0;av<numSolve;av++){
	Average[av] = (diffJointPos[av][0] + diffJointPos[av][1] +diffJointPos[av][2] +diffJointPos[av][3] +diffJointPos[av][4] +diffJointPos[av][5] +diffJointPos[av][6])/(ARM_FREEDOM);//ARM_FREEDOM=7
	//Average[av] = fabs(Average[av]);
	//std::cout << "Average["<<av<<"] = "<< Average[av] <<std::endl;  
      }
      //MinAveNum = 0;
      MinAve = Average[0];
      for(int mi=1;mi<numSolve;mi++){
	if(MinAve > Average[mi]){
	  MinAve = Average[mi];
	  MinAveNum = mi;
	}
      }
    
    if(!ret&&LimitSolNum[MinAveNum]!=-1){
      //std::cout << "弧度法の角度[rad]" << std::endl;
      for(int end=0;end<ARM_FREEDOM;end++){
	iksol[end] = sol[LimitSolNum[MinAveNum]][end]*180/M_PI;
	if(end==1){
	  //std::cout << -sol[LimitSolNum[MinAveNum]][end]+M_PI/2 << std::endl;
	}
	else if(end==3){
	  //std::cout << sol[LimitSolNum[MinAveNum]][end]-M_PI/2 << std::endl;
	}
	else{
	  //std::cout << sol[LimitSolNum[MinAveNum]][end]<<std::endl;
	  //std::cout << LimitSolNum[MinAveNum] <<std::endl;
	}
      }
      //std::cout << "IK計算完了" << std::endl;
      return 0;
    }
    else{
      //std::cout << "与えられた位置姿勢ではIKが解けません" << std::endl;
      return -1;
    }  
}


/************************************************

	int Solve_LeftArmIk(double eerot[9],double eetrans[3], double elbow,double nowJointPos[], double iksol[])
	
	概要：Seednoid左腕の逆運動学を計算する

	引数：
             double eerot[9]・・・先端姿勢の行列
             double eetrans[3]・・・先端座標(x,y,z)[mm]
             double elbow・・・冗長肘の関節角度
             double iksol[]・・・計算角度を格納する配列

	戻り値：IKが計算できれば0，計算できなければ-1

*************************************************/
int SeedUpper::Solve_LeftArmIk(double eerot[9],double eetrans[3], double elbow, double nowJointPos[], double iksol[])
{
    std::cout << "Solve_LeftArmIk" << std::endl;
  int ret;
  std::vector<IkReal> free_joint;
  int NumSolutions = 0;
  int phase = 0;
  std::vector<int> LimitSolNum;
  std::vector<std::vector<double> > sol;
  int numSolve = 0;//可動範囲内の解の数
  std::vector<double> min;
  LimitSolNum.push_back(1);
  free_joint.push_back(1);
  free_joint[0] = elbow*M_PI/180;
  //free_joint[1] = 0;
  eetrans[0] = eetrans[0]/1000;
  eetrans[1] = eetrans[1]/1000;
  eetrans[2] = eetrans[2]/1000;

  ret = IKFAST_VIRTUAL::left_ik_solve(eerot,eetrans,sol,free_joint,&NumSolutions);
  if(!ret)
    {
      //printf("IK計算完了0~Angle3_LimitMin-1\n");
      for(int k=0;k<NumSolutions;k++)
	{
	  if(sol[k][0]*180/M_PI<Angle1_LimitMax&&sol[k][0]*180/M_PI>Angle1_LimitMin&&
	     sol[k][1]*180/M_PI<Angle2_LimitMax&&sol[k][1]*180/M_PI>Angle2_LimitMin&&
	     sol[k][2]*180/M_PI<Angle3_LimitMax&&sol[k][2]*180/M_PI>Angle3_LimitMin&&
	     sol[k][3]*180/M_PI<Angle4_LimitMax&&sol[k][3]*180/M_PI>Angle4_LimitMin&&
	     sol[k][4]*180/M_PI<Angle5_LimitMax&&sol[k][4]*180/M_PI>Angle5_LimitMin&&
	     sol[k][5]*180/M_PI<Angle6_LimitMax&&sol[k][5]*180/M_PI>Angle6_LimitMin&&
	     sol[k][6]*180/M_PI<Angle7_LimitMax&&sol[k][6]*180/M_PI>Angle7_LimitMin)
	    {
	      LimitSolNum[numSolve] = k;
	      numSolve++;
	    }
	}//end for(int k=0;k<NumSolutions;k++)

      if(numSolve==0){//可動範囲内の解がない
	//std::cout << "与えられた位置姿勢ではIKが解けません(解が可動範囲外)" << std::endl;
	return -1;
      }
      //std::cout << "可動範囲内の解の数は"<<l<<"個"<<std::endl;
    }
  else
    {
      //std::cout << "与えられた位置姿勢ではIKが解けません" << std::endl;
      return -1;
    }
        
      //現在値から近い解を選択する
      int MinAveNum=0;
      int MinAve;
      double diffJointPos[numSolve][7];
      for(int n=0;n<numSolve;n++){
	for(int a=0;a<ARM_FREEDOM;a++){
	  diffJointPos[n][a] = (nowJointPos[a]*M_PI/180) - sol[LimitSolNum[n]][a];
	}//end for(int a=0;a<ARM_FREEDOM;a++)
      }//end for(int n=0;n<l;n++)
      double Average[numSolve];
      for(int av=0;av<numSolve;av++){
	Average[av] = (diffJointPos[av][0] + diffJointPos[av][1] +diffJointPos[av][2] +diffJointPos[av][3] +diffJointPos[av][4] +diffJointPos[av][5] +diffJointPos[av][6])/(ARM_FREEDOM);//ARM_FREEDOM=7
	//Average[av] = fabs(Average[av]);
	//std::cout << "Average["<<av<<"] = "<< Average[av] <<std::endl;  
      }
      //MinAveNum = 0;
      MinAve = Average[0];
      for(int mi=1;mi<numSolve;mi++){
	if(MinAve > Average[mi]){
	  MinAve = Average[mi];
	  MinAveNum = mi;
	}
      }
    
    if(!ret&&LimitSolNum[MinAveNum]!=-1){
      //std::cout << "弧度法の角度[rad]" << std::endl;
      for(int end=0;end<ARM_FREEDOM;end++){
	iksol[end] = sol[LimitSolNum[MinAveNum]][end]*180/M_PI;
	if(end==1){
	  //std::cout << -sol[LimitSolNum[MinAveNum]][end]+M_PI/2 << std::endl;
	}
	else if(end==3){
	  //std::cout << sol[LimitSolNum[MinAveNum]][end]-M_PI/2 << std::endl;
	}
	else{
	  //std::cout << sol[LimitSolNum[MinAveNum]][end]<<std::endl;
	  //std::cout << LimitSolNum[MinAveNum] <<std::endl;
	}
      }
      //std::cout << "IK計算完了" << std::endl;
      return 0;
    }
    else{
      //std::cout << "与えられた位置姿勢ではIKが解けません" << std::endl;
      return -1;
    }
}


/************************************************

        int Solve_RightArmFK(double eerot[9],double eetrans[3],double joint[])

	概要：Seednoid右腕の順運動学を計算する

	引数：
           　double eerot[]・・・計算した行列を格納する配列
                                 |0 1 2|
                                 |3 4 5|
                                 |6 7 8|
             double eetrans[3]・・・先端座標(x,y,z)が格納される[mm]
             double joint[]・・・入力関節角度を格納する配列

	戻り値：FKが計算できれば0，計算できなければ-1

*************************************************/
int SeedUpper::Solve_RightArmFk(double eerot[9],double eetrans[3],double joint[])
{
  //std::cout << "Solve_RightArmFk" << std::endl;
  double ikjoint[7];
  ikjoint[0] = joint[0]*M_PI/180;
  ikjoint[1] = -joint[1]*M_PI/180+M_PI/2;
  ikjoint[2] = joint[2]*M_PI/180;
  ikjoint[3] = -joint[3]*M_PI/180;
  ikjoint[4] = joint[4]*M_PI/180;
  ikjoint[5] = joint[5]*M_PI/180;
  ikjoint[6] = -joint[6]*M_PI/180; 

  IKFAST_VIRTUAL::ComputeFk(ikjoint,eetrans,eerot);
  //for(int j=0;j<7;j++)
  //  {
  //    std::cout << "right_ik_joint["<<j<<"] = "<<ikjoint[j]<<std::endl;
  //  }
  //for(int i=0;i<9;i++)
  //  {
  //    std::cout << "eerot["<<i<<"] = "<<eerot[i]<<std::endl;
  //  }
  //for(int k=0;k<3;k++)
  //  {
  //  std::cout << "eetrans["<<k<<"] = "<<eetrans[k]<<std::endl;
  //}
  //mmに変換
  eetrans[0] = eetrans[0]*1000;
  eetrans[1] = eetrans[1]*1000;
  eetrans[2] = eetrans[2]*1000;
  
  return 0;
}


/************************************************

        int Solve_LeftArmFK(double eerot[9],double eetrans[3],double joint[])

	概要：Seednoid左腕の順運動学を計算する

	引数：
           　double eerot[]・・・計算した行列を格納する配列
                                 |0 1 2|
                                 |3 4 5|
                                 |6 7 8|
             double eetrans[3]・・・先端座標(x,y,z)が格納される
             double joint[]・・・入力関節角度を格納する配列列

	戻り値：FKが計算できれば0，計算できなければ-1

*************************************************/
int SeedUpper::Solve_LeftArmFk(double eerot[9],double eetrans[3],double joint[])
{

  double ikjoint[7];
  ikjoint[0] = joint[0]*M_PI/180;
  ikjoint[1] = -joint[1]*M_PI/180+M_PI/2;
  ikjoint[2] = -joint[2]*M_PI/180;
  ikjoint[3] = -joint[3]*M_PI/180;
  ikjoint[4] = -joint[4]*M_PI/180;
  ikjoint[5] = joint[5]*M_PI/180;
  ikjoint[6] = -joint[6]*M_PI/180; 

  IKFAST_VIRTUAL::ComputeFk(ikjoint,eetrans,eerot);
  //for(int j=0;j<7;j++)
  //  {
  //    std::cout << "left_ik_joint["<<j<<"] = "<<ikjoint[j]<<std::endl;
  //  }
  //for(int i=0;i<9;i++)
  //  {
  //    std::cout << "eerot["<<i<<"] = "<<eerot[i]<<std::endl;
  //  }
  //for(int k=0;k<3;k++)
  //  {
  //    std::cout << "eetrans["<<k<<"] = "<<eetrans[k]<<std::endl;
  //  }
  //mmに変換
  eetrans[0] = eetrans[0]*1000;
  eetrans[1] = eetrans[1]*1000;
  eetrans[2] = eetrans[2]*1000;
  
  return 0;
}


/************************************************

	int Solve_WRArmIk(double eerot[9], double eetrans[3], double elbow, Frame WaistPos, double nowJointPos[], double iksol[])
	
	概要：Seednoid腰を原点とした右腕の逆運動学を計算する

	引数：
             double eerot[9]・・・先端姿勢の行列
             double eetrans[3]・・・先端座標(x,y,z)
             double elbow・・・冗長肘関節の角度
             Frame WaistPos・・・冗長腰の関節角度
             double nowJointPos[]・・・現在角度
             double iksol[]・・・計算角度を格納する配列

	戻り値：IKが計算できれば0，計算できなければ-1

*************************************************/
int SeedUpper::Solve_WRArmIk(double eerot[9], double eetrans[3], double elbow, Frame WaistPos, double nowJointPos[], double iksol[])
{
  //std::cout << "Solve_WRArmIk" << std::endl;
  double set_eerot[9];
  double set_eetrans[3];
  Frame set_WaistPos;
  double set_virNowJointPos[10];
  double set_reNowJointPos[11];
  double vir_solRightJointPos[10];
  double re_solRightJointPos[11];
  double vir_calcelbow;
  double elbowAbsolute;
  double elbowAbsolute_CalcElbow_a;
  double elbow_a;
  double elbow_a_calcElbow_b;
  double endElbow;
  double nextElbow_a;
  double diffElbow_a;
  double elbow_b;
  int ret;

  for(int i=0;i<9;i++){
    set_eerot[i] = eerot[i];
    //std::cout << "eerot["<<i<<"] = " << set_eerot[i] << std::endl;
  }
  for(int h=0;h<3;h++){
    set_eetrans[h] = eetrans[h];
  }
  for(int j=0;j<10;j++)
    {
      set_virNowJointPos[j] = nowJointPos[j];
    }
  //std::cout << "x = " << set_eetrans[0] << std::endl;
  //std::cout << "y = " << set_eetrans[1] << std::endl;
  //std::cout << "z = " << set_eetrans[2] << std::endl;

  set_WaistPos.roll = WaistPos.roll;
  set_WaistPos.pitch = WaistPos.pitch;
  set_WaistPos.yaw = WaistPos.yaw;

  //solRightJointPos = new IK_RTC::JointPos;
  //solRightJointPos->length(10);
  
  ret = Solve_WRArm_VirtualIk(set_eerot, set_eetrans, elbow, set_WaistPos, nowJointPos, vir_solRightJointPos);
  if(ret!=0)
    {
      //可動範囲外の解
      //std::cout << "可動範囲外の解" << std::endl;
      return -1;
    }

  vir_calcelbow = vir_solRightJointPos[6];
  elbowAbsolute = 0.000000000000491110199391109*pow(vir_calcelbow,6) - 0.00000000039070227836422*pow(vir_calcelbow,5) + 0.000000130488756716618*pow(vir_calcelbow,4) - 0.0000234826686984491*pow(vir_calcelbow,3) + 0.00161963482241845*pow(vir_calcelbow,2) + 0.261403325177525*vir_calcelbow - 0.00665618754283059;

  elbow_a = -0.00000000692890119585732*pow(elbowAbsolute,6) + 0.00000124710103754921*pow(elbowAbsolute,5) - 0.000084428935736014*pow(elbowAbsolute,4) + 0.0031388252882607*pow(elbowAbsolute,3) - 0.0662216643686406*pow(elbowAbsolute,2) + 2.63918264403765*elbowAbsolute + 0.0360316324076848;

  //現在角度をRealElbow変換
    for(int f=0;f<6;f++)
      {
	set_reNowJointPos[f] = nowJointPos[f];
      }
    set_reNowJointPos[6] = -0.00000000692890119585732*pow(elbowAbsolute,6) + 0.00000124710103754921*pow(elbowAbsolute,5) - 0.000084428935736014*pow(elbowAbsolute,4) + 0.0031388252882607*pow(elbowAbsolute,3) - 0.0662216643686406*pow(elbowAbsolute,2) + 2.63918264403765*elbowAbsolute + 0.0360316324076848;
    set_reNowJointPos[7] = 0.0000000459591281663785*pow(elbowAbsolute,6) - 0.00000466502825657855*pow(elbowAbsolute,5) + 0.000185818559202744*pow(elbowAbsolute,4) - 0.00313808415239691*pow(elbowAbsolute,3) + 0.0314923537516734*pow(elbowAbsolute,2) + 1.03307512408355*elbowAbsolute + 0.0815648272255203;
    for(int a=8;a<11;a++)
      {
	set_reNowJointPos[a] = nowJointPos[a-1];
      }

  ret = Solve_WRArm_RealIk(set_eerot,set_eetrans, elbow, elbow_a, set_WaistPos, set_reNowJointPos, re_solRightJointPos);
  if(ret!=0)
    {
      return -1;
    }
  
  elbow_b = re_solRightJointPos[7];
  elbow_a_calcElbow_b = -0.000000000302917143815305*pow(elbow_b,6) + 0.0000000946098533266548*pow(elbow_b,5) - 0.0000120929290741145*pow(elbow_b,4) + 0.000841058161313413*pow(elbow_b,3) - 0.0408098155826337*pow(elbow_b,2) + 2.25577397604502*elbow_b + 0.0983527337011765;

  diffElbow_a = (elbow_a_calcElbow_b - elbow_a)/2;

  nextElbow_a = elbow_a + diffElbow_a;
  //std::cout << "1回目" << std::endl;
  //std::cout << "elbow_a = " << elbow_a << std::endl;
  //std::cout << "elbow_b = " << elbow_b << std::endl;
  //std::cout << "elbow_a_calcElbow_b = " << elbow_a_calcElbow_b << std::endl;
  //std::cout << "diffElbow_a = " << diffElbow_a << std::endl;
  //std::cout << "" << std::endl;
  
  for(int k=0;k<100;k++)
    {
      ret = Solve_WRArm_RealIk(set_eerot,set_eetrans, elbow, nextElbow_a, set_WaistPos, set_reNowJointPos, re_solRightJointPos);
      if(ret!=0)
	{
	  return -1;
	}
      elbow_b = re_solRightJointPos[7];
      elbow_a_calcElbow_b = -0.000000000302917143815305*pow(elbow_b,6) + 0.0000000946098533266548*pow(elbow_b,5) - 0.0000120929290741145*pow(elbow_b,4) + 0.000841058161313413*pow(elbow_b,3) - 0.0408098155826337*pow(elbow_b,2) + 2.25577397604502*elbow_b + 0.0983527337011765;
      
      diffElbow_a = (elbow_a_calcElbow_b - nextElbow_a)/2;
   
      nextElbow_a = nextElbow_a + diffElbow_a;
      //std::cout << "elbow_b = " << elbow_b << std::endl;
      //std::cout << "elbow_a_calcElbow_b = " << elbow_a_calcElbow_b << std::endl;
      //std::cout << "diffElbow_a = " << diffElbow_a << std::endl;
      if(diffElbow_a < 0.001 && diffElbow_a > -0.001)
	{
	  //std::cout << "解が収束" << std::endl;
	  break;
	}
    }

  elbowAbsolute_CalcElbow_a = 0.00000000000446851246055282*pow(nextElbow_a,6) - 0.00000000216929143745381*pow(nextElbow_a,5) + 0.000000491170863536894*pow(nextElbow_a,4) - 0.0000738432952118728*pow(nextElbow_a,3) + 0.00509896918492814*pow(nextElbow_a,2) + 0.368496408573264*nextElbow_a + 0.000472026767965872;

  endElbow = 0.000000043014640453698*pow(elbowAbsolute_CalcElbow_a,6) - 0.00000393656800934394*pow(elbowAbsolute_CalcElbow_a,5) + 0.000126937708159858*pow(elbowAbsolute_CalcElbow_a,4) - 0.000589847731134796*pow(elbowAbsolute_CalcElbow_a,3) - 0.0283161111874506*pow(elbowAbsolute_CalcElbow_a,2) + 3.644187481259*elbowAbsolute_CalcElbow_a + 0.147067213780247;
    
  //for(int g=0;g<11;g++)
  //  {
  //    std::cout << "re_solRightJointPos["<<g<<"] = " << re_solRightJointPos[g] << std::endl;
  //  }
  
  for(int d=0;d<6;d++){
    iksol[d] = re_solRightJointPos[d];
  }
  iksol[6] = endElbow;
  for(int s=7;s<10;s++){
    iksol[s] = re_solRightJointPos[s+1];
  }

  //for(int q=0;q<10;q++)
  //  {
  //    std::cout << "solRightJointPos["<<q<<"] = " << iksol[q] << std::endl;
  //  }
    
  return 0;
}

/************************************************

	int Solve_WLArmIk(double eerot[9], double eetrans[3], double elbow, Frame WaistPos, double nowJointPos[], double iksol[])
	
	概要：Seednoid腰を原点とした左腕の逆運動学を計算する

	引数：
             double eerot[9]・・・先端姿勢の行列
             double eetrans[3]・・・先端座標(x,y,z)
             double elbow・・・冗長肘関節の角度
             Frame WaistPos・・・冗長腰の関節角度
             double nowJointPos[]・・・現在角度
             double iksol[]・・・計算角度を格納する配列

	戻り値：IKが計算できれば0，計算できなければ-1

*************************************************/
int SeedUpper::Solve_WLArmIk(double eerot[9],double eetrans[3], double elbow, Frame WaistPos, double nowJointPos[], double iksol[])
{
  //std::cout << "Solve_WLArmIk" << std::endl;
  double set_eerot[9];
  double set_eetrans[3];
  Frame set_WaistPos;
  double set_virNowJointPos[10];
  double set_reNowJointPos[11];
  double vir_solLeftJointPos[10];
  double re_solLeftJointPos[11];
  double vir_calcelbow;
  double elbowAbsolute;
  double elbowAbsolute_CalcElbow_a;
  double elbow_a;
  double elbow_a_calcElbow_b;
  double endElbow;
  double nextElbow_a;
  double diffElbow_a;
  double elbow_b;
  int ret;

  for(int i=0;i<9;i++){
    set_eerot[i] = eerot[i];
    //std::cout << "eerot["<<i<<"] = " << set_eerot[i] << std::endl;
  }
  for(int h=0;h<3;h++){
    set_eetrans[h] = eetrans[h];
  }
  for(int j=0;j<10;j++)
    {
      set_virNowJointPos[j] = nowJointPos[j];
    }
  //std::cout << "x = " << set_eetrans[0] << std::endl;
  //std::cout << "y = " << set_eetrans[1] << std::endl;
  //std::cout << "z = " << set_eetrans[2] << std::endl;

  set_WaistPos.roll = WaistPos.roll;
  set_WaistPos.pitch = WaistPos.pitch;
  set_WaistPos.yaw = WaistPos.yaw;

  //solLeftJointPos = new IK_RTC::JointPos;
  //solLeftJointPos->length(10);
  
  ret = Solve_WLArm_VirtualIk(set_eerot, set_eetrans, elbow, set_WaistPos, nowJointPos, vir_solLeftJointPos);
  if(ret!=0)
    {
      //可動範囲外の解
      //std::cout << "可動範囲外の解" << std::endl;
      return -1;
    }

  vir_calcelbow = vir_solLeftJointPos[6];
  elbowAbsolute = 0.000000000000491110199391109*pow(vir_calcelbow,6) - 0.00000000039070227836422*pow(vir_calcelbow,5) + 0.000000130488756716618*pow(vir_calcelbow,4) - 0.0000234826686984491*pow(vir_calcelbow,3) + 0.00161963482241845*pow(vir_calcelbow,2) + 0.261403325177525*vir_calcelbow - 0.00665618754283059;

  elbow_a = -0.00000000692890119585732*pow(elbowAbsolute,6) + 0.00000124710103754921*pow(elbowAbsolute,5) - 0.000084428935736014*pow(elbowAbsolute,4) + 0.0031388252882607*pow(elbowAbsolute,3) - 0.0662216643686406*pow(elbowAbsolute,2) + 2.63918264403765*elbowAbsolute + 0.0360316324076848;

  //現在角度をRealElbow変換
    for(int f=0;f<6;f++)
      {
	set_reNowJointPos[f] = nowJointPos[f];
      }
    set_reNowJointPos[6] = -0.00000000692890119585732*pow(elbowAbsolute,6) + 0.00000124710103754921*pow(elbowAbsolute,5) - 0.000084428935736014*pow(elbowAbsolute,4) + 0.0031388252882607*pow(elbowAbsolute,3) - 0.0662216643686406*pow(elbowAbsolute,2) + 2.63918264403765*elbowAbsolute + 0.0360316324076848;
    set_reNowJointPos[7] = 0.0000000459591281663785*pow(elbowAbsolute,6) - 0.00000466502825657855*pow(elbowAbsolute,5) + 0.000185818559202744*pow(elbowAbsolute,4) - 0.00313808415239691*pow(elbowAbsolute,3) + 0.0314923537516734*pow(elbowAbsolute,2) + 1.03307512408355*elbowAbsolute + 0.0815648272255203;
    for(int a=8;a<11;a++)
      {
	set_reNowJointPos[a] = nowJointPos[a-1];
      }

  ret = Solve_WLArm_RealIk(set_eerot,set_eetrans, elbow, elbow_a, set_WaistPos, set_reNowJointPos, re_solLeftJointPos);
  if(ret!=0)
    {
      return -1;
    }
  
  elbow_b = re_solLeftJointPos[7];
  elbow_a_calcElbow_b = -0.000000000302917143815305*pow(elbow_b,6) + 0.0000000946098533266548*pow(elbow_b,5) - 0.0000120929290741145*pow(elbow_b,4) + 0.000841058161313413*pow(elbow_b,3) - 0.0408098155826337*pow(elbow_b,2) + 2.25577397604502*elbow_b + 0.0983527337011765;

  diffElbow_a = (elbow_a_calcElbow_b - elbow_a)/2;

  nextElbow_a = elbow_a + diffElbow_a;
  //std::cout << "1回目" << std::endl;
  //std::cout << "elbow_a = " << elbow_a << std::endl;
  //std::cout << "elbow_b = " << elbow_b << std::endl;
  //std::cout << "elbow_a_calcElbow_b = " << elbow_a_calcElbow_b << std::endl;
  //std::cout << "diffElbow_a = " << diffElbow_a << std::endl;
  //std::cout << "" << std::endl;
  
  for(int k=0;k<100;k++)
    {
      ret = Solve_WLArm_RealIk(set_eerot,set_eetrans, elbow, nextElbow_a, set_WaistPos, set_reNowJointPos, re_solLeftJointPos);
      if(ret!=0)
	{
	  return -1;
	}
      elbow_b = re_solLeftJointPos[7];
      elbow_a_calcElbow_b = -0.000000000302917143815305*pow(elbow_b,6) + 0.0000000946098533266548*pow(elbow_b,5) - 0.0000120929290741145*pow(elbow_b,4) + 0.000841058161313413*pow(elbow_b,3) - 0.0408098155826337*pow(elbow_b,2) + 2.25577397604502*elbow_b + 0.0983527337011765;
      
      diffElbow_a = (elbow_a_calcElbow_b - nextElbow_a)/2;
   
      nextElbow_a = nextElbow_a + diffElbow_a;
      //std::cout << "elbow_b = " << elbow_b << std::endl;
      //std::cout << "elbow_a_calcElbow_b = " << elbow_a_calcElbow_b << std::endl;
      //std::cout << "diffElbow_a = " << diffElbow_a << std::endl;
      if(diffElbow_a < 0.001 && diffElbow_a > -0.001)
	{
	  //std::cout << "解が収束" << std::endl;
	  break;
	}
    }

  elbowAbsolute_CalcElbow_a = 0.00000000000446851246055282*pow(nextElbow_a,6) - 0.00000000216929143745381*pow(nextElbow_a,5) + 0.000000491170863536894*pow(nextElbow_a,4) - 0.0000738432952118728*pow(nextElbow_a,3) + 0.00509896918492814*pow(nextElbow_a,2) + 0.368496408573264*nextElbow_a + 0.000472026767965872;

  endElbow = 0.000000043014640453698*pow(elbowAbsolute_CalcElbow_a,6) - 0.00000393656800934394*pow(elbowAbsolute_CalcElbow_a,5) + 0.000126937708159858*pow(elbowAbsolute_CalcElbow_a,4) - 0.000589847731134796*pow(elbowAbsolute_CalcElbow_a,3) - 0.0283161111874506*pow(elbowAbsolute_CalcElbow_a,2) + 3.644187481259*elbowAbsolute_CalcElbow_a + 0.147067213780247;
    
  //for(int g=0;g<11;g++)
  //  {
  //    std::cout << "re_solLeftJointPos["<<g<<"] = " << re_solLeftJointPos[g] << std::endl;
  //  }
  
  for(int d=0;d<6;d++){
    iksol[d] = re_solLeftJointPos[d];
  }
  iksol[6] = endElbow;
  for(int s=7;s<10;s++){
    iksol[s] = re_solLeftJointPos[s+1];
  }

  //for(int q=0;q<10;q++)
  //  {
  //    std::cout << "solLeftJointPos["<<q<<"] = " << iksol[q] << std::endl;
  //  }
    
  return 0;
}

/************************************************

        int Solve_WRArmFK(double eerot[9],double eetrans[3],double joint[])

	概要：Seednoid腰を原点とした右腕の順運動学を計算する

	引数：
           　double eerot[]・・・計算した行列を格納する配列
                                 |0 1 2|
                                 |3 4 5|
                                 |6 7 8|
             double eetrans[3]・・・先端座標(x,y,z)が格納される[mm]
             double joint[]・・・入力関節角度を格納する配列列

	戻り値：FKが計算できれば0，計算できなければ-1

*************************************************/
int SeedUpper::Solve_WRArmFk(double eerot[9],double eetrans[3], double joint[])
{
  //std::cout << "Solve_WRArmFk" << std::endl;
  double ikjoint[12];
  double calceerot[9];
  double calceetrans[3];
  double elbowAbsolute;
  double elbow;
  double elbow_a;
  double elbow_b;
 
  elbow = joint[6];
  elbowAbsolute = 0.000000000000491110199391109*pow(elbow,6) - 0.00000000039070227836422*pow(elbow,5) + 0.000000130488756716618*pow(elbow,4) - 0.0000234826686984491*pow(elbow,3) + 0.00161963482241845*pow(elbow,2) + 0.261403325177525*elbow - 0.00665618754283059;
  elbow_a = -0.00000000692890119585732*pow(elbowAbsolute,6) + 0.00000124710103754921*pow(elbowAbsolute,5) - 0.000084428935736014*pow(elbowAbsolute,4) + 0.0031388252882607*pow(elbowAbsolute,3) - 0.0662216643686406*pow(elbowAbsolute,2) + 2.63918264403765*elbowAbsolute + 0.0360316324076848;
  elbow_b = 0.0000000459591281663785*pow(elbowAbsolute,6) - 0.00000466502825657855*pow(elbowAbsolute,5) + 0.000185818559202744*pow(elbowAbsolute,4) - 0.00313808415239691*pow(elbowAbsolute,3) + 0.0314923537516734*pow(elbowAbsolute,2) + 1.03307512408355*elbowAbsolute + 0.0815648272255203;
    
  ikjoint[0] = joint[0];
  ikjoint[1] = joint[1];
  ikjoint[2] = joint[2];
  ikjoint[3] = joint[3];
  ikjoint[4] = -0.1745;//仮想10°
  ikjoint[5] = joint[4];
  ikjoint[6] = joint[5];
  ikjoint[7] = elbow_a;
  ikjoint[8] = elbow_b;
  ikjoint[9] = joint[7];
  ikjoint[10] = joint[8];
  ikjoint[11] = joint[9]; 

  Solve_WRArm_RealFk(calceerot,calceetrans,ikjoint);
  
  for(int i=0;i<9;i++)
    {
      eerot[i] = calceerot[i];
    }
  for(int j=0;j<3;j++)
    {
      eetrans[j] = calceetrans[j];
    }

  return 0;
}

/************************************************

        int Solve_WRArmFK(double eerot[9],double eetrans[3],double joint[])

	概要：Seednoid腰を原点とした右腕の順運動学を計算する

	引数：
           　double eerot[]・・・計算した行列を格納する配列
                                 |0 1 2|
                                 |3 4 5|
                                 |6 7 8|
             double eetrans[3]・・・先端座標(x,y,z)が格納される[mm]
             double joint[]・・・入力関節角度を格納する配列列

	戻り値：FKが計算できれば0，計算できなければ-1

*************************************************/
int SeedUpper::Solve_WLArmFk(double eerot[9],double eetrans[3], double joint[])
{
  //std::cout << "Solve_WRArmFk" << std::endl;
  double ikjoint[12];
  double calceerot[9];
  double calceetrans[3];
  double elbowAbsolute;
  double elbow;
  double elbow_a;
  double elbow_b;
 
  elbow = joint[6];
  elbowAbsolute = 0.000000000000491110199391109*pow(elbow,6) - 0.00000000039070227836422*pow(elbow,5) + 0.000000130488756716618*pow(elbow,4) - 0.0000234826686984491*pow(elbow,3) + 0.00161963482241845*pow(elbow,2) + 0.261403325177525*elbow - 0.00665618754283059;
  elbow_a = -0.00000000692890119585732*pow(elbowAbsolute,6) + 0.00000124710103754921*pow(elbowAbsolute,5) - 0.000084428935736014*pow(elbowAbsolute,4) + 0.0031388252882607*pow(elbowAbsolute,3) - 0.0662216643686406*pow(elbowAbsolute,2) + 2.63918264403765*elbowAbsolute + 0.0360316324076848;
  elbow_b = 0.0000000459591281663785*pow(elbowAbsolute,6) - 0.00000466502825657855*pow(elbowAbsolute,5) + 0.000185818559202744*pow(elbowAbsolute,4) - 0.00313808415239691*pow(elbowAbsolute,3) + 0.0314923537516734*pow(elbowAbsolute,2) + 1.03307512408355*elbowAbsolute + 0.0815648272255203;
    
  ikjoint[0] = joint[0];
  ikjoint[1] = joint[1];
  ikjoint[2] = joint[2];
  ikjoint[3] = joint[3];
  ikjoint[4] = 0.1745;//仮想10°
  ikjoint[5] = joint[4];
  ikjoint[6] = joint[5];
  ikjoint[7] = elbow_a;
  ikjoint[8] = elbow_b;
  ikjoint[9] = joint[7];
  ikjoint[10] = joint[8];
  ikjoint[11] = joint[9]; 

  Solve_WLArm_RealFk(calceerot,calceetrans,ikjoint);
  
  for(int i=0;i<9;i++)
    {
      eerot[i] = calceerot[i];
    }
  for(int j=0;j<3;j++)
    {
      eetrans[j] = calceetrans[j];
    }

  return 0;
}

/************************************************

        int Solve_LIWARArmIkSetRedun(double eerot[9],double eetrans[3], double elbow, Frame WaistPos, double lifter[], double nowJointPos[], double iksol[])
	
	概要：Seednoidリフターを原点とした右腕の逆運動学を計算する

	引数：
             double eerot[9]・・・先端姿勢の行列
             double eetrans[3]・・・先端座標(x,y,z)[mm]
             double elbow・・・冗長肘関節の角度
             Frame WaistPos・・・冗長腰の関節角度
             double lifter[]・・・冗長リフターの関節角度
             double nowJointPos[]・・・現在角度
             double iksol[]・・・計算角度を格納する配列

	戻り値：IKが計算できれば0，計算できなければ-1

*************************************************/
int SeedUpper::Solve_LIWARArmIkSetRedun(double eerot[9],double eetrans[3], double elbow, Frame WaistPos, double lifter[], double nowJointPos[], double iksol[])
{
  double eerotInLifter[9];
  double eetransInLifter[3];
  double waistRoll = 0;
  Frame setWaistPos;

  double lifterFkJoint[3];
  lifterFkJoint[0] = lifter[0];
  lifterFkJoint[1] = lifter[1];
  lifterFkJoint[2] = 0;//urdfの余り

  double lifterEEtrans[3];
  Solve_Lifter_Fk(lifterEEtrans,lifterFkJoint);

  //std::cout << "lifterEEtrans[0] = " << lifterEEtrans[0]*1000 << std::endl;
  //std::cout << "lifterEEtrans[1] = " << lifterEEtrans[1]*1000 << std::endl;
  //std::cout << "lifterEEtrans[2] = " << lifterEEtrans[2]*1000 << std::endl;
  
  eerotInLifter[0] = eerot[0];
  eerotInLifter[1] = eerot[1];
  eerotInLifter[2] = eerot[2];
  eerotInLifter[3] = eerot[3];
  eerotInLifter[4] = eerot[4];
  eerotInLifter[5] = eerot[5];
  eerotInLifter[6] = eerot[6];
  eerotInLifter[7] = eerot[7];
  eerotInLifter[8] = eerot[8];
  eetransInLifter[0] = eetrans[0] - lifterEEtrans[0];
  eetransInLifter[1] = eetrans[1] - lifterEEtrans[1];
  eetransInLifter[2] = eetrans[2] - lifterEEtrans[2];
  
  //std::cout << "eetransInLifter[0] = " << eetransInLifter[0] << std::endl;
  //std::cout << "eetransInLifter[1] = " << eetransInLifter[1] << std::endl;
  //std::cout << "eetransInLifter[2] = " << eetransInLifter[2] << std::endl;
      
  setWaistPos.yaw = WaistPos.yaw;
  setWaistPos.pitch = WaistPos.pitch;
  setWaistPos.roll = WaistPos.roll;

  double armIksol[10];
  int ret;
  ret = noid.Solve_WRArmIk(eerotInLifter,eetransInLifter,elbow,setWaistPos,nowJointPos,armIksol);
  if(ret!=0)
    {
      return -1;
    }
  else
    {
      iksol[0] = lifter[0];
      iksol[1] = lifter[1];
      for(int i=0;i<10;i++)
	{
	  iksol[i+2] = armIksol[i];
	}
    }

  return 0;
  
}

/************************************************

        int Solve_LIWALArmIkSetRedun(double eerot[9],double eetrans[3], double elbow, Frame WaistPos, double lifter[], double nowJointPos[], double iksol[])
	
	概要：Seednoidリフターを原点とした左腕の逆運動学を計算する

	引数：
             double eerot[9]・・・先端姿勢の行列
             double eetrans[3]・・・先端座標(x,y,z)[mm]
             double elbow・・・冗長肘関節の角度
             Frame WaistPos・・・冗長腰の関節角度
             double lifter[]・・・冗長リフターの関節角度
             double nowJointPos[]・・・現在角度
             double iksol[]・・・計算角度を格納する配列

	戻り値：IKが計算できれば0，計算できなければ-1

*************************************************/
int SeedUpper::Solve_LIWALArmIkSetRedun(double eerot[9],double eetrans[3], double elbow, Frame WaistPos, double lifter[], double nowJointPos[], double iksol[])
{
  double eerotInLifter[9];
  double eetransInLifter[3];
  double waistRoll = 0;
  Frame setWaistPos;

  double lifterFkJoint[3];
  lifterFkJoint[0] = lifter[0];
  lifterFkJoint[1] = lifter[1];
  lifterFkJoint[2] = 0;//urdfの余り

  double lifterEErot[9];
  double lifterEEtrans[3];
  Solve_Lifter_Fk(lifterEEtrans,lifterFkJoint);

  //std::cout << "lifterEEtrans[0] = " << lifterEEtrans[0]*1000 << std::endl;
  //std::cout << "lifterEEtrans[1] = " << lifterEEtrans[1]*1000 << std::endl;
  //std::cout << "lifterEEtrans[2] = " << lifterEEtrans[2]*1000 << std::endl;
  
  eerotInLifter[0] = eerot[0];
  eerotInLifter[1] = eerot[1];
  eerotInLifter[2] = eerot[2];
  eerotInLifter[3] = eerot[3];
  eerotInLifter[4] = eerot[4];
  eerotInLifter[5] = eerot[5];
  eerotInLifter[6] = eerot[6];
  eerotInLifter[7] = eerot[7];
  eerotInLifter[8] = eerot[8];
  eetransInLifter[0] = eetrans[0] - lifterEEtrans[0];
  eetransInLifter[1] = eetrans[1] - lifterEEtrans[1];
  eetransInLifter[2] = eetrans[2] - lifterEEtrans[2];
  
  //std::cout << "eetransInLifter[0] = " << eetransInLifter[0] << std::endl;
  //std::cout << "eetransInLifter[1] = " << eetransInLifter[1] << std::endl;
  //std::cout << "eetransInLifter[2] = " << eetransInLifter[2] << std::endl;
      
  setWaistPos.yaw = WaistPos.yaw;
  setWaistPos.pitch = WaistPos.pitch;
  setWaistPos.roll = WaistPos.roll;

  double armIksol[10];
  int ret;
  ret = noid.Solve_WLArmIk(eerotInLifter,eetransInLifter,elbow,setWaistPos,nowJointPos,armIksol);
  if(ret!=0)
    {
      return -1;
    }
  else
    {
      iksol[0] = lifter[0];
      iksol[1] = lifter[1];
      for(int i=0;i<10;i++)
	{
	  iksol[i+2] = armIksol[i];
	}
    }

  return 0;
  
}


/************************************************

        int Solve_LIWARArmIk(double eerot[9],double eetrans[3], double nowJointPos[], double iksol[])
	
	概要：Seednoidリフターを原点とした右腕の逆運動学を計算する

	引数：
             double eerot[9]・・・先端姿勢の行列
             double eetrans[3]・・・先端座標(x,y,z)[mm]
             double nowJointPos[]・・・現在角度
             double iksol[]・・・計算角度を格納する配列

	戻り値：IKが計算できれば0，計算できなければ-1

*************************************************/
int SeedUpper::Solve_LIWARArmIk(double eerot[9],double eetrans[3], double nowJointPos[], double iksol[])
{
  double rednowJoint[4];
  rednowJoint[0] = nowJointPos[0];
  rednowJoint[1] = nowJointPos[1];
  rednowJoint[2] = nowJointPos[2];
  rednowJoint[3] = nowJointPos[3];

  double redundancyJoint[4];
  double endEEtrans[3];
  int ret;
  ret = redun.getRightRedundantJoint(eerot,eetrans,rednowJoint,redundancyJoint,endEEtrans);
  if(ret)
    {
      return -1;
    }

  Frame WaistPos;
  WaistPos.yaw = redundancyJoint[2];
  WaistPos.pitch = redundancyJoint[3];
  WaistPos.roll = 0;

  double setNowJointPos[10];
  for(int l=0;l<10;l++){
    setNowJointPos[l] = nowJointPos[l+2];
  }

  
  double elbow = 0;
  double armIksol[10];
  ret = noid.Solve_WRArmIk(eerot,endEEtrans,elbow,WaistPos,setNowJointPos,armIksol);
  if(ret)
    {
      return -1;
    }
  
  iksol[0] = redundancyJoint[0];
  iksol[1] = redundancyJoint[1];
  for(int i=0;i<10;i++)
    {
      iksol[i+2] = armIksol[i];
    }

  return 0;
}

/************************************************

        int Solve_LIWALArmIk(double eerot[9],double eetrans[3], double nowJointPos[], double iksol[])
	
	概要：Seednoidリフターを原点とした左腕の逆運動学を計算する

	引数：
             double eerot[9]・・・先端姿勢の行列
             double eetrans[3]・・・先端座標(x,y,z)[mm]
             double nowJointPos[]・・・現在角度
             double iksol[]・・・計算角度を格納する配列

	戻り値：IKが計算できれば0，計算できなければ-1

*************************************************/
int SeedUpper::Solve_LIWALArmIk(double eerot[9],double eetrans[3], double nowJointPos[], double iksol[])
{
  double rednowJoint[4];
  rednowJoint[0] = nowJointPos[0];
  rednowJoint[1] = nowJointPos[1];
  rednowJoint[2] = nowJointPos[2];
  rednowJoint[3] = nowJointPos[3];

  double redundancyJoint[4];
  double endEEtrans[3];
  int ret;
  //左
  ret = redun.getLeftRedundantJoint(eerot,eetrans,rednowJoint,redundancyJoint,endEEtrans);
  if(ret)
    {
      return -1;
    }

  Frame WaistPos;
  WaistPos.yaw = redundancyJoint[2];
  WaistPos.pitch = redundancyJoint[3];
  WaistPos.roll = 0;

  double setNowJointPos[10];
  for(int l=0;l<10;l++){
    setNowJointPos[l] = nowJointPos[l+2];
  }

  
  double elbow = 0;
  double armIksol[10];
  ret = noid.Solve_WLArmIk(eerot,endEEtrans,elbow,WaistPos,setNowJointPos,armIksol);
  if(ret)
    {
      return -1;
    }
  
  iksol[0] = redundancyJoint[0];
  iksol[1] = redundancyJoint[1];
  for(int i=0;i<10;i++)
    {
      iksol[i+2] = armIksol[i];
    }

  return 0;
}


/************************************************

        int Solve_LIWARArmFk(double eerot[9],double eetrans[3], double joint[])

	概要：Seednoidリフターを原点とした右腕の順運動学を計算する

	引数：
           　double eerot[]・・・計算した行列を格納する配列
                                 |0 1 2|
                                 |3 4 5|
                                 |6 7 8|
             double eetrans[3]・・・先端座標(x,y,z)が格納される[mm]
             double joint[]・・・入力関節角度を格納する配列

	戻り値：FKが計算できれば0，計算できなければ-1

*************************************************/
int SeedUpper::Solve_LIWARArmFk(double eerot[9],double eetrans[3], double joint[])
{
  double lifterFkJoint[3];
  lifterFkJoint[0] = joint[0];
  lifterFkJoint[1] = joint[1];
  lifterFkJoint[2] = 0;//urdfの余り

  double lifterEEtrans[3];
  Solve_Lifter_Fk(lifterEEtrans,lifterFkJoint);

  double setWRJoint[10];
  for(int i=0;i<10;i++)
    {
      setWRJoint[i] = joint[i+2];
    }
  double Righteerot[9];
  double Righteetrans[3];
  noid.Solve_WRArmFk(Righteerot,Righteetrans,setWRJoint);

  for(int i=0;i<9;i++)
    {
      eerot[i] = Righteerot[i];
    }
  eetrans[0] = Righteetrans[0] + lifterEEtrans[0];
  eetrans[1] = Righteetrans[1] + lifterEEtrans[1];
  eetrans[2] = Righteetrans[2] + lifterEEtrans[2];

}


/************************************************

        int Solve_LIWALArmFk(double eerot[9],double eetrans[3], double joint[])

	概要：Seednoidリフターを原点とした左腕の順運動学を計算する

	引数：
           　double eerot[]・・・計算した行列を格納する配列
                                 |0 1 2|
                                 |3 4 5|
                                 |6 7 8|
             double eetrans[3]・・・先端座標(x,y,z)が格納される[mm]
             double joint[]・・・入力関節角度を格納する配列

	戻り値：FKが計算できれば0，計算できなければ-1

*************************************************/
int SeedUpper::Solve_LIWALArmFk(double eerot[9],double eetrans[3], double joint[])
{
  double lifterFkJoint[3];
  lifterFkJoint[0] = joint[0];
  lifterFkJoint[1] = joint[1];
  lifterFkJoint[2] = 0;//urdfの余り

  double lifterEEtrans[3];
  Solve_Lifter_Fk(lifterEEtrans,lifterFkJoint);

  double setWRJoint[10];
  for(int i=0;i<10;i++)
    {
      setWRJoint[i] = joint[i+2];
    }
  double Righteerot[9];
  double Righteetrans[3];
  noid.Solve_WLArmFk(Righteerot,Righteetrans,setWRJoint);

  for(int i=0;i<9;i++)
    {
      eerot[i] = Righteerot[i];
    }
  eetrans[0] = Righteetrans[0] + lifterEEtrans[0];
  eetrans[1] = Righteetrans[1] + lifterEEtrans[1];
  eetrans[2] = Righteetrans[2] + lifterEEtrans[2];

}

/************************************************

        int Solve_Lifter_Fk(double eerot[9],double eetrans[3], double joint[])

	概要：Seednoidリフターの順運動学を計算する

	引数：
             double eetrans[3]・・・先端座標(x,y,z)が格納される[mm]
             double joint[]・・・入力関節角度を格納する配列 0~85 と 0~85

	戻り値：FKが計算できれば0，計算できなければ-1

*************************************************/
int SeedUpper::Solve_Lifter_Fk(double eetrans[3], double joint[])
{
  double calcJoint[2];
  calcJoint[0] = -joint[0];
  calcJoint[1] = joint[1];
  
  eetrans[0] = LIFTER_L1*cos(M_PI/2+(-calcJoint[0]*M_PI/180)) + LIFTER_L2*cos(M_PI/2+(-calcJoint[1]*M_PI/180));
  eetrans[1] = 0;
  eetrans[2] = (MOBILE_LIFTER_Z) + LIFTER_L1*sin(M_PI/2+(-calcJoint[0]*M_PI/180)) + LIFTER_L2*sin(M_PI/2+(-calcJoint[1]*M_PI/180));
}


//以下IK FK private関数




/************************************************

        int Solve_WRArm_VirtualIk(double eerot[9], double eetrans[3], double elbow, Frame WaistPos, double nowJointPos[], double iksol[])
	
	概要：Seednoid腰を原点とした左腕の逆運動学を計算する

	引数：
             double eerot[9]・・・先端姿勢の行列
             double eetrans[3]・・・先端座標(x,y,z)[mm]
             double elbow・・・冗長肘関節の角度
             Frame WaistPos・・・冗長腰の関節角度
             double nowJointPos[]・・・現在角度
             double iksol[]・・・計算角度を格納する配列

	戻り値：IKが計算できれば0，計算できなければ-1

*************************************************/
int SeedUpper::Solve_WRArm_VirtualIk(double eerot[9], double eetrans[3], double elbow, Frame WaistPos, double nowJointPos[], double iksol[])
{
  //std::cout << "Solve_WRArm_VirtualIk" << std::endl;
  int ret; 
  double sol_eerot[9];
  double sol_eetrans[3];
  std::vector<IkReal> free_joint(IKFAST_WR_VIRTUAL::GetNumFreeParameters());
  int NumSolutions = 0;
  int phase = 0;
  std::vector<int> LimitSolNum;
  std::vector<std::vector<double> > sol;
  int numSolve = 0;//可動範囲内の解の数
  std::vector<double> min;
  LimitSolNum.push_back(-1);
  free_joint[0] = WaistPos.yaw*M_PI/180;
  free_joint[1] = WaistPos.pitch*M_PI/180;
  free_joint[2] = WaistPos.roll*M_PI/180;
  free_joint[3] = -0.1745;//仮想10°
  free_joint[4] = elbow*M_PI/180;

  Eigen::MatrixXd Target_Mat(4,4);
  Eigen::MatrixXd WristHand_Mat(4,4);
  Eigen::MatrixXd IKFAST_InMat(4,4);
    
  Target_Mat(0,0)=eerot[0];
  Target_Mat(0,1)=eerot[1];
  Target_Mat(0,2)=eerot[2];
  Target_Mat(1,0)=eerot[3];
  Target_Mat(1,1)=eerot[4];
  Target_Mat(1,2)=eerot[5];
  Target_Mat(2,0)=eerot[6];
  Target_Mat(2,1)=eerot[7];
  Target_Mat(2,2)=eerot[8];
  Target_Mat(0,3)=eetrans[0]/1000;//x
  Target_Mat(1,3)=eetrans[1]/1000;//y
  Target_Mat(2,3)=eetrans[2]/1000;//z
  Target_Mat(3,0)=0;
  Target_Mat(3,1)=0;
  Target_Mat(3,2)=0;
  Target_Mat(3,3)=1.0;

  WristHand_Mat(0,0) = 1;
  WristHand_Mat(0,1) = 0;
  WristHand_Mat(0,2) = 0;
  WristHand_Mat(1,0) = 0;
  WristHand_Mat(1,1) = 1;
  WristHand_Mat(1,2) = 0;
  WristHand_Mat(2,0) = 0;
  WristHand_Mat(2,1) = 0;
  WristHand_Mat(2,2) = 1;
  WristHand_Mat(0,3) = 0;//x
  WristHand_Mat(1,3) = -0.0964;//y
  WristHand_Mat(2,3) = -0.0296;//z
  WristHand_Mat(3,0)=0;
  WristHand_Mat(3,1)=0;
  WristHand_Mat(3,2)=0;
  WristHand_Mat(3,3) = 1.0;

  IKFAST_InMat = Target_Mat * WristHand_Mat.inverse();

  sol_eerot[0] = IKFAST_InMat(0,0);
  sol_eerot[1] = IKFAST_InMat(0,1);
  sol_eerot[2] = IKFAST_InMat(0,2);
  sol_eerot[3] = IKFAST_InMat(1,0);
  sol_eerot[4] = IKFAST_InMat(1,1);
  sol_eerot[5] = IKFAST_InMat(1,2);
  sol_eerot[6] = IKFAST_InMat(2,0);
  sol_eerot[7] = IKFAST_InMat(2,1);
  sol_eerot[8] = IKFAST_InMat(2,2);
  sol_eetrans[0] = IKFAST_InMat(0,3);
  sol_eetrans[1] = IKFAST_InMat(1,3);
  sol_eetrans[2] = IKFAST_InMat(2,3);

  /*
  for(int i=0;i<9;i++){
    std::cout << "sol_eerot["<<i<<"] = " << sol_eerot[i] << std::endl;
  }
  std::cout << "x = " << sol_eetrans[0] << std::endl;
  std::cout << "y = " << sol_eetrans[1] << std::endl;
  std::cout << "z = " << sol_eetrans[2] << std::endl;
  */
  ret = IKFAST_WR_VIRTUAL::ik_solve(sol_eerot,sol_eetrans,sol,free_joint,&NumSolutions);
  if(!ret)
    {
      //printf("IK計算完了0~Angle3_LimitMin-1\n");
      for(int k=0;k<NumSolutions;k++)
	{
	  if(sol[k][0]*180/M_PI<WaistYaw_LimitMax&&sol[k][0]*180/M_PI>WaistYaw_LimitMin&&
	     sol[k][1]*180/M_PI<WaistPitch_LimitMax&&sol[k][1]*180/M_PI>WaistPitch_LimitMin&&
	     sol[k][2]*180/M_PI<WaistRoll_LimitMax&&sol[k][2]*180/M_PI>WaistRoll_LimitMin&&
	     sol[k][3]*180/M_PI<Angle1_LimitMax&&sol[k][3]*180/M_PI>Angle1_LimitMin&&
	     sol[k][4]*180/M_PI<Angle2_LimitMax&&sol[k][4]*180/M_PI>Angle2_LimitMin&&
	     sol[k][5]*180/M_PI<Angle3_LimitMax&&sol[k][5]*180/M_PI>Angle3_LimitMin&&
	     sol[k][6]*180/M_PI<Angle4_LimitMax&&sol[k][6]*180/M_PI>Angle4_LimitMin&&
	     sol[k][7]*180/M_PI<Angle5_LimitMax&&sol[k][7]*180/M_PI>Angle5_LimitMin&&
	     sol[k][8]*180/M_PI<Angle6_LimitMax&&sol[k][8]*180/M_PI>Angle6_LimitMin&&
	     sol[k][9]*180/M_PI<Angle7_LimitMax&&sol[k][9]*180/M_PI>Angle7_LimitMin)
	    {
	      LimitSolNum[numSolve] = k;
	      numSolve++;
	      phase = 2;
	    }
	}//end for(int k=0;k<NumSolutions;k++)

      if(numSolve==0){//可動範囲内の解がない
	//std::cout << "与えられた位置姿勢ではIKが解けません(解が可動範囲外)" << std::endl;
	return -1;
      }
      //std::cout << "可動範囲内の解の数は"<<l<<"個"<<std::endl;
    }
  else
    {
      //std::cout << "与えられた位置姿勢ではIKが解けません" << std::endl;
      return -1;
    }
  /*
  for(int nn=0;nn<numSolve;nn++){
    for(int aa=0;aa<ARM_FREEDOM+3;aa++){
      std::cout << "RightJointPos["<<nn<<"]["<<aa<<"] = " << sol[LimitSolNum[nn]][aa]*180/M_PI << std::endl;
    }
  }
  for(int now=0;now<10;now++)
    {
      std::cout << "RightNowPos["<<now<<"] = " << nowJointPos[now] << std::endl;
    }
  */
  //現在値から近い解を選択する
  int MinAveNum=0;
  double MinAve;
  double diffJointPos[numSolve][10];
  if(phase == 2){
    double diffJointPos[numSolve][10];
    for(int n=0;n<numSolve;n++){
      for(int a=0;a<ARM_FREEDOM+3;a++){
	diffJointPos[n][a] = fabs((nowJointPos[a]*M_PI/180) - sol[LimitSolNum[n]][a]);
	//std::cout << "diffJointPos["<<n<<"]["<<a<<"] = " << diffJointPos[n][a] << std::endl;
      }//end for(int a=0;a<ARM_FREEDOM;a++)
    }//end for(int n=0;n<l;n++)
    double Average[numSolve];
    for(int av=0;av<numSolve;av++){
      Average[av] = (diffJointPos[av][0] + diffJointPos[av][1] + diffJointPos[av][2] + diffJointPos[av][3] + diffJointPos[av][4] + diffJointPos[av][5] + diffJointPos[av][6] + diffJointPos[av][7] + diffJointPos[av][8] + diffJointPos[av][9])/(ARM_FREEDOM+3);//ARM_FREEDOM=7
      //Average[av] = fabs(Average[av]);
      //std::cout << "Average["<<av<<"] = "<< Average[av] <<std::endl;  
    }
    //MinAveNum = 0;
    MinAve = Average[0];
    for(int mi=1;mi<numSolve;mi++){
      if(MinAve > Average[mi]){
	MinAve = Average[mi];
	MinAveNum = mi;
      }
    }
    //std::cout << "MinAveNum = " << MinAveNum << std::endl;
  }//end if(phase == 2)
    
  if(!ret&&LimitSolNum[MinAveNum]!=-1){
    //std::cout << "弧度法の角度[rad]" << std::endl;
    for(int end=0;end<ARM_FREEDOM+3;end++){
      iksol[end] = sol[LimitSolNum[MinAveNum]][end]*180/M_PI;
      /*
	if(end==4){
	std::cout << -sol[LimitSolNum[MinAveNum]][end]+M_PI/2 << std::endl;
	}
	else if(end==5){
	std::cout << -sol[LimitSolNum[MinAveNum]][end] << std::endl;
	}
	else if(end==7){
	std::cout << -sol[LimitSolNum[MinAveNum]][end] << std::endl;
	}
	else if(end==8){
	std::cout << -sol[LimitSolNum[MinAveNum]][end] << std::endl;
	}
	else if(end==9){
	std::cout << -sol[LimitSolNum[MinAveNum]][end] << std::endl;
	}
	else{
	std::cout << sol[LimitSolNum[MinAveNum]][end]<<std::endl;
	//std::cout << LimitSolNum[MinAveNum] <<std::endl;
	}
      */
    }
    //std::cout << "IK計算完了" << std::endl;
    return 0;
  }
  else{
    //std::cout << "与えられた位置姿勢ではIKが解けません" << std::endl;
    return -1;
  }  
}

/************************************************

        int Solve_WLArm_VirtualIk(double eerot[9], double eetrans[3], double elbow, Frame WaistPos, double nowJointPos[], double iksol[])
	
	概要：Seednoid腰を原点とした左腕の逆運動学を計算する

	引数：
             double eerot[9]・・・先端姿勢の行列
             double eetrans[3]・・・先端座標(x,y,z)[mm]
             double elbow・・・冗長肘関節の角度
             Frame WaistPos・・・冗長腰の関節角度
             double nowJointPos[]・・・現在角度
             double iksol[]・・・計算角度を格納する配列

	戻り値：IKが計算できれば0，計算できなければ-1

*************************************************/
int SeedUpper::Solve_WLArm_VirtualIk(double eerot[9],double eetrans[3], double elbow, Frame WaistPos, double nowJointPos[], double iksol[])
{
  //std::cout << "Solve_WLArm_VirtualIk" << std::endl;
  int ret; 
  double sol_eerot[9];
  double sol_eetrans[3];
  std::vector<IkReal> free_joint(IKFAST_WR_VIRTUAL::GetNumFreeParameters());
  int NumSolutions = 0;
  int phase = 0;
  std::vector<int> LimitSolNum;
  std::vector<std::vector<double> > sol;
  int numSolve = 0;//可動範囲内の解の数
  std::vector<double> min;
  LimitSolNum.push_back(-1);
  free_joint[0] = WaistPos.yaw*M_PI/180;
  free_joint[1] = WaistPos.pitch*M_PI/180;
  free_joint[2] = WaistPos.roll*M_PI/180;
  free_joint[3] = 0.1745;//仮想10°
  free_joint[4] = elbow*M_PI/180;

  Eigen::MatrixXd Target_Mat(4,4);
  Eigen::MatrixXd WristHand_Mat(4,4);
  Eigen::MatrixXd IKFAST_InMat(4,4);
    
  Target_Mat(0,0)=eerot[0];
  Target_Mat(0,1)=eerot[1];
  Target_Mat(0,2)=eerot[2];
  Target_Mat(1,0)=eerot[3];
  Target_Mat(1,1)=eerot[4];
  Target_Mat(1,2)=eerot[5];
  Target_Mat(2,0)=eerot[6];
  Target_Mat(2,1)=eerot[7];
  Target_Mat(2,2)=eerot[8];
  Target_Mat(0,3)=eetrans[0]/1000;//x
  Target_Mat(1,3)=eetrans[1]/1000;//y
  Target_Mat(2,3)=eetrans[2]/1000;//z
  Target_Mat(3,0)=0;
  Target_Mat(3,1)=0;
  Target_Mat(3,2)=0;
  Target_Mat(3,3)=1.0;

  WristHand_Mat(0,0) = 1;
  WristHand_Mat(0,1) = 0;
  WristHand_Mat(0,2) = 0;
  WristHand_Mat(1,0) = 0;
  WristHand_Mat(1,1) = 1;
  WristHand_Mat(1,2) = 0;
  WristHand_Mat(2,0) = 0;
  WristHand_Mat(2,1) = 0;
  WristHand_Mat(2,2) = 1;
  WristHand_Mat(0,3) = 0;//x
  WristHand_Mat(1,3) = 0.0964;//y
  WristHand_Mat(2,3) = -0.0296;//z
  WristHand_Mat(3,0)=0;
  WristHand_Mat(3,1)=0;
  WristHand_Mat(3,2)=0;
  WristHand_Mat(3,3) = 1.0;

  IKFAST_InMat = Target_Mat * WristHand_Mat.inverse();

  sol_eerot[0] = IKFAST_InMat(0,0);
  sol_eerot[1] = IKFAST_InMat(0,1);
  sol_eerot[2] = IKFAST_InMat(0,2);
  sol_eerot[3] = IKFAST_InMat(1,0);
  sol_eerot[4] = IKFAST_InMat(1,1);
  sol_eerot[5] = IKFAST_InMat(1,2);
  sol_eerot[6] = IKFAST_InMat(2,0);
  sol_eerot[7] = IKFAST_InMat(2,1);
  sol_eerot[8] = IKFAST_InMat(2,2);
  sol_eetrans[0] = IKFAST_InMat(0,3);
  sol_eetrans[1] = IKFAST_InMat(1,3);
  sol_eetrans[2] = IKFAST_InMat(2,3);

  ret = IKFAST_WL_VIRTUAL::ik_solve(sol_eerot,sol_eetrans,sol,free_joint,&NumSolutions);
  if(!ret)
    {
      //printf("IK計算完了0~Angle3_LimitMin-1\n");
      for(int k=0;k<NumSolutions;k++)
	{
	  if(sol[k][0]*180/M_PI<WaistYaw_LimitMax&&sol[k][0]*180/M_PI>WaistYaw_LimitMin&&
	     sol[k][1]*180/M_PI<WaistPitch_LimitMax&&sol[k][1]*180/M_PI>WaistPitch_LimitMin&&
	     sol[k][2]*180/M_PI<WaistRoll_LimitMax&&sol[k][2]*180/M_PI>WaistRoll_LimitMin&&
	     sol[k][3]*180/M_PI<Angle1_LimitMax&&sol[k][3]*180/M_PI>Angle1_LimitMin&&
	     sol[k][4]*180/M_PI<Angle2_LimitMax&&sol[k][4]*180/M_PI>Angle2_LimitMin&&
	     sol[k][5]*180/M_PI<Angle3_LimitMax&&sol[k][5]*180/M_PI>Angle3_LimitMin&&
	     sol[k][6]*180/M_PI<Angle4_LimitMax&&sol[k][6]*180/M_PI>Angle4_LimitMin&&
	     sol[k][7]*180/M_PI<Angle5_LimitMax&&sol[k][7]*180/M_PI>Angle5_LimitMin&&
	     sol[k][8]*180/M_PI<Angle6_LimitMax&&sol[k][8]*180/M_PI>Angle6_LimitMin&&
	     sol[k][9]*180/M_PI<Angle7_LimitMax&&sol[k][9]*180/M_PI>Angle7_LimitMin)
	    {
	      LimitSolNum[numSolve] = k;
	      numSolve++;
	    }
	}//end for(int k=0;k<NumSolutions;k++)

      if(numSolve==0){//可動範囲内の解がない
	//std::cout << "与えられた位置姿勢ではIKが解けません(解が可動範囲外)" << std::endl;
	return -1;
      }
      //std::cout << "可動範囲内の解の数は"<<l<<"個"<<std::endl;
    }
  else
    {
      //std::cout << "与えられた位置姿勢ではIKが解けません" << std::endl;
      return -1;
    }

  //for(int nn=0;nn<numSolve;nn++){
  //  for(int aa=0;aa<ARM_FREEDOM+3;aa++){
  //    std::cout << "RightJointPos["<<nn<<"]["<<aa<<"] = " << sol[LimitSolNum[nn]][aa]*180/M_PI << std::endl;
  //  }
  //}
  //for(int now=0;now<10;now++)
  //  {
  //    std::cout << "RightNowPos["<<now<<"] = " << nowJointPos[now] << std::endl;
  //  }
    
  //現在値から近い解を選択する
  int MinAveNum=0;
  double MinAve;
  double diffJointPos[numSolve][10];
  if(phase == 2){
    double diffJointPos[numSolve][10];
    for(int n=0;n<numSolve;n++){
      for(int a=0;a<ARM_FREEDOM+3;a++){
	diffJointPos[n][a] = fabs((nowJointPos[a]*M_PI/180) - sol[LimitSolNum[n]][a]);
	//std::cout << "diffJointPos["<<n<<"]["<<a<<"] = " << diffJointPos[n][a] << std::endl;
      }//end for(int a=0;a<ARM_FREEDOM;a++)
    }//end for(int n=0;n<l;n++)
    double Average[numSolve];
    for(int av=0;av<numSolve;av++){
      Average[av] = (diffJointPos[av][0] + diffJointPos[av][1] + diffJointPos[av][2] + diffJointPos[av][3] + diffJointPos[av][4] + diffJointPos[av][5] + diffJointPos[av][6] + diffJointPos[av][7] + diffJointPos[av][8] + diffJointPos[av][9])/(ARM_FREEDOM+3);//ARM_FREEDOM=7
      //Average[av] = fabs(Average[av]);
      //std::cout << "Average["<<av<<"] = "<< Average[av] <<std::endl;  
    }
    //MinAveNum = 0;
    MinAve = Average[0];
    for(int mi=1;mi<numSolve;mi++){
      if(MinAve > Average[mi]){
	MinAve = Average[mi];
	MinAveNum = mi;
      }
    }
    //std::cout << "MinAveNum = " << MinAveNum << std::endl;
  }//end if(phase == 2)
    
  if(!ret&&LimitSolNum[MinAveNum]!=-1){
    //std::cout << "弧度法の角度[rad]" << std::endl;
    for(int end=0;end<ARM_FREEDOM+3;end++){
      iksol[end] = sol[LimitSolNum[MinAveNum]][end]*180/M_PI;
      /*
	if(end==4){
	std::cout << -sol[LimitSolNum[MinAveNum]][end]+M_PI/2 << std::endl;
	}
	else if(end==5){
	std::cout << -sol[LimitSolNum[MinAveNum]][end] << std::endl;
	}
	else if(end==7){
	std::cout << -sol[LimitSolNum[MinAveNum]][end] << std::endl;
	}
	else if(end==8){
	std::cout << -sol[LimitSolNum[MinAveNum]][end] << std::endl;
	}
	else if(end==9){
	std::cout << -sol[LimitSolNum[MinAveNum]][end] << std::endl;
	}
	else{
	std::cout << sol[LimitSolNum[MinAveNum]][end]<<std::endl;
	//std::cout << LimitSolNum[MinAveNum] <<std::endl;
	}
      */
    }
    //std::cout << "IK計算完了" << std::endl;
    return 0;
  }
  else{
    //std::cout << "与えられた位置姿勢ではIKが解けません" << std::endl;
    return -1;
  }  
}

/************************************************

        int Solve_WRArm_RealIk(double eerot[9], double eetrans[3], double elbow, Frame WaistPos, double nowJointPos[], double iksol[])
	
	概要：Seednoid腰を原点とした右腕の逆運動学を計算する

	引数：
             double eerot[9]・・・先端姿勢の行列
             double eetrans[3]・・・先端座標(x,y,z)[mm]
             double elbow・・・冗長肘関節の角度
             double elbow_a・・・肘の2関節の手前側の関節角度
             Frame WaistPos・・・冗長腰の関節角度
             double nowJointPos[]・・・現在角度
             double iksol[]・・・計算角度を格納する配列

	戻り値：IKが計算できれば0，計算できなければ-1

*************************************************/
int SeedUpper::Solve_WRArm_RealIk(double eerot[9],double eetrans[3], double elbow, double elbow_a, Frame WaistPos, double nowJointPos[], double iksol[])
{
  //std::cout << "Solve_WRArm_RealIk" << std::endl;
  int ret; 
  double sol_eerot[9];
  double sol_eetrans[3];
  std::vector<IkReal> free_joint(IKFAST_WR_REAL::GetNumFreeParameters());
  int NumSolutions = 0;
  int phase = 0;
  std::vector<int> LimitSolNum;
  std::vector<std::vector<double> > sol;
  int numSolve = 0;//可動範囲内の解の数
  std::vector<double> min;
  LimitSolNum.push_back(-1);
  free_joint[0] = WaistPos.yaw*M_PI/180;
  free_joint[1] = WaistPos.pitch*M_PI/180;
  free_joint[2] = WaistPos.roll*M_PI/180;
  free_joint[3] = -0.1745;//仮想10°
  free_joint[4] = elbow*M_PI/180;
  free_joint[5] = elbow_a*M_PI/180;

  Eigen::MatrixXd Target_Mat(4,4);
  Eigen::MatrixXd WristHand_Mat(4,4);
  Eigen::MatrixXd IKFAST_InMat(4,4);
 
  //for(int i=0;i<9;i++){
  //  std::cout << "eerot["<<i<<"] = " << eerot[i] << std::endl;
  //}
  //std::cout << "x = " << eetrans[0] << std::endl;
  //std::cout << "y = " << eetrans[1] << std::endl;
  //std::cout << "z = " << eetrans[2] << std::endl;
  
  Target_Mat(0,0)=eerot[0];
  Target_Mat(0,1)=eerot[1];
  Target_Mat(0,2)=eerot[2];
  Target_Mat(1,0)=eerot[3];
  Target_Mat(1,1)=eerot[4];
  Target_Mat(1,2)=eerot[5];
  Target_Mat(2,0)=eerot[6];
  Target_Mat(2,1)=eerot[7];
  Target_Mat(2,2)=eerot[8];
  Target_Mat(0,3)=eetrans[0]/1000;//x
  Target_Mat(1,3)=eetrans[1]/1000;//y
  Target_Mat(2,3)=eetrans[2]/1000;//z
  Target_Mat(3,0)=0;
  Target_Mat(3,1)=0;
  Target_Mat(3,2)=0;
  Target_Mat(3,3)=1.0;

  WristHand_Mat(0,0) = 1;
  WristHand_Mat(0,1) = 0;
  WristHand_Mat(0,2) = 0;
  WristHand_Mat(1,0) = 0;
  WristHand_Mat(1,1) = 1;
  WristHand_Mat(1,2) = 0;
  WristHand_Mat(2,0) = 0;
  WristHand_Mat(2,1) = 0;
  WristHand_Mat(2,2) = 1;
  WristHand_Mat(0,3) = 0;//x
  WristHand_Mat(1,3) = -0.0964;//y
  WristHand_Mat(2,3) = -0.0296;//z
  WristHand_Mat(3,0)=0;
  WristHand_Mat(3,1)=0;
  WristHand_Mat(3,2)=0;
  WristHand_Mat(3,3) = 1.0;

  IKFAST_InMat = Target_Mat * WristHand_Mat.inverse();

  sol_eerot[0] = IKFAST_InMat(0,0);
  sol_eerot[1] = IKFAST_InMat(0,1);
  sol_eerot[2] = IKFAST_InMat(0,2);
  sol_eerot[3] = IKFAST_InMat(1,0);
  sol_eerot[4] = IKFAST_InMat(1,1);
  sol_eerot[5] = IKFAST_InMat(1,2);
  sol_eerot[6] = IKFAST_InMat(2,0);
  sol_eerot[7] = IKFAST_InMat(2,1);
  sol_eerot[8] = IKFAST_InMat(2,2);
  sol_eetrans[0] = IKFAST_InMat(0,3);
  sol_eetrans[1] = IKFAST_InMat(1,3);
  sol_eetrans[2] = IKFAST_InMat(2,3);

  //std::cout << "Target_Mat" << std::endl;
  //std::cout << Target_Mat << std::endl;
  //std::cout << "WristHand_Mat" << std::endl;
  //std::cout << WristHand_Mat << std::endl;
  //std::cout << "IKFAST_InMat" << std::endl;
  //std::cout << IKFAST_InMat << std::endl;
    
  //for(int i=0;i<9;i++){
  //  std::cout << "sol_eerot["<<i<<"] = " << sol_eerot[i] << std::endl;
  //}
  //std::cout << "x = " << sol_eetrans[0] << std::endl;
  //std::cout << "y = " << sol_eetrans[1] << std::endl;
  //std::cout << "z = " << sol_eetrans[2] << std::endl;
  ret = IKFAST_WR_REAL::ik_solve(sol_eerot,sol_eetrans,sol,free_joint,&NumSolutions);
  if(!ret)
    {
      for(int k=0;k<NumSolutions;k++)
	{
	  if(sol[k][0]*180/M_PI<WaistYaw_LimitMax&&sol[k][0]*180/M_PI>WaistYaw_LimitMin&&
	     sol[k][1]*180/M_PI<WaistPitch_LimitMax&&sol[k][1]*180/M_PI>WaistPitch_LimitMin&&
	     sol[k][2]*180/M_PI<WaistRoll_LimitMax&&sol[k][2]*180/M_PI>WaistRoll_LimitMin&&
	     sol[k][3]*180/M_PI<Angle1_LimitMax&&sol[k][3]*180/M_PI>Angle1_LimitMin&&
	     sol[k][4]*180/M_PI<Angle2_LimitMax&&sol[k][4]*180/M_PI>Angle2_LimitMin&&
	     sol[k][5]*180/M_PI<Angle3_LimitMax&&sol[k][5]*180/M_PI>Angle3_LimitMin&&
	     sol[k][6]*180/M_PI<Angle4a_LimitMax&&sol[k][6]*180/M_PI>Angle4a_LimitMin&&
	     sol[k][7]*180/M_PI<Angle4b_LimitMax&&sol[k][7]*180/M_PI>Angle4b_LimitMin&&
	     sol[k][8]*180/M_PI<Angle5_LimitMax&&sol[k][8]*180/M_PI>Angle5_LimitMin&&
	     sol[k][9]*180/M_PI<Angle6_LimitMax&&sol[k][9]*180/M_PI>Angle6_LimitMin&&
	     sol[k][10]*180/M_PI<Angle7_LimitMax&&sol[k][10]*180/M_PI>Angle7_LimitMin)
	    {
	      LimitSolNum[numSolve] = k;
	      numSolve++;
	      phase = 2;
	    }
	}//end for(int k=0;k<NumSolutions;k++)

      if(numSolve==0){//可動範囲内の解がない
	//std::cout << "与えられた位置姿勢ではIKが解けません(解が可動範囲外)" << std::endl;
	return -1;
      }
      //std::cout << "可動範囲内の解の数は"<<l<<"個"<<std::endl;
    }
  else
    {
      //std::cout << "与えられた位置姿勢ではIKが解けません" << std::endl;
      return -1;
    }

  //for(int nn=0;nn<numSolve;nn++){
  //  for(int aa=0;aa<ARM_FREEDOM+3+1;aa++){
  //    std::cout << "RightJointPos["<<nn<<"]["<<aa<<"] = " << sol[LimitSolNum[nn]][aa]*180/M_PI << std::endl;
  //  }
  //}
  //for(int now=0;now<11;now++)
  //  {
  //    std::cout << "RightNowPos["<<now<<"] = " << nowJointPos[now] << std::endl;
  //  }

  //現在値から近い解を選択する
  int MinAveNum=0;
  double MinAve;
  double diffJointPos[numSolve][11];
  if(phase == 2){
    for(int n=0;n<numSolve;n++){
      for(int a=0;a<ARM_FREEDOM+3+1;a++){
	diffJointPos[n][a] = fabs((nowJointPos[a]*M_PI/180) - sol[LimitSolNum[n]][a]);
	//std::cout << "diffJointPos["<<n<<"]["<<a<<"] = " << diffJointPos[n][a] << std::endl;
      }//end for(int a=0;a<ARM_FREEDOM;a++)
    }//end for(int n=0;n<l;n++)
    double Average[numSolve];
    for(int av=0;av<numSolve;av++){
      Average[av] = (diffJointPos[av][0] + diffJointPos[av][1] + diffJointPos[av][2] + diffJointPos[av][3] + diffJointPos[av][4] + diffJointPos[av][5] + diffJointPos[av][6] + diffJointPos[av][7] + diffJointPos[av][8] + diffJointPos[av][9] + diffJointPos[av][10])/(ARM_FREEDOM+3+1);//ARM_FREEDOM=7
      //Average[av] = fabs(Average[av]);
      //std::cout << "Average["<<av<<"] = "<< Average[av] <<std::endl;  
    }
    //MinAveNum = 0;
    MinAve = Average[0];
    for(int mi=1;mi<numSolve;mi++){
      //std::cout << "MinAve = " << MinAve << std::endl;
      //std::cout << "Average["<<mi<<"] = " << Average[mi] << std::endl;
      //std::cout << "mi = " << mi << std::endl;
      if(MinAve > Average[mi]){
	MinAve = Average[mi];
	MinAveNum = mi;
      }
    }
 
    //std::cout << "MinAveNum = " << MinAveNum << std::endl;
  }//end if(phase == 2)
      
    
  if(!ret&&LimitSolNum[MinAveNum]!=-1){
    //std::cout << "弧度法の角度[rad]" << std::endl;
    for(int end=0;end<ARM_FREEDOM+3+1;end++){
      iksol[end] = sol[LimitSolNum[MinAveNum]][end]*180/M_PI;
      /*
	if(end==4){
	std::cout << -sol[LimitSolNum[MinAveNum]][end]+M_PI/2 << std::endl;
	}
	else if(end==5){
	std::cout << -sol[LimitSolNum[MinAveNum]][end] << std::endl;
	}
	else if(end==7){
	std::cout << -sol[LimitSolNum[MinAveNum]][end] << std::endl;
	}
	else if(end==8){
	std::cout << -sol[LimitSolNum[MinAveNum]][end] << std::endl;
	}
	else if(end==9){
	std::cout << -sol[LimitSolNum[MinAveNum]][end] << std::endl;
	}
	else{
	std::cout << sol[LimitSolNum[MinAveNum]][end]<<std::endl;
	//std::cout << LimitSolNum[MinAveNum] <<std::endl;
	}
      */
    }
    //std::cout << "IK計算完了" << std::endl;
    return 0;
  }
  else{
    //std::cout << "与えられた位置姿勢ではIKが解けません" << std::endl;
    return -1;
  }  
  
}

/************************************************

        int Solve_WLArm_RealIk(double eerot[9], double eetrans[3], double elbow, Frame WaistPos, double nowJointPos[], double iksol[])
	
	概要：Seednoid腰を原点とした左腕の逆運動学を計算する

	引数：
             double eerot[9]・・・先端姿勢の行列
             double eetrans[3]・・・先端座標(x,y,z)[mm]
             double elbow・・・冗長肘関節の角度
             double elbow_a・・・肘の2関節の手前側の関節角度
             Frame WaistPos・・・冗長腰の関節角度
             double nowJointPos[]・・・現在角度
             double iksol[]・・・計算角度を格納する配列

	戻り値：IKが計算できれば0，計算できなければ-1

*************************************************/
int SeedUpper::Solve_WLArm_RealIk(double eerot[9],double eetrans[3], double elbow, double elbow_a, Frame WaistPos, double nowJointPos[], double iksol[])
{
  //std::cout << "Solve_WLArm_RealIk" << std::endl;
  int ret; 
  double sol_eerot[9];
  double sol_eetrans[3];
  std::vector<IkReal> free_joint(IKFAST_WL_REAL::GetNumFreeParameters());
  int NumSolutions = 0;
  int phase = 0;
  std::vector<int> LimitSolNum;
  std::vector<std::vector<double> > sol;
  int numSolve = 0;//可動範囲内の解の数
  std::vector<double> min;
  LimitSolNum.push_back(-1);
  free_joint[0] = WaistPos.yaw*M_PI/180;
  free_joint[1] = WaistPos.pitch*M_PI/180;
  free_joint[2] = WaistPos.roll*M_PI/180;
  free_joint[3] = 0.1745;//仮想10°
  free_joint[4] = elbow*M_PI/180;
  free_joint[5] = -elbow_a*M_PI/180;

  Eigen::MatrixXd Target_Mat(4,4);
  Eigen::MatrixXd WristHand_Mat(4,4);
  Eigen::MatrixXd IKFAST_InMat(4,4);
 
  //for(int i=0;i<9;i++){
  //  std::cout << "eerot["<<i<<"] = " << eerot[i] << std::endl;
  //}
  //std::cout << "x = " << eetrans[0] << std::endl;
  //std::cout << "y = " << eetrans[1] << std::endl;
  //std::cout << "z = " << eetrans[2] << std::endl;
  
  Target_Mat(0,0)=eerot[0];
  Target_Mat(0,1)=eerot[1];
  Target_Mat(0,2)=eerot[2];
  Target_Mat(1,0)=eerot[3];
  Target_Mat(1,1)=eerot[4];
  Target_Mat(1,2)=eerot[5];
  Target_Mat(2,0)=eerot[6];
  Target_Mat(2,1)=eerot[7];
  Target_Mat(2,2)=eerot[8];
  Target_Mat(0,3)=eetrans[0]/1000;//x
  Target_Mat(1,3)=eetrans[1]/1000;//y
  Target_Mat(2,3)=eetrans[2]/1000;//z
  Target_Mat(3,0)=0;
  Target_Mat(3,1)=0;
  Target_Mat(3,2)=0;
  Target_Mat(3,3)=1.0;

  WristHand_Mat(0,0) = 1;
  WristHand_Mat(0,1) = 0;
  WristHand_Mat(0,2) = 0;
  WristHand_Mat(1,0) = 0;
  WristHand_Mat(1,1) = 1;
  WristHand_Mat(1,2) = 0;
  WristHand_Mat(2,0) = 0;
  WristHand_Mat(2,1) = 0;
  WristHand_Mat(2,2) = 1;
  WristHand_Mat(0,3) = 0;//x
  WristHand_Mat(1,3) = 0.0964;//y
  WristHand_Mat(2,3) = -0.0296;//z
  WristHand_Mat(3,0)=0;
  WristHand_Mat(3,1)=0;
  WristHand_Mat(3,2)=0;
  WristHand_Mat(3,3) = 1.0;

  IKFAST_InMat = Target_Mat * WristHand_Mat.inverse();

  sol_eerot[0] = IKFAST_InMat(0,0);
  sol_eerot[1] = IKFAST_InMat(0,1);
  sol_eerot[2] = IKFAST_InMat(0,2);
  sol_eerot[3] = IKFAST_InMat(1,0);
  sol_eerot[4] = IKFAST_InMat(1,1);
  sol_eerot[5] = IKFAST_InMat(1,2);
  sol_eerot[6] = IKFAST_InMat(2,0);
  sol_eerot[7] = IKFAST_InMat(2,1);
  sol_eerot[8] = IKFAST_InMat(2,2);
  sol_eetrans[0] = IKFAST_InMat(0,3);
  sol_eetrans[1] = IKFAST_InMat(1,3);
  sol_eetrans[2] = IKFAST_InMat(2,3);

  //std::cout << "Target_Mat" << std::endl;
  //std::cout << Target_Mat << std::endl;
  //std::cout << "WristHand_Mat" << std::endl;
  //std::cout << WristHand_Mat << std::endl;
  //std::cout << "IKFAST_InMat" << std::endl;
  //std::cout << IKFAST_InMat << std::endl;
    
  //for(int i=0;i<9;i++){
  //  std::cout << "sol_eerot["<<i<<"] = " << sol_eerot[i] << std::endl;
  //}
  //std::cout << "x = " << sol_eetrans[0] << std::endl;
  //std::cout << "y = " << sol_eetrans[1] << std::endl;
  //std::cout << "z = " << sol_eetrans[2] << std::endl;
  ret = IKFAST_WL_REAL::ik_solve(sol_eerot,sol_eetrans,sol,free_joint,&NumSolutions);
  if(!ret)
    {
      for(int k=0;k<NumSolutions;k++)
	{
	  if(sol[k][0]*180/M_PI<WaistYaw_LimitMax&&sol[k][0]*180/M_PI>WaistYaw_LimitMin&&
	     sol[k][1]*180/M_PI<WaistPitch_LimitMax&&sol[k][1]*180/M_PI>WaistPitch_LimitMin&&
	     sol[k][2]*180/M_PI<WaistRoll_LimitMax&&sol[k][2]*180/M_PI>WaistRoll_LimitMin&&
	     sol[k][3]*180/M_PI<Angle1_LimitMax&&sol[k][3]*180/M_PI>Angle1_LimitMin&&
	     sol[k][4]*180/M_PI<Angle2_LimitMax&&sol[k][4]*180/M_PI>Angle2_LimitMin&&
	     sol[k][5]*180/M_PI<Angle3_LimitMax&&sol[k][5]*180/M_PI>Angle3_LimitMin&&
	     sol[k][6]*180/M_PI<Angle4a_LimitMax&&sol[k][6]*180/M_PI>Angle4a_LimitMin&&
	     sol[k][7]*180/M_PI<Angle4b_LimitMax&&sol[k][7]*180/M_PI>Angle4b_LimitMin&&
	     sol[k][8]*180/M_PI<Angle5_LimitMax&&sol[k][8]*180/M_PI>Angle5_LimitMin&&
	     sol[k][9]*180/M_PI<Angle6_LimitMax&&sol[k][9]*180/M_PI>Angle6_LimitMin&&
	     sol[k][10]*180/M_PI<Angle7_LimitMax&&sol[k][10]*180/M_PI>Angle7_LimitMin)
	    {
	      LimitSolNum[numSolve] = k;
	      numSolve++;
	      phase = 2;
	    }
	}//end for(int k=0;k<NumSolutions;k++)

      if(numSolve==0){//可動範囲内の解がない
	//std::cout << "与えられた位置姿勢ではIKが解けません(解が可動範囲外)" << std::endl;
	return -1;
      }
      //std::cout << "可動範囲内の解の数は"<<l<<"個"<<std::endl;
    }
  else
    {
      //std::cout << "与えられた位置姿勢ではIKが解けません" << std::endl;
      return -1;
    }

  //for(int nn=0;nn<numSolve;nn++){
  //  for(int aa=0;aa<ARM_FREEDOM+3+1;aa++){
  //    std::cout << "LeftJointPos["<<nn<<"]["<<aa<<"] = " << sol[LimitSolNum[nn]][aa]*180/M_PI << std::endl;
  //  }
  //}
  //for(int now=0;now<11;now++)
  //  {
  //    std::cout << "LeftNowPos["<<now<<"] = " << nowJointPos[now] << std::endl;
  //  }
  
  //現在値から近い解を選択する
  int MinAveNum=0;
  double MinAve;
  double diffJointPos[numSolve][11];
  if(phase == 2){
    for(int n=0;n<numSolve;n++){
      for(int a=0;a<ARM_FREEDOM+3+1;a++){
	diffJointPos[n][a] = fabs((nowJointPos[a]*M_PI/180) - sol[LimitSolNum[n]][a]);
	//std::cout << "diffJointPos["<<n<<"]["<<a<<"] = " << diffJointPos[n][a] << std::endl;
      }//end for(int a=0;a<ARM_FREEDOM;a++)
    }//end for(int n=0;n<l;n++)
    double Average[numSolve];
    for(int av=0;av<numSolve;av++){
      Average[av] = (diffJointPos[av][0] + diffJointPos[av][1] + diffJointPos[av][2] + diffJointPos[av][3] + diffJointPos[av][4] + diffJointPos[av][5] + diffJointPos[av][6] + diffJointPos[av][7] + diffJointPos[av][8] + diffJointPos[av][9] + diffJointPos[av][10])/(ARM_FREEDOM+3+1);//ARM_FREEDOM=7
      //Average[av] = fabs(Average[av]);
      //std::cout << "Average["<<av<<"] = "<< Average[av] <<std::endl;  
    }
    //MinAveNum = 0;
    MinAve = Average[0];
    for(int mi=1;mi<numSolve;mi++){
      //std::cout << "MinAve = " << MinAve << std::endl;
      //std::cout << "Average["<<mi<<"] = " << Average[mi] << std::endl;
      //std::cout << "mi = " << mi << std::endl;
      if(MinAve > Average[mi]){
	MinAve = Average[mi];
	MinAveNum = mi;
      }
    }
 
    //std::cout << "MinAveNum = " << MinAveNum << std::endl;
  }//end if(phase == 2)
      
    
  if(!ret&&LimitSolNum[MinAveNum]!=-1){
    //std::cout << "弧度法の角度[rad]" << std::endl;
    for(int end=0;end<ARM_FREEDOM+3+1;end++){
      iksol[end] = sol[LimitSolNum[MinAveNum]][end]*180/M_PI;
      /*
	if(end==4){
	std::cout << -sol[LimitSolNum[MinAveNum]][end]+M_PI/2 << std::endl;
	}
	else if(end==5){
	std::cout << -sol[LimitSolNum[MinAveNum]][end] << std::endl;
	}
	else if(end==7){
	std::cout << -sol[LimitSolNum[MinAveNum]][end] << std::endl;
	}
	else if(end==8){
	std::cout << -sol[LimitSolNum[MinAveNum]][end] << std::endl;
	}
	else if(end==9){
	std::cout << -sol[LimitSolNum[MinAveNum]][end] << std::endl;
	}
	else{
	std::cout << sol[LimitSolNum[MinAveNum]][end]<<std::endl;
	//std::cout << LimitSolNum[MinAveNum] <<std::endl;
	}
      */
    }
    //std::cout << "IK計算完了" << std::endl;
    return 0;
  }
  else{
    //std::cout << "与えられた位置姿勢ではIKが解けません" << std::endl;
    return -1;
  }  
}



/************************************************

        int Solve_WRArmRealFK(double eerot[9],double eetrans[3],double joint[])

	概要：Seednoid腰を原点とした肘2関節を考慮した右腕の順運動学を計算する

	引数：
           　double eerot[]・・・計算した行列を格納する配列
                                 |0 1 2|
                                 |3 4 5|
                                 |6 7 8|
             double eetrans[3]・・・先端座標(x,y,z)が格納される[mm]
             double joint[]・・・入力関節角度を格納する配列列

	戻り値：FKが計算できれば0，計算できなければ-1

*************************************************/
int SeedUpper::Solve_WRArm_RealFk(double eerot[9],double eetrans[3], double joint[])
{
  //std::cout << "Solve_WRArm_RealFk" << std::endl;
  double ikjoint[12];
  double calceerot[9];
  double calceetrans[3];
  
  ikjoint[0] = joint[0]*M_PI/180;
  ikjoint[1] = joint[1]*M_PI/180;
  ikjoint[2] = joint[2]*M_PI/180;
  ikjoint[3] = -joint[3]*M_PI/180;
  ikjoint[4] = joint[4];//仮想10°
  ikjoint[5] = -joint[5]*M_PI/180+M_PI/2;
  ikjoint[6] = -joint[6]*M_PI/180;
  ikjoint[7] = joint[7]*M_PI/180;
  ikjoint[8] = joint[8]*M_PI/180;
  ikjoint[9] = -joint[9]*M_PI/180;
  ikjoint[10] = -joint[10]*M_PI/180;
  ikjoint[11] = -joint[11]*M_PI/180;
  
  IKFAST_WR_REAL::ComputeFk(ikjoint,calceetrans,calceerot);
  
  Eigen::MatrixXd NowMat(4,4);
  Eigen::MatrixXd WristHand_Mat(4,4);
  Eigen::MatrixXd IKFAST_OutMat(4,4);

  IKFAST_OutMat(0,0) = calceerot[0];
  IKFAST_OutMat(0,1) = calceerot[1];
  IKFAST_OutMat(0,2) = calceerot[2];
  IKFAST_OutMat(1,0) = calceerot[3];
  IKFAST_OutMat(1,1) = calceerot[4];
  IKFAST_OutMat(1,2) = calceerot[5];
  IKFAST_OutMat(2,0) = calceerot[6];
  IKFAST_OutMat(2,1) = calceerot[7];
  IKFAST_OutMat(2,2) = calceerot[8];
  IKFAST_OutMat(0,3) = calceetrans[0];
  IKFAST_OutMat(1,3) = calceetrans[1];
  IKFAST_OutMat(2,3) = calceetrans[2];
  IKFAST_OutMat(3,0)=0;
  IKFAST_OutMat(3,1)=0;
  IKFAST_OutMat(3,2)=0;
  IKFAST_OutMat(3,3) = 1.0;

  WristHand_Mat(0,0) = 1;
  WristHand_Mat(0,1) = 0;
  WristHand_Mat(0,2) = 0;
  WristHand_Mat(1,0) = 0;
  WristHand_Mat(1,1) = 1;
  WristHand_Mat(1,2) = 0;
  WristHand_Mat(2,0) = 0;
  WristHand_Mat(2,1) = 0;
  WristHand_Mat(2,2) = 1;
  WristHand_Mat(0,3) = 0;//x
  WristHand_Mat(1,3) = -0.0964;//y
  WristHand_Mat(2,3) = -0.0296;//z
  WristHand_Mat(3,0)=0;
  WristHand_Mat(3,1)=0;
  WristHand_Mat(3,2)=0;
  WristHand_Mat(3,3) = 1.0;

  NowMat = IKFAST_OutMat * WristHand_Mat;

  eerot[0] = NowMat(0,0);
  eerot[1] = NowMat(0,1);
  eerot[2] = NowMat(0,2);
  eerot[3] = NowMat(1,0);
  eerot[4] = NowMat(1,1);
  eerot[5] = NowMat(1,2);
  eerot[6] = NowMat(2,0);
  eerot[7] = NowMat(2,1);
  eerot[8] = NowMat(2,2);
  eetrans[0] = NowMat(0,3) * 1000;
  eetrans[1] = NowMat(1,3) * 1000;
  eetrans[2] = NowMat(2,3) * 1000;

  return 0;
}

/************************************************

        int Solve_WLArmRealFK(double eerot[9],double eetrans[3],double joint[])

	概要：Seednoid腰を原点とした肘2関節を考慮した左腕の順運動学を計算する

	引数：
           　double eerot[]・・・計算した行列を格納する配列
                                 |0 1 2|
                                 |3 4 5|
                                 |6 7 8|
             double eetrans[3]・・・先端座標(x,y,z)が格納される[mm]
             double joint[]・・・入力関節角度を格納する配列列

	戻り値：FKが計算できれば0，計算できなければ-1

*************************************************/
int SeedUpper::Solve_WLArm_RealFk(double eerot[9],double eetrans[3], double joint[])
{
  //std::cout << "Solve_WLArm_RealFk" << std::endl;
  double ikjoint[12];
  double calceerot[9];
  double calceetrans[3];
  ikjoint[0] = joint[0]*M_PI/180;
  ikjoint[1] = joint[1]*M_PI/180;
  ikjoint[2] = joint[2]*M_PI/180;
  ikjoint[3] = -joint[3]*M_PI/180;
  ikjoint[4] = joint[4];//仮想10°
  ikjoint[5] = joint[5]*M_PI/180-M_PI/2;
  ikjoint[6] = joint[6]*M_PI/180;
  ikjoint[7] = -joint[7]*M_PI/180;
  ikjoint[8] = -joint[8]*M_PI/180;
  ikjoint[9] = joint[9]*M_PI/180;
  ikjoint[10] = joint[10]*M_PI/180;
  ikjoint[11] = joint[11]*M_PI/180; 

  IKFAST_WL_REAL::ComputeFk(ikjoint,calceetrans,calceerot);
  
  Eigen::MatrixXd NowMat(4,4);
  Eigen::MatrixXd WristHand_Mat(4,4);
  Eigen::MatrixXd IKFAST_OutMat(4,4);

  IKFAST_OutMat(0,0)=calceerot[0];
  IKFAST_OutMat(0,1)=calceerot[1];
  IKFAST_OutMat(0,2)=calceerot[2];
  IKFAST_OutMat(1,0)=calceerot[3];
  IKFAST_OutMat(1,1)=calceerot[4];
  IKFAST_OutMat(1,2)=calceerot[5];
  IKFAST_OutMat(2,0)=calceerot[6];
  IKFAST_OutMat(2,1)=calceerot[7];
  IKFAST_OutMat(2,2)=calceerot[8];
  IKFAST_OutMat(0,3)=calceetrans[0];//x
  IKFAST_OutMat(1,3)=calceetrans[1];//y
  IKFAST_OutMat(2,3)=calceetrans[2];//z
  IKFAST_OutMat(3,0)=0;
  IKFAST_OutMat(3,1)=0;
  IKFAST_OutMat(3,2)=0;
  IKFAST_OutMat(3,3)=1.0;

  WristHand_Mat(0,0) = 1;
  WristHand_Mat(0,1) = 0;
  WristHand_Mat(0,2) = 0;
  WristHand_Mat(1,0) = 0;
  WristHand_Mat(1,1) = 1;
  WristHand_Mat(1,2) = 0;
  WristHand_Mat(2,0) = 0;
  WristHand_Mat(2,1) = 0;
  WristHand_Mat(2,2) = 1;
  WristHand_Mat(0,3) = 0;//x
  WristHand_Mat(1,3) = 0.0964;//y
  WristHand_Mat(2,3) = -0.0296;//z
  WristHand_Mat(3,0)=0;
  WristHand_Mat(3,1)=0;
  WristHand_Mat(3,2)=0;
  WristHand_Mat(3,3) = 1.0;

  NowMat = IKFAST_OutMat * WristHand_Mat;
  
  eerot[0] = NowMat(0,0);
  eerot[1] = NowMat(0,1);
  eerot[2] = NowMat(0,2);
  eerot[3] = NowMat(1,0);
  eerot[4] = NowMat(1,1);
  eerot[5] = NowMat(1,2);
  eerot[6] = NowMat(2,0);
  eerot[7] = NowMat(2,1);
  eerot[8] = NowMat(2,2);
  eetrans[0] = NowMat(0,3) * 1000;
  eetrans[1] = NowMat(1,3) * 1000;
  eetrans[2] = NowMat(2,3) * 1000;

  return 0;
}
