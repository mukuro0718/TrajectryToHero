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
void StrongerUI::Update(const VECTOR _enemyPos)
{
	pos = _enemyPos;
	pos.y += 40.0f;
}
const void StrongerUI::Draw(const float playerLv,const float enemyLv) const
{
	if (enemyLv > playerLv)
	{
		DrawBillboard3D(pos, 0.5f, 0.5f, size, angle, imageHandle, TRUE);
	}
}