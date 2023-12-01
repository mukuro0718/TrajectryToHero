//===========================================================================
//@brief �X�e�[�^�X�̏����ݒ�N���X
//===========================================================================

#pragma once
#include"DxLib.h"
class CharacterStatus
{
public:
    CharacterStatus();           //�R���X�g���N�^
    ~CharacterStatus();          //�f�X�g���N�^
    void InitWeakEnemyStatus();      //�X�e�[�^�X�̏����ݒ�
    void InitStrongEnemyStatus();    //�X�e�[�^�X�̏����ݒ�
    void InitBossEnemyStatus();      //�X�e�[�^�X�̏����ݒ�
    void InitPlayerStatus();         //�X�e�[�^�X�̏����ݒ�

    void CalcHP(const float _atk);//HP�v�Z
    void CalcExp(const float _expToGive);//���x���A�b�v����

    const float GetAgi()const { return agi; }
    const float GetHp()const { return hp; }
    const float GetLv()const { return lv; }
    const float GetAtk()const { return atk; }
private:
    /*�����o�ϐ�*/
    float  lv;        //���x��
    float  hp;          //�̗�
    float  atk;          //�U����
    float  def;         //�h���
    float  agi;         //�f����
    float  expToGive;          //�^����o���l
    float  exp;          //�o���l
    float  needExp;          //�K�v�o���l
    float  maxHp;          //�ő�HP

    /*�ÓI�萔*/
    static constexpr float MIN_EXP = 5.0f;  //�^����Œ���̌o���l
};