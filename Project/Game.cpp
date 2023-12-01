#include"Game.h"
#include"Camera.h"
#include"PlayerManager.h"
#include"Skydome.h"
#include"StageManager.h"
#include"StageChanger.h"
#include"EnemyManager.h"
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
    //スカイドームの開放
    if (skydome)
    {
        delete(skydome);
        skydome = NULL;
    }
    //エネミーの開放
    if (enemyManager)
    {
        delete(enemyManager);
        enemyManager = NULL;
    }
}
/// <summary>
/// 更新
/// </summary>
void Game::Update()
{
    camera->Update(playerManager->GetPos());
    //移動処理
    playerManager->Move(camera->GetCameraToPlayer());
    //攻撃処理
    playerManager->Attack();
    //コリジョン処理

    //位置情報,ステータスなどの更新処理
    playerManager->Update();
    enemyManager->Update(playerManager->GetPos(),stageChanger->GetIsFarm(),stageChanger->GetIsBoss());
    stageChanger->DrawImageWhenSwitchingStage();
}
/// <summary>
/// 描画
/// </summary>
void Game::Draw()
{
    skydome->Draw();
    stageManager->Draw();
    playerManager->Draw();
    enemyManager->Draw(playerManager->GetPos(), stageChanger->GetIsFarm(), stageChanger->GetIsBoss());
}
