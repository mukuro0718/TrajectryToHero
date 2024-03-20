//===========================================================================
//@brief 画面ブラークラス
// 参考URL https://haina.hatenablog.com/entry/2016/05/17/230902
// 最初の座標がセットされたらタイマーをスタートさせる
// タイマーが目標時間に達したらその時の座標をまた記憶する
// 現在の軌跡は保存している頂点数が少なく、角ばっているため、時間があるときに
// スプライン曲線を使う
//===========================================================================
#pragma once
#include<DxLib.h>
#include<vector>

class Timer;

class SwordTrail
{
public:
	SwordTrail();	//コンストラクタ
	~SwordTrail();	//デストラクタ

	const void Init();													//初期化
	const void Update(const VECTOR _topPos, const VECTOR _underPos);	//更新
	const void Draw();													//描画
	const void Delete();												//削除
	const void StartTimer();											//タイマーを始める
	/*getter*/
	const bool GetIsStartTimer();
private:
	/*静的定数*/
	static constexpr int VERTEX_POS_NUM	 = 10;	//頂点座標数
	static constexpr int MAX_ALPHA_VALUE = 100;	//最大アルファ値
	static constexpr int ADD_ALPHA_VALUE = 10;	//アルファ値増加量

	static const VERTEX3D INIT_VERTEX;	//初期頂点情報
	static const COLOR_U8 TRAIL_COLOR;	//軌跡の色
	static const VECTOR	  VERTEX_NORM;	//法線ベクトル
	
	/*内部処理関数*/
	const VERTEX3D	SetVertexInfo(const VECTOR _pos);//頂点情報の設定
	const void		SetVertexAd();					 //頂点アドレスの設定
	const void		SetAlpha();						 //アルファ値の設定

	/*メンバ変数*/
	Timer* drawTimer;//描画用タイマー
	
	//頂点インデックス配列へのアドレス
	//ポリゴンを描画するときに、頂点座標配列のどの頂点を使うのかを決める
	//例：1番、２番、３番の頂点を使うとき
	//index[0] = 1,index[1] = 2,index[2] = 3
	std::vector<VERTEX3D> vertexInfo;	//頂点座標
	std::vector<WORD>	  vertexIndexAd;//頂点インデックス
	std::vector<int>	  alphaValue;	//アルファ値
	
	bool isDraw;				//描画するか
	int	 frameCount;				//アルファ値増減用フレームカウント
	int  vertexSetWaitFrameCount;//頂点設定待機時間
	int  holdVertexNum;			//保持している頂点数
	int  assignAd;				//代入するアドレス
	/*
	HAKC:
	<WORD>
	unsigned int型 typedefで名前をつけたもの
	これにより,WORDでもunsigned intがたの変数として使える
	<COLOR_U8>
	unsigned char型のカラー値
	通常のRGBに加え、透明度を表すアルファ値も設定できる
	*/
};
