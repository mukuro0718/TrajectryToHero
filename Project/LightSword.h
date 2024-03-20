//=====================================================
//���̌��G�t�F�N�g�N���X
// �������̉��F������`�悵�A�u���[���N���X�ɂ���Č��点��
//=====================================================
#pragma once
#include<DxLib.h>

class LightSword
{
public:
	LightSword();	//�R���X�g���N�^
	~LightSword();	//�f�X�g���N�^
	const void Update(const VECTOR _bladeUnderPos, const VECTOR _bladeMiddlePos, const VECTOR _bladeTopPos);//�X�V
	const void Draw();//�`��

private:
	/*�ÓI�萔*/
	static constexpr int BLADE_VERTEX_NUM = 9;								//�n���_��
	static constexpr int POLYGON_NUM = 12;									//�|���S����
	static constexpr unsigned short BLADE_VERTEX_INDEX[POLYGON_NUM * 3] =	//���_�C���f�b�N�X
	{ 
		0,1,2,
		0,2,3,
		0,3,4,
		0,4,1,
		1,4,8,
		1,8,5,
		2,1,5,
		2,5,6,
		3,2,6,
		3,6,7,
		4,3,7,
		4,7,8,
	};
	static constexpr float OFFSET_VALUE = 3.0f;	//�I�t�Z�b�g�l
	static constexpr float BLADE_SCALE = 5.0f;	//�傫��
	static constexpr int VERTEX_FOR_ROTATE_NUM = 3;//���_��

	static const VECTOR	  VERTEX_FOR_ROTATE[VERTEX_FOR_ROTATE_NUM];	//���ς̊p�x��90�x�ɂȂ�悤�Ȉʒu�֌W�̒��_�Q
	static const VERTEX3D INIT_VERTEX;								//�������p���_�\����
	/*���������֐�*/
	const void MakeRotateMatrix();   //�K�v�ȉ�]�s������
	const void MakeBladeVertex(const VECTOR _bladeVec, const VECTOR _sickleVec);//�n�̃x�N�g�������

	/*�ÓI�萔*/
	VERTEX3D bladeVertex[BLADE_VERTEX_NUM];	//���_
	/*��]�}�g���b�N�X���o�����߂̕ϐ��Q*/
	MATRIX rotateMatrix;//blade,sickle�̒��_�̂��ƂɂȂ���W���o�����߂̉�]�s��
};

