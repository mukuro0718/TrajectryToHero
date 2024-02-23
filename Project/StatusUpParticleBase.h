#pragma once
#include<DxLib.h>
#include"Common.h"
class StatusUpParticleBase
{
public:
	StatusUpParticleBase(const int _imageHandle);//コンストラクタ
	~StatusUpParticleBase();//デストラクタ

	void Init();
	void Update(const VECTOR _targetPos);//更新
	void Draw();//描画
private:
	/*静的定数*/
	static constexpr int SIZE_RANGE = 5;
	static constexpr int SIGN_RANGE = 1;
	static constexpr int POS_RANGE = 10;
	static constexpr int SPEED_RANGE = 5;
	static constexpr int ALPHA_RANGE = 10;
	static constexpr int MAX_ALPHA_VALUE = 200;
	static constexpr int MIN_ALPHA_VALUE = 0;
	/*メンバ変数*/
	int addAlphaValue;
	float size;
	VECTOR targetPos;
	VECTOR offsetPos;//補正座標
	float speed;//速さ
	int alpha;
	int imageHandle;
	int frameCount;
	/*内部処理関数*/
	float ReturnRandomFloatValue(const bool _sign, const int _range);//ランダムでFloat型の値を返す
};

