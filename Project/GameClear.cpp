////===========================================================================
////@brief ゲームクリアクラス
//// ゲームクリア時の描画を行う
////===========================================================================
//#include "GameClear.h"
//#include "Common.h"
//#include "Animation.h"
//#include"Load.h"
//#include"Timer.h"
//
//
///// <summary>
///// コンストラクタ
///// </summary>
//GameClear::GameClear()
//{
//	//初期化
//	Init();
//	//ロードクラスのインスタンスを取得
//	auto& load = Load::GetInstance();
//	//画像のロード
//	load.GetGameClearData(&gameClearImageHandle);
//	//作成
//	Create();
//}
///// <summary>
///// デストラクタ
///// </summary>
//GameClear::~GameClear()
//{
//}
///// <summary>
///// 初期化
///// </summary>
//void GameClear::Init()
//{
//	gameClearImageHandle = 0;
//	gameClearImageAlpha  = 0;
//	isChangeAlphaValueSign = false;
//	isEndGameClearImage  = false;
//	isImageDrawingWait   = false;
//	imageDrawingWait	 = NULL;
//}
///// <summary>
///// 作成
///// </summary>
//void GameClear::Create()
//{
//	imageDrawingWait = new Timer();
//	imageDrawingWait->Init(10);
//}
///// <summary>
///// 初期化
///// </summary>
//void GameClear::Final()
//{
//	DeleteGraph(gameClearImageHandle);
//	if (imageDrawingWait)
//	{
//		delete(imageDrawingWait);
//		imageDrawingWait = NULL;
//	}
//}
///// <summary>
///// 更新
///// </summary>
//void GameClear::Update()
//{
//	//ゲームクリア画像を描画
//	if (!isEndGameClearImage)
//	{
//		if (!isImageDrawingWait)
//		{
//			//もし符号変更フラグが立っていたらアルファ値をマイナスする
//			if (isChangeAlphaValueSign)
//			{
//				gameClearImageAlpha -= ADD_GAME_CLEAR_IMAGE_ALPHA_VALUE;
//			}
//			//そうでなければプラスする
//			else
//			{
//				gameClearImageAlpha += ADD_GAME_CLEAR_IMAGE_ALPHA_VALUE;
//			}
//
//			//アルファ値が最大値よりも大きくなったら
//			if (gameClearImageAlpha >= MAX_GAME_CLEAR_IMAGE_ALPHA)
//			{
//				gameClearImageAlpha = MAX_GAME_CLEAR_IMAGE_ALPHA;
//				//タイマーをスタートさせる
//				imageDrawingWait->StartTimer();
//				//タイマーをスタートしたのでフラグを立てる
//				isImageDrawingWait = true;
//				//アルファ値符号変更フラグを立てる
//				isChangeAlphaValueSign = true;
//			}
//			//アルファ値が最小値よりも小さくなったら
//			if (gameClearImageAlpha <= MIN_GAME_CLEAR_IMAGE_ALPHA)
//			{
//				//フラグを立てる
//				isEndGameClearImage = true;
//			}
//		}
//
//		//もし待機タイマーがスタートしていなかったら
//		if (isImageDrawingWait)
//		{
//			//もし待機タイマーが終了していたら
//			if (imageDrawingWait->CountTimer())
//			{
//				//タイマーを終了する
//				imageDrawingWait->EndTimer();
//				//フラグを下す
//				isImageDrawingWait = false;
//			}
//		}
//	}
//}
///// <summary>
///// 描画
///// </summary>
//void GameClear::Draw()
//{
//	if (!isEndGameClearImage)
//	{
//		// 非選択時の画像の描画（選択されていない画像を薄くする）
//		SetDrawBlendMode(DX_BLENDMODE_ALPHA, gameClearImageAlpha);
//		DrawGraph(0, 0, gameClearImageHandle, TRUE);
//		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//	}
//}
