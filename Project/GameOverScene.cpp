//===========================================================================
//@brief �Q�[���I�[�o�[�V�[���N���X
// �Q�[���I�[�o�[�N���X�̎��s���V�[���x�[�X�N���X�����Ƃɍs��
//===========================================================================
#include"GameOverScene.h"
#include"SceneChanger.h"
#include"GameOver.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
GameOverScene::GameOverScene()
{
	gameOver = NULL;
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
GameOverScene::~GameOverScene()
{
	Final();
}
/// <summary>
/// �쐬
/// </summary>
void GameOverScene::Create()
{
	gameOver = new GameOver();
}
/// <summary>
/// �폜
/// </summary>
void GameOverScene::Final()
{
	if (gameOver)
	{
		delete(gameOver);
		gameOver = NULL;
	}
}
/// <summary>
/// �X�V
/// </summary>
void GameOverScene::Update()
{
	//�X�V
	gameOver->Update();
	//�V�[���؂�ւ��i�t���O�����������j
	ChangeNextScene();
}
/// <summary>
/// �`��
/// </summary>
void GameOverScene::Draw()
{
	gameOver->Draw();
}

/// <summary>
/// ���̃V�[����
/// </summary>
void GameOverScene::ChangeNextScene()
{
	//�C���X�^���X���擾
	auto& sceneChange = SceneChanger::GetInstance();

	//�����I�[�v�j���O���I�����Ă�����
	if (gameOver->GetIsEndGameOverImage())
	{
		//�V�[���`�F���W���ғ�������
		sceneChange.SetIsSceneChanger(true);
		//���݂̃V�[������^�C�g���V�[����
		sceneChange.ChangeSceneFromNowToNext(SceneType::GAMEOVER, SceneType::TITLE);
	}
}
