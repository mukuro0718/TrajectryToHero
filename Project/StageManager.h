//===========================================================================
//@brief �X�e�[�W�}�l�[�W���[/�Ǘ�
//===========================================================================

#pragma once
#include"DxLib.h"
#include"StageBase.h"

class StageManager
{
public:
    StageManager();         // �R���X�g���N�^
    ~StageManager();        //�f�X�g���N�^
    void Draw();            //�Ǘ����邷�ׂẴI�u�W�F�N�g��`��
    void Update();          //�X�V
    void Create();     //����
    void Delete();    //�폜
    const int GetModelHandle()const { return ground->GetModelHandle(); }
private:
    //�N���X
    StageBase* ground;      //�}�b�v
    //�ϐ�
    int model;
};

