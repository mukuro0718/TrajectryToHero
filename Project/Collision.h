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
	
	void SphereSphereCalc();//���Ƌ��̓����蔻��
	VECTOR NearestPointOfSegmentPointCalc(const VECTOR _startPos,const VECTOR _endPos,const VECTOR _targetPos);//�����Ɠ_�̍ŋߐړ_
	bool SphereCapsuleCalc(const VECTOR _capsuleStartPos, const VECTOR _capsuleEndPos, const float _capsuleRadius, const VECTOR _spherePos, const float sphereRadius);//���ƃJ�v�Z���̓����蔻��
private:
	//�\����
};