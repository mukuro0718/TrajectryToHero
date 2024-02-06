#pragma once
#include<DxLib.h>
#include<vector>
class FireParticle
{
public:
	FireParticle(const VECTOR _centerPos, const int _particleData);//コンストラクタ
	~FireParticle();//デストラクタ

	void Init();//初期化
	void Update();//更新
	void Draw();//描画

private:
	/*静的定数*/
	static constexpr int SIGN_RANGE = 1;
	static constexpr int X_POS_RANGE = 5;
	static constexpr int Z_POS_RANGE = 5;
	static constexpr int SPEED_RANGE = 2;
	static constexpr float SIZE_REDUCED_VALUE = 0.4f;
	static constexpr int ALPHA_RANGE = 255; 
	static constexpr int ALPHA_MAX_VALUE = 255;
	static constexpr int ALPHA_REDUCED_VALUE = 10;

	static constexpr float CX = 0.5;
	static constexpr float CY = 0.5f;
	static constexpr float ANGLE = 0.0f;
	/*メンバ変数*/
	VECTOR centerPos;//中心座標
	VECTOR pos;//座標
	float  size;//サイズ
	float  speed;//速さ
	bool   isDraw;//描画するか
	int alpha;
    int particleData;
	float ReturnRandomFloat(const bool _useSign, const int _range);
};

