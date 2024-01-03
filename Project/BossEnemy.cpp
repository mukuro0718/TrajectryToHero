//===========================================================================
//@brief ボスエネミークラス/継承
//===========================================================================

#include"BossEnemy.h"
#include<math.h>
#include"Animation.h"
#include"Timer.h"
//モデル設定
const VECTOR BossEnemy::MODEL_SCALE = VGet(0.4f, 0.4f, 0.4f);//モデルの拡大率
const VECTOR BossEnemy::MODEL_ROTATE = VGet(0.0f, 90 * DX_PI_F / 180.0f, 0.0f);//モデルの回転値
const VECTOR BossEnemy::INIT_POS = VGet(0.0f, 0.0f, 500.0f);//モデルの回転値

/// <summary>
/// コンストラクタ
/// </summary>
BossEnemy::BossEnemy(const VECTOR _spawnPos,const int _modelHandle)
	:EnemyBase(_modelHandle)
{
	Create();
	spawnPos = _spawnPos;
	Init();
	//モデル設定
	MV1SetScale(modelHandle, scale);
	//回転値のセット
	MV1SetRotationXYZ(modelHandle, rotate);
	//アニメーションの追加
	anim->Add(MV1LoadModel("Data/Animation/BossEnemy_Walk.mv1"), 0);
	anim->Add(MV1LoadModel("Data/Animation/BossEnemy_StronglAttackAnim.mv1"), 0);	//通常攻撃アニメーション
	anim->Add(MV1LoadModel("Data/Animation/BossEnemy_RotateAttackAnim.mv1"), 0);	//回転攻撃アニメーション
	anim->Add(MV1LoadModel("Data/Animation/BossEnemy_JumpAttackAnim.mv1"), 0);		//ジャンプ攻撃アニメーション
	anim->Add(MV1LoadModel("Data/Animation/BossEnemy_JumpIdleAnim.mv1"), 0);			//待機アニメーション
	anim->Add(MV1LoadModel("Data/Animation/BossEnemy_IdleAnim.mv1"), 0);			//待機アニメーション
	anim->Add(MV1LoadModel("Data/Animation/BossEnemy_DeathAnim.mv1"), 0);			//死亡アニメーション
	//アタッチするアニメーション
	anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	//アニメーションのアタッチ（最初は明示的に呼び出してアニメーションをアタッチする必要がある）
	anim->Attach(&modelHandle);
}
/// <summary>
/// デストラクタ
/// </summary>
BossEnemy::~BossEnemy()
{
	Final();
}
/// <summary>
/// 作成
/// </summary>
void BossEnemy::Create()
{
	//インスタンスの初期化
	invincibleTimer		= NULL;
	restTimeAfterAttack = NULL;
	anim				= NULL;
	//インスタンスの生成
	invincibleTimer			= new Timer();
	restTimeAfterAttack		= new Timer();
	anim					= new Animation();
	waitBeforeJunpAttack	= new Timer();
	waitBeforeRotateAttack	= new Timer();
	rotateAttackLoopTime	= new Timer();
}
/// <summary>
/// 初期化
/// </summary>
void BossEnemy::Init()
{
	//必要なInitクラスの呼び出し
	waitBeforeJunpAttack  ->Init(10);
	waitBeforeRotateAttack->Init(10);
	rotateAttackLoopTime  ->Init(50);
	invincibleTimer		  ->Init(9);	
	restTimeAfterAttack   ->Init(20);
	//最大HPの設定
	status->InitBossEnemyStatus();
	maxHP = status->GetHp();
	attackType				= 0;
	jumpAttackTargetPos		= ORIGIN_POS;
	attackAnimLoopCount		= 0;
	pos						= spawnPos;
	rotate					= MODEL_ROTATE;
	scale					= MODEL_SCALE;
	isJumpAttack	= false;
	isJumpIdle		= false;
	isAttack		= false;
	isDeath			= false;
	isHit			= false;
	isRestTime		= false;
}
/// <summary>
/// 最終処理
/// </summary>
void BossEnemy::Final()
{
	if (invincibleTimer)
	{
		delete(invincibleTimer);
		invincibleTimer = nullptr;
	}
	if (restTimeAfterAttack)
	{
		delete(restTimeAfterAttack);
		restTimeAfterAttack = nullptr;
	}
	if (anim)
	{
		delete(anim);
		anim = nullptr;
	}
	if (waitBeforeJunpAttack)
	{
		delete(waitBeforeJunpAttack);
		waitBeforeJunpAttack = nullptr;
	}
	if (waitBeforeRotateAttack)
	{
		delete(waitBeforeRotateAttack);
		waitBeforeRotateAttack = nullptr;
	}

	if (rotateAttackLoopTime)
	{
		delete(rotateAttackLoopTime);
		rotateAttackLoopTime = nullptr;
	}

}
/// <summary>
/// 更新
/// </summary>
void BossEnemy::Update()
{

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
	//もしプレイヤーに当たっていたら
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
	pos = VGet(pos.x, 0.0f, pos.z);
	MV1SetPosition(modelHandle, pos);//位置の設定
	//アニメーション再生時間をセット
	anim->Play(&modelHandle);
}
/// <summary>
/// 移動
/// </summary>
void BossEnemy::Move(const VECTOR _playerPos)
{
	//目標までのベクトル
	VECTOR targetPos = ORIGIN_POS;
	//正規化したベクトル
	VECTOR normalizePos = ORIGIN_POS;
	float vectorSize = 0.0f;
	//もし攻撃中ではなかったら攻撃をする
	if (!isAttack)
	{
		//もし休憩中ではなければ攻撃パターンを決めなおす
		if (!isRestTime)
		{
			//プレイヤーと自分の座標のベクトルの差を求める(目標までのベクトル)
			targetPos = VSub(pos, _playerPos);
			//そのベクトルの大きさを求める
			vectorSize = VSize(targetPos);
			if (vectorSize <= 11)
			{
				attackType = 1;
			}
			else
			{
				attackType = GetRand(1) + 2;
			}
			switch (attackType)
			{
			case 1://通常
				anim->SetAnim(static_cast<int>(AnimationType::NORMAL_ATTACK));
				attackAnimLoopCount = 1;
				break;
			case 2://回転
				anim->SetAnim(static_cast<int>(AnimationType::ROTATE_ATTACK));
				waitBeforeRotateAttack->StartTimer();
				isRotateAttack = false;
				break;
			case 3://ジャンプ
				anim->SetAnim(static_cast<int>(AnimationType::JUMP_ATTACK));
				jumpAttackTargetPos = _playerPos;//目標座標を設定
				waitBeforeJunpAttack->StartTimer();
				isJumpAttack = false;
				break;
			default:
				break;
			}
			isAttack = true;
		}
	}
	//攻撃中だったら
	else
	{
		//ジャンプアタック処理
		/*ジャンプアタック中
		攻撃開始時に目標座標を設定し、その座標に向かって飛ぶ
		追尾なしの代わりに、移動速度が速い*/
		if (attackType == static_cast<int>(AnimationType::JUMP_ATTACK))
		{
			//タイマーがスタートしていて、目標時間に達していたら
			if (waitBeforeJunpAttack->getIsStartTimer() && waitBeforeJunpAttack->CountTimer())
			{
				//ジャンプアタックを許可する
				isJumpAttack = true;
				//タイマーを終了させる
				waitBeforeJunpAttack->EndTimer();
			}
			//許可されていたら
			if (isJumpAttack)
			{
				//プレイヤーと自分の座標のベクトルの差を求める(目標までのベクトル)
				targetPos = VSub(pos, jumpAttackTargetPos);
				//そのベクトルの大きさを求める
				vectorSize = VSize(targetPos);
				//サイズが定数よりも小さくなったら
				if (vectorSize <= 5)
				{
					//休憩フラグを立てる
					isRestTime = true;
					//攻撃フラグを下す
					isAttack = false;
				}
				else
				{
					//目標までのベクトルを正規化する
					normalizePos = VNorm(targetPos);
					// もし攻撃中に正規化した値がーになっていたら正規化した値に移動スピードをかけて移動量を返す
					moveVec = VScale(normalizePos, status->GetAgi() * -3);
					//角度を変える
					rotate = VGet(0.0f, (float)ChangeRotate(jumpAttackTargetPos), 0.0f);
				}
			}
		}
		else
		{
			/*回転攻撃*/
			if (attackType == static_cast<int>(AnimationType::ROTATE_ATTACK))
			{
				//タイマーがスタートしていて、目標時間に達していたら
				if (waitBeforeRotateAttack->getIsStartTimer() && waitBeforeRotateAttack->CountTimer())
				{
					//回転アタックを許可する
					isRotateAttack = true;
					//タイマーを終了させる
					waitBeforeRotateAttack->EndTimer();
				}
				//許可されていたら
				if (isRotateAttack)
				{
					//回転攻撃継続時間がスタートしていなかったら
					if (!rotateAttackLoopTime->getIsStartTimer())
					{
						//タイマーをスタートする
						rotateAttackLoopTime->StartTimer();
					}
					//スタートしていたら
					else
					{
						//もしタイマーが目標時間に達したら
						if (rotateAttackLoopTime->CountTimer())
						{
							//休憩フラグを立てる
							isRestTime = true;
							//攻撃フラグを下す
							isAttack = false;
						}
					}
				}
				//プレイヤーと自分の座標のベクトルの差を求める(目標までのベクトル)
				targetPos = VSub(pos, _playerPos);
				//そのベクトルの大きさを求める
				vectorSize = VSize(targetPos);
				//目標までのベクトルを正規化する
				normalizePos = VNorm(targetPos);
				moveVec = VScale(normalizePos, status->GetAgi() * -1);
			}
			//もし通常攻撃中かつアニメーション変更フラグがたったら
			if (attackType == static_cast<int>(AnimationType::NORMAL_ATTACK) && anim->GetIsChangeAnim())
			{
				//休憩フラグを立てる
				isRestTime = true;
				//攻撃フラグを下す
				isAttack = false;
			}
			//角度を変える
			rotate = VGet(0.0f, (float)ChangeRotate(_playerPos), 0.0f);

		}
	}
	//休憩フラグが立っていて、タイマーがスタートしていなかったらスタートする
	if (isRestTime && !restTimeAfterAttack->getIsStartTimer())
	{
		//タイマーをスタート
		restTimeAfterAttack->StartTimer();
		//アニメーションがジャンプアタックだったら
		if (attackType == static_cast<int>(AnimationType::JUMP_ATTACK))
		{
			anim->SetAnim(static_cast<int>(AnimationType::JUMP_IDLE));
		}
		else
		{
			anim->SetAnim(static_cast<int>(AnimationType::IDLE));
		}
	}
	//スタートしているなら
	else
	{
		//もしタイマーが目標時間に達したら
		if (restTimeAfterAttack->CountTimer())
		{
			isRestTime = false;
			restTimeAfterAttack->EndTimer();
		}
	}
}
/// <summary>
///	角度の変更
/// </summary>
float BossEnemy::ChangeRotate(VECTOR playerPos)
{
	//2点間のベクトルを出す(エネミーからプレイヤー)
	VECTOR EP_Vector = VSub(pos, playerPos);
	return static_cast<float>(atan2(static_cast<double>(EP_Vector.x), static_cast<double>(EP_Vector.z)));
}

