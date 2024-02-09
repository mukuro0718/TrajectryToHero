#include "StatusUpParticle.h"
#include"StatusUpParticleBase.h"

const int StatusUpParticle::COLOR_RED = GetColor(150,50,50);
const int StatusUpParticle::COLOR_BLUE = GetColor(50, 50, 150);
const int StatusUpParticle::COLOR_YELLOW = GetColor(150, 150, 50);
const int StatusUpParticle::COLOR_GREEN = GetColor(50, 150, 50);

/// <summary>
/// コンストラクタ
/// </summary>
StatusUpParticle::StatusUpParticle()
	:redNum(0)
	,blueNum(0)
	,yellowNum(0)
{
	for (int i = 0; i < 50; i++)
	{
		particle.push_back(new StatusUpParticleBase(COLOR_GREEN));
	}
}
/// <summary>
/// デストラクタ
/// </summary>
StatusUpParticle::~StatusUpParticle()
{

}
/// <summary>
/// 更新
/// </summary>
//void StatusUpParticle::Update(const VECTOR _targetPos,const int _atkUpCount, const int _agiUpCount, const int _defUpCount)
//{
//	for (int i = 0; i < (_atkUpCount - redNum) * 5; i++)
//	{
//		particle.push_back(new StatusUpParticleBase(COLOR_RED));
//	}
//	for (int i = 0; i < (_agiUpCount - blueNum) *5; i++)
//	{
//		particle.push_back(new StatusUpParticleBase(COLOR_BLUE));
//	}
//	for (int i = 0; i < (_defUpCount - yellowNum) *5; i++)
//	{
//		particle.push_back(new StatusUpParticleBase(COLOR_YELLOW));
//	}
//
//	redNum = _atkUpCount;
//	blueNum = _agiUpCount;
//	yellowNum = _defUpCount;
//
//	for (int i = 0; i < particle.size(); i++)
//	{
//		particle[i]->Update(_targetPos);
//	}
//}
void StatusUpParticle::Update(const VECTOR _targetPos, const bool _isBonfireMenu)
{
	if (_isBonfireMenu)
	{
		for (int i = 0; i < particle.size(); i++)
		{
			particle[i]->Update(_targetPos);
		}
	}
}

/// <summary>
/// 描画
/// </summary>
//void StatusUpParticle::Draw()
//{
//	for (int i = 0; i < particle.size(); i++)
//	{
//		particle[i]->Draw();
//	}
//}
void StatusUpParticle::Draw(const bool _isBonfireMenu)
{
	if (_isBonfireMenu)
	{
		for (int i = 0; i < particle.size(); i++)
		{
			particle[i]->Draw();
		}
	}
}