////===========================================================================
////@brief 当たり判定クラス
////===========================================================================
//#include"Collision.h"
///// <summary>
///// コンストラクタ
///// </summary>
//Collision::Collision()
//{
//}
///// <summary>
///// デストラクタ
///// </summary>
//Collision::~Collision()
//{
//
//}
///// <summary>
///// 初期化
///// </summary>
//void Collision::Init()
//{
//}
///// <summary>
///// 攻撃時当たり判定
///// </summary>
///// <param name="baseToAttack">攻撃したベース</param>
///// <param name="baseToHit">攻撃を受けた側のベース</param>
///// <param name="statusToHit">攻撃を受けた側のステータス</param>
///// <param name="statusToAttack">攻撃したステータス</param>
//void Collision::OnAttackCollision(int _frameNum, CharacterBase _baseToAttack, CharacterBase _baseToHit, CharacterStatus _statusToHit, CharacterStatus _statusToAttack)
//{
//	statusToHit = _statusToHit;
//	statusToAttack = _statusToAttack;
//	if (!statusToHit.isInvincible && !baseToHit.isDeath)
//	{
//		//攻撃側と受け手側の選択している行動の有利不利の判定
//		//当たり判定構造体
//		MV1_COLL_RESULT_POLY_DIM hitPolyDim;
//		/*VECTOR pos = VGet(_baseToHit.pos.x, _baseToHit.pos.y + 20.0f, _baseToHit.pos.z);*/
//		VECTOR underPos = baseToHit.pos;
//		VECTOR topPos = VGet(_baseToHit.pos.x, _baseToHit.pos.y + 30.0f, _baseToHit.pos.z);
//		//モデルとスフィアの当たり判定をチェック
//		//hitPolyDim = MV1CollCheck_Sphere(_baseToAttack.modelHandle, _frameNum, pos, _baseToHit.radius);
//		hitPolyDim = MV1CollCheck_Capsule(_baseToAttack.modelHandle, _frameNum, underPos,topPos, _baseToHit.radius);
//		//一度でもあたっていたら処理を行う
//		if (hitPolyDim.HitNum >= 1 && !statusToHit.isHit)
//		{
//			statusToHit.isInvincible = true;
//			CalcStatus();
//		}
//		//後始末
//		MV1CollResultPolyDimTerminate(hitPolyDim);
//	}
//}
///// <summary>
///// 攻撃時のステータス計算
///// </summary>
///// <param name="statusToHit">攻撃が当たった側のステータス</param>
///// <param name="statusToAttack">攻撃した側のステータス</param>
//void Collision::CalcStatus()
//{
//	statusToHit.isInvincible = true;
//	//HP計算
//	statusToHit.HP -= statusToAttack.ATK / statusToHit.DEF;
//
//	//HPが０だったらEXPを増やす
//	if (statusToHit.HP < 0)
//	{
//		statusToAttack.EXP += statusToHit.EXP_TO_GIVE;
//	}
//}
///// <summary>
///// 球と球の当たり判定
///// </summary>
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