#include "StatusUpParticle.h"
#include"StatusUpParticleBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
StatusUpParticle::StatusUpParticle(const float _prevPlayerLv)
	:hpParticleImage(0)
	,LvUPParticleImage(0)
	,prevPlayerLv(_prevPlayerLv)
	,lvUpFrameCount(0)
	, isDrawLvupParticle(false)
	,targetPos(ORIGIN_POS)
{
	hpParticleImage = LoadGraph("Data/Img/Game/Particle/HP.png");
	LvUPParticleImage = LoadGraph("Data/Img/Game/Particle/LvUP.png");
	textImageHandle = LoadGraph("Data/Img/Game/Particle/LvUPText.png");
	for (int i = 0; i < 25; i++)
	{
		hpParticle.push_back(new StatusUpParticleBase(hpParticleImage));
		lvUpParticle.push_back(new StatusUpParticleBase(LvUPParticleImage));
	}
}
/// <summary>
/// デストラクタ
/// </summary>
StatusUpParticle::~StatusUpParticle()
{

}

void StatusUpParticle::Update(const VECTOR _targetPos, const bool _isBonfireMenu,const float _playerLv)
{
	targetPos = _targetPos;
	if (_isBonfireMenu)
	{
		for (int i = 0; i < hpParticle.size(); i++)
		{
			hpParticle[i]->Update(_targetPos);
		}
	}
	if (_playerLv != prevPlayerLv)
	{
		prevPlayerLv = _playerLv;
		isDrawLvupParticle = true;
	}
	if (isDrawLvupParticle)
	{
		for (int i = 0; i < lvUpParticle.size(); i++)
		{
			lvUpParticle[i]->Update(_targetPos);
		}
		lvUpFrameCount++;
		if (lvUpFrameCount > MAX_FRAME_COUNT)
		{
			isDrawLvupParticle = false;
			lvUpFrameCount = 0;
		}
	}
	
}

void StatusUpParticle::Draw(const bool _isBonfireMenu)
{
	if (_isBonfireMenu)
	{
		for (int i = 0; i < hpParticle.size(); i++)
		{
			hpParticle[i]->Draw();
		}
	}
	if (isDrawLvupParticle)
	{
		for (int i = 0; i < lvUpParticle.size(); i++)
		{
			lvUpParticle[i]->Draw();
		}
		DrawBillboard3D(targetPos, 0.5f, 1.0f, 20.0f, 0.0f, textImageHandle, TRUE);
	}
}