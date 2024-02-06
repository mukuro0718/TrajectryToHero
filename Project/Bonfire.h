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
	void Draw();//描画

	const VECTOR GetPos() const { return POS; }
private:
	/*静的定数*/
	static constexpr int FIRE_PARTICLE_NUM = 150;
	static const VECTOR POS;//座標
	static const VECTOR SCALE;//拡大率
	static const VECTOR ROTATE;//回転率
	//メンバ変数
	enum class DataType
	{
		BONFIRE_MODEL,
		FLAME,
	};
	int modelHandle;
	std::vector<int> particleData;
	std::vector<int> bonfireData;
	std::vector<FireParticle*> fire;
};

