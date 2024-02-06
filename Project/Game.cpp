#include"Game.h"
#include"Camera.h"
#include"PlayerManager.h"
#include"Skydome.h"
#include"StageManager.h"
#include"StageChanger.h"
#include"EnemyManager.h"
#include"Collision.h"
#include"Load.h"
const int Game::MOVE_RANGE_COLOR = GetColor(200,200,200);

/// <summary>
/// コンストラクタ
/// </summary>
Game::Game()
    :isGameOver(false)
    , isGameClear(false)
    , camera(nullptr)
    , playerManager(nullptr)
    , skydome(nullptr)
    , stageManager(nullptr)
    , stageChanger(nullptr)
    , enemyManager(nullptr)
    , collision(nullptr)
    , victoryImage(0)
    , alpha(0)
    , isFrameCount(false)
{
    auto& load = Load::GetInstance();
    load.GetVictoryData(&victoryImage);
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
    stageChanger->Init();
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
    stageManager->Update(static_cast<int>(playerManager->GetLv()));

    if (!playerManager->GetIsShowStatusMenu())
    {
        enemyManager->AdjustTheNumberOfEnemy(static_cast<int>(playerManager->GetLv()));
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
        enemyManager->Update(playerManager->GetPos(), playerManager->GetLv(), stageChanger->GetIsFarm(), stageChanger->GetIsBoss());
        stageChanger->DrawImageWhenSwitchingStage();
    }
    else
    {
        playerManager->PhysicalRecovery();
    }
    playerManager->StatusUpdate(stageManager->GetBonfirePos());
}
/// <summary>
/// 描画
/// </summary>
void Game::Draw()
{
    skydome->Draw();
    stageChanger->Draw();
    stageManager->Draw(stageChanger->GetIsFarm());
    DrawMoveRange();
    playerManager->DrawShadow(stageManager->GetModelHandle());
    enemyManager->DrawShadow(stageManager->GetModelHandle(), stageChanger->GetIsFarm(), stageChanger->GetIsBoss());
    enemyManager->Draw(playerManager->GetPos(), stageChanger->GetIsFarm(), stageChanger->GetIsBoss());
    playerManager->Draw(stageManager->GetBonfirePos());
    if (!stageChanger->GetIsBoss())
    {
        bool isChangeStage = stageChanger->DrawAlert(playerManager->GetPos(), stageManager->GetGatePos(), stageManager->GetIsShowGate());
        if (isChangeStage)
        {
            playerManager->InitPos();
        }
    }
    if (!stageChanger->GetIsAlert())
    {
        stageChanger->DrawImageWhenSwitchingStage();
    }
    GameEnd(playerManager->GetIsDeath(), enemyManager->GetIsDeathBossEnemy());
}
const void Game::DrawMoveRange()const
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
    DrawTriangle3D(MOVE_RANGE_POS_LTB, MOVE_RANGE_POS_LBB, MOVE_RANGE_POS_LTT,MOVE_RANGE_COLOR,TRUE);
    DrawTriangle3D(MOVE_RANGE_POS_LBB, MOVE_RANGE_POS_LTB, MOVE_RANGE_POS_LBT, MOVE_RANGE_COLOR, TRUE);
    DrawTriangle3D(MOVE_RANGE_POS_LTB, MOVE_RANGE_POS_RTB, MOVE_RANGE_POS_RTT, MOVE_RANGE_COLOR, TRUE);
    DrawTriangle3D(MOVE_RANGE_POS_RTB, MOVE_RANGE_POS_LTB, MOVE_RANGE_POS_LTT, MOVE_RANGE_COLOR, TRUE);
    DrawTriangle3D(MOVE_RANGE_POS_LBB, MOVE_RANGE_POS_RBB, MOVE_RANGE_POS_RBT, MOVE_RANGE_COLOR, TRUE);
    DrawTriangle3D(MOVE_RANGE_POS_RBB, MOVE_RANGE_POS_LBB, MOVE_RANGE_POS_LBT, MOVE_RANGE_COLOR, TRUE);
    DrawTriangle3D(MOVE_RANGE_POS_RTB, MOVE_RANGE_POS_RBB, MOVE_RANGE_POS_RBT, MOVE_RANGE_COLOR, TRUE);
    DrawTriangle3D(MOVE_RANGE_POS_RBB, MOVE_RANGE_POS_RTB, MOVE_RANGE_POS_RTT, MOVE_RANGE_COLOR, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_ALPHA_VALUE);
}

