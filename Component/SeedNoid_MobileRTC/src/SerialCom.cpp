#include "SerialCom.h"

//=========================================================================
//USB接続開始関数
//
//引数：
//port：接続されたポートの番号　例："COM1","/dev/ttyUSB0"
//baudrate：通信速度　例：1152000
//
//返り値：
//true: 正常終了　false: 異常発生(表示されるエラー内容を参照)
//=========================================================================
bool SerialCom::serialOpen(const std::string portName, const unsigned int baudRate)
{
  //シリアルポートをオープン
  serialPort.open(portName);
  
  //接続状態の確認
  if(!serialPort.is_open())
    {
      return false;
    }
  else
    {
      //ボーレートを設定
      serialPort.set_option(boost::asio::serial_port_base::baud_rate(baudRate));
      return true;
    }
}

//=========================================================================
//USB接続終了関数
//
//引数：
//なし
//
//返り値：
//true: 正常終了　false: 異常発生(表示されるエラー内容を参照)
//=========================================================================
bool SerialCom::serialClose()
{
  //接続状態の確認
  if(!serialPort.is_open())
    {
      return false;
    }
  else
    {
      //シリアルポートをクローズ
      serialPort.close();
      return true;
    }
}

//=========================================================================
//データ送信関数(同期バージョン)
//
//引数：
//sendData：送信バッファ
//
//返り値：
//なし
//=========================================================================
void SerialCom::serialWrite(std::vector<unsigned char>& sendData)
{
  //データの送信
  serialPort.write_some(boost::asio::buffer(sendData));
}

//=========================================================================
//データ受信関数(同期バージョン)
//
//引数：
//sendData：受信バッファ
//size：データサイズ
//
//返り値：
//なし
//=========================================================================
void SerialCom::serialRead(std::vector<unsigned char>& receiveData,unsigned char size = 1)
{
  //受信バッファのデータサイズを設定
  receiveData.resize(size);
  //データの受信
  serialPort.read_some(boost::asio::buffer(receiveData,size));
}

//=========================================================================
//データ送信関数(非同期バージョン)
//
//引数：
//sendData：送信バッファ
//
//返り値：
//なし
//=========================================================================
void SerialCom::serialAsyncWrite(std::vector<unsigned char>& sendData)
{
  //データの送信ハンドラを登録
  serialPort.async_write_some(boost::asio::buffer(sendData), boost::bind(&SerialCom::writeHandler, this, _1, _2));

  //後続のrun()呼び出しに備えてリセット
  ioService.reset();
  //実行可能なハンドラの呼び出し
  ioService.run();
}

//=========================================================================
//送信ハンドラ関数
//送信の際に呼び出される関数
//
//引数：
//errorCode：送信失敗時のエラー情報
//bytesTransferred：送信したバイト数
//
//返り値：
//なし
//=========================================================================
void SerialCom::writeHandler(const boost::system::error_code& errorCode, std::size_t bytesTransferred)
{
  //エラー情報の確認
  if(errorCode)
    {
      //エラー内容の表示
      std::cout << "Write failed : " << errorCode.message() << std::endl;
    }
}

//=========================================================================
//データ受信関数(非同期バージョン)
//
//引数：
//sendData：受信バッファ
//size：データサイズ
//timeOut：タイムアウト時間
//
//返り値：
//なし
//=========================================================================
void SerialCom::serialAsyncRead(std::vector<unsigned char>& receiveData, unsigned char size = 1, unsigned char timeOut = 1)
{
  //受信バッファのデータサイズを設定
  receiveData.resize(size);
  //データの受信ハンドラを登録
  serialPort.async_read_some(boost::asio::buffer(receiveData, size), boost::bind(&SerialCom::readHandler, this, _1, _2));

  //<timeOut>時間でタイムアウト
  deadlineTimer.expires_from_now(boost::posix_time::seconds(timeOut));
  deadlineTimer.async_wait(boost::bind(&SerialCom::onTimer, this, _1));
  
  //後続のrun()呼び出しに備えてリセット
  ioService.reset();
  //実行可能なハンドラの呼び出し
  ioService.run();
}

//=========================================================================
//受信ハンドラ関数
//受信の際に呼び出される関数
//
//引数：
//errorCode：受信失敗時のエラー情報
//bytesTransferred：受信したバイト数
//
//返り値：
//なし
//=========================================================================
void SerialCom::readHandler(const boost::system::error_code& errorCode, std::size_t bytesTransferred)
{
  //操作キャンセルの確認
  if(errorCode == boost::asio::error::operation_aborted)
    {
      std::cout << "Timeout"<< std::endl;
    }
  else
    {
      //タイマーハンドラのキャンセル
      deadlineTimer.cancel();
      isCanceled = true;

      //エラー情報の確認
      if(errorCode)
	{
	  //エラー内容の表示
	  std::cout << "Read failed : " << errorCode.message() << std::endl;
	}
    }  
}

//=========================================================================
//タイマーのイベント受信関数
//
//引数：
//errorCode：エラー情報
//
//返り値：
//なし
//=========================================================================
void SerialCom::onTimer(const boost::system::error_code &errorCode)
{
  //受信ハンドラのエラー確認
  if(!errorCode && !isCanceled)
    {
      //通信処理のキャンセル
      serialPort.cancel();
    }
}

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
void SerialCom::flushSerialPort()
{
  tcflush(serialPort.lowest_layer().native_handle(),TCIOFLUSH);
}

