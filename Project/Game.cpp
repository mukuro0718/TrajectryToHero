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
    stageManager->Update();
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
    clsDx();
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
/// <summary>
/// �`��
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
/// �ړ��ʕ␳
/// </summary>
void Game::FixMoveVec()
{
    //�v���C���[�̕␳
    for (int i = 0; i < enemyManager->GetMaxWeakEnemy(); i++)
    {
        VECTOR fixVec = collision->CapsuleToCapsuleCollision(playerManager->GetMoveVec(), playerManager->GetPos(), enemyManager->GetPosWeakEnemy(i),playerManager->GetCapsuleInfo().radius,enemyManager->GetCapsuleInfoWeakEnemy(i).radius);
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
/// <summary>
/// �_���[�W����
/// </summary>
void Game::OnDamage()
{
    //�G�l�~�[�ւ̍U��
    if (playerManager->GetIsAttack())
    {
        for (int i = 0; i < enemyManager->GetMaxWeakEnemy(); i++)
        {
            //�����蔻��`�F�b�N
            bool isHitEnemy = collision->OnDamage(enemyManager->GetIsInvincible(i), enemyManager->GetIsDeathWeakEnemy(i), enemyManager->GetCapsuleInfoWeakEnemy(i), playerManager->GetSphereInfo());
            //�����U�����������Ă�����
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
                playerManager->CalcHP(enemyManager->GetAtkWeakEnemy(i));
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