////===========================================================================
////@brief ゲームシーンクラス
////===========================================================================
//#include"GameScene.h"
//#include"Camera.h"
//#include"StageManager.h"
//#include"StageChanger.h"
//#include"EnemyManager.h"
//#include"PlayerManager.h"
//#include"Common.h"
//#include"SceneChanger.h"
//#include"Timer.h"
//#include"Collision.h"
//#include"Shadow.h"
//#include"Animation.h"
//const int GameScene::FONT_COLOR = GetColor(255, 255, 255);
//const VECTOR GameScene::SHADOW_OFFSET_POS = VGet(0.0f,0.0f,-10.0f);
///// <summary>
///// コンストラクタ
///// </summary>
//GameScene::GameScene()
//{
//    //各クラスの初期化
//    camera        = NULL;
//    stageManager  = NULL;
//    enemyManager  = NULL;
//    playerManager = NULL;
//    collision     = NULL;
//    stageChanger  = NULL;
//    shadow        = NULL;
//    anim = NULL;
//    Create();
//    //入力変数の初期化
//    input = 0;
//    alpha = 300;
//    bossModelHandle = MV1LoadModel("Data/Model/Enemy/Mutant.mv1");
//    MV1SetPosition(bossModelHandle,VGet(0.0f, 0.0f, 750.0f));
//    MV1SetScale(bossModelHandle, VGet(0.4f, 0.4f, 0.4f));
//    fontHandle = CreateFontToHandle("Data/Img/Font/HelpMe.ttf", FONT_SIZE, FONT_THICK, DX_FONTTYPE_NORMAL);
//    skyDomeHandle = MV1LoadModel("Data/Skydome/Dome_Y901.pmx");
//    MV1SetScale(skyDomeHandle, VGet(1.5f, 1.5f, 1.5f));
//    anim->Add(MV1LoadModel("Data/Animation/BossEnemy_IdleAnim.mv1"), 0);			//待機アニメーション
////アタッチするアニメーション
//    anim->SetAnim(0);
//    //アニメーションのアタッチ（最初は明示的に呼び出してアニメーションをアタッチする必要がある）
//    anim->Attach(&bossModelHandle);
//
//}
///// <summary>
///// デストラクタ
///// </summary>
//GameScene::~GameScene()
//{
//    //最終解放
//    Final();
//}
///// <summary>
///// 生成
///// </summary>
//void GameScene::Create()
//{
//    //各クラスの生成
//    camera        = new Camera();
//    stageManager  = new StageManager();
//    enemyManager  = new EnemyManager();
//    playerManager = new PlayerManager();
//    collision     = new Collision();
//    stageChanger  = new StageChanger();
//    shadow        = new Shadow();
//    anim = new Animation();
//    Init();
//}
//void GameScene::Init()
//{
//    //クラスの初期化
//    camera->Init(playerManager->GetPos());
//    playerManager->Init();
//    enemyManager->Init();
//}
//void GameScene::Final()
//{
//    //カメラの開放
//    if (camera)
//    {
//        delete(camera);
//        camera = NULL;
//    }
//    //地面の開放
//    if (stageManager)
//    {
//        delete(stageManager);
//        stageManager = NULL;
//    }
//    //エネミーの開放
//    if (enemyManager)
//    {
//        delete(enemyManager);
//        enemyManager = NULL;
//    }
//    //プレイヤーの開放
//    if (playerManager)
//    {
//        delete(playerManager);
//        playerManager = NULL;
//    }
//    //ステージチェンジャーの開放
//    if (stageChanger)
//    {
//        delete(stageChanger);
//        stageChanger = NULL;
//    }
//    //影の開放
//    if (shadow)
//    {
//        delete(shadow);
//        shadow = NULL;
//    }
//    //当たり判定の開放
//    if (collision)
//    {
//        delete(collision);
//        collision = NULL;
//    }
//}
///// <summary>
///// 更新
///// </summary>
//void GameScene::Update()
//{
//    //ステージ名表示
//    if (stageChanger->GetIsChangeStage())
//    {
//        //もし警告が表示されていなかったら
//        if (!stageChanger->GetIsAlert())
//        {
//            //ステージ切り替えと画像の表示を行う
//            stageChanger->DrawImageWhenSwitchingStage();
//        }
//    }
//    else
//    {
//        //もしレベルアップ画面が表示されていたら処理を止める
//        if (!playerManager->IsStoppingUpdate())
//        {
//            //カメラの更新のみ外で実行
//            camera->Update(playerManager->GetPos());
//            //更新処理
//            stageManager->Update();
//            playerManager->Update(camera->GetCameraToPlayer());
//            enemyManager->Update(playerManager->GetBase(), playerManager->GetStatus(), stageChanger->GetIsFarm(), stageChanger->GetIsBoss());
//            //当たり判定（半径）
//            HitCheckAllEnemy();
//            //プレイヤーへの攻撃
//            AttackToPlayer();
//            //エネミーへの攻撃
//            AttackToEnemy();
//            //シーン切り替え
//            ChangeNextScene();
//        }
//    }
//    VECTOR playerPos = playerManager->GetPos();
//    //もしゲート座標だったら
//    if (playerPos.z >= 500.0f && playerPos.x <= 50.0f && playerPos.x >= -100.0f)
//    {
//        //プレイヤーの座標をセット
//        //帰ってくるVECTORの値は警告表示後、Bを押したら０に、Aを押したらゲートの前に押し戻す
//        playerManager->SetPos(stageChanger->DrawAlert(playerManager->GetPos()));
//    }
//    if (enemyManager->GetBossStatus().HP < 0)
//    {
//        stageChanger->SetIsGameClear(true);
//        stageChanger->SetIsGameEnd(true);
//    }
//    if (playerManager->GetStatus().HP < 0)
//    {
//        stageChanger->SetIsGameOver(true);
//        stageChanger->SetIsGameEnd(true);
//    }
//}
///// <summary>
///// エネミーへの攻撃
///// </summary>
//void GameScene::AttackToEnemy()
//{
//    //プレイヤーが攻撃していた時
//    if (playerManager->GetIsAttack())
//    {
//        //エネミーの最大数だけループ
//        for (int i = 0; i < enemyManager->GetMaxWeakEnemy(); i++)
//        {
//            //エネミーが死亡していなかったら
//            if (enemyManager->GetWeakStatus(i).HP > 0)
//            {
//                //プレイヤーの66フレームと雑魚敵の球との当たり判定
//                collision->OnAttackCollision(66, playerManager->GetBase(), enemyManager->GetWeakBase(i), enemyManager->GetWeakStatus(i), playerManager->GetStatus());
//                //collisionクラスで持つ攻撃を受けた側のステータスを現在の雑魚敵のステータスに入れる
//                enemyManager->SetWeakStatus(i, collision->GetStatusToHit());
//                //collisionクラスで持つ攻撃をした側のステータスをプレイヤーのステータスに入れる
//                playerManager->SetStatus(collision->GetStatusToAttack());
//            }
//        }
//        if(enemyManager->GetIsStrongEnemy())
//        {
//            //プレイヤーの66フレームと雑魚敵の球との当たり判定
//            collision->OnAttackCollision(66, playerManager->GetBase(), enemyManager->GetStrongBase(), enemyManager->GetStrongStatus(), playerManager->GetStatus());
//            //collisionクラスで持つ攻撃を受けた側のステータスを中ボスのステータスに入れる
//            enemyManager->SetStrongStatus(collision->GetStatusToHit());
//            //collisionクラスで持つ攻撃をした側のステータスをプレイヤーのステータスに入れる
//            playerManager->SetStatus(collision->GetStatusToAttack());
//        }
//        if (stageChanger->GetIsBoss())
//        {
//            //プレイヤーの66フレームと雑魚敵の球との当たり判定
//            collision->OnAttackCollision(66, playerManager->GetBase(), enemyManager->GetBossBase(), enemyManager->GetBossStatus(), playerManager->GetStatus());
//            //collisionクラスで持つ攻撃を受けた側のステータスをボスのステータスに入れる
//            enemyManager->SetBossStatus(collision->GetStatusToHit());
//            //collisionクラスで持つ攻撃をした側のステータスをプレイヤーのステータスに入れる
//            playerManager->SetStatus(collision->GetStatusToAttack());
//        }
//    }
//}
///// <summary>
///// プレイヤーへの攻撃
///// </summary>
//void GameScene::AttackToPlayer()
//{
//    //雑魚敵の最大数分ループ
//    for (int i = 0; i < enemyManager->GetMaxWeakEnemy(); i++)
//    {
//        //もし現在の雑魚敵が攻撃していたら処理を行う
//        if (enemyManager->GetWeakBase(i).isAttack)
//        {
//            //雑魚敵の66フレームとプレイヤーの球との当たり判定
//            collision->OnAttackCollision(-1, enemyManager->GetWeakBase(i), playerManager->GetBase(), playerManager->GetStatus(), enemyManager->GetWeakStatus(i));
//            //collisionクラスで持つ攻撃をした側のステータスを現在の雑魚敵のステータスに入れる
//            enemyManager->SetWeakStatus(i, collision->GetStatusToAttack());
//            //collisionクラスで持つ攻撃を受けた側のステータスをプレイヤーのステータスに入れる
//            playerManager->SetStatus(collision->GetStatusToHit());
//
//        }
//    }
//    //もし中ボスが出現していたら
//    if (enemyManager->GetIsStrongEnemy())
//    {
//        //もし中ボスが攻撃していたら
//        if (enemyManager->GetStrongBase().isAttack)
//        {
//            //中ボスの99フレームとプレイヤーの球との当たり判定
//            collision->OnAttackCollision(-1, enemyManager->GetStrongBase(), playerManager->GetBase(), playerManager->GetStatus(), enemyManager->GetStrongStatus());
//            //collisionクラスで持つ攻撃をした側のステータスを中ボスのステータスに入れる
//            enemyManager->SetStrongStatus(collision->GetStatusToAttack());
//            //collisionクラスで持つ攻撃を受けた側のステータスをプレイヤーのステータスに入れる
//            playerManager->SetStatus(collision->GetStatusToHit());
//        }
//    }
//    //ボスが出現していたら
//    if (stageChanger->GetIsBoss())
//    {
//        //ボスが攻撃していたら
//        if (enemyManager->GetBossBase().isAttack)
//        {
//            //プレイヤーの66フレームと雑魚敵の球との当たり判定
//            collision->OnAttackCollision(-1,enemyManager->GetBossBase(), playerManager->GetBase(), playerManager->GetStatus(), enemyManager->GetBossStatus());
//            //collisionクラスで持つ攻撃をした側のステータスを現在のボスのステータスに入れる
//            enemyManager->SetBossStatus(collision->GetStatusToAttack());
//            //collisionクラスで持つ攻撃を受けた側のステータスを現在のプレイヤーのステータスに入れる
//            playerManager->SetStatus(collision->GetStatusToHit());
//        }
//    }
//}
///// <summary>
///// 描画
///// </summary>
//void GameScene::Draw()
//{
//
//    //ステージ名表示
//    if (!stageChanger->GetIsChangeStage())
//    {
//        SetUseLighting(FALSE);
//        SetUseZBuffer3D(TRUE);
//        MV1DrawModel(skyDomeHandle);
//        SetUseLighting(TRUE);
//        SetUseZBuffer3D(FALSE);
//        if (stageChanger->GetIsFarm())
//        {
//            MV1DrawModel(bossModelHandle);
//        }
//        //ステージは常に描画する
//        stageManager->Draw();
//        enemyManager->Draw(playerManager->GetPos(), stageChanger->GetIsFarm(), stageChanger->GetIsBoss());
//        playerManager->Draw();
//        DrawShadow();
//    }
//    
//}
///// <summary>
///// シーン切り替え
///// </summary>
//void GameScene::ChangeNextScene()
//{
//    //インスタンスを取得
//    auto &sceneChange = SceneChanger::GetInstance();
//
//    if (stageChanger->GetIsGameEnd())
//    {
//        if (stageChanger->GetIsGameClear())
//        {
//            //シーンチェンジを稼働させる
//            sceneChange.SetIsSceneChanger(true);
//            sceneChange.ChangeSceneFromNowToNext(GAME, GAMECLEAR);
//        }
//        else if (stageChanger->GetIsGameOver())
//        {
//            //シーンチェンジを稼働させる
//            sceneChange.SetIsSceneChanger(true);
//            sceneChange.ChangeSceneFromNowToNext(GAME, GAMEOVER);
//        }
//    }
//}
///// <summary>
///// すべてのエネミーの半径での当たり判定(重ならないようにする)
///// </summary>
///// <param name="base">チェック対象のベース</param>
//void GameScene::HitCheckAllEnemy()
//{
//    ////weakエネミーの当たり判定
//    //for (int j = 0; j < enemyManager->GetMaxWeakEnemy(); j++)
//    //{
//    //    for (int i = 0; i < enemyManager->GetMaxWeakEnemy(); i++)
//    //    {
//    //        collision->SphereToSphere(enemyManager->GetWeakBase(j), enemyManager->GetWeakBase(i));
//    //        enemyManager->SetWeakBase(j,collision->GetBaseToAttack());
//    //    }
//    //    for (int i = 0; i < enemyManager->GetNowStrongEnemy(); i++)
//    //    {
//    //        collision->SphereToSphere(enemyManager->GetWeakBase(j), enemyManager->GetStrongBase(i));
//    //        enemyManager->SetWeakBase(j, collision->GetBaseToAttack());
//    //    }
//    //    collision->SphereToSphere(enemyManager->GetWeakBase(j),enemyManager->GetBossBase());
//    //    enemyManager->SetWeakBase(j, collision->GetBaseToAttack());
//    //}
//    ////strongエネミーの当たり判定
//    //for (int j = 0; j < enemyManager->GetMaxStrongEnemy(); j++)
//    //{
//    //    for (int i = 0; i < enemyManager->GetMaxWeakEnemy(); i++)
//    //    {
//    //        collision->SphereToSphere(enemyManager->GetStrongBase(j), enemyManager->GetWeakBase(i));
//    //        enemyManager->SetStrongBase(j, collision->GetBaseToAttack());
//    //    }
//    //    for (int i = 0; i < enemyManager->GetNowStrongEnemy(); i++)
//    //    {
//    //        collision->SphereToSphere(enemyManager->GetStrongBase(j), enemyManager->GetStrongBase(i));
//    //        enemyManager->SetStrongBase(j, collision->GetBaseToAttack());
//    //    }
//    //    collision->SphereToSphere(enemyManager->GetStrongBase(j), enemyManager->GetBossBase());
//    //    enemyManager->SetStrongBase(j, collision->GetBaseToAttack());
//    //}
//    ////bossエネミーの当たり判定
//    //for (int i = 0; i < enemyManager->GetMaxWeakEnemy(); i++)
//    //{
//    //    collision->SphereToSphere(enemyManager->GetBossBase(), enemyManager->GetWeakBase(i));
//    //    enemyManager->SetBossBase(collision->GetBaseToAttack());
//    //}
//    //for (int i = 0; i < enemyManager->GetNowStrongEnemy(); i++)
//    //{
//    //    collision->SphereToSphere(enemyManager->GetBossBase(), enemyManager->GetStrongBase(i));
//    //    enemyManager->SetBossBase(collision->GetBaseToAttack());
//    //}
//    //collision->SphereToSphere(enemyManager->GetBossBase(), enemyManager->GetBossBase());
//    //enemyManager->SetBossBase(collision->GetBaseToAttack());
//}
//
///// <summary>
///// 影の描画
///// </summary>
//void GameScene::DrawShadow()
//{
//    //ステージモデルハンドル
//    int stageModelHandle = stageManager->GetModelHandle();
//    //プレイヤーの影座標
//    VECTOR playerShadowPos = playerManager->GetPos();
//    //プレイヤーの影の描画
//    shadow->Draw(stageModelHandle, playerShadowPos, PLAYER_SHADOW_HEIGHT, PLAYER_SHADOW_SIZE);
//
//    for (int i = 0; i < enemyManager->GetMaxWeakEnemy(); i++)
//    {
//        //プレイヤーの影の描画
//        shadow->Draw(stageModelHandle, enemyManager->GetWeakBase(i).pos, NORMAL_ENEMY_SHADOW_HEIGHT, NORMAL_ENEMY_SHADOW_SIZE);
//    }
//    if (enemyManager->GetIsStrongEnemy())
//    {
//        //プレイヤーの影の描画
//        shadow->Draw(stageModelHandle, enemyManager->GetStrongBase().pos, NORMAL_ENEMY_SHADOW_HEIGHT, NORMAL_ENEMY_SHADOW_SIZE);
//    }
//    if (stageChanger->GetIsBoss())
//    {
//        //プレイヤーの影の描画
//        shadow->Draw(stageModelHandle, enemyManager->GetStrongBase().pos, BOSS_ENEMY_SHADOW_HEIGHT, BOSS_ENEMY_SHADOW_SIZE);
//    }
//}