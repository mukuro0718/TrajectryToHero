//===================================
//@brief 操作UIの描画クラス
//待機時に操作説明用のUIを描画する
//===================================
#pragma once
#include<DxLib.h>
#include"Common.h"

class OperationUI
{
public:
	OperationUI();//コンストラクタ
	~OperationUI();//デストラクタ

	void Update(const bool _isMove);//更新
	void Draw(const VECTOR _bonfirePos, const VECTOR _playerPos);//描画
private:
	struct DrawRect
	{
		int LX = 0;
		int LY = 0;
		int RX = 0;
		int RY = 0;
	};
	/*静的定数*/
	static constexpr DrawRect MOVE_UI_DRAW_RECT = { 1670,800,1870,850 };//移動UI描画範囲
	static constexpr DrawRect ATTACK_UI_DRAW_RECT = { 1670,860,1870,910 };//攻撃UI描画範囲
	static constexpr DrawRect CAMERA_UI_DRAW_RECT = { 1670,920,1870,970 };//カメラUI描画範囲
	static constexpr DrawRect BONFIRE_MENU_UI_DRAW_RECT = { 1120,660,1320,700 };
	static constexpr int ADD_ALPHA_VALUE = 5;
	static constexpr int MAX_ALPHA = 255;
	static constexpr int MIN_ALPHA = 0;
	static constexpr DrawRect BACKGROUND_POS_FOR_DESCRIPTION = { 1400,30,1910,520 };
	static constexpr VEC2D TEXT_POS_FOR_DESCRIPTION = { 1420,50 };
	static const int FONT_COLOR;//フォントの色


	/*メンバ変数*/
	int alpha;
	int moveUI;
	int menuUI;
	int attackUI;
	int cameraUI;
	int textFont;
	int strongUI;
};

