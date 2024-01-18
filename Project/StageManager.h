//===========================================================================
//@brief �X�e�[�W�}�l�[�W���[/�Ǘ�
//===========================================================================

#pragma once
#include"DxLib.h"
#include<vector>

class FarmStage;

class StageManager
{
public:
    StageManager();         // �R���X�g���N�^
    ~StageManager();        //�f�X�g���N�^
    void Draw();            //�Ǘ����邷�ׂẴI�u�W�F�N�g��`��
    void Update();          //�X�V
    void Create();     //����
    void Delete();    //�폜
    const int GetModelHandle()const;
private:
    //�N���X
    FarmStage* farm;      //�}�b�v
    //�ϐ�
    std::vector<int> farmStageData;
};

