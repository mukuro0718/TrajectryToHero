//===========================================================================
//@brief �^�C�g���N���X
//===========================================================================
#include"Title.h"
#include"TutorialStage.h"
#include"Camera.h"
#include"SwordGirl.h"
#include"Common.h"
#include"OperationUI.h"
#include"Load.h"
#include"TutorialEnemy.h"
#include"Collision.h"
#include"StatusUpParticle.h"

const int Title::FONT_COLOR = GetColor(200, 200, 200);
/// <summary>
/// �R���X�g���N�^
/// </summary>
Title::Title()
	:startIconAlpha(MIN_ALPHA_VALUE)
	, titleAlpha(MAX_ALPHA_VALUE)
	, stageNameAlpha(MIN_ALPHA_VALUE)
	, addAlphaValue(ADD_ALPHA_VALUE)
	, frameCount(INIT_FRAME_COUNT)
	, isChangeAddAlpha(false)
	, isFrameCount(false)
	, isDrawTitleEnd(false)
	, isDrawTitleFinish(false)
	, isTitleEnd(false)
	, isDrawStageName(false)
	, isChangeScene(false)
	, stage(nullptr)
	, camera(nullptr)
	, player(nullptr)
	, opeUI(nullptr)
	, statusUpParticle(nullptr)
	, tutorialProgress(0)
	, isChange(false)
	, textAlpha(MIN_ALPHA_VALUE)
	, progressFrameCount(0)
	, destroyEnemy(false)
	, enemy(nullptr)
	, collision(nullptr)
	, prevPlayerAtk(0.0f)
	, isDescription(false)
	, strongUI(0)
{
	//���[�h�N���X�̃C���X�^���X���擾
	auto& load = Load::GetInstance();
	//�摜�̃��[�h
	load.GetTitleData(&titleData, &fontData, &playerData, &enemyData, &stageData);
	load.GetStrongerUIData(&strongUI);
	stage = new TutorialStage(stageData);
	camera = new Camera();
	player = new SwordGirl(playerData[static_cast<int>(PlayerData::MODEL)], playerData[static_cast<int>(PlayerData::FRAME)], playerData[static_cast<int>(PlayerData::HP)], playerData[static_cast<int>(PlayerData::EXP)], fontData[static_cast<int>(FontType::TEXT)]);
	opeUI = new OperationUI();
	enemy = new TutorialEnemy(MV1LoadModel("Data/Model/Enemy/WeakEnemy.mv1"));
	collision = new Collision();
	statusUpParticle = new StatusUpParticle(player->GetLv());
	prevPlayerAtk = player->GetAtk();
	//������
	Init();
}
/// <summary>
/// ������
/// </summary>
void Title::Init()
{
	player->Init();
	enemy->Init();
	camera->Init(player->GetPos());
	for (int i = 0; i < PROGRESS_NUM; i++)
	{
		isProgress.push_back(false);
	}
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
Title::~Title()
{
	if (player)
	{
		delete(player);
		player = nullptr;
	}
	if (camera)
	{
		delete(camera);
		camera = nullptr;
	}
	if (enemy)
	{
		delete(enemy);
		enemy = nullptr;
	}
	if (stage)
	{
		delete(stage);
		stage = nullptr;
	}
	if (opeUI)
	{
		delete(opeUI);
		opeUI = nullptr;
	}
	if (collision)
	{
		delete(collision);
		collision = nullptr;
	}
}
/// <summary>
/// �^�C�g�����j���[�p�A���t�@�l�ύX
/// </summary>
void Title::ChangeTitleAlphaValue()
{
	int tmpAlpha = 0;
	if (!isDrawTitleFinish)
	{
		tmpAlpha = startIconAlpha;
	}
	if(isDrawTitleFinish && !isDrawTitleEnd)
	{
		tmpAlpha = titleAlpha;
	}
	if (isDrawStageName)
	{
		tmpAlpha = stageNameAlpha;
	}

	tmpAlpha += addAlphaValue;

	if (tmpAlpha >= MAX_ALPHA_VALUE)
	{
		if (isChangeAddAlpha)
		{
			addAlphaValue = -ADD_ALPHA_VALUE;
			isChangeAddAlpha = false;
		}
		else
		{
			tmpAlpha = MAX_ALPHA_VALUE;
			isFrameCount = true;
		}
	}

	if (tmpAlpha <= MIN_ALPHA_VALUE)
	{
		if (isChangeAddAlpha)
		{
			addAlphaValue = ADD_ALPHA_VALUE;
			isChangeAddAlpha = false;
		}
		else
		{
			tmpAlpha = MIN_ALPHA_VALUE;
			isFrameCount = true;
		}
	}

	if (isFrameCount)
	{
		frameCount++;
		if (frameCount == MAX_FRAME_COUNT)
		{
			isFrameCount = false;
			isChangeAddAlpha = true;
			frameCount = INIT_FRAME_COUNT;
		}
	}
	if (!isDrawTitleFinish)
	{
		startIconAlpha = tmpAlpha;
	}
	if (isDrawTitleFinish && !isDrawTitleEnd)
	{
		titleAlpha = tmpAlpha;
	}
	if (isDrawStageName)
	{
		stageNameAlpha = tmpAlpha;
	}

}
/// <summary>
/// �X�V
/// </summary>
void Title::Update()
{
	FragChanger();
	//�^�C�g���p�̃A���t�@�l��ύX����i�r������g��Ȃ��j
	ChangeTitleAlphaValue();
	//�n�ʁA���΁A�Q�[�g�̍X�V
	stage->Update();
	//�J�����̍X�V
	camera->Update(player->GetPos());
	//���΃��j���[��\�����Ă����ꍇ�́A�ʂ�Ȃ��悤�ɂ���
	if (!player->GetIsShowStatusMenu())
	{
		//���G���Ԃ̌v��
		player->CountInvincibleTimer();
		//�����^�C�g���ƃX�e�[�W���̕`�悪�I�����Ă�����
		if (isDrawTitleEnd)
		{
			//�v���C���[�̈ړ�
			player->Move(camera->GetCameraToPlayer());
			//�v���C���[�̍U��
			player->Attack();
			OnDamage();
			FixMoveVec();
		}
		//�v���C���[�̍X�V
		player->Update();
		enemy->Update();
		//�������UI�̕\��������
		opeUI->Update(player->GetIsMove());
		//�v���C���[UI�̍X�V
		player->UpdateUI();
		//�A�j���[�V�����̕ύX
		player->AnimChange();
	}
	//�X�e�[�^�X�̍X�V
	player->StatusUpdate(stage->GetBonfirePos());
	float atk = player->GetAtk();
	if (atk != prevPlayerAtk && !player->GetIsShowStatusMenu())
	{
		enemy->OnIsDamage();
	}
	if(!player->GetIsShowStatusMenu())
	{
		player->TutorialStatusReset();
	}
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		isChangeScene = true;
	}
	statusUpParticle->Update(player->GetPos(), player->GetIsBonfireMenu(), player->GetLv());

}
/// <summary>
/// �`��
/// </summary>
void Title::Draw()
{
	stage->Draw();
	enemy->Draw(player->GetLv());
	enemy->DrawShadow(stage->GetGroundModelHandle());
	player->Draw();
	player->DrawShadow(stage->GetGroundModelHandle(),player->GetPos(),1000.0f,20.0f);
	player->DrawUI();
	opeUI->Draw(stage->GetBonfirePos(), player->GetPos());
	DrawTutorialText();
	statusUpParticle->Draw(player->GetIsBonfireMenu());
	player->DrawMenu();
	/*�^�C�g�����S�ƊJ�n�{�^���̕\��*/
	DrawTitle();
	DrawStageName();
	//DrawDetailedDescription();
	VECTOR gateToPlayer = VSub(stage->GetGatePos(), player->GetPos());
	gateToPlayer.y = 0.0f;
	float vecSize = VSize(gateToPlayer);
	if (vecSize < 60.0f)
	{
		//DrawExtendGraph(BOSS_UI_DRAW_RECT.lx, BOSS_UI_DRAW_RECT.ly, BOSS_UI_DRAW_RECT.rx, BOSS_UI_DRAW_RECT.ry, titleData[static_cast<int>(TitleData::BACKGROUND)], TRUE);
		DrawBox(BOSS_UI_DRAW_RECT.lx, BOSS_UI_DRAW_RECT.ly, BOSS_UI_DRAW_RECT.rx, BOSS_UI_DRAW_RECT.ry, GetColor(0,0,0),TRUE);
		DrawStringToHandle(TEXT_POS.x, TEXT_POS.y + 700, "�Q�[�g��������", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT)]);
		DrawExtendGraph(BUTTON_POS.lx + 20, BUTTON_POS.ly + 700, BUTTON_POS.rx + 20, BUTTON_POS.ry + 700, titleData[static_cast<int>(TitleData::A_BUTTON)], TRUE);
		int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		//B��������Ă�����U��
		if (input & PAD_INPUT_1)
		{
			isChangeScene = true;
		}
	}
}
/// <summary>
/// �^�C�g���`��
/// </summary>
void Title::DrawTitle()
{
	if (!isDrawTitleEnd)
	{
		if (!isDrawTitleFinish)
		{
			//�^�C�g�����S�̕`��
			DrawExtendGraph(TITLE_LOGO_POS.lx, TITLE_LOGO_POS.ly, TITLE_LOGO_POS.rx, TITLE_LOGO_POS.ry, titleData[static_cast<int>(TitleData::LOGO)], TRUE);
			//�X�^�[�g�A�C�R���iPRESS A BUTTON�j�̕`��
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, startIconAlpha);
			DrawStringToHandle(START_ICON_POS.x, START_ICON_POS.y, "PRESS A BUTTON", FONT_COLOR, fontData[static_cast<int>(FontType::PLAYER)]);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_ALPHA_VALUE);
			int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
			//B��������Ă�����U��
			if (input & PAD_INPUT_1)
			{
				isDrawTitleFinish = true;
				addAlphaValue = -ADD_ALPHA_VALUE;
			}
		}
		else
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, titleAlpha);
			DrawExtendGraph(TITLE_LOGO_POS.lx, TITLE_LOGO_POS.ly, TITLE_LOGO_POS.rx, TITLE_LOGO_POS.ry, titleData[static_cast<int>(TitleData::LOGO)], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_ALPHA_VALUE);
			if (titleAlpha <= MIN_ALPHA_VALUE)
			{
				isDrawTitleEnd = true;
				isDrawStageName = true;
				addAlphaValue = ADD_ALPHA_VALUE;
			}
		}
	}


}

