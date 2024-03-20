//===========================================================================
//@brief ステージ切り替えクラス
//===========================================================================
#pragma once
#include"DxLib.h"
#include"Common.h"
#include<vector>

class Timer;
using namespace std;
class StageChanger
{
public:
    StageChanger();             //コンストラクタ
    ~StageChanger();            //デストラクタ

    const void Init();                          //初期化
    const void Delete();                        //削除
    const void Draw();                          //描画
    const void ChangeStage();                   //ステージの変更
    const void DrawGameClear();                 //ゲームクリアの画像の表示
    const void DrawImageWhenSwitchingStage();   //ウェーブ開始時の画像の表示
    const bool DrawAlert(const VECTOR _playerPos, const VECTOR _gatePos, const bool _isShowGate);//farm_bossのステージ移動を行うかどうか
    /*getter*/
    //ステージ切り替えフラグ（切り替えが終わっているかどうかを管理）
    const bool GetIsChangeStage()const { return isChangeStage; }
    //ファームステージフラグのgetter/setter
    const bool GetIsFarm()const { return isFarm; }
    //ボスステージフラグのgetter/setter
    const bool GetIsBoss()const{return isBoss; }
    //ゲームオーバーフラグのgetter/setter
    const bool GetIsGameOver()const { return isGameOver; }
    //ゲームクリアフラグのgetter/setter
    const bool GetIsGameClear()const { return isGameClear; }
    //ゲームオーバーフラグのgetter/setter
    const bool GetIsGameEnd()const { return isGameEnd; }
    //警告フラグのgetter/setter
    const bool GetIsAlert()const { return isDrawAlert; }
private:
    /*構造体・列挙体*/
    enum class ImageType
    {
        FARM_STAGE, //ファームステージ
        BOSS_STAGE,	//ボスステージ
        ALERT,      //画面暗転用
    };
    /*静的定数*/
    static constexpr DrawRect   BOSS_UI_DRAW_RECT   = { 1120,660,1320,700 };//移動UI描画範囲
    static constexpr float      IMG_ANGLE           = 0.0f;                 //画像アングル
    static constexpr float      SET_GAMEOVER_TIMER  = 10.0f;                //タイマー目標時間
    static constexpr float      SET_STAY_TIMER      = 10.0f;                //タイマー目標時間
    static constexpr int        IMG_SIZE            = 60;                   //画像サイズ
    static constexpr int        IMAGE_NUM           = 3;                    //総画像数
    static constexpr int        VERTEX_POS_NUM      = 4;	                //頂点座標数

    static const VERTEX3D INIT_VERTEX;		//初期頂点情報
    static const COLOR_U8 TRAIL_COLOR;		//軌跡の色
    static const VECTOR DRAW_GATEIMAGE_POS; //ゲートの描画位置
    static const VECTOR VERTEX_NORM;		//法線ベクトル

    /*メンバ変数*/
    Timer* stayMaxAlphaTimer;//アルファ値が最大の時に描画する時間
    
    std::vector<VERTEX3D>   vertexInfo;	    //頂点座標
    std::vector<WORD>       vertexIndexAd;  //頂点インデックス
    std::vector<int>        image;          //画像ハンドル

    VEC2D DrawImagePos;     //画像描画位置
    float gateImageAngle;   //ゲート画像の回転角度
    bool  isFarm;           //ファームステージ
    bool  isBoss;           //ボスステージ
    bool  isChangeStage;    //ステージ切り替えフラグ
    bool  isGameOver;       //ゲームオーバーフラグ
    bool  isGameClear;      //ゲームクリアフラグ
    bool  isGameEnd;        //ゲーム終了フラグ
    bool  isDrawBlackBack;  //黒背景描画フラグ
    bool  isDrawAlert;      //警告描画フラグ(true:描画している false:描画していない)
    int   gateImage;        //ゲート画像
    int   alpha;            //アルファ値
    int   backGroundAlpha;  //背景アルファ値
    int   alphaValue;       //増加量

};