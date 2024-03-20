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

	const void Create()	override;	//����
	const void Final()	override;	//�ŏI����
	const void Update()	override;	//�X�V
	const void Draw()	override;	//�`��
private:
	/*���������֐�*/
	const void ChangeNextScene();	//���̃V�[����
	/*�����o�ϐ�*/
	Opening* opening;	//�I�[�v�j���O�N���X
};