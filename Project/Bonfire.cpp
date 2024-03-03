#include "Bonfire.h"
#include "FireParticle.h"
#include "Load.h"
const VECTOR Bonfire::POS = VGet(0.0f,5.0f,-50.0f);
const VECTOR Bonfire::SCALE = VGet(0.3f,0.3f,0.3f);
const VECTOR Bonfire::ROTATE = VGet(0.0f, 0.0f, 0.0f);

/// <summary>
/// コンストラクタ
/// </summary>
Bonfire::Bonfire()
	:modelHandle(0)
{
	auto& load = Load::GetInstance();
	load.GetBonfireData(&bonfireData);

	modelHandle = bonfireData[static_cast<int>(DataType::BONFIRE_MODEL)];
	MV1SetPosition(modelHandle, POS);
	//サイズの設定
	MV1SetScale(modelHandle, SCALE);
	//回転率の設定
	MV1SetRotationXYZ(modelHandle, ROTATE);
	for (int i = 0; i < FIRE_PARTICLE_NUM; i++)
	{
		fire.push_back(new FireParticle(POS, bonfireData[static_cast<int>(DataType::FLAME)]));
	}
}
/// <summary>
/// デストラクタ
/// </summary>
Bonfire::~Bonfire()
{

}
/// <summary>
/// 描画
/// </summary>
void Bonfire::Draw()
{
	MV1DrawModel(modelHandle);
	for (int i = 0; i < FIRE_PARTICLE_NUM; i++)
	{
		fire[i]->Update();
		fire[i]->Draw();
	}
}