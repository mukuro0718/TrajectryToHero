#include"Game.h"
#include"Camera.h"
#include"PlayerManager.h"
#include"Skydome.h"
#include"StageManager.h"
#include"StageChanger.h"
#include"EnemyManager.h"
#include"Collision.h"
#include"Load.h"
#include"StatusUpParticle.h"
#include"Meteorite.h"
#include"Explosion.h"
#include"LightSword.h"


const int Game::MOVE_RANGE_COLOR = GetColor(200,200,200);
const int Game::FONT_COLOR = GetColor(200, 200, 200);

/// <summary>
/// コンストラクタ
/// </summary>
Game::Game()
    : isGameOver        (false)
    , isGameClear       (false)
    , isFrameCount      (false)
    , statusUpParticle  (nullptr)
    , playerManager     (nullptr)
    , stageManager      (nullptr)
    , stageChanger      (nullptr)
    , enemyManager      (nullptr)
    , lightSword        (nullptr)
    , collision         (nullptr)
    , explosion         (nullptr)
    , skydome           (nullptr)
    , camera            (nullptr)
    , meteo             (nullptr)
    , victoryImage      (0)
    , alpha             (0)
    , youDiedImage      (0)
    , strongUI          (0)

{
    auto& load = Load::GetInstance();
    load.GetVictoryData(&victoryImage);
    load.GetDiedData(&youDiedImage);
    load.GetStrongerUIData(&strongUI);
    textFont = CreateFontToHandle("Data/Font/Honoka_Shin_Mincho_L.otf", 24, 32, DX_FONTTYPE_NORMAL);
    youDiedFont = CreateFontToHandle("Data/Img/Font/HelpMe.ttf", 150, 32, DX_FONTTYPE_NORMAL);
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
const void Game::Create()
{
    playerManager    = new PlayerManager();
    statusUpParticle = new StatusUpParticle(playerManager->GetLv());
    stageManager     = new StageManager();
    stageChanger     = new StageChanger();
    enemyManager     = new EnemyManager();
    lightSword       = new LightSword();
    collision        = new Collision(enemyManager->GetMaxWeakEnemy(),enemyManager->GetMaxStrongEnemy());
    explosion        = new Explosion();
    skydome          = new Skydome();
    camera           = new Camera();
    meteo            = new Meteorite();


}
const void Game::Init()
{
    playerManager->Init();
    camera->Init(playerManager->GetPos());
    camera->SetFarmStageInitAngle();
    stageChanger->Init();
    enemyManager->Init();
}
const void Game::Delete()
{
    //プレイヤーの開放
    if (playerManager)
    {
        delete(playerManager);
        playerManager = nullptr;
    }
    //ステータス上昇パーティクルの開放
    if (statusUpParticle)
    {
        delete(statusUpParticle);
        statusUpParticle = nullptr;
    }
    //ステージの開放
    if (stageManager)
    {
        delete(stageManager);
        stageManager = nullptr;
    }
    //ステージ変更の開放
    if (stageChanger)
    {
        delete(stageChanger);
        stageChanger = nullptr;
    }
    //エネミーの開放
    if (enemyManager)
    {
        delete(enemyManager);
        enemyManager = nullptr;
    }
    //光の剣の開放
    if (lightSword)
    {
        delete(lightSword);
        lightSword = nullptr;
    }
    //コリジョンの開放
    if (collision)
    {
        delete(collision);
        collision = nullptr;
    }
    //爆発の開放
    if (explosion)
    {
        delete(explosion);
        explosion = nullptr;
    }
    //スカイドームの開放
    if (skydome)
    {
        delete(skydome);
        skydome = nullptr;
    }
    //カメラの開放
    if (camera)
    {
        delete(camera);
        camera = nullptr;
    }
    if (meteo)
    {
        delete(meteo);
        meteo = nullptr;
    }
}
/// <summary>
/// 更新
/// </summary>
const void Game::Update()
{
    stageManager->Update(static_cast<int>(playerManager->GetLv()));

    if (!playerManager->GetIsShowStatusMenu())
    {
        enemyManager->AdjustTheNumberOfEnemy(static_cast<int>(playerManager->GetLv()));
        ///*カメラのみ更新*/
        //camera->Update(playerManager->GetPos());
        /*移動処理*/
        playerManager->Move(camera->GetCameraToPlayer());
        enemyManager->Move(playerManager->GetPos(), stageChanger->GetIsFarm(), stageChanger->GetIsBoss());
        /*攻撃処理*/
        playerManager->Attack();
        meteo->Update(enemyManager->GetIsMeteoAttack());
        explosion->Update(enemyManager->GetIsExplosionAttack(), enemyManager->GetPosBossEnemy());
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
    statusUpParticle->Update(playerManager->GetPos(), playerManager->GetIsBonfireMenu(),playerManager->GetLv());
    lightSword->Update(MV1GetFramePosition(playerManager->GetModelHandle(),67), MV1GetFramePosition(playerManager->GetModelHandle(), 68), MV1GetFramePosition(playerManager->GetModelHandle(), 69));

}
/// <summary>
/// 描画
/// </summary>
const void Game::Draw()
{
    skydome->SetDrawScreenType(camera->GetAngleX());
    camera->Update(playerManager->GetPos());
    skydome->Draw();
    stageChanger->Draw();
    stageManager->Draw(stageChanger->GetIsFarm());
    DrawMoveRange();
    meteo->Draw(stageManager->GetModelHandle());
    playerManager->DrawShadow(stageManager->GetModelHandle());
    enemyManager->DrawShadow(stageManager->GetModelHandle(), stageChanger->GetIsFarm(), stageChanger->GetIsBoss());
    enemyManager->Draw(playerManager->GetPos(), stageChanger->GetIsFarm(), stageChanger->GetIsBoss());
    for (int i = 0; i < enemyManager->GetNowStrongEnemyNum(); i++)
    {
        enemyManager->DrawMagicSphere(i);
    }
    enemyManager->DrawStrongerUI(playerManager->GetLv(),stageChanger->GetIsFarm());
    VECTOR playerToExplosion = VSub(playerManager->GetPos(), explosion->GetSphereInfo().centerPos);
    if (VSize(playerToExplosion) <= explosion->GetSphereInfo().radius)
    {
        lightSword->Draw();
        playerManager->Draw(stageManager->GetBonfirePos());
        explosion->Draw();
    }
    else
    {
        explosion->Draw();
        lightSword->Draw();
        playerManager->Draw(stageManager->GetBonfirePos());
    }
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
    statusUpParticle->Draw(playerManager->GetIsBonfireMenu());
    playerManager->DrawMenu();


    
    skydome->BloomProg();
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
const void Game::FixMoveVec()
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
const void Game::OnDamage()
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
                //もしプレイヤーの攻撃番号と対応するエネミーのヒット番号が異なっていたら当たり判定を行う
                if (playerManager->GetAttackNum() != collision->GetHitNumWeakEnemy(i))
                {
                    //当たり判定チェック
                    bool isHitEnemy = collision->OnDamage(enemyManager->GetIsDeathWeakEnemy(i), enemyManager->GetCapsuleInfoWeakEnemy(i), playerManager->GetSphereInfo());
                    //もし攻撃が当たっていたら
                    if (isHitEnemy)
                    {
                        //コリジョン側のヒット番号と攻撃側の攻撃番号を合わせる
                        for (int j = 0; j < playerManager->GetAttackNum() - collision->GetHitNumWeakEnemy(i); j++)
                        {
                            collision->AddHitNumWeakEnemy(i);
                        }
                        //経験値の計算
                        float exp = enemyManager->CalcHPWeakEnemy(i, playerManager->GetAtk(), playerManager->GetPos());
                        //対象のエネミーが死亡して、経験値が入ってきたら処理を行う
                        if (exp > 0)
                        {
                            playerManager->CalcExp(exp);
                            enemyManager->InitExpToGive(i);
                        }
                    }
                }
            }
            /*中ボス*/
            for (int i = 0; i < enemyManager->GetNowStrongEnemyNum(); i++)
            {
                if (playerManager->GetAttackNum() != collision->GetHitNumStrongEnemy(i))
                {
                    //当たり判定チェック
                    bool isHitEnemy = collision->OnDamage(enemyManager->GetIsDeathStrongEnemy(i), enemyManager->GetCapsuleInfoStrongEnemy(i), playerManager->GetSphereInfo());
                    //もし攻撃が当たっていたら
                    if (isHitEnemy)
                    {
                        //コリジョン側のヒット番号と攻撃側の攻撃番号を合わせる
                        for (int j = 0; j < playerManager->GetAttackNum() - collision->GetHitNumStrongEnemy(i); j++)
                        {
                            collision->AddHitNumStrongEnemy(i);
                        }
                        float exp = enemyManager->CalcHPStrongEnemy(i, playerManager->GetAtk(), playerManager->GetPos());
                        if (exp > 0)
                        {
                            playerManager->CalcExp(exp);
                            enemyManager->InitExpToGive(i);
                        }
                    }
                }
            }
        }

        //プレイヤーへの攻撃
        bool isHitPlayer = false;
        for (int i = 0; i < enemyManager->GetNowWeakEnemyNum(); i++)
        {
            if (enemyManager->GetAttackNumWeakEnemy(i) != collision->GetHitNumPlayerForWeakEnemy(i))
            {
                //もしエネミーが攻撃していたら
                if (enemyManager->GetIsAttackWeakEnemy(i))
                {
                    //攻撃が当たっているかのチェック
                    isHitPlayer = collision->OnDamage(playerManager->GetIsDeath(), playerManager->GetCapsuleInfo(), enemyManager->GetSphereInfoWeakEnemy(i));
                    //もしプレイヤーに当たっていたら
                    if (isHitPlayer)
                    {
                        //コリジョン側のヒット番号と攻撃側の攻撃番号を合わせる
                        for (int j = 0; j < enemyManager->GetAttackNumWeakEnemy(i) - collision->GetHitNumPlayerForWeakEnemy(i); j++)
                        {
                            collision->AddHitNumPlayerForWeakEnemy(i);
                        }
                        //HP計算
                        playerManager->CalcHP(enemyManager->GetAtkWeakEnemy(i), enemyManager->GetPosWeakEnemy(i));
                    }
                }
            }
        }
        for (int i = 0; i < enemyManager->GetNowStrongEnemyNum(); i++)
        {
            if (enemyManager->GetAttackNumStrongEnemy(i) != collision->GetHitNumPlayerForStrongEnemy(i))
            {
                //もしエネミーが攻撃していたら
                if (enemyManager->GetIsAttackStrongEnemy(i))
                {
                    //攻撃が当たっているかのチェック
                    isHitPlayer = collision->OnDamage(playerManager->GetIsDeath(), playerManager->GetCapsuleInfo(), enemyManager->GetSphereInfoStrongEnemy(i));
                    if (isHitPlayer)
                    {
                        //コリジョン側のヒット番号と攻撃側の攻撃番号を合わせる
                        for (int j = 0; j < enemyManager->GetAttackNumStrongEnemy(i) - collision->GetHitNumPlayerForStrongEnemy(i); j++)
                        {
                            collision->AddHitNumPlayerForStrongEnemy(i);
                        }
                        //HP計算
                        playerManager->CalcHP(enemyManager->GetAtkStrongEnemy(i), enemyManager->GetPosStrongEnemy(i));
                        playerManager->OnKnockBack(enemyManager->GetPosStrongEnemy(i));
                    }
                }
            }
        }
    }
    if (stageChanger->GetIsBoss())
    {
        if (playerManager->GetIsAttack())
        {
            if (playerManager->GetAttackNum() != collision->GetHitNumBossEnemy())
            {

            }
            //当たり判定チェック
            bool isHitEnemy = collision->OnDamage( enemyManager->GetIsDeathBossEnemy(), enemyManager->GetCapsuleInfoBossEnemy(), playerManager->GetSphereInfo());
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
            if (enemyManager->GetIsMeteoAttack())
            {
                /*隕石攻撃だった場合*/
                //カプセルと複数の球との当たり判定を行う
                for (int i = 0; i < meteo->GetMeteoNum(); i++)
                {
                    bool isHitPlayer = collision->OnDamage( playerManager->GetIsDeath(), playerManager->GetCapsuleInfo(), meteo->GetSphereInfo(i));
                    if (isHitPlayer)
                    {
                        if (!enemyManager->GetIsHitBossEnemy())
                        {
                            //HP計算
                            playerManager->CalcHP(enemyManager->GetAtkBossEnemy(), enemyManager->GetPosBossEnemy());
                            enemyManager->SetIsHitBossEnemy(isHitPlayer);
                        }
                    }
                    else
                    {
                        enemyManager->SetIsHitBossEnemy(isHitPlayer);
                    }
                }
            }
            /*爆発攻撃だった場合*/
            //カプセルと球との当たり判定を行う
            if (enemyManager->GetIsExplosionAttack())
            {
                bool isHitPlayer = collision->OnDamage( playerManager->GetIsDeath(), playerManager->GetCapsuleInfo(), explosion->GetSphereInfo());
                if (isHitPlayer)
                {
                    if (!enemyManager->GetIsHitBossEnemy())
                    {
                        //HP計算
                        playerManager->CalcHP(enemyManager->GetAtkBossEnemy(), enemyManager->GetPosBossEnemy());
                        enemyManager->SetIsHitBossEnemy(isHitPlayer);
                    }
                }
                else
                {
                    enemyManager->SetIsHitBossEnemy(isHitPlayer);
                }
            }
            /*通常攻撃またはジャンプ攻撃だった場合*/
            //カプセルと一つの球との当たり判定を行う

            bool isHitPlayer = collision->OnDamage( playerManager->GetIsDeath(), playerManager->GetCapsuleInfo(), enemyManager->GetSphereInfoBossEnemy());
            if (isHitPlayer)
            {
                if (!enemyManager->GetIsHitBossEnemy())
                {
                    //HP計算
                    playerManager->CalcHP(enemyManager->GetAtkBossEnemy(), enemyManager->GetPosBossEnemy());
                    enemyManager->SetIsHitBossEnemy(isHitPlayer);
                }
            }
            else
            {
                enemyManager->SetIsHitBossEnemy(isHitPlayer);
            }
        }
    }
}
/// <summary>
/// ゲーム終了判定
/// </summary>
const void Game::GameEnd(const bool _playerIsDeath, const bool _bossIsDeath)
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
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
        DrawBox(YOU_DIED_BACKGROUND.lx, YOU_DIED_BACKGROUND.ly, YOU_DIED_BACKGROUND.rx, YOU_DIED_BACKGROUND.ry, GetColor(0, 0, 0), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_ALPHA_VALUE);
        DrawExtendFormatStringToHandle(250,400,1.0,1.0,GetColor(150,150,150), youDiedFont, "あなたは死亡しました\n  %d秒後にリスポーン",(MAX_FRAME_COUNT / 60) - (frameCount / 60));
        if (!isFrameCount)
        {
            alpha += ADD_ALPHA_VALUE;
            if (alpha >= MAX_ALPHA_VALUE)
            {
                isFrameCount = true;
                alpha = MAX_ALPHA_VALUE;
            }
        }
        else
        {
            frameCount++;
            if (frameCount >= MAX_FRAME_COUNT)
            {
                enemyManager->PhysicalRecoveryBossEnemy();
                playerManager->ReSpawn();
                stageChanger->ChangeStage();
                isFrameCount = false;
                frameCount = 0;
            }
        }
    }
}