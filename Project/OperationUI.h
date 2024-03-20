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

	const void Update(const bool _isMove);								//更新
	const void Draw(const VECTOR _bonfirePos, const VECTOR _playerPos);	//描画
private:
	/*構造体・列挙体*/
	struct DrawRect
	{
		int LX = 0;
		int LY = 0;
		int RX = 0;
		int RY = 0;
	};
	/*静的定数*/
	static constexpr DrawRect	BACKGROUND_POS_FOR_DESCRIPTION	= { 1400,30,1910,520 };	//背景描画座標
	static constexpr DrawRect	BONFIRE_MENU_UI_DRAW_RECT		= { 1120,660,1320,700 };//焚火メニュー描画位置
	static constexpr VEC2D		TEXT_POS_FOR_DESCRIPTION		= { 1420,50 };			//テキスト描画位置
	static constexpr DrawRect	ATTACK_UI_DRAW_RECT				= { 1670,860,1870,910 };//攻撃UI描画範囲
	static constexpr DrawRect	CAMERA_UI_DRAW_RECT				= { 1670,920,1870,970 };//カメラUI描画範囲
	static constexpr DrawRect	MOVE_UI_DRAW_RECT				= { 1670,800,1870,850 };//移動UI描画範囲
	static constexpr int		ADD_ALPHA_VALUE					= 5;					//追加アルファ/
	static constexpr int		MAX_ALPHA						= 255;					//最大アルファ
	static constexpr int		MIN_ALPHA						= 0;					//最小アルファ
	static const int FONT_COLOR;//フォントの色


	/*メンバ変数*/
	int alpha;		//アルファ
	//操作方法UI画像
	int moveUI;		//移動
	int menuUI;		//メニュー
	int attackUI;	//攻撃UI
	int cameraUI;	//カメラUI
	int textFont;	//テキスト
	int strongUI;	//強敵マーク
};

