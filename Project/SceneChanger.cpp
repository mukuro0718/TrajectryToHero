//===========================================================================
//@brief �V�[���`�F���W�N���X
// �e�V�[���̐؂�ւ����s��
//===========================================================================
#include"SceneChanger.h"

SceneChanger* SceneChanger::sceneChange = NULL;

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneChanger::SceneChanger()
{
	nowSceneType	 = SceneType::OPENING;		//���݂̃V�[���̎��
	//nowSceneType = GAMEOVER;		//���݂̃V�[���̎��
	isSceneChanger	 = false;		//�؂�ւ��t���O
	sceneChangeTimer = FIRST_TIMER;	//�V�[���؂�ւ�����
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneChanger::~SceneChanger()
{
	//�����Ȃ�
}
/// <summary>
/// ���̃V�[���ɐ؂�ւ���
/// </summary>
/// <param name="nowSceneType">���݂̃V�[��</param>
/// <param name="nextSceneType">���̃V�[��</param>
void SceneChanger::ChangeSceneFromNowToNext(SceneType _nowSceneType, SceneType _nextSceneType)
{
	//�V�[����؂�ւ���
	if (isSceneChanger == true)
	{
		//�V�[����������������i�����ɐ؂�ւ��Ȃ��悤�ɑҋ@���Ԃ�݂���j
		if (this->nowSceneType == _nowSceneType)
		{
			sceneChangeTimer++;//�^�C�}�[�v��
			if (sceneChangeTimer >= LAST_TIMER)//�����^�C�}�[���Q�O�ȏゾ������
			{
				//���̃V�[���ɐ؂�ւ���
				this->nowSceneType = _nextSceneType;
				isSceneChanger = false;
				sceneChangeTimer = FIRST_TIMER;
			}
		}
	}
}