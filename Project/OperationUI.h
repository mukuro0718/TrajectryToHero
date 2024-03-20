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

	const void Update(const bool _isMove);								//�X�V
	const void Draw(const VECTOR _bonfirePos, const VECTOR _playerPos);	//�`��
private:
	/*�\���́E�񋓑�*/
	struct DrawRect
	{
		int LX = 0;
		int LY = 0;
		int RX = 0;
		int RY = 0;
	};
	/*�ÓI�萔*/
	static constexpr DrawRect	BACKGROUND_POS_FOR_DESCRIPTION	= { 1400,30,1910,520 };	//�w�i�`����W
	static constexpr DrawRect	BONFIRE_MENU_UI_DRAW_RECT		= { 1120,660,1320,700 };//���΃��j���[�`��ʒu
	static constexpr VEC2D		TEXT_POS_FOR_DESCRIPTION		= { 1420,50 };			//�e�L�X�g�`��ʒu
	static constexpr DrawRect	ATTACK_UI_DRAW_RECT				= { 1670,860,1870,910 };//�U��UI�`��͈�
	static constexpr DrawRect	CAMERA_UI_DRAW_RECT				= { 1670,920,1870,970 };//�J����UI�`��͈�
	static constexpr DrawRect	MOVE_UI_DRAW_RECT				= { 1670,800,1870,850 };//�ړ�UI�`��͈�
	static constexpr int		ADD_ALPHA_VALUE					= 5;					//�ǉ��A���t�@/
	static constexpr int		MAX_ALPHA						= 255;					//�ő�A���t�@
	static constexpr int		MIN_ALPHA						= 0;					//�ŏ��A���t�@
	static const int FONT_COLOR;//�t�H���g�̐F


	/*�����o�ϐ�*/
	int alpha;		//�A���t�@
	//������@UI�摜
	int moveUI;		//�ړ�
	int menuUI;		//���j���[
	int attackUI;	//�U��UI
	int cameraUI;	//�J����UI
	int textFont;	//�e�L�X�g
	int strongUI;	//���G�}�[�N
};

