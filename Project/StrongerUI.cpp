#include "StrongerUI.h"
#include"Common.h"
#include"Load.h"
StrongerUI::StrongerUI()
	:pos(ORIGIN_POS)
	,size(5.0f)
	,angle(0.0f)
	,imageHandle(0)
{
	auto& load = Load::GetInstance();
	load.GetStrongerUIData(&imageHandle);
}
StrongerUI::~StrongerUI()
{

}
const void StrongerUI::Update(const VECTOR _enemyPos, const int _modelHandle,const int _frameNum)
{
	pos = MV1GetFramePosition(_modelHandle,_frameNum);
	pos.y += 5.0f;
}
const void StrongerUI::Draw(const float _playerLv,const float _enemyLv) const
{
	if (_enemyLv > _playerLv)
	{
		DrawBillboard3D(pos, 0.5f, 0.5f, size, angle, imageHandle, TRUE);
	}
}