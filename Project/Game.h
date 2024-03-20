//===========================================================================
//@brief ゲームシーンクラス
// ゲームシーンの処理を行う
//===========================================================================
#pragma once
#include"DxLib.h"
#include"Common.h"
class Camera;
class PlayerManager;
class Skydome;
class StageManager;
class StageChanger;
class EnemyManager;
class Collision;
class StatusUpParticle;
class Meteorite;
class Explosion;
class LightSword;



using namespace std;
class Game final
{
public:
	Game();//コンストラクタ
	~Game();//デストラクタ

	const void Create();	//生成
	const void Delete();	//削除
	const void Update();	//更新
	const void Draw();		//描画
	const void OnDamage();	//ダメージ判定
	const void FixMoveVec();//移動量補正

	const void GameEnd(const bool _playerIsDeath_, const bool _bossIsDeath);//ゲーム終了処理
	
	/*getter*/
	const bool GetIsGameOver()const { return isGameOver; }	//ゲーム終了フラグのgetter
	const bool GetIsGameClear()const { return isGameClear; }
private:
	/*静的定数*/
	static constexpr DrawRect VICTORY_LOGO_POS				 = { 200, 200, 1720, 700 };	//勝利ロゴ背景
	static constexpr DrawRect YOU_DIED_BACKGROUND			 = { 0, 0, 1920, 1080 };	//死亡ロゴ背景座標
	static constexpr DrawRect YOU_DIED_LOGO					 = { 200, 700, 1720, 1000 };//死亡ロゴ座標
	static constexpr DrawRect BACKGROUND_POS_FOR_DESCRIPTION = { 1400,30,1910,520 };	//排撃座標
	static constexpr VECTOR	  MOVE_RANGE_POS_LBB			 = { -450,0  ,-840 };		//左下下
	static constexpr VECTOR   MOVE_RANGE_POS_RTB			 = {  451,0  , 510 };		//右上下
	static constexpr VECTOR   MOVE_RANGE_POS_RBB			 = { -450,0  , 510 };		//右下下
	static constexpr VECTOR   MOVE_RANGE_POS_LTT			 = {  451,10 ,-840 };		//左上上
	static constexpr VECTOR   MOVE_RANGE_POS_LBT			 = { -450,10 ,-840 };		//左下上
	static constexpr VECTOR   MOVE_RANGE_POS_RTT			 = {  451,10 , 510 };		//右上上
	static constexpr VECTOR   MOVE_RANGE_POS_RBT			 = { -450,10 , 510 };		//右下上
	static constexpr VECTOR   MOVE_RANGE_POS_LTB			 = {  451,0  ,-840 };		//左上下
	static constexpr VEC2D    TEXT_POS_FOR_DESCRIPTION		 = { 1420,50 };				//テキスト座標
	static constexpr int	  MAX_FRAME_COUNT				 = 180;						//最大フレーム
	static constexpr int	  MAX_ALPHA_VALUE				 = 155;						//最大アルファ
	static constexpr int	  ADD_ALPHA_VALUE				 = 5;						//追加アルファ
	static constexpr int	  MIN_ALPHA_VALUE				 = 0;						//最小アルファ

	static const	 int	  MOVE_RANGE_COLOR;	//移動範囲表示カラー
	static const	 int	  FONT_COLOR;		//フォントの色

	/*内部処理関数*/
    const void Init();	//初期化
	const void DrawMoveRange()const;

	/*メンバ変数*/
	StatusUpParticle*	statusUpParticle;	//ステータス関連のパーティクル
	PlayerManager*		playerManager;		//プレイヤー
	StageManager*		stageManager;		//ステージ
	StageChanger*		stageChanger;		//ステージ切り替え
	EnemyManager*		enemyManager;		//エネミー
	LightSword*			lightSword;			//光の剣
	Collision*			collision;			//コリジョン
	Meteorite*			meteo;				//隕石
	Explosion*			explosion;			//爆発
	Skydome*			skydome;			//スカイドーム
	Camera*				camera;				//カメラ

	bool isGameOver;	//プレイヤーの死亡
	bool isGameClear;	//ボスの死亡
	bool isFrameCount;	//フレームカウントを行うか
	int  victoryImage;	//勝利画像
	int  alpha;			//アルファ
	int  frameCount;	//フレームカウント
	int  youDiedImage;	//死亡画像
	int  youDiedFont;	//死亡フォント
	int  textFont;		//テキスト
	int  strongUI;		//強敵マーク画像
};

