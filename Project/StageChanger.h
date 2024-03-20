//===========================================================================
//@brief �X�e�[�W�؂�ւ��N���X
//===========================================================================
#pragma once
#include"DxLib.h"
#include"Common.h"
#include<vector>

class Timer;
using namespace std;
class StageChanger
{
public:
    StageChanger();             //�R���X�g���N�^
    ~StageChanger();            //�f�X�g���N�^

    const void Init();                          //������
    const void Delete();                        //�폜
    const void Draw();                          //�`��
    const void ChangeStage();                   //�X�e�[�W�̕ύX
    const void DrawGameClear();                 //�Q�[���N���A�̉摜�̕\��
    const void DrawImageWhenSwitchingStage();   //�E�F�[�u�J�n���̉摜�̕\��
    const bool DrawAlert(const VECTOR _playerPos, const VECTOR _gatePos, const bool _isShowGate);//farm_boss�̃X�e�[�W�ړ����s�����ǂ���
    /*getter*/
    //�X�e�[�W�؂�ւ��t���O�i�؂�ւ����I����Ă��邩�ǂ������Ǘ��j
    const bool GetIsChangeStage()const { return isChangeStage; }
    //�t�@�[���X�e�[�W�t���O��getter/setter
    const bool GetIsFarm()const { return isFarm; }
    //�{�X�X�e�[�W�t���O��getter/setter
    const bool GetIsBoss()const{return isBoss; }
    //�Q�[���I�[�o�[�t���O��getter/setter
    const bool GetIsGameOver()const { return isGameOver; }
    //�Q�[���N���A�t���O��getter/setter
    const bool GetIsGameClear()const { return isGameClear; }
    //�Q�[���I�[�o�[�t���O��getter/setter
    const bool GetIsGameEnd()const { return isGameEnd; }
    //�x���t���O��getter/setter
    const bool GetIsAlert()const { return isDrawAlert; }
private:
    /*�\���́E�񋓑�*/
    enum class ImageType
    {
        FARM_STAGE, //�t�@�[���X�e�[�W
        BOSS_STAGE,	//�{�X�X�e�[�W
        ALERT,      //��ʈÓ]�p
    };
    /*�ÓI�萔*/
    static constexpr DrawRect   BOSS_UI_DRAW_RECT   = { 1120,660,1320,700 };//�ړ�UI�`��͈�
    static constexpr float      IMG_ANGLE           = 0.0f;                 //�摜�A���O��
    static constexpr float      SET_GAMEOVER_TIMER  = 10.0f;                //�^�C�}�[�ڕW����
    static constexpr float      SET_STAY_TIMER      = 10.0f;                //�^�C�}�[�ڕW����
    static constexpr int        IMG_SIZE            = 60;                   //�摜�T�C�Y
    static constexpr int        IMAGE_NUM           = 3;                    //���摜��
    static constexpr int        VERTEX_POS_NUM      = 4;	                //���_���W��

    static const VERTEX3D INIT_VERTEX;		//�������_���
    static const COLOR_U8 TRAIL_COLOR;		//�O�Ղ̐F
    static const VECTOR DRAW_GATEIMAGE_POS; //�Q�[�g�̕`��ʒu
    static const VECTOR VERTEX_NORM;		//�@���x�N�g��

    /*�����o�ϐ�*/
    Timer* stayMaxAlphaTimer;//�A���t�@�l���ő�̎��ɕ`�悷�鎞��
    
    std::vector<VERTEX3D>   vertexInfo;	    //���_���W
    std::vector<WORD>       vertexIndexAd;  //���_�C���f�b�N�X
    std::vector<int>        image;          //�摜�n���h��

    VEC2D DrawImagePos;     //�摜�`��ʒu
    float gateImageAngle;   //�Q�[�g�摜�̉�]�p�x
    bool  isFarm;           //�t�@�[���X�e�[�W
    bool  isBoss;           //�{�X�X�e�[�W
    bool  isChangeStage;    //�X�e�[�W�؂�ւ��t���O
    bool  isGameOver;       //�Q�[���I�[�o�[�t���O
    bool  isGameClear;      //�Q�[���N���A�t���O
    bool  isGameEnd;        //�Q�[���I���t���O
    bool  isDrawBlackBack;  //���w�i�`��t���O
    bool  isDrawAlert;      //�x���`��t���O(true:�`�悵�Ă��� false:�`�悵�Ă��Ȃ�)
    int   gateImage;        //�Q�[�g�摜
    int   alpha;            //�A���t�@�l
    int   backGroundAlpha;  //�w�i�A���t�@�l
    int   alphaValue;       //������

};