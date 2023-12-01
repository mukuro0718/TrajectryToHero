//===========================================================================
//@brief �����蔻��N���X
//===========================================================================
#include"Collision.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
Collision::Collision()
{
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
Collision::~Collision()
{

}
/// <summary>
/// ������
/// </summary>
void Collision::Init()
{
}
/// <summary>
/// �U���������蔻��
/// �_���[�W������s���ꍇ��true,�����łȂ����false��Ԃ�
/// </summary>
bool Collision::OnDamage(const bool _isInvicible,const bool _isDeath,const CapsuleInfo _capsuleInfo,const SphereInfo _sphereInfo)
{
	if (!_isInvicible && !_isDeath)
	{
		//���ƃX�t�B�A�̓����蔻����`�F�b�N
		bool isHit = SphereCapsuleCalc(_capsuleInfo.topPos,_capsuleInfo.underPos,_capsuleInfo.radius,_sphereInfo.centerPos,_sphereInfo.radius);
		//�������Ă����珈�����s��
		if (isHit)
		{
			return true;
		}
	}
	return false;
}
 //<summary>
 //���Ƌ��̓����蔻��
 //</summary>
//void Collision::SphereToSphere(CharacterBase _base1, CharacterBase _base2)
//{
//	//�`�F�b�N�Ώۂ̃x�[�X
//	baseToAttack = _base1;
//	//�ق��̑Ώۂ̃x�[�X
//	baseToHit = _base2;
//	//�Q�̃x�[�X�̍��W�������������珈�������Ȃ�
//	//�i�G�̔ԍ����o���Ă��ꂪ�����������珈�������Ȃ��悤�ɂ����ق����ǂ������j
//	if (baseToAttack.pos == baseToHit.pos || baseToAttack.isHit == true){}
//	else
//	{
//		int isHit = HitCheck_Sphere_Sphere(baseToAttack.pos, baseToAttack.radius, baseToHit.pos, baseToHit.radius);
//		if (isHit > 0)
//		{
//			//�������瓖���蔻����s������֌������x�N�g�����o��
//			VECTOR myToOther = VSub(baseToHit.pos, baseToAttack.pos);
//			//myToOther�̋t�x�N�g��
//			VECTOR otherToMy = VSub(baseToAttack.pos, baseToAttack.pos);
//
//			//�߂荞�ݗʁ��i�����̔��a�{�����蔻����s�����蔼�a�j�[�x�N�g��AB�̑傫��
//			float pushBackValue = (baseToAttack.radius + baseToHit.radius) - VSize(myToOther);
//			//�t�x�N�g���𐳋K������
//			VECTOR myToOtherNorm = VNorm(otherToMy);
//			baseToAttack.correctionValue = VScale(myToOtherNorm,pushBackValue);
//			baseToAttack.isHit = true;
//		}
//	}
//}

/// <summary>
/// �����Ɠ_�̍ŋߐړ_��Ԃ�
/// </summary>
VECTOR Collision::NearestPointOfSegmentPointCalc(const VECTOR _startPos,	const VECTOR _endPos,const VECTOR _targetPos)
{
	VECTOR targetPos = _targetPos;//�ŋߐړ_�����߂����ڕW�_
	VECTOR startPos = _startPos;//�ŋߐړ_�����߂��������J�n�_
	VECTOR endPos = _endPos;//�ŋߐړ_�����߂��������I���_
	VECTOR nearestPos = ORIGIN_POS;//�ŋߐړ_
	float time = 0.0f;//�n�_�`�I�_�܂ł�0.0f�`1.0f�Ƃ����l
	//�n�_����I�_�ɐL�т��x�N�g��
	VECTOR segmentVecSE = VSub(_endPos, _startPos);
	//�n�_����^�[�Q�b�g�ɐL�т��x�N�g��
	VECTOR segmentVecST = VSub(_targetPos, _startPos);
	//�^�C���Ɏn�_����ڕW�ɐL�т��x�N�g���Ǝn�_����I�_�ɐL�т��x�N�g���̓��ς�����
	time = VDot(segmentVecST, segmentVecSE);

	//�����^�C�����O�ȉ��ɂȂ�����i���߂����ڕW�_�������̎n�_�̊O���ɂ���j
	if (time <= 0.0f)
	{
		//�^�C�����O�ɂ���
		time = 0.0f;
		//�ŋߐړ_�͐����̎n�_�ɂȂ�
		nearestPos = startPos;
	}
	else
	{
		//�����x�N�g���̓��ς���邽�߁A��ɐ��ɂȂ�A���̒l�̓x�N�g���̃T�C�Y�ɂȂ�
		/*HACK:vecA�EvecA = |vecA|^2*/
		float segmentVecSESize = VDot(segmentVecSE, segmentVecSE);
		//�x�N�g���̃T�C�Y���^�C��������������΁i���߂����ڕW�_���n�_����I�_�܂ł͈̔͊O�ɂ���j
		if (time >= segmentVecSESize)
		{
			//�^�C�����P�ɂ���
			time = 1.0f;
			//�ŋߐړ_�͐����̏I�_�ɂȂ�
			nearestPos = endPos;
		}
		//�����łȂ���΁i���߂����ڕW�_���n�_����I�_�܂ł͈͓̔��ɂ���j
		else
		{
			//�^�C���Ɏn�_�`�I�_�Ǝn�_�`�ڕW�_�ɐL�т��x�N�g���̓��ς��n�_�`�I�_�̃x�N�g���̃T�C�Y�Ŋ���
			time = time / segmentVecSESize;
			//�ŋߐړ_�͎n�_�`�I�_�ɐL�т��x�N�g���Ƀ^�C�����������x�N�g���Ǝn�_�𑫂������̂ɂȂ�
			nearestPos = VAdd(startPos,VScale(segmentVecSE, time));
		}
	}
	return nearestPos;
}
bool Collision::SphereCapsuleCalc(const VECTOR _capsuleStartPos,const VECTOR _capsuleEndPos,const float _capsuleRadius,const VECTOR _spherePos,const float sphereRadius)
{
	VECTOR nearestPos = ORIGIN_POS;

	//�J�v�Z���̐����Ƌ��̒��S�_���Ƃɍŋߐړ_���o��
	nearestPos = NearestPointOfSegmentPointCalc(_capsuleStartPos,_capsuleEndPos,_spherePos);
	//�ŋߐړ_�ƃX�t�B�A�̒��S�Ƃ̋���
	VECTOR vecSphNear = VSub(_spherePos,nearestPos);
	//�ŋߐړ_�Ƌ��̒��S�Ƃ̃T�C�Y���A�J�v�Z���̔��a�{���̔��a��菬����������true��Ԃ�
	if (VSize(vecSphNear) < _capsuleRadius + sphereRadius)
	{
		return true;
	}
	return false;
}