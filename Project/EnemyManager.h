/*�C���X�^���X�͂��ׂčŏ��ɐ�������
�ϐ��ŏ���������G�̐���ω�������*/
#pragma once

#include"DxLib.h"
#include<vector>
#include"Boss.h"
#include"StrongEnemy.h"
#include"WeakEnemy.h"

using namespace std;
class EnemyManager
{
public:
    EnemyManager();                                         //�R���X�g���N�^
    ~EnemyManager();                                        //�f�X�g���N�^
    void Init();                           //������
    void Draw(VECTOR _playerPos, const bool _isFarm, const bool _isBoss);                            //�`��
    void Move(const VECTOR _playerPos, const bool _isFarm, const bool _isBoss);//�ړ�
    void Update(const VECTOR _playerPos, const bool _isFarm,const bool _isBoss);       //�X�V
    void CreateAndInit();                                          //����
    void AllDestroy();//���ׂĂ̍폜
    bool CountDestroyEnemy();
    void DrawShadow(const int _stageModelHandle, const bool _isFarm, const bool _isBoss);

    //�ړ��ʕ␳
    void FixMoveVecWeakEnemy(const int _enemyNum,const VECTOR _fixVec);
    void FixMoveVecStrongEnemy(const VECTOR _fixVec);
    void FixMoveVecBossEnemy(const VECTOR _fixVec);
    //���W��getter
    const VECTOR GetPosWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetPos(); }
    const VECTOR GetPosStrongEnemy()const { return strongEnemy->GetPos(); }
    const VECTOR GetPosBossEnemy()const { return bossEnemy->GetPos(); }
    //�ړ��ʂ�getter
    const VECTOR GetMoveVecWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetMoveVec(); }
    const VECTOR GetMoveVecStrongEnemy()const { return strongEnemy->GetMoveVec(); }
    const VECTOR GetMoveVecBossEnemy()const { return bossEnemy->GetMoveVec(); }
    //�G�l�~�[�z���getter
    const int GetMaxWeakEnemy()const { return MAX_WEAK_ENEMY_NUM; }
    const int GetNowEnemyIndex()const { return nowEnemyIndex; }
    const bool GetIsStrongEnemy()const { return isStrongEnemy; }
    const bool GetIsBossEnemy()const { return isBossEnemy; }
    //���S�t���O��getter
    const bool GetIsDeathWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetIsDeath(); }
    const bool GetIsDeathStrongEnemy()const { return strongEnemy->GetIsDeath(); }
    const bool GetIsDeathBossEnemy()const { return bossEnemy->GetIsDeath(); }
    //�J�v�Z������getter
    const CapsuleInfo GetCapsuleInfoWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetCapsuleInfo(); }
    const CapsuleInfo GetCapsuleInfoStrongEnemy()const { return strongEnemy->GetCapsuleInfo(); }
    const CapsuleInfo GetCapsuleInfoBossEnemy()const { return bossEnemy->GetCapsuleInfo(); }
    //������getter
    const SphereInfo GetSphereInfoWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetSphereInfo(); }
    const SphereInfo GetSphereInfoStrongEnemy()const { return strongEnemy->GetSphereInfo(); }
    const SphereInfo GetSphereInfoBossEnemy()const { return bossEnemy->GetSphereInfo(); }
    //�U���͂�getter
    const float GetAtkWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetAtk(); }
    const float GetAtkStrongEnemy()const { return strongEnemy->GetAtk(); }
    const float GetAtkBossEnemy()const { return bossEnemy->GetAtk(); }
    //�U���t���O��getter
    const float GetIsAttackWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetIsAttack(); }
    const float GetIsAttackStrongEnemy()const { return strongEnemy->GetIsAttack(); }
    const float GetIsAttackBossEnemy()const { return bossEnemy->GetIsAttack(); }
    //���G�t���O��getter
    const bool GetIsInvincible(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetIsInvincible(); }
    //HP�v�Z
    float CalcHPWeakEnemy(const int _enemyNum,const float _atk);
    //�^����o���l�̏�����
    void InitExpToGive(const int _enemyNum);
private:
    /*�萔*/
    enum class ModelType//���f���ϐ�
    {
        WEAK_MODEL,     //�G���G
        STRONG_MODEL,   //���{�X
        BOSS_MODEL,     //�{�X
    };
    static constexpr int    MAX_WEAK_ENEMY_NUM = 8;         //�G���G�̐�
    static constexpr float  weakEnemyRadius = 5.0f;         //�G���G�̓����蔻��p�X�t�B�A���a
    static constexpr float  strongEnemyRadius = 5.0f;       //���{�X�̓����蔻��p�X�t�B�A���a
    static constexpr float  bossEnemyRadius = 5.0f;         //�{�X�̓����蔻��p�X�t�B�A���a
    static constexpr float  NORMAL_ENEMY_SHADOW_HEIGHT = 1000.0f;   //�ʏ�̓G�̉e�̍���
    static constexpr float  NORMAL_ENEMY_SHADOW_SIZE   = 20.0f;     //�ʏ�̓G�̉e�̃T�C�Y
    static constexpr float  BOSS_ENEMY_SHADOW_HEIGHT   = 1000.0f;   //�{�X�̉e�̍���
    static constexpr float  BOSS_ENEMY_SHADOW_SIZE     = 30.0f;     //�{�X�̉e�̃T�C�Y
    /*�����o�ϐ�*/
    WeakEnemy* weakEnemy[MAX_WEAK_ENEMY_NUM];
    StrongEnemy* strongEnemy;
    Boss* bossEnemy;                                   //���X�{�X
    MV1_COLL_RESULT_POLY_DIM hitPolyDim;                    //�R���W�������ʑ���p�|���S���z��
    vector<int>model;
    bool isStrongEnemy;                                     //���{�X����������Ă��邩
    bool isBossEnemy;                                       //�{�X����������Ă��邩
    bool isDrawImg;                                         //�摜��`�悵�Ă��邩
    bool isHitCheckSetUp;                                   //�R���W���������\�z������
    int nowEnemyIndex;                                      //���݂���G�̐�
    int destroyEnemy;                                       //�|���ꂽ�G�l�~�[�̐�
    int deathStrongEnemyNum;
    static const	 int   FONT_COLOR_GREEN;			//�t�H���g�̐F
    static constexpr int   HP_FONT_SIZE = 64;		//�t�H���g�̃T�C�Y
    static constexpr int   HP_FONT_THICK = 28;		//�t�H���g�̑���
    int   hpFontHandle;	//HP�t�H���g�n���h��
    
    //�X�|�[���|�C���g�̕ϐ�
    static constexpr int SPAWN_POINT_NUM = 8;
    static const VECTOR SPAWN_POINT[SPAWN_POINT_NUM];
    bool isAlreadySpawn[SPAWN_POINT_NUM];
};


