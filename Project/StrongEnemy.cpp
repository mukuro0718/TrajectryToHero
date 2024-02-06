#include"StrongEnemy.h"
#include<math.h>
#include"Animation.h"
#include"CharacterStatus.h"
#include"Timer.h"
#include"BloodParticle.h"

//モデル設定
const VECTOR StrongEnemy::MODEL_SCALE	= VGet(0.3f, 0.3f, 0.3f);//モデルの拡大率
const VECTOR StrongEnemy::MODEL_ROTATE	= VGet(0.0f, 90 * DX_PI_F / 180.0f, 0.0f);//モデルの回転値
const int    StrongEnemy::CAPSULE_COLOR = GetColor(0, 255, 0);
const int	 StrongEnemy::SPHERE_COLOR	= GetColor(0, 200, 0);

/// <summary>
/// コンストラクタ
/// </summary>
StrongEnemy::StrongEnemy(const VECTOR _spawnPos,const int _modelHandle)
	: EnemyBase(_modelHandle)
	, invincibleTimer(nullptr)
	, restTimeAfterAttack(nullptr)
	, anim(nullptr)
	, randomRest(nullptr)
	, preliminaryOperation(nullptr)
	, isPreliminaryOperation(false)
{
	//インスタンスの生成
	Create();
	spawnPos = _spawnPos;
	Init();
	//モデル設定
	MV1SetScale(modelHandle, scale);
	//回転値のセット
	MV1SetRotationXYZ(modelHandle, rotate);
	//アニメーションの追加
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Strong/RunAnim.mv1")	, 0);			//走りアニメーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Strong/AttackAnim.mv1"), 1);		//攻撃アニメーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Strong/IdleAnim.mv1")	, 0);			//待機アニメーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Strong/DeathAnim.mv1")	, 1);		//死亡アニメーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/BeforeAttackAnim.mv1"), 1);//攻撃前モーション

	//アタッチするアニメーション
	anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	//アニメーションのアタッチ
	anim->Attach(&modelHandle);
}
/// <summary>
/// 作成
/// </summary>
void StrongEnemy::Create()
{
	//インスタンスの生成
	invincibleTimer		= new Timer();
	restTimeAfterAttack = new Timer();
	randomRest			= new Timer();
	preliminaryOperation = new Timer();
	anim				= new Animation();
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
	randomRest->Init(20);
	preliminaryOperation->Init(9);
	status->InitStrongEnemyStatus(1.0f);
	//新しい座標の生成
	pos = spawnPos;
	rotate = MODEL_ROTATE;
	scale = MODEL_SCALE;
	isAttack = false;
	isDeath = false;
	isHit = false;
	isRestTime = false;
	isRandomWalk = false;
	isRandomRest = false;
	//最大HPの設定
	maxHP = status->GetHp();
}
const void StrongEnemy::NewStatus(const float _playerLv)
{
	status->InitStrongEnemyStatus(_playerLv);
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
	VECTOR enemyLeftFootPos = MV1GetFramePosition(modelHandle, 63);
	SetUpCapsule(pos, HEIGHT, RADIUS, CAPSULE_COLOR, false);
	SetUpSphere(enemyLeftFootPos, SPHERE_RADIUS, SPHERE_COLOR, false);
	blood->Update(60);
	//色の変更
	ChangeColor();
	//アニメーション再生時間をセット
	anim->Play(&modelHandle);
}
/// <summary>
/// 移動
/// </summary>
void StrongEnemy::Move(VECTOR _playerPos)
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
	if (vectorSize <= 80.0f)
	{
		//すでに攻撃していない、休憩中ではない
		if (!isAttack && !isRestTime)
		{
			if (!isPreliminaryOperation)
			{
				preliminaryOperation->StartTimer();
			}
			else
			{

				attackAnimLoopCount = 100;
				isAttack = true;
				isMove = false;
				isRandomWalk = false;
				isRandomRest = false;
			}
		}
	}
	//80以上だったら
	else
	{
		//攻撃や休憩をしていなかったら
		if (!isAttack && !isRestTime)
		{
			//もしベクトルサイズが定数以下だったらプレイヤーに向けて走る
			if (vectorSize <= 100.0f)
			{
				isMove = true;
				isAttack = false;
				isRandomWalk = false;
				isRandomRest = false;
			}
			//それより離れていたら
			else
			{
				RandomWalk();
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
			isPreliminaryOperation = false;
			isRestTime = true;
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
	if (isMove && vectorSize >= 20 || isAttack && vectorSize >= 20)
	{
		// もし攻撃中に正規化した値がーになっていたら正規化した値に移動スピードをかけて移動量を返す
		moveVec = VScale(normalizePos, status->GetAgi() * -1);
		//角度を変える
		rotate = VGet(0.0f, (float)ChangeRotate(_playerPos), 0.0f);
	}
	if (preliminaryOperation->getIsStartTimer())
	{
		if (preliminaryOperation->CountTimer())
		{
			preliminaryOperation->EndTimer();
			isPreliminaryOperation = true;
		}
	}
}
/// <summary>
/// ランダムに歩く
/// </summary>
void StrongEnemy::RandomWalk()
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
///	角度の変更
/// </summary>
double StrongEnemy::ChangeRotate(VECTOR playerPos)
{
	//2点間のベクトルを出す(エネミーからプレイヤー)
	VECTOR EP_Vector = VSub(pos, playerPos);
	//2点の座標からラジアンを求める

	return static_cast<float>(atan2(static_cast<double>(EP_Vector.x), static_cast<double>(EP_Vector.z)));
}
/// <summary>
///	アニメーションの変更
/// </summary>
void StrongEnemy::ChangeAnim()
{
	//攻撃も移動もしていないまたは休憩中だったら
	if (!isAttack && !isMove && !isRandomWalk || isRestTime || isRandomRest)
	{
		anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	}
	//攻撃中だったら
	else if (isAttack && !isMove && !isRestTime)
	{
		anim->SetAnim(static_cast<int>(AnimationType::ATTACK));
	}
	//移動中だったら
	else if (!isAttack && isMove && !isRestTime || !isAttack && isRandomWalk && !isRestTime)
	{
		anim->SetAnim(static_cast<int>(AnimationType::RUN));
	}
	//もしHPが0以下になったら
	if (status->GetHp() <= 0)
	{
		anim->SetAnim(static_cast<int>(AnimationType::DEATH));
	}
	else if (preliminaryOperation->getIsStartTimer() && !isRestTime)
	{
		anim->SetAnim(static_cast<int>(AnimationType::BEFORE_ATTACK));
	}

}
/// <summary>
/// 最終処理
/// </summary>
void StrongEnemy::Final()
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
