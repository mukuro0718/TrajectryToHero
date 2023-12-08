//===========================================================================
//@brief 画面ブラークラス
// 参考URL:https://qiita.com/himego/items/c043ca5d58912b9a58d2
//===========================================================================
#pragma once
#include<DxLib.h>
#include<vector>
class BlurScreen
{
public:
	BlurScreen();//コンストラクタ
	~BlurScreen();//デストラクタ

	void Init(const int _alpha, const int _offsetX1, const int _offsetY1, const int _offsetX2, const int _offsetY2);
	void ReplayInit();
	void Delete();

	void PreRenderBlurScreen();

	void PostRenderBlurScreen();
private:
	static constexpr int SCREEN_INDEX = 2;//スクリーン変数の添え字
	static constexpr int SCREEN_INIT_VALUE = -1;//スクリーン変数初期化値
	int screen[SCREEN_INDEX];//スクリーン変数
	int current;
	int alpha;
	int screenWidth, screenHeight;
	int offsetX1, offsetX2, offsetY1, offsetY2;
	int notBlendDraw;
};
