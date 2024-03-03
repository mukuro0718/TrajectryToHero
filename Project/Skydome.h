//===========================================================================
//@brief �X�J�C�h�[���N���X
// �X�J�C�h�[���̕`����s��
// 3�p�`�|���S�����u���[�����ʂ�^���ĕ`�悷��
//===========================================================================

#pragma once
#include"DxLib.h"
#include"Common.h"

class Star;
class BloomEffect;
class Skydome
{
public:
	Skydome();//�R���X�g���N�^
	~Skydome();//�f�X�g���N�^

	void Init();//������
	void Draw();//�`��
	
private:
	/*�ÓI�萔*/
	static const VECTOR SCALE;
	static constexpr int POLYGON_NUM = 500;
	static const VERTEX3D ORIGIN_VERTEX;
	static const COLOR_U8 STAR_COLOR;			//�O�Ղ̐F
	/*�����o�ϐ�*/
	VECTOR pos;
	int modelHandle;
	int vertexIndex;
	VERTEX3D vertexPos[POLYGON_NUM * 3];//���_���W
	Star* star[POLYGON_NUM];
	BloomEffect* bloom;
};

