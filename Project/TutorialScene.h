//===========================================================================
//@brief �`���[�g���A���V�[���N���X
// �`���[�g���A���N���X�̎��s���V�[���x�[�X�N���X�����ƂɎ��s
//===========================================================================

#pragma once
#include"SceneBase.h"
#include"DxLib.h"

class Tutorial;

class TutorialScene :public SceneBase
{
public:
	TutorialScene();					//�R���X�g���N�^
	virtual ~TutorialScene();			//�f�X�g���N�^

	void Create() override;	//�V�[���̐���
	void Final()  override;	//�V�[���̍폜
	void Update() override;	//�X�V
	void Draw()	  override;	//�`��

private:
	/*���������֐�*/
	void ChangeNextScene();	//���̃V�[����
	void Delete();			//�ŏI�I�ȏ���
	/*�N���X*/
	Tutorial* tutorial;	//�^�C�g���N���X
	/*�ϐ�*/
	int padInput;	//�L�[�ƃp�b�h�̓��͏��
};