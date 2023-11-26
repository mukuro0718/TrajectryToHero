////===========================================================================
////@brief ゲームオーバークラス
//// ゲームオーバー時の描画を行う
////===========================================================================
//#pragma once
//#include "DxLib.h"
//#include<vector>
//
//class Timer;
//
//using namespace std;
//
//class GameOver
//{
//public:
//
//	GameOver();	// コンストラクタ
//	~GameOver();	// デストラクタ
//
//	void Init();	//初期化
//	void Final();	//最終処理
//	void Update();	//更新
//	void Draw();	//描画
//
//	const bool GetIsEndGameOverImage()const { return isEndGameOverImage; }
//private:
//	static constexpr int MAX_GAME_CLEAR_IMAGE_ALPHA = 255;	//最大ゲームクリア画像アルファ値
//	static constexpr int MIN_GAME_CLEAR_IMAGE_ALPHA = 0;	//最小ゲームクリア画像アルファ値
//	static constexpr int ADD_GAME_CLEAR_IMAGE_ALPHA_VALUE = 2;//ゲームクリア画像アルファ値増加量
//	Timer* imageDrawingWait;	//画像描画待機時間
//	/*内部処理関数*/
//	void Create();//作成
//	/*変数*/
//	int  gameOverImageHandle;			//ゲームオーバー画像ハンドル
//	int  gameOverImageAlpha;			//ゲームオーバー画像アルファ値
//	int  addGameOverImageAlphaValue;	//ゲームオーバー画像アルファ値増加量
//	bool isChangeAlphaValueSign;		//アルファ値符号変更フラグ（true:ー false:＋）
//	bool isEndGameOverImage;			//ゲームオーバー画像が終了したか(true:終了している false:終了していない)
//	bool isImageDrawingWait;			//画像描画待機時間タイマーをスタートしたか(true:スタートしている false:スタートしていない)
//};
