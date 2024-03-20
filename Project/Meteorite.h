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
	Meteorite();	//コンストラクタ
	~Meteorite();	//デストラクタ

	const void Update(const bool _isMeteo);			//更新
	const void Draw(const int _stageModelHandle);	//描画
	/*getter*/
	const int GetMeteoNum() { return METEO_NUM; }
	const SphereInfo  GetSphereInfo(const int _meteoNum);
private:
	/*静的定数*/
	static constexpr int METEO_NUM = 20;

	/*メンバ変数*/
	std::vector<MeteoriteBase*> base;	//隕石ベース
	
	bool isInit;//初期化を行ったかどうか
	bool isDraw;//描画しているか
};

