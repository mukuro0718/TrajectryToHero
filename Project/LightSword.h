//=====================================================
//光の剣エフェクトクラス
// 半透明の黄色い剣を描画し、ブルームクラスによって光らせる
//=====================================================
#pragma once
#include<DxLib.h>

class LightSword
{
public:
	LightSword();	//コンストラクタ
	~LightSword();	//デストラクタ
	const void Update(const VECTOR _bladeUnderPos, const VECTOR _bladeMiddlePos, const VECTOR _bladeTopPos);//更新
	const void Draw();//描画

private:
	/*静的定数*/
	static constexpr int BLADE_VERTEX_NUM = 9;								//刃頂点数
	static constexpr int POLYGON_NUM = 12;									//ポリゴン数
	static constexpr unsigned short BLADE_VERTEX_INDEX[POLYGON_NUM * 3] =	//頂点インデックス
	{ 
		0,1,2,
		0,2,3,
		0,3,4,
		0,4,1,
		1,4,8,
		1,8,5,
		2,1,5,
		2,5,6,
		3,2,6,
		3,6,7,
		4,3,7,
		4,7,8,
	};
	static constexpr float OFFSET_VALUE = 3.0f;	//オフセット値
	static constexpr float BLADE_SCALE = 5.0f;	//大きさ
	static constexpr int VERTEX_FOR_ROTATE_NUM = 3;//頂点数

	static const VECTOR	  VERTEX_FOR_ROTATE[VERTEX_FOR_ROTATE_NUM];	//内積の角度が90度になるような位置関係の頂点群
	static const VERTEX3D INIT_VERTEX;								//初期化用頂点構造体
	/*内部処理関数*/
	const void MakeRotateMatrix();   //必要な回転行列を作る
	const void MakeBladeVertex(const VECTOR _bladeVec, const VECTOR _sickleVec);//刃のベクトルを作る

	/*静的定数*/
	VERTEX3D bladeVertex[BLADE_VERTEX_NUM];	//頂点
	/*回転マトリックスを出すための変数群*/
	MATRIX rotateMatrix;//blade,sickleの頂点のもとになる座標を出すための回転行列
};

