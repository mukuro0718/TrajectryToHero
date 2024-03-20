#include "Skydome.h"
#include"Load.h"
#include"Common.h"
#include "BloomEffect.h"
const VECTOR Skydome::SCALE[] =
{
	VGet(1.5f, 1.5f, 1.5f),
	VGet(1.5f, 1.5f, 1.5f),
};
const VECTOR Skydome::ADD_ROTATE[] =
{
	VGet(0.0f, 0.0f , 0.0f),
	VGet(0.0f, 0.001f, 0.0f),
};
/// <summary>
/// コンストラクタ
/// </summary>
Skydome::Skydome()
	: bloom(nullptr)
{
	bloom = new BloomEffect();
	Init();
	bloom->MakeBloomScreen();
}
/// <summary>
/// デストラクタ
/// </summary>
Skydome::~Skydome()
{

}
/// <summary>
/// 初期化
/// </summary>
const void Skydome::Init()
{
	pos = ORIGIN_POS;
	auto& load = Load::GetInstance();
	load.GetSkydomeData(&modelHandle);
	for (int i = 0; i < MODEL_NUM; i++)
	{
		MV1SetPosition(modelHandle[i], pos);
		MV1SetScale(modelHandle[i], SCALE[i]);
	}
}
/// <summary>
/// 描画
/// </summary>
const void Skydome::Draw()
{
	for (int i = 0; i < MODEL_NUM; i++)
	{
		rotate[i] = VAdd(rotate[i], ADD_ROTATE[i]);
		MV1SetRotationXYZ(modelHandle[i],rotate[i]);
	}

	MV1DrawModel(modelHandle[0]);
	bloom->GetImage();
	MV1DrawModel(modelHandle[1]);

}
const void Skydome::SetDrawScreenType(const float _angleX)
{
	bloom->SetDrawScreenType();
	// 画面をクリア
	ClearDrawScreen();
	
}
const void Skydome::BloomProg()
{

	bloom->DrawNormalGraph();
	bloom->DrawGaussBlendGraph();
}
