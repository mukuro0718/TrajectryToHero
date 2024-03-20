#include "FireParticle.h"
#include"Common.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
FireParticle::FireParticle(const VECTOR _centerPos,const int _particleData)
	: centerPos	(_centerPos)
	, pos		(_centerPos)
	, size(0.0f)
	, speed		(0.0f)
	, isDraw	(false)
	, particleData(_particleData)
	, alpha(0)
{
	Init();
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
FireParticle::~FireParticle()
{
}
/// <summary>
/// ������
/// </summary>
const void FireParticle::Init()
{
	pos = centerPos;

	pos.x += ReturnRandomFloat(true, X_POS_RANGE);
	pos.z += ReturnRandomFloat(true, Z_POS_RANGE);

	VECTOR centerToNowPos = VSub(pos, centerPos);
	float vecSize = VSize(centerToNowPos);
	if (vecSize <= 3)
	{
		size = ReturnRandomFloat(false, 3) * 0.1f;
		pos.y = 15.0f;
	}
	else if (vecSize <= 6)
	{
		size = ReturnRandomFloat(false, 2) * 0.1f;
		pos.y = 10.0f;
	}
	else
	{
		size = ReturnRandomFloat(false, 1) *0.1f;
		pos.y = 5.0f;
	}
	
	speed = ReturnRandomFloat(false,SPEED_RANGE) * 0.01f;

	alpha = static_cast<int>(ReturnRandomFloat(false, ALPHA_RANGE));
}
const void FireParticle::Update()
{
	size -= SIZE_REDUCED_VALUE;

	pos.y += speed;
	alpha -= ALPHA_REDUCED_VALUE;
	if (alpha < 0)
	{
		Init();
	}
}
const void FireParticle::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBillboard3D(pos, CX, CY, size, ANGLE, particleData, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, ALPHA_MAX_VALUE);
}
/// <summary>
/// �����_���ŏo����int�^�̒l��float�^�ŕԂ�
/// </summary>
/// <param name="_useSign"></param>
const float FireParticle::ReturnRandomFloat(const bool _useSign,const int _range)
{
	//�Ԃ��l
	float outPutValue = static_cast<float>(GetRand(_range));
	//�������g�p���邩�i�}�C�i�X�̒l�����e���邩�j
	if (_useSign)
	{
		//�����O���o����}�C�i�X�ɂ���
		if (GetRand(SIGN_RANGE) == 0)
		{
			outPutValue *= -1;
		}
	}
	return outPutValue;
}