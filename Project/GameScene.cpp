#include"GameScene.h"
#include"SceneChanger.h"
#include"Game.h"
#include"Common.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameScene::GameScene()
{
	game = NULL;
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
GameScene::~GameScene()
{
	Final();
}
/// <summary>
/// �쐬
/// </summary>
void GameScene::Create()
{
	game = new Game();
}
/// <summary>
/// �폜
/// </summary>
void GameScene::Final()
{
	if (game)
	{
		delete(game);
		game = NULL;
	}
}
/// <summary>
/// �X�V
/// </summary>
void GameScene::Update()
{
	//�X�V
	game->Update();
	//�V�[���؂�ւ��i�t���O�����������j
	ChangeNextScene();
}
/// <summary>
/// �`��
/// </summary>
void GameScene::Draw()
{
	//�`��
	game->Draw();
}

/// <summary>
/// ���̃V�[����
/// </summary>
void GameScene::ChangeNextScene()
{
	//�C���X�^���X���擾
	auto& sceneChange = SceneChanger::GetInstance();
	bool isGameOver = game->GetIsGameOver();
	bool isGameClear = game->GetIsGameClear();

	//�����I�[�v�j���O���I�����Ă�����
	if (isGameClear)
	{
		//�V�[���`�F���W���ғ�������
		sceneChange.SetIsSceneChanger(true);
		sceneChange.ChangeSceneFromNowToNext(SceneType::GAME, SceneType::GAMECLEAR);
	}
	else if(isGameOver)
	{
		//�V�[���`�F���W���ғ�������
		sceneChange.SetIsSceneChanger(true);
		sceneChange.ChangeSceneFromNowToNext(SceneType::GAME, SceneType::GAMEOVER);
	}
}
