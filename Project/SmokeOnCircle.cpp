#include "SmokeOnCircle.h"
#include "Common.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SmokeOnCircle::SmokeOnCircle(const int _graphHandle)
	:scale(INIT_SCALE)
	, isDrawStart(false)
	, centerPos(ORIGIN_POS)
	, handle(_graphHandle)
	, alpha(INIT_ALPHA)
	, removeAlpha(0)
	,pos(ORIGIN_POS)
{
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
SmokeOnCircle::~SmokeOnCircle()
{

}
/// <summary>
/// ���W�̐ݒ�
/// </summary>
const void SmokeOnCircle::SetPosAndAlpha()
{
	pos.x = ReturnRandomFloatValue(MAX_SIZE, true) * 0.1f;
	pos.y = 1.0f;
	pos.z = ReturnRandomFloatValue(MAX_SIZE,true) * 0.1f;

	pos = VSub(pos, ORIGIN_POS);
	pos = VNorm(pos);
	pos = VScale(pos, INIT_SCALE);
	pos = VAdd(centerPos,pos);
	pos.y = 1.0f;

	removeAlpha = GetRand(MAX_REMOVE_ALPHA) + 1;
}
/// <summary>
/// ������
/// </summary>
const void SmokeOnCircle::Init(const VECTOR _targetPos)
{
	scale = 5.0f;
	centerPos = _targetPos;
	SetPosAndAlpha();
	alpha = INIT_ALPHA;
}
/// <summary>
/// �X�V
/// </summary>
const void SmokeOnCircle::Update()
{
	alpha -= removeAlpha;
	if (alpha <= MIN_ALPHA)
	{
		Init(centerPos);
	}
	pos.y += 0.05f;
}
/// <summary>
/// �`��
/// </summary>
const void SmokeOnCircle::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBillboard3D(pos, 0.5f, 0.5f, scale, 0.0f, handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, INIT_ALPHA);
}
/// <summary>
/// �w�肵���͈͂̃����_���l��Ԃ�
/// </summary>
const float SmokeOnCircle::ReturnRandomFloatValue(const int _range, const bool _useSign)
{
	if (_useSign)
	{
		if (1 == GetRand(1))
		{
			return static_cast<float>(-GetRand(_range));
		}
	}
	return static_cast<float>(GetRand(_range));
}
