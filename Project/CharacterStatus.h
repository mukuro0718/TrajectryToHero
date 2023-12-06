//===========================================================================
//@brief ステータスクラス
// キャラクターごとのステータスの初期化
// ステータス上昇計算をおこなう
//===========================================================================

#pragma once
#include"DxLib.h"
#include<vector>
#include<string>

using namespace std;
class Timer;

class CharacterStatus final
{
public:
    CharacterStatus();           //コンストラクタ
    ~CharacterStatus();          //デストラクタ

    void Init();											// 初期化
    void Delete();											// 画像ハンドル、クラスインスタンスの削除
    void Update();	// 更新
    void Draw();								// 描画


    void InitWeakEnemyStatus();      //ステータスの初期設定
    void InitStrongEnemyStatus();    //ステータスの初期設定
    void InitBossEnemyStatus();      //ステータスの初期設定
    void InitPlayerStatus();         //ステータスの初期設定

    float CalcHP(const float _atk);//HP計算
    void CalcExp(const float _expToGive);//レベルアップ処理
    void InitExpToGive();
    const float GetAgi()const { return agi; }
    const float GetHp()const { return hp; }
    const float GetLv()const { return lv; }
    const float GetAtk()const { return atk; }
    const bool GetIsShowMenu()const { return isShowMenu; }
    void ShowInfo();//情報の表示
private:
    /*クラス・構造体*/
    struct VEC2D
    {
        int x = 0;
        int y = 0;
    };
    enum class SelectStatus//選択しているステータスの種類
    {
        ATK,//攻撃力
        DEF,//防御力
        AGI,//素早さ
    };
    /*静的定数*/
    static constexpr float MIN_EXP = 5.0f;  //与える最低限の経験値

    static constexpr float	IMG_SIZE = 5.0f;			//画像サイズ
    static constexpr float	IMG_ANGLE = 0.0f;			//回転率
    static constexpr float	LV_UP_ADD_VALUE = 1.0f;			//レベルアップ時ステータス増加量
    static constexpr int	MODIFIABLE_STATUS_COUNT = 3;				//変更可能なステータスの数
    static constexpr int	FONT_SIZE = 128;				//フォントのサイズ
    static constexpr int	FONT_THICK = 64;				//フォントの太さ
    static constexpr int	BACKGROUND_WIDTH = 900;				//背景画像の横
    static constexpr int	BACKGROUND_HEIGHT = 980;				//背景画像の縦
    static const	 int	FONT_COLOR_RED;								//フォントの色
    static const	 int	FONT_COLOR_WHITE;							//フォントの色
    static const	 VECTOR SET_DRAW_POS;								//描画座標
    static constexpr VEC2D	BACKGROUND_POS = { 510,50 };		//メニュー背景座標
    static constexpr VEC2D	STATUS_UP_TEXT_POS = { 650,100 };		//ステータスアップテキスト座標
    static constexpr VEC2D	STATUS_TEXT_POS[MODIFIABLE_STATUS_COUNT] =	//ボタン座標
    {
        {850,300},
        {850,500},
        {850,700},
    };

    /*内部処理関数*/
    void ChangeSelectStatus();//選択しているステータスの変更
    void UpSelectStatus();//選択しているステータスの上昇
    void ChangeBlendRateDrawText(const int nowSelectStatus, const int statusType);//ブレンド率を変えて描画

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

    float  prevLv;				//前回のレベル
    bool   isShowMenu;			//メニューを表示しているか
    bool   isLvUP;				//レベルアップしたか
    bool   isFinalSelectStatus;	//最終的に選択したステータス
    bool   isInputPad;			//スティック入力しているか（連続入力の防止）
    int    lvUpCount;			//現在のレベルアップ数（今のレベルから前のレベルを引く）
    int    nowSelectStatus;		//現在選択しているステータス
    int	   backGroundImage;		//背景画像ハンドル
    Timer* inputWaitTimer;		//入力待機時間
    int	   statusFontHandle;	//LvUp時メニュー用フォントハンドル

};