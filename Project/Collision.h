//===========================================================================
//@brief 当たり判定クラス
//===========================================================================
#pragma once
#include"DxLib.h"
#include"Common.h"
class Collision
{
public:
	Collision();//コンストラクタ
	void Init();//初期化
	~Collision();//デストラクタ
	void Delete(int modelHandle);//削除
	//プレイヤーとエネミーの攻撃時当たり判定
	bool OnDamage(const bool _isInvicible, const bool _isDeath, const CapsuleInfo _capsuleInfo, const SphereInfo _sphereInfo);
	
	void SphereSphereCalc();//球と球の当たり判定
	VECTOR NearestPointOfSegmentPointCalc(const VECTOR _startPos,const VECTOR _endPos,const VECTOR _targetPos);//線分と点の最近接点
	bool SphereCapsuleCalc(const VECTOR _capsuleStartPos, const VECTOR _capsuleEndPos, const float _capsuleRadius, const VECTOR _spherePos, const float sphereRadius);//球とカプセルの当たり判定
private:
	//構造体
};