#include"BloodParticleBase.h"
#include"Common.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
BloodParticleBase::BloodParticleBase()
	:particleDir(ORIGIN_POS)
	,moveDir(ORIGIN_POS)
	,pos(ORIGIN_POS)
	,speed(0.0f)
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
void BloodParticleBase::Init(const VECTOR _targetDir)
{
	SetDir(_targetDir);
	SetScale();
	SetSpeed();
}
/// <summary>
/// �X�V
/// </summary>
void BloodParticleBase::Update()
{
	//�ړ��T�C�Y�����߂�
	VECTOR moveSize = VScale(moveDir, speed);
	//���W�̍X�V
	pos = VAdd(pos, moveSize);
}
/// <summary>
/// �X�P�[���̐ݒ�
/// </summary>
void BloodParticleBase::SetScale()
{
	scale.x = static_cast<float>(GetRand(RANDOM_OFFSET_RANGE));
	scale.y = static_cast<float>(GetRand(RANDOM_OFFSET_RANGE));
	scale.z = static_cast<float>(GetRand(RANDOM_OFFSET_RANGE));
}
/// <summary>
/// �����̐ݒ�
/// </summary>
void BloodParticleBase::SetSpeed()
{
	speed = static_cast<float>(GetRand(RANDOM_SPEED_RANGE));
}
/// <summary>
/// �����̐ݒ�
/// </summary>
void BloodParticleBase::SetDir(const VECTOR _targetDir)
{
	/*�p�[�e�B�N�����o�����������߂�*/
	//�p�[�e�B�N�����o���ڕW�̕����x�N�g������
	particleDir = _targetDir;
	//���K������
	particleDir = VNorm(particleDir);
	//Y�������Ƃ�-90�񂷍s����擾����
	MATRIX yMatrix = MGetRotY(Y_DEG * (DX_PI_F / 180));
	//Z�������Ƃ�-45�񂷍s����擾����
	MATRIX zMatrix = MGetRotZ(Z_DEG * (DX_PI_F / 180));
	//���߂��s������ƂɁA�x�N�g������]������
	particleDir = VTransform(particleDir, yMatrix);
	particleDir = VTransform(particleDir, zMatrix);
	
	/*�ړ����������߂�(�P�ʃx�N�g���ɂ���)*/
	//�����_����XYZ�̑����ʂ����߂�
	VECTOR offset = ORIGIN_POS;
	offset.x = static_cast<float>(GetRand(RANDOM_OFFSET_RANGE));
	offset.y = static_cast<float>(GetRand(RANDOM_OFFSET_RANGE));
	offset.z = static_cast<float>(GetRand(RANDOM_OFFSET_RANGE));
	//�ڕW�̕����x�N�g���ɃI�t�Z�b�g�x�N�g���𑫂�
	moveDir = VAdd(particleDir, offset);
	//�o�����x�N�g���𐳋K�����ĕ����x�N�g���ɂ���
	moveDir = VNorm(moveDir);
}