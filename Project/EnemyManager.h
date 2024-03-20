/*�C���X�^���X�͂��ׂčŏ��ɐ�������
�ϐ��ŏ���������G�̐���ω�������*/
#pragma once

#include"DxLib.h"
#include<vector>
#include"BossEnemy.h"
#include"StrongEnemy.h"
#include"WeakEnemy.h"

class EnemyManager
{
public:
    EnemyManager(); //�R���X�g���N�^
    ~EnemyManager();//�f�X�g���N�^
    const void   Init();                                                                                        //������
    const void   Draw(VECTOR _playerPos, const bool _isFarm, const bool _isBoss);                               //�`��
    const void   Move(const VECTOR _playerPos, const bool _isFarm, const bool _isBoss);                         //�ړ�
    const void   Update(const VECTOR _playerPos,const float _playerLv, const bool _isFarm,const bool _isBoss);  //�X�V
    const void   CreateAndInit();                                                                               //����
    const void   AllDestroy();                                                                                  //���ׂĂ̍폜
    const void   DrawShadow(const int _stageModelHandle, const bool _isFarm, const bool _isBoss);               //�e�̕`��
    const void   AdjustTheNumberOfEnemy(const int _playerLv);                                                   //�G�l�~�[�̃X�|�[�����̒���
    const void   DrawMagicSphere(const int _enemyNum) { strongEnemy[_enemyNum]->DrawMagicSphere(); }            //���@�w�̕`��
    const VECTOR RandomSpawnPos();                                                                              //�����_���ŃX�|�[�����W��Ԃ�
    //�ړ��ʕ␳
    const void FixMoveVecWeakEnemy(const int _enemyNum,const VECTOR _fixVec);
    const void FixMoveVecStrongEnemy(const int _enemyNum, const VECTOR _fixVec);
    const void FixMoveVecBossEnemy(const VECTOR _fixVec);
    //HP�v�Z
    const float CalcHPWeakEnemy(const int _enemyNum,const float _atk,const VECTOR _attackerPos);
    const float CalcHPStrongEnemy(const int _enemyNum, const float _atk, const VECTOR _attackerPos);
    const float CalcHPBossEnemy(const float _atk, const VECTOR _attackerPos);
    //�^����o���l�̏�����
    const void InitExpToGive(const int _enemyNum);
    const void PhysicalRecoveryBossEnemy();
    const void DrawStrongerUI(const float _playerLv,const bool _isFarm);


    /*getter/setter*/
    //���W��getter
    const VECTOR GetPosWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetPos(); }
    const VECTOR GetPosStrongEnemy(const int _enemyNum)const { return strongEnemy[_enemyNum]->GetPos(); }
    const VECTOR GetPosBossEnemy()const { return bossEnemy->GetPos(); }
    //�ړ��ʂ�getter
    const VECTOR GetMoveVecWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetMoveVec(); }
    const VECTOR GetMoveVecStrongEnemy(const int _enemyNum)const { return strongEnemy[_enemyNum]->GetMoveVec(); }
    const VECTOR GetMoveVecBossEnemy()const { return bossEnemy->GetMoveVec(); }
    //�G�l�~�[�z���getter
    const int GetMaxWeakEnemy()const { return MAX_WEAK_ENEMY_NUM; }
    const int GetMaxStrongEnemy()const { return MAX_STRONG_ENEMY_NUM; }
    const int GetNowWeakEnemyNum()const { return nowWeakEnemyNum; }
    const int GetNowStrongEnemyNum()const { return nowStrongEnemyNum; }
    const bool GetIsBossEnemy()const { return isBossEnemy; }
    //���S�t���O��getter
    const bool GetIsDeathWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetIsDeath(); }
    const bool GetIsDeathStrongEnemy(const int _enemyNum)const { return strongEnemy[_enemyNum]->GetIsDeath(); }
    const bool GetIsDeathBossEnemy()const { return bossEnemy->GetIsDeath(); }
    //�J�v�Z������getter
    const CapsuleInfo GetCapsuleInfoWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetCapsuleInfo(); }
    const CapsuleInfo GetCapsuleInfoStrongEnemy(const int _enemyNum)const { return strongEnemy[_enemyNum]->GetCapsuleInfo(); }
    const CapsuleInfo GetCapsuleInfoBossEnemy()const { return bossEnemy->GetCapsuleInfo(); }
    //������getter
    const SphereInfo GetSphereInfoWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetSphereInfo(); }
    const SphereInfo GetSphereInfoStrongEnemy(const int _enemyNum)const { return strongEnemy[_enemyNum]->GetSphereInfo(); }
    const SphereInfo GetSphereInfoBossEnemy()const { return bossEnemy->GetSphereInfo(); }
    //�U���͂�getter
    const float GetAtkWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetAtk(); }
    const float GetAtkStrongEnemy(const int _enemyNum)const { return strongEnemy[_enemyNum]->GetAtk(); }
    const float GetAtkBossEnemy()const { return bossEnemy->GetAtk(); }
    //�U���t���O��getter
    const float GetIsAttackWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetIsAttack(); }
    const float GetIsAttackStrongEnemy(const int _enemyNum)const { return strongEnemy[_enemyNum]->GetIsAttack(); }
    const float GetIsAttackBossEnemy()const { return bossEnemy->GetIsAttack(); }
    //���G�t���O��getter
    const bool GetIsInvincibleWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetIsInvincible(); }
    const bool GetIsInvincibleStrongEnemy(const int _enemyNum)const { return strongEnemy[_enemyNum]->GetIsInvincible(); }
    const bool GetIsInvincibleBossEnemy()const { return bossEnemy->GetIsInvincible(); }
    //�U���̓����蔻���getter
    const bool GetIsHitWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetIsHit(); }
    const bool GetIsHitStrongEnemy(const int _enemyNum)const { return strongEnemy[_enemyNum]->GetIsHit(); }
    const bool GetIsHitBossEnemy()const { return bossEnemy->GetIsHit(); }
    const bool GetIsMeteoAttack()const { return bossEnemy->GetIsMeteoAttack(); }
    const bool GetIsExplosionAttack()const { return bossEnemy->GetIsExplosionAttack(); }
    //�U���J�E���g��getter
    const int GetAttackNumWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetAttackNum(); }
    const int GetAttackNumStrongEnemy(const int _enemyNum)const { return strongEnemy[_enemyNum]->GetAttackNum(); }
    const int GetAttackNumBossEnemy()const { return bossEnemy->GetAttackNum(); }
    
    const void SetIsHitWeakEnemy(const int _enemyNum,const bool _isHitPlayer)const { weakEnemy[_enemyNum]->SetIsHit(_isHitPlayer); }
    const void SetIsHitStrongEnemy(const int _enemyNum, const bool _isHitPlayer)const { strongEnemy[_enemyNum]->SetIsHit(_isHitPlayer); }
    const void SetIsHitBossEnemy(const bool _isHitPlayer)const { bossEnemy->SetIsHit(_isHitPlayer); }
    //���G�t���O������
    const void FlaggingBossEnemy();//�t���O������
    //HP�v�Z
