//====================================================
// @brief �������@�N���X
//====================================================
#pragma once
#include<DxLib.h>
#include "Common.h"
class Explosion
{
public:
	Explosion();	//�R���X�g���N�^
	~Explosion();	//�f�X�g���N�^

	const void Init();												//������
	const void Update(const bool _isDraw, const VECTOR _targetPos);	//�X�V
	const void Draw();												//�`��

	/*getter*/
	const SphereInfo GetSphereInfo()const { return sphere; }
private:
	/*�ÓI�萔*/
	static constexpr float	MAX_RADIUS = 50.0f;	//�������@�ő唼�a
	static constexpr float	MAX_SCALE  = 0.8f;	//�ő�g�嗦
	static constexpr float	ADD_SCALE  = 0.01f;	//�g�嗦������
	static constexpr float	ADD_ROTATE = 0.1f;	//��]��������
	/*���������֐�*/
	const void SetScale(const float _scale);	//�g�嗦�̐ݒ�
	const void SetRotate(const float _rotate);	//��]���̐ݒ�
	/*�����o�ϐ�*/
	VECTOR		rotate;		//��]��
	VECTOR		scale;		//�g�嗦
	bool		isDraw;		//�`�悵�Ă��邩
	int			modelHandle;//���f���n���h��
	SphereInfo	sphere;		//�����
};

