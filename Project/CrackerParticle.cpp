#include "CrackerParticle.h"
#include "CrackerParticleBase.h"

const int CrackerParticle::COLOR_RED = GetColor(150, 50, 50);
const int CrackerParticle::COLOR_BLUE = GetColor(50, 50, 150);
const int CrackerParticle::COLOR_YELLOW = GetColor(150, 150, 50);

CrackerParticle::CrackerParticle()
{
	for (int i = 0; i < MAX_RED_PARTICLE_NUM; i++)
	{
		redParticle.push_back(new CrackerParticleBase(COLOR_RED));
	}
	for (int i = 0; i < MAX_BLUE_PARTICLE_NUM; i++)
	{
		blueParticle.push_back(new CrackerParticleBase(COLOR_BLUE));
	}
	for (int i = 0; i < MAX_YELLOW_PARTICLE_NUM; i++)
	{
		yellowParticle.push_back(new CrackerParticleBase(COLOR_YELLOW));
	}
}
const void CrackerParticle::Init(const bool _isDrawRed, const bool _isDrawBlue, const bool _isDrawYellow)
{
	if (_isDrawRed)
	{
		for (int i = 0; i < MAX_RED_PARTICLE_NUM; i++)
		{
			redParticle[i]->Init(INIT_POS);
		}
	}
	if (_isDrawBlue)
	{
		for (int i = 0; i < MAX_RED_PARTICLE_NUM; i++)
		{
			blueParticle[i]->Init(INIT_POS);
		}
	}
	if (_isDrawYellow)
	{
		for (int i = 0; i < MAX_RED_PARTICLE_NUM; i++)
		{
			yellowParticle[i]->Init(INIT_POS);
		}
	}
}
CrackerParticle::~CrackerParticle()
{
	redParticle.clear();
	blueParticle.clear();
	yellowParticle.clear();
}

const void CrackerParticle::Update()
{
	for (int i = 0; i < MAX_RED_PARTICLE_NUM; i++)
	{
		redParticle[i]->Update();
	}
	for (int i = 0; i < MAX_BLUE_PARTICLE_NUM; i++)
	{
		blueParticle[i]->Update();
	}
	for (int i = 0; i < MAX_YELLOW_PARTICLE_NUM; i++)
	{
		yellowParticle[i]->Update();
	}
}
const void CrackerParticle::Draw()
{
	for (int i = 0; i < MAX_RED_PARTICLE_NUM; i++)
	{
		redParticle[i]->Draw();
	}
	for (int i = 0; i < MAX_BLUE_PARTICLE_NUM; i++)
	{
		blueParticle[i]->Draw();
	}
	for (int i = 0; i < MAX_YELLOW_PARTICLE_NUM; i++)
	{
		yellowParticle[i]->Draw();
	}
}
const void CrackerParticle::OffIsDraw()
{
	for (int i = 0; i < MAX_RED_PARTICLE_NUM; i++)
	{
		redParticle[i]->OffIsDraw();
	}
	for (int i = 0; i < MAX_BLUE_PARTICLE_NUM; i++)
	{
		blueParticle[i]->OffIsDraw();
	}
	for (int i = 0; i < MAX_YELLOW_PARTICLE_NUM; i++)
	{
		yellowParticle[i]->OffIsDraw();
	}
}