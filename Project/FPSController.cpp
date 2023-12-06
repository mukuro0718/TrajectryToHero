//===========================================================================
//@brief FPS�R���g���[���[�N���X
//===========================================================================

#include"FPSController.h"

const int FPSController::FONT_COLOR = GetColor(255,255,255);
using namespace std;

/// <summary>
/// �R���X�g���N�^
/// </summary>
FPSController::FPSController()
	:fps(0.0f)
	,startTime(0)
	,count(0)
{
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
FPSController::~FPSController()
{

}
/// <summary>
/// ������
/// </summary>
void FPSController::Init()
{
	fps = 0.0f;
	startTime = 0;
	count = 0;
}
/// <summary>
/// FPS�̕���
/// </summary>
void FPSController::Ave()
{
	//�J�E���g���O��������X�^�[�g�^�C����������
	if (count == 0)
	{
		startTime = GetNowCount();
	}
	//�J�E���g���ڕWFPS�ɂȂ�����
	if (count == static_cast<int>(SET_FPS))
	{
		//���݂̎������擾
		int nowTime = GetNowCount();
		//FPS�v�Z
		fps = 1000.0 / (static_cast<double>((nowTime - startTime)) / SET_FPS);
		//������
		startTime = 0;
		count = 0;
	}
	else
	{
		count++;
	}
}
/// <summary>
/// FPS�̕`��
/// </summary>
void FPSController::Draw()
{
#if _DEBUG
	//FPS�̕`��
	DrawFormatString(1650, 0, FONT_COLOR, "FPS:%lg", fps);
#endif // _DEBUG
}
/// <summary>
/// �ڕWFPS�ɂȂ�悤�ҋ@
/// </summary>
void FPSController::Wait()
{
	//���݂̌o�ߎ���
	int elapsedTime = GetNowCount() - startTime;
	//�ҋ@����
	int waitTime = count * 1000 / static_cast<int>(SET_FPS) - elapsedTime;
	if (waitTime > 0)
	{
		Sleep(waitTime);
	}
}
