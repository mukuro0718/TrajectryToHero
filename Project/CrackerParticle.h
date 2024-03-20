#pragma once
#include<DxLib.h>
#include<vector>
class CrackerParticleBase;

class CrackerParticle
{
public:
	CrackerParticle();	//�R���X�g���N�^
	~CrackerParticle();	//�f�X�g���N�^

	const void Init(const bool _isDrawRed, const bool _isDrawBlue, const bool _isDrawYellow);//������
	const void Update();	//�X�V
	const void Draw();		//�`��
	const void OffIsDraw();	//�t���O������
private:
	/*�ÓI�萔*/
	static constexpr VECTOR INIT_POS				= { 550.0f,800.0f,0.0f };	//���������W
	static constexpr int	MAX_RED_PARTICLE_NUM	= 50;						//�Ԃ̃p�[�e�B�N���̐�
	static constexpr int	MAX_BLUE_PARTICLE_NUM	= 50;						//�̃p�[�e�B�N���̐�
	static constexpr int	MAX_YELLOW_PARTICLE_NUM = 50;						//���F�̃p�[�e�B�N���̐�
	static constexpr int	FLAG_NUM				= 3;						//�t���O�̐�
	static const int COLOR_RED;		//�ԐF
	static const int COLOR_BLUE;	//�F
	static const int COLOR_YELLOW;	//���F
	/*�����o�ϐ�*/
	std::vector<CrackerParticleBase*> redParticle;		//�ԃp�[�e�B�N��
	std::vector<CrackerParticleBase*> blueParticle;		//�p�[�e�B�N��
	std::vector<CrackerParticleBase*> yellowParticle;	//���F�p�[�e�B�N��
};

