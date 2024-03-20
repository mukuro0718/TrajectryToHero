#include"CharacterStatus.h"
#include "Common.h"
#include "SceneChanger.h"
#include "Load.h"
#include "Timer.h"
#include "CrackerParticle.h"
const int	 CharacterStatus::FONT_COLOR		= GetColor(200, 200, 150);
const int	 CharacterStatus::BLUE_FONT_COLOR	= GetColor(50, 50, 150);

/// <summary>
/// コンストラクタ
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
	//初期化
	Init();
	load.GetCharacterStatusData(&data);
	rectPos = { 200,200 };
	nowHighCursorPos = ATK_HIGH_CURSOR_POS;
	nowLowCursorPos = ATK_LOW_CURSOR_POS;
}
/// <summary>
/// 初期化
/// </summary>
const void CharacterStatus::Init()
{
	inputWaitTimer->Init(5);
}

/// <summary>
/// デストラクタ
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
		hp = 1.0f;//体力のセット
		atk = 0.0f;//攻撃力のセット
		def = 1.0f;//防御力のセット
		agi = 1.0f;	//素早さのセット
		expToGive = 20.0f;	//倒されたとき与える経験値のセット(Enemy用)
		exp = 20.0f;	//経験値のセット
		needExp = 0.0f;	//レベルアップに必要な経験値（Player用）
		maxHp = hp;	//最大ＨＰ
		prevLv = lv;	//前のレベル
	}
	else
	{
		lv = 3.0f;
		hp = 1.0f;//体力のセット
		atk = 0.0f;//攻撃力のセット
		def = 1.0f;//防御力のセット
		agi = 1.0f;	//素早さのセット
		expToGive = 20.0f;	//倒されたとき与える経験値のセット(Enemy用)
		exp = 20.0f;	//経験値のセット
		needExp = 0.0f;	//レベルアップに必要な経験値（Player用）
		maxHp = hp;	//最大ＨＰ
		prevLv = lv;	//前のレベル
	}
}
/// <summary>
/// 雑魚敵ステータスの初期設定
/// </summary>
const void CharacterStatus::InitWeakEnemyStatus(const float _playerLv)
{
	/*プレイヤーのレベルをもとに、ステータスを調整する*/
	//もしプレイヤーレベルが2以下だったら
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
	//前回のレベルと今のレベルの差を求める
	int lvDif = static_cast<int>(lv - prevLv);
	//もしレベルが１（スタート時）だったら
	if (lv == 1)
	{
		//ステータスの初期設定をする
		hp			= 3.0f;//体力のセット
		atk			= 3.0f;//攻撃力のセット
		def			= 1.0f;//防御力のセット
		agi			= 1.0f;	//素早さのセット
		expToGive	= 20.0f;	//倒されたとき与える経験値のセット(Enemy用)
		exp			= 0.0f;	//経験値のセット
		needExp		= 0.0f;	//レベルアップに必要な経験値（Player用）
		maxHp		= hp;	//最大ＨＰ
		prevLv		= lv;	//前のレベル
	}
	else if (lvDif == 1)
	{
		hp = maxHp;
		//ステータスを1.75倍する
		hp *= 1.5f ;//体力のセット
		atk *= 1.5f;//攻撃力のセット
		def *= 1.5f;//防御力のセット
		expToGive *= 1.5f;	//倒されたとき与える経験値のセット(Enemy用)
		maxHp = hp;	//最大ＨＰ
		prevLv = lv;	//前のレベル
	}
}
/// <summary>
/// 中ボスステータスの初期設定
/// </summary>
const void CharacterStatus::InitStrongEnemyStatus(const float _playerLv)
{
	/*プレイヤーのレベルをもとに、ステータスを調整する*/
	//もしプレイヤーレベルが8以下だったら
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
	//前回のレベルと今のレベルの差を求める
	int lvDif = static_cast<int>(lv - prevLv);
	//もしレベルが１（スタート時）だったら
	if (lv == 10)
	{
		hp = 10.0f;		//体力のセット
		atk = 6.0f;			//攻撃力のセット
		def = 3.0f;			//防御力のセット
		agi = 1.0f;			//素早さのセット
		expToGive = 80.0f;	//倒されたとき与える経験値のセット
		exp = 0;			//経験値のセット
		needExp = 0.0f;
		maxHp = hp;
	}
	else if (lvDif == 1)
	{
		hp = maxHp;
		//ステータスを1.75倍する
		hp *= 1.5f;//体力のセット
		atk *= 1.5f;//攻撃力のセット
		def *= 1.5f;//防御力のセット
		expToGive *= 1.5f;	//倒されたとき与える経験値のセット(Enemy用)
		maxHp = hp;	//最大ＨＰ
		prevLv = lv;	//前のレベル
	}

}
/// <summary>
/// ボスステータスの初期設定
/// </summary>
const void CharacterStatus::InitBossEnemyStatus()
{
	lv			= 10.0f;	//レベルのセット
	hp			= 30.0f;	//体力のセット
	atk			= 15.0f;	//攻撃力のセット
	def			= 5.0f;	//防御力のセット
	agi			= 0.8f;		//素早さのセット
	expToGive   = 10.0f;		//倒されたとき与える経験値のセット
	exp			= 0.0f;		//経験値のセット
	needExp     = 0.0f;
	maxHp       = hp;
}

