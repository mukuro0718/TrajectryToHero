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
class CrackerParticle;
class CharacterStatus final
{
public:
    CharacterStatus();           //コンストラクタ
    ~CharacterStatus();          //デストラクタ

    const void Init();											// 初期化
    const void Delete();											// 画像ハンドル、クラスインスタンスの削除
    const void Update(const bool _isShowMenu);	// 更新
    const void Draw();								// 描画

    const void  InitTutorialStatus(const int _showCount);
    const void  InitWeakEnemyStatus(const float _playerLv);    //ステータスの初期設定
    const void  InitStrongEnemyStatus(const float _playerLv);  //ステータスの初期設定
    const void  InitBossEnemyStatus();                         //ステータスの初期設定
    const void  InitPlayerStatus();                            //ステータスの初期設定
    const void  InitExpToGive();                               //経験値の初期化
    const void  PhysicalRecovery();//体力回復
    const void  CalcExp(const float _expToGive);//レベルアップ処理
    const void  ShowInfo();//情報の表示
    const void  TutorialStatusReset();
    const float CalcHP(const float _atk);//HP計算

    /*getter*/
    const bool  GetIsShowMenu()const { return isShowMenu; }
    const bool  GetIsBonfireMenu()const { return isBonfireMenu; }
    const float GetAgi()const { return agi; }
    const float GetHp()const { return hp; }
    const float GetLv()const { return lv; }
    const float GetAtk()const { return atk; }
    const float GetMaxHP()const { return maxHp;}
    const float GetExp()const { return exp; }
    const float GetNeedExp()const { return needExp; }
    const int   GetAtkUpCount()const { return atkUpCount; }
    const int   GetAgiUpCount()const { return agiUpCount; }
    const int   GetDefUpCount()const { return defUpCount; }
private:
    /*構造体・列挙体*/
    enum class DataType//ロードしたデータの種類
    {
        BACK_GROUND,
        BONFIRE_MENU,
        CURSOR,
        SELECT_RECT,
        ATK,
        AGI,
        DEF,
        A_BUTTON,
        B_BUTTON,
    };
    enum class SelectBonfireMenu//かがり火メニュー
    {
        BACK_TO_THE_GAME,//ゲームに戻る
        LEVEL_UP,//レベルアップ
        BACK_TO_THE_TITLE,//タイトルに戻る
    };
    struct Vec2d//2Dベクトル構造体
    {
        int x = 0;
        int y = 0;
    };
    enum class SelectStatus//ステータス種類
    {
        ATK,
        AGI,
        DEF
    };
    struct DrawRect
    {
        int lx = 0;
        int ly = 0;
        int rx = 0;
        int ry = 0;
    };
    /*静的定数*/
    static constexpr DrawRect ATK_POS             = { 600,450,800,650 };    //攻撃画像描画範囲
    static constexpr DrawRect AGI_POS             = { 900,450,1100,650 };   //素早さ画像描画範囲
    static constexpr DrawRect DEF_POS             = { 1200,450,1400,650 };  //防御力画像描画範囲
    static constexpr DrawRect ATK_HIGH_CURSOR_POS = { 670,670,700,700 };    //上矢印座標
    static constexpr DrawRect AGI_HIGH_CURSOR_POS = { 960,670,990,700 };    //上矢印座標
    static constexpr DrawRect DEF_HIGH_CURSOR_POS = { 1270,670,1300,700 };  //上矢印座標
    static constexpr DrawRect ATK_LOW_CURSOR_POS  = { 670,760,700,730 };    //下矢印座標
    static constexpr DrawRect AGI_LOW_CURSOR_POS  = { 960,760,990,730 };    //下矢印座標
    static constexpr DrawRect DEF_LOW_CURSOR_POS  = { 1270,760,1300,730 };  //下矢印座標
    static constexpr DrawRect BACKGROUND_POS      = {550,250,1450,800};     //背景描画位置
    static constexpr Vec2d    menuPos             = { 100,100 };            //メニュー座標
    static constexpr Vec2d    highCursorPos       = { 159,152 };            //上矢印座標
    static constexpr Vec2d    lowCursorPos        = { 175,967 };            //下矢印座標
    static constexpr Vec2d    GAME_POS            = { 200,200 };            //選択位置（ゲームに戻る）
    static constexpr Vec2d    LEVEL_POS           = { 200,269 };            //選択位置（レベルアップ）
    static constexpr Vec2d    ATK_TEXT_POS        = { 650,420 };            //文字描画位置
    static constexpr Vec2d    AGI_TEXT_POS        = { 950,420 };            //文字描画位置
    static constexpr Vec2d    DEF_TEXT_POS        = { 1250,420 };           //文字描画位置
    static constexpr Vec2d    TEXT_POS            = { 600,300 };            //レベルアップメニュータイトル文字描画位置
    static constexpr Vec2d    ATK_UP_COUNT_POS    = { 670,700 };            //攻撃力上昇回数描画位置
    static constexpr Vec2d    AGI_UP_COUNT_POS    = { 960,700 };            //素早さ上昇回数描画位置
    static constexpr Vec2d    DEF_UP_COUNT_POS    = { 1270,700 };           //防御力上昇回数描画位置
    static constexpr float    MAX_LV              = 16.0f;                  //最大レベル
    static constexpr int      MAX_ATK_UP_COUNT    = 5;                      //最大ステータス上昇回数
    static constexpr int      MAX_AGI_UP_COUNT    = 5;                      //最大ステータス上昇回数
    static constexpr int      MAX_DEF_UP_COUNT    = 5;                      //最大ステータス上昇回数

