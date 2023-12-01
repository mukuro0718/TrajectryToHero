/*�C���X�^���X�͂��ׂčŏ��ɐ�������
�ϐ��ŏ���������G�̐���ω�������*/
#pragma once

#include"DxLib.h"
#include<vector>

class WeakEnemy;
class StrongEnemy;
class Boss;
using namespace std;
class EnemyManager
{
public:
    EnemyManager();                                         //�R���X�g���N�^
    ~EnemyManager();                                        //�f�X�g���N�^
    void Init();                           //������
    void Draw(VECTOR playerPos, const bool isFarm, const bool isBoss);                            //�`��
    void Update(const VECTOR playerPos, const bool isFarm,const bool isBoss);       //�X�V
    void CreateAndInit();                                          //����
    void AllDestroy();//���ׂĂ̍폜
    void PushBack();    //�����蔻��
    bool CountDestroyEnemy();

    //�G�l�~�[�z���getter/setter
    const int GetMaxWeakEnemy()const { return MAX_WEAK_ENEMY_NUM; }
    const int GetNowEnemyIndex()const { return nowEnemyIndex; }

    const bool GetIsStrongEnemy()const { return isStrongEnemy; }

    const bool GetIsBossEnemy()const { return isBossEnemy; }
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


