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
	void Init();	//������
	void Ave();	//FPS�̕��ς��Z�o
	void Draw();	//FPS��\��
	void Wait();	//�ڕWFPS�ɂȂ�悤�ҋ@
private:
	static const int FONT_COLOR;//�����̐F
	static constexpr double SET_FPS = 60.0;//�ڕWFPS
	double fps;//fps
	int startTime;//�v���J�n����
	int count;//������
};