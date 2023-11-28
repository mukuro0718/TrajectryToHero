//===========================================================================
//@brief ステージ切り替えクラス
//===========================================================================
#include"StageChanger.h"
#include"Timer.h"
#include"Load.h"

/// <summary>
/// コンストラクタ
/// </summary>
StageChanger::StageChanger()
{
	//初期化
	Init();
	//画像のロード
	auto& load = Load::GetInstance();
	load.GetStageChangeData(&image);
}
/// <summary>
/// デストラクタ
/// </summary>
StageChanger::~StageChanger()
{
	Delete();
}
/// <summary>
/// 初期化
/// </summary>
void StageChanger::Init()
{
	//タイマーインスタンスの作成
	StayMaxAlphaTimer = new Timer();
	//目標時間のセット
	StayMaxAlphaTimer->Init(SET_STAY_TIMER);
	//アルファ値の初期化
	alpha			= 0;
	backGroundAlpha = 0;
	alphaValue		= 6;
	//ウェーブ状態管理フラグ
	isFarm			= true;//ファームステージ
	isBoss			= false;//ボスステージ
	isChangeStage	= true;
	isGameOver		= false;
	isGameClear		= false;
	isGameEnd		= false;
	isDrawBlackBack = false;
	isDrawAlert		= false;
}
/// <summary>
/// ステージ切り替え時の画像(FARM、BOSS)の表示
/// </summary>
void StageChanger::DrawImageWhenSwitchingStage()
{
	//ステージ切り替えフラグが立っていたら
	if (isChangeStage)
	{
		//もしアルファ値が最大になったら
		if (alphaValue > 0 && alpha >= 255)
		{
			//タイマーのスタート
			StayMaxAlphaTimer->StartTimer();

			//タイマーが目標時間に達したら処理を行う
			if (StayMaxAlphaTimer->CountTimer())
			{
				alphaValue = -6;
				StayMaxAlphaTimer->EndTimer();
			}
			//待っていなかったら
			else
			{
				alpha = 255;
			}
		}
		//アルファ値を増やす
		alpha += alphaValue;

		//ブレンド処理
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		//描画画像切り替え
		if (isFarm)
		{
			DrawGraph(0, 0, image[static_cast<int>(ImageType::FARM_STAGE)], TRUE);
		}
		else if (isBoss)
		{
			DrawGraph(0, 0, image[static_cast<int>(ImageType::BOSS_STAGE)], TRUE);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//もしアルファ値が０未満になったらループを抜ける
		if (alpha < 0)
		{
			alpha = 0;
			alphaValue = 6;
			isChangeStage = false;
		}
	}
}
/// <summary>
/// ゲームクリアの画像の表示
/// </summary>
void StageChanger::DrawGameClear()
{

}
/// <summary>
/// 削除
/// </summary>
void StageChanger::Delete()
{
	//for (int i = 0; i < IMAGE_NUM; i++)
	//{
	//	DeleteGraph(image[i]);
	//}
}
/// <summary>
/// ステージ移動を行うかどうか
/// </summary>
/// <param name="playerPos">変更したプレイヤー座標</param>
VECTOR StageChanger::DrawAlert(VECTOR playerPos)
{
	VECTOR outPutPos = playerPos;
	isChangeStage = true;
	isDrawAlert = true;
	DrawGraph(0, 0, image[static_cast<int>(ImageType::ALERT)], TRUE);
	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (input & PAD_INPUT_2)
	{
		outPutPos = ORIGIN_POS;
		isFarm = false;
		isBoss = true;
		isDrawAlert = false;
	}
	else if (input & PAD_INPUT_3)
	{
		outPutPos.z = 450.0f;
		isChangeStage = false;
		isDrawAlert = false;
	}
	return outPutPos;
}