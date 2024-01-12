#include"StrongEnemy.h"
#include<math.h>
#include"Animation.h"
#include"CharacterStatus.h"
#include"Timer.h"
#include"BloodParticle.h"

//モデル設定
const VECTOR StrongEnemy::MODEL_SCALE = VGet(0.3f, 0.3f, 0.3f);//モデルの拡大率
const VECTOR StrongEnemy::MODEL_ROTATE = VGet(0.0f, 90 * DX_PI_F / 180.0f, 0.0f);//モデルの回転値


/// <summary>
/// コンストラクタ
/// </summary>
StrongEnemy::StrongEnemy(const VECTOR _spawnPos,const int _modelHandle)
	:EnemyBase(_modelHandle)
{
	//インスタンスの初期化
	invincibleTimer = NULL;
	restTimeAfterAttack = NULL;
	anim = NULL;
	//インスタンスの生成
	invincibleTimer = new Timer();
	restTimeAfterAttack = new Timer();
	anim = new Animation();
	spawnPos = _spawnPos;
	Init();
	//モデル設定
	MV1SetScale(modelHandle, scale);
	//回転値のセット
	MV1SetRotationXYZ(modelHandle, rotate);
	//コリジョン情報を構築
	MV1SetupCollInfo(modelHandle, -1, 1, 1, 1);
	//アニメーションの追加
	anim->Add(MV1LoadModel("Data/Animation/StrongEnemy_RunAnim.mv1"), 0);			//走りアニメーション
	anim->Add(MV1LoadModel("Data/Animation/WeakEnemy_StrongAttack.mv1"), 1);		//攻撃アニメーション
	anim->Add(MV1LoadModel("Data/Animation/StrongEnemy_IdleAnim.mv1"), 0);			//待機アニメーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy_DeathAnim_public.mv1"), 0);		//死亡アニメーション
	//アタッチするアニメーション
	anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	//アニメーションのアタッチ
	anim->Attach(&modelHandle);
}
/// <summary>
/// デストラクタ
/// </summary>
StrongEnemy::~StrongEnemy()
{
	Final();
}
/// <summary>
/// 初期化
/// </summary>
void StrongEnemy::Init()
{
	//必要なInitクラスの呼び出し
	invincibleTimer->Init(9);
	restTimeAfterAttack->Init(20);
	status->InitStrongEnemyStatus();
	//新しい座標の生成
	pos = spawnPos;
	rotate		= MODEL_ROTATE;
	scale		= MODEL_SCALE;
	isAttack	= false;
	isDeath	= false;
	isHit		= false;
	isRestTime		= false;
	//最大HPの設定
	maxHP = status->GetHp();
}
/// <summary>
/// 更新
/// </summary>
void StrongEnemy::Update()
{
	blood->UpdateGravity();
	if (isInvincible)
	{
		blood->Init(bloodBaseDir, pos);
	}

	//無敵フラグが立っていたら
	if (isInvincible)
	{
		//タイマーを始める
		invincibleTimer->StartTimer();
		if (invincibleTimer->CountTimer())
		{
			invincibleTimer->EndTimer();
			isInvincible = false;
		}
	}
	//コリジョン情報を更新
	MV1RefreshCollInfo(modelHandle, -1);

	//もしプレイヤーに当たっていたら（後々HPをつけてHPが０になったら）
	if (status->GetHp() < 0)
	{
		//現在のアニメーションをやられたアニメーションにする
		if (!isDeath)
		{
			anim->SetAnim(static_cast<int>(AnimationType::DEATH));
		}
		if (anim->GetAnim() == static_cast<int>(AnimationType::DEATH) && anim->GetPlayTime() == 0.0f)
		{
			isDeath = true;
			pos = DESTROY_POS;
		}
	}
	else
	{
		pos = VAdd(pos, moveVec);//移動
		MV1SetRotationXYZ(modelHandle, rotate);//回転値の設定
	}
	pos.y = 10.0f;
	MV1SetPosition(modelHandle, pos);//位置の設定
	blood->Update(45);

	//アニメーション再生時間をセット
	anim->Play(&modelHandle);
}
/// <summary>
/// 移動
/// </summary>
void StrongEnemy::Move(VECTOR _playerPos)
{
	VECTOR playerPos = _playerPos;
	playerPos.y = 0.0f;
	//目標までのベクトル
	VECTOR targetPos = ORIGIN_POS;
	//正規化したベクトル
	VECTOR normalizePos = ORIGIN_POS;
	float vectorSize = 0.0f;
	//プレイヤーと自分の座標のベクトルの差を求める(目標までのベクトル)
	targetPos = VSub(pos, playerPos);
	//そのベクトルの大きさを求める
	vectorSize = VSize(targetPos);
	//目標までのベクトルを正規化する
	normalizePos = VNorm(targetPos);
	//もしベクトルサイズが80以下だったら攻撃する
	if (vectorSize <= 80.0f)
	{
		if (!isAttack)
		{
			anim->SetAnim(static_cast<int>(AnimationType::ATTACK));
			attackAnimLoopCount = 150;
			isAttack = true;
		}
	}
	else
	{
		if (!isAttack && !isRestTime)
		{
			//もしベクトルサイズが200以下だったらプレイヤーに向けて走る
			if (vectorSize <= 100.0f)
			{
				anim->SetAnim(static_cast<int>(AnimationType::RUN));
			}
			//それより離れていたら
			else
			{
				anim->SetAnim(static_cast<int>(AnimationType::IDLE));
			}
		}
	}
	//攻撃アニメーション中かつアニメーション変更フラグが立っていたら
	if (isAttack)
	{
		//攻撃回数が０になったら休憩する
		if (attackAnimLoopCount == 0 || vectorSize <= 0)
		{
			attackAnimLoopCount = 0;
			restTimeAfterAttack->StartTimer();
			//もしジャンプ中だったらそれ用のIdleにする
			isAttack = false;
			isRestTime = true;
			anim->SetAnim(static_cast<int>(AnimationType::IDLE));
		}
		//0じゃなければ攻撃回数を減らす
		else
		{
			attackAnimLoopCount--;
		}
	}
	//もし休憩中だったら
	if (isRestTime)
	{
		//タイマーが終了していたら
		if (restTimeAfterAttack->CountTimer())
		{
			isRestTime = false;
			restTimeAfterAttack->EndTimer();
		}
	}
	if (anim->GetAnim() != static_cast<int>(AnimationType::IDLE))
	{
		// もし攻撃中に正規化した値がーになっていたら正規化した値に移動スピードをかけて移動量を返す
		moveVec = VScale(normalizePos, status->GetAgi() * -1);
		//角度を変える
		rotate = VGet(0.0f, (float)ChangeRotate(playerPos), 0.0f);
	}
}
/// <summary>
///	角度の変更
/// </summary>
float StrongEnemy::ChangeRotate(VECTOR playerPos)
{
	//2点間のベクトルを出す(エネミーからプレイヤー)
	VECTOR EP_Vector = VSub(pos, playerPos);
	//2点の座標からラジアンを求める

	return static_cast<float>(atan2(static_cast<double>(EP_Vector.x), static_cast<double>(EP_Vector.z)));
}
/// <summary>
/// 最終処理
/// </summary>
void StrongEnemy::Final()
{
	if (invincibleTimer)
	{
		delete(invincibleTimer);
		invincibleTimer = NULL;
	}
	if (restTimeAfterAttack)
	{
		delete(restTimeAfterAttack);
		restTimeAfterAttack = NULL;
	}
	if (anim)
	{
		delete(anim);
		anim = NULL;
	}

}
/// <summary>
/// 球と球の当たり判定
/// </summary>
/// <param name="isAttack">攻撃しているかどうかの判定</param>
/// <param name="playerAttackPos">攻撃時当たり判定座標</param>
/// <param name="attackRadius">攻撃時当たり判定半径</param>
/// <returns>当たったかどうか</returns>
//bool StrongEnemy::SphereAndSphere(bool isAttack, VECTOR playerAttackPos, float attackRadius)
//{
//	// 距離の計算(二つのベクトルを引いたベクトルを取得)
//	VECTOR playerToEnemy = VSub(playerAttackPos, base.pos);
//	// 上で求めたベクトルの大きさよりも、二つの半径を足したものが大きければ当たっていると判定
//	if (VSize(playerToEnemy) < attackRadius + RADIUS)
//	{
//		base.isHit = true;
//		return true;
//	}
//	return false;
//}