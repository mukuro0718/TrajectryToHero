//===========================================================================
//@brief �Q�[���V�[���N���X
// �Q�[���N���X�̎��s���V�[���x�[�X�N���X�����Ƃɍs��
//===========================================================================
#pragma once
#include"SceneBase.h"
class Game;

class GameScene :public SceneBase
{
public:
    GameScene();            //�R���X�g���N�^
    virtual ~GameScene();   //�f�X�g���N�^

    void Create() override; //����
    void Final()  override; //�ŏI����
    void Update() override; //�X�V
    void Draw()   override; //�`��
private:
    /*���������֐�*/
    void ChangeNextScene();//���̃V�[����
    /*�����o�ϐ�*/
    Game* game;//�Q�[���N���X
};

