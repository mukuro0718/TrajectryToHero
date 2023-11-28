//===========================================================================
//@brief �G�t�F�N�g�Ǘ��N���X
// �G�t�F�N�g�̊Ǘ��Ɗ֐��̎��s���s��
//===========================================================================
#pragma once
#include<DxLib.h>

class EffectBase;

class EffectManager
{
public:
	EffectManager();//�R���X�g���N�^
	~EffectManager();//�f�X�g���N�^
	void Create();//����
	void Init();//������
	void Final();//�폜
	void SpreadEffectManager(VECTOR _pos, bool isInvicible);//�g�U����G�t�F�N�g�̊Ǘ��i�`��A�X�V�j
private:
	//�萔
	enum class Direction
	{
		PLUS_X,
		PLUS_XY,
		PLUS_X_MINUS_Y,
		PLUS_XZ,
		PLUS_X_MINUS_Z,
		PLUS_XYZ,
		PLUS_XY_MINUS_Z,
		PLUS_XZ_MINUS_Y,
		PLUS_X_MINUS_YZ,

		MINUS_X,
		MINUS_X_PLUS_Y,
		MINUS_XY,
		MINUS_X_PLUS_Z,
		MINUS_XZ,
		MINUS_X_PLUS_YZ,
		MINUS_XZ_PLUS_Y,
		MINUS_XY_PLUS_Z,
		MINUS_XYZ,

		PLUS_Y,
		PLUS_YZ,
		PLUS_Y_MINUS_Z,

		MINUS_Y,
		MINUS_Y_PLUS_Z,
		MINUS_YZ,

		PLUS_Z,
		MINUS_Z,
	};
	static constexpr int DIRECTION_NUM = 26;//�g�U����G�t�F�N�g�̕�����
	static const VECTOR DIRECTION[DIRECTION_NUM];//�x�N�g���̕���
	static constexpr int SPREAD_CIRCLE_RADIUS = 10;
	static const int SPREAD_CIRCLE_COLOR;
	//�N���X
	EffectBase* spreadEffect[DIRECTION_NUM];
	/*�ϐ�*/
	bool isShowSpreadEffect;//�g�U����G�t�F�N�g��\�����Ă��邩
	VECTOR spreadFirstPos;
};