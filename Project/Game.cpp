#include"Game.h"
#include"Camera.h"
#include"PlayerManager.h"
#include"Skydome.h"
#include"StageManager.h"
#include"StageChanger.h"
#include"EnemyManager.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
Game::Game()
{
    Create();
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
Game::~Game()
{
    //�ŏI���
    Delete();
}
/// <summary>
/// ����
/// </summary>
void Game::Create()
{
    playerManager = new PlayerManager();
    camera = new Camera();
    skydome = new Skydome();
    stageManager = new StageManager();
    stageChanger = new StageChanger();
    enemyManager = new EnemyManager();
    Init();
}
void Game::Init()
{
    playerManager->Init();
    camera->Init(playerManager->GetPos());
    stageManager->Update();
    enemyManager->Init();
}
void Game::Delete()
{
    //�J�����̊J��
    if (camera)
    {
        delete(camera);
        camera = NULL;
    }
    //�v���C���[�̊J��
    if (playerManager)
    {
        delete(playerManager);
        playerManager = NULL;
    }
    //�X�J�C�h�[���̊J��
    if (skydome)
    {
        delete(skydome);
        skydome = NULL;
    }
    //�G�l�~�[�̊J��
    if (enemyManager)
    {
        delete(enemyManager);
        enemyManager = NULL;
    }
}
/// <summary>
/// �X�V
/// </summary>
void Game::Update()
{
    camera->Update(playerManager->GetPos());
    //�ړ�����
    playerManager->Move(camera->GetCameraToPlayer());
    //�U������
    playerManager->Attack();
    //�R���W��������

    //�ʒu���,�X�e�[�^�X�Ȃǂ̍X�V����
    playerManager->Update();
    enemyManager->Update(playerManager->GetPos(),stageChanger->GetIsFarm(),stageChanger->GetIsBoss());
    stageChanger->DrawImageWhenSwitchingStage();
}
/// <summary>
/// �`��
/// </summary>
void Game::Draw()
{
    skydome->Draw();
    stageManager->Draw();
    playerManager->Draw();
    enemyManager->Draw(playerManager->GetPos(), stageChanger->GetIsFarm(), stageChanger->GetIsBoss());
}
