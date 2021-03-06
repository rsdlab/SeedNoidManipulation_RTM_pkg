#ifndef _SERIAL_COM_H_
#define _SERIAL_COM_H_

//Boost include
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/array.hpp>
#include <vector>
#include <stdlib.h>
#include <string>


//using namespace std;
//using namespace boost::asio;

class SerialCom
{
 public:

  bool isCanceled;

  //=========================================================================
  //コンストラクタ
  //Constructor
  //プログラムの最初で呼び出す関数．
  //
  //引数：
  //なし
  //
  //返り値：
  //なし
  //=========================================================================
  SerialCom()
    :ioService(),serialPort(ioService),deadlineTimer(ioService){}

  //=========================================================================
  //USB接続開始関数
  //USB接続を行う．
  //
  //引数：
  //port：接続されたポートの番号　例："COM1","/dev/ttyUSB0"
  //baudrate：通信速度　例：1152000
  //
  //返り値：
  //true: 正常終了　false: 異常発生(表示されるエラー内容を参照)
  //=========================================================================
  bool serialOpen(const std::string portName, const unsigned int baudRate);

  //=========================================================================
  //USB接続終了関数
  //USB接続を終了する関数
  //
  //引数：
  //なし
  //
  //返り値：
  //true: 正常終了　false: 異常発生(表示されるエラー内容を参照)
  //=========================================================================
  bool serialClose();

  //=========================================================================
  //データ送信関数(同期バージョン)
  //データを送信する関数
  //
  //引数：
  //sendData：送信バッファ
  //
  //返り値：
  //なし
  //=========================================================================
  void serialWrite(std::vector<unsigned char>& sendData);

  //=========================================================================
  //データ受信関数(同期バージョン)
  //データを受信する関数
  //
  //引数：
  //sendData：受信バッファ
  //size：データサイズ
  //
  //返り値：
  //なし
  //=========================================================================
  void serialRead(std::vector<unsigned char>& receiveData,unsigned char size);

  //=========================================================================
  //データ送信関数(非同期バージョン)
  //データを送信する関数
  //
  //引数：
  //sendData：送信バッファ
  //
  //返り値：
  //なし
  //=========================================================================
  void serialAsyncWrite(std::vector<unsigned char>& sendData);

  //=========================================================================
  //送信ハンドラ関数
  //送信の際に呼び出される関数
  //
  //引数：
  //errorCode：送信失敗時にエラー情報を格納
  //bytesTransferred：送信したバイト数
  //
  //返り値：
  //なし
  //=========================================================================
  void writeHandler(const boost::system::error_code& errorCode, std::size_t bytesTransferred);

  //=========================================================================
  //データ受信関数(非同期バージョン)
  //データを受信する関数
  //
  //引数：
  //sendData：受信バッファ
  //size：データサイズ
  //timeOut：タイムアウト時間
  //
  //返り値：
  //なし
  //=========================================================================
  void serialAsyncRead(std::vector<unsigned char>& receiveData, unsigned char size, unsigned char timeOut);
  
  //=========================================================================
  //受信ハンドラ関数
  //受信の際に呼び出される関数
  //
  //引数：
  //errorCode：受信失敗時にエラー情報を格納
  //bytesTransferred：受信したバイト数
  //
  //返り値：
  //なし
  //=========================================================================
  void readHandler(const boost::system::error_code& errorCode, std::size_t bytesTransferred);
   
  //=========================================================================
  //タイマーのイベント受信関数
  //
  //引数：
  //errorCode：エラー情報
  //
  //返り値：
  //なし
  //=========================================================================
  void onTimer(const boost::system::error_code &errorCode);

  //=========================================================================
  //データクリア関数
  //受信したが読んでないデータ・書いたが送信していないデータをフラッシュ
  //
  //引数：
  //なし
  //
  //返り値：
  //なし
  //=========================================================================
  void flushSerialPort();
  
 private:

  //I/O制御のためのコンストラクタ
  boost::asio::io_service ioService;
  //シリアルポートのハンドラ
  boost::asio::serial_port serialPort;
  //タイマーのハンドラ
  boost::asio::deadline_timer deadlineTimer;

};

#endif     //_SERIAL_COM_H_
