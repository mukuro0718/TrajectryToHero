//===========================================================================
//@brief �^�C�}�[�N���X
//===========================================================================
#pragma once
#include"Dxlib.h"

class Timer
{
public:
	Timer();//�R���X�g���N�^
	~Timer();//�f�X�g���N�^
	void Init(float targetTime);//������
	bool CountTimer();//���Ԃ̌v��
	void StartTimer();//�^�C�}�[�J�n
	void EndTimer();//�^�C�}�[�I��
	//�^�C�}�[�X�^�[�g�����getter
	const bool getIsStartTimer()const { return isStartTimer; }
	void DrawNowTimer(VECTOR playerPos);
private:
	//�ϐ�
	bool isStartTimer;//�v�����n�܂��Ă��邩
	float nowTime;//���݂̎���
	float prevTime;//�v���J�n���̎���
	float targetTime;//�ڕW����
};