//===========================================================================
//@brief �n�ʃN���X/�p��
//===========================================================================

#pragma once
#include"DxLib.h"
#include"StageBase.h"

class Ground :public StageBase
{
public:
    Ground() {};                // �R���X�g���N�^
    Ground(int modelHandle);    //��������R���X�g���N�^
    ~Ground();                  //�f�X�g���N�^
};

