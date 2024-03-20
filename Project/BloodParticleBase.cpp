#include"BloodParticleBase.h"
#include"Common.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
BloodParticleBase::BloodParticleBase(const int _imageHandle)
	: moveDir(ORIGIN_POS)
	, pos	 (ORIGIN_POS)
	, scale	 (0.0f)
	, speed	 (0.0f)
	, alpha	 (0)
	, isUpdateGrav(false)
	, imageHandle(_imageHandle)
	, framecount(0)
{

}
/// <summary>
/// �f�X�g���N�^
/// </summary>
BloodParticleBase::~BloodParticleBase()
{

}
/// <summary>
/// ������
/// </summary>
const void BloodParticleBase::Init(const VECTOR _targetDir, const VECTOR _targetPos)
{
	pos = _targetPos;
	pos.y += 20.0f;
	alpha = 255;
	SetScale();
	SetSpeed();
	SetMoveDir();
}
/// <summary>
/// �X�V
/// </summary>
const void BloodParticleBase::Update()
{
	//���W�̍X�V
	pos = VAdd(pos, moveDir);
	
	moveDir.y -= GRAVITY;
}
/// <summary>
/// �X�P�[���̐ݒ�
/// </summary>
const void BloodParticleBase::SetScale()
{
	scale = ReturnRandomFloatValue(RANDOM_SCALE_RANGE, false);
}
/// <summary>
/// �����̐ݒ�
/// </summary>
const void BloodParticleBase::SetSpeed()
{
	speed = ReturnRandomFloatValue(RANDOM_SPEED_RANGE, false) / 5;
}
/// <summary>
/// �����̐ݒ�
/// </summary>
const void BloodParticleBase::SetMoveDir()
{
	/*�ړ����������߂�(�P�ʃx�N�g���ɂ���)*/
	//�����_����XYZ�̒l�����߂�
	
	moveDir.x = ReturnRandomFloatValue(RANDOM_DIR_RANGE,true);
	moveDir.y = ReturnRandomFloatValue(RANDOM_DIR_RANGE, true);
	moveDir.z = ReturnRandomFloatValue(RANDOM_DIR_RANGE, true);
	//�o�����x�N�g���𐳋K�����ĕ����x�N�g���ɂ���
	moveDir = VNorm(moveDir);
	//�����x�N�g���ɃX�s�[�h�������Ĉړ��x�N�g���ɂ���
	moveDir = VScale(moveDir, speed);
}
/// <summary>
/// �`��
/// </summary>
const void BloodParticleBase::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBillboard3D(pos, 0.0f, 0.0f, scale, 0.0f, imageHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	alpha -= ALPHA_REDUCED_VALUE;
	if (alpha < 0)
	{
		alpha = 0;
	}
}
/// <summary>
/// �w�肵���͈͂̃����_���l��Ԃ�
/// </summary>
const float BloodParticleBase::ReturnRandomFloatValue(const int _range, const bool _useSign)
{
	if (_useSign)
	{
		if (static_cast<int>(Sign::MINUS) == GetRand(RANDOM_SCALE_RANGE))
		{
			return static_cast<float>(-GetRand(_range));
		}
	}
	return static_cast<float>(GetRand(_range));
}










///// <summary>
///// �R���X�g���N�^
///// </summary>
//BloodParticleBase::BloodParticleBase(const int _imageHandle)
//	:particleDir(ORIGIN_POS)
//	,moveDir(ORIGIN_POS)
//	,pos(ORIGIN_POS)
//	,scale(0.0f)
//	,speed(0.0f)
//	,alpha(0)
//	,imageHandle(_imageHandle)
//{
//
//}
///// <summary>
///// �f�X�g���N�^
///// </summary>
//BloodParticleBase::~BloodParticleBase()
//{
//
//}
///// <summary>
///// ������
///// </summary>
//void BloodParticleBase::Init(const VECTOR _targetDir , const VECTOR _targetPos)
//{
//	pos = _targetPos;
//	pos.y += 20.0f;
//	alpha = 255;
//	SetDir(_targetDir);
//	SetScale();
//	SetSpeed();
//}
///// <summary>
///// �X�V
///// </summary>
//void BloodParticleBase::Update()
//{
//
//	//���W�̍X�V
//	pos = VAdd(pos, moveDir);
//	pos.y -= GRAVITY;
//}
///// <summary>
///// �X�P�[���̐ݒ�
///// </summary>
//void BloodParticleBase::SetScale()
//{
//	scale = ReturnRandomFloatValue(RANDOM_SCALE_RANGE, false);
//}
///// <summary>
///// �����̐ݒ�
///// </summary>
//void BloodParticleBase::SetSpeed()
//{
//	speed = ReturnRandomFloatValue(RANDOM_SPEED_RANGE,false) / 10;
//}
///// <summary>
///// �����̐ݒ�
///// </summary>
//void BloodParticleBase::SetDir(const VECTOR _targetDir)
//{
//	/*�p�[�e�B�N�����o�����������߂�*/
//	//�p�[�e�B�N�����o���ڕW�̕����x�N�g������
//	particleDir = _targetDir;
//	//���K������
//	particleDir = VNorm(particleDir);
//	//Y�������Ƃ�-90�񂷍s����擾����
//	MATRIX yMatrix = MGetRotY(Y_DEG * (DX_PI_F / 180));
//	//Z�������Ƃ�-45�񂷍s����擾����
//	MATRIX zMatrix = MGetRotZ(Z_DEG * (DX_PI_F / 180));
//	//���߂��s������ƂɁA�x�N�g������]������
//	particleDir = VTransform(particleDir, yMatrix);
//	particleDir = VTransform(particleDir, zMatrix);
//	
//	/*�ړ����������߂�(�P�ʃx�N�g���ɂ���)*/
//	//�����_����XYZ�̌X�������߂�
//	MATRIX xRot = MGetRotX(ReturnRandomFloatValue(RANDOM_DEG_RANGE, true) * (DX_PI_F / 180));
//	MATRIX yRot = MGetRotY(ReturnRandomFloatValue(RANDOM_DEG_RANGE, true) * (DX_PI_F / 180));
//	MATRIX zRot = MGetRotZ(ReturnRandomFloatValue(RANDOM_DEG_RANGE, true) * (DX_PI_F / 180));
//	//�ڕW�̕����x�N�g���ɃI�t�Z�b�g�x�N�g���𑫂�
//	moveDir = VTransform(particleDir, xRot);
//	moveDir = VTransform(particleDir, yRot);
//	moveDir = VTransform(particleDir, zRot);
//	//�o�����x�N�g���𐳋K�����ĕ����x�N�g���ɂ���
//	moveDir = VNorm(moveDir);
//	moveDir = VScale(moveDir, speed);
//}
///// <summary>
///// �`��
///// </summary>
//void BloodParticleBase::Draw()
//{
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
//	DrawBillboard3D(pos, 0.0f, 0.0f, scale, 0.0f, imageHandle, TRUE);
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
//	alpha -= ALPHA_REDUCED_VALUE;
//	if (alpha < 0)
//	{
//		alpha = 0;
//	}
//}
///// <summary>
///// �w�肵���͈͂̃����_���l��Ԃ�
///// </summary>
//float BloodParticleBase::ReturnRandomFloatValue(const int _range, const bool _useSign)
//{
//	if (_useSign)
//	{
//		if (static_cast<int>(Sign::MINUS) == GetRand(RANDOM_SCALE_RANGE))
//		{
//			return static_cast<float>(-GetRand(_range) - 2);
//		}
//	}
//	return static_cast<float>(GetRand(_range) + 2);
//}