////===========================================================================
////@brief ステータス管理クラス
//// ステータス計算、ステータス画像の描画
////===========================================================================
//#include "StatusManager.h"
//#include "Common.h"
//#include "ScenesCommon.h"
//#include "SceneChanger.h"
//#include "Load.h"
//#include "Timer.h"
//
//constexpr VECTOR StatusManager::SET_DRAW_POS = VGet(50.0f,50.0f,0.0f);
//const int StatusManager::FONT_COLOR_WHITE = GetColor(210, 210, 210);
//const int StatusManager::FONT_COLOR_RED = GetColor(255, 50, 50);
///// <summary>
///// コンストラクタ
///// </summary>
//StatusManager::StatusManager()
//{
//	//クラスインスタンスの作成
//	CreateInstance();
//	auto& load = Load::GetInstance();
//	//初期化
//	Init();
//	load.GetStatusManagerData(&backGroundImage);
//	
//}
//
///// <summary>
///// デストラクタ
///// </summary>
//StatusManager::~StatusManager()
//{
//	Delete();
//}
///// <summary>
///// 初期化
///// </summary>
//void StatusManager::Init()
//{
//	inputWaitTimer->Init(5);
//	isInputPad			= false;
//	isLvUP				= false;
//	isShowMenu			= false;
//	isFinalSelectStatus = false;
//	prevLv				= 1.0f;
//	lvUpCount			= 0;
//	backGroundImage		= 0;
//	nowSelectStatus		= static_cast<int>(SelectStatus::ATK);
//	statusFontHandle	= CreateFontToHandle("Data/Img/Font/HelpMe.ttf", FONT_SIZE, FONT_THICK, DX_FONTTYPE_NORMAL);
//}
///// <summary>
///// クラスインスタンスの生成
///// </summary>
//void StatusManager::CreateInstance()
//{
//	inputWaitTimer = NULL;
//	inputWaitTimer = new Timer();
//}
///// <summary>
///// 画像ハンドル、クラスインスタンスの削除
///// </summary>
//void StatusManager::Delete()
//{
//	// モデルのアンロード
//	DeleteGraph(backGroundImage);
//	//インスタンスの削除
//	if (inputWaitTimer)
//	{
//		delete(inputWaitTimer);
//		inputWaitTimer = NULL;
//	}
//}
///// <summary>
///// 更新
///// </summary>
//void StatusManager::Update(CharacterStatus* status)
//{
//	lvUpCount = static_cast<int>(status->LV) - static_cast<int>(prevLv);
//	//レベルアップをしていたら
//	if (lvUpCount > 0)
//	{
//		isShowMenu = true;
//		//選択ステータスの変更
//		ChangeSelectStatus();
//		//選択しているステータスの上昇
//		UpSelectStatus(status);
//	}
//	else
//	{
//		nowSelectStatus = static_cast<int>(SelectStatus::ATK);
//		isShowMenu = false;
//	}
//}
///// <summary>
///// 描画
///// </summary>
//void StatusManager::Draw()
//{
//	// メニューが開いているとき
//	if (isShowMenu)
//	{
//		DrawExtendGraph(BACKGROUND_POS.x, BACKGROUND_POS.y, BACKGROUND_POS.x + BACKGROUND_WIDTH, BACKGROUND_POS.y + BACKGROUND_HEIGHT, backGroundImage,TRUE);
//		DrawStringToHandle(STATUS_UP_TEXT_POS.x, STATUS_UP_TEXT_POS.y, "STATUS UP!", FONT_COLOR_WHITE, statusFontHandle);
//		//選択されいないアイコンは少し暗くする
//		ChangeBlendRateDrawText(nowSelectStatus, static_cast<int>(SelectStatus::ATK));	//攻撃力
//		ChangeBlendRateDrawText(nowSelectStatus, static_cast<int>(SelectStatus::DEF));	//防御力
//		ChangeBlendRateDrawText(nowSelectStatus, static_cast<int>(SelectStatus::AGI));	//素早さ
//	}
//}
///// <summary>
///// 選択しているステータスの上昇
///// </summary>
//void StatusManager::UpSelectStatus(CharacterStatus* status)
//{
//	//最終決定されていたら
//	if (isFinalSelectStatus && lvUpCount != 0)
//	{
//		//選択しているステータスの上昇
//		switch (nowSelectStatus)
//		{
//		case static_cast<int>(SelectStatus::ATK):
//			status->ATK += LV_UP_ADD_VALUE;
//			break;
//		case static_cast<int>(SelectStatus::DEF):
//			status->DEF += LV_UP_ADD_VALUE;
//			break;
//		case static_cast<int>(SelectStatus::AGI):
//			status->AGI += LV_UP_ADD_VALUE;
//			break;
//		}
//		//フラグを折る
//		isFinalSelectStatus = false;
//		prevLv++;
//	}
//}
///// <summary>
///// 選択された/されていないを透明度を変えて表示
///// </summary>
///// <param name="nowSelectStatus">現在選択中のステータス</param>
///// <param name="statusType">ステータスの種類</param>
///// <param name="imgHandle"></param>
//void StatusManager::ChangeBlendRateDrawText(const int currentSelectStatus, const int statusType)
//{
//	const TCHAR* drawText = NULL;
//	switch (statusType)
//	{
//	case static_cast<int>(SelectStatus::ATK):
//		drawText = "ATK";
//		break;
//	case static_cast<int>(SelectStatus::DEF):
//		drawText = "DEF";
//		break;
//	case static_cast<int>(SelectStatus::AGI):
//		drawText = "AGI";
//		break;
//	}
//	// カーソル番号が等しいときは選択している
//	// 選択されているときは普通に描画する
//	if (nowSelectStatus == statusType)
//	{
//		//レベルアップしていたらbutton画像を表示する
//		DrawStringToHandle(STATUS_TEXT_POS[statusType].x, STATUS_TEXT_POS[statusType].y, drawText, FONT_COLOR_RED, statusFontHandle);
//	}
//	//選択されていないときは少し暗く描画する
//	else
//	{
//		// 非選択時の画像の描画（選択されていない画像を薄くする）
//		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
//		DrawStringToHandle(STATUS_TEXT_POS[statusType].x, STATUS_TEXT_POS[statusType].y, drawText, FONT_COLOR_RED, statusFontHandle);
//		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//	}
//}
//
///// <summary>
///// アイコンの選択（カーソルの番号を切り替える）
///// </summary>
//void StatusManager::ChangeSelectStatus()
//{
//	// キーの入力状態をとる
//	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//
//	//上に
//	if (!isInputPad)
//	{
//		if (input & PAD_INPUT_UP)
//		{
//			switch (nowSelectStatus)
//			{
//			case static_cast<int>(SelectStatus::ATK):
//				nowSelectStatus = static_cast<int>(SelectStatus::ATK);
//				break;
//			case static_cast<int>(SelectStatus::DEF):
//				nowSelectStatus = static_cast<int>(SelectStatus::ATK);
//				break;
//			case static_cast<int>(SelectStatus::AGI):
//				nowSelectStatus = static_cast<int>(SelectStatus::DEF);
//				break;
//			}
//			isInputPad = true;
//		}
//		// 下に
//		if (input & PAD_INPUT_DOWN)
//		{
//			switch (nowSelectStatus)
//			{
//			case static_cast<int>(SelectStatus::ATK):
//				nowSelectStatus = static_cast<int>(SelectStatus::DEF);
//				break;
//			case static_cast<int>(SelectStatus::DEF):
//				nowSelectStatus = static_cast<int>(SelectStatus::AGI);
//				break;
//			case static_cast<int>(SelectStatus::AGI):
//				nowSelectStatus = static_cast<int>(SelectStatus::AGI);
//				break;
//			}
//			isInputPad = true;
//		}
//	}
//	else
//	{
//		inputWaitTimer->StartTimer();
//	}
//	if (inputWaitTimer->CountTimer())
//	{
//		isInputPad = false;
//		inputWaitTimer->EndTimer();
//	}
//	// 最終選択
//	if (input & PAD_INPUT_2)
//	{
//		isFinalSelectStatus = true;
//		isInputPad = true;
//	}
//}
