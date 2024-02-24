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
 //�J�v�Z�����m�̓����蔻��iY���W�͍l�����Ȃ����߁A���ۂ̔���͂QD�ɂȂ�j
 // �Q�_�Ԃ̍��W�Ɣ��a�̍��v���ׂ�
 //</summary>
VECTOR Collision::CapsuleToCapsuleCollision(const VECTOR _myMoveVec,const VECTOR _myPos,const VECTOR _otherPos,const float _myRadius,const float _otherRadius)
{
	//�����ړ����Ă��Ȃ���Έړ���0��Ԃ�
	if (_myMoveVec == ORIGIN_POS)
	{
		return ORIGIN_POS;
	}
	VECTOR outPutVec = ORIGIN_POS;
	VECTOR myPos = _myPos;	//�����̃x�N�g��
	VECTOR otherPos = _otherPos;//����̃x�N�g��
	//2�̍��W�Ԃ̃x�N�g�������߂�
	VECTOR myToOtherPos = VSub( otherPos,myPos);
	//�x�N�g���̑傫�������߂�
	float myToOtherPosSize = VSize(myToOtherPos);

	float myRadius = _myRadius;		//�����̔��a
	float otherRadius = _otherRadius;	//����̔��a
	//��̔��a�̍��v�����߂�
	float sumRadius = myRadius + otherRadius;

	//�����x�N�g���̑傫�������a�̍��v������������Γ������Ă���
	if (sumRadius > myToOtherPosSize)
	{
		//�x�N�g���̑傫���Ɣ��a�̍��v�̍������߂�
		float diff = sumRadius - myToOtherPosSize;
		VECTOR otherToMyPos = VSub(myPos,otherPos);
		//2�_�Ԃ̃x�N�g���𐳋K������
		VECTOR otherTomyPosNorm = VNorm(otherToMyPos);
		//���K�������x�N�g�������ŃX�P�[�����O����
		outPutVec = VScale(otherTomyPosNorm,diff);
	}
	return outPutVec;
}

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
/// <summary>
/// �J�v�Z�����m�̓����蔻��
/// </summary>
bool Collision::TwoCapsuleHitCollision(const VECTOR _startPos1, const VECTOR _endPos1, const float _radius1, const VECTOR _startPos2, const VECTOR _endPos2, const float _radius2)
{
	//�Q�̃J�v�Z���̐������o���A�ŋߓ_�Ԃ̋����𓾂�
	float minLength = Segment_Segment_MinLength(_startPos1,_startPos2,_endPos1,_endPos2);
	//��̃J�v�Z���̔��a�̍��v�����߂�
	float sumRadius = _radius1 + _radius2;
	//�ŋߓ_�ԂƔ��a�̍��v���ׂāA���a�̍��v�����ŋߓ_�Ԃ�������Փ˂��Ă���
	if (sumRadius <= minLength)
	{
		return true;
	}
	return false;
}