//================================
// �`���[�g���A���v���C���[�N���X
// �Q�[���V�[����SwordGirl�N���X�����Ƃ�
// �`���[�g���A���Ǝ��̉��ǂ�������
//================================
#pragma once
#include<DxLib.h>
class TutorialPlayer final
{
public:
	TutorialPlayer(const int _model);//�R���X�g���N�^
	~TutorialPlayer();//�f�X�g���N�^
	void Update();				//�X�V
	void Init();				//������
	const VECTOR GetPos()const { return pos; }//���W��getter
	const bool GetIsAttack()const { return isAttack; }//�U���t���O��getter
	const bool GetIsMove()const { return isMove; }//�ړ��t���O��getter
	void DrawMenu();//�X�e�[�^�X���j���[�̕\��
	const bool GetIsShowStatusMenu();//�X�e�[�^�X�N���X��isShowMenu��Ԃ�
	void FixMoveVec(const VECTOR _fixVec);//�ړ��C��
	void DrawUI();//UI�̕`��
private:
	/*�����o�ϐ�*/
	VECTOR pos;
	bool isAttack;
	bool isMove;
	/*���������֐�*/
	void Move(const VECTOR cameraToPlayer);//�ړ�����
	void Attack();//�U������
	void Death();//���S����
	void AnimChange();//�A�j���[�V�����̕ύX
	void CountInvincibleTimer();//���G���Ԃ̌v��
	void StatusUpdate(const VECTOR _bonfirePos);//�X�e�[�^�X�̍X�V
	void UpdateUI();//UI�̍X�V
	void ChangeColor();//�F�̕ύX
};


