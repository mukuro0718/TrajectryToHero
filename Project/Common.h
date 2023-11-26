//===========================================================================
//@brief 共通クラス
// 各クラスで共通して使う定数や関数を定義
//===========================================================================

#pragma once
#include"DxLib.h"

static constexpr int    WINDOW_WIDTH  = 1920;                   //ウィンドウ横サイズ
static constexpr int    WINDOW_HEIGHT = 1080;                   //ウィンドウ縦サイズ
static constexpr int    COLOR_BIT     = 16;                     //カラービット
static const     VECTOR ORIGIN_POS    = VGet(0.0f, 0.0f, 0.0f); //０座標


//キャラクターの共通ステータス
struct CharacterStatus
{
    float  HP           = 0.0f;         //体力
    float  ATK          = 0.0f;         //攻撃力
    float  DEF          = 0.0f;         //防御力
    float  AGI          = 0.0f;         //素早さ
    float  LV           = 0.0f;         //レベル
    float  EXP_TO_GIVE  = 0.0f;         //与える経験値
    float  EXP          = 0.0f;         //経験値
    bool   isHit        = false;		//当たったか
    bool   isInvincible = false;        //無敵状態
};
//キャラクター共通ベース
struct CharacterBase
{
    VECTOR pos         = ORIGIN_POS;    //座標
    VECTOR rotate      = ORIGIN_POS;    //回転率
    VECTOR scale       = ORIGIN_POS;    //拡大率
    float  radius      = 0.0f;          //半径
    int    modelHandle = 0;			    //モデルハンドル
    bool   isSelectAttack = false;      //攻撃を選択しているか
    bool   isAttack    = false;		    //攻撃中か
    bool   isDeath     = false;			//死亡アニメーションを描画し終わったか
    bool   isHit       = false;         //半径がヒットしたか
    VECTOR  correctionValue = ORIGIN_POS;      //補正値
};
struct VEC2D//２Dベクトル構造体
{
    int x = 0;
    int y = 0;
};
enum class SceneType//シーンタイプ
{
    OPENING,	//オープニング
    TITLE,		//タイトル
    GAME,		//ゲーム
    GAMECLEAR,	//エンド
    GAMEOVER,	//エンド
};

float RadToDeg(float _rad);		// ラシアンを度に
float DegToRad(float _deg);		// 度をラジアンに

bool operator ==(VECTOR _vector1, VECTOR _vector2);