/// <summary>
/// プレイヤーステータスの初期設定
/// </summary>
const void CharacterStatus::InitPlayerStatus()
{
	lv			= 1.0f;	//レベルのセット
	hp			= 30.0f;//体力のセット
	atk			= 1.0f;	//攻撃力のセット
	def			= 1.0f;	//防御力のセット
	agi			= 1.0f;	//素早さのセット
	expToGive	= 0.0f;	//倒されたとき与える経験値のセット
	exp			= 0.0f;	//経験値のセット
	needExp		= 10.0f;//必要な経験値のセット
	maxHp		= hp;	//最大HPのセット
	prevLv		= lv;	//前のレベルの設定
	//lv			= 1.0f;	//レベルのセット
	//hp			= 100.0f;//体力のセット
	//atk			= 6.0f;	//攻撃力のセット
	//def			= 10.0f;	//防御力のセット
	//agi			= 3.0f;	//素早さのセット
	//expToGive	= 0.0f;	//倒されたとき与える経験値のセット
	//exp			= 0.0f;	//経験値のセット
	//needExp		= 10.0f;//必要な経験値のセット
	//maxHp		= hp;	//最大HPのセット
	//prevLv		= lv;	//前のレベルの設定
}
/// <summary>
/// 体力回復
/// </summary>
const void CharacterStatus::PhysicalRecovery()
{
	hp = maxHp;
}
/// <summary>
/// HP計算
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
/// 与える経験値の初期化
/// </summary>
const void CharacterStatus::InitExpToGive()
{
	expToGive = 0.0f;
}
/// <summary>
/// HP計算
/// </summary>
const void CharacterStatus::CalcExp(const float _expToGive)
{
	if (lv != MAX_LV)
	{
		//経験値を足す
		exp += _expToGive;
		//もし経験値量がレベルアップに必要な経験値量を超えていたら
		if (exp >= needExp)
		{
			//レベルアップ
			++lv;
			//経験値量の初期化
			exp -= needExp;
			//次に必要な経験値量を設定
			needExp = lv * 10;
		}
	}
	else
	{
		exp = 0.0f;
	}
}
/// <summary>
/// 画像ハンドル、クラスインスタンスの削除
/// </summary>
const void CharacterStatus::Delete()
{
	//インスタンスの削除
	if (inputWaitTimer)
	{
		delete(inputWaitTimer);
		inputWaitTimer = nullptr;
	}
	//インスタンスの削除
	if (particle)
	{
		delete(particle);
		particle = nullptr;
	}
}
/// <summary>
/// 更新
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
/// 描画
/// </summary>
const void CharacterStatus::Draw()
{
	DrawBonfireMenu();
	DrawLevelUpMenu();
}
const void CharacterStatus::UpdateBonfireMenu()
{
	//キーボードまたはXInputのゲームパットの入力を受け付ける
	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//かがり火メニューの表示
	if (isBonfireMenu)
	{
		//もし入力フラグが立っていなかったら
		if (!isInputPad)
		{
			//もし上入力を受け付けたら
			if (input & PAD_INPUT_UP)
			{
				//現在選択しているメニューを切り替える
				switch (nowSelectMenu)
				{
				case static_cast<int>(SelectBonfireMenu::BACK_TO_THE_GAME):
					//現在選択しているメニューを変更する
					nowSelectMenu = static_cast<int>(SelectBonfireMenu::BACK_TO_THE_GAME);
					//強調表示用座標を変更する
					rectPos = GAME_POS;
					break;
				case static_cast<int>(SelectBonfireMenu::LEVEL_UP):
					nowSelectMenu = static_cast<int>(SelectBonfireMenu::BACK_TO_THE_GAME);
					rectPos = GAME_POS;
					break;
				}
				isInputPad = true;
			}
			// 下に
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
			//もしAボタンが押されたら
			if (input & PAD_INPUT_1)
			{
				//最終入力フラグを立てる
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
	//もし何も入力を受け付けていなかったら
	if (input == 0)
	{
		//入力フラグを下す
		isInputPad = false;
	}
	//もし最終入力フラグが立っていたら
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
/// 選択しているステータスの上昇
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

			//決定
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
			//戻る
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
/// アイコンの選択（カーソルの番号を切り替える）
/// </summary>
const void CharacterStatus::DrawLevelUpMenu()
{
	if (isLevelUp)
	{
		DrawExtendGraph(BACKGROUND_POS.lx, BACKGROUND_POS.ly, BACKGROUND_POS.rx, BACKGROUND_POS.ry,data[static_cast<int>(DataType::BACK_GROUND)],TRUE);

		particle->Draw();

		DrawFormatString(TEXT_POS.x, TEXT_POS.y,  FONT_COLOR, "ステータスアップ       ステータスポイント:%d\n上昇させるステータスを選んでください",statusUpPoint );
		DrawExtendGraph(ATK_POS.lx, ATK_POS.ly, ATK_POS.rx, ATK_POS.ry, data[static_cast<int>(DataType::ATK)], TRUE);
		DrawExtendGraph(AGI_POS.lx, AGI_POS.ly, AGI_POS.rx, AGI_POS.ry, data[static_cast<int>(DataType::AGI)], TRUE);
		DrawExtendGraph(DEF_POS.lx, DEF_POS.ly, DEF_POS.rx, DEF_POS.ry, data[static_cast<int>(DataType::DEF)], TRUE);

		SetFontSize(30);
		DrawString(ATK_TEXT_POS.x, ATK_TEXT_POS.y, "攻撃力", FONT_COLOR);
		DrawString(AGI_TEXT_POS.x, AGI_TEXT_POS.y, "素早さ", FONT_COLOR);
		DrawString(DEF_TEXT_POS.x, DEF_TEXT_POS.y, "防御力", FONT_COLOR);

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
/// 情報の表示
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