    static const int FONT_COLOR;//文字の色
    static const int BLUE_FONT_COLOR;//文字（青色）

    /*内部処理関数*/
    const void UpdateBonfireMenu();
    const void DrawBonfireMenu();
    const void UpdateLevelUpMenu();
    const void DrawLevelUpMenu();

    /*メンバ変数*/
    CrackerParticle* particle;          //ステータスアップ時パーティクル
    Timer*           inputWaitTimer;	//入力待機時間

    DrawRect nowHighCursorPos;  //現在の上矢印描画位置
    DrawRect nowLowCursorPos;   //現在の下矢印描画位置
    Vec2d    rectPos;           //選択位置（わかりやすいように描画する画像の位置）
    float    lv;                //レベル
    float    hp;                //体力
    float    atk;               //攻撃力
    float    def;               //防御力
    float    agi;               //素早さ
    float    expToGive;         //与える経験値
    float    exp;               //経験値
    float    needExp;           //必要経験値
    float    maxHp;             //最大HP
    float    prevLv;		    //前回のレベル
    bool     isInputPad;        //入力があったか
    bool     isFinalSelectMenu; //メニュー上での最終決定（Aボタンが押されたか）
    bool     isShowMenu;        //メニューを表示しているか
    bool     isLevelUp;         //レベルアップしているか
    bool     isBonfireMenu;     //焚火メニューを表示しているか
    bool     isShowLevelUpMenu;	//メニューを表示しているか
    int      nowSelectMenu;     //現在選択しているメニュー
    int      atkUpCount;        //ステータス上昇回数
    int      agiUpCount;        //ステータス上昇回数
    int      defUpCount;        //ステータス上昇回数
    int      prevAtkUpCount;    //以前のステータス上昇回数
    int      prevAgiUpCount;    //以前のステータス上昇回数
    int      prevDefUpCount;    //以前のステータス上昇回数
    int      nowSelectStatus;   //現在選択しているステータス
    int      statusUpPoint;     //ステータス上昇ポイント
    int      prevStatusUpPoint; //以前のステータス上昇ポイント

    std::vector<int> data;//ロードしたデータ
};