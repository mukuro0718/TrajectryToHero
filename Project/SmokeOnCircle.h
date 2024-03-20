//===============================================
// @brief 煙クラス
// 敵のスポーン位置に描画
//===============================================

#pragma once
#include<DxLib.h>
class SmokeOnCircle
{
public:
	SmokeOnCircle(const int _graphHandle);	//コンストラクタ
	~SmokeOnCircle();						//デストラクタ

	const void Init(const VECTOR _targetPos); //初期化
	const void Update();					  //更新
	const void Draw();						  //描画
private:
	/*静的定数*/
	static constexpr float	INIT_SCALE			= 15.0f;//初期化用サイズ
	static constexpr int	MAX_SIZE			= 50;	//最大サイズ
	static constexpr int	INIT_ALPHA			= 130;	//初期化用アルファ
	static constexpr int	MAX_ALPHA			= 255;	//最大アルファ
	static constexpr int	MIN_ALPHA			= 0;	//最小アルファ
	static constexpr int	MAX_REMOVE_ALPHA	= 5;	//最大削除アルファ
	/*内部処理関数*/
	const void SetPosAndAlpha();												//座標とアルファの設定
	const float ReturnRandomFloatValue(const int _range, const bool _useSign);	//ランダムでFloat型の値を渡す
	
	/*メンバ変数*/
	VECTOR	centerPos;	//中心座標
	VECTOR	pos;		//座標
	float	scale;		//スケール
	bool	isDrawStart;//描画が始まっているか
	int		removeAlpha;//減少アルファ
	int		alpha;		//アルファ
	int		handle;		//画像ハンドル
};

