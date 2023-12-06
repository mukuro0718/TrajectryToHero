//===========================================================================
//@brief ステータスクラス
//===========================================================================
#include"CharacterStatus.h"
#include "Common.h"
#include "SceneChanger.h"
#include "Load.h"
#include "Timer.h"
const VECTOR CharacterStatus::SET_DRAW_POS		= VGet(50.0f,50.0f,0.0f);
const int	 CharacterStatus::FONT_COLOR_WHITE	= GetColor(210, 210, 210);
const int	 CharacterStatus::FONT_COLOR_RED	= GetColor(255, 50, 50);
/// <summary>
/// コンストラクタ
/// </summary>
CharacterStatus::CharacterStatus()
	:isInputPad(false)
	,isLvUP(false)
	,isShowMenu(false)
	,isFinalSelectStatus(false)
	,lvUpCount(0)
	,prevLv(1.0f)
	,backGroundImage(0)
	,nowSelectStatus(static_cast<int>(SelectStatus::ATK))
	,statusFontHandle(0)
	, inputWaitTimer(nullptr)
{
	auto& load = Load::GetInstance();
	inputWaitTimer = new Timer();
	//初期化
	Init();
	load.GetCharacterStatusData(&backGroundImage,&statusFontHandle);
}
/// <summary>
/// 初期化
/// </summary>
void CharacterStatus::Init()
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
/// <summary>
/// 雑魚敵ステータスの初期設定
/// </summary>
void CharacterStatus::InitWeakEnemyStatus()
{
	lv = 10.0f;			//レベルのセット
	hp = 50.0f;		//体力のセット
	atk = 10.0f;			//攻撃力のセット
	def = 50.0f;			//防御力のセット
	agi = 1.0f;			//素早さのセット
	expToGive = 5.0f;	//倒されたとき与える経験値のセット
	exp = 0.0f;			//経験値のセット
	needExp = 0.0f;
	maxHp = hp;
}
/// <summary>
/// 中ボスステータスの初期設定
/// </summary>
void CharacterStatus::InitStrongEnemyStatus()
{
	lv = 10.0f;			//レベルのセット
	hp = 100.0f;		//体力のセット
	atk = 20.0f;			//攻撃力のセット
	def = 60.0f;			//防御力のセット
	agi = 2.0f;			//素早さのセット
	expToGive = 15.0f;	//倒されたとき与える経験値のセット
	exp = 0;			//経験値のセット
	needExp = 0.0f;
	maxHp = hp;
}
/// <summary>
/// ボスステータスの初期設定
/// </summary>
void CharacterStatus::InitBossEnemyStatus()
{
	lv			= 10.0f;	//レベルのセット
	hp			= 300.0f;	//体力のセット
	atk			= 30.0f;	//攻撃力のセット
	def			= 70.0f;	//防御力のセット
	agi			=2.0f;		//素早さのセット
	expToGive = 10.0f;		//倒されたとき与える経験値のセット
	exp			= 0.0f;		//経験値のセット
	needExp = 0.0f;
	maxHp = hp;
}

/// <summary>
/// プレイヤーステータスの初期設定
/// </summary>
void CharacterStatus::InitPlayerStatus()
{
	lv			 = 1.0f;	//レベルのセット
	hp			 = 30.0f;	//体力のセット
	atk		 = 3.0f;	//攻撃力のセット
	def		 = 1.0f;	//防御力のセット
	agi		 = 1.5f;	//素早さのセット
	expToGive = 0.0f;	//倒されたとき与える経験値のセット
	exp		 = 0.0f;	//経験値のセット
	needExp = 10.0f;
	maxHp = hp;
}

/// <summary>
/// HP計算
/// </summary>
float CharacterStatus::CalcHP(const float _atk)
{
	hp -= atk * def * 0.05f;
	if (hp <= 0)
	{
		return expToGive;
	}
	return 0.0f;
}
/// <summary>
/// 与える経験値の初期化
/// </summary>
void CharacterStatus::InitExpToGive()
{
	expToGive = 0.0f;
}
/// <summary>
/// HP計算
/// </summary>
void CharacterStatus::CalcExp(const float _expToGive)
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
/// <summary>
/// 画像ハンドル、クラスインスタンスの削除
/// </summary>
void CharacterStatus::Delete()
{
	// モデルのアンロード
	DeleteGraph(backGroundImage);
	//インスタンスの削除
	if (inputWaitTimer)
	{
		delete(inputWaitTimer);
		inputWaitTimer = nullptr;
	}
}

