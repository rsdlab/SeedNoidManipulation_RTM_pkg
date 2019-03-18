//ReturnID.h
#ifndef __GeneratorReturnID_H__
#define __GeneratorReturnID_H__

static Manipulation::RETURN_ID* RETURN_CODE(int id, const char *comment)
{
  Manipulation::RETURN_ID_var RETURNCODE = new Manipulation::RETURN_ID;
  RETURNCODE->id = id;
  RETURNCODE->comment = comment;
  return RETURNCODE._retn(); 
}

#define RETURNID(id,comment) { return RETURN_CODE(id,comment);}

#define RETURNID_OK RETURNID(Manipulation::OK,"オペレーションを正常に受け付け.")
#define RETURNID_NG RETURNID(Manipulation::NG,"オペレーション拒否.")
#define RETURNID_STATUS_ERR RETURNID(Manipulation::STATUS_ERR,"オペレーションを受け付け可能な状態でない.")
#define RETURNID_VALUE_ERR RETURNID(Manipulation::VALUE_ERR,"引数が不正.")
#define RETURNID_NOT_SV_ON_ERR RETURNID(Manipulation::NOT_SV_ON_ERR,"全ての軸のサーボが入っていない.")
#define RETURNID_FULL_MOTION_QUEUE_ERR RETURNID(Manipulation::FULL_MOTION_QUEUE_ERR,"バッファが一杯.")
#define RETURNID_NOT_IMPLEMENTED RETURNID(Manipulation::NOT_IMPLEMENTED,"未実装のコマンド.")

#endif//__GeneratorReturnID_H__
