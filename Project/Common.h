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

//カプセルの作成（描画）に必要な情報
struct CapsuleInfo
{
    VECTOR topPos   = ORIGIN_POS;//カプセル上部座標
    VECTOR underPos = ORIGIN_POS;//カプセル下部座標
    float radius    = 0.0f      ;//半径
    int divNum      = 8         ;//カプセル分割数
    int difColor    = 0         ;//ディフューズカラー
    int spcColor    = 0         ;//スペキュラカラー
    int fillFlag    = false     ;//描画する球を塗りつぶすかどうか
};
struct FontInfo//フォントの描画に必要な情報
{
    int size = 0;//フォントの大きさ
    int thick = 0;//フォントの太さ
    int type = 0;//フォントタイプ
};

struct InputAnalogStick//アナログスティック入力変数
{
    int XBuf = 0;//左右の入力状態を格納
    int YBuf = 0;//上下の入力状態を格納
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