/// <summary>
/// 更新
/// </summary>
void CharacterStatus::Update()
{
	lvUpCount = static_cast<int>(lv) - static_cast<int>(prevLv);
	//レベルアップをしていたら
	if (lvUpCount > 0)
	{
		isShowMenu = true;
		//選択ステータスの変更
		ChangeSelectStatus();
		//選択しているステータスの上昇
		UpSelectStatus();
	}
	else
	{
		nowSelectStatus = static_cast<int>(SelectStatus::ATK);
		isShowMenu = false;
	}
}
/// <summary>
/// 描画
/// </summary>
void CharacterStatus::Draw()
{
	// メニューが開いているとき
	if (isShowMenu)
	{
		DrawExtendGraph(BACKGROUND_POS.x, BACKGROUND_POS.y, BACKGROUND_POS.x + BACKGROUND_WIDTH, BACKGROUND_POS.y + BACKGROUND_HEIGHT, backGroundImage, TRUE);
		DrawStringToHandle(STATUS_UP_TEXT_POS.x, STATUS_UP_TEXT_POS.y, "STATUS UP!", FONT_COLOR_WHITE, statusFontHandle);
		//選択されいないアイコンは少し暗くする
		ChangeBlendRateDrawText(nowSelectStatus, static_cast<int>(SelectStatus::ATK));	//攻撃力
		ChangeBlendRateDrawText(nowSelectStatus, static_cast<int>(SelectStatus::DEF));	//防御力
		ChangeBlendRateDrawText(nowSelectStatus, static_cast<int>(SelectStatus::AGI));	//素早さ
	}
}
/// <summary>
/// 選択しているステータスの上昇
/// </summary>
void CharacterStatus::UpSelectStatus()
{
	//最終決定されていたら
	if (isFinalSelectStatus && lvUpCount != 0)
	{
		//選択しているステータスの上昇
		switch (nowSelectStatus)
		{
		case static_cast<int>(SelectStatus::ATK):
			atk += LV_UP_ADD_VALUE;
			break;
		case static_cast<int>(SelectStatus::DEF):
			def += LV_UP_ADD_VALUE;
			break;
		case static_cast<int>(SelectStatus::AGI):
			agi += LV_UP_ADD_VALUE;
			break;
		}
		//フラグを折る
		isFinalSelectStatus = false;
		prevLv++;
	}
}
/// <summary>
/// 選択された/されていないを透明度を変えて表示
/// </summary>
/// <param name="nowSelectStatus">現在選択中のステータス</param>
/// <param name="statusType">ステータスの種類</param>
/// <param name="imgHandle"></param>
void CharacterStatus::ChangeBlendRateDrawText(const int currentSelectStatus, const int statusType)
{
	const TCHAR* drawText = NULL;
	switch (statusType)
	{
	case static_cast<int>(SelectStatus::ATK):
		drawText = "ATK";
		break;
	case static_cast<int>(SelectStatus::DEF):
		drawText = "DEF";
		break;
	case static_cast<int>(SelectStatus::AGI):
		drawText = "AGI";
		break;
	}
	// カーソル番号が等しいときは選択している
	// 選択されているときは普通に描画する
	if (nowSelectStatus == statusType)
	{
		//レベルアップしていたらbutton画像を表示する
		DrawStringToHandle(STATUS_TEXT_POS[statusType].x, STATUS_TEXT_POS[statusType].y, drawText, FONT_COLOR_RED, statusFontHandle);
	}
	//選択されていないときは少し暗く描画する
	else
	{
		// 非選択時の画像の描画（選択されていない画像を薄くする）
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawStringToHandle(STATUS_TEXT_POS[statusType].x, STATUS_TEXT_POS[statusType].y, drawText, FONT_COLOR_RED, statusFontHandle);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

/// <summary>
/// アイコンの選択（カーソルの番号を切り替える）
/// </summary>
void CharacterStatus::ChangeSelectStatus()
{
	// キーの入力状態をとる
	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//上に
	if (!isInputPad)
	{
		if (input & PAD_INPUT_UP)
		{
			switch (nowSelectStatus)
			{
			case static_cast<int>(SelectStatus::ATK):
				nowSelectStatus = static_cast<int>(SelectStatus::ATK);
				break;
			case static_cast<int>(SelectStatus::DEF):
				nowSelectStatus = static_cast<int>(SelectStatus::ATK);
				break;
			case static_cast<int>(SelectStatus::AGI):
				nowSelectStatus = static_cast<int>(SelectStatus::DEF);
				break;
			}
			isInputPad = true;
		}
		// 下に
		if (input & PAD_INPUT_DOWN)
		{
			switch (nowSelectStatus)
			{
			case static_cast<int>(SelectStatus::ATK):
				nowSelectStatus = static_cast<int>(SelectStatus::DEF);
				break;
			case static_cast<int>(SelectStatus::DEF):
				nowSelectStatus = static_cast<int>(SelectStatus::AGI);
				break;
			case static_cast<int>(SelectStatus::AGI):
				nowSelectStatus = static_cast<int>(SelectStatus::AGI);
				break;
			}
			isInputPad = true;
		}
	}
	else
	{
		inputWaitTimer->StartTimer();
	}
	if (inputWaitTimer->CountTimer())
	{
		isInputPad = false;
		inputWaitTimer->EndTimer();
	}
	// 最終選択
	if (input & PAD_INPUT_2)
	{
		isFinalSelectStatus = true;
		isInputPad = true;
	}
}
/// <summary>
/// 情報の表示
/// </summary>
void CharacterStatus::ShowInfo()
{
	printfDx("STATUS\n");
	printfDx("LV:%f\n", lv);
	printfDx("HP:%f\n", hp);
	printfDx("ATK:%f\n", atk);
	printfDx("DEF:%f\n", def);
	printfDx("AGI:%f\n", agi);
	printfDx("EXP:%f\n", exp);
	printfDx("needEXP:%f\n", needExp);
	printfDx("maxHP:%f\n", maxHp);
}