#include"Game.h"
#include"Camera.h"
#include"PlayerManager.h"
#include"Skydome.h"
#include"StageManager.h"
#include"StageChanger.h"
#include"EnemyManager.h"
#include"Collision.h"
/// <summary>
/// コンストラクタ
/// </summary>
Game::Game()
    :isGameOver(false)
    ,isGameClear(false)
    ,camera(nullptr)
    ,playerManager(nullptr)
    ,skydome(nullptr)
    ,stageManager(nullptr)
    ,stageChanger(nullptr)
    ,enemyManager(nullptr)
    ,collision(nullptr)
{
    Create();
    Init();
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
    collision = new Collision();
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
        camera = nullptr;
    }
    //プレイヤーの開放
    if (playerManager)
    {
        delete(playerManager);
        playerManager = nullptr;
    }
    //スカイドームの開放
    if (skydome)
    {
        delete(skydome);
        skydome = nullptr;
    }
    //エネミーの開放
    if (enemyManager)
    {
        delete(enemyManager);
        enemyManager = nullptr;
    }
    //コリジョンの開放
    if (collision)
    {
        delete(collision);
        collision = nullptr;
    }
}
/// <summary>
/// 更新
/// </summary>
void Game::Update()
{
    clsDx();
    if (!playerManager->GetIsShowStatusMenu())
    {
        /*カメラのみ更新*/
        camera->Update(playerManager->GetPos());
        /*移動処理*/
        playerManager->Move(camera->GetCameraToPlayer());
        enemyManager->Move(playerManager->GetPos(), stageChanger->GetIsFarm(), stageChanger->GetIsBoss());
        /*攻撃処理*/
        playerManager->Attack();
        /*コリジョン処理*/
        OnDamage();
        FixMoveVec();
        /*更新処理*/
        playerManager->Update();
        enemyManager->Update(playerManager->GetPos(), stageChanger->GetIsFarm(), stageChanger->GetIsBoss());
        stageChanger->DrawImageWhenSwitchingStage();
    }
    playerManager->StatusUpdate();
    GameEnd(playerManager->GetIsDeath());
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
    playerManager->DrawShadow(stageManager->GetModelHandle());
    enemyManager->DrawShadow(stageManager->GetModelHandle(), stageChanger->GetIsFarm(), stageChanger->GetIsBoss());
}
/// <summary>
/// 移動量補正
/// </summary>
void Game::FixMoveVec()
{
    //プレイヤーの補正
    for (int i = 0; i < enemyManager->GetMaxWeakEnemy(); i++)
    {
        VECTOR fixVec = collision->CapsuleToCapsuleCollision(playerManager->GetMoveVec(), playerManager->GetPos(), enemyManager->GetPosWeakEnemy(i),playerManager->GetCapsuleInfo().radius,enemyManager->GetCapsuleInfoWeakEnemy(i).radius);
        playerManager->FixMoveVec(fixVec);
    }

    //エネミーの補正
    for (int i = 0; i < enemyManager->GetMaxWeakEnemy(); i++)
    {
        VECTOR fixVec = collision->CapsuleToCapsuleCollision(enemyManager->GetMoveVecWeakEnemy(i), enemyManager->GetPosWeakEnemy(i), playerManager->GetPos(), enemyManager->GetCapsuleInfoWeakEnemy(i).radius, playerManager->GetCapsuleInfo().radius);
        enemyManager->FixMoveVecWeakEnemy(i, fixVec);
        for (int j = 0; j < enemyManager->GetMaxWeakEnemy(); j++)
        {
            if (i != j)
            {
                fixVec = collision->CapsuleToCapsuleCollision(enemyManager->GetMoveVecWeakEnemy(i), enemyManager->GetPosWeakEnemy(i), enemyManager->GetPosWeakEnemy(j), enemyManager->GetCapsuleInfoWeakEnemy(i).radius, enemyManager->GetCapsuleInfoWeakEnemy(j).radius);
                enemyManager->FixMoveVecWeakEnemy(i, fixVec);
            }
        }
    }
}
/// <summary>
/// ダメージ判定
/// </summary>
void Game::OnDamage()
{
    //エネミーへの攻撃
    if (playerManager->GetIsAttack())
    {
        for (int i = 0; i < enemyManager->GetMaxWeakEnemy(); i++)
        {
            //当たり判定チェック
            bool isHitEnemy = collision->OnDamage(enemyManager->GetIsInvincible(i), enemyManager->GetIsDeathWeakEnemy(i), enemyManager->GetCapsuleInfoWeakEnemy(i), playerManager->GetSphereInfo());
            //もし攻撃が当たっていたら
            if (isHitEnemy)
            {
                float exp = enemyManager->CalcHPWeakEnemy(i, playerManager->GetAtk());
                if (exp > 0)
                {
                    playerManager->CalcExp(exp);
                    enemyManager->InitExpToGive(i);
                }
                
            }
        }
        

    }
    //プレイヤーへの攻撃
    bool isHitPlayer = false;
    for (int i = 0; i < enemyManager->GetMaxWeakEnemy(); i++)
    {
        //もしエネミーが攻撃していたら
        if (enemyManager->GetIsAttackWeakEnemy(i))
        {
            //攻撃が当たっているかのチェック
            isHitPlayer = collision->OnDamage(playerManager->GetIsInvincible(), playerManager->GetIsDeath(), playerManager->GetCapsuleInfo(), enemyManager->GetSphereInfoWeakEnemy(i));
            //もし攻撃が当たっていたら
            if (isHitPlayer)
            {
                //HP計算
                playerManager->CalcHP(enemyManager->GetAtkWeakEnemy(i));
            }
        }
    }
}
/// <summary>
/// ゲーム終了判定
/// </summary>
void Game::GameEnd(const bool _playerIsDeath)
{
    if (_playerIsDeath)
    {
        isGameOver = true;
    }
}