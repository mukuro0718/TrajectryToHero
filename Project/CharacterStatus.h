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

    void Init();											// 初期化
    void Delete();											// 画像ハンドル、クラスインスタンスの削除
    void Update(const bool _isShowMenu);	// 更新
    void Draw();								// 描画

    void InitTutorialStatus(const int _showCount);
    void InitWeakEnemyStatus(const float _playerLv);    //ステータスの初期設定
    void InitStrongEnemyStatus(const float _playerLv);  //ステータスの初期設定
    void InitBossEnemyStatus();                         //ステータスの初期設定
    void InitPlayerStatus();                            //ステータスの初期設定
    void InitExpToGive();                               //経験値の初期化
    void PhysicalRecovery();//体力回復
    float CalcHP(const float _atk);//HP計算
    void CalcExp(const float _expToGive);//レベルアップ処理
    const float GetAgi()const { return agi; }
    const float GetHp()const { return hp; }
    const float GetDef()const { return def; }
    const float GetLv()const { return lv; }
    const float GetAtk()const { return atk; }
    const int GetAtkUpCount()const { return atkUpCount; }
    const int GetAgiUpCount()const { return agiUpCount; }
    const int GetDefUpCount()const { return defUpCount; }
    const float GetMaxHP()const { return maxHp;}
    const float GetExp()const { return exp; }
    const float GetNeedExp()const { return needExp; }
    const bool GetIsShowMenu()const { return isShowMenu; }
    const bool GetIsBonfireMenu()const { return isBonfireMenu; }
    void ShowInfo();//情報の表示
    void TutorialStatusReset();
private:
    /*クラス・構造体*/
    enum class DataType
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
    std::vector<int> data;
    //==============================
    //かがり火メニュー
    //==============================
    enum class SelectBonfireMenu
    {
        BACK_TO_THE_GAME,//ゲームに戻る
        LEVEL_UP,//レベルアップ
        BACK_TO_THE_TITLE,//タイトルに戻る
    };
    struct Vec2d
    {
        int x = 0;
        int y = 0;
    };
    static constexpr Vec2d menuPos = { 100,100 };
    static constexpr Vec2d highCursorPos = { 159,152 };
    static constexpr Vec2d lowCursorPos = { 175,967 };
    static constexpr int ADD_RECTPOS_VALUE = 64;
    static constexpr int FRAME_LIMIT = 60;
    static constexpr int RECTPOS_MIN_VALUE = 200;
    static constexpr int RECTPOS_MAX_VALUE = 792;

    static constexpr Vec2d GAME_POS = { 200,200 };
    static constexpr Vec2d LEVEL_POS = { 200,269 };
    static constexpr Vec2d TITLE_POS = { 200,338 };

    void UpdateBonfireMenu();
    void DrawBonfireMenu();

    Vec2d rectPos;
    int nowSelectMenu;
    int menuImage;
    int cursorImage;
    int rectImage;
    int frameCount;
    bool isInputPad;
    bool isFinalSelectMenu;
    bool isShowMenu;
    //=======================================
    //レベルアップメニュー
    //=======================================
    enum class SelectStatus
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
    static constexpr DrawRect ATK_POS = { 600,450,800,650 };
    static constexpr DrawRect AGI_POS = { 900,450,1100,650 };
    static constexpr DrawRect DEF_POS = { 1200,450,1400,650 };
    static constexpr Vec2d ATK_TEXT_POS = { 650,420 };
    static constexpr Vec2d AGI_TEXT_POS = { 950,420 };
    static constexpr Vec2d DEF_TEXT_POS = { 1250,420 };
    static constexpr Vec2d TEXT_POS = { 600,300 };
    static constexpr Vec2d ATK_UP_COUNT_POS = { 670,700 };
    static constexpr Vec2d AGI_UP_COUNT_POS = { 960,700 };
    static constexpr Vec2d DEF_UP_COUNT_POS = { 1270,700 };

    static constexpr DrawRect ATK_HIGH_CURSOR_POS = { 670,670,700,700 };
    static constexpr DrawRect AGI_HIGH_CURSOR_POS = { 960,670,990,700 };
    static constexpr DrawRect DEF_HIGH_CURSOR_POS = { 1270,670,1300,700 };

    static constexpr DrawRect ATK_LOW_CURSOR_POS = { 670,760,700,730 };
    static constexpr DrawRect AGI_LOW_CURSOR_POS = { 960,760,990,730 };
    static constexpr DrawRect DEF_LOW_CURSOR_POS = { 1270,760,1300,730 };
    static constexpr DrawRect BACKGROUND_POS = {550,250,1450,800};

    static constexpr int MAX_ATK_UP_COUNT = 5;
    static constexpr int MAX_AGI_UP_COUNT = 5;
    static constexpr int MAX_DEF_UP_COUNT = 5;
    static constexpr float MAX_LV = 16.0f;

    static const int FONT_COLOR;
    static const int BLUE_FONT_COLOR;
    static const int PREV_FONT_COLOR;
    int atkImage;
    int agiImage;
    int defImage;
    int atkUpCount;
    int agiUpCount;
    int defUpCount;
    int prevAtkUpCount;
    int prevAgiUpCount;
    int prevDefUpCount;
    int nowSelectStatus;
    int statusUpPoint;
    int prevStatusUpPoint;
    DrawRect nowHighCursorPos;
    DrawRect nowLowCursorPos;
    void UpdateLevelUpMenu();
    void DrawLevelUpMenu();

    bool isBonfireMenu;
    bool isLevelUp;



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
    static constexpr Vec2d	STATUS_UP_TEXT_POS = { 650,100 };		//ステータスアップテキスト座標
    static constexpr Vec2d  STATUS_UP_COUNT_TEXT_POS[MODIFIABLE_STATUS_COUNT] =
    {
        {850,300},
        {850,500},
        {850,700},
    };
    static constexpr Vec2d	STATUS_TEXT_POS[MODIFIABLE_STATUS_COUNT] =	//ボタン座標
    {
        {850,300},
        {850,500},
        {850,700},
    };
    static const VECTOR BONFIRE_POS;
    /*内部処理関数*/
    void ChangeBlendRateDrawText(const int nowSelectStatus, const int statusType);//ブレンド率を変えて描画
    /*メンバ変数*/
    float  lv;          //レベル
    float  hp;          //体力
    float  atk;         //攻撃力
    float  def;         //防御力
    float  agi;         //素早さ
    float  expToGive;   //与える経験値
    float  exp;         //経験値
    float  needExp;     //必要経験値
    float  maxHp;       //最大HP
    float  prevLv;		//前回のレベル

    bool   isShowBonfireMenu;			//メニューを表示しているか
    bool   isShowLevelUpMenu;			//メニューを表示しているか
    bool   isLvUP;				//レベルアップしたか
    bool   isFinalSelectStatus;	//最終的に選択したステータス
    int    lvUpCount;			//現在のレベルアップ数（今のレベルから前のレベルを引く）
    int	   backGroundImage;		//背景画像ハンドル
    Timer* inputWaitTimer;		//入力待機時間
    int	   statusFontHandle;	//LvUp時メニュー用フォントハンドル
    CrackerParticle* particle;

};