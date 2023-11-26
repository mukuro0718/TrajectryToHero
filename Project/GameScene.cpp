////===========================================================================
////@brief �Q�[���V�[���N���X
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
///// �R���X�g���N�^
///// </summary>
//GameScene::GameScene()
//{
//    //�e�N���X�̏�����
//    camera        = NULL;
//    stageManager  = NULL;
//    enemyManager  = NULL;
//    playerManager = NULL;
//    collision     = NULL;
//    stageChanger  = NULL;
//    shadow        = NULL;
//    anim = NULL;
//    Create();
//    //���͕ϐ��̏�����
//    input = 0;
//    alpha = 300;
//    bossModelHandle = MV1LoadModel("Data/Model/Enemy/Mutant.mv1");
//    MV1SetPosition(bossModelHandle,VGet(0.0f, 0.0f, 750.0f));
//    MV1SetScale(bossModelHandle, VGet(0.4f, 0.4f, 0.4f));
//    fontHandle = CreateFontToHandle("Data/Img/Font/HelpMe.ttf", FONT_SIZE, FONT_THICK, DX_FONTTYPE_NORMAL);
//    skyDomeHandle = MV1LoadModel("Data/Skydome/Dome_Y901.pmx");
//    MV1SetScale(skyDomeHandle, VGet(1.5f, 1.5f, 1.5f));
//    anim->Add(MV1LoadModel("Data/Animation/BossEnemy_IdleAnim.mv1"), 0);			//�ҋ@�A�j���[�V����
////�A�^�b�`����A�j���[�V����
//    anim->SetAnim(0);
//    //�A�j���[�V�����̃A�^�b�`�i�ŏ��͖����I�ɌĂяo���ăA�j���[�V�������A�^�b�`����K�v������j
//    anim->Attach(&bossModelHandle);
//
//}
///// <summary>
///// �f�X�g���N�^
///// </summary>
//GameScene::~GameScene()
//{
//    //�ŏI���
//    Final();
//}
///// <summary>
///// ����
///// </summary>
//void GameScene::Create()
//{
//    //�e�N���X�̐���
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
//    //�N���X�̏�����
//    camera->Init(playerManager->GetPos());
//    playerManager->Init();
//    enemyManager->Init();
//}
//void GameScene::Final()
//{
//    //�J�����̊J��
//    if (camera)
//    {
//        delete(camera);
//        camera = NULL;
//    }
//    //�n�ʂ̊J��
//    if (stageManager)
//    {
//        delete(stageManager);
//        stageManager = NULL;
//    }
//    //�G�l�~�[�̊J��
//    if (enemyManager)
//    {
//        delete(enemyManager);
//        enemyManager = NULL;
//    }
//    //�v���C���[�̊J��
//    if (playerManager)
//    {
//        delete(playerManager);
//        playerManager = NULL;
//    }
//    //�X�e�[�W�`�F���W���[�̊J��
//    if (stageChanger)
//    {
//        delete(stageChanger);
//        stageChanger = NULL;
//    }
//    //�e�̊J��
//    if (shadow)
//    {
//        delete(shadow);
//        shadow = NULL;
//    }
//    //�����蔻��̊J��
//    if (collision)
//    {
//        delete(collision);
//        collision = NULL;
//    }
//}
///// <summary>
///// �X�V
///// </summary>
//void GameScene::Update()
//{
//    //�X�e�[�W���\��
//    if (stageChanger->GetIsChangeStage())
//    {
//        //�����x�����\������Ă��Ȃ�������
//        if (!stageChanger->GetIsAlert())
//        {
//            //�X�e�[�W�؂�ւ��Ɖ摜�̕\�����s��
//            stageChanger->DrawImageWhenSwitchingStage();
//        }
//    }
//    else
//    {
//        //�������x���A�b�v��ʂ��\������Ă����珈�����~�߂�
//        if (!playerManager->IsStoppingUpdate())
//        {
//            //�J�����̍X�V�̂݊O�Ŏ��s
//            camera->Update(playerManager->GetPos());
//            //�X�V����
//            stageManager->Update();
//            playerManager->Update(camera->GetCameraToPlayer());
//            enemyManager->Update(playerManager->GetBase(), playerManager->GetStatus(), stageChanger->GetIsFarm(), stageChanger->GetIsBoss());
//            //�����蔻��i���a�j
//            HitCheckAllEnemy();
//            //�v���C���[�ւ̍U��
//            AttackToPlayer();
//            //�G�l�~�[�ւ̍U��
//            AttackToEnemy();
//            //�V�[���؂�ւ�
//            ChangeNextScene();
//        }
//    }
//    VECTOR playerPos = playerManager->GetPos();
//    //�����Q�[�g���W��������
//    if (playerPos.z >= 500.0f && playerPos.x <= 50.0f && playerPos.x >= -100.0f)
//    {
//        //�v���C���[�̍��W���Z�b�g
//        //�A���Ă���VECTOR�̒l�͌x���\����AB����������O�ɁAA����������Q�[�g�̑O�ɉ����߂�
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
///// �G�l�~�[�ւ̍U��
///// </summary>
//void GameScene::AttackToEnemy()
//{
//    //�v���C���[���U�����Ă�����
//    if (playerManager->GetIsAttack())
//    {
//        //�G�l�~�[�̍ő吔�������[�v
//        for (int i = 0; i < enemyManager->GetMaxWeakEnemy(); i++)
//        {
//            //�G�l�~�[�����S���Ă��Ȃ�������
//            if (enemyManager->GetWeakStatus(i).HP > 0)
//            {
//                //�v���C���[��66�t���[���ƎG���G�̋��Ƃ̓����蔻��
//                collision->OnAttackCollision(66, playerManager->GetBase(), enemyManager->GetWeakBase(i), enemyManager->GetWeakStatus(i), playerManager->GetStatus());
//                //collision�N���X�Ŏ��U�����󂯂����̃X�e�[�^�X�����݂̎G���G�̃X�e�[�^�X�ɓ����
//                enemyManager->SetWeakStatus(i, collision->GetStatusToHit());
//                //collision�N���X�Ŏ��U�����������̃X�e�[�^�X���v���C���[�̃X�e�[�^�X�ɓ����
//                playerManager->SetStatus(collision->GetStatusToAttack());
//            }
//        }
//        if(enemyManager->GetIsStrongEnemy())
//        {
//            //�v���C���[��66�t���[���ƎG���G�̋��Ƃ̓����蔻��
//            collision->OnAttackCollision(66, playerManager->GetBase(), enemyManager->GetStrongBase(), enemyManager->GetStrongStatus(), playerManager->GetStatus());
//            //collision�N���X�Ŏ��U�����󂯂����̃X�e�[�^�X�𒆃{�X�̃X�e�[�^�X�ɓ����
//            enemyManager->SetStrongStatus(collision->GetStatusToHit());
//            //collision�N���X�Ŏ��U�����������̃X�e�[�^�X���v���C���[�̃X�e�[�^�X�ɓ����
//            playerManager->SetStatus(collision->GetStatusToAttack());
//        }
//        if (stageChanger->GetIsBoss())
//        {
//            //�v���C���[��66�t���[���ƎG���G�̋��Ƃ̓����蔻��
//            collision->OnAttackCollision(66, playerManager->GetBase(), enemyManager->GetBossBase(), enemyManager->GetBossStatus(), playerManager->GetStatus());
//            //collision�N���X�Ŏ��U�����󂯂����̃X�e�[�^�X���{�X�̃X�e�[�^�X�ɓ����
//            enemyManager->SetBossStatus(collision->GetStatusToHit());
//            //collision�N���X�Ŏ��U�����������̃X�e�[�^�X���v���C���[�̃X�e�[�^�X�ɓ����
//            playerManager->SetStatus(collision->GetStatusToAttack());
//        }
//    }
//}
///// <summary>
///// �v���C���[�ւ̍U��
///// </summary>
//void GameScene::AttackToPlayer()
//{
//    //�G���G�̍ő吔�����[�v
//    for (int i = 0; i < enemyManager->GetMaxWeakEnemy(); i++)
//    {
//        //�������݂̎G���G���U�����Ă����珈�����s��
//        if (enemyManager->GetWeakBase(i).isAttack)
//        {
//            //�G���G��66�t���[���ƃv���C���[�̋��Ƃ̓����蔻��
//            collision->OnAttackCollision(-1, enemyManager->GetWeakBase(i), playerManager->GetBase(), playerManager->GetStatus(), enemyManager->GetWeakStatus(i));
//            //collision�N���X�Ŏ��U�����������̃X�e�[�^�X�����݂̎G���G�̃X�e�[�^�X�ɓ����
//            enemyManager->SetWeakStatus(i, collision->GetStatusToAttack());
//            //collision�N���X�Ŏ��U�����󂯂����̃X�e�[�^�X���v���C���[�̃X�e�[�^�X�ɓ����
//            playerManager->SetStatus(collision->GetStatusToHit());
//
//        }
//    }
//    //�������{�X���o�����Ă�����
//    if (enemyManager->GetIsStrongEnemy())
//    {
//        //�������{�X���U�����Ă�����
//        if (enemyManager->GetStrongBase().isAttack)
//        {
//            //���{�X��99�t���[���ƃv���C���[�̋��Ƃ̓����蔻��
//            collision->OnAttackCollision(-1, enemyManager->GetStrongBase(), playerManager->GetBase(), playerManager->GetStatus(), enemyManager->GetStrongStatus());
//            //collision�N���X�Ŏ��U�����������̃X�e�[�^�X�𒆃{�X�̃X�e�[�^�X�ɓ����
//            enemyManager->SetStrongStatus(collision->GetStatusToAttack());
//            //collision�N���X�Ŏ��U�����󂯂����̃X�e�[�^�X���v���C���[�̃X�e�[�^�X�ɓ����
//            playerManager->SetStatus(collision->GetStatusToHit());
//        }
//    }
//    //�{�X���o�����Ă�����
//    if (stageChanger->GetIsBoss())
//    {
//        //�{�X���U�����Ă�����
//        if (enemyManager->GetBossBase().isAttack)
//        {
//            //�v���C���[��66�t���[���ƎG���G�̋��Ƃ̓����蔻��
//            collision->OnAttackCollision(-1,enemyManager->GetBossBase(), playerManager->GetBase(), playerManager->GetStatus(), enemyManager->GetBossStatus());
//            //collision�N���X�Ŏ��U�����������̃X�e�[�^�X�����݂̃{�X�̃X�e�[�^�X�ɓ����
//            enemyManager->SetBossStatus(collision->GetStatusToAttack());
//            //collision�N���X�Ŏ��U�����󂯂����̃X�e�[�^�X�����݂̃v���C���[�̃X�e�[�^�X�ɓ����
//            playerManager->SetStatus(collision->GetStatusToHit());
//        }
//    }
//}
///// <summary>
///// �`��
///// </summary>
//void GameScene::Draw()
//{
//
//    //�X�e�[�W���\��
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
//        //�X�e�[�W�͏�ɕ`�悷��
//        stageManager->Draw();
//        enemyManager->Draw(playerManager->GetPos(), stageChanger->GetIsFarm(), stageChanger->GetIsBoss());
//        playerManager->Draw();
//        DrawShadow();
//    }
//    
//}
///// <summary>
///// �V�[���؂�ւ�
///// </summary>
//void GameScene::ChangeNextScene()
//{
//    //�C���X�^���X���擾
//    auto &sceneChange = SceneChanger::GetInstance();
//
//    if (stageChanger->GetIsGameEnd())
//    {
//        if (stageChanger->GetIsGameClear())
//        {
//            //�V�[���`�F���W���ғ�������
//            sceneChange.SetIsSceneChanger(true);
//            sceneChange.ChangeSceneFromNowToNext(GAME, GAMECLEAR);
//        }
//        else if (stageChanger->GetIsGameOver())
//        {
//            //�V�[���`�F���W���ғ�������
//            sceneChange.SetIsSceneChanger(true);
//            sceneChange.ChangeSceneFromNowToNext(GAME, GAMEOVER);
//        }
//    }
//}
///// <summary>
///// ���ׂẴG�l�~�[�̔��a�ł̓����蔻��(�d�Ȃ�Ȃ��悤�ɂ���)
///// </summary>
///// <param name="base">�`�F�b�N�Ώۂ̃x�[�X</param>
//void GameScene::HitCheckAllEnemy()
//{
//    ////weak�G�l�~�[�̓����蔻��
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
//    ////strong�G�l�~�[�̓����蔻��
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
//    ////boss�G�l�~�[�̓����蔻��
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
///// �e�̕`��
///// </summary>
//void GameScene::DrawShadow()
//{
//    //�X�e�[�W���f���n���h��
//    int stageModelHandle = stageManager->GetModelHandle();
//    //�v���C���[�̉e���W
//    VECTOR playerShadowPos = playerManager->GetPos();
//    //�v���C���[�̉e�̕`��
//    shadow->Draw(stageModelHandle, playerShadowPos, PLAYER_SHADOW_HEIGHT, PLAYER_SHADOW_SIZE);
//
//    for (int i = 0; i < enemyManager->GetMaxWeakEnemy(); i++)
//    {
//        //�v���C���[�̉e�̕`��
//        shadow->Draw(stageModelHandle, enemyManager->GetWeakBase(i).pos, NORMAL_ENEMY_SHADOW_HEIGHT, NORMAL_ENEMY_SHADOW_SIZE);
//    }
//    if (enemyManager->GetIsStrongEnemy())
//    {
//        //�v���C���[�̉e�̕`��
//        shadow->Draw(stageModelHandle, enemyManager->GetStrongBase().pos, NORMAL_ENEMY_SHADOW_HEIGHT, NORMAL_ENEMY_SHADOW_SIZE);
//    }
//    if (stageChanger->GetIsBoss())
//    {
//        //�v���C���[�̉e�̕`��
//        shadow->Draw(stageModelHandle, enemyManager->GetStrongBase().pos, BOSS_ENEMY_SHADOW_HEIGHT, BOSS_ENEMY_SHADOW_SIZE);
//    }
//}