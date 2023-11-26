//===========================================================================
//@brief �^�C�g���N���X
//===========================================================================
#include"Title.h"
#include"Common.h"
#include"Load.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Title::Title()
{
	//������
	Init();
	//���[�h�N���X�̃C���X�^���X���擾
	auto& load = Load::GetInstance();
	//�摜�̃��[�h
	load.GetTitleData(&image);
	SetDrawScreen(GetActiveGraph());
}
/// <summary>
/// ������
/// </summary>
void Title::Init()
{
	//���W�̏�����
	escapeIconPos		= INIT_ESCAPE_ICON_POS;
	goIconPos			= INIT_GO_ICON_POS;
	briefingIconPos		= INIT_BRIEFING_ICON_POS;
	titlePos			= INIT_TITLE_POS;
	cursorPos			= INIT_CURSOR_POS_OF_GO	;
	briefingDataImgPos	= INIT_BRIEFING_DATA_POS;
	//�I�����Ă���A�C�R���̏�����
	nowSelectIconType = static_cast<int>(CursorType::GO);
	//�t���O�̏�����
	isSelectIcon	= false;
	isShowBriefing	= false;
	isTitleEnd		= false;
	isChangeScene	= false;
	isInputState	= false;
	//�摜�u�����h
	alpha			= MIN_ALPHA_VALUE;
	floatY			= INIT_Y_POS;
	nowWaitCount	= INIT_WAIT_COUNT;
	floatYAddValue  = MAX_Y_VALUE;
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
Title::~Title()
{
}
/// <summary>
/// �X�V
/// </summary>
void Title::Update()
{
	FloatCursor();
	ChangeCursor();
}
/// <summary>
/// �`��
/// </summary>
void Title::Draw()
{
	DrawMoveBackGround();
	//�摜�̕`��
	DrawGraph(escapeIconPos.x	, escapeIconPos.y		, image[static_cast<int>(ImageType::ESCAPE_ICON)]	, TRUE);//ESCAPE�A�C�R���摜
	DrawGraph(goIconPos.x		, goIconPos.y			, image[static_cast<int>(ImageType::GO_ICON)]		, TRUE);//GO�A�C�R���摜
	DrawGraph(briefingIconPos.x	, briefingIconPos.y		, image[static_cast<int>(ImageType::BRIEFING_ICON)]	, TRUE);//�����A�C�R���摜
	DrawGraph(titlePos.x		, titlePos.y			, image[static_cast<int>(ImageType::TITLE_TEXT)]		, TRUE);//�^�C�g�������摜
	DrawGraph(cursorPos.x		, cursorPos.y + floatY	, image[static_cast<int>(ImageType::CURSOR)]			, TRUE);//�J�[�\���摜
	//�A�C�R����I�����Ă�����
	if (isSelectIcon)
	{
		//�����A�C�R����I�����Ă�����
		if (isShowBriefing)
		{
			//��ʂ����X�ɈÂ�����i�A���t�@�l��萔�܂ő���������j
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			DrawGraph(ORIGIN_POS_2D.x, ORIGIN_POS_2D.y, image[static_cast<int>(ImageType::BACKGROUND)], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MIN_ALPHA_VALUE);

			//�A���t�@�l����
			alpha += ADD_ALPHA_VALUE;
			//�����A���t�@�l���ő�A���t�@�l�𒴂��Ă�����
			if (alpha > MAX_ALPHA_VALUE)
			{
				alpha = MAX_ALPHA_VALUE;
				DrawGraph(briefingDataImgPos.x, briefingDataImgPos.y, image[static_cast<int>(ImageType::BRIEFING_DATA)], TRUE);
			}
		}
		else
		{
			//�A���t�@�l����
			alpha -= ADD_ALPHA_VALUE;
			//�����A���t�@�l���ő�A���t�@�l�𒴂��Ă�����
			if (alpha < MIN_ALPHA_VALUE)
			{
				alpha = MIN_ALPHA_VALUE;
				//�t���O������
				isSelectIcon = false;
			}
		}
	}
}
/// <summary>
/// �J�[�\�����W�̕ύX
/// </summary>
void Title::ChangeCursor()
{
	if (isInputState)
	{
		nowWaitCount++;
		if (nowWaitCount == MAX_WAIT_COUNT)
		{
			nowWaitCount = INIT_WAIT_COUNT;
			isInputState = false;
		}
	}
	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//�A�C�R�����I�΂�Ă��Ȃ�������
	if (!isSelectIcon)
	{
		//��
		if (!isInputState && input & PAD_INPUT_LEFT || !isInputState && CheckHitKey(KEY_INPUT_LEFT))
		{
			//�������[�̃A�C�R������͂��Ă��Ȃ�������
			if (nowSelectIconType != static_cast<int>(CursorType::ESCAPE))
			{
				nowSelectIconType--;
			}
			isInputState = true;
		}
		//�E
		if (!isInputState && input & PAD_INPUT_RIGHT || !isInputState && CheckHitKey(KEY_INPUT_RIGHT))
		{
			//�����E�[�̃A�C�R������͂��Ă��Ȃ�������
			if (nowSelectIconType != static_cast<int>(CursorType::BRIEFING))
			{
				nowSelectIconType++;
			}
			isInputState = true;
		}
	}
	//����{�^���������ꂽ��
	if (input & PAD_INPUT_2 || CheckHitKey(KEY_INPUT_RETURN))
	{
		isSelectIcon = true;
		isInputState = true;
	}

		//�����A�C�R���̏�Ō���{�^���������ꂽ��
		if (!isShowBriefing)
		{
			if (isSelectIcon && nowSelectIconType == static_cast<int>(CursorType::BRIEFING))
			{
				isShowBriefing = true;
			}
		}
		//�������\������A�{�^���������ꂽ����������
		else if (isShowBriefing)
		{
			if (!isInputState && input & PAD_INPUT_1 || !isInputState && CheckHitKey(KEY_INPUT_BACK))
			{
				isShowBriefing = false;
				isSelectIcon = false;
				isInputState = true;
			}
		}
		//���݃A�C�R����I�𒆂��I�����Ă���A�C�R����ESCAPE��������
		if (isSelectIcon && nowSelectIconType == static_cast<int>(CursorType::ESCAPE))
		{
			//�^�C�g����ʂ��I�����邩
			//isGameEnd = true;
			//���������ƃt���[�Y����̂ŁA�R�����g�A�E�g����
			//�Z���N�g�t���O������
			DxLib_End();
			isSelectIcon = false;
		}
		//���݃A�C�R����I�𒆂��I�����Ă���A�C�R����GO��������
		if (isSelectIcon && nowSelectIconType == static_cast<int>(CursorType::GO))
		{
			isChangeScene = true;
		}
	//�����J�[�\���^�C�v��ESCAPE��������
	if (nowSelectIconType == static_cast<int>(CursorType::ESCAPE))
	{
		cursorPos = INIT_CURSOR_POS_OF_ESCAPE;
	}
	//�����J�[�\���^�C�v��GO��������
	else if (nowSelectIconType == static_cast<int>(CursorType::GO))
	{
		cursorPos = INIT_CURSOR_POS_OF_GO;
	}
	//�����J�[�\���^�C�v��BRIEFING��������
	else if (nowSelectIconType == static_cast<int>(CursorType::BRIEFING))
	{
		cursorPos = INIT_CURSOR_POS_OF_BRIEFING;
	}
}
/// <summary>
/// �����w�i�̕`��
/// </summary>
void Title::DrawMoveBackGround()
{
	//�`��ʒu�̍X�V
	for (int i = 0; i < MAX_BACKGROUND_NUM; i++)
	{
		//�w�i�ʂō��W���v���X����
		moveBackGroundPos[i].x -= MOVE_BACKGROUND_SPEED[i];
		//�����摜���Q���`��
		DrawExtendGraph(moveBackGroundPos[i].x, moveBackGroundPos[i].y, moveBackGroundPos[i].x + WINDOW_WIDTH, moveBackGroundPos[i].y+ WINDOW_HEIGHT, image[i + MAX_BACKGROUND_NUM], TRUE);
		DrawExtendGraph(moveBackGroundPos[i].x + WINDOW_WIDTH, moveBackGroundPos[i].y, moveBackGroundPos[i].x + WINDOW_WIDTH + WINDOW_WIDTH, moveBackGroundPos[i].y + WINDOW_HEIGHT, image[i + MAX_BACKGROUND_NUM], TRUE);
		//�������W���萔�𒴂�����O�ɏ���������
		if (moveBackGroundPos[i].x < -MAX_BACKGROUND_POS)
		{
			moveBackGroundPos[i].x = INIT_X_POS;
		}
	}
}
void Title::FloatCursor()
{
	//����Add������������
	if (floatYAddValue == MAX_Y_VALUE)
	{
		if (floatY > MAX_Y_POS)
		{
			floatYAddValue = MIN_Y_VALUE;
		}
	}
	else
	{
		if (floatY < MIN_Y_POS)
		{
			floatYAddValue = MAX_Y_VALUE;
		}
	}
	floatY += floatYAddValue;
}