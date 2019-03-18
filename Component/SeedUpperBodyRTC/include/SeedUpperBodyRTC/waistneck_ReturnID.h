//WaistNeckReturnID.h
#ifndef __WaistNeckReturnID_H__
#define __WaistNeckReturnID_H__

static WaistNeck::RETURN_ID* RETURN_CODE(int id, const char *comment)
{
  WaistNeck::RETURN_ID_var RETURNCODE = new WaistNeck::RETURN_ID;
  RETURNCODE->id = id;
  RETURNCODE->comment = comment;
  return RETURNCODE._retn(); 
}

#define RETURNID(id,comment) { return RETURN_CODE(id,comment);}

#define RETURNID_OK RETURNID(WaistNeck::OK,"オペレーションを正常に受け付け.")
#define RETURNID_NG RETURNID(WaistNeck::NG,"オペレーション拒否.")
#define RETURNID_STATUS_ERR RETURNID(WaistNeck::STATUS_ERR,"オペレーションを受け付け可能な状態でない.")
#define RETURNID_VALUE_ERR RETURNID(WaistNeck::VALUE_ERR,"引数が不正.")
#define RETURNID_NOT_SV_ON_ERR RETURNID(WaistNeck::NOT_SV_ON_ERR,"全ての軸のサーボが入っていない.")
#define RETURNID_FULL_MOTION_QUEUE_ERR RETURNID(WaistNeck::FULL_MOTION_QUEUE_ERR,"バッファが一杯.")
#define RETURNID_NOT_IMPLEMENTED RETURNID(WaistNeck::NOT_IMPLEMENTED,"未実装のコマンド.")

#endif//__WaistNeckReturnID_H__
