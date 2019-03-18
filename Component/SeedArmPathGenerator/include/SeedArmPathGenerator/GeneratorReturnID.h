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

#define RETURNID_OK RETURNID(Manipulation::OK,"�I�y���[�V�����𐳏�Ɏ󂯕t��.")
#define RETURNID_NG RETURNID(Manipulation::NG,"�I�y���[�V��������.")
#define RETURNID_STATUS_ERR RETURNID(Manipulation::STATUS_ERR,"�I�y���[�V�������󂯕t���\�ȏ�ԂłȂ�.")
#define RETURNID_VALUE_ERR RETURNID(Manipulation::VALUE_ERR,"�������s��.")
#define RETURNID_NOT_SV_ON_ERR RETURNID(Manipulation::NOT_SV_ON_ERR,"�S�Ă̎��̃T�[�{�������Ă��Ȃ�.")
#define RETURNID_FULL_MOTION_QUEUE_ERR RETURNID(Manipulation::FULL_MOTION_QUEUE_ERR,"�o�b�t�@����t.")
#define RETURNID_NOT_IMPLEMENTED RETURNID(Manipulation::NOT_IMPLEMENTED,"�������̃R�}���h.")

#endif//__GeneratorReturnID_H__
