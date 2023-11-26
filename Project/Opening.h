//===========================================================================
//@brief オープニングクラス
// 使用した言語、サイトなどの画像を描画
//===========================================================================
#pragma once
#include"DxLib.h"
#include<vector>
#include"Common.h"
using namespace std;

class Opening final
{
public:
	Opening();	//コンストラクタ
	~Opening();	//デストラクタ

	void Init();	//初期化
	void Update();	//更新
	void Draw();	//描画

	// オープニング終了フラグの getter
	const bool& GetIsEndOpening() const { return isEndOpening; }
private:
	/*定数*/
	enum class ImageType//画像タイプ
	{
		SE_SITE,	//SEサイト
		MODEL_SITE,	//モデルサイト
		MUSIC_SITE,	//使用した音楽サイト
		LANGUAGE,	//使用言語（開発環境）
	};
	static constexpr float LAST_TIMER	= 60.0f;	//タイマー最大値
	static constexpr float FIRST_TIMER	= 0.0f;		//タイマー初期化値
	static constexpr int   MAX_ALPHA	= 255;		//最大アルファ値
	static constexpr int   MIN_ALPHA	= 0;		//最小アルファ値
	static constexpr int   ALPHA_COUNT	= 5;		//アルファ値増加量
	static constexpr VEC2D IMAGE_POS	= { 0,0 };	//画像描画座標
	/*内部処理関数*/
	void CountProcess();	//カウント処理
	void EndOpening();		//オープニング終了
	/*メンバ変数*/
	vector<int> image;				//画像ハンドル
	int			nowShowImageType;	//描画する画像の種類
	int			alpha;				//ブレンドするアルファ値
	bool		isChangeAlpha;		//アルファ値変更フラグ
	bool		isEndOpening;		//オープニング終了フラグ
	float		changeTimer;		//表示画像切り替えタイマー
};
