#include "Explosion.h"
/// <summary>
/// コンストラクタ
/// </summary>
Explosion::Explosion()
	: isDraw(false)
	, scale(ORIGIN_POS)
	, rotate(ORIGIN_POS)
{
	modelHandle = MV1LoadModel("Data/Model/Enemy/flame.mv1");
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
const void Explosion::Init()
{
	isDraw = false;
	rotate = ORIGIN_POS;
	scale = ORIGIN_POS;
	sphere.centerPos = ORIGIN_POS;
	sphere.radius = 0.0f;
}
/// <summary>
/// 更新
/// </summary>
const void Explosion::Update(const bool _isDraw,const VECTOR _targetPos)
{
	if (_isDraw)
	{
		//もし前フレームで描画フラグが立っていなかったら描画中心座標を目標の座標に設定し、Y座標を０にし、フラグを立てる
		if (!isDraw)
		{
			sphere.centerPos = _targetPos;
			isDraw = true;
			MV1SetPosition(modelHandle, sphere.centerPos);
		}
		//拡大率の設定
		SetScale(ADD_SCALE);
		SetRotate(ADD_ROTATE);
	}
	else
	{
		Init();
	}
}
/// <summary>
/// 描画
/// </summary>
const void Explosion::Draw()
{
	if (isDraw)
	{
		MV1DrawModel(modelHandle);
	}
}
/// <summary>
/// 拡大率の設定
/// </summary>
const void Explosion::SetScale(const float _scale)
{
	if (scale.x <= MAX_SCALE)
	{
		float prevScale = scale.x;
		float addScale = prevScale + _scale;
		scale = VGet(addScale, addScale, addScale);
		MV1SetScale(modelHandle, scale);
		if (sphere.radius <= MAX_RADIUS)
		{
			sphere.radius += 0.25;
		}
	}
}
/// <summary>
/// 回転率の設定
/// </summary>
const void Explosion::SetRotate(const float _rotate)
{
	/*
	このクラス内では、Y軸をもとにモデルを回転させるため、
	Y座標のみ設定する
	またこの関数内で、回転率の増加も行う
	*/
	float rotateY = rotate.y;
	rotate = VGet(0.0f, rotateY + _rotate, 0.0f);
	MV1SetRotationXYZ(modelHandle, rotate);
}