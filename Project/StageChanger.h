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

    void Init();//初期化
    void Delete();//削除
    void DrawImageWhenSwitchingStage();//ウェーブ開始時の画像の表示
    void DrawGameClear();//ゲームクリアの画像の表示
    void Draw();
    bool DrawAlert(const VECTOR _playerPos, const VECTOR _gatePos, const bool _isShowGate);//farm_bossのステージ移動を行うかどうか

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
    const void ChangeStage();
private:
    //定数
    enum class ImageType
    {
        FARM_STAGE, //ファームステージ
        BOSS_STAGE,	//ボスステージ
        ALERT, //画面暗転用
    };
    static constexpr int   IMG_SIZE             = 60;       //画像サイズ
    static constexpr int   IMAGE_NUM            = 3;        //総画像数
    static constexpr float IMG_ANGLE            = 0.0f;     //画像アングル
    static constexpr float SET_GAMEOVER_TIMER   = 10.0f;    //タイマー目標時間
    static constexpr float SET_STAY_TIMER       = 10.0f;    //タイマー目標時間
    static const VECTOR DRAW_GATEIMAGE_POS;
    static const VERTEX3D INIT_VERTEX;			//初期頂点情報
    static const VECTOR VERTEX_NORM;			//法線ベクトル
    static const COLOR_U8 TRAIL_COLOR;			//軌跡の色
    static constexpr int VERTEX_POS_NUM = 4;	//頂点座標数

    //クラス・構造体
    Timer* StayMaxAlphaTimer;//アルファ値が最大の時に描画する時間
    VEC2D DrawImagePos;
    //変数
    std::vector<VERTEX3D> vertexInfo;		//頂点座標
    std::vector<WORD> vertexIndexAd;

    vector<int> image;      //画像ハンドル
    int gateImage;          //ゲート画像
    int  alpha;             //アルファ値
    int  backGroundAlpha;   //背景アルファ値
    int  alphaValue;        //増加量
    float gateImageAngle;   //ゲート画像の回転角度
    bool isFarm;            //ファームステージ
    bool isBoss;            //ボスステージ
    bool isChangeStage;     //ステージ切り替えフラグ
    bool isGameOver;        //ゲームオーバーフラグ
    bool isGameClear;       //ゲームクリアフラグ
    bool isGameEnd;         //ゲーム終了フラグ
    bool isDrawBlackBack;   //黒背景描画フラグ
    bool isDrawAlert;       //警告描画フラグ(true:描画している false:描画していない)
    static constexpr DrawRect BOSS_UI_DRAW_RECT = { 1120,660,1320,700 };//移動UI描画範囲

};