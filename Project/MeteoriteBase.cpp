#include "MeteoriteBase.h"
#include "Shadow.h"
const int MeteoriteBase::COLOR = GetColor(100,10,10);
/// <summary>
/// �R���X�g���N�^
/// </summary>
MeteoriteBase::MeteoriteBase()
	:speed(0.0f)
	, shadow(nullptr)
{
	Init();
	shadow = new Shadow();
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
MeteoriteBase::~MeteoriteBase()
{

}
/// <summary>
/// ������
/// </summary>
void MeteoriteBase::Init()
{
	//���S���W�������_���ŏo��
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
/// �X�V
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
/// �`��
/// </summary>
void MeteoriteBase::Draw(const int _stageModelHandle)
{
	DrawSphere3D(sphereInfo.centerPos,sphereInfo.radius,sphereInfo.divNum,sphereInfo.difColor,sphereInfo.spcColor,sphereInfo.fillFlag);
	shadow->Draw(_stageModelHandle,sphereInfo.centerPos,SHADOW_HEIGHT,SHADOW_SIZE);
}
