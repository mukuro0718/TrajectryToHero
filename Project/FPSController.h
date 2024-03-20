//===========================================================================
//@brief FPS�R���g���[���[�N���X
// FPS�̐ݒ�A�v�Z�ƕ`����s��
// https://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q10175479905�����p
//===========================================================================
#pragma once
#include"DxLib.h"
class FPSController
{
public:
	FPSController();
	~FPSController();
	const void Init();	//������
	const void Ave();	//FPS�̕��ς��Z�o
	const void Draw();	//FPS��\��
	const void Wait();	//�ڕWFPS�ɂȂ�悤�ҋ@
private:
	/*�ÓI�萔*/
	static constexpr double SET_FPS = 60.0;//�ڕWFPS
	
	static const int FONT_COLOR;//�����̐F

	/*�����o�ϐ�*/
	double	fps;		//fps
	int		startTime;	//�v���J�n����
	int		count;		//������
};