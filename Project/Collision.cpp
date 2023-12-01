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
 //球と球の当たり判定
 //</summary>
//void Collision::SphereToSphere(CharacterBase _base1, CharacterBase _base2)
//{
//	//チェック対象のベース
//	baseToAttack = _base1;
//	//ほかの対象のベース
//	baseToHit = _base2;
//	//２つのベースの座標が同じだったら処理をしない
//	//（敵の番号を出してそれが同じだったら処理をしないようにしたほうが良いかも）
//	if (baseToAttack.pos == baseToHit.pos || baseToAttack.isHit == true){}
//	else
//	{
//		int isHit = HitCheck_Sphere_Sphere(baseToAttack.pos, baseToAttack.radius, baseToHit.pos, baseToHit.radius);
//		if (isHit > 0)
//		{
//			//自分から当たり判定を行う相手へ向いたベクトルを出す
//			VECTOR myToOther = VSub(baseToHit.pos, baseToAttack.pos);
//			//myToOtherの逆ベクトル
//			VECTOR otherToMy = VSub(baseToAttack.pos, baseToAttack.pos);
//
//			//めり込み量＝（自分の半径＋当たり判定を行う相手半径）ーベクトルABの大きさ
//			float pushBackValue = (baseToAttack.radius + baseToHit.radius) - VSize(myToOther);
//			//逆ベクトルを正規化する
//			VECTOR myToOtherNorm = VNorm(otherToMy);
//			baseToAttack.correctionValue = VScale(myToOtherNorm,pushBackValue);
//			baseToAttack.isHit = true;
//		}
//	}
//}

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