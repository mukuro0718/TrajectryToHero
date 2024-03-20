//======================================================
// @brief かがり火クラス
//======================================================
#pragma once
#include<DxLib.h>
#include<vector>
class FireParticle;
class Bonfire
{
public:
	Bonfire();//コンストラクタ
	~Bonfire();//デストラクタ

	const void Draw();//描画
	/*getter*/
	const VECTOR GetPos() const { return POS; }
private:
	/*構造体・列挙体*/
	enum class DataType
	{
		BONFIRE_MODEL,
		FLAME,
	};
	/*静的定数*/
	static constexpr int FIRE_PARTICLE_NUM = 150;//パーティクル数
	
	static const VECTOR POS;	//座標
	static const VECTOR SCALE;	//拡大率
	static const VECTOR ROTATE;	//回転率
	/*メンバ変数*/
	std::vector<FireParticle*> fire;//パーティクル

	std::vector<int> particleData;	//パーティクルデータ
	std::vector<int> bonfireData;	//焚火データ

	int modelHandle;//モデルハンドル
};