/// <summary>
/// 移動量補正
/// </summary>
void Game::FixMoveVec()
{
    if (stageChanger->GetIsFarm())
    {
        /*プレイヤーの補正*/
        //雑魚敵との接触判定
        for (int i = 0; i < enemyManager->GetNowWeakEnemyNum(); i++)
        {
            VECTOR fixVec = collision->CapsuleToCapsuleCollision(playerManager->GetMoveVec(), playerManager->GetPos(), enemyManager->GetPosWeakEnemy(i), playerManager->GetCapsuleInfo().radius, enemyManager->GetCapsuleInfoWeakEnemy(i).radius);
            playerManager->FixMoveVec(fixVec);
        }
        //チューボスとの接触判定
        for (int i = 0; i < enemyManager->GetNowStrongEnemyNum(); i++)
        {
            VECTOR fixVec = collision->CapsuleToCapsuleCollision(playerManager->GetMoveVec(), playerManager->GetPos(), enemyManager->GetPosStrongEnemy(i), playerManager->GetCapsuleInfo().radius, enemyManager->GetCapsuleInfoWeakEnemy(i).radius);
            playerManager->FixMoveVec(fixVec);
        }
        /*エネミーの補正*/
        //雑魚敵の接触判定判定
        for (int i = 0; i < enemyManager->GetNowWeakEnemyNum(); i++)
        {
            //プレイヤーとの接触判定
            VECTOR fixVec = collision->CapsuleToCapsuleCollision(enemyManager->GetMoveVecWeakEnemy(i), enemyManager->GetPosWeakEnemy(i), playerManager->GetPos(), enemyManager->GetCapsuleInfoWeakEnemy(i).radius, playerManager->GetCapsuleInfo().radius);
            enemyManager->FixMoveVecWeakEnemy(i, fixVec);
            //雑魚敵との接触判定
            for (int j = 0; j < enemyManager->GetNowWeakEnemyNum(); j++)
            {
                if (i != j)
                {
                    fixVec = collision->CapsuleToCapsuleCollision(enemyManager->GetMoveVecWeakEnemy(i), enemyManager->GetPosWeakEnemy(i), enemyManager->GetPosWeakEnemy(j), enemyManager->GetCapsuleInfoWeakEnemy(i).radius, enemyManager->GetCapsuleInfoWeakEnemy(j).radius);
                    enemyManager->FixMoveVecWeakEnemy(i, fixVec);
                }
            }
            //中ボスとの接触判定
            for (int j = 0; j < enemyManager->GetNowStrongEnemyNum(); j++)
            {
                fixVec = collision->CapsuleToCapsuleCollision(enemyManager->GetMoveVecWeakEnemy(i), enemyManager->GetPosWeakEnemy(i), enemyManager->GetPosStrongEnemy(j), enemyManager->GetCapsuleInfoWeakEnemy(i).radius, enemyManager->GetCapsuleInfoStrongEnemy(j).radius);
                enemyManager->FixMoveVecWeakEnemy(i, fixVec);
            }
        }

        //雑魚敵の接触判定判定
        for (int i = 0; i < enemyManager->GetNowStrongEnemyNum(); i++)
        {
            //プレイヤーとの接触判定
            VECTOR fixVec = collision->CapsuleToCapsuleCollision(enemyManager->GetMoveVecStrongEnemy(i), enemyManager->GetPosStrongEnemy(i), playerManager->GetPos(), enemyManager->GetCapsuleInfoStrongEnemy(i).radius, playerManager->GetCapsuleInfo().radius);
            enemyManager->FixMoveVecStrongEnemy(i, fixVec);
            //雑魚敵との接触判定
            for (int j = 0; j < enemyManager->GetNowWeakEnemyNum(); j++)
            {
                fixVec = collision->CapsuleToCapsuleCollision(enemyManager->GetMoveVecStrongEnemy(i), enemyManager->GetPosStrongEnemy(i), enemyManager->GetPosWeakEnemy(j), enemyManager->GetCapsuleInfoStrongEnemy(i).radius, enemyManager->GetCapsuleInfoWeakEnemy(j).radius);
                enemyManager->FixMoveVecStrongEnemy(i, fixVec);
            }
            //中ボスとの接触判定
            for (int j = 0; j < enemyManager->GetNowStrongEnemyNum(); j++)
            {
                if (i != j)
                {
                    fixVec = collision->CapsuleToCapsuleCollision(enemyManager->GetMoveVecStrongEnemy(i), enemyManager->GetPosStrongEnemy(i), enemyManager->GetPosStrongEnemy(j), enemyManager->GetCapsuleInfoStrongEnemy(i).radius, enemyManager->GetCapsuleInfoStrongEnemy(j).radius);
                    enemyManager->FixMoveVecStrongEnemy(i, fixVec);
                }
            }
        }

    }
    else if (stageChanger->GetIsBoss())
    {
        VECTOR fixVec = collision->CapsuleToCapsuleCollision(playerManager->GetMoveVec(), playerManager->GetPos(), enemyManager->GetPosBossEnemy(), playerManager->GetCapsuleInfo().radius, enemyManager->GetCapsuleInfoBossEnemy().radius);
        playerManager->FixMoveVec(fixVec);
        fixVec = collision->CapsuleToCapsuleCollision(enemyManager->GetMoveVecBossEnemy(), enemyManager->GetPosBossEnemy(), playerManager->GetPos(), enemyManager->GetCapsuleInfoBossEnemy().radius, playerManager->GetCapsuleInfo().radius);
        enemyManager->FixMoveVecBossEnemy(fixVec);
    }
}
/// <summary>
/// ダメージ判定
/// </summary>
void Game::OnDamage()
{
    /*
    攻撃をした側から受けた側へ向かうベクトルを取出す
    ↑このベクトルをもとに、キャラクターごとに血の飛ぶ方向を決めればよい？
    */
    if (stageChanger->GetIsFarm())
    {
        //エネミーへの攻撃
        if (playerManager->GetIsAttack())
        {
            /*雑魚敵*/
            for (int i = 0; i < enemyManager->GetNowWeakEnemyNum(); i++)
            {
                //当たり判定チェック
                bool isHitEnemy = collision->OnDamage(enemyManager->GetIsInvincibleWeakEnemy(i), enemyManager->GetIsDeathWeakEnemy(i), enemyManager->GetCapsuleInfoWeakEnemy(i), playerManager->GetSphereInfo());
                //もし攻撃が当たっていたら
                if (isHitEnemy)
                {
                    float exp = enemyManager->CalcHPWeakEnemy(i, playerManager->GetAtk(),playerManager->GetPos());
                    if (exp > 0)
                    {
                        playerManager->CalcExp(exp);
                        enemyManager->InitExpToGive(i);
                    }
                }
            }
            /*中ボス*/
            for (int i = 0; i < enemyManager->GetNowStrongEnemyNum(); i++)
            {
                //当たり判定チェック
                bool isHitEnemy = collision->OnDamage(enemyManager->GetIsInvincibleStrongEnemy(i), enemyManager->GetIsDeathStrongEnemy(i), enemyManager->GetCapsuleInfoStrongEnemy(i), playerManager->GetSphereInfo());
                //もし攻撃が当たっていたら
                if (isHitEnemy)
                {
                    float exp = enemyManager->CalcHPStrongEnemy(i, playerManager->GetAtk(), playerManager->GetPos());
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
        for (int i = 0; i < enemyManager->GetNowWeakEnemyNum(); i++)
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
                    playerManager->CalcHP(enemyManager->GetAtkWeakEnemy(i),enemyManager->GetPosWeakEnemy(i));
                }
            }
        }
        for (int i = 0; i < enemyManager->GetNowStrongEnemyNum(); i++)
        {
            //もしエネミーが攻撃していたら
            if (enemyManager->GetIsAttackStrongEnemy(i))
            {
                //攻撃が当たっているかのチェック
                isHitPlayer = collision->OnDamage(playerManager->GetIsInvincible(), playerManager->GetIsDeath(), playerManager->GetCapsuleInfo(), enemyManager->GetSphereInfoStrongEnemy(i));
                //もし攻撃が当たっていたら
                if (isHitPlayer)
                {
                    //HP計算
                    playerManager->CalcHP(enemyManager->GetAtkStrongEnemy(i), enemyManager->GetPosStrongEnemy(i));
                }
            }
        }
    }
    if (stageChanger->GetIsBoss())
    {
        if (playerManager->GetIsAttack())
        {
            //当たり判定チェック
            bool isHitEnemy = collision->OnDamage(enemyManager->GetIsInvincibleBossEnemy(), enemyManager->GetIsDeathBossEnemy(), enemyManager->GetCapsuleInfoBossEnemy(), playerManager->GetSphereInfo());
            //もし攻撃が当たっていたら
            if (isHitEnemy)
            {
                float exp = enemyManager->CalcHPBossEnemy(playerManager->GetAtk(), playerManager->GetPos());
                if (exp > 0)
                {
                    playerManager->CalcExp(exp);
                }
            }
        }
        else
        {
            enemyManager->FlaggingBossEnemy();
        }
        if (enemyManager->GetIsAttackBossEnemy())
        {
            bool isHitPlayer = collision->OnDamage(playerManager->GetIsInvincible(), playerManager->GetIsDeath(), playerManager->GetCapsuleInfo(), enemyManager->GetSphereInfoBossEnemy());
            //もし攻撃が当たっていたら
            if (isHitPlayer)
            {
                //HP計算
                playerManager->CalcHP(enemyManager->GetAtkBossEnemy(),enemyManager->GetPosBossEnemy());
            }
        }
        
    }
}
/// <summary>
/// ゲーム終了判定
/// </summary>
void Game::GameEnd(const bool _playerIsDeath, const bool _bossIsDeath)
{
    if (_bossIsDeath)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
        DrawExtendGraph(VICTORY_LOGO_POS.lx, VICTORY_LOGO_POS.ly, VICTORY_LOGO_POS.rx, VICTORY_LOGO_POS.ry, victoryImage, TRUE);
        //DrawExtendString(VICTORY_LOGO_POS.lx, VICTORY_LOGO_POS.ly, 2.0, 2.0, "VICTORY", GetColor(200, 200, 0));
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_ALPHA_VALUE);
        if (!isFrameCount)
        {
            alpha += ADD_ALPHA_VALUE;
            if (alpha >= MAX_ALPHA_VALUE)
            {
                isFrameCount = true;
            }
        }
        else
        {
            if (frameCount != MAX_FRAME_COUNT)
            {
                frameCount++;
            }
            else
            {
                alpha -= ADD_ALPHA_VALUE;
                if (alpha < MIN_ALPHA_VALUE)
                {
                    isGameClear = true;
                }
            }
        }
    }
    if (_playerIsDeath)
    {
        enemyManager->PhysicalRecoveryBossEnemy();
        playerManager->ReSpawn();
        stageChanger->ChangeStage();
    }
}