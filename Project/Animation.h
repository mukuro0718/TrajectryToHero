//===========================================================================
//@brief アニメーションクラス
//===========================================================================

#pragma once
#include"DxLib.h"
#include<vector>
#include<iostream>
using namespace std;

class Animation
{
public:
    Animation();    //コンストラクタ
    ~Animation();   //デストラクタ

    void Add             (int _animModelHandle, int _useAnimIndex); //アニメーションの追加
    void Attach          (int* _modelHandle);                       //アニメーションのアタッチ
    void Play            (int* _modelHandle);                       //アニメーションの再生時間
    void InitAnimPlayTime() { animPlayTime = 0.0f; }                //アニメーション再生時間の初期化
    void InitIsChangeAnim() { isChangeAnim = false; }               //アニメーション変更フラグの初期化

    //アタッチしているアニメーションのgetter/setter
    void SetAnim(const int _animKind) { nowAnim = _animKind; }
    const int GetAnim()const { return nowAnim; }
    //再生時間のgetter
    const float GetPlayTime()const { return animPlayTime; }
    //アニメーション変更フラグのgetter
    const bool GetIsChangeAnim()const { return isChangeAnim; }
    //モデルハンドルのgetter
    const int GetAnimModelHandle(int modelIndex)const { return animModelHandle[modelIndex]; }
private:
    //変数
    vector<int> animModelHandle;    //アニメーションのモデルのハンドル
    vector<int> useAnimIndex;       //使用したいアニメーションの番号
    int animAttachIndex;            //アニメーションアタッチ番号
    int prevAnim;                   //前のアニメーション
    int nowAnim;                    //現在のアニメーション
    float animTotalTime;            //アニメーション総再生時間
    float animPlayTime;             //アニメーション再生時間
    bool isChangeAnim;              //アニメーション変更フラグ（true:変更可能 false:不可）
};