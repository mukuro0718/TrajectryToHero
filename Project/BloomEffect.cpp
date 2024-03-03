#include "BloomEffect.h"

/// <summary>
/// コンストラクタ
/// </summary>
BloomEffect::BloomEffect()
	:colorScreen(0)
	,highBrightScreen(0)
	,downScaleScreen(0)
	,gaussScreen(0)
	, GaussRatio(900)
{

}
/// <summary>
/// デストラクタ
/// </summary>
BloomEffect::~BloomEffect()
{

}
/// <summary>
/// スクリーンの作成
/// </summary>
const void BloomEffect::MakeBloomScreen()
{
	// 通常の描画結果を書き込むスクリーンと、フィルターの処理結果を書き込むスクリーンの作成
	colorScreen = MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, FALSE);
	highBrightScreen = MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, FALSE);
	downScaleScreen = MakeScreen(DOWN_SCALE_SCREEN_WIDTH, DOWN_SCALE_SCREEN_HEIGHT, FALSE);
	gaussScreen = MakeScreen(DOWN_SCALE_SCREEN_WIDTH, DOWN_SCALE_SCREEN_HEIGHT, FALSE);
}
/// <summary>
/// 更新
/// </summary>
const void BloomEffect::Update()
{
	// 上下キーが押されたらガウスフィルタのぼかし度合いを変更する
	if (CheckHitKey(KEY_INPUT_UP))
	{
		GaussRatio++;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		if (GaussRatio > 0)
		{
			GaussRatio--;
		}
	}
}
/// <summary>
/// 描画するスクリーンを設定
/// </summary>
const void BloomEffect::SetDrawScreenType()
{
	SetDrawScreen(colorScreen);
}
/// <summary>
/// ガウスでぼかした画像を得る
/// </summary>
/// <returns></returns>
const void BloomEffect::GetImage()
{
	// 描画結果から高輝度部分のみを抜き出した画像を得る
	GraphFilterBlt(colorScreen, highBrightScreen, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 230, TRUE, GetColor(0, 0, 0), 255);

	// 高輝度部分を８分の１に縮小した画像を得る
	GraphFilterBlt(highBrightScreen, downScaleScreen, DX_GRAPH_FILTER_DOWN_SCALE, DOWN_SCALE);

	// ８分の１に縮小した画像をガウスフィルタでぼかす
	GraphFilterBlt(downScaleScreen, gaussScreen, DX_GRAPH_FILTER_GAUSS, 16, GaussRatio);
}
const void BloomEffect::DrawNormalGraph()
{
	// 描画対象を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);
	// 通常の描画結果を描画する
	DrawGraph(0, 0, colorScreen, FALSE);
}
const void BloomEffect::DrawGaussBlendGraph()
{
	// 描画モードをバイリニアフィルタリングにする( 拡大したときにドットがぼやけるようにする )
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	// 描画ブレンドモードを加算にする
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	// 高輝度部分を縮小してぼかした画像を画面いっぱいに２回描画する( ２回描画するのはより明るくみえるようにするため )
	DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, gaussScreen, FALSE);
	DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, gaussScreen, FALSE);

	// 描画ブレンドモードをブレンド無しに戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// 描画モードを二アレストに戻す
	SetDrawMode(DX_DRAWMODE_NEAREST);


	// フィルター処理の途中経過が分かるように画面下部に縮小して描画する
	DrawExtendGraph(180 * 0 + 24, 320, 180 * 0 + 24 + 160, 120 + 320, highBrightScreen, FALSE);
	DrawExtendGraph(180 * 1 + 24, 320, 180 * 1 + 24 + 160, 120 + 320, downScaleScreen, FALSE);
	DrawExtendGraph(180 * 2 + 24, 320, 180 * 2 + 24 + 160, 120 + 320, gaussScreen, FALSE);

	// 現在のガウスフィルタのぼかし度合いを描画する
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Gauss:%d", GaussRatio);
}