private:
    /*�萔*/
    enum class ModelType//���f���ϐ�
    {
        WEAK_MODEL,     //�G���G
        STRONG_MODEL,   //���{�X
        BOSS_MODEL,     //�{�X
    };
    static constexpr int MAX_WEAK_ENEMY_NUM = 8;  //�G���G�̍ő吔
    static constexpr int MAX_STRONG_ENEMY_NUM = 8;//���{�X�̍ő吔

    static constexpr float  WEAK_ENEMY_RADIUS = 5.0f;         //�G���G�̓����蔻��p�X�t�B�A���a
    static constexpr float  STRONG_ENEMY_RADIUS = 5.0f;       //���{�X�̓����蔻��p�X�t�B�A���a
    static constexpr float  BOSS_ENEMY_RADIUS = 5.0f;         //�{�X�̓����蔻��p�X�t�B�A���a

    static constexpr float  NORMAL_ENEMY_SHADOW_HEIGHT = 1000.0f;   //�ʏ�̓G�̉e�̍���
    static constexpr float  NORMAL_ENEMY_SHADOW_SIZE   = 20.0f;     //�ʏ�̓G�̉e�̃T�C�Y
    static constexpr float  BOSS_ENEMY_SHADOW_HEIGHT   = 1000.0f;   //�{�X�̉e�̍���
    static constexpr float  BOSS_ENEMY_SHADOW_SIZE     = 30.0f;     //�{�X�̉e�̃T�C�Y
    /*�����o�ϐ�*/
    std::vector<WeakEnemy*> weakEnemy;      //�G���G
    std::vector<StrongEnemy*> strongEnemy;  //���{�X
    BossEnemy* bossEnemy;                   //���X�{�X

    MV1_COLL_RESULT_POLY_DIM hitPolyDim;    //�R���W�������ʑ���p�|���S���z��

    vector<int>model;       //���f����
    int nowWeakEnemyNum;    //���݂̎G���G�̐�
    int nowStrongEnemyNum;  //���݂̒��{�X�̐�
    bool isStrongEnemy;     //���{�X����������Ă��邩
    bool isBossEnemy;       //�{�X����������Ă��邩
    bool isDrawImg;         //�摜��`�悵�Ă��邩
    bool isHitCheckSetUp;   //�R���W���������\�z������
    int font;	            //�t�H���g�n���h��
    int frameImage;         //HP�o�[�t���[��
    int hpImage;            //HP�o�[

    //�X�|�[���|�C���g�̕ϐ�
    static constexpr int SPAWN_POINT_NUM = 8;
    static const VECTOR SPAWN_POINT[SPAWN_POINT_NUM];
    bool isAlreadySpawn[SPAWN_POINT_NUM];
};


