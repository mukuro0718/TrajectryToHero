//===========================================================================
//@brief �X�e�[�W�}�l�[�W���[/�Ǘ�
//===========================================================================

#pragma once
#include"DxLib.h"
#include<vector>

class FarmStage;
class Bonfire;

class StageManager
{
public:
    StageManager();   // �R���X�g���N�^
    ~StageManager();  //�f�X�g���N�^
    void Draw(const bool _isFarm);      //�Ǘ����邷�ׂẴI�u�W�F�N�g��`��
    void Update(const int _playerLv);    //�X�V
    void Create();    //����
    void Delete();    //�폜
    const int GetModelHandle()const;
    const VECTOR GetBonfirePos()const;
    const bool GetIsShowGate()const;
    const VECTOR GetGatePos()const;
private:
    //�N���X
    FarmStage* farm;    //�}�b�v
    Bonfire* bonfire;   //�������
    //�ϐ�
    std::vector<int> farmStageData;
};

