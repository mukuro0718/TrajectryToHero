#include "Meteorite.h"
#include"MeteoriteBase.h"
/// <summary>
/// コンストラクタ
/// </summary>
Meteorite::Meteorite()
	:isInit(false)
	, isDraw(false)
{
	for (int i = 0; i < METEO_NUM; i++)
	{
		base.push_back(new MeteoriteBase());
	}
	
}
/// <summary>
/// デストラクタ
/// </summary>
Meteorite::~Meteorite()
{
	for (int i = 0; i < METEO_NUM; i++)
	{
		delete(base[i]);
		base[i] = nullptr;
	}
	base.clear();
}
/// <summary>
/// 更新
/// </summary>
void Meteorite::Update(const bool _isMeteo)
{
	isDraw = _isMeteo;
	if (isDraw)
	{
		isInit = false;
		for (int i = 0; i < base.size(); i++)
		{
			base[i]->Update();
		}
	}
	else
	{
		if (!isInit)
		{
			isInit = true;
			for (int i = 0; i < base.size(); i++)
			{
				base[i]->Init();
			}
		}
		
	}
	
}
/// <summary>
/// 更新
/// </summary>
void Meteorite::Draw(const int _stageModelHandle)
{
	if (isDraw)
	{
		for (int i = 0; i < base.size(); i++)
		{
			base[i]->Draw(_stageModelHandle);
		}
	}
}

const SphereInfo Meteorite::GetSphereInfo(const int _meteoNum) 
{ 
	return base[_meteoNum]->GetSphereInfo();
}