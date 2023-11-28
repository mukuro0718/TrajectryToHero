#include"Game.h"
#include"Camera.h"
#include"PlayerManager.h"
#include"Skydome.h"

/// <summary>
/// コンストラクタ
/// </summary>
Game::Game()
{
    Create();

}
/// <summary>
/// デストラクタ
/// </summary>
Game::~Game()
{
    //最終解放
    Delete();
}
/// <summary>
/// 生成
/// </summary>
void Game::Create()
{
    playerManager = new PlayerManager();
    camera = new Camera();
    skydome = new Skydome();
    Init();
}
void Game::Init()
{
    playerManager->Init();
    camera->Init(playerManager->GetPos());
}
void Game::Delete()
{
    //カメラの開放
    if (camera)
    {
        delete(camera);
        camera = NULL;
    }
    //プレイヤーの開放
    if (playerManager)
    {
        delete(playerManager);
        playerManager = NULL;
    }
    //プレイヤーの開放
    if (skydome)
    {
        delete(skydome);
        skydome = NULL;
    }
}
/// <summary>
/// 更新
/// </summary>
void Game::Update()
{
    camera->Update(playerManager->GetPos());
    playerManager->Update(camera->GetCameraToPlayer());

}
/// <summary>
/// 描画
/// </summary>
void Game::Draw()
{
    playerManager->Draw();
    skydome->Draw();
}
