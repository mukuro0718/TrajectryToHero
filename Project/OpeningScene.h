//===========================================================================
//@brief �I�[�v�j���O�V�[���N���X
// �I�[�v�j���O�N���X�̎��s���V�[���x�[�X�N���X�����Ƃɍs��
//===========================================================================

#pragma once
#include"SceneBase.h"
class Opening;

class OpeningScene :public SceneBase
{
public:
	OpeningScene();			//�R���X�g���N�^
	virtual ~OpeningScene();//�f�X�g���N�^

	void Create()	override;	//����
	void Final()	override;	//�ŏI����
	void Update()	override;	//�X�V
	void Draw()		override;	//�`��
private:
	/*���������֐�*/
	void ChangeNextScene();	//���̃V�[����
	/*�����o�ϐ�*/
	Opening* opening;	//�I�[�v�j���O�N���X
};