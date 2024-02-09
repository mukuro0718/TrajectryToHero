#include "StatusUpParticleBase.h"
#include"Common.h"
/// <summary>
/// コンストラクタ
/// </summary>
StatusUpParticleBase::StatusUpParticleBase(const int _color)
	:topPos(ORIGIN_POS)
	, underPos(ORIGIN_POS)
	, offsetPos(ORIGIN_POS)
	, size(0.0f)
	, color(_color)
	, alpha(MAX_ALPHA_VALUE)
{
	Init();
}
/// <summary>
/// デストラクタ
/// </summary>
StatusUpParticleBase::~StatusUpParticleBase()
{
}
/// <summary>
/// 初期化
/// </summary>
void StatusUpParticleBase::Init()
{
	speed = ReturnRandomFloatValue(false, SPEED_RANGE) / 10.0f;
	size = ReturnRandomFloatValue(false,SIZE_RANGE);
	offsetPos = VGet(ReturnRandomFloatValue(true,POS_RANGE), 0.0f, ReturnRandomFloatValue(true, POS_RANGE));
}
/// <summary>
/// 更新
/// </summary>
void StatusUpParticleBase::Update(const VECTOR _targetPos)
{
	underPos = VAdd(_targetPos,offsetPos);
	topPos = VGet(underPos.x,underPos.y + size,underPos.z);

	offsetPos.y += speed;
	alpha -= ADD_ALPHA_VALUE;

	if (offsetPos.y > 30.0f)
	{
		alpha = MAX_ALPHA_VALUE;
		offsetPos.y = 0.0f;
	}
}
/// <summary>
/// 描画
/// </summary>
void StatusUpParticleBase::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawLine3D(topPos,underPos,color);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_ALPHA_VALUE);
}
float StatusUpParticleBase::ReturnRandomFloatValue(const bool _sign,const int _range)
{
	int outPutValue = 0;
	outPutValue = GetRand(_range) + 1;
	if (_sign)
	{
		if (GetRand(SIGN_RANGE) == 1)
		{
			outPutValue *= -1;
		}
	}
	return static_cast<float>(outPutValue);
}