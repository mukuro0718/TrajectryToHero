//===========================================================================
//@brief �A�j���[�V�����N���X
// �d�l��ŏ_��ɒl��ύX�ł���悤�ɁAgetter/setter�����p����Ă��邪
// ����ł̓J�v�Z�������ł��Ă��Ȃ��̂ŁA���ǂ̗]�n����
//===========================================================================

#pragma once
#include"DxLib.h"
#include<vector>
#include<iostream>
using namespace std;

class Animation
{
public:
    Animation();    //�R���X�g���N�^
    ~Animation();   //�f�X�g���N�^

    void Add             (int _animModelHandle, int _useAnimIndex);         //�A�j���[�V�����̒ǉ�
    void Attach          (int* _modelHandle);                               //�A�j���[�V�����̃A�^�b�`
    void Play            (int* _modelHandle, const float _addAnimPlayTime); //�A�j���[�V�����̍Đ�����
    void InitAnimPlayTime() { animPlayTime = 0.0f; }                        //�A�j���[�V�����Đ����Ԃ̏�����
    void InitIsChangeAnim() { isChangeAnim = false; }                       //�A�j���[�V�����ύX�t���O�̏�����

    /*getter/setter*/
          void   SetAnim(const int _animKind) { nowAnim = _animKind; }
    const int    GetAnim()              const { return nowAnim; }
    const float  GetPlayTime()          const { return animPlayTime; }
    const bool   GetIsChangeAnim()      const { return isChangeAnim; }
    const int    GetAnimModelHandle(int modelIndex)const { return animModelHandle[modelIndex]; }
private:
    //�ϐ�
    vector<int> animModelHandle;    //�A�j���[�V�����̃��f���̃n���h��
    vector<int> useAnimIndex;       //�g�p�������A�j���[�V�����̔ԍ�
    int animAttachIndex;            //�A�j���[�V�����A�^�b�`�ԍ�
    int prevAnim;                   //�O�̃A�j���[�V����
    int nowAnim;                    //���݂̃A�j���[�V����
    float animTotalTime;            //�A�j���[�V�������Đ�����
    float animPlayTime;             //�A�j���[�V�����Đ�����
    bool isChangeAnim;              //�A�j���[�V�����ύX�t���O�itrue:�ύX�\ false:�s�j
};