//=====================================
//@brief �X�e�[�^�XUI�N���X
// �X�e�[�^�XUI�̕`����s��
//=====================================
#pragma once
#include<DxLib.h>
#include"Common.h"
class StatusUI
{
public:
	StatusUI();//�R���X�g���N�^
	~StatusUI();//�f�X�g���N�^

	const void Draw(const int _atkUpCount, const int _defUpCount, const int _agiUpCount);//�`��
private:
	/*�ÓI�萔*/
	static constexpr VEC2D ATK_IMAGE_POS = { 10,140  };	//�U���̓A�C�R���̉摜��`�悷����W
	static constexpr VEC2D DEF_IMAGE_POS = { 10,280 };	//�h��̓A�C�R���̉摜��`�悷����W
	static constexpr VEC2D AGI_IMAGE_POS = { 10,210 };	//�f�����A�C�R���̉摜��`�悷����W
	static constexpr VEC2D ATK_TEXT_POS	 = { 60,140  };	//�U���̓A�C�R���p�e�L�X�g��`�悷����W
	static constexpr VEC2D DEF_TEXT_POS  = { 60,280 };	//�h��̓A�C�R���p�e�L�X�g��`�悷����W
	static constexpr VEC2D AGI_TEXT_POS  = { 60,210 };	//�f�����A�C�R���p�e�L�X�g��`�悷����W
	static constexpr VEC2D IMAGE_SIZE	 = { 60,60	};	//�摜�T�C�Y
	
	static const int FONT_COLOR;//�t�H���g�̐F
	/*�����o�ϐ�*/
	int atkImageHandle;	//�摜�n���h��
	int defImageHandle;	//�摜�n���h��
	int agiImageHandle;	//�摜�n���h��
	int fontHandle;		//�t�H���g�n���h��

};

