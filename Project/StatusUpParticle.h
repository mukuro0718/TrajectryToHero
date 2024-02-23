#pragma once
#include<DxLib.h>
#include<vector>
class StatusUpParticleBase;
class StatusUpParticle
{
public:
	StatusUpParticle(const float _prevPlayerLv);//コンストラクタ
	~StatusUpParticle();//デストラクタ

	//void Update(const VECTOR _targetPos,const int _atkUpCount, const int _agiUpCount, const int _defUpCount);//更新
	void Update(const VECTOR _targetPos,const bool _isBonfireMenu, const float _playerLv);//更新

	//void Draw();//描画
	void Draw(const bool _isBonfireMenu);//描画

private:
	/*静的定数*/
	static constexpr int MAX_FRAME_COUNT = 60;
	/*メンバ変数*/
	int hpParticleImage;
	int LvUPParticleImage;
	float prevPlayerLv;
	int lvUpFrameCount;
	bool isDrawLvupParticle;
	int textImageHandle;
	VECTOR targetPos;
	std::vector<StatusUpParticleBase*> hpParticle;
	std::vector<StatusUpParticleBase*> lvUpParticle;
};

