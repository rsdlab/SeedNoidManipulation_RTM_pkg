//seedUpper_ReturnID.h
#ifndef __seedUpper_ReturnID_H__
#define __seedUpper_ReturnID_H__

static SEED_UPPER::RETURN_ID* RETURN_CODE(int id, const char *comment)
{
  SEED_UPPER::RETURN_ID_var RETURNCODE = new SEED_UPPER::RETURN_ID;
  RETURNCODE->id = id;
  RETURNCODE->comment = comment;
  return RETURNCODE._retn(); 
}

#define RETURNID(id,comment) { return RETURN_CODE(id,comment);}

#define RETURNID_OK RETURNID(SEED_UPPER::OK,"オペレーションを正常に受け付け.")
#define RETURNID_NG RETURNID(SEED_UPPER::NG,"オペレーション拒否.")
#define RETURNID_STATUS_ERR RETURNID(SEED_UPPER::STATUS_ERR,"オペレーションを受け付け可能な状態でない.")
#define RETURNID_VALUE_ERR RETURNID(SEED_UPPER::VALUE_ERR,"引数が不正.")
#define RETURNID_NOT_SV_ON_ERR RETURNID(SEED_UPPER::NOT_SV_ON_ERR,"全ての軸のサーボが入っていない.")
#define RETURNID_FULL_MOTION_QUEUE_ERR RETURNID(SEED_UPPER::FULL_MOTION_QUEUE_ERR,"バッファが一杯.")
#define RETURNID_NOT_IMPLEMENTED RETURNID(SEED_UPPER::NOT_IMPLEMENTED,"未実装のコマンド.")

#endif//__seedUpper_ReturnIDID_H__
