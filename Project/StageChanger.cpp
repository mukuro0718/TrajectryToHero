//===========================================================================
//@brief ステージ切り替えクラス
//===========================================================================
#include"StageChanger.h"
#include"Timer.h"
#include"Load.h"
const VECTOR StageChanger::DRAW_GATEIMAGE_POS = { 0.0f,30.0f,0.0f };
const VECTOR StageChanger::VERTEX_NORM = VGet(0.0f, 0.0f, -1.0f);
const COLOR_U8 StageChanger::TRAIL_COLOR = GetColorU8(255, 255, 255, 255);

const VERTEX3D StageChanger::INIT_VERTEX =
{
	ORIGIN_POS,	//座標
	VERTEX_NORM,//法線
	TRAIL_COLOR,//ディフューズカラー
	TRAIL_COLOR,//スペキュラカラー
	0.0f,		//テクスチャ座標
	0.0f,		//テクスチャ座標
	0.0f,		//補助テクスチャ座標
	0.0f		//補助テクスチャ座標
};

/// <summary>
/// コンストラクタ
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
	//初期化
	Init();
	//画像のロード
	auto& load = Load::GetInstance();
	load.GetStageChangeData(&image,&gateImage);
}
/// <summary>
/// デストラクタ
/// </summary>
StageChanger::~StageChanger()
{
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
		SetFontSize(180);
		//ブレンド処理
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		//描画画像切り替え
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
/// 描画
/// </summary>
void StageChanger::Draw()
{
	//DrawGraph(0, 30, gateImage, true);
	//DrawBillboard3D(DRAW_GATEIMAGE_POS, 0.5f, 0.5f, IMG_SIZE, gateImageAngle * (DX_PI_F / 180), gateImage, TRUE);
	++gateImageAngle;
}
/// <summary>
/// ステージ移動を行うかどうか
/// </summary>
/// <param name="playerPos">変更したプレイヤー座標</param>
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