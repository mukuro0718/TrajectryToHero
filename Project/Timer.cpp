//===========================================================================
//@brief �^�C�}�[�N���X
//===========================================================================
#include"Timer.h"

/// <summary>
/// ��������R���X�g���N�^
/// </summary>
/// <param name="targetTime">�ڕW����</param>
Timer::Timer()
{
	//SetFontSize(64);
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
Timer::~Timer()
{
	//�����Ȃ�
}
/// <summary>
/// ������
/// </summary>
/// <param name="targetTime">�ڕW����</param>
void Timer::Init(float targetTime)
{
	isStartTimer = false;
	this->targetTime = targetTime * 100.0f;
	nowTime = prevTime = 0.0f;
}
/// <summary>
/// �^�C�}�[�J�n
/// </summary>
void Timer::StartTimer()
{
	if (!isStartTimer)
	{
		nowTime = prevTime = GetNowCount();
		isStartTimer = true;
	}
}
/// <summary>
/// �^�C�}�[�I��
/// </summary>
void Timer::EndTimer()
{
	if (isStartTimer)
	{
		nowTime = prevTime = 0.0f;
		isStartTimer = false;
	}
}
/// <summary>
/// ���Ԃ̌v��
/// </summary>
/// <returns>true/false</returns>
bool Timer::CountTimer()
{
	if (isStartTimer)
	{
		nowTime = GetNowCount();
		//�ڕW���Ԃ��z���Ă�����true��Ԃ�
		if (nowTime - prevTime >= targetTime)
		{
			nowTime = prevTime = GetNowCount();
			return true;
		}
	}
	return false;
}
/// <summary>
/// �^�C�}�[�̕\��
/// </summary>
/// <param name="playerPos">�v���C���[�̂O�Ԗڂ̃t���[���̍��W</param>
void Timer::DrawNowTimer(VECTOR playerPos)
{
	//clsDx();
	//�v���C���[�̂O�Ԗڂ̃t���[���̃��[���h���W����ɃX�N���[�����W���o��
	//VECTOR screenPos = ConvWorldPosToScreenPos(playerPos);
	//DrawFormatString(static_cast<int>(screenPos.x), static_cast<int> ( screenPos.y), GetColor(255, 255, 255), "Time:%f", prevTime + targetTime - nowTime);
}