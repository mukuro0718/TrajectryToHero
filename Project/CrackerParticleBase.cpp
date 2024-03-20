#include "CrackerParticleBase.h"
#include "Common.h"
/// <summary>
/// コンストラクタ
/// </summary>
CrackerParticleBase::CrackerParticleBase(const int _color)
	:color(_color)
	, vertexPos1(ORIGIN_POS)
	, vertexPos2(ORIGIN_POS)
	, vertexPos3(ORIGIN_POS)
	, vertexPos2Offset(ORIGIN_POS)
	, vertexPos3Offset(ORIGIN_POS)
	, moveVec(ORIGIN_POS)
	, initPos(ORIGIN_POS)
	, speed(0.0f)
	, size(0.0f)
	, isDraw(false)
	, count(0)
{
	
}
/// <summary>
/// デストラクタ
/// </summary>
CrackerParticleBase::~CrackerParticleBase()
{

}
const void CrackerParticleBase::Init(const VECTOR _initPos)
{
	if (!isDraw)
	{
		//ベクトルをスケーリングするサイズを求める
		size = ReturnRandomFloatValue(false, SIZE_RANGE) + 5;
		//速さを求める
		speed = ReturnRandomFloatValue(false, SPEED_RANGE) + 5;
		isDraw = true;
		//基準となる座標を出す
		initPos = _initPos;
		//高さをばらつかせる
		initPos.x += ReturnRandomFloatValue(false, X_LIMIT);
		initPos.y -= ReturnRandomFloatValue(true, POS_RANGE);
		vertexPos1 = initPos;
		/*Pos2,Pos3を決める*/
		//オフセット座標を出す
		vertexPos2Offset = VGet(ReturnRandomFloatValue(true, POS_RANGE), ReturnRandomFloatValue(true, POS_RANGE), 0.0f);
		vertexPos3Offset = VGet(ReturnRandomFloatValue(true, POS_RANGE), ReturnRandomFloatValue(true, POS_RANGE), 0.0f);
		//基準となる座標に足す
		vertexPos2Offset = VAdd(vertexPos1, vertexPos2Offset);
		vertexPos3Offset = VAdd(vertexPos1, vertexPos3Offset);
		//基準となる座標から上で求めた座標へ伸びるベクトルを求める
		vertexPos2Offset = VSub(vertexPos1, vertexPos2Offset);
		vertexPos3Offset = VSub(vertexPos1, vertexPos3Offset);
		//上で求めたベクトルを正規化する
		vertexPos2Offset = VNorm(vertexPos2Offset);
		vertexPos3Offset = VNorm(vertexPos3Offset);
		//正規化したベクトルをサイズでスケーリングする
		vertexPos2Offset = VScale(vertexPos2Offset, size);
		vertexPos3Offset = VScale(vertexPos3Offset, size);

		vertexPos2 = VAdd(vertexPos1, vertexPos2Offset);
		vertexPos3 = VAdd(vertexPos1, vertexPos3Offset);

	}
}
/// <summary>
/// 更新
/// </summary>
const void CrackerParticleBase::Update()
{
	if (isDraw)
	{
		//基準となる座標にスピードを足す

		vertexPos1.y -= speed;
		//基準をもとにほかの座標を出す
		if (vertexPos1.y <= Y_LIMIT)
		{
			vertexPos1 = initPos;
			count++;
		}
		vertexPos2 = VAdd(vertexPos1, vertexPos2Offset);
		vertexPos3 = VAdd(vertexPos1, vertexPos3Offset);
	}
}
/// <summary>
/// 描画
/// </summary>
const void CrackerParticleBase::Draw()
{
	if (isDraw)
	{
		DrawTriangle(static_cast<int>(vertexPos1.x), static_cast<int>(vertexPos1.y), static_cast<int>(vertexPos2.x), static_cast<int>(vertexPos2.y), static_cast<int>(vertexPos3.x), static_cast<int>(vertexPos3.y), color, TRUE);
		if (count >= MAX_FRAME_COUNT)
		{
			isDraw = false;
			count = 0;
		}
	}
}
/// <summary>
/// ランダムでFloat型の値を返す
/// </summary>
float CrackerParticleBase::ReturnRandomFloatValue(const bool _sign, const int _range)
{
	int outPutValue = 0;
	outPutValue = GetRand(_range) + 1;
	if (_sign)
	{
		if (GetRand(SIGN_RANGE) == 1)
		{
			outPutValue *= -1;
		}
	}
	return static_cast<float>(outPutValue);
}