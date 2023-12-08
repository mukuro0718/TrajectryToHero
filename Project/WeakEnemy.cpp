//===========================================================================
//@brief ウィークエネミークラス/継承
//===========================================================================

#include"WeakEnemy.h"
#include<math.h>
#include"Animation.h"
//#include"CharacterStatus.h"
#include"Timer.h"
//モデル設定
 const VECTOR WeakEnemy::MODEL_SCALE = VGet(0.2f, 0.2f, 0.2f);//モデルの拡大率
 const VECTOR WeakEnemy::MODEL_ROTATE = VGet(0.0f, 90 * DX_PI_F / 180.0f, 0.0f);//モデルの回転値
 
/// <summary>
/// コンストラクタ
/// </summary>
WeakEnemy::WeakEnemy(const VECTOR _spawnPos,const int _modelHandle)
 :EnemyBase(_modelHandle)
{
	Create();
	spawnPos = _spawnPos;
	Init();
	//スケールのセット
	MV1SetScale(modelHandle, scale);
	//回転値のセット
	MV1SetRotationXYZ(modelHandle, rotate);
	//アニメーションの追加
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/RunAnim.mv1"), 1);				//走りアニメーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/AttackAnim.mv1"), 1);		//攻撃アニメーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/IdleAnim.mv1"), 1);			//待機アニメーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/DeathAnim.mv1"), 1);		//死亡アニメーション
	//アタッチするアニメーション
	anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	//アニメーションのアタッチ
	anim->Attach(&modelHandle);
}
/// <summary>
/// 生成
/// </summary>
void WeakEnemy::Create()
{
	//インスタンスの初期化
	statusInit = NULL;
	invincibleTimer = NULL;
	restTimeAfterAttack = NULL;
	anim = NULL;
	//インスタンスの生成
	invincibleTimer = new Timer();
	restTimeAfterAttack = new Timer();
	anim = new Animation();
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
	invincibleTimer->Init(9);
	restTimeAfterAttack->Init(20);
	//新しい座標の生成
	pos			= spawnPos;
	rotate		= MODEL_ROTATE;
	scale		= MODEL_SCALE;
	isAttack	= false;
	isDeath		= false;
	isHit		= false;
	isRestTime	= false;
	//最大HPの設定
	//pos.y = 10.0f;
	status->InitWeakEnemyStatus();
	maxHP = status->GetHp();
}
/// <summary>
/// 更新
/// </summary>
void WeakEnemy::Update()
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
	
	//もしHPをつけてHPが０になったら
	if (status->GetHp() <= 0)
	{
		//現在のアニメーションをやられたアニメーションにする
		if(anim->GetAnim() == static_cast<int>(AnimationType::DEATH) && anim->GetPlayTime() == 0.0f)
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
	ChangeAnim();
	//pos.y = 10.0f;
	MV1SetPosition(modelHandle, pos);//位置の設定
	//アニメーション再生時間をセット
	anim->Play(&modelHandle);
}
/// <summary>
/// 移動
/// </summary>
void WeakEnemy::Move(VECTOR playerPos)
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
	targetPos = VSub(pos, playerPos);
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
			attackAnimLoopCount = 100;
			isAttack = true;
			isMove = false;
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
			}
			//それより離れていたら
			else
			{
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
	if (isMove && vectorSize >= 20 || isAttack && vectorSize >=20)
	{
		// もし攻撃中に正規化した値がーになっていたら正規化した値に移動スピードをかけて移動量を返す
		moveVec = VScale(normalizePos, status->GetAgi() * -1);
		//角度を変える
		rotate = VGet(0.0f, (float)ChangeRotate(playerPos), 0.0f);
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
	//攻撃も移動もしていないまたは休憩中だったら
	if (!isAttack && !isMove || isRestTime)
	{
		anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	}
	//攻撃中だったら
	else if (isAttack && !isMove && !isRestTime)
	{
		anim->SetAnim(static_cast<int>(AnimationType::ATTACK));
	}
	//移動中だったら
	else if (!isAttack && isMove && !isRestTime)
	{
		anim->SetAnim(static_cast<int>(AnimationType::RUN));
	}
	//もしHPが0以下になったら
	if (status->GetHp() <= 0)
	{
		anim->SetAnim(static_cast<int>(AnimationType::DEATH));
	}
}
/// <summary>
/// 最終処理
/// </summary>
void WeakEnemy::Final()
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
