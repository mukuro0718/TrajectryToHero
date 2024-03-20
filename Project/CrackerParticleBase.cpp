#include "CrackerParticleBase.h"
#include "Common.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
CrackerParticleBase::CrackerParticleBase(const int _color)
	:color(_color)
	, vertexPos1(ORIGIN_POS)
	, vertexPos2(ORIGIN_POS)
	, vertexPos3(ORIGIN_POS)
	, vertexPos2Offset(ORIGIN_POS)
	, vertexPos3Offset(ORIGIN_POS)
	, moveVec(ORIGIN_POS)
	, initPos(ORIGIN_POS)
	, speed(0.0f)
	, size(0.0f)
	, isDraw(false)
	, count(0)
{
	
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
CrackerParticleBase::~CrackerParticleBase()
{

}
const void CrackerParticleBase::Init(const VECTOR _initPos)
{
	if (!isDraw)
	{
		//�x�N�g�����X�P�[�����O����T�C�Y�����߂�
		size = ReturnRandomFloatValue(false, SIZE_RANGE) + 5;
		//���������߂�
		speed = ReturnRandomFloatValue(false, SPEED_RANGE) + 5;
		isDraw = true;
		//��ƂȂ���W���o��
		initPos = _initPos;
		//�������΂������
		initPos.x += ReturnRandomFloatValue(false, X_LIMIT);
		initPos.y -= ReturnRandomFloatValue(true, POS_RANGE);
		vertexPos1 = initPos;
		/*Pos2,Pos3�����߂�*/
		//�I�t�Z�b�g���W���o��
		vertexPos2Offset = VGet(ReturnRandomFloatValue(true, POS_RANGE), ReturnRandomFloatValue(true, POS_RANGE), 0.0f);
		vertexPos3Offset = VGet(ReturnRandomFloatValue(true, POS_RANGE), ReturnRandomFloatValue(true, POS_RANGE), 0.0f);
		//��ƂȂ���W�ɑ���
		vertexPos2Offset = VAdd(vertexPos1, vertexPos2Offset);
		vertexPos3Offset = VAdd(vertexPos1, vertexPos3Offset);
		//��ƂȂ���W�����ŋ��߂����W�֐L�т�x�N�g�������߂�
		vertexPos2Offset = VSub(vertexPos1, vertexPos2Offset);
		vertexPos3Offset = VSub(vertexPos1, vertexPos3Offset);
		//��ŋ��߂��x�N�g���𐳋K������
		vertexPos2Offset = VNorm(vertexPos2Offset);
		vertexPos3Offset = VNorm(vertexPos3Offset);
		//���K�������x�N�g�����T�C�Y�ŃX�P�[�����O����
		vertexPos2Offset = VScale(vertexPos2Offset, size);
		vertexPos3Offset = VScale(vertexPos3Offset, size);

		vertexPos2 = VAdd(vertexPos1, vertexPos2Offset);
		vertexPos3 = VAdd(vertexPos1, vertexPos3Offset);

	}
}
/// <summary>
/// �X�V
/// </summary>
const void CrackerParticleBase::Update()
{
	if (isDraw)
	{
		//��ƂȂ���W�ɃX�s�[�h�𑫂�

		vertexPos1.y -= speed;
		//������Ƃɂق��̍��W���o��
		if (vertexPos1.y <= Y_LIMIT)
		{
			vertexPos1 = initPos;
			count++;
		}
		vertexPos2 = VAdd(vertexPos1, vertexPos2Offset);
		vertexPos3 = VAdd(vertexPos1, vertexPos3Offset);
	}
}
/// <summary>
/// �`��
/// </summary>
const void CrackerParticleBase::Draw()
{
	if (isDraw)
	{
		DrawTriangle(static_cast<int>(vertexPos1.x), static_cast<int>(vertexPos1.y), static_cast<int>(vertexPos2.x), static_cast<int>(vertexPos2.y), static_cast<int>(vertexPos3.x), static_cast<int>(vertexPos3.y), color, TRUE);
		if (count >= MAX_FRAME_COUNT)
		{
			isDraw = false;
			count = 0;
		}
	}
}
/// <summary>
/// �����_����Float�^�̒l��Ԃ�
/// </summary>
float CrackerParticleBase::ReturnRandomFloatValue(const bool _sign, const int _range)
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