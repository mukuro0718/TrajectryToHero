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
BossEnemy::BossEnemy(const VECTOR _spawnPos,const int _modelHandle, const int _frameImage, const int _hpImage, const int _font)
	:EnemyBase(_modelHandle)
	,font(_font)
	,frameImage(_frameImage)
	,hpImage(_hpImage)
	, preliminaryOperation(nullptr)
	, isPreliminaryOperation(false)
	, isAttackPreparation(false)
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
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/WalkAnim.mv1"), 0);
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/StronglAttackAnim.mv1"), 0);	//通常攻撃アニメーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/RotateAttackAnim.mv1"), 0);	//回転攻撃アニメーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/JumpAttackAnim.mv1"), 0);		//ジャンプ攻撃アニメーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/JumpIdleAnim.mv1"), 0);			//待機アニメーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/IdleAnim.mv1"), 0);			//待機アニメーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/DeathAnim.mv1"), 0);			//死亡アニメーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/BeforeAttackAnim.mv1"), 0);//攻撃前モーション
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
	waitBeforeJumpAttack	= new Timer();
	waitBeforeRotateAttack	= new Timer();
	rotateAttackLoopTime	= new Timer();
	preliminaryOperation = new Timer();

}
/// <summary>
/// 初期化
/// </summary>
void BossEnemy::Init()
{
	//必要なInitクラスの呼び出し
	waitBeforeJumpAttack  ->Init(20);
	waitBeforeRotateAttack->Init(10);
	rotateAttackLoopTime  ->Init(50);
	invincibleTimer		  ->Init(8);	
	restTimeAfterAttack   ->Init(30);
	preliminaryOperation->Init(12);
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
	isPreliminaryOperation = false;
	isAttackPreparation = false;
	SetUpCapsule(pos, HEIGHT, RADIUS, CAPSULE_COLOR, false);
	SetUpSphere(spherePos, 10.0f, CAPSULE_COLOR, false);
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
	if (waitBeforeJumpAttack)
	{
		delete(waitBeforeJumpAttack);
		waitBeforeJumpAttack = nullptr;
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
	SetUpSphere(spherePos, 10.0f, CAPSULE_COLOR, false);
	blood->Update(45);
	//色の変更
	ChangeColor();
	//アニメーション再生時間をセット
	anim->Play(&modelHandle, 0.8f);
}
/// <summary>
/// 移動
/// </summary>
void BossEnemy::Move(const VECTOR _playerPos)
{
	moveVec = ORIGIN_POS;
	//目標までのベクトル
	VECTOR targetPos = ORIGIN_POS;
	//正規化したベクトル
	VECTOR normalizePos = ORIGIN_POS;
	//返り値として返す移動後座標（角度有）
	VECTOR outPutPos = ORIGIN_POS;
	//ベクトルの大きさ
	float vectorSize = 0.0f;
	//目標までのベクトル
	targetPos = VSub(pos, _playerPos);
	//そのベクトルの大きさを求める
	vectorSize = VSize(targetPos);
	//printfDx("size %f", vectorSize);
	//目標までのベクトルを正規化する
	normalizePos = VNorm(targetPos);
	//攻撃も休憩もしていなかったら
	if (!isAttackPreparation && !isRestTime)
	{
		//攻撃フラグを立てる
		//isAttack = true;
		isAttackPreparation = true;
		if (vectorSize <= 20)
		{
			attackType = static_cast<int>(AnimationType::NORMAL_ATTACK);
		}
		else
		{
			attackType = GetRand(1) + 2;
		}
	}
	if (!isRestTime)
	{
			//角度を変える
			rotate = VGet(0.0f, (float)ChangeRotate(_playerPos), 0.0f);
		//もし回転攻撃タイマーが始まっていて
		if (rotateAttackLoopTime->getIsStartTimer())
		{
			//目標時間に達したら
			if (rotateAttackLoopTime->CountTimer())
			{
				//休憩タイマーをスタートさせる
				restTimeAfterAttack->StartTimer();
				isRestTime = true;
				isPreliminaryOperation = false;
				isAttack = false;
				//回転攻撃タイマーを終わらせる
				rotateAttackLoopTime->EndTimer();
			}
			else
			{
				//目標までのベクトル
				targetPos = VSub(pos, _playerPos);
				//そのベクトルの大きさを求める
				vectorSize = VSize(targetPos);
				//目標までのベクトルを正規化する
				normalizePos = VNorm(targetPos);
				moveVec = VScale(normalizePos, status->GetAgi() * -1);
			}
		}
		//もしジャンプ攻撃タイマーが始まっていて
		if (waitBeforeJumpAttack->getIsStartTimer())
		{
			//目標時間に達したら
			if (waitBeforeJumpAttack->CountTimer())
			{
				jumpAttackTargetPos = _playerPos;
				isJumpAttack = true;
				isAttack = true;
				waitBeforeJumpAttack->EndTimer();
			}
		}
		if (isJumpAttack)
		{
			//目標までのベクトル
			targetPos = VSub(pos, jumpAttackTargetPos);
			//そのベクトルの大きさを求める
			vectorSize = VSize(targetPos);
			//目標までのベクトルを正規化する
			normalizePos = VNorm(targetPos);
			//ベクトルの大きさが定数値以下になったら
			if (vectorSize <= 20)
			{
				//休憩タイマーが始める
				restTimeAfterAttack->StartTimer();
				isRestTime = true;
				isAttack = false;
			}
			else
			{
				moveVec = VScale(normalizePos, status->GetAgi() * -3);
				//角度を変える
				rotate = VGet(0.0f, (float)ChangeRotate(jumpAttackTargetPos), 0.0f);
			}
		}

	}
	//もし休憩時間タイマーが始まっていて
	else if (restTimeAfterAttack->getIsStartTimer())
	{
		//目標時間に達したら
		if (restTimeAfterAttack->CountTimer())
		{
			restTimeAfterAttack->EndTimer();
			isRestTime = false;
			isAttackPreparation = false;
		}
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
		if (!isRestTime)
		{
			switch (attackType)
			{
			case 1://通常
				if (isAttack)
				{


					anim->SetAnim(static_cast<int>(AnimationType::NORMAL_ATTACK));
					spherePos = MV1GetFramePosition(modelHandle, 11);
					attackAnimLoopCount = 1;
				}
				break;
			case 2://回転
					if (!isPreliminaryOperation)
					{
						preliminaryOperation->StartTimer();
					}
					else
					{
						isAttack = true;
						anim->SetAnim(static_cast<int>(AnimationType::ROTATE_ATTACK));
						spherePos = MV1GetFramePosition(modelHandle, 31);
						rotateAttackLoopTime->StartTimer();
					}
					if (preliminaryOperation->getIsStartTimer())
					{
						anim->SetAnim(static_cast<int>(AnimationType::BEFORE_ATTACK));
						if (preliminaryOperation->CountTimer())
						{
							preliminaryOperation->EndTimer();
							isPreliminaryOperation = true;
						}
					}
				
				break;
			case 3://ジャンプ
				if (isAttack || isAttackPreparation)
				{
					anim->SetAnim(static_cast<int>(AnimationType::JUMP_ATTACK));
					spherePos = MV1GetFramePosition(modelHandle, 7);
					if (!isJumpAttack)
					{
						waitBeforeJumpAttack->StartTimer();
					}
				}
				break;
			default:
				break;
			}
		}
		if (isRestTime)
		{
			spherePos = MV1GetFramePosition(modelHandle, 7);
			if (anim->GetAnim() == static_cast<int>(AnimationType::JUMP_IDLE) && anim->GetPlayTime() == 0.0f)
			{
				anim->SetAnim(static_cast<int>(AnimationType::IDLE));
				attackType = 0;
				isJumpAttack = false;
			}
			//アニメーションがジャンプアタックだったら
			else if (attackType == static_cast<int>(AnimationType::JUMP_ATTACK))
			{
				anim->SetAnim(static_cast<int>(AnimationType::JUMP_IDLE));
			}
			else
			{
				anim->SetAnim(static_cast<int>(AnimationType::IDLE));
			}
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
/// <summary>
/// UIの更新
/// </summary>
void BossEnemy::UpdateUI()
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
void BossEnemy::DrawUI()
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
