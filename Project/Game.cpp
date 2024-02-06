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
/// �R���X�g���N�^
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
    //�J�����̊J��
    if (camera)
    {
        delete(camera);
        camera = nullptr;
    }
    //�v���C���[�̊J��
    if (playerManager)
    {
        delete(playerManager);
        playerManager = nullptr;
    }
    //�X�J�C�h�[���̊J��
    if (skydome)
    {
        delete(skydome);
        skydome = nullptr;
    }
    //�G�l�~�[�̊J��
    if (enemyManager)
    {
        delete(enemyManager);
        enemyManager = nullptr;
    }
    //�R���W�����̊J��
    if (collision)
    {
        delete(collision);
        collision = nullptr;
    }
}
/// <summary>
/// �X�V
/// </summary>
void Game::Update()
{
    stageManager->Update(static_cast<int>(playerManager->GetLv()));

    if (!playerManager->GetIsShowStatusMenu())
    {
        enemyManager->AdjustTheNumberOfEnemy(static_cast<int>(playerManager->GetLv()));
        /*�J�����̂ݍX�V*/
        camera->Update(playerManager->GetPos());
        /*�ړ�����*/
        playerManager->Move(camera->GetCameraToPlayer());
        enemyManager->Move(playerManager->GetPos(), stageChanger->GetIsFarm(), stageChanger->GetIsBoss());
        /*�U������*/
        playerManager->Attack();
        /*�R���W��������*/
        OnDamage();
        FixMoveVec();
        /*�X�V����*/
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
/// �`��
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
/// �ړ��ʕ␳
/// </summary>
void Game::FixMoveVec()
{
    if (stageChanger->GetIsFarm())
    {
        /*�v���C���[�̕␳*/
        //�G���G�Ƃ̐ڐG����
        for (int i = 0; i < enemyManager->GetNowWeakEnemyNum(); i++)
        {
            VECTOR fixVec = collision->CapsuleToCapsuleCollision(playerManager->GetMoveVec(), playerManager->GetPos(), enemyManager->GetPosWeakEnemy(i), playerManager->GetCapsuleInfo().radius, enemyManager->GetCapsuleInfoWeakEnemy(i).radius);
            playerManager->FixMoveVec(fixVec);
        }
        //�`���[�{�X�Ƃ̐ڐG����
        for (int i = 0; i < enemyManager->GetNowStrongEnemyNum(); i++)
        {
            VECTOR fixVec = collision->CapsuleToCapsuleCollision(playerManager->GetMoveVec(), playerManager->GetPos(), enemyManager->GetPosStrongEnemy(i), playerManager->GetCapsuleInfo().radius, enemyManager->GetCapsuleInfoWeakEnemy(i).radius);
            playerManager->FixMoveVec(fixVec);
        }
        /*�G�l�~�[�̕␳*/
        //�G���G�̐ڐG���蔻��
        for (int i = 0; i < enemyManager->GetNowWeakEnemyNum(); i++)
        {
            //�v���C���[�Ƃ̐ڐG����
            VECTOR fixVec = collision->CapsuleToCapsuleCollision(enemyManager->GetMoveVecWeakEnemy(i), enemyManager->GetPosWeakEnemy(i), playerManager->GetPos(), enemyManager->GetCapsuleInfoWeakEnemy(i).radius, playerManager->GetCapsuleInfo().radius);
            enemyManager->FixMoveVecWeakEnemy(i, fixVec);
            //�G���G�Ƃ̐ڐG����
            for (int j = 0; j < enemyManager->GetNowWeakEnemyNum(); j++)
            {
                if (i != j)
                {
                    fixVec = collision->CapsuleToCapsuleCollision(enemyManager->GetMoveVecWeakEnemy(i), enemyManager->GetPosWeakEnemy(i), enemyManager->GetPosWeakEnemy(j), enemyManager->GetCapsuleInfoWeakEnemy(i).radius, enemyManager->GetCapsuleInfoWeakEnemy(j).radius);
                    enemyManager->FixMoveVecWeakEnemy(i, fixVec);
                }
            }
            //���{�X�Ƃ̐ڐG����
            for (int j = 0; j < enemyManager->GetNowStrongEnemyNum(); j++)
            {
                fixVec = collision->CapsuleToCapsuleCollision(enemyManager->GetMoveVecWeakEnemy(i), enemyManager->GetPosWeakEnemy(i), enemyManager->GetPosStrongEnemy(j), enemyManager->GetCapsuleInfoWeakEnemy(i).radius, enemyManager->GetCapsuleInfoStrongEnemy(j).radius);
                enemyManager->FixMoveVecWeakEnemy(i, fixVec);
            }
        }

        //�G���G�̐ڐG���蔻��
        for (int i = 0; i < enemyManager->GetNowStrongEnemyNum(); i++)
        {
            //�v���C���[�Ƃ̐ڐG����
            VECTOR fixVec = collision->CapsuleToCapsuleCollision(enemyManager->GetMoveVecStrongEnemy(i), enemyManager->GetPosStrongEnemy(i), playerManager->GetPos(), enemyManager->GetCapsuleInfoStrongEnemy(i).radius, playerManager->GetCapsuleInfo().radius);
            enemyManager->FixMoveVecStrongEnemy(i, fixVec);
            //�G���G�Ƃ̐ڐG����
            for (int j = 0; j < enemyManager->GetNowWeakEnemyNum(); j++)
            {
                fixVec = collision->CapsuleToCapsuleCollision(enemyManager->GetMoveVecStrongEnemy(i), enemyManager->GetPosStrongEnemy(i), enemyManager->GetPosWeakEnemy(j), enemyManager->GetCapsuleInfoStrongEnemy(i).radius, enemyManager->GetCapsuleInfoWeakEnemy(j).radius);
                enemyManager->FixMoveVecStrongEnemy(i, fixVec);
            }
            //���{�X�Ƃ̐ڐG����
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
/// �_���[�W����
/// </summary>
void Game::OnDamage()
{
    /*
    �U��������������󂯂����֌������x�N�g������o��
    �����̃x�N�g�������ƂɁA�L�����N�^�[���ƂɌ��̔�ԕ��������߂�΂悢�H
    */
    if (stageChanger->GetIsFarm())
    {
        //�G�l�~�[�ւ̍U��
        if (playerManager->GetIsAttack())
        {
            /*�G���G*/
            for (int i = 0; i < enemyManager->GetNowWeakEnemyNum(); i++)
            {
                //�����蔻��`�F�b�N
                bool isHitEnemy = collision->OnDamage(enemyManager->GetIsInvincibleWeakEnemy(i), enemyManager->GetIsDeathWeakEnemy(i), enemyManager->GetCapsuleInfoWeakEnemy(i), playerManager->GetSphereInfo());
                //�����U�����������Ă�����
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
            /*���{�X*/
            for (int i = 0; i < enemyManager->GetNowStrongEnemyNum(); i++)
            {
                //�����蔻��`�F�b�N
                bool isHitEnemy = collision->OnDamage(enemyManager->GetIsInvincibleStrongEnemy(i), enemyManager->GetIsDeathStrongEnemy(i), enemyManager->GetCapsuleInfoStrongEnemy(i), playerManager->GetSphereInfo());
                //�����U�����������Ă�����
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
        //�v���C���[�ւ̍U��
        bool isHitPlayer = false;
        for (int i = 0; i < enemyManager->GetNowWeakEnemyNum(); i++)
        {
            //�����G�l�~�[���U�����Ă�����
            if (enemyManager->GetIsAttackWeakEnemy(i))
            {
                //�U�����������Ă��邩�̃`�F�b�N
                isHitPlayer = collision->OnDamage(playerManager->GetIsInvincible(), playerManager->GetIsDeath(), playerManager->GetCapsuleInfo(), enemyManager->GetSphereInfoWeakEnemy(i));
                //�����U�����������Ă�����
                if (isHitPlayer)
                {
                    //HP�v�Z
                    playerManager->CalcHP(enemyManager->GetAtkWeakEnemy(i),enemyManager->GetPosWeakEnemy(i));
                }
            }
        }
        for (int i = 0; i < enemyManager->GetNowStrongEnemyNum(); i++)
        {
            //�����G�l�~�[���U�����Ă�����
            if (enemyManager->GetIsAttackStrongEnemy(i))
            {
                //�U�����������Ă��邩�̃`�F�b�N
                isHitPlayer = collision->OnDamage(playerManager->GetIsInvincible(), playerManager->GetIsDeath(), playerManager->GetCapsuleInfo(), enemyManager->GetSphereInfoStrongEnemy(i));
                //�����U�����������Ă�����
                if (isHitPlayer)
                {
                    //HP�v�Z
                    playerManager->CalcHP(enemyManager->GetAtkStrongEnemy(i), enemyManager->GetPosStrongEnemy(i));
                }
            }
        }
    }
    if (stageChanger->GetIsBoss())
    {
        if (playerManager->GetIsAttack())
        {
            //�����蔻��`�F�b�N
            bool isHitEnemy = collision->OnDamage(enemyManager->GetIsInvincibleBossEnemy(), enemyManager->GetIsDeathBossEnemy(), enemyManager->GetCapsuleInfoBossEnemy(), playerManager->GetSphereInfo());
            //�����U�����������Ă�����
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
            //�����U�����������Ă�����
            if (isHitPlayer)
            {
                //HP�v�Z
                playerManager->CalcHP(enemyManager->GetAtkBossEnemy(),enemyManager->GetPosBossEnemy());
            }
        }
        
    }
}
/// <summary>
/// �Q�[���I������
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