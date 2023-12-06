//===========================================================================
//@brief �Q�[���N���A�V�[���N���X
// �Q�[���N���A�N���X�̎��s���V�[���x�[�X�N���X�����Ƃɍs��
//===========================================================================
#pragma once
#include"SceneBase.h"
#include"ScenesCommon.h"

class GameClear;

class GameClearScene :public SceneBase
{
public:
	GameClearScene();	//�R���X�g���N�^
	~GameClearScene();	//�f�X�g���N�^

	void Create()	override;	//����
	void Final()	override;	//�ŏI����
	void Update()	override;	//�X�V
	void Draw()		override;	//�`��
private:
	/*���������֐�*/
	void ChangeNextScene();	//���̃V�[����
	/*�����o�ϐ�*/
	GameClear* gameClear;	//�I�[�v�j���O�N���X
};