//===========================================================================
//@brief �X�e�[�W�؂�ւ��N���X
//===========================================================================
#include"StageChanger.h"
#include"Timer.h"
#include"Load.h"
const VECTOR StageChanger::DRAW_GATEIMAGE_POS = { 0.0f,30.0f,0.0f };
const VECTOR StageChanger::VERTEX_NORM = VGet(0.0f, 0.0f, -1.0f);
const COLOR_U8 StageChanger::TRAIL_COLOR = GetColorU8(255, 255, 255, 255);

const VERTEX3D StageChanger::INIT_VERTEX =
{
	ORIGIN_POS,	//���W
	VERTEX_NORM,//�@��
	TRAIL_COLOR,//�f�B�t���[�Y�J���[
	TRAIL_COLOR,//�X�y�L�����J���[
	0.0f,		//�e�N�X�`�����W
	0.0f,		//�e�N�X�`�����W
	0.0f,		//�⏕�e�N�X�`�����W
	0.0f		//�⏕�e�N�X�`�����W
};

/// <summary>
/// �R���X�g���N�^
/// </summary>
StageChanger::StageChanger()
	: gateImage(0)
	, alpha(0)
	, backGroundAlpha(0)
	, alphaValue(6)
	, gateImageAngle(0.0f)
	, isFarm(true)//true
	, isBoss(false)//false
	//, isFarm(false)
	//, isBoss(true)
	, isChangeStage(true)
	, isGameOver(false)
	, isGameClear(false)
	, isGameEnd(false)
	, isDrawBlackBack(false)
	, isDrawAlert(false)
{
	//������
	Init();
	//�摜�̃��[�h
	auto& load = Load::GetInstance();
	load.GetStageChangeData(&image,&gateImage);
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
StageChanger::~StageChanger()
{
}
/// <summary>
/// ������
/// </summary>
void StageChanger::Init()
{
	//�^�C�}�[�C���X�^���X�̍쐬
	StayMaxAlphaTimer = new Timer();
	//�ڕW���Ԃ̃Z�b�g
	StayMaxAlphaTimer->Init(SET_STAY_TIMER);
	for (int i = 0; i < 4; i++)
	{
		vertexInfo.push_back(INIT_VERTEX);
	}
	vertexIndexAd.push_back(0);
	vertexIndexAd.push_back(1);
	vertexIndexAd.push_back(2);
	vertexIndexAd.push_back(0);
	vertexIndexAd.push_back(0);
	vertexIndexAd.push_back(0);
	SetFontSize(180);
}
/// <summary>
/// �X�e�[�W�؂�ւ����̉摜(FARM�ABOSS)�̕\��
/// </summary>
void StageChanger::DrawImageWhenSwitchingStage()
{
	//�X�e�[�W�؂�ւ��t���O�������Ă�����
	if (isChangeStage)
	{
		//�����A���t�@�l���ő�ɂȂ�����
		if (alphaValue > 0 && alpha >= 255)
		{
			//�^�C�}�[�̃X�^�[�g
			StayMaxAlphaTimer->StartTimer();

			//�^�C�}�[���ڕW���ԂɒB�����珈�����s��
			if (StayMaxAlphaTimer->CountTimer())
			{
				alphaValue = -6;
				StayMaxAlphaTimer->EndTimer();
			}
			//�҂��Ă��Ȃ�������
			else
			{
				alpha = 255;
			}
		}
		//�A���t�@�l�𑝂₷
		alpha += alphaValue;
		SetFontSize(180);
		//�u�����h����
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		//�`��摜�؂�ւ�
		if (isFarm)
		{
			DrawString(400, 300,"FARM STAGE", GetColor(200, 200, 200));
			DrawLine(300, 480, 1500, 480, GetColor(200, 200, 200),2);
		}
		else if (isBoss)
		{
			DrawString(400, 300, "BOSS STAGE", GetColor(200, 200, 200));
			DrawLine(300, 480, 1500, 480, GetColor(200, 200, 200), 2);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�����A���t�@�l���O�����ɂȂ����烋�[�v�𔲂���
		if (alpha < 0)
		{
			alpha = 0;
			alphaValue = 6;
			isChangeStage = false;
		}
	}
}
/// <summary>
/// �Q�[���N���A�̉摜�̕\��
/// </summary>
void StageChanger::DrawGameClear()
{

}
/// <summary>
/// �`��
/// </summary>
void StageChanger::Draw()
{
	//DrawGraph(0, 30, gateImage, true);
	//DrawBillboard3D(DRAW_GATEIMAGE_POS, 0.5f, 0.5f, IMG_SIZE, gateImageAngle * (DX_PI_F / 180), gateImage, TRUE);
	++gateImageAngle;
}
/// <summary>
/// �X�e�[�W�ړ����s�����ǂ���
/// </summary>
/// <param name="playerPos">�ύX�����v���C���[���W</param>
bool StageChanger::DrawAlert(const VECTOR _playerPos, const VECTOR _gatePos, const bool _isShowGate)
{
	VECTOR playerToGate = VSub(_playerPos,_gatePos);
	float vecSize = VSize(playerToGate);
	if (_isShowGate)
	{
		if (vecSize <= 30.0f)
		{
			DrawExtendGraph(BOSS_UI_DRAW_RECT.lx, BOSS_UI_DRAW_RECT.ly, BOSS_UI_DRAW_RECT.rx, BOSS_UI_DRAW_RECT.ry, image[static_cast<int>(ImageType::ALERT)], TRUE);
			int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
			if (input & PAD_INPUT_1)
			{
				isFarm = false;
				isChangeStage = true;
				isBoss = true;
				return true;
			}
		}
	}
	return false;
}
const void StageChanger::ChangeStage()
{
	isFarm = true;
	isBoss = false;
}