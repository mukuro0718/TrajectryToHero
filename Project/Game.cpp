#include"Game.h"
#include"Camera.h"
#include"PlayerManager.h"
#include"Skydome.h"
#include"StageManager.h"
#include"StageChanger.h"
#include"EnemyManager.h"
#include"Collision.h"
/// <summary>
/// �R���X�g���N�^
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
    stageManager->Update();

    if (!stageChanger->GetIsChangeStage())
    {
        if (!playerManager->GetIsShowStatusMenu())
        {
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
            enemyManager->Update(playerManager->GetPos(), stageChanger->GetIsFarm(), stageChanger->GetIsBoss());
            stageChanger->DrawImageWhenSwitchingStage();
        }
        playerManager->StatusUpdate();
        GameEnd(playerManager->GetIsDeath());
    }
    if (!stageChanger->GetIsBoss())
    {
        stageChanger->DrawAlert(playerManager->GetPos());
    }
}
/// <summary>
/// �`��
/// </summary>
void Game::Draw()
{
    if (!stageChanger->GetIsChangeStage())
    {
        skydome->Draw();
        stageChanger->Draw();
        stageManager->Draw();
        playerManager->DrawShadow(stageManager->GetModelHandle());
        enemyManager->DrawShadow(stageManager->GetModelHandle(), stageChanger->GetIsFarm(), stageChanger->GetIsBoss());
        playerManager->Draw();
        enemyManager->Draw(playerManager->GetPos(), stageChanger->GetIsFarm(), stageChanger->GetIsBoss());
    }
    else
    {
        if (!stageChanger->GetIsAlert())
        {
            stageChanger->DrawImageWhenSwitchingStage();
        }
    }
}
/// <summary>
/// �ړ��ʕ␳
/// </summary>
void Game::FixMoveVec()
{
    if (stageChanger->GetIsFarm())
    {
        //�v���C���[�̕␳
        for (int i = 0; i < enemyManager->GetMaxWeakEnemy(); i++)
        {
            VECTOR fixVec = collision->CapsuleToCapsuleCollision(playerManager->GetMoveVec(), playerManager->GetPos(), enemyManager->GetPosWeakEnemy(i), playerManager->GetCapsuleInfo().radius, enemyManager->GetCapsuleInfoWeakEnemy(i).radius);
            playerManager->FixMoveVec(fixVec);
        }

        //�G�l�~�[�̕␳
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
            for (int i = 0; i < enemyManager->GetMaxWeakEnemy(); i++)
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

        }
        //�v���C���[�ւ̍U��
        bool isHitPlayer = false;
        for (int i = 0; i < enemyManager->GetMaxWeakEnemy(); i++)
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
void Game::GameEnd(const bool _playerIsDeath)
{
    if (_playerIsDeath)
    {
        isGameOver = true;
    }
}