#pragma once
#include<DxLib.h>
class BloomEffect
{
public:
	BloomEffect();
	~BloomEffect();
	const void MakeBloomScreen();
	const void Update();
	const void SetDrawScreenType();
	const void GetImage();
	const void DrawNormalGraph();
	const void DrawGaussBlendGraph();
	const int GetScreenWidth()const { return SCREEN_WIDTH; }
	const int GetScreenHeight()const { return SCREEN_HEIGHT; }
	const int GetDownScaleScreenWidth()const { return DOWN_SCALE_SCREEN_WIDTH; }
	const int GetDownScaleScreenHeight()const { return DOWN_SCALE_SCREEN_HEIGHT; }
private:
	/*静的定数*/
	static constexpr int SCREEN_WIDTH = 1920;//画面の横サイズ
	static constexpr int SCREEN_HEIGHT = 1080;//画面の縦サイズ
	static constexpr int DOWN_SCALE = 8;// ガウスフィルタを掛ける画像が画面のサイズの何分の１か
	static constexpr int DOWN_SCALE_SCREEN_WIDTH = SCREEN_WIDTH / DOWN_SCALE;// ガウスフィルタを掛ける画像の横幅
	static constexpr int DOWN_SCALE_SCREEN_HEIGHT = SCREEN_HEIGHT / DOWN_SCALE;// ガウスフィルタを掛ける画像の縦幅
	/*メンバ変数*/
	int colorScreen;	// 普通の描画結果を書き込むスクリーン
	int highBrightScreen;	// 普通の描画結果から高輝度部分を抜き出した結果を書き込むスクリーン
	int downScaleScreen;	// 高輝度部分を縮小した結果を書き込むスクリーン
	int gaussScreen;	// 縮小画像をガウスフィルタでぼかした結果を書き込むスクリーン
	int GaussRatio;	// ガウスフィルタのぼかし度合い
};

