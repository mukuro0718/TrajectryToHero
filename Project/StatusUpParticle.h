//=======================================================
// @brief�@���x���A�b�v�EHP�񕜎��p�[�e�B�N��
//=======================================================
#pragma once
#include<DxLib.h>
#include<vector>
class StatusUpParticleBase;
class StatusUpParticle
{
public:
	StatusUpParticle(const float _prevPlayerLv);//�R���X�g���N�^
	~StatusUpParticle();//�f�X�g���N�^

	const void Update(const VECTOR _targetPos,const bool _isBonfireMenu, const float _playerLv);//�X�V

	const void Draw(const bool _isBonfireMenu);//�`��

private:
	/*�ÓI�萔*/
	static constexpr int MAX_FRAME_COUNT = 60;//�ő�t���[��
	/*�����o�ϐ�*/
	std::vector<StatusUpParticleBase*> hpParticle;	//hp�p�[�e�B�N��
	std::vector<StatusUpParticleBase*> lvUpParticle;//���x���A�b�v���p�[�e�B�N��

	VECTOR	targetPos;			//�ڕW���W
	float	prevPlayerLv;		//�O�̃v���C���[���x��
	bool	isDrawLvupParticle;	//�p�[�e�B�N����`�悷�邩
	int		hpParticleImage;	//hp�p�[�e�B�N���摜�n���h��
	int		LvUPParticleImage;	//���x���A�b�v�p�[�e�B�N���摜�n���h��
	int		lvUpFrameCount;		//�p�[�e�B�N���\���t���[���J�E���g
	int		textImageHandle;	//���x���A�b�v�e�L�X�g�p�[�e�B�N���摜�n���h��
};

