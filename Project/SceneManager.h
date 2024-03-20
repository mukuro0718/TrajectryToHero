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

    const void mainGame();//�Q�[���{��

private:
    /*���������֐�*/
    const void ChangeScene(); //�V�[���̐؂�ւ�
    const void Create();      //�쐬
    const void Final();       //�ŏI����
    const void Update();      //�X�V
    const void Draw();        //�`��
    /*�N���X*/
    SceneBase*     scene;           //�V�[��
    FPSController* fpsController;   //FPS�R���g���[���[
};