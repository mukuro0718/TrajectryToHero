//===========================================================================
//@brief ゲームクリアクラス
// ゲームクリア時の描画を行う
//===========================================================================
#pragma once
#include "DxLib.h"

class Animation;
class Timer;
class GameClear
{
public:

	GameClear();	// コンストラクタ
	~GameClear();	// デストラクタ

	void Init();	//初期化
	void Final();	//最終処理
	void Update();	//更新
	void Draw();	//描画

	const bool GetIsEndGameClearImage()const { return isEndGameClearImage; }
private:
	/*定数*/
	static constexpr int MAX_GAME_CLEAR_IMAGE_ALPHA = 255;	//最大ゲームクリア画像アルファ値
	static constexpr int MIN_GAME_CLEAR_IMAGE_ALPHA = 0;	//最小ゲームクリア画像アルファ値
	static constexpr int ADD_GAME_CLEAR_IMAGE_ALPHA_VALUE = 2;//ゲームクリア画像アルファ値増加量
	/*クラス*/
	Timer* imageDrawingWait;//画像描画待機時間
	/*内部処理関数*/
	void Create();//作成
	/*変数*/
	int gameClearImageHandle;//ゲームクリア画像ハンドル
	int gameClearImageAlpha;//ゲームクリア画像アルファ値
	int  addGameOverImageAlphaValue;	//ゲームオーバー画像アルファ値増加量
	bool isChangeAlphaValueSign;//アルファ値符号変更フラグ（true:ー false:＋）
	bool isEndGameClearImage;//ゲームクリア画像が終了したか(true:終了している false:終了していない)
	bool isImageDrawingWait;//画像描画待機時間タイマーをスタートしたか(true:スタートしている false:スタートしていない)
	VECTOR playerPos;
};
