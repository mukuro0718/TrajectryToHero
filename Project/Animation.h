//===========================================================================
//@brief �A�j���[�V�����N���X
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

    void Add             (int _animModelHandle, int _useAnimIndex); //�A�j���[�V�����̒ǉ�
    void Attach          (int* _modelHandle);                       //�A�j���[�V�����̃A�^�b�`
    void Play            (int* _modelHandle);                       //�A�j���[�V�����̍Đ�����
    void InitAnimPlayTime() { animPlayTime = 0.0f; }                //�A�j���[�V�����Đ����Ԃ̏�����
    void InitIsChangeAnim() { isChangeAnim = false; }               //�A�j���[�V�����ύX�t���O�̏�����

    //�A�^�b�`���Ă���A�j���[�V������getter/setter
    void SetAnim(const int _animKind) { nowAnim = _animKind; }
    const int GetAnim()const { return nowAnim; }
    //�Đ����Ԃ�getter
    const float GetPlayTime()const { return animPlayTime; }
    //�A�j���[�V�����ύX�t���O��getter
    const bool GetIsChangeAnim()const { return isChangeAnim; }
    //���f���n���h����getter
    const int GetAnimModelHandle(int modelIndex)const { return animModelHandle[modelIndex]; }
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