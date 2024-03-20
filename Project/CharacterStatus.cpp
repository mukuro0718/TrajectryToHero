#include"CharacterStatus.h"
#include "Common.h"
#include "SceneChanger.h"
#include "Load.h"
#include "Timer.h"
#include "CrackerParticle.h"
const int	 CharacterStatus::FONT_COLOR		= GetColor(200, 200, 150);
const int	 CharacterStatus::BLUE_FONT_COLOR	= GetColor(50, 50, 150);

/// <summary>
/// �R���X�g���N�^
/// </summary>
CharacterStatus::CharacterStatus()
	: lv(1.0f)
	, hp(0.0f)
	, atk(0.0f)
	, def(0.0f)
	, agi(0.0f)
	, expToGive(0.0f)
	, exp(0.0f)
	, needExp(0.0f)
	, maxHp(0.0f)
	, prevLv(0.0f)
	, isInputPad(false)
	, isShowLevelUpMenu(false)
	, nowSelectStatus(static_cast<int>(SelectStatus::ATK))
	, inputWaitTimer(nullptr)
	, nowSelectMenu(0)
	, isFinalSelectMenu(false)
	, isBonfireMenu(false)
	, atkUpCount(0)
	, agiUpCount(0)
	, defUpCount(0)
	, prevAtkUpCount(0)
	, prevAgiUpCount(0)
	, prevDefUpCount(0)
	, isLevelUp(false)
	, statusUpPoint(5)
	, prevStatusUpPoint(5)
	, isShowMenu(false)
	, particle(nullptr)
{
	auto& load = Load::GetInstance();
	inputWaitTimer = new Timer();
	particle = new CrackerParticle();
	//������
	Init();
	load.GetCharacterStatusData(&data);
	rectPos = { 200,200 };
	nowHighCursorPos = ATK_HIGH_CURSOR_POS;
	nowLowCursorPos = ATK_LOW_CURSOR_POS;
}
/// <summary>
/// ������
/// </summary>
const void CharacterStatus::Init()
{
	inputWaitTimer->Init(5);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CharacterStatus::~CharacterStatus()
{
	Delete();
}
const void CharacterStatus::InitTutorialStatus(const int _showCount)
{
	if (_showCount == 0)
	{
		lv = 1.0f;
		hp = 1.0f;//�̗͂̃Z�b�g
		atk = 0.0f;//�U���͂̃Z�b�g
		def = 1.0f;//�h��͂̃Z�b�g
		agi = 1.0f;	//�f�����̃Z�b�g
		expToGive = 20.0f;	//�|���ꂽ�Ƃ��^����o���l�̃Z�b�g(Enemy�p)
		exp = 20.0f;	//�o���l�̃Z�b�g
		needExp = 0.0f;	//���x���A�b�v�ɕK�v�Ȍo���l�iPlayer�p�j
		maxHp = hp;	//�ő�g�o
		prevLv = lv;	//�O�̃��x��
	}
	else
	{
		lv = 3.0f;
		hp = 1.0f;//�̗͂̃Z�b�g
		atk = 0.0f;//�U���͂̃Z�b�g
		def = 1.0f;//�h��͂̃Z�b�g
		agi = 1.0f;	//�f�����̃Z�b�g
		expToGive = 20.0f;	//�|���ꂽ�Ƃ��^����o���l�̃Z�b�g(Enemy�p)
		exp = 20.0f;	//�o���l�̃Z�b�g
		needExp = 0.0f;	//���x���A�b�v�ɕK�v�Ȍo���l�iPlayer�p�j
		maxHp = hp;	//�ő�g�o
		prevLv = lv;	//�O�̃��x��
	}
}
/// <summary>
/// �G���G�X�e�[�^�X�̏����ݒ�
/// </summary>
const void CharacterStatus::InitWeakEnemyStatus(const float _playerLv)
{
	/*�v���C���[�̃��x�������ƂɁA�X�e�[�^�X�𒲐�����*/
	//�����v���C���[���x����2�ȉ���������
	if (_playerLv <= 2.0f)
	{
		lv = 1.0f;
	}
	else if (_playerLv <= 3.0f)
	{
		lv = 2.0f;
	}
	else if (_playerLv <= 4.0f)
	{
		lv = 3.0f;
	}
	//�O��̃��x���ƍ��̃��x���̍������߂�
	int lvDif = static_cast<int>(lv - prevLv);
	//�������x�����P�i�X�^�[�g���j��������
	if (lv == 1)
	{
		//�X�e�[�^�X�̏����ݒ������
		hp			= 3.0f;//�̗͂̃Z�b�g
		atk			= 3.0f;//�U���͂̃Z�b�g
		def			= 1.0f;//�h��͂̃Z�b�g
		agi			= 1.0f;	//�f�����̃Z�b�g
		expToGive	= 20.0f;	//�|���ꂽ�Ƃ��^����o���l�̃Z�b�g(Enemy�p)
		exp			= 0.0f;	//�o���l�̃Z�b�g
		needExp		= 0.0f;	//���x���A�b�v�ɕK�v�Ȍo���l�iPlayer�p�j
		maxHp		= hp;	//�ő�g�o
		prevLv		= lv;	//�O�̃��x��
	}
	else if (lvDif == 1)
	{
		hp = maxHp;
		//�X�e�[�^�X��1.75�{����
		hp *= 1.5f ;//�̗͂̃Z�b�g
		atk *= 1.5f;//�U���͂̃Z�b�g
		def *= 1.5f;//�h��͂̃Z�b�g
		expToGive *= 1.5f;	//�|���ꂽ�Ƃ��^����o���l�̃Z�b�g(Enemy�p)
		maxHp = hp;	//�ő�g�o
		prevLv = lv;	//�O�̃��x��
	}
}
/// <summary>
/// ���{�X�X�e�[�^�X�̏����ݒ�
/// </summary>
const void CharacterStatus::InitStrongEnemyStatus(const float _playerLv)
{
	/*�v���C���[�̃��x�������ƂɁA�X�e�[�^�X�𒲐�����*/
	//�����v���C���[���x����8�ȉ���������
	if (_playerLv <= 8.0f)
	{
		lv = 10.0f;
	}
	else if (_playerLv <= 12.0f)
	{
		lv = 12.0f;
	}
	else if (_playerLv <= 15.0f)
	{
		lv = 13.0f;
	}
	//�O��̃��x���ƍ��̃��x���̍������߂�
	int lvDif = static_cast<int>(lv - prevLv);
	//�������x�����P�i�X�^�[�g���j��������
	if (lv == 10)
	{
		hp = 10.0f;		//�̗͂̃Z�b�g
		atk = 6.0f;			//�U���͂̃Z�b�g
		def = 3.0f;			//�h��͂̃Z�b�g
		agi = 1.0f;			//�f�����̃Z�b�g
		expToGive = 80.0f;	//�|���ꂽ�Ƃ��^����o���l�̃Z�b�g
		exp = 0;			//�o���l�̃Z�b�g
		needExp = 0.0f;
		maxHp = hp;
	}
	else if (lvDif == 1)
	{
		hp = maxHp;
		//�X�e�[�^�X��1.75�{����
		hp *= 1.5f;//�̗͂̃Z�b�g
		atk *= 1.5f;//�U���͂̃Z�b�g
		def *= 1.5f;//�h��͂̃Z�b�g
		expToGive *= 1.5f;	//�|���ꂽ�Ƃ��^����o���l�̃Z�b�g(Enemy�p)
		maxHp = hp;	//�ő�g�o
		prevLv = lv;	//�O�̃��x��
	}

}
/// <summary>
/// �{�X�X�e�[�^�X�̏����ݒ�
/// </summary>
const void CharacterStatus::InitBossEnemyStatus()
{
	lv			= 10.0f;	//���x���̃Z�b�g
	hp			= 30.0f;	//�̗͂̃Z�b�g
	atk			= 15.0f;	//�U���͂̃Z�b�g
	def			= 5.0f;	//�h��͂̃Z�b�g
	agi			= 0.8f;		//�f�����̃Z�b�g
	expToGive   = 10.0f;		//�|���ꂽ�Ƃ��^����o���l�̃Z�b�g
	exp			= 0.0f;		//�o���l�̃Z�b�g
	needExp     = 0.0f;
	maxHp       = hp;
}

/// <summary>
/// �v���C���[�X�e�[�^�X�̏����ݒ�
/// </summary>
const void CharacterStatus::InitPlayerStatus()
{
	lv			= 1.0f;	//���x���̃Z�b�g
	hp			= 30.0f;//�̗͂̃Z�b�g
	atk			= 1.0f;	//�U���͂̃Z�b�g
	def			= 1.0f;	//�h��͂̃Z�b�g
	agi			= 1.0f;	//�f�����̃Z�b�g
	expToGive	= 0.0f;	//�|���ꂽ�Ƃ��^����o���l�̃Z�b�g
	exp			= 0.0f;	//�o���l�̃Z�b�g
	needExp		= 10.0f;//�K�v�Ȍo���l�̃Z�b�g
	maxHp		= hp;	//�ő�HP�̃Z�b�g
	prevLv		= lv;	//�O�̃��x���̐ݒ�
	//lv			= 1.0f;	//���x���̃Z�b�g
	//hp			= 100.0f;//�̗͂̃Z�b�g
	//atk			= 6.0f;	//�U���͂̃Z�b�g
	//def			= 10.0f;	//�h��͂̃Z�b�g
	//agi			= 3.0f;	//�f�����̃Z�b�g
	//expToGive	= 0.0f;	//�|���ꂽ�Ƃ��^����o���l�̃Z�b�g
	//exp			= 0.0f;	//�o���l�̃Z�b�g
	//needExp		= 10.0f;//�K�v�Ȍo���l�̃Z�b�g
	//maxHp		= hp;	//�ő�HP�̃Z�b�g
	//prevLv		= lv;	//�O�̃��x���̐ݒ�
}
/// <summary>
/// �̗͉�
/// </summary>
const void CharacterStatus::PhysicalRecovery()
{
	hp = maxHp;
}
/// <summary>
/// HP�v�Z
/// </summary>
const float CharacterStatus::CalcHP(const float _atk)
{
	hp -= _atk / def;
	if (hp <= 0)
	{
		return expToGive;
	}
	return 0.0f;
}
/// <summary>
/// �^����o���l�̏�����
/// </summary>
const void CharacterStatus::InitExpToGive()
{
	expToGive = 0.0f;
}
/// <summary>
/// HP�v�Z
/// </summary>
const void CharacterStatus::CalcExp(const float _expToGive)
{
	if (lv != MAX_LV)
	{
		//�o���l�𑫂�
		exp += _expToGive;
		//�����o���l�ʂ����x���A�b�v�ɕK�v�Ȍo���l�ʂ𒴂��Ă�����
		if (exp >= needExp)
		{
			//���x���A�b�v
			++lv;
			//�o���l�ʂ̏�����
			exp -= needExp;
			//���ɕK�v�Ȍo���l�ʂ�ݒ�
			needExp = lv * 10;
		}
	}
	else
	{
		exp = 0.0f;
	}
}
/// <summary>
/// �摜�n���h���A�N���X�C���X�^���X�̍폜
/// </summary>
const void CharacterStatus::Delete()
{
	//�C���X�^���X�̍폜
	if (inputWaitTimer)
	{
		delete(inputWaitTimer);
		inputWaitTimer = nullptr;
	}
	//�C���X�^���X�̍폜
	if (particle)
	{
		delete(particle);
		particle = nullptr;
	}
}
/// <summary>
/// �X�V
/// </summary>
const void CharacterStatus::Update(const bool _isShowMenu)
{
	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	
	if (_isShowMenu && !isShowMenu)
	{
		statusUpPoint = static_cast<int>(lv) - static_cast<int>(prevLv);
		if (!isInputPad)
		{
			if (input & PAD_INPUT_1)
			{
				isShowMenu = true;
				isBonfireMenu = true;
				isLevelUp = false;
				isInputPad = true;
			}
		}
	}
		particle->Update();
		UpdateBonfireMenu();
		UpdateLevelUpMenu();
}
/// <summary>
/// �`��
/// </summary>
const void CharacterStatus::Draw()
{
	DrawBonfireMenu();
	DrawLevelUpMenu();
}
const void CharacterStatus::UpdateBonfireMenu()
{
	//�L�[�{�[�h�܂���XInput�̃Q�[���p�b�g�̓��͂��󂯕t����
	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//������΃��j���[�̕\��
	if (isBonfireMenu)
	{
		//�������̓t���O�������Ă��Ȃ�������
		if (!isInputPad)
		{
			//��������͂��󂯕t������
			if (input & PAD_INPUT_UP)
			{
				//���ݑI�����Ă��郁�j���[��؂�ւ���
				switch (nowSelectMenu)
				{
				case static_cast<int>(SelectBonfireMenu::BACK_TO_THE_GAME):
					//���ݑI�����Ă��郁�j���[��ύX����
					nowSelectMenu = static_cast<int>(SelectBonfireMenu::BACK_TO_THE_GAME);
					//�����\���p���W��ύX����
					rectPos = GAME_POS;
					break;
				case static_cast<int>(SelectBonfireMenu::LEVEL_UP):
					nowSelectMenu = static_cast<int>(SelectBonfireMenu::BACK_TO_THE_GAME);
					rectPos = GAME_POS;
					break;
				}
				isInputPad = true;
			}
			// ����
			if (input & PAD_INPUT_DOWN)
			{
				switch (nowSelectMenu)
				{
				case static_cast<int>(SelectBonfireMenu::BACK_TO_THE_GAME):
					nowSelectMenu = static_cast<int>(SelectBonfireMenu::LEVEL_UP);
					rectPos = LEVEL_POS;
					break;
				case static_cast<int>(SelectBonfireMenu::LEVEL_UP):
					nowSelectMenu = static_cast<int>(SelectBonfireMenu::LEVEL_UP);
					rectPos = LEVEL_POS;
					break;
				}
				isInputPad = true;
			}
			//����A�{�^���������ꂽ��
			if (input & PAD_INPUT_1)
			{
				//�ŏI���̓t���O�𗧂Ă�
				isFinalSelectMenu = true;
			}
			if (input & PAD_INPUT_2)
			{
				isLevelUp = false;
				isBonfireMenu = false;
				isFinalSelectMenu = false;
				isShowMenu = false;
				isInputPad = true;
			}
		}
	}
	//�����������͂��󂯕t���Ă��Ȃ�������
	if (input == 0)
	{
		//���̓t���O������
		isInputPad = false;
	}
	//�����ŏI���̓t���O�������Ă�����
	if (isFinalSelectMenu)
	{
		switch (nowSelectMenu)
		{
		case static_cast<int>(SelectBonfireMenu::BACK_TO_THE_GAME):
			isLevelUp = false;
			isBonfireMenu = false;
			isFinalSelectMenu = false;
			isShowMenu = false;
			isInputPad = true;
			break;
		case static_cast<int>(SelectBonfireMenu::LEVEL_UP):
			isLevelUp = true;
			isBonfireMenu = false;
			isFinalSelectMenu = false;
			prevStatusUpPoint = statusUpPoint;
			break;
		}
		isInputPad = true;
	}
}
/// <summary>
/// �I�����Ă���X�e�[�^�X�̏㏸
/// </summary>
const void CharacterStatus::DrawBonfireMenu()
{
	if (isBonfireMenu)
	{
		DrawGraph(menuPos.x, menuPos.y, data[static_cast<int>(DataType::BONFIRE_MENU)], TRUE);
		DrawGraph(highCursorPos.x, highCursorPos.y, data[static_cast<int>(DataType::CURSOR)], TRUE);
		DrawRotaGraph(lowCursorPos.x, lowCursorPos.y, 1.0, DX_PI_F, data[static_cast<int>(DataType::CURSOR)], TRUE);
		DrawGraph(rectPos.x, rectPos.y, data[static_cast<int>(DataType::SELECT_RECT)], TRUE);
	}
}
const void CharacterStatus::TutorialStatusReset()
{
	if (atk < 2.0f && !isShowLevelUpMenu)
	{
		statusUpPoint = 1;
		atk = 1.0f;
		agi = 1.0f;
		def = 1.0f;
		atkUpCount = 0;
		agiUpCount = 0;
		defUpCount = 0;
		prevAtkUpCount = atkUpCount;
		prevAgiUpCount = agiUpCount;
		prevDefUpCount = defUpCount;
		prevStatusUpPoint = statusUpPoint;
		prevLv = 1;
	}
}
const void CharacterStatus::UpdateLevelUpMenu()
{
	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (isLevelUp)
	{
		if (!isInputPad)
		{
			if (input & PAD_INPUT_RIGHT)
			{
				switch (nowSelectStatus)
				{
				case static_cast<int>(SelectStatus::ATK):
					nowSelectStatus = static_cast<int>(SelectStatus::AGI);
					nowHighCursorPos = AGI_HIGH_CURSOR_POS;
					nowLowCursorPos = AGI_LOW_CURSOR_POS;
					break;
				case static_cast<int>(SelectStatus::AGI):
					nowSelectStatus = static_cast<int>(SelectStatus::DEF);
					nowHighCursorPos = DEF_HIGH_CURSOR_POS;
					nowLowCursorPos = DEF_LOW_CURSOR_POS;
					break;
				case static_cast<int>(SelectStatus::DEF):
					nowSelectStatus = static_cast<int>(SelectStatus::DEF);
					nowHighCursorPos = DEF_HIGH_CURSOR_POS;
					nowLowCursorPos = DEF_LOW_CURSOR_POS;
					break;
				}
				isInputPad = true;
			}
			if (input & PAD_INPUT_LEFT)
			{
				switch (nowSelectStatus)
				{
				case static_cast<int>(SelectStatus::ATK):
					nowSelectStatus = static_cast<int>(SelectStatus::ATK);
					nowHighCursorPos = ATK_HIGH_CURSOR_POS;
					nowLowCursorPos = ATK_LOW_CURSOR_POS;
					break;
				case static_cast<int>(SelectStatus::AGI):
					nowSelectStatus = static_cast<int>(SelectStatus::ATK);
					nowHighCursorPos = ATK_HIGH_CURSOR_POS;
					nowLowCursorPos = ATK_LOW_CURSOR_POS;
					break;
				case static_cast<int>(SelectStatus::DEF):
					nowSelectStatus = static_cast<int>(SelectStatus::AGI);
					nowHighCursorPos = AGI_HIGH_CURSOR_POS;
					nowLowCursorPos = AGI_LOW_CURSOR_POS;
					break;
				}
				isInputPad = true;
			}
			if (statusUpPoint != 0)
			{
				if (input & PAD_INPUT_UP)
				{
					switch (nowSelectStatus)
					{
					case static_cast<int>(SelectStatus::ATK):
						if (atkUpCount != MAX_ATK_UP_COUNT)
						{
							atkUpCount++;
							statusUpPoint--;
						}
						break;
					case static_cast<int>(SelectStatus::AGI):
						if (agiUpCount != MAX_AGI_UP_COUNT)
						{
							agiUpCount++;
							statusUpPoint--;
						}
						break;
					case static_cast<int>(SelectStatus::DEF):
						if (defUpCount != MAX_DEF_UP_COUNT)
						{
							defUpCount++;
							statusUpPoint--;
						}
						break;
					}
					isInputPad = true;
				}
			}
			if (input & PAD_INPUT_DOWN)
			{
				switch (nowSelectStatus)
				{
				case static_cast<int>(SelectStatus::ATK):
					if (atkUpCount != prevAtkUpCount)
					{
						atkUpCount--;
						statusUpPoint++;
					}
					break;
				case static_cast<int>(SelectStatus::AGI):
					if (agiUpCount != prevAgiUpCount)
					{
						agiUpCount--;
						statusUpPoint++;
					}
					break;
				case static_cast<int>(SelectStatus::DEF):
					if (defUpCount != prevDefUpCount)
					{
						defUpCount--;
						statusUpPoint++;
					}
					break;
				}
				isInputPad = true;
			}

			//����
			if (input & PAD_INPUT_1)
			{
				bool isParticle[3] = { false };
				for (int i = 0; i < atkUpCount - prevAtkUpCount; i++)
				{
					isParticle[0] = true;
					atk += 3.0f;
					prevLv++;
				}
				for (int i = 0; i < agiUpCount - prevAgiUpCount; i++)
				{
					isParticle[1] = true;
					agi += 1.0f;
					prevLv++;
				}
				for (int i = 0; i < defUpCount - prevDefUpCount; i++)
				{
					isParticle[2] = true;
					def += 3.0f;
					prevLv++;
				}
				particle->Init(isParticle[0], isParticle[1], isParticle[2]);
				prevAtkUpCount = atkUpCount;
				prevAgiUpCount = agiUpCount;
				prevDefUpCount = defUpCount;
				prevStatusUpPoint = statusUpPoint;
				//prevLv = lv;
			}
			//�߂�
			if (input & PAD_INPUT_2)
			{
				statusUpPoint = prevStatusUpPoint;
				atkUpCount = prevAtkUpCount;
				agiUpCount = prevAgiUpCount;
				defUpCount = prevDefUpCount;
				isLevelUp = false;
				isBonfireMenu = true;
				isInputPad = true;
			}
		}
	}
}
/// <summary>
/// �A�C�R���̑I���i�J�[�\���̔ԍ���؂�ւ���j
/// </summary>
const void CharacterStatus::DrawLevelUpMenu()
{
	if (isLevelUp)
	{
		DrawExtendGraph(BACKGROUND_POS.lx, BACKGROUND_POS.ly, BACKGROUND_POS.rx, BACKGROUND_POS.ry,data[static_cast<int>(DataType::BACK_GROUND)],TRUE);

		particle->Draw();

		DrawFormatString(TEXT_POS.x, TEXT_POS.y,  FONT_COLOR, "�X�e�[�^�X�A�b�v       �X�e�[�^�X�|�C���g:%d\n�㏸������X�e�[�^�X��I��ł�������",statusUpPoint );
		DrawExtendGraph(ATK_POS.lx, ATK_POS.ly, ATK_POS.rx, ATK_POS.ry, data[static_cast<int>(DataType::ATK)], TRUE);
		DrawExtendGraph(AGI_POS.lx, AGI_POS.ly, AGI_POS.rx, AGI_POS.ry, data[static_cast<int>(DataType::AGI)], TRUE);
		DrawExtendGraph(DEF_POS.lx, DEF_POS.ly, DEF_POS.rx, DEF_POS.ry, data[static_cast<int>(DataType::DEF)], TRUE);

		SetFontSize(30);
		DrawString(ATK_TEXT_POS.x, ATK_TEXT_POS.y, "�U����", FONT_COLOR);
		DrawString(AGI_TEXT_POS.x, AGI_TEXT_POS.y, "�f����", FONT_COLOR);
		DrawString(DEF_TEXT_POS.x, DEF_TEXT_POS.y, "�h���", FONT_COLOR);

		if (prevAtkUpCount != atkUpCount)
		{
			DrawFormatString(ATK_UP_COUNT_POS.x, ATK_UP_COUNT_POS.y, BLUE_FONT_COLOR, "x%d", atkUpCount);
		}
		else
		{
			DrawFormatString(ATK_UP_COUNT_POS.x, ATK_UP_COUNT_POS.y, FONT_COLOR, "x%d", atkUpCount);
		}
		if (prevAgiUpCount != agiUpCount)
		{
			DrawFormatString(AGI_UP_COUNT_POS.x, AGI_UP_COUNT_POS.y, BLUE_FONT_COLOR, "x%d", agiUpCount);
		}
		else
		{
			DrawFormatString(AGI_UP_COUNT_POS.x, AGI_UP_COUNT_POS.y, FONT_COLOR, "x%d", agiUpCount);
		}
		if (prevDefUpCount != defUpCount)
		{
			DrawFormatString(DEF_UP_COUNT_POS.x, DEF_UP_COUNT_POS.y, BLUE_FONT_COLOR, "x%d", defUpCount);
		}
		else
		{
			DrawFormatString(DEF_UP_COUNT_POS.x, DEF_UP_COUNT_POS.y, FONT_COLOR, "x%d", defUpCount);
		}

		DrawExtendGraph(nowHighCursorPos.lx, nowHighCursorPos.ly, nowHighCursorPos.rx, nowHighCursorPos.ry, data[static_cast<int>(DataType::CURSOR)], TRUE);
		DrawExtendGraph(nowLowCursorPos.lx, nowLowCursorPos.ly, nowLowCursorPos.rx, nowLowCursorPos.ry, data[static_cast<int>(DataType::CURSOR)], TRUE);
	}
	else
	{
		particle->OffIsDraw();
	}
}
/// <summary>
/// ���̕\��
/// </summary>
const void CharacterStatus::ShowInfo()
{
	//printfDx("STATUS\n");
	//printfDx("LV:%f\n", lv);
	//printfDx("HP:%f\n", hp);
	//printfDx("ATK:%f\n", atk);
	//printfDx("DEF:%f\n", def);
	//printfDx("AGI:%f\n", agi);
	//printfDx("EXP:%f\n", exp);
	//printfDx("needEXP:%f\n", needExp);
	//printfDx("maxHP:%f\n", maxHp);
}
