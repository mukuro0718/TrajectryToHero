//===========================================================================
//@brief �g�U����G�t�F�N�g�N���X
// �����Ԃ����o��
//===========================================================================
#pragma once
#include<DxLib.h>
#include<vector>

class BloodParticleBase;

class BloodParticle
{
public:
	BloodParticle();				//�R���X�g���N�^
	~BloodParticle();				//�f�X�g���N�^
	void Init(const VECTOR _targetDir, const VECTOR _targetPos);//������
	void Update();//�X�V
	void Draw();//�`��
private:
	/*�ÓI�萔*/
	static constexpr int PARTICLE_NUM = 100;//�p�[�e�B�N����
	static constexpr int MAX_FRAME_NUM = 15;//�ő�t���[����
	/*�����o�ϐ�*/
	VECTOR initPos;	//�����`����W
	std::vector<BloodParticleBase*> particle;
	int imageHandle;//�摜�n���h��
	int frameCount;//�t���[���J�E���g
	bool isDraw;//�`�悵�Ă��邩
};