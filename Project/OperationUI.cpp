#include "OperationUI.h"
#include"Load.h"
/// <summary>
/// コンストラクタ
/// </summary>
OperationUI::OperationUI()
	: alpha(MAX_ALPHA)
	, moveUI(0)
	, menuUI(0)
	, attackUI(0)
	, cameraUI(0)
{
	auto& load = Load::GetInstance();
	load.GetOpeUIData(&moveUI, &menuUI, &attackUI, &cameraUI);
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
void OperationUI::Update(const bool _isMove)
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
void OperationUI::Draw(const VECTOR _bonfirePos, const VECTOR _playerPos)
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
	DrawExtendGraph(MOVE_UI_DRAW_RECT.LX, MOVE_UI_DRAW_RECT.LY, MOVE_UI_DRAW_RECT.RX, MOVE_UI_DRAW_RECT.RY, moveUI, TRUE);
	DrawExtendGraph(ATTACK_UI_DRAW_RECT.LX, ATTACK_UI_DRAW_RECT.LY, ATTACK_UI_DRAW_RECT.RX, ATTACK_UI_DRAW_RECT.RY, attackUI, TRUE);
	DrawExtendGraph(CAMERA_UI_DRAW_RECT.LX, CAMERA_UI_DRAW_RECT.LY, CAMERA_UI_DRAW_RECT.RX, CAMERA_UI_DRAW_RECT.RY, cameraUI, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_ALPHA);
}