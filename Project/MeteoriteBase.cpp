#include "MeteoriteBase.h"
#include "Shadow.h"
const int MeteoriteBase::COLOR = GetColor(100,10,10);
/// <summary>
/// コンストラクタ
/// </summary>
MeteoriteBase::MeteoriteBase()
	:speed(0.0f)
	, shadow(nullptr)
{
	Init();
	shadow = new Shadow();
}
/// <summary>
/// デストラクタ
/// </summary>
MeteoriteBase::~MeteoriteBase()
{

}
/// <summary>
/// 初期化
/// </summary>
void MeteoriteBase::Init()
{
	//中心座標をランダムで出す
	VECTOR centerPos = ORIGIN_POS;
	if (GetRand(1) == 0)
	{
		centerPos.x = static_cast<float>(GetRand(static_cast<int>(POS_RANGE.x)));
	}
	else
	{
		centerPos.x = -static_cast<float>(GetRand(static_cast<int>(POS_RANGE.x)));
	}
		centerPos.y = static_cast<float>(GetRand(static_cast<int>(POS_RANGE.y)));
	if (GetRand(1) == 0)
	{
		centerPos.z = static_cast<float>(GetRand(static_cast<int>(POS_RANGE.z)));
	}
	else
	{
		centerPos.z = -static_cast<float>(GetRand(static_cast<int>(POS_RANGE.z)));
	}
	sphereInfo.centerPos = VAdd(centerPos,POS_OFFSET);
	sphereInfo.radius	 = RADIUS;
	sphereInfo.divNum	 = DIV_NUM;
	sphereInfo.difColor  = COLOR;
	sphereInfo.spcColor  = COLOR;
	sphereInfo.fillFlag  = FILL_FLAG;
	speed = static_cast<float>(GetRand(SPEED_RANGE) + 5) * 0.5f;
}
/// <summary>
/// 更新
/// </summary>
void MeteoriteBase::Update()
{
	sphereInfo.centerPos.y -= speed;
	if (sphereInfo.centerPos.y <= 0.0f)
	{
		Init();
	}
}
/// <summary>
/// 描画
/// </summary>
void MeteoriteBase::Draw(const int _stageModelHandle)
{
	DrawSphere3D(sphereInfo.centerPos,sphereInfo.radius,sphereInfo.divNum,sphereInfo.difColor,sphereInfo.spcColor,sphereInfo.fillFlag);
	shadow->Draw(_stageModelHandle,sphereInfo.centerPos,SHADOW_HEIGHT,SHADOW_SIZE);
}
