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
using namespace std;

class Game final
{
public:
	Game();//コンストラクタ
	~Game();//デストラクタ

	void Create();//生成
	void Delete();//削除
	void Update();//更新
	void Draw();//描画
	void OnDamage();//ダメージ判定
	void FixMoveVec();//移動量補正
	void GameEnd(const bool _playerIsDeath_, const bool _bossIsDeath);//ゲーム終了処理
	const bool GetIsGameOver()const { return isGameOver; }//ゲーム終了フラグのgetter
	const bool GetIsGameClear()const { return isGameClear; }
private:
	/*内部処理関数*/
    void Init();                                //初期化
	/*メンバ変数*/
	bool isGameOver;//プレイヤーの死亡
	bool isGameClear;//ボスの死亡
	Camera* camera;//カメラ
	PlayerManager* playerManager;//プレイヤー
	Skydome* skydome;//スカイドーム
	StageManager* stageManager;//ステージ
	StageChanger* stageChanger;//ステージ切り替え
	EnemyManager* enemyManager;//エネミー
	Collision* collision;
	StatusUpParticle* statusUpParticle;
	Meteorite* meteo;
	Explosion* explosion;
	static constexpr DrawRect VICTORY_LOGO_POS = { 200, 200, 1720, 700 };
	int victoryImage;
	int alpha;
	int frameCount;
	bool isFrameCount;
	static constexpr int MAX_FRAME_COUNT = 180;
	static constexpr int MAX_ALPHA_VALUE = 155;
	static constexpr int ADD_ALPHA_VALUE = 5;
	static constexpr int MIN_ALPHA_VALUE = 0;
	static constexpr VECTOR MOVE_RANGE_POS_LTB = {  451,0  ,-840 };//左上下
	static constexpr VECTOR MOVE_RANGE_POS_LBB = { -450,0  ,-840 };//左下下
	static constexpr VECTOR MOVE_RANGE_POS_RTB = {  451,0  , 510 };//右上下
	static constexpr VECTOR MOVE_RANGE_POS_RBB = { -450,0  , 510 };//右下下
	static constexpr VECTOR MOVE_RANGE_POS_LTT = {  451,10 ,-840 };//左上上
	static constexpr VECTOR MOVE_RANGE_POS_LBT = { -450,10 ,-840 };//左下上
	static constexpr VECTOR MOVE_RANGE_POS_RTT = {  451,10 , 510 };//右上上
	static constexpr VECTOR MOVE_RANGE_POS_RBT = { -450,10 , 510 };//右下上
	static const int MOVE_RANGE_COLOR;
	const void DrawMoveRange()const;
	const void DrawYouDied()const;
	int youDiedImage;
	static constexpr DrawRect YOU_DIED_BACKGROUND = { 0, 0, 1920, 1080 };
	static constexpr DrawRect YOU_DIED_LOGO = { 200, 700, 1720, 1000 };
	int youDiedFont;
	int textFont;
	static const int FONT_COLOR;//フォントの色

	static constexpr DrawRect BACKGROUND_POS_FOR_DESCRIPTION = { 1400,30,1910,520 };
	static constexpr VEC2D TEXT_POS_FOR_DESCRIPTION = { 1420,50 };
	int strongUI;
};

