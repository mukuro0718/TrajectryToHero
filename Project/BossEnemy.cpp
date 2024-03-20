//===========================================================================
//@brief ボスエネミークラス/継承
//===========================================================================

#include"BossEnemy.h"
#include<math.h>
#include"Animation.h"
#include"Timer.h"
#include"BloodParticle.h"

//モデル設定
const VECTOR BossEnemy::MODEL_SCALE = VGet(0.4f, 0.4f, 0.4f);//モデルの拡大率
const VECTOR BossEnemy::MODEL_ROTATE = VGet(0.0f, 90 * DX_PI_F / 180.0f, 0.0f);//モデルの回転値
const VECTOR BossEnemy::INIT_POS = VGet(0.0f, 0.0f, 500.0f);//モデルの回転値
const int    BossEnemy::CAPSULE_COLOR = GetColor(0, 255, 0);
const int	 BossEnemy::FONT_COLOR = GetColor(150, 150, 150);

/// <summary>
/// コンストラクタ
/// </summary>
BossEnemy::BossEnemy(const VECTOR _spawnPos, const int _modelHandle, const int _frameImage, const int _hpImage, const int _font)
	:EnemyBase(_modelHandle)
	, font(_font)
	, frameImage(_frameImage)
	, hpImage(_hpImage)
	, jumpAtttackFlySpeed(0.0f)
	, animPlayTime{ 0.8f,0.6f,0.6f,0.6f,0.6f,0.6f,0.6f,0.8f,0.8f }
	, flyFrameCount(0)
	, isOnGround(false)
{
	Create();
	spawnPos = _spawnPos;
	nowHP.y = 20;
	Init();
	//モデル設定
	MV1SetScale(modelHandle, scale);
	//回転値のセット
	MV1SetRotationXYZ(modelHandle, rotate);
	//アニメーションの追加
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/WalkAnim.mv1")			, 0);//歩き
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/MeleeAnim.mv1")			, 0);//通常攻撃
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/StrongAttackAnim.mv1")	, 0);//強い攻撃
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/RotateAttackAnim.mv1")	, 0);//回転攻撃
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/JumpAttackAnim.mv1")		, 0);//ジャンプ攻撃
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/MeteoAttackAnim.mv1")		, 0);//隕石攻撃
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/ExplosionAttackAnim.mv1")	, 0);//爆発攻撃
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/IdleAnim.mv1")			, 0);//待機
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/DeathAnim.mv1")			, 0);//死亡
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
	invincibleTimer		= nullptr;
	restTimeAfterAttack = nullptr;
	anim				= nullptr;
	//インスタンスの生成
	invincibleTimer			= new Timer();
	restTimeAfterAttack		= new Timer();
	anim					= new Animation();
	rotateAttackLoopTime	= new Timer();
}
/// <summary>
/// 初期化
/// </summary>
const void BossEnemy::Init()
{
	//必要なInitクラスの呼び出し
	rotateAttackLoopTime  ->Init(50);
	invincibleTimer		  ->Init(8);	
	restTimeAfterAttack   ->Init(20);
	//最大HPの設定
	status->InitBossEnemyStatus();
	maxHP = status->GetHp();
	attackType				= 0;
	attackAnimLoopCount		= 0;
	pos						= spawnPos;
	rotate					= MODEL_ROTATE;
	scale					= MODEL_SCALE;
	jumpAttackTargetPos		= ORIGIN_POS;
	spherePos = MV1GetFramePosition(modelHandle, 11);;
	isJumpAttack	= false;
	isJumpIdle		= false;
	isAttack		= false;
	isDeath			= false;
	isHit			= false;
	isRestTime		= false;
	SetUpCapsule(pos, HEIGHT, RADIUS, CAPSULE_COLOR, false);
	SetUpSphere(spherePos, 10.0f, CAPSULE_COLOR, false);
}
/// <summary>
/// 最終処理
/// </summary>
void BossEnemy::Delete()
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
	if (rotateAttackLoopTime)
	{
		delete(rotateAttackLoopTime);
		rotateAttackLoopTime = nullptr;
	}

}
/// <summary>
/// 更新
/// </summary>
const void BossEnemy::Update()
{
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
			//isInvincible = false;
		}
	}
	//もしプレイヤーに当たっていたら
	if (status->GetHp() < 0)
	{
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
	SetUpCapsule(pos, HEIGHT, RADIUS,CAPSULE_COLOR,false);
	SetUpSphere(spherePos, attackRadius, CAPSULE_COLOR, false);
	blood->Update(45);
	//色の変更
	ChangeColor();
	//アニメーション再生時間をセット
	anim->Play(&modelHandle, animPlayTime[anim->GetAnim() ]);
}
const void BossEnemy::Attack(const float _targetVecSize, const VECTOR _targetPos)
{
	//攻撃をしていなかったら
	if (!isAttack)
	{
		//各攻撃フラグを初期化する
		isJumpAttack = false;
		isRotateAttack = false;
		isMeteoAttack = false;
		isExplosionAttack = false;
		isNormalAttack = false;
		isStrongAttack = false;
		isAttack = true;
		isMove = false;
		/*目標までのベクトルをもとに攻撃を割り振る*/
		//ベクトルサイズが定数以下だったら近距離用攻撃をする
		if (_targetVecSize <= CLOSE_ATTACK_RANGE)
		{
			int random = GetRand(RANDOM_RANGE_CLOSE_ATTACK);
			//通常攻撃
			if (random <= NORMAL_ATTACK_RANGE)
			{
				isNormalAttack = true;
			}
			//強い攻撃
			else if (random <= STRONG_ATTACK_RANGE)
			{
				isStrongAttack = true;
			}
			//爆発攻撃
			else
			{
				isExplosionAttack = true;
			}
		}
		//中距離攻撃
		else if (_targetVecSize <= MIDDLE_ATTACK_RANGE)
		{
			int random = GetRand(RANDOM_RANGE_MIDDLE_ATTACK);
			//回転攻撃
			if (random == 0)
			{
				isRotateAttack = true;
				rotateAttackLoopTime->StartTimer();
			}
			//ジャンプ攻撃
			else
			{
				isJumpAttack = true;
				jumpAttackTargetPos = _targetPos;
			}
		}
		//遠距離攻撃
		else if (_targetVecSize <= LONG_ATTACK_RANGE)
		{
			isMeteoAttack = true;
		}
		//それよりも離れていたら攻撃フラグを下し、近づくために移動フラグを立てる
		else
		{
			isAttack = false;
			isMove = true;
		}
	}
	//攻撃をしていた場合、攻撃を終了するための処理を行う
	else
	{
		//回転攻撃をしていたら
		if (isRotateAttack && rotateAttackLoopTime->getIsStartTimer())
		{
			//タイマーが目標時間に達したら
			if (rotateAttackLoopTime->CountTimer())
			{
				//フラグを調整する
				rotateAttackLoopTime->EndTimer();
				isAttack = false;
				isRotateAttack = false;
				isRestTime = true;
				restTimeAfterAttack->StartTimer();
			}
		}
		else if(isJumpAttack)
		{
			if (anim->GetIsChangeAnim())
			{
				isJumpAttack = false;
				isFly = true;
			}
		}
		//ジャンプ・通常・強い・爆発・隕石攻撃をしていたら
		else if (isMeteoAttack || isExplosionAttack || isNormalAttack || isStrongAttack)
		{
			if (anim->GetIsChangeAnim())
			{
				//フラグを調整する
				isJumpAttack = false;
				isMeteoAttack = false;
				isExplosionAttack = false;
				isNormalAttack = false;
				isStrongAttack = false;
				isAttack = false;
				isRestTime = true;
				restTimeAfterAttack->StartTimer();
			}
		}
	}
}
const void BossEnemy::Rest()
{
	if (restTimeAfterAttack->CountTimer())
	{
		restTimeAfterAttack->EndTimer();
		isRestTime = false;
	}
}
/// <summary>
/// 移動
/// </summary>
const void BossEnemy::Move(const VECTOR _playerPos)
{
	moveVec = ORIGIN_POS;
	//目標までのベクトル
	VECTOR targetVec = ORIGIN_POS;
	//正規化したベクトル
	VECTOR normalizePos = ORIGIN_POS;
	//返り値として返す移動後座標（角度有）
	VECTOR outPutPos = ORIGIN_POS;
	//ベクトルの大きさ
	float vectorSize = 0.0f;
	//目標までのベクトル
	targetVec = VSub(pos, _playerPos);
	//そのベクトルの大きさを求める
	vectorSize = VSize(targetVec);
	//目標までのベクトルを正規化する
	normalizePos = VNorm(targetVec);
	//もし休憩していなければ攻撃する
	if (!isRestTime)
	{
		Attack(vectorSize,_playerPos);
		//角度を変える
		rotate = VGet(0.0f, (float)ChangeRotate(_playerPos), 0.0f);
		//移動・角度の変更が必要な時に変更する
		if (isMove || isRotateAttack)
		{
			moveVec = VScale(normalizePos, status->GetAgi() * -1);
		}
		else if (isFly)
		{
			if (!isOnGround)
			{
				pos.y = 500.0f;
			}
			//目標までのベクトル
			targetVec = VSub(pos, _playerPos);
			//そのベクトルの大きさを求める
			vectorSize = VSize(targetVec);
			//目標までのベクトルを正規化する
			normalizePos = VNorm(targetVec);

			
			if (vectorSize >= 501.0f)
			{
				moveVec = VScale(normalizePos, status->GetAgi() * -30);
			}
			else
			{
				isOnGround = true;
				pos.y = 0.0f;
				frameCount++;
				if (frameCount == 10)
				{
					frameCount = 0;
					isFly = false;
					isAttack = false;
					isRestTime = true;
					isOnGround = false;
					restTimeAfterAttack->StartTimer();
				}
			}
		}
	}
	//もし休憩していれば、休憩を終了する判定を行う
	else
	{
		Rest();
	}
}
/// <summary>
/// アニメーションの変更
/// </summary>
void BossEnemy::ChangeAnim()
{
	//死亡アニメーション
	if (status->GetHp() < 0)
	{
		if (!isDeath)
		{
			anim->SetAnim(static_cast<int>(AnimationType::DEATH));
		}
	}
	else
	{
		//もし攻撃中だったら
		if (isAttack)
		{
			//通常攻撃
			if (isNormalAttack)
			{
				anim->SetAnim(static_cast<int>(AnimationType::NORMAL_ATTACK));
				spherePos = MV1GetFramePosition(modelHandle, 15);
				attackRadius = 10.0f;
			}
			//強い攻撃
			else if (isStrongAttack)
			{
				anim->SetAnim(static_cast<int>(AnimationType::STRONG_ATTACK));
				spherePos = MV1GetFramePosition(modelHandle, 11);
				attackRadius = 10.0f;
			}
			//回転攻撃
			else if (isRotateAttack)
			{
				anim->SetAnim(static_cast<int>(AnimationType::ROTATE_ATTACK));
				spherePos = MV1GetFramePosition(modelHandle, 30);
				attackRadius = 10.0f;
			}
			//ジャンプ攻撃
			else if (isJumpAttack)
			{
				anim->SetAnim(static_cast<int>(AnimationType::JUMP_ATTACK));
				spherePos = pos;
				attackRadius = 30.0f;
			}
			//隕石攻撃
			else if (isMeteoAttack)
			{
				anim->SetAnim(static_cast<int>(AnimationType::METEO_ATTACK));
				spherePos = VGet(0.0f, 500.0f, 0.0f);
				attackRadius = 20.0f;
			}
			//爆発攻撃
			else if (isExplosionAttack)
			{
				anim->SetAnim(static_cast<int>(AnimationType::EXPLOSION_ATTACK));
				spherePos = VGet(0.0f, 500.0f, 0.0f);
				attackRadius = 20.0f;
			}
			else if (isFly)
			{
				spherePos = pos;
				anim->SetAnim(static_cast<int>(AnimationType::IDLE));
			}
		}
		else if (isRestTime)
		{
			anim->SetAnim(static_cast<int>(AnimationType::IDLE));
		}
		else if (isMove)
		{
			spherePos = VGet(0.0f, 500.0f, 0.0f);
			anim->SetAnim(static_cast<int>(AnimationType::WALK));
		}
	}
}
/// <summary>
///	角度の変更
/// </summary>
float BossEnemy::ChangeRotate(const VECTOR _playerPos)
{
	//2点間のベクトルを出す(エネミーからプレイヤー)
	VECTOR EP_Vector = VSub(pos, _playerPos);
	return static_cast<float>(atan2(static_cast<double>(EP_Vector.x), static_cast<double>(EP_Vector.z)));
}
/// <summary>
/// UIの更新
/// </summary>
const void BossEnemy::UpdateUI()
{
	//最大HPを求める
	//現在のHPを求める
	//指数化する（式：現在のHP/最大HP * 100）
	nowHP.x = static_cast<int>(status->GetHp() / status->GetMaxHP() * 1000.0f);

	if (nowHP.x <  0)
	{
		nowHP.x = 0;
	}
}
/// <summary>
/// UIの描画
/// </summary>
const void BossEnemy::DrawUI()
{
	//テキストの表示
	DrawStringToHandle(50, 980, "HP", FONT_COLOR, font);
	//フレームの描画
	DrawExtendGraph(static_cast<int>(HP_FRAME_POS.LX), static_cast<int>(HP_FRAME_POS.LZ), static_cast<int>(HP_FRAME_POS.RX), static_cast<int>(HP_FRAME_POS.RZ), frameImage, TRUE);
	//HPバーの表示
	DrawExtendGraph(HP_BAR_POS.x, HP_BAR_POS.y, HP_BAR_POS.x + nowHP.x, HP_BAR_POS.y + nowHP.y, hpImage, TRUE);
}
const void BossEnemy::PhysicalRecovery()
{
	status->PhysicalRecovery();
}
