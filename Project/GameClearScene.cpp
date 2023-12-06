//===========================================================================
//@brief �Q�[���N���A�V�[���N���X
// �Q�[���N���A�N���X�̎��s���V�[���x�[�X�N���X�����Ƃɍs��
//===========================================================================
#include"GameClearScene.h"
#include"SceneChanger.h"
#include"GameClear.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
GameClearScene::GameClearScene()
{
	gameClear = NULL;
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
GameClearScene::~GameClearScene()
{
	Final();
}
/// <summary>
/// �쐬
/// </summary>
void GameClearScene::Create()
{
	gameClear = new GameClear();
}
/// <summary>
/// �폜
/// </summary>
void GameClearScene::Final()
{
	if (gameClear)
	{
		delete(gameClear);
		gameClear = NULL;
	}
}
/// <summary>
/// �X�V
/// </summary>
void GameClearScene::Update()
{
	//�X�V
	gameClear->Update();
	//�V�[���؂�ւ��i�t���O�����������j
	ChangeNextScene();
}
/// <summary>
/// �`��
/// </summary>
void GameClearScene::Draw()
{
	gameClear->Draw();
}

/// <summary>
/// ���̃V�[����
/// </summary>
void GameClearScene::ChangeNextScene()
{
	//�C���X�^���X���擾
	auto& sceneChange = SceneChanger::GetInstance();

	//�����I�[�v�j���O���I�����Ă�����
	if (gameClear->GetIsEndGameClearImage())
	{
		//�V�[���`�F���W���ғ�������
		sceneChange.SetIsSceneChanger(true);
		//���݂̃V�[������^�C�g���V�[����
		sceneChange.ChangeSceneFromNowToNext(SceneType::GAMECLEAR, SceneType::TITLE);
	}
}
