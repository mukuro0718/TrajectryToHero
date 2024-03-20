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

    const void Create() override; //����
    const void Final()  override; //�ŏI����
    const void Update() override; //�X�V
    const void Draw()   override; //�`��
private:
    /*���������֐�*/
    const void ChangeNextScene();//���̃V�[����
    /*�����o�ϐ�*/
    Game* game;//�Q�[���N���X
};

