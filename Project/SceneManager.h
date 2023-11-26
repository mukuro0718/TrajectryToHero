//===========================================================================
//@brief �V�[���}�l�[�W���[�N���X
// �V�[���̊e���������s����
//===========================================================================

#pragma once
#include"DxLib.h"
#include"Common.h"
class SceneBase;
class FPSController;

class SceneManager final
{
public:
    SceneManager(); //�R���X�g���N�^
    ~SceneManager();//�f�X�g���N�^

    void mainGame();//�Q�[���{��

private:
    /*���������֐�*/
    void ChangeScene(); //�V�[���̐؂�ւ�
    void Create();      //�쐬
    void Final();       //�ŏI����
    void Update();      //�X�V
    void Draw();        //�`��
    /*�N���X*/
    SceneBase*     scene;           //�V�[��
    FPSController* fpsController;   //FPS�R���g���[���[
};