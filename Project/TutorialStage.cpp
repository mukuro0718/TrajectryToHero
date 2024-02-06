#include "TutorialStage.h"
#include"FireParticle.h"
#include"Common.h"

const VECTOR TutorialStage::SCALE = VGet(0.3f, 0.3f, 0.3f);
const VECTOR TutorialStage::INIT_STAGE_POS = VGet(0.0f, 0.0f, -150.0f);


TutorialStage::TutorialStage(const std::vector<int> _data)
	:isShowGate(false)
	,portalRotate(0.0f)
{
	for (int i = 0; i < MAX_DATA_NUM; i++)
	{
		data.push_back(_data[i]);
	}
	for (int i = 0; i < MAX_DATA_NUM; i++)
	{
		pos.push_back(INIT_STAGE_POS);
		scale.push_back(SCALE);
	}
	scale[static_cast<int>(DataType::SKYDOME)] = VGet(1.0f, 1.0f, 1.0f);
	//座標のセット
	pos[static_cast<int>(DataType::GATE)] = VGet(0.0f, -20.0f, -500.0f);
	pos[static_cast<int>(DataType::PORTAL)] = VGet(0.0f, 40.0f, -450.0f);
	pos[static_cast<int>(DataType::BONFIRE)] = VGet(0.0f, 5.0f, -300.0f);
	for (int i = 0; i < MODEL_DATA_NUM; i++)
	{
		MV1SetPosition(data[i], pos[i]);
		MV1SetScale(data[i], scale[i]);
	}
	fireData.push_back(data[static_cast<int>(DataType::FLAME)]);
	for (int i = 0; i < FIRE_PARTICLE_NUM; i++)
	{
		fire.push_back(new FireParticle(pos[static_cast<int>(DataType::BONFIRE)], data[static_cast<int>(DataType::FLAME)]));
	}
}
TutorialStage::~TutorialStage()
{
	Delete();
}
/// <summary>
/// 最終処理
/// </summary>
void TutorialStage::Delete()
{
	data.clear();
	pos.clear();
	pos.clear();
}

void TutorialStage::Update()
{
	portalRotate += 1.0f;
	
	MV1SetRotationXYZ(data[static_cast<int>(DataType::PORTAL)], VGet(0.0f, 0.0f, portalRotate * (DX_PI_F / 180.0f)));

}
void TutorialStage::Draw()
{
	MV1DrawModel(data[static_cast<int>(DataType::SKYDOME)]);
	MV1DrawModel(data[static_cast<int>(DataType::BONFIRE)]);
	MV1DrawModel(data[static_cast<int>(DataType::STAGE)]);
	for (int i = 0; i < FIRE_PARTICLE_NUM; i++)
	{
		fire[i]->Update();
		fire[i]->Draw();
	}
	if (isShowGate)
	{
		MV1DrawModel(data[static_cast<int>(DataType::GATE)]);
		MV1DrawModel(data[static_cast<int>(DataType::PORTAL)]);
	}
}
