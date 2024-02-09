#pragma once
#include<DxLib.h>
class StatusUpParticleBase
{
public:
	StatusUpParticleBase(const int _color);//コンストラクタ
	~StatusUpParticleBase();//デストラクタ

	void Init();
	void Update(const VECTOR _targetPos);//更新
	void Draw();//描画
private:
	/*静的定数*/
	static constexpr int SIZE_RANGE = 5;
	static constexpr int SIGN_RANGE = 1;
	static constexpr int POS_RANGE = 10;
	static constexpr int SPEED_RANGE = 9;
	static constexpr int MAX_ALPHA_VALUE = 200;
	static constexpr int MIN_ALPHA_VALUE = 0;
	static constexpr int ADD_ALPHA_VALUE = 5;
	/*メンバ変数*/
	VECTOR topPos;//上座標
	VECTOR underPos;//した座標
	VECTOR offsetPos;//補正座標
	float size;//サイズ
	float speed;//速さ
	int color;
	int alpha;
	/*内部処理関数*/
	float ReturnRandomFloatValue(const bool _sign, const int _range);//ランダムでFloat型の値を返す
};

