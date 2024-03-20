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

    const void Draw(const bool _isFarm);    //�Ǘ����邷�ׂẴI�u�W�F�N�g��`��
    const void Update(const int _playerLv); //�X�V
    const void Create();                    //����
    const void Delete();                    //�폜
    
    /*getter*/
    const VECTOR GetBonfirePos()const;
    const VECTOR GetGatePos()const;
    const bool   GetIsShowGate()const;
    const int    GetModelHandle()const;
private:
    /*�����o�ϐ�*/
    FarmStage*  farm;   //�}�b�v
    Bonfire*    bonfire;//�������

    std::vector<int> farmStageData;//�X�e�[�W���f���f�[�^
};

