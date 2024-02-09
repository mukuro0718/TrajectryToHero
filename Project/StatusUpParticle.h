#pragma once
#include<DxLib.h>
#include<vector>
class StatusUpParticleBase;
class StatusUpParticle
{
public:
	StatusUpParticle();//コンストラクタ
	~StatusUpParticle();//デストラクタ

	//void Update(const VECTOR _targetPos,const int _atkUpCount, const int _agiUpCount, const int _defUpCount);//更新
	void Update(const VECTOR _targetPos,const bool _isBonfireMenu);//更新

	//void Draw();//描画
	void Draw(const bool _isBonfireMenu);//描画

private:
	/*静的定数*/
	static const int COLOR_RED;
	static const int COLOR_BLUE;
	static const int COLOR_YELLOW;
	static const int COLOR_GREEN;
	int redNum;
	int blueNum;
	int yellowNum;
	/*メンバ変数*/

	std::vector<StatusUpParticleBase*> particle;
};

