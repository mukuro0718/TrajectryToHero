//=====================================
// @brief �`���[�g���A���N���X
// �������
// ���邱�ƁE�ړI�i���x���A�b�v�j�̐���
// �{�X�Ɛ키���@
//=====================================
#pragma once
class Tutorial
{
public:
	Tutorial();//�R���X�g���N�^
	~Tutorial();//�f�X�g���N�^

	void ExplanationOfOperation();//����̐���
	void ExplanationOfPurpose();//�ړI�̐���
	void ExplanationOfFightingBoss();//�{�X��̐���

	//�`���[�g���A���I���t���O��getter
	const bool GetIsTitleEnd()const { return isTutorialEnd; }
	//�V�[���ύX�t���O��getter
	const bool GetIsChangeScene()const { return isChangeScene; }

private:
	bool isTutorialEnd;//�`���[�g���A���I���t���O
	bool isOperation;//����t���O
	bool isPurpose;//�ړI�t���O
	bool isFightBoss;//�{�X��t���O
	bool isChangeScene;//�V�[���ύX�t���O

};

