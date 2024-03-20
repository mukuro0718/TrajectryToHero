#include "OperationUI.h"
#include"Load.h"
const int OperationUI::FONT_COLOR = GetColor(200, 200, 200);

/// <summary>
/// コンストラクタ
/// </summary>
OperationUI::OperationUI()
	: alpha(MAX_ALPHA)
	, moveUI(0)
	, menuUI(0)
	, attackUI(0)
	, cameraUI(0)
	, strongUI(0)
{
	auto& load = Load::GetInstance();
	load.GetStrongerUIData(&strongUI);
	load.GetOpeUIData(&moveUI, &menuUI, &attackUI, &cameraUI);
	textFont = CreateFontToHandle("Data/Font/Honoka_Shin_Mincho_L.otf", 24, 32, DX_FONTTYPE_NORMAL);
}
/// <summary>
/// デストラクタ
/// </summary>
OperationUI::~OperationUI()
{
	//処理なし
}
/// <summary>
/// 更新
/// </summary>
const void OperationUI::Update(const bool _isMove)
{
	if (!_isMove)
	{
		alpha += ADD_ALPHA_VALUE;
		if (alpha > MAX_ALPHA)
		{
			alpha = MAX_ALPHA;
		}
	}
	else
	{
		alpha = MIN_ALPHA;
	}
}
/// <summary>
/// 描画
/// </summary>
const void OperationUI::Draw(const VECTOR _bonfirePos, const VECTOR _playerPos)
{
	VECTOR bonfirePos = _bonfirePos;
	bonfirePos.y = 0;
	VECTOR fireToPlayer = VSub(_bonfirePos, _playerPos);
	float vecSize = VSize(fireToPlayer);

	if (vecSize < 30.0f)
	{
		DrawExtendGraph(BONFIRE_MENU_UI_DRAW_RECT.LX, BONFIRE_MENU_UI_DRAW_RECT.LY, BONFIRE_MENU_UI_DRAW_RECT.RX, BONFIRE_MENU_UI_DRAW_RECT.RY, menuUI, TRUE);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	//文字用の背景画像の描画
	DrawBox(BACKGROUND_POS_FOR_DESCRIPTION.LX, BACKGROUND_POS_FOR_DESCRIPTION.LY, BACKGROUND_POS_FOR_DESCRIPTION.RX, BACKGROUND_POS_FOR_DESCRIPTION.RY, GetColor(0, 0, 0), TRUE);
	DrawStringToHandle(TEXT_POS_FOR_DESCRIPTION.x, TEXT_POS_FOR_DESCRIPTION.y, "敵を倒すと、経験値を取得できます。\nレベルが上がると、ステータスポイントが\n付与されます。", FONT_COLOR, textFont);
	//文字用の背景画像の描画
	DrawExtendGraph(1390, 150, 1500, 230, strongUI, TRUE);
	DrawStringToHandle(TEXT_POS_FOR_DESCRIPTION.x + 70, TEXT_POS_FOR_DESCRIPTION.y + 100, "このマークがついている敵は,\nあなたよりもレベルが上の敵です。\nステータスを強化して挑みましょう。", FONT_COLOR, textFont);
	//文字用の背景画像の描画
	DrawStringToHandle(TEXT_POS_FOR_DESCRIPTION.x, TEXT_POS_FOR_DESCRIPTION.y + 200, "たき火で休むと、体力を回復することが\nできます。\nまたレベルアップメニューを選択すると、\nステータスポイントを消費してステータス\nを強化できます。", FONT_COLOR, textFont);
	//文字用の背景画像の描画
	DrawStringToHandle(TEXT_POS_FOR_DESCRIPTION.x, TEXT_POS_FOR_DESCRIPTION.y + 350, "レベルが一定以上上がると、ゲートが出現\nします。\nゲートをくぐるとボス戦が始まるので、\nステータスを強化して挑みましょう。", FONT_COLOR, textFont);
	DrawExtendGraph(MOVE_UI_DRAW_RECT.LX, MOVE_UI_DRAW_RECT.LY, MOVE_UI_DRAW_RECT.RX, MOVE_UI_DRAW_RECT.RY, moveUI, TRUE);
	DrawExtendGraph(ATTACK_UI_DRAW_RECT.LX, ATTACK_UI_DRAW_RECT.LY, ATTACK_UI_DRAW_RECT.RX, ATTACK_UI_DRAW_RECT.RY, attackUI, TRUE);
	DrawExtendGraph(CAMERA_UI_DRAW_RECT.LX, CAMERA_UI_DRAW_RECT.LY, CAMERA_UI_DRAW_RECT.RX, CAMERA_UI_DRAW_RECT.RY, cameraUI, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_ALPHA);
}