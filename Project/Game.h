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
	const bool GetIsEndgame() { return isEndGame; }//ゲーム終了フラグのgetter
private:
	/*内部処理関数*/
    void Init();                                //初期化
	/*メンバ変数*/
	bool isEndGame;//ゲームが終了したか
	Camera* camera;//カメラ
	PlayerManager* playerManager;//プレイヤー
	Skydome* skydome;//スカイドーム
	StageManager* stageManager;//ステージ
	StageChanger* stageChanger;//ステージ切り替え
	EnemyManager* enemyManager;//エネミー
};

