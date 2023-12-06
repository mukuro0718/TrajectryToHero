//===========================================================================
//@brief ゲームオーバークラス
// ゲームオーバー時の描画を行う
//===========================================================================
#include "GameOver.h"
#include "Common.h"
#include "Animation.h"
#include"Load.h"
#include"Timer.h"


/// <summary>
/// コンストラクタ
/// </summary>
GameOver::GameOver()
{
	//初期化
	Init();
	//ロードクラスのインスタンスを取得
	auto& load = Load::GetInstance();
	//画像のロード
	load.GetGameOverData(&gameOverImageHandle);
	//作成
	Create();
}
/// <summary>
/// デストラクタ
/// </summary>
GameOver::~GameOver()
{
}
/// <summary>
/// 初期化
/// </summary>
void GameOver::Init()
{
	gameOverImageHandle = 0;
	gameOverImageAlpha = 0;
	addGameOverImageAlphaValue = 1;
	isEndGameOverImage = false;
	isImageDrawingWait = false;
	imageDrawingWait = NULL;
}
/// <summary>
/// 作成
/// </summary>
void GameOver::Create()
{
	imageDrawingWait = new Timer();
	imageDrawingWait->Init(10);
}
/// <summary>
/// 初期化
/// </summary>
void GameOver::Final()
{
	DeleteGraph(gameOverImageHandle);
	if (imageDrawingWait)
	{
		delete(imageDrawingWait);
		imageDrawingWait = NULL;
	}
}
/// <summary>
/// 更新
/// </summary>
void GameOver::Update()
{
	//ゲームクリア画像を描画
	if (!isEndGameOverImage)
	{
		//もし待機タイマーがスタートしていなかったら
		if (!isImageDrawingWait)
		{
			//もし符号変更フラグが立っていたらアルファ値をマイナスする
			if (isChangeAlphaValueSign)
			{
				gameOverImageAlpha -= ADD_GAME_CLEAR_IMAGE_ALPHA_VALUE;
			}
			//そうでなければプラスする
			else
			{
				gameOverImageAlpha += ADD_GAME_CLEAR_IMAGE_ALPHA_VALUE;
			}

			//アルファ値が最大値よりも大きくなったら
			if (gameOverImageAlpha >= MAX_GAME_CLEAR_IMAGE_ALPHA)
			{
				gameOverImageAlpha = MAX_GAME_CLEAR_IMAGE_ALPHA;
				//タイマーをスタートさせる
				imageDrawingWait->StartTimer();
				//タイマーをスタートしたのでフラグを立てる
				isImageDrawingWait = true;
				//アルファ値符号変更フラグを立てる
				isChangeAlphaValueSign = true;
			}
			//アルファ値が最小値よりも小さくなったら
			if (gameOverImageAlpha <= MIN_GAME_CLEAR_IMAGE_ALPHA)
			{
				//フラグを立てる
				isEndGameOverImage = true;
			}
		}

		//もし待機タイマーがスタートしていなかったら
		if (isImageDrawingWait)
		{
			//もし待機タイマーが終了していたら
			if (imageDrawingWait->CountTimer())
			{
				//タイマーを終了する
				imageDrawingWait->EndTimer();
				//フラグを下す
				isImageDrawingWait = false;
			}
		}
	}
}
/// <summary>
/// 描画
/// </summary>
void GameOver::Draw()
{
	if (!isEndGameOverImage)
	{
		// 非選択時の画像の描画（選択されていない画像を薄くする）
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, gameOverImageAlpha);
		DrawGraph(0, 0, gameOverImageHandle, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}
