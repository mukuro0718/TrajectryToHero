////===========================================================================
////@brief �����蔻��N���X
////===========================================================================
//#include"Collision.h"
///// <summary>
///// �R���X�g���N�^
///// </summary>
//Collision::Collision()
//{
//}
///// <summary>
///// �f�X�g���N�^
///// </summary>
//Collision::~Collision()
//{
//
//}
///// <summary>
///// ������
///// </summary>
//void Collision::Init()
//{
//}
///// <summary>
///// �U���������蔻��
///// </summary>
///// <param name="baseToAttack">�U�������x�[�X</param>
///// <param name="baseToHit">�U�����󂯂����̃x�[�X</param>
///// <param name="statusToHit">�U�����󂯂����̃X�e�[�^�X</param>
///// <param name="statusToAttack">�U�������X�e�[�^�X</param>
//void Collision::OnAttackCollision(int _frameNum, CharacterBase _baseToAttack, CharacterBase _baseToHit, CharacterStatus _statusToHit, CharacterStatus _statusToAttack)
//{
//	statusToHit = _statusToHit;
//	statusToAttack = _statusToAttack;
//	if (!statusToHit.isInvincible && !baseToHit.isDeath)
//	{
//		//�U�����Ǝ󂯎葤�̑I�����Ă���s���̗L���s���̔���
//		//�����蔻��\����
//		MV1_COLL_RESULT_POLY_DIM hitPolyDim;
//		/*VECTOR pos = VGet(_baseToHit.pos.x, _baseToHit.pos.y + 20.0f, _baseToHit.pos.z);*/
//		VECTOR underPos = baseToHit.pos;
//		VECTOR topPos = VGet(_baseToHit.pos.x, _baseToHit.pos.y + 30.0f, _baseToHit.pos.z);
//		//���f���ƃX�t�B�A�̓����蔻����`�F�b�N
//		//hitPolyDim = MV1CollCheck_Sphere(_baseToAttack.modelHandle, _frameNum, pos, _baseToHit.radius);
//		hitPolyDim = MV1CollCheck_Capsule(_baseToAttack.modelHandle, _frameNum, underPos,topPos, _baseToHit.radius);
//		//��x�ł��������Ă����珈�����s��
//		if (hitPolyDim.HitNum >= 1 && !statusToHit.isHit)
//		{
//			statusToHit.isInvincible = true;
//			CalcStatus();
//		}
//		//��n��
//		MV1CollResultPolyDimTerminate(hitPolyDim);
//	}
//}
///// <summary>
///// �U�����̃X�e�[�^�X�v�Z
///// </summary>
///// <param name="statusToHit">�U���������������̃X�e�[�^�X</param>
///// <param name="statusToAttack">�U���������̃X�e�[�^�X</param>
//void Collision::CalcStatus()
//{
//	statusToHit.isInvincible = true;
//	//HP�v�Z
//	statusToHit.HP -= statusToAttack.ATK / statusToHit.DEF;
//
//	//HP���O��������EXP�𑝂₷
//	if (statusToHit.HP < 0)
//	{
//		statusToAttack.EXP += statusToHit.EXP_TO_GIVE;
//	}
//}
///// <summary>
///// ���Ƌ��̓����蔻��
///// </summary>
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