#include "Skydome.h"
#include"Load.h"

const VECTOR Skydome::SCALE = VGet(1.5f,1.5f,1.5f);

/// <summary>
/// コンストラクタ
/// </summary>
Skydome::Skydome()
{
	Init();
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
void Skydome::Init()
{
	pos = ORIGIN_POS;
	modelHandle = 0;
	auto& load = Load::GetInstance();
	load.GetSkydomeData(&modelHandle);
	MV1SetPosition(modelHandle, pos);
	MV1SetScale(modelHandle,SCALE);
}
/// <summary>
/// 描画
/// </summary>
void Skydome::Draw()
{
	MV1DrawModel(modelHandle);
}