#pragma once
#include<DxLib.h>
#include "Common.h"
class Explosion
{
public:
	Explosion();//コンストラクタ
	~Explosion();//デストラクタ
	void Init();//初期化
	void Update(const bool _isDraw, const VECTOR _targetPos);//更新
	void Draw();//描画
	const SphereInfo GetSphereInfo() { return sphereInfo; }
private:
	/*静的定数*/
	static constexpr float MAX_RADIUS_RANGE = 100.0f;//最大半径範囲
	static constexpr float MIN_RADIUS_RANGE = 0.0f;//最小半径範囲
	static constexpr float ADD_RADIUS_VALUE = 0.25f;//半径増加量
	static constexpr int MAX_ALPHA_VALUE = 255;//最大アルファ値
	static constexpr int MIN_ALPHA_VALUE = 0;//最小アルファ値
	static constexpr int ADD_ALPHA_VALUE = 5;//アルファ増加量
	static constexpr int DIV_NUM = 16;//球の分割数
	static constexpr bool FILL_FLAG = true;//描画する球を塗りつぶすかどうか
	static const int COLOR;
	/*メンバ変数*/
	SphereInfo sphereInfo;
	int alpha;//アルファ値
	bool isDraw;//描画しているか
	bool isInit;//初期化したか
};

