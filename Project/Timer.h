//===========================================================================
//@brief �^�C�}�[�N���X
// �����̃^�C�~���O�����߂鎞�́A���Ԃł͂Ȃ��t���[�����ōs�����ق����ǂ��Ǝv���̂ŁA
// ����͎������Ȃ��ق����ǂ��i����Ӗ����Ȃ��j
//===========================================================================
#pragma once
#include"Dxlib.h"

class Timer
{
public:
	Timer();	//�R���X�g���N�^
	~Timer();	//�f�X�g���N�^

	const bool CountTimer();							//���Ԃ̌v��
	const void Init(const float _targetTime);			//������
	const void StartTimer();							//�^�C�}�[�J�n
	const void EndTimer();								//�^�C�}�[�I��
	const void DrawNowTimer(const VECTOR _playerPos);	//���ݎ��Ԃ̕`��
	//�^�C�}�[�X�^�[�g�����getter
	const bool getIsStartTimer()const { return isStartTimer; }
private:
	/*�����o�ϐ�*/
	float nowTime;		//���݂̎���
	float prevTime;		//�v���J�n���̎���
	float targetTime;	//�ڕW����
	bool  isStartTimer;	//�v�����n�܂��Ă��邩
};