//===============================================
// @brief 広がる円クラス
// 敵のスポーン位置に描画
//===============================================
#pragma once
#include<DxLib.h>
class SpreadCircle
{
public:
	SpreadCircle(const int _graphHandle);	//コンストラクタ
	~SpreadCircle();						//デストラクタ
	
	const void Init(const VECTOR _targetPos);	//初期化
	const void Update();						//更新
	const void Draw();							//描画
private:
	/*静的定数*/
	static constexpr float			INIT_SCALE				= 10.0f;		//初期化用スケール
	static constexpr float			ADD_SCALE				= 0.2f;			//増加スケール
	static constexpr int			INIT_ALPHA				= 255;			//初期化用アルファ
	static constexpr int			REMOVE_ALPHA			= -3;			//減少アルファ
	static constexpr int			MIN_ALPHA				= 0;			//最小アルファ
	static constexpr int			VERTEX_NUM				= 4;			//頂点数
	static constexpr int			POLYGON_NUM				= 2;			//ポリゴン数
	static constexpr unsigned short INDEX[POLYGON_NUM * 3]	= {0,1,2,0,2,3};//インデックス
	
	static const VERTEX3D INIT_VERTEX;//初期化用頂点
	/*内部処理関数*/
	const void SetPosAndAlpha();//座標とアルファの設定

	/*メンバ変数*/
	VERTEX3D vertex[VERTEX_NUM];//頂点
	VECTOR	 centerPos;			//中心座標
	float	 scale;				//スケール
	bool	 isDrawStart;		//描画が始まっているか
	int		 alpha;				//アルファ
	int		 handle;			//画像ハンドル
};

