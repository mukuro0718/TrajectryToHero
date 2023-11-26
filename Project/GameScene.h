////===========================================================================
////@brief �Q�[���V�[���N���X
//// �Q�[���V�[���̏������s��
////===========================================================================
//#pragma once
//#include"DxLib.h"
//#include"SceneBase.h"
//#include<vector>
//class Camera;
//class StageManager;
//class StageChanger;
//class EnemyManager;
//class PlayerManager;
//class Timer;
//class Collision;
//class Shadow;
//class Animation;
//
//using namespace std;
//
//class GameScene :public SceneBase
//{
//public:
//    GameScene();            //�R���X�g���N�^
//    virtual ~GameScene();   //�f�X�g���N�^
//
//    void Create() override; //����
//    void Final()  override; //�ŏI����
//    void Update() override; //�X�V
//    void Draw()   override; //�`��
//
//    void EndWave(); //�E�F�[�u�̏I������
//private:
//    static constexpr float  PLAYER_SHADOW_HEIGHT       = 1000.0f;   //�v���C���[�̉e�̍���
//    static constexpr float  PLAYER_SHADOW_SIZE         = 20.0f;     //�v���C���[�̉e�̃T�C�Y
//    static constexpr float  NORMAL_ENEMY_SHADOW_HEIGHT = 1000.0f;   //�ʏ�̓G�̉e�̍���
//    static constexpr float  NORMAL_ENEMY_SHADOW_SIZE   = 20.0f;     //�ʏ�̓G�̉e�̃T�C�Y
//    static constexpr float  BOSS_ENEMY_SHADOW_HEIGHT   = 1000.0f;   //�{�X�̉e�̍���
//    static constexpr float  BOSS_ENEMY_SHADOW_SIZE     = 30.0f;     //�{�X�̉e�̃T�C�Y
//    static constexpr int    FONT_SIZE                  = 28;        //�t�H���g�̃T�C�Y
//    static constexpr int    FONT_THICK                 = 28;        //�t�H���g�̑���
//    static const     int    FONT_COLOR;                             //�t�H���g�̐F
//    static const     VECTOR SHADOW_OFFSET_POS;                      //�v���C���[���W�I�t�Z�b�g
//
//    /*���������֐�*/
//    void HitCheckAllEnemy();                    //���ł̓����蔻��
//    void DrawShadow();                          //�e�̕`��
//    void AttackToEnemy();                       //�G�l�~�[�ւ̍U��
//    void AttackToPlayer();                      //�v���C���[�ւ̍U��
//    void Init();                                //������
//    void ChangeNextScene();//�V�[���؂�ւ�
//    /*�N���X*/
//    Camera*        camera;          //�J����
//    StageManager*  stageManager;    //�X�e�[�W
//    StageChanger*  stageChanger;    //�X�e�[�W�ύX
//    EnemyManager*  enemyManager;    //�G�l�~�[
//    PlayerManager* playerManager;   //�v���C���[
//    Collision*     collision;       //�����蔻��
//    Shadow*        shadow;          //�e
//    Animation* anim;
//    /*�ϐ�*/
//    int input;          //���͕ϐ�
//    int alpha;          //�A���t�@�l
//    int fontHandle;     //�t�H���g�n���h��
//    int skyDomeHandle;
//    int bossModelHandle;
//};
//
