//=============================================
//ロード画面クラス
// 5つの頂点を保持し、DrawLineで星を描画する
// また頂点の位置を移動させ、動いていることを表す。
//=============================================
#pragma once
#include<DxLib.h>
#include<vector>

class LoadScene
{
public:
	LoadScene();//コンストラクタ
	~LoadScene();//デストラクタ

	const void Init();//初期化
	const void Final();//最終処理
	const void Update();//更新
	const void Draw();//描画
private:
	/*静的定数*/
	static constexpr int ADD_ALPHA					 = 1;	//追加アルファ
	static constexpr int MAX_ALPHA					 = 255;	//最大アルファ
	static constexpr int MIN_ALPHA					 = 0;	//最小アルファ
	static constexpr int FONT_SIZE					 = 32;	//フォントの大きさ
	static constexpr int MAX_IS_INC_WAIT_FRAME_COUNT = 60;	//最大フレームカウント
	static constexpr int MAX_UPDATE_WAIT_FRAME_COUNT = 80;	//最大フレームカウント
	static constexpr int X							 = 1620;//Ｘ座標
	static constexpr int Y							 = 980;	//Ｙ座標

	static const int FONT_COLOR;//フォントの色

	/*メンバ変数*/
	int alpha;					//アルファ
	int isIncWaitFrameCount;	//フレームカウント
	int updateWaitFrameCount;	//フレームカウント
	bool isIncTheValue;			//値が増加しているか(TRUE:増加 FALSE:減少 )
};

