//===========================================================================
//@brief ゲームシーンクラス
// ゲームシーンの処理を行う
//===========================================================================
#pragma once
#include"DxLib.h"
class Camera;
class PlayerManager;
class Skydome;
class StageManager;
class StageChanger;
class EnemyManager;
class Collision;

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
	void GameEnd(const bool _playerIsDeath/*,const float _bossHP*/);//ゲーム終了処理
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
};

