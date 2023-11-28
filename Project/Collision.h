////===========================================================================
////@brief 当たり判定クラス
////===========================================================================
//#pragma once
//#include"DxLib.h"
//#include"Common.h"
//class Collision
//{
//public:
//	Collision();//コンストラクタ
//	void Init();//初期化
//	~Collision();//デストラクタ
//	void Delete(int modelHandle);//削除
//	//プレイヤーとエネミーの攻撃時当たり判定
//	void OnAttackCollision(int _frameNum, CharacterBase _baseToAttack, CharacterBase _baseToHit, CharacterStatus _statusToHit, CharacterStatus _statusToAttack);
//	//ステータス計算
//	void CalcStatus();
//	//球と球の当たり判定
//	void SphereToSphere(CharacterBase _base1, CharacterBase _base2);
//	//当たり判定後、変更したステータスを返す
//	const CharacterStatus GetStatusToHit()	 const { return statusToHit;	}
//	const CharacterStatus GetStatusToAttack()const { return statusToAttack; }
//	const CharacterBase   GetBaseToHit()	 const { return baseToHit;		}
//	const CharacterBase   GetBaseToAttack()  const { return baseToAttack;	}
//private:
//	//構造体
//	CharacterStatus statusToHit;	//攻撃を受けた側のステータス
//	CharacterStatus statusToAttack;	//攻撃をした側のステータス
//	CharacterBase	baseToHit;		//攻撃を受けた側のベース
//	CharacterBase	baseToAttack;		//攻撃をした側のベース
//};