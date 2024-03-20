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
/// �R���X�g���N�^
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
    //�v���C���[�̊J��
    if (playerManager)
    {
        delete(playerManager);
        playerManager = nullptr;
    }
    //�X�e�[�^�X�㏸�p�[�e�B�N���̊J��
    if (statusUpParticle)
    {
        delete(statusUpParticle);
        statusUpParticle = nullptr;
    }
    //�X�e�[�W�̊J��
    if (stageManager)
    {
        delete(stageManager);
        stageManager = nullptr;
    }
    //�X�e�[�W�ύX�̊J��
    if (stageChanger)
    {
        delete(stageChanger);
        stageChanger = nullptr;
    }
    //�G�l�~�[�̊J��
    if (enemyManager)
    {
        delete(enemyManager);
        enemyManager = nullptr;
    }
    //���̌��̊J��
    if (lightSword)
    {
        delete(lightSword);
        lightSword = nullptr;
    }
    //�R���W�����̊J��
    if (collision)
    {
        delete(collision);
        collision = nullptr;
    }
    //�����̊J��
    if (explosion)
    {
        delete(explosion);
        explosion = nullptr;
    }
    //�X�J�C�h�[���̊J��
    if (skydome)
    {
        delete(skydome);
        skydome = nullptr;
    }
    //�J�����̊J��
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
/// �X�V
/// </summary>
const void Game::Update()
{
    stageManager->Update(static_cast<int>(playerManager->GetLv()));

    if (!playerManager->GetIsShowStatusMenu())
    {
        enemyManager->AdjustTheNumberOfEnemy(static_cast<int>(playerManager->GetLv()));
        ///*�J�����̂ݍX�V*/
        //camera->Update(playerManager->GetPos());
        /*�ړ�����*/
        playerManager->Move(camera->GetCameraToPlayer());
        enemyManager->Move(playerManager->GetPos(), stageChanger->GetIsFarm(), stageChanger->GetIsBoss());
        /*�U������*/
        playerManager->Attack();
        meteo->Update(enemyManager->GetIsMeteoAttack());
        explosion->Update(enemyManager->GetIsExplosionAttack(), enemyManager->GetPosBossEnemy());
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
    statusUpParticle->Update(playerManager->GetPos(), playerManager->GetIsBonfireMenu(),playerManager->GetLv());
    lightSword->Update(MV1GetFramePosition(playerManager->GetModelHandle(),67), MV1GetFramePosition(playerManager->GetModelHandle(), 68), MV1GetFramePosition(playerManager->GetModelHandle(), 69));

}
/// <summary>
/// �`��
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
/// �ړ��ʕ␳
/// </summary>
const void Game::FixMoveVec()
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
const void Game::OnDamage()
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
                //�����v���C���[�̍U���ԍ��ƑΉ�����G�l�~�[�̃q�b�g�ԍ����قȂ��Ă����瓖���蔻����s��
                if (playerManager->GetAttackNum() != collision->GetHitNumWeakEnemy(i))
                {
                    //�����蔻��`�F�b�N
                    bool isHitEnemy = collision->OnDamage(enemyManager->GetIsDeathWeakEnemy(i), enemyManager->GetCapsuleInfoWeakEnemy(i), playerManager->GetSphereInfo());
                    //�����U�����������Ă�����
                    if (isHitEnemy)
                    {
                        //�R���W�������̃q�b�g�ԍ��ƍU�����̍U���ԍ������킹��
                        for (int j = 0; j < playerManager->GetAttackNum() - collision->GetHitNumWeakEnemy(i); j++)
                        {
                            collision->AddHitNumWeakEnemy(i);
                        }
                        //�o���l�̌v�Z
                        float exp = enemyManager->CalcHPWeakEnemy(i, playerManager->GetAtk(), playerManager->GetPos());
                        //�Ώۂ̃G�l�~�[�����S���āA�o���l�������Ă����珈�����s��
                        if (exp > 0)
                        {
                            playerManager->CalcExp(exp);
                            enemyManager->InitExpToGive(i);
                        }
                    }
                }
            }
            /*���{�X*/
            for (int i = 0; i < enemyManager->GetNowStrongEnemyNum(); i++)
            {
                if (playerManager->GetAttackNum() != collision->GetHitNumStrongEnemy(i))
                {
                    //�����蔻��`�F�b�N
                    bool isHitEnemy = collision->OnDamage(enemyManager->GetIsDeathStrongEnemy(i), enemyManager->GetCapsuleInfoStrongEnemy(i), playerManager->GetSphereInfo());
                    //�����U�����������Ă�����
                    if (isHitEnemy)
                    {
                        //�R���W�������̃q�b�g�ԍ��ƍU�����̍U���ԍ������킹��
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

        //�v���C���[�ւ̍U��
        bool isHitPlayer = false;
        for (int i = 0; i < enemyManager->GetNowWeakEnemyNum(); i++)
        {
            if (enemyManager->GetAttackNumWeakEnemy(i) != collision->GetHitNumPlayerForWeakEnemy(i))
            {
                //�����G�l�~�[���U�����Ă�����
                if (enemyManager->GetIsAttackWeakEnemy(i))
                {
                    //�U�����������Ă��邩�̃`�F�b�N
                    isHitPlayer = collision->OnDamage(playerManager->GetIsDeath(), playerManager->GetCapsuleInfo(), enemyManager->GetSphereInfoWeakEnemy(i));
                    //�����v���C���[�ɓ������Ă�����
                    if (isHitPlayer)
                    {
                        //�R���W�������̃q�b�g�ԍ��ƍU�����̍U���ԍ������킹��
                        for (int j = 0; j < enemyManager->GetAttackNumWeakEnemy(i) - collision->GetHitNumPlayerForWeakEnemy(i); j++)
                        {
                            collision->AddHitNumPlayerForWeakEnemy(i);
                        }
                        //HP�v�Z
                        playerManager->CalcHP(enemyManager->GetAtkWeakEnemy(i), enemyManager->GetPosWeakEnemy(i));
                    }
                }
            }
        }
        for (int i = 0; i < enemyManager->GetNowStrongEnemyNum(); i++)
        {
            if (enemyManager->GetAttackNumStrongEnemy(i) != collision->GetHitNumPlayerForStrongEnemy(i))
            {
                //�����G�l�~�[���U�����Ă�����
                if (enemyManager->GetIsAttackStrongEnemy(i))
                {
                    //�U�����������Ă��邩�̃`�F�b�N
                    isHitPlayer = collision->OnDamage(playerManager->GetIsDeath(), playerManager->GetCapsuleInfo(), enemyManager->GetSphereInfoStrongEnemy(i));
                    if (isHitPlayer)
                    {
                        //�R���W�������̃q�b�g�ԍ��ƍU�����̍U���ԍ������킹��
                        for (int j = 0; j < enemyManager->GetAttackNumStrongEnemy(i) - collision->GetHitNumPlayerForStrongEnemy(i); j++)
                        {
                            collision->AddHitNumPlayerForStrongEnemy(i);
                        }
                        //HP�v�Z
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
            //�����蔻��`�F�b�N
            bool isHitEnemy = collision->OnDamage( enemyManager->GetIsDeathBossEnemy(), enemyManager->GetCapsuleInfoBossEnemy(), playerManager->GetSphereInfo());
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
            if (enemyManager->GetIsMeteoAttack())
            {
                /*覐΍U���������ꍇ*/
                //�J�v�Z���ƕ����̋��Ƃ̓����蔻����s��
                for (int i = 0; i < meteo->GetMeteoNum(); i++)
                {
                    bool isHitPlayer = collision->OnDamage( playerManager->GetIsDeath(), playerManager->GetCapsuleInfo(), meteo->GetSphereInfo(i));
                    if (isHitPlayer)
                    {
                        if (!enemyManager->GetIsHitBossEnemy())
                        {
                            //HP�v�Z
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
            /*�����U���������ꍇ*/
            //�J�v�Z���Ƌ��Ƃ̓����蔻����s��
            if (enemyManager->GetIsExplosionAttack())
            {
                bool isHitPlayer = collision->OnDamage( playerManager->GetIsDeath(), playerManager->GetCapsuleInfo(), explosion->GetSphereInfo());
                if (isHitPlayer)
                {
                    if (!enemyManager->GetIsHitBossEnemy())
                    {
                        //HP�v�Z
                        playerManager->CalcHP(enemyManager->GetAtkBossEnemy(), enemyManager->GetPosBossEnemy());
                        enemyManager->SetIsHitBossEnemy(isHitPlayer);
                    }
                }
                else
                {
                    enemyManager->SetIsHitBossEnemy(isHitPlayer);
                }
            }
            /*�ʏ�U���܂��̓W�����v�U���������ꍇ*/
            //�J�v�Z���ƈ�̋��Ƃ̓����蔻����s��

            bool isHitPlayer = collision->OnDamage( playerManager->GetIsDeath(), playerManager->GetCapsuleInfo(), enemyManager->GetSphereInfoBossEnemy());
            if (isHitPlayer)
            {
                if (!enemyManager->GetIsHitBossEnemy())
                {
                    //HP�v�Z
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
/// �Q�[���I������
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
        DrawExtendFormatStringToHandle(250,400,1.0,1.0,GetColor(150,150,150), youDiedFont, "���Ȃ��͎��S���܂���\n  %d�b��Ƀ��X�|�[��",(MAX_FRAME_COUNT / 60) - (frameCount / 60));
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