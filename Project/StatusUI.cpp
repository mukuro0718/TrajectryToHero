#include "StatusUI.h"
#include "Load.h"

const int StatusUI::FONT_COLOR = GetColor(255, 255, 255);//フォントの色

/// <summary>
/// コンストラクタ
/// </summary>
StatusUI::StatusUI()
	:atkImageHandle(0)
	,defImageHandle(0)
	,agiImageHandle(0)
	,fontHandle(0)
{
	auto& load = Load::GetInstance();
	load.GetStatusUIData(&atkImageHandle, &defImageHandle, &agiImageHandle, &fontHandle);
}
/// <summary>
/// デストラクタ
/// </summary>
StatusUI::~StatusUI()
{

}
/// <summary>
/// 更新
/// </summary>
void StatusUI::Update()
{

}
/// <summary>
/// 描画
/// </summary>
void StatusUI::Draw(const int _atkUpCount, const int _defUpCount, const int _agiUpCount)
{
	DrawGraph(ATK_IMAGE_POS.x, ATK_IMAGE_POS.y, atkImageHandle, TRUE);
	DrawGraph(DEF_IMAGE_POS.x, DEF_IMAGE_POS.y, defImageHandle, TRUE);
	DrawGraph(AGI_IMAGE_POS.x, AGI_IMAGE_POS.y, agiImageHandle, TRUE);
	DrawFormatStringToHandle(ATK_TEXT_POS.x, ATK_TEXT_POS.y, FONT_COLOR, fontHandle, "×%d", _atkUpCount);
	DrawFormatStringToHandle(DEF_TEXT_POS.x, DEF_TEXT_POS.y, FONT_COLOR, fontHandle, "×%d", _defUpCount);
	DrawFormatStringToHandle(AGI_TEXT_POS.x, AGI_TEXT_POS.y, FONT_COLOR, fontHandle, "×%d", _agiUpCount);
}