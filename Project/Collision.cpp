//===========================================================================
//@brief 当たり判定クラス
//===========================================================================
#include"Collision.h"
/// <summary>
/// コンストラクタ
/// </summary>
Collision::Collision()
{
}
/// <summary>
/// デストラクタ
/// </summary>
Collision::~Collision()
{

}
/// <summary>
/// 初期化
/// </summary>
void Collision::Init()
{
}
/// <summary>
/// 攻撃時当たり判定
/// ダメージ判定を行う場合はtrue,そうでなければfalseを返す
/// </summary>
bool Collision::OnDamage(const bool _isInvicible,const bool _isDeath,const CapsuleInfo _capsuleInfo,const SphereInfo _sphereInfo)
{
	if (!_isInvicible && !_isDeath)
	{
		//球とスフィアの当たり判定をチェック
		bool isHit = SphereCapsuleCalc(_capsuleInfo.topPos,_capsuleInfo.underPos,_capsuleInfo.radius,_sphereInfo.centerPos,_sphereInfo.radius);
		//あたっていたら処理を行う
		if (isHit)
		{
			return true;
		}
	}
	return false;
}
 //<summary>
 //カプセル同士の当たり判定（Y座標は考慮しないため、実際の判定は２Dになる）
 // ２点間の座標と半径の合計を比べる
 //</summary>
VECTOR Collision::CapsuleToCapsuleCollision(const VECTOR _myMoveVec,const VECTOR _myPos,const VECTOR _otherPos,const float _myRadius,const float _otherRadius)
{
	//もし移動していなければ移動量0を返す
	if (_myMoveVec == ORIGIN_POS)
	{
		return ORIGIN_POS;
	}
	VECTOR outPutVec = ORIGIN_POS;
	VECTOR myPos = _myPos;	//自分のベクトル
	VECTOR otherPos = _otherPos;//相手のベクトル
	//2つの座標間のベクトルを求める
	VECTOR myToOtherPos = VSub( otherPos,myPos);
	//ベクトルの大きさを求める
	float myToOtherPosSize = VSize(myToOtherPos);

	float myRadius = _myRadius;		//自分の半径
	float otherRadius = _otherRadius;	//相手の半径
	//二つの半径の合計を求める
	float sumRadius = myRadius + otherRadius;

	//もしベクトルの大きさが半径の合計よりも小さければ当たっている
	if (sumRadius > myToOtherPosSize)
	{
		//ベクトルの大きさと半径の合計の差を求める
		float diff = sumRadius - myToOtherPosSize;
		VECTOR otherToMyPos = VSub(myPos,otherPos);
		//2点間のベクトルを正規化する
		VECTOR otherTomyPosNorm = VNorm(otherToMyPos);
		//正規化したベクトルを差でスケーリングする
		outPutVec = VScale(otherTomyPosNorm,diff);
	}
	return outPutVec;
}

/// <summary>
/// 線分と点の最近接点を返す
/// </summary>
VECTOR Collision::NearestPointOfSegmentPointCalc(const VECTOR _startPos,	const VECTOR _endPos,const VECTOR _targetPos)
{
	VECTOR targetPos = _targetPos;//最近接点を求めたい目標点
	VECTOR startPos = _startPos;//最近接点を求めたい線分開始点
	VECTOR endPos = _endPos;//最近接点を求めたい線分終了点
	VECTOR nearestPos = ORIGIN_POS;//最近接点
	float time = 0.0f;//始点～終点までを0.0f～1.0fとした値
	//始点から終点に伸びたベクトル
	VECTOR segmentVecSE = VSub(_endPos, _startPos);
	//始点からターゲットに伸びたベクトル
	VECTOR segmentVecST = VSub(_targetPos, _startPos);
	//タイムに始点から目標に伸びたベクトルと始点から終点に伸びたベクトルの内積を入れる
	time = VDot(segmentVecST, segmentVecSE);

	//もしタイムが０以下になったら（求めたい目標点が線分の始点の外側にある）
	if (time <= 0.0f)
	{
		//タイムを０にする
		time = 0.0f;
		//最近接点は線分の始点になる
		nearestPos = startPos;
	}
	else
	{
		//同じベクトルの内積を取るため、常に正になり、その値はベクトルのサイズになる
		/*HACK:vecA・vecA = |vecA|^2*/
		float segmentVecSESize = VDot(segmentVecSE, segmentVecSE);
		//ベクトルのサイズがタイムよりも小さければ（求めたい目標点が始点から終点までの範囲外にある）
		if (time >= segmentVecSESize)
		{
			//タイムを１にする
			time = 1.0f;
			//最近接点は線分の終点になる
			nearestPos = endPos;
		}
		//そうでなければ（求めたい目標点が始点から終点までの範囲内にある）
		else
		{
			//タイムに始点～終点と始点～目標点に伸びたベクトルの内積を始点～終点のベクトルのサイズで割る
			time = time / segmentVecSESize;
			//最近接点は始点～終点に伸びたベクトルにタイムをかけたベクトルと始点を足したものになる
			nearestPos = VAdd(startPos,VScale(segmentVecSE, time));
		}
	}
	return nearestPos;
}
bool Collision::SphereCapsuleCalc(const VECTOR _capsuleStartPos,const VECTOR _capsuleEndPos,const float _capsuleRadius,const VECTOR _spherePos,const float sphereRadius)
{
	VECTOR nearestPos = ORIGIN_POS;

	//カプセルの線分と球の中心点もとに最近接点を出す
	nearestPos = NearestPointOfSegmentPointCalc(_capsuleStartPos,_capsuleEndPos,_spherePos);
	//最近接点とスフィアの中心との距離
	VECTOR vecSphNear = VSub(_spherePos,nearestPos);
	//最近接点と球の中心とのサイズが、カプセルの半径＋球の半径より小さかったらtrueを返す
	if (VSize(vecSphNear) < _capsuleRadius + sphereRadius)
	{
		return true;
	}
	return false;
}
/// <summary>
/// カプセル同士の当たり判定
/// </summary>
bool Collision::TwoCapsuleHitCollision(const VECTOR _startPos1, const VECTOR _endPos1, const float _radius1, const VECTOR _startPos2, const VECTOR _endPos2, const float _radius2)
{
	//２つのカプセルの線分を出し、最近点間の距離を得る
	float minLength = Segment_Segment_MinLength(_startPos1,_startPos2,_endPos1,_endPos2);
	//二つのカプセルの半径の合計を求める
	float sumRadius = _radius1 + _radius2;
	//最近点間と半径の合計を比べて、半径の合計＜＝最近点間だったら衝突している
	if (sumRadius <= minLength)
	{
		return true;
	}
	return false;
}