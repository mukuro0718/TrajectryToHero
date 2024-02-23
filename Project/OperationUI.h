//===================================
//@brief ����UI�̕`��N���X
//�ҋ@���ɑ�������p��UI��`�悷��
//===================================
#pragma once
#include<DxLib.h>
#include"Common.h"

class OperationUI
{
public:
	OperationUI();//�R���X�g���N�^
	~OperationUI();//�f�X�g���N�^

	void Update(const bool _isMove);//�X�V
	void Draw(const VECTOR _bonfirePos, const VECTOR _playerPos);//�`��
private:
	struct DrawRect
	{
		int LX = 0;
		int LY = 0;
		int RX = 0;
		int RY = 0;
	};
	/*�ÓI�萔*/
	static constexpr DrawRect MOVE_UI_DRAW_RECT = { 1670,800,1870,850 };//�ړ�UI�`��͈�
	static constexpr DrawRect ATTACK_UI_DRAW_RECT = { 1670,860,1870,910 };//�U��UI�`��͈�
	static constexpr DrawRect CAMERA_UI_DRAW_RECT = { 1670,920,1870,970 };//�J����UI�`��͈�
	static constexpr DrawRect BONFIRE_MENU_UI_DRAW_RECT = { 1120,660,1320,700 };
	static constexpr int ADD_ALPHA_VALUE = 5;
	static constexpr int MAX_ALPHA = 255;
	static constexpr int MIN_ALPHA = 0;
	static constexpr DrawRect BACKGROUND_POS_FOR_DESCRIPTION = { 1400,30,1910,520 };
	static constexpr VEC2D TEXT_POS_FOR_DESCRIPTION = { 1420,50 };
	static const int FONT_COLOR;//�t�H���g�̐F


	/*�����o�ϐ�*/
	int alpha;
	int moveUI;
	int menuUI;
	int attackUI;
	int cameraUI;
	int textFont;
	int strongUI;
};

