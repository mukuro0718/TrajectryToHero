//===============================================
// 隕石マネージャークラス
//===============================================
#pragma once
#include<DxLib.h>
#include<vector>
#include "Common.h"
class MeteoriteBase;
class Meteorite
{
public:
	Meteorite();
	~Meteorite();
	void Update(const bool _isMeteo);
	void Draw(const int _stageModelHandle);
	const int GetMeteoNum() { return METEO_NUM; }
	const SphereInfo  GetSphereInfo(const int _meteoNum);
private:
	static constexpr int METEO_NUM = 20;
	std::vector<MeteoriteBase*> base;
	bool isInit;//初期化を行ったかどうか
	bool isDraw;//描画しているか
};

