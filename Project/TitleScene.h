//===========================================================================
//@brief �^�C�g���V�[���N���X
// �^�C�g���N���X�̎��s���V�[���x�[�X�N���X�����ƂɎ��s
//===========================================================================

#pragma once
#include"SceneBase.h"
#include"DxLib.h"

class Title;

class TitleScene:public SceneBase
{
public:
    TitleScene();					//�R���X�g���N�^
    virtual ~TitleScene();			//�f�X�g���N�^

	void Create() override;	//�V�[���̐���
	void Final()  override;	//�V�[���̍폜
	void Update() override;	//�X�V
	void Draw()	  override;	//�`��

private:
	/*���������֐�*/
	void ChangeNextScene();	//���̃V�[����
	void Delete();			//�ŏI�I�ȏ���
	/*�N���X*/
	Title* title;	//�^�C�g���N���X
	/*�ϐ�*/
	int padInput;	//�L�[�ƃp�b�h�̓��͏��
};

