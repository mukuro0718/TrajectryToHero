#include "Explosion.h"
const int Explosion::COLOR = GetColor(60, 10, 10);
/// <summary>
/// コンストラクタ
/// </summary>
Explosion::Explosion()
	: alpha(MIN_ALPHA_VALUE)
	, isDraw(false)
{
	Init();
}
/// <summary>
/// デストラクタ
/// </summary>
Explosion::~Explosion()
{

}
/// <summary>
/// 初期化
/// </summary>
void Explosion::Init()
{
	sphereInfo.centerPos = ORIGIN_POS;
	sphereInfo.radius = MIN_RADIUS_RANGE;
	sphereInfo.divNum = DIV_NUM;
	sphereInfo.fillFlag = FILL_FLAG;
	sphereInfo.difColor = COLOR;
	sphereInfo.spcColor = COLOR;
	alpha = MAX_ALPHA_VALUE;
	isDraw = false;
	isInit = false;
}
/// <summary>
/// 更新
/// </summary>
void Explosion::Update(const bool _isDraw,const VECTOR _targetPos)
{
	if (_isDraw)
	{
		//もし前フレームで描画フラグが立っていなかったら描画中心座標を目標の座標に設定し、Y座標を０にし、フラグを立てる
		if (!isDraw)
		{
			sphereInfo.centerPos = _targetPos;
			sphereInfo.centerPos.y = 0.0f;
			isDraw = true;
		}
		//半径を増加させる
		sphereInfo.radius += ADD_RADIUS_VALUE;
		//半径が最大値を超えないようにする
		if (sphereInfo.radius >= MAX_RADIUS_RANGE)
		{
			sphereInfo.radius = MAX_RADIUS_RANGE;
		}
	}
	else
	{
		//アルファ値を減少させる
		alpha -= ADD_ALPHA_VALUE;
		//アルファ値が最小値を下回らないようにする
		if (alpha <= MIN_ALPHA_VALUE)
		{
			alpha = MIN_ALPHA_VALUE;
			isInit = false;
		}

		if (!isInit)
		{
			Init();
			isInit = true;
		}
	}
}
/// <summary>
/// 描画
/// </summary>
void Explosion::Draw()
{
	if (isDraw)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawSphere3D(sphereInfo.centerPos,sphereInfo.radius,sphereInfo.divNum, sphereInfo.difColor, sphereInfo.spcColor, sphereInfo.fillFlag);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,MAX_ALPHA_VALUE);
	}
}