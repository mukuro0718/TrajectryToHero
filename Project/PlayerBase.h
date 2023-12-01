//===========================================================================
//@brief プレイヤーベースクラス
//モデルの描画とコピーしたモデルのアンロードを行う
//===========================================================================
#pragma once
#include"DxLib.h"
#include"CharacterBase.h"
class StatusManager;
class EffectManager;
class CharacterStatus;

class PlayerBase :public CharacterBase
{
public:
	PlayerBase(){};						//コンストラクタ
	PlayerBase(const int _modelHandle);	// 引数ありコンストラクタ
	virtual ~PlayerBase();				// デストラクタ
	void Draw();						//描画
	void Delete();						//削除
	//仮想関数（継承先で実装）
	virtual void Update() = 0;			//更新
	virtual void Init() = 0;			//初期化

	bool IsStoppingUpdate();

protected:
	/*静的定数*/
	static constexpr float WALK_SPEED = 5.0f;	//歩く速さ
	/*メンバ変数*/
	CharacterStatus* status;			//ステータス
	VECTOR cameraToPlayer;
private:
	/*メンバ変数*/
	static constexpr float CAPSULE_HEIGHT = 30.0f;
	static constexpr float CAPSULE_RADIUS = 10.0f;
	static const	 int   CAPSULE_COLOR;
	static constexpr float SPHERE_RADIUS = 3.0f;
	static const int SPHERE_COLOR;
};

