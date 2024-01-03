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
	void Draw();//�`��
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
	static constexpr DrawRect MENU_UI_DRAW_RECT = { 1620,860,1870,910 };//���j���[UI�`��͈�
	static constexpr DrawRect ATTACK_UI_DRAW_RECT = { 1670,920,1870,970 };//�U��UI�`��͈�
	static constexpr DrawRect CAMERA_UI_DRAW_RECT = { 1670,980,1870,1030 };//�J����UI�`��͈�
	static constexpr int ADD_ALPHA_VALUE = 5;
	static constexpr int MAX_ALPHA = 255;
	static constexpr int MIN_ALPHA = 0;
	/*�����o�ϐ�*/
	int alpha;
	int moveUI;
	int menuUI;
	int attackUI;
	int cameraUI;
};

