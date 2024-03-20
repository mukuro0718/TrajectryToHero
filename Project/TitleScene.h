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

	const void Create() override;	//�V�[���̐���
	const void Final()  override;	//�V�[���̍폜
	const void Update() override;	//�X�V
	const void Draw()	override;	//�`��

private:
	/*���������֐�*/
	const void ChangeNextScene();	//���̃V�[����
	const void Delete();			//�ŏI�I�ȏ���
	/*�N���X*/
	Title* title;	//�^�C�g���N���X
	/*�ϐ�*/
	int padInput;	//�L�[�ƃp�b�h�̓��͏��
};

