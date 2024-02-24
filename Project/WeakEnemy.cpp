//===========================================================================
//@brief ウィークエネミークラス/継承
//===========================================================================

#include"WeakEnemy.h"
#include<math.h>
#include"Animation.h"
#include"Timer.h"
#include"BloodParticle.h"

//モデル設定
 const VECTOR WeakEnemy::MODEL_SCALE = VGet(0.2f, 0.2f, 0.2f);//モデルの拡大率
 const VECTOR WeakEnemy::MODEL_ROTATE = VGet(0.0f, 90 * DX_PI_F / 180.0f, 0.0f);//モデルの回転値
 const int    WeakEnemy::CAPSULE_COLOR = GetColor(0, 255, 0);
 const int	  WeakEnemy::SPHERE_COLOR = GetColor(0, 200, 0);

/// <summary>
/// コンストラクタ
/// </summary>
 WeakEnemy::WeakEnemy(const VECTOR _spawnPos, const int _modelHandle)
	 : EnemyBase(_modelHandle)
	 , invincibleTimer(nullptr)
	 , restTimeAfterAttack(nullptr)
	 , anim(nullptr)
	 , randomRest(nullptr)
	 //, preliminaryOperation(nullptr)
	 //, isPreliminaryOperation(false)
	 , isWalk(false)
	 , animPlayTime{0.8f,0.95f, 0.6f, 0.7f, 0.8f, 0.8f, 0.6f}
	 , attackType(0)
{
	Create();
	spawnPos = _spawnPos;
	Init();
	//スケールのセット
	MV1SetScale(modelHandle, scale);
	//回転値のセット
	MV1SetRotationXYZ(modelHandle, rotate);
	//アニメーションの追加
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/RunAnim.mv1"), 1);			//走りアニメーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/ComboAttack.mv1"), 1);		//攻撃アニメーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/AttackAnim.mv1"), 1);		//攻撃アニメーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/IdleAnim.mv1"), 1);		//待機アニメーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/DeathAnim.mv1"), 1);		//死亡アニメーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/WalkAnim.mv1"), 1);	//右へ歩くモーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/KnockBack.mv1"), 1);	//右へ歩くモーション

	//アタッチするアニメーション
	anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	//アニメーションのアタッチ
	anim->Attach(&modelHandle);
}
/// <summary>
/// 作成
/// </summary>
void WeakEnemy::Create()
{
	//インスタンスの生成
	invincibleTimer		= new Timer();
	restTimeAfterAttack = new Timer();
	randomRest			= new Timer();
	//preliminaryOperation= new Timer();
	anim				= new Animation();
}
/// <summary>
/// デストラクタ
/// </summary>
WeakEnemy::~WeakEnemy()
{
	Final();
}
/// <summary>
/// 初期化
/// </summary>
void WeakEnemy::Init()
{
	//必要なInitクラスの呼び出し
	invincibleTimer->Init(8);
	restTimeAfterAttack->Init(5);
	randomRest->Init(20);
	//preliminaryOperation->Init(12);
	//新しい座標の生成
	pos			= spawnPos;
	rotate		= MODEL_ROTATE;
	scale		= MODEL_SCALE;
	isAttack	= false;
	isDeath		= false;
	isHit		= false;
	isRestTime	= false;
	isRandomWalk = false;
	isRandomRest = false;
	//最大HPの設定
	status->InitWeakEnemyStatus(1.0f);
	maxHP = status->GetHp();
}
const void WeakEnemy::NewStatus(const float _playerLv)
{
	status->InitWeakEnemyStatus(_playerLv);
	maxHP = status->GetHp();
}
/// <summary>
/// 更新
/// </summary>
void WeakEnemy::Update()
{
	if (isHit)
	{
		frameCount++;
		if (frameCount == 60)
		{
			isHit = false;
			frameCount = 0;
		}
	}
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

	//もしHPをつけてHPが０になったら
	if (status->GetHp() <= 0)
	{
		//現在のアニメーションをやられたアニメーションにする
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
	//アニメーションの変更
	ChangeAnim();
	//位置の設定
	MV1SetPosition(modelHandle, pos);

	SetUpCapsule(pos, HEIGHT, RADIUS, CAPSULE_COLOR, false);
	//攻撃当たり判定用スフィア座標の設定
	VECTOR framePos33 = MV1GetFramePosition(modelHandle, 33);
	VECTOR framePos46 = MV1GetFramePosition(modelHandle, 46);
	VECTOR framePos33to46 = VSub(framePos46, framePos33);
	framePos33to46 = VNorm(framePos33to46);
	framePos33to46 = VScale(framePos33to46, 10.0f);
	VECTOR attackSphereCenterPos = VAdd(framePos46, framePos33to46);
	SetUpSphere(attackSphereCenterPos, SPHERE_RADIUS, SPHERE_COLOR, false);
	blood->Update(50);
	//色の変更
	ChangeColor();
	//アニメーション再生時間をセット
	anim->Play(&modelHandle, animPlayTime[anim->GetAnim()]);
}
/// <summary>
/// 移動
/// </summary>
void WeakEnemy::Move(VECTOR _playerPos)
{
	moveVec = ORIGIN_POS;
	//目標までのベクトル
	VECTOR targetPos = ORIGIN_POS;
	//正規化したベクトル
	VECTOR normalizePos = ORIGIN_POS;
	//返り値として返す移動後座標（角度有）
	VECTOR outPutPos = ORIGIN_POS;
	float vectorSize = 0.0f;
	//プレイヤーと自分の座標のベクトルの差を求める(目標までのベクトル)
	targetPos = VSub(pos, _playerPos);
	//そのベクトルの大きさを求める
	vectorSize = VSize(targetPos);
	//目標までのベクトルを正規化する
	normalizePos = VNorm(targetPos);
	//もしベクトルサイズが定数以下だったら攻撃する
	if (vectorSize <= 20.0f)
	{
		//すでに攻撃していない、休憩中ではない
		if (!isAttack && !isRestTime && !isInvincible)
		{
			//if (!isPreliminaryOperation)
			//{
			//	preliminaryOperation->StartTimer();
			//}
			//else
			//{
			attackType = GetRand(1);
			attackAnimLoopCount = 100;
			isAttack = true;
			isMove = false;
			isRandomWalk = false;
			isRandomRest = false;
			isWalk = false;
			//}
		}
	}
	//80以上だったら
	else if (vectorSize <= 50.0f)
	{
		//すでに攻撃していない、休憩中ではない
		if (!isAttack && !isRestTime)
		{
			isWalk = true;
			isMove = false;
			isAttack = false;
			isRandomWalk = false;
			isRandomRest = false;
		}
	}
	else
	{
		//攻撃や休憩をしていなかったら
		if (!isAttack && !isRestTime)
		{
			//もしベクトルサイズが定数以下だったらプレイヤーに向けて走る
			if (vectorSize <= 200.0f)
			{
				isMove = true;
				isAttack = false;
				isRandomWalk = false;
				isRandomRest = false;
				isWalk = false;
			}
			//それより離れていたら
			else
			{
				RandomWalk();
				isWalk = false;
				isMove = false;
				isAttack = false;
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
			isAttack = false;
			isMove = false;
			isRandomWalk = false;
			//isPreliminaryOperation = false;
			isRestTime = true;
			isWalk = false;
		}
		//0じゃなければ攻撃回数を減らす
		else
		{
			attackAnimLoopCount--;
		}
	}
	//もし休憩中だったら
	else if (isRestTime)
	{
		//タイマーが終了していたら
		if (restTimeAfterAttack->CountTimer())
		{
			isRestTime = false;
			restTimeAfterAttack->EndTimer();
		}
	}
	if (isMove && vectorSize >= 20 && !isInvincible)
	{
		// もし攻撃中に正規化した値がーになっていたら正規化した値に移動スピードをかけて移動量を返す
		moveVec = VScale(normalizePos, status->GetAgi() * -1);
	}
	else if (isWalk && !isInvincible)
	{
		// もし攻撃中に正規化した値がーになっていたら正規化した値に移動スピードをかけて移動量を返す
		moveVec = VScale(normalizePos, status->GetAgi() * -0.5f);
	}
	if (isMove && vectorSize >= 20 && !isInvincible || isAttack && vectorSize >= 20 && !isInvincible || isWalk && !isInvincible)
	{
		//角度を変える
		rotate = VGet(0.0f, (float)ChangeRotate(_playerPos), 0.0f);
	}

	//if (preliminaryOperation->getIsStartTimer())
	//{
	//	if (preliminaryOperation->CountTimer())
	//	{
	//		preliminaryOperation->EndTimer();
	//		isPreliminaryOperation = true;
	//	}
	//}
}
/// <summary>
/// ランダムに歩く
/// </summary>
void WeakEnemy::RandomWalk()
{
	//目標までのベクトル
	VECTOR targetVec = ORIGIN_POS;
	//正規化したベクトル
	VECTOR normalizeVec = ORIGIN_POS;
	//ベクトルのサイズ
	float vectorSize = 0.0f;
	targetVec = VSub(randomWalkTargetPos, pos);
	if (isRandomWalk == false)
	{
		randomWalkTargetPos = spawnPos;
		/*TODO*/
		//もしスポーン位置から定数以上離れていたらスポーン位置スポーン位置に向かって進む
		//そうでなければランダムで座標を出して、進む方向を決める、ベクトルのサイズを出して、０になるまで進む
		// ランダムで出す座標はスポーン位置からX,Z座標方向に＋定数の範囲で出す
		//もし進んでいる途中にスポーン位置から定数以上離れたら止まる
		randomWalkTargetPos.x += static_cast<float>(GetRand(200) - 100);
		randomWalkTargetPos.z += static_cast<float>(GetRand(200) - 100);
		isRandomWalk = true;
		targetVec = VSub(randomWalkTargetPos, pos);
	}
	//そのベクトルの大きさを求める
	else if (VSize(targetVec) < 10.0f)
	{
		randomRest->StartTimer();
		isRandomRest = true;
	}
	if (randomRest->CountTimer())
	{
		randomRest->EndTimer();
		isRandomWalk = false;
		isRandomRest = false;
	}
	if (!randomRest->getIsStartTimer())
	{
		normalizeVec = VNorm(targetVec);
		// もし攻撃中に正規化した値がーになっていたら正規化した値に移動スピードをかけて移動量を返す
		moveVec = VScale(normalizeVec, status->GetAgi());
		moveVec.y = 0.0f;
		//角度を変える
		rotate = VGet(0.0f, (float)ChangeRotate(randomWalkTargetPos), 0.0f);
	}
}
/// <summary>
///	角度の変更(モデルが向いている初期方向がz＝０)
/// </summary>
double WeakEnemy::ChangeRotate(VECTOR playerPos)
{
	//2点間のベクトルを出す(エネミーからプレイヤー)
	VECTOR EP_Vector = VSub(pos, playerPos);
	//2点の座標からラジアンを求める
	return static_cast<float>(atan2(static_cast<double>(EP_Vector.x), static_cast<double>(EP_Vector.z)));
}
/// <summary>
///	アニメーションの変更
/// </summary>
void WeakEnemy::ChangeAnim()
{
	if (isInvincible)
	{
	anim->SetAnim(static_cast<int>(AnimationType::FRIGHTENING));//怯み
	}
	//攻撃も移動もしていないまたは休憩中だったら
	else if (!isAttack && !isMove && !isRandomWalk && !isWalk|| isRestTime || isRandomRest)
	{
		anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	}
	//攻撃中だったら
	else if (isAttack && !isMove && !isRestTime)
	{
		if (attackType == static_cast<int>(AttackType::COMBO_ATTACK))
		{
			anim->SetAnim(static_cast<int>(AnimationType::COMBO_ATTACK));
		}
		else
		{
			anim->SetAnim(static_cast<int>(AnimationType::NORMAL_ATTACK));
		}
	}
	//移動中だったら
	else if (!isAttack && isMove && !isRestTime || !isAttack && isRandomWalk && !isRestTime)
	{
		anim->SetAnim(static_cast<int>(AnimationType::RUN));
	}
	else if (isWalk)
	{
		anim->SetAnim(static_cast<int>(AnimationType::WALK));
	}
	//もしHPが0以下になったら
	if (status->GetHp() <= 0)
	{
		anim->SetAnim(static_cast<int>(AnimationType::DEATH));
	}
	//else if (preliminaryOperation->getIsStartTimer() && !isRestTime)
	//{
	//	anim->SetAnim(static_cast<int>(AnimationType::BEFORE_ATTACK));
	//}
}
/// <summary>
/// 最終処理
/// </summary>
void WeakEnemy::Final()
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
}
