//===============================================
// 覐΃N���X
// 覐Έ�̓������s��
//===============================================
#pragma once
#include<DxLib.h>
#include"Common.h"
class Shadow;
class MeteoriteBase
{
public:
	MeteoriteBase();//�R���X�g���N�^
	~MeteoriteBase();//�f�X�g���N�^

	const void Init();								//������
	const void Update();							//�X�V
	const void Draw(const int _stageModelHandle);	//�`��
	/*getter*/
	const SphereInfo GetSphereInfo() { return sphereInfo; }
private:
	/*�ÓI�萔*/
	static constexpr VECTOR POS_RANGE		= { 450.0f,100.0f,500.0f };	//�����_���ŏo�����W�͈̔�
	static constexpr VECTOR POS_OFFSET		= { 0.0f,200.0f,0.0f };		//���W�̕␳�l
	static constexpr float	SHADOW_SIZE		= 20.0f;					//�e�̑傫��
	static constexpr float	SHADOW_HEIGHT	= 1000.0f;					//�e�̍���
	static constexpr float	RADIUS			= 20.0f;					//���a
	static constexpr bool	FILL_FLAG		= true;						//����h��Ԃ���
	static constexpr int	RADIUS_RANGE	= 7;						//���a�͈̔�
	static constexpr int	SPEED_RANGE		= 2;						//�X�s�[�h�̑���
	static constexpr int	DIV_NUM			= 16;						//��������

	static const int COLOR;//�F
	/*�����o�ϐ�*/
	Shadow*		shadow;		//�e

	SphereInfo	sphereInfo;	//�����\����
	float		speed;		//����
};

