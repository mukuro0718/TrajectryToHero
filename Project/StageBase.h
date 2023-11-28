//===========================================================================
//@brief �X�e�[�W�x�[�X�N���X
//===========================================================================
#pragma once
#include "DxLib.h"
class StageBase
{
public:
	StageBase(){}						// �R���X�g���N�^
	StageBase(int _modelHandle);			// ��������R���X�g���N�^
	virtual ~StageBase();				// �f�X�g���N�^

	void Draw();						//�`��
	void Delete();						//�ŏI����
	void Update();						//�X�V
	const int GetModelHandle()const { return modelHandle; }

protected:
	//�萔
	static const VECTOR SCALE;			//�g�嗦
	static const VECTOR INIT_STAGE_POS;//�����v���C���[���W
	//�ϐ�
	VECTOR pos;							//�|�W�V����
	int modelHandle;					//���f���n���h��
};