void Title::DrawStageName()
{
	if (isDrawStageName)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, stageNameAlpha);
		DrawStringToHandle(TUTORIAL_LOGO_POS.x, TUTORIAL_LOGO_POS.y, "�`���[�g���A��", FONT_COLOR, fontData[static_cast<int>(FontType::LOGO)], TRUE);
		DrawLine(TUTORIAL_LOGO_LINE_POS.lx, TUTORIAL_LOGO_LINE_POS.ly, TUTORIAL_LOGO_LINE_POS.rx, TUTORIAL_LOGO_LINE_POS.ry,FONT_COLOR,15);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_ALPHA_VALUE);
		if (stageNameAlpha < MIN_ALPHA_VALUE)
		{
			isDrawStageName = false;
		}
	}
}
void Title::DrawDetailedDescription()
{
	if (isDrawText && isDescription)
	{
		int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		//B��������Ă�����U��
		if (input & PAD_INPUT_2)
		{
			isDescription = false;
		}
	}
}
void Title::DrawTutorialText()
{
	//�����p�̔w�i�摜�̕`��
	DrawBox(BACKGROUND_POS_FOR_DESCRIPTION.lx, BACKGROUND_POS_FOR_DESCRIPTION.ly, BACKGROUND_POS_FOR_DESCRIPTION.rx, BACKGROUND_POS_FOR_DESCRIPTION.ry, GetColor(0, 0, 0), TRUE);
	DrawStringToHandle(TEXT_POS_FOR_DESCRIPTION.x, TEXT_POS_FOR_DESCRIPTION.y, "�G��|���ƁA�o���l���擾�ł��܂��B\n���x�����オ��ƁA�X�e�[�^�X�|�C���g��\n�t�^����܂��B", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT_2)]);
	//�����p�̔w�i�摜�̕`��
	DrawExtendGraph(1390, 150, 1500, 230, strongUI, TRUE);
	DrawStringToHandle(TEXT_POS_FOR_DESCRIPTION.x + 70, TEXT_POS_FOR_DESCRIPTION.y + 100, "���̃}�[�N�����Ă���G��,\n���Ȃ��������x������̓G�ł��B\n�X�e�[�^�X���������Ē��݂܂��傤�B", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT_2)]);
	//�����p�̔w�i�摜�̕`��
	DrawStringToHandle(TEXT_POS_FOR_DESCRIPTION.x, TEXT_POS_FOR_DESCRIPTION.y + 200, "�����΂ŋx�ނƁA�̗͂��񕜂��邱�Ƃ�\n�ł��܂��B\n�܂����x���A�b�v���j���[��I������ƁA\n�X�e�[�^�X�|�C���g������ăX�e�[�^�X\n�������ł��܂��B", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT_2)]);
	//�����p�̔w�i�摜�̕`��
	DrawStringToHandle(TEXT_POS_FOR_DESCRIPTION.x, TEXT_POS_FOR_DESCRIPTION.y + 350, "���x�������ȏ�オ��ƁA�Q�[�g���o��\n���܂��B\n�Q�[�g��������ƃ{�X�킪�n�܂�̂ŁA\n�X�e�[�^�X���������Ē��݂܂��傤�B", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT_2)]);


	if (!isDrawStageName && isDrawTitleEnd)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, textAlpha);	
		//�e�L�X�g�����̕`��
		switch (tutorialProgress)
		{
		case static_cast<int>(TutorialProgress::MOVE):
			//�����p�̔w�i�摜�̕`��
			DrawBox(BACKGROUND_POS_FOR_TEXT.lx, BACKGROUND_POS_FOR_TEXT.ly, BACKGROUND_POS_FOR_TEXT.rx, BACKGROUND_POS_FOR_TEXT.ry, GetColor(0, 0, 0), TRUE);
			DrawStringToHandle(TEXT_POS.x, TEXT_POS.y, "�ړ�", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT)]);
			DrawExtendGraph(BUTTON_POS.lx, BUTTON_POS.ly, BUTTON_POS.rx, BUTTON_POS.ry, titleData[static_cast<int>(TitleData::L_STICK)], TRUE);
			//�v���C���[���ړ������玟�ɍs��
			if (isDrawText && player->GetIsMove())
			{
				isChange = true;
			}
			break;
		case static_cast<int>(TutorialProgress::CAMERA):
			//�����p�̔w�i�摜�̕`��
			DrawBox(BACKGROUND_POS_FOR_TEXT.lx, BACKGROUND_POS_FOR_TEXT.ly, BACKGROUND_POS_FOR_TEXT.rx, BACKGROUND_POS_FOR_TEXT.ry, GetColor(0, 0, 0), TRUE);
			DrawStringToHandle(TEXT_POS.x, TEXT_POS.y, "�J��������", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT)]);
			DrawExtendGraph(BUTTON_POS.lx, BUTTON_POS.ly, BUTTON_POS.rx, BUTTON_POS.ry, titleData[static_cast<int>(TitleData::R_STICK)], TRUE);
			//�J�����̃A���O�����ς���Ă����玟�ɍs��
			if (isDrawText && camera->GetAngleX() != 0.0f)
			{
				isChange = true;
			}
			break;
		case static_cast<int>(TutorialProgress::ATTACK):
			//�����p�̔w�i�摜�̕`��
			DrawBox(BACKGROUND_POS_FOR_TEXT.lx, BACKGROUND_POS_FOR_TEXT.ly, BACKGROUND_POS_FOR_TEXT.rx, BACKGROUND_POS_FOR_TEXT.ry, GetColor(0, 0, 0), TRUE);
			DrawStringToHandle(TEXT_POS.x, TEXT_POS.y, "�U��", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT)]);
			DrawExtendGraph(BUTTON_POS.lx, BUTTON_POS.ly, BUTTON_POS.rx, BUTTON_POS.ry, titleData[static_cast<int>(TitleData::X_BUTTON)], TRUE);
			//�v���C���[���U�������玟�ɍs��
			if (isDrawText && player->GetIsAttack())
			{
				isChange = true;
			}
			break;
		case static_cast<int>(TutorialProgress::DESTROY_ENEMY_1):
			//�����p�̔w�i�摜�̕`��
			DrawBox(BACKGROUND_POS_FOR_TEXT.lx, BACKGROUND_POS_FOR_TEXT.ly, BACKGROUND_POS_FOR_TEXT.rx, BACKGROUND_POS_FOR_TEXT.ry, GetColor(0, 0, 0), TRUE);
			DrawStringToHandle(TEXT_POS.x, TEXT_POS.y, "�G��|��", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT)]);
			//�G�����S�����玟�ɍs��
			if (isDrawText && enemy->GetIsDeath())
			{
				isChange = true;
			}
			break;
		case static_cast<int>(TutorialProgress::CAMPFIRE_2):
			//�����p�̔w�i�摜�̕`��
			DrawBox(BACKGROUND_POS_FOR_TEXT.lx, BACKGROUND_POS_FOR_TEXT.ly, BACKGROUND_POS_FOR_TEXT.rx, BACKGROUND_POS_FOR_TEXT.ry, GetColor(0, 0, 0), TRUE);
			DrawStringToHandle(TEXT_POS.x, TEXT_POS.y, "������΂ŋx��", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT)]);
			//�U���͂��A�b�v���Ă����玟�ɍs��
			if (isDrawText && player->GetIsShowStatusMenu())
			{
				isChange = true;
			}
			break;
		case static_cast<int>(TutorialProgress::STATUS_UP):
				//�����p�̔w�i�摜�̕`��
				DrawBox(BACKGROUND_POS_FOR_TEXT.lx + 20, BACKGROUND_POS_FOR_TEXT.ly + 700, BACKGROUND_POS_FOR_TEXT.rx + 20, BACKGROUND_POS_FOR_TEXT.ry + 700, GetColor(0, 0, 0), TRUE);
				//�G�����S���Ă����玟�ɍs��
				DrawStringToHandle(TEXT_POS.x + 120, TEXT_POS.y + 700, "�U���͂��������Ă��������B", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT)]);
				if (isDrawText && !enemy->GetIsDamage())
				{
					isChange = true;
				}
			break;
		case static_cast<int>(TutorialProgress::DESTROY_ENEMY_2):
				//�����p�̔w�i�摜�̕`��
				DrawBox(BACKGROUND_POS_FOR_TEXT.lx, BACKGROUND_POS_FOR_TEXT.ly, BACKGROUND_POS_FOR_TEXT.rx, BACKGROUND_POS_FOR_TEXT.ry, GetColor(0, 0, 0), TRUE);
				//�G�����S���Ă����玟�ɍs��
				DrawStringToHandle(TEXT_POS.x, TEXT_POS.y, "�G��|���B", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT)]);
				if (isDrawText&& enemy->GetIsDeath())
				{
					isChange = true;
					isDescription = true;
				}
			break;
		case static_cast<int>(TutorialProgress::GATE_2):
			//�����p�̔w�i�摜�̕`��
			DrawBox(BACKGROUND_POS_FOR_TEXT.lx, BACKGROUND_POS_FOR_TEXT.ly, BACKGROUND_POS_FOR_TEXT.rx, BACKGROUND_POS_FOR_TEXT.ry, GetColor(0, 0, 0), TRUE);
			DrawStringToHandle(TEXT_POS.x, TEXT_POS.y, "�Q�[�g��������B", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT)]);
			if (isDrawText && stage->GetIsShowGate())
			{
				isChange = true;
			}
			break;
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_ALPHA_VALUE);
	}
}
/// <summary>
/// �t���O��ύX����
/// </summary>
void Title::FragChanger()
{
	if (!isDrawStageName && isDrawTitleEnd)
	{
		//�ŏ��ɏ��X�ɕ`�悳���
		if (!isDrawText)
		{
			//�A���t�@�l�𑝉�������
			textAlpha += ADD_ALPHA_VALUE;
			//�����ő�l�ɒB���Ă�����ő�l�𒴂��Ȃ��悤�ɂ���
			if (textAlpha >= MAX_ALPHA_VALUE)
			{
				textAlpha = MAX_ALPHA_VALUE;
				//�A���t�@�l���ő�ɂȂ�����isDrawText�t���O�𗧂Ă�
				isDrawText = true;
			}
		}
		//�t���O�������Ă���Ƃ��Ɏw��̃A�N�V���������ꂽ�珙�X�ɕ`�������
		if (isChange)
		{
			textAlpha -= ADD_ALPHA_VALUE;
			//�����A���t�@�l���ŏ��l�����������ŏ��l�ɐݒ肷��
			if (textAlpha < MIN_ALPHA_VALUE)
			{
				textAlpha = MIN_ALPHA_VALUE;
				//�t���O������
				isDrawText = false;
				//�`���[�g���A���̐i�s�x��1�i�߂�
				tutorialProgress++;
				isChange = false;
			}
		}
	}
	//���ԂŃe�L�X�g�̕\����ύX���邽�߂̏���
	if (isDescription)
	{
		progressFrameCount++;
		if (progressFrameCount > 240)
		{
			progressFrameCount = 0;
			isProgress[tutorialProgress] = true;
			isDescription = false;
		}
	}
	if (tutorialProgress == static_cast<int>(TutorialProgress::GATE_2))
	{
		stage->OnIsShowGate();
	}
}
/// <summary>
/// �ړ��ʕ␳
/// </summary>
void Title::FixMoveVec()
{
	VECTOR fixVec = collision->CapsuleToCapsuleCollision(player->GetMoveVec(), player->GetPos(), enemy->GetPos(), player->GetCapsuleInfo().radius, enemy->GetRadius());
	player->FixMoveVec(fixVec);
}
/// <summary>
/// �_���[�W����
/// </summary>
void Title::OnDamage()
{
	if (player->GetIsAttack() && !enemy->GetIsDamage() && tutorialProgress == static_cast<int>(TutorialProgress::DESTROY_ENEMY_1) ||
		player->GetIsAttack() && !enemy->GetIsDamage() && tutorialProgress == static_cast<int>(TutorialProgress::DESTROY_ENEMY_2))
	{
		//�����蔻��`�F�b�N
		bool isHitEnemy = collision->OnDamage(false, enemy->GetIsDeath(), enemy->GetCapsuleInfo(), player->GetSphereInfo());
		//�����U�����������Ă�����
		if (isHitEnemy)
		{
			float exp = enemy->CalcHP( player->GetAtk(), player->GetPos());
			if (exp > 0)
			{
				player->CalcExp(exp);
				enemy->InitExpToGive();
			}
		}
	}
}