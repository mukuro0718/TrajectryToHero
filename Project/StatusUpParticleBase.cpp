#include "StatusUpParticleBase.h"
#include"Common.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
StatusUpParticleBase::StatusUpParticleBase(const int _imageHandle)
	: offsetPos(ORIGIN_POS)
	, targetPos(ORIGIN_POS)
	, size(0.0f)
	, imageHandle(_imageHandle)
	, alpha(MAX_ALPHA_VALUE)
{
	Init();
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
StatusUpParticleBase::~StatusUpParticleBase()
{
}
/// <summary>
/// ������
/// </summary>
void StatusUpParticleBase::Init()
{
	speed = ReturnRandomFloatValue(false, SPEED_RANGE) / 10.0f;
	size = ReturnRandomFloatValue(false,SIZE_RANGE);
	offsetPos = VGet(ReturnRandomFloatValue(true, POS_RANGE),0.0f, ReturnRandomFloatValue(true, POS_RANGE));
	addAlphaValue = static_cast<int>(ReturnRandomFloatValue(false, ALPHA_RANGE));
	alpha = MAX_ALPHA_VALUE;
	frameCount = 0;
}
/// <summary>
/// �X�V
/// </summary>
void StatusUpParticleBase::Update(const VECTOR _targetPos)
{
	//�摜��`�悷�钆�S���W
	targetPos = VAdd(_targetPos,offsetPos);

	offsetPos.y += speed;
	alpha -= addAlphaValue;

	frameCount++;
	
}
/// <summary>
/// �`��
/// </summary>
void StatusUpParticleBase::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBillboard3D(targetPos, 0.5f,0.5f, size,0.0f, imageHandle,TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_ALPHA_VALUE);
	if (offsetPos.y > 30.0f || alpha < MIN_ALPHA_VALUE)
	{
		Init();
	}
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