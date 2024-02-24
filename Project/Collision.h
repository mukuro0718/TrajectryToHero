//===========================================================================
//@brief �����蔻��N���X
//===========================================================================
#pragma once
#include"DxLib.h"
#include"Common.h"
class Collision
{
public:
	Collision();//�R���X�g���N�^
	void Init();//������
	~Collision();//�f�X�g���N�^
	void Delete(int modelHandle);//�폜
	//�v���C���[�ƃG�l�~�[�̍U���������蔻��
	bool OnDamage(const bool _isInvicible, const bool _isDeath, const CapsuleInfo _capsuleInfo, const SphereInfo _sphereInfo);
	
	VECTOR CapsuleToCapsuleCollision(const VECTOR _myMoveVec, const VECTOR _myVec, const VECTOR _otherVec, const float _myRadius, const float _otherRadius);//�J�v�Z�����m�̂߂荞�ݔ���
	VECTOR NearestPointOfSegmentPointCalc(const VECTOR _startPos,const VECTOR _endPos,const VECTOR _targetPos);//�����Ɠ_�̍ŋߐړ_
	bool SphereCapsuleCalc(const VECTOR _capsuleStartPos, const VECTOR _capsuleEndPos, const float _capsuleRadius, const VECTOR _spherePos, const float sphereRadius);//���ƃJ�v�Z���̓����蔻��
	bool TwoCapsuleHitCollision(const VECTOR _topPos1, const VECTOR _underPos1, const float _radius1, const VECTOR _topPos2, const VECTOR _underPos2, const float _radius2);//�J�v�Z�����m�̓����蔻��
private:
	//�\����
};