//================================================
// @brief ���N���X
// 3�̒��_��ێ����A�O�p�`�̃|���S����`�悷��
//================================================
#pragma once
#include<DxLib.h>
#include<vector>
class Star
{
public:
	Star();//�R���X�g���N�^
	~Star();//�f�X�g���N�^
	const VECTOR& GetVertex(const int _index)const { return vertex[_index]; }
private:
	/*�ÓI�萔*/
	static constexpr int VERTEX_NUM = 3;//���_��
	static constexpr int POS_RANGE = 800;
	static constexpr int SIGN_RANGE = 1;
	static constexpr int SCALE = 10;
	/*�����o�ϐ�*/
	VECTOR vertex[VERTEX_NUM];
	const VECTOR GetRandomFirstPos();
	const VECTOR GetRandomOtherPos();
};

