////===========================================================================
////@brief �����蔻��N���X
////===========================================================================
//#pragma once
//#include"DxLib.h"
//#include"Common.h"
//class Collision
//{
//public:
//	Collision();//�R���X�g���N�^
//	void Init();//������
//	~Collision();//�f�X�g���N�^
//	void Delete(int modelHandle);//�폜
//	//�v���C���[�ƃG�l�~�[�̍U���������蔻��
//	void OnAttackCollision(int _frameNum, CharacterBase _baseToAttack, CharacterBase _baseToHit, CharacterStatus _statusToHit, CharacterStatus _statusToAttack);
//	//�X�e�[�^�X�v�Z
//	void CalcStatus();
//	//���Ƌ��̓����蔻��
//	void SphereToSphere(CharacterBase _base1, CharacterBase _base2);
//	//�����蔻���A�ύX�����X�e�[�^�X��Ԃ�
//	const CharacterStatus GetStatusToHit()	 const { return statusToHit;	}
//	const CharacterStatus GetStatusToAttack()const { return statusToAttack; }
//	const CharacterBase   GetBaseToHit()	 const { return baseToHit;		}
//	const CharacterBase   GetBaseToAttack()  const { return baseToAttack;	}
//private:
//	//�\����
//	CharacterStatus statusToHit;	//�U�����󂯂����̃X�e�[�^�X
//	CharacterStatus statusToAttack;	//�U�����������̃X�e�[�^�X
//	CharacterBase	baseToHit;		//�U�����󂯂����̃x�[�X
//	CharacterBase	baseToAttack;		//�U�����������̃x�[�X
//};