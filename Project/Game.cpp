#include"Game.h"
#include"Camera.h"
#include"PlayerManager.h"
#include"Skydome.h"
#include"StageManager.h"
#include"StageChanger.h"

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
    Init();
}
void Game::Init()
{
    playerManager->Init();
    camera->Init(playerManager->GetPos());
    stageManager->Update();
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
    //�v���C���[�̊J��
    if (skydome)
    {
        delete(skydome);
        skydome = NULL;
    }
}
/// <summary>
/// �X�V
/// </summary>
void Game::Update()
{
    camera->Update(playerManager->GetPos());
    playerManager->Update(camera->GetCameraToPlayer());
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
}
