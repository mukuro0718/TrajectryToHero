//===========================================================================
//@brief タイトルクラス
//===========================================================================
#include"Title.h"
#include"Common.h"
#include"Load.h"

/// <summary>
/// コンストラクタ
/// </summary>
Title::Title()
{
	//初期化
	Init();
	//ロードクラスのインスタンスを取得
	auto& load = Load::GetInstance();
	//画像のロード
	load.GetTitleData(&image);
	SetDrawScreen(GetActiveGraph());
}
/// <summary>
/// 初期化
/// </summary>
void Title::Init()
{
	//座標の初期化
	escapeIconPos		= INIT_ESCAPE_ICON_POS;
	goIconPos			= INIT_GO_ICON_POS;
	briefingIconPos		= INIT_BRIEFING_ICON_POS;
	titlePos			= INIT_TITLE_POS;
	cursorPos			= INIT_CURSOR_POS_OF_GO	;
	briefingDataImgPos	= INIT_BRIEFING_DATA_POS;
	//選択しているアイコンの初期化
	nowSelectIconType = static_cast<int>(CursorType::GO);
	//フラグの初期化
	isSelectIcon	= false;
	isShowBriefing	= false;
	isTitleEnd		= false;
	isChangeScene	= false;
	isInputState	= false;
	//画像ブレンド
	alpha			= MIN_ALPHA_VALUE;
	floatY			= INIT_Y_POS;
	nowWaitCount	= INIT_WAIT_COUNT;
	floatYAddValue  = MAX_Y_VALUE;
}
/// <summary>
/// デストラクタ
/// </summary>
Title::~Title()
{
}
/// <summary>
/// 更新
/// </summary>
void Title::Update()
{
	FloatCursor();
	ChangeCursor();
}
/// <summary>
/// 描画
/// </summary>
void Title::Draw()
{
	DrawMoveBackGround();
	//画像の描画
	DrawGraph(escapeIconPos.x	, escapeIconPos.y		, image[static_cast<int>(ImageType::ESCAPE_ICON)]	, TRUE);//ESCAPEアイコン画像
	DrawGraph(goIconPos.x		, goIconPos.y			, image[static_cast<int>(ImageType::GO_ICON)]		, TRUE);//GOアイコン画像
	DrawGraph(briefingIconPos.x	, briefingIconPos.y		, image[static_cast<int>(ImageType::BRIEFING_ICON)]	, TRUE);//説明アイコン画像
	DrawGraph(titlePos.x		, titlePos.y			, image[static_cast<int>(ImageType::TITLE_TEXT)]		, TRUE);//タイトル文字画像
	DrawGraph(cursorPos.x		, cursorPos.y + floatY	, image[static_cast<int>(ImageType::CURSOR)]			, TRUE);//カーソル画像
	//アイコンを選択している状態
	if (isSelectIcon)
	{
		//説明アイコンを選択していたら
		if (isShowBriefing)
		{
			//画面を徐々に暗くする（アルファ値を定数まで増加させる）
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			DrawGraph(ORIGIN_POS_2D.x, ORIGIN_POS_2D.y, image[static_cast<int>(ImageType::BACKGROUND)], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MIN_ALPHA_VALUE);

			//アルファ値増加
			alpha += ADD_ALPHA_VALUE;
			//もしアルファ値が最大アルファ値を超えていたら
			if (alpha > MAX_ALPHA_VALUE)
			{
				alpha = MAX_ALPHA_VALUE;
				DrawGraph(briefingDataImgPos.x, briefingDataImgPos.y, image[static_cast<int>(ImageType::BRIEFING_DATA)], TRUE);
			}
		}
		else
		{
			//アルファ値減少
			alpha -= ADD_ALPHA_VALUE;
			//もしアルファ値が最大アルファ値を超えていたら
			if (alpha < MIN_ALPHA_VALUE)
			{
				alpha = MIN_ALPHA_VALUE;
				//フラグを下す
				isSelectIcon = false;
			}
		}
	}
}
/// <summary>
/// カーソル座標の変更
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
	//アイコンが選ばれていなかったら
	if (!isSelectIcon)
	{
		//左
		if (!isInputState && input & PAD_INPUT_LEFT || !isInputState && CheckHitKey(KEY_INPUT_LEFT))
		{
			//もし左端のアイコンを入力していなかったら
			if (nowSelectIconType != static_cast<int>(CursorType::ESCAPE))
			{
				nowSelectIconType--;
			}
			isInputState = true;
		}
		//右
		if (!isInputState && input & PAD_INPUT_RIGHT || !isInputState && CheckHitKey(KEY_INPUT_RIGHT))
		{
			//もし右端のアイコンを入力していなかったら
			if (nowSelectIconType != static_cast<int>(CursorType::BRIEFING))
			{
				nowSelectIconType++;
			}
			isInputState = true;
		}
	}
	//決定ボタンが押されたか
	if (input & PAD_INPUT_2 || CheckHitKey(KEY_INPUT_RETURN))
	{
		isSelectIcon = true;
		isInputState = true;
	}

		//説明アイコンの上で決定ボタンが押されたら
		if (!isShowBriefing)
		{
			if (isSelectIcon && nowSelectIconType == static_cast<int>(CursorType::BRIEFING))
			{
				isShowBriefing = true;
			}
		}
		//説明が表示中にAボタンが押されたら説明を閉じる
		else if (isShowBriefing)
		{
			if (!isInputState && input & PAD_INPUT_1 || !isInputState && CheckHitKey(KEY_INPUT_BACK))
			{
				isShowBriefing = false;
				isSelectIcon = false;
				isInputState = true;
			}
		}
		//現在アイコンを選択中かつ選択しているアイコンがESCAPEだったら
		if (isSelectIcon && nowSelectIconType == static_cast<int>(CursorType::ESCAPE))
		{
			//タイトル画面を終了するか
			//isGameEnd = true;
			//これをするとフリーズするので、コメントアウトする
			//セレクトフラグを下す
			DxLib_End();
			isSelectIcon = false;
		}
		//現在アイコンを選択中かつ選択しているアイコンがGOだったら
		if (isSelectIcon && nowSelectIconType == static_cast<int>(CursorType::GO))
		{
			isChangeScene = true;
		}
	//もしカーソルタイプがESCAPEだったら
	if (nowSelectIconType == static_cast<int>(CursorType::ESCAPE))
	{
		cursorPos = INIT_CURSOR_POS_OF_ESCAPE;
	}
	//もしカーソルタイプがGOだったら
	else if (nowSelectIconType == static_cast<int>(CursorType::GO))
	{
		cursorPos = INIT_CURSOR_POS_OF_GO;
	}
	//もしカーソルタイプがBRIEFINGだったら
	else if (nowSelectIconType == static_cast<int>(CursorType::BRIEFING))
	{
		cursorPos = INIT_CURSOR_POS_OF_BRIEFING;
	}
}
/// <summary>
/// 動く背景の描画
/// </summary>
void Title::DrawMoveBackGround()
{
	//描画位置の更新
	for (int i = 0; i < MAX_BACKGROUND_NUM; i++)
	{
		//背景別で座標をプラスする
		moveBackGroundPos[i].x -= MOVE_BACKGROUND_SPEED[i];
		//同じ画像を２枚描画
		DrawExtendGraph(moveBackGroundPos[i].x, moveBackGroundPos[i].y, moveBackGroundPos[i].x + WINDOW_WIDTH, moveBackGroundPos[i].y+ WINDOW_HEIGHT, image[i + MAX_BACKGROUND_NUM], TRUE);
		DrawExtendGraph(moveBackGroundPos[i].x + WINDOW_WIDTH, moveBackGroundPos[i].y, moveBackGroundPos[i].x + WINDOW_WIDTH + WINDOW_WIDTH, moveBackGroundPos[i].y + WINDOW_HEIGHT, image[i + MAX_BACKGROUND_NUM], TRUE);
		//もし座標が定数を超えたら０に初期化する
		if (moveBackGroundPos[i].x < -MAX_BACKGROUND_POS)
		{
			moveBackGroundPos[i].x = INIT_X_POS;
		}
	}
}
void Title::FloatCursor()
{
	//もしAddが正だったら
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