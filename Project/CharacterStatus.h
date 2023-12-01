//===========================================================================
//@brief ステータスの初期設定クラス
//===========================================================================

#pragma once
#include"DxLib.h"
class CharacterStatus
{
public:
    CharacterStatus();           //コンストラクタ
    ~CharacterStatus();          //デストラクタ
    void InitWeakEnemyStatus();      //ステータスの初期設定
    void InitStrongEnemyStatus();    //ステータスの初期設定
    void InitBossEnemyStatus();      //ステータスの初期設定
    void InitPlayerStatus();         //ステータスの初期設定

    void CalcHP(const float _atk);//HP計算
    void CalcExp(const float _expToGive);//レベルアップ処理

    const float GetAgi()const { return agi; }
    const float GetHp()const { return hp; }
    const float GetLv()const { return lv; }
    const float GetAtk()const { return atk; }
private:
    /*メンバ変数*/
    float  lv;        //レベル
    float  hp;          //体力
    float  atk;          //攻撃力
    float  def;         //防御力
    float  agi;         //素早さ
    float  expToGive;          //与える経験値
    float  exp;          //経験値
    float  needExp;          //必要経験値
    float  maxHp;          //最大HP

    /*静的定数*/
    static constexpr float MIN_EXP = 5.0f;  //与える最低限の経験値
};