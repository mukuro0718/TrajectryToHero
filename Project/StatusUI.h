//=====================================
//@brief ステータスUIクラス
// ステータスUIの描画を行う
//=====================================
#pragma once
#include<DxLib.h>
#include"Common.h"
class StatusUI
{
public:
	StatusUI();//コンストラクタ
	~StatusUI();//デストラクタ

	const void Draw(const int _atkUpCount, const int _defUpCount, const int _agiUpCount);//描画
private:
	/*静的定数*/
	static constexpr VEC2D ATK_IMAGE_POS = { 10,140  };	//攻撃力アイコンの画像を描画する座標
	static constexpr VEC2D DEF_IMAGE_POS = { 10,280 };	//防御力アイコンの画像を描画する座標
	static constexpr VEC2D AGI_IMAGE_POS = { 10,210 };	//素早さアイコンの画像を描画する座標
	static constexpr VEC2D ATK_TEXT_POS	 = { 60,140  };	//攻撃力アイコン用テキストを描画する座標
	static constexpr VEC2D DEF_TEXT_POS  = { 60,280 };	//防御力アイコン用テキストを描画する座標
	static constexpr VEC2D AGI_TEXT_POS  = { 60,210 };	//素早さアイコン用テキストを描画する座標
	static constexpr VEC2D IMAGE_SIZE	 = { 60,60	};	//画像サイズ
	
	static const int FONT_COLOR;//フォントの色
	/*メンバ変数*/
	int atkImageHandle;	//画像ハンドル
	int defImageHandle;	//画像ハンドル
	int agiImageHandle;	//画像ハンドル
	int fontHandle;		//フォントハンドル

};

