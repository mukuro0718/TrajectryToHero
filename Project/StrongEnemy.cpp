#include"StrongEnemy.h"
#include<math.h>
#include"Animation.h"
#include"CharacterStatus.h"
#include"Timer.h"
#include"BloodParticle.h"
#include"SpawnParticle.h"
#include"Explosion.h"

//モデル設定
const VECTOR   StrongEnemy::MODEL_SCALE	= VGet(0.3f, 0.3f, 0.3f);//モデルの拡大率
const VECTOR   StrongEnemy::MODEL_ROTATE	= VGet(0.0f, 90 * DX_PI_F / 180.0f, 0.0f);//モデルの回転値
const int      StrongEnemy::CAPSULE_COLOR = GetColor(0, 255, 0);
const int	   StrongEnemy::HOMING_MAGIC_COLOR = GetColor(100, 100, 200);
const int	   StrongEnemy::EXPLOSION_MAGIC_COLOR = GetColor(200, 100, 0);
const VERTEX3D StrongEnemy::INIT_MAGIC_CIRCLE_VERTEX
{
	ORIGIN_POS				,
	VGet(0.0f,1.0f,0.0f)	,
	GetColorU8(255,255,255,150),
	GetColorU8(0,0,0,0),
	1.0f,
	1.0f,
	1.0f,
	1.0f
};
const VECTOR StrongEnemy::MAGIC_CIRCLE_VERTEX_OFFSET[MAGIC_CIRCLE_VERTEX_NUM]
{
		{ 50.0f,1.0f, 50.0f},
		{ 50.0f,1.0f,-50.0f},
		{-50.0f,1.0f,-50.0f},
		{-50.0f,1.0f, 50.0f},
};
const VECTOR StrongEnemy::MAGIC_CIRCLE_VERTEX_OFFSET_2[MAGIC_CIRCLE_VERTEX_NUM]
{
		{ 30.0f,1.0f, 30.0f},
		{ 30.0f,1.0f,-30.0f},
		{-30.0f,1.0f,-30.0f},
		{-30.0f,1.0f, 30.0f},
};
const VERTEX3D StrongEnemy::INIT_VERTEX_FOR_HOMING_MAGIC
{
	ORIGIN_POS				,
	VGet(0.0f,1.0f,0.0f)	,
	GetColorU8(100,100,255,255),
	GetColorU8(100,100,255,255),
	0.0f,
	0.0f,
	0.0f,
	0.0f
};
const VECTOR StrongEnemy::VERTEX_OFFSET_FOR_HOMING_MAGIC[HOMING_MAGIC_VERTEX_NUM]
{
		{  0.0f, 40.0f ,  0.0f},
		{ 15.0f, 25.0f ,  0.0f},
		{  0.0f, 25.0f , 15.0f},
		{-15.0f, 25.0f ,  0.0f},
		{  0.0f, 25.0f ,-15.0f},
		{ 10.0f, 0.0f  ,  0.0f},
		{  0.0f, 0.0f  , 10.0f},
		{-10.0f, 0.0f  ,  0.0f},
		{  0.0f, 0.0f  ,-10.0f},
};
/// <summary>
/// コンストラクタ
/// </summary>
StrongEnemy::StrongEnemy(const VECTOR _spawnPos,const int _modelHandle)
	: EnemyBase(_modelHandle)
	, invincibleTimer(nullptr)
	, restTimeAfterAttack(nullptr)
	, anim(nullptr)
	, randomRest(nullptr)
	, explosion(nullptr)
	, animPlayTime{0.8f,0.5f,0.3f,0.8f,0.8f}
	, attackType(0)
	, homingMoveVec(ORIGIN_POS)
	, explosionMagicRadius(0.0f)
	, magicWaitFrameCount(0)
	, isInitMagicExp(false)
	, magicCircleTexture(0)
	, magicCircleTexture2(0)
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
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Strong/RunAnim.mv1")		, 0);			//走りアニメーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Strong/HomingMagic.mv1")	, 0);		//攻撃アニメーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Strong/ExplosionMagic.mv1"), 0);		//攻撃アニメーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Strong/IdleAnim.mv1")		, 0);			//待機アニメーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Strong/DeathAnim.mv1")		, 1);		//死亡アニメーション
	magicCircleTexture = LoadGraph("Data/Texture/Enemy/magicCircle2.png");
	magicCircleTexture2 = LoadGraph("Data/Texture/Enemy/magicCircle.png");
	//アタッチするアニメーション
	anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	//アニメーションのアタッチ
	anim->Attach(&modelHandle);
	for (int i = 0; i < MAGIC_CIRCLE_VERTEX_NUM; i++)
	{
		magicCircleVertex[i] = INIT_MAGIC_CIRCLE_VERTEX;
		magicCircleVertex2[i] = INIT_MAGIC_CIRCLE_VERTEX;
	}
	for (int i = 0; i < HOMING_MAGIC_VERTEX_NUM; i++)
	{
		homingMagicVertex[i] = INIT_VERTEX_FOR_HOMING_MAGIC;
	}
	magicCircleVertex[0].u = 0.0f;
	magicCircleVertex[0].v = 0.0f;
	magicCircleVertex[1].u = 1.0f;
	magicCircleVertex[1].v = 0.0f;
	magicCircleVertex[2].u = 1.0f;
	magicCircleVertex[2].v = 1.0f;
	magicCircleVertex[3].u = 0.0f;
	magicCircleVertex[3].v = 1.0f;

	magicCircleVertex2[0].u = 0.0f;
	magicCircleVertex2[0].v = 0.0f;
	magicCircleVertex2[1].u = 1.0f;
	magicCircleVertex2[1].v = 0.0f;
	magicCircleVertex2[2].u = 1.0f;
	magicCircleVertex2[2].v = 1.0f;
	magicCircleVertex2[3].u = 0.0f;
	magicCircleVertex2[3].v = 1.0f;
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
	anim				= new Animation();
	explosion			= new Explosion();
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
const void StrongEnemy::Init()
{
	//必要なInitクラスの呼び出し
	invincibleTimer->Init(8);
	restTimeAfterAttack->Init(20);
	randomRest->Init(20);
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
	isSpawn = true;//スポーンしたか
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
const void StrongEnemy::Update()
{
	if (isSpawn)
	{
		spawnFrameCount++;
		if (spawnFrameCount >= 120)
		{
			isSpawn = false;
			spawnFrameCount = 0;
		}
	}
	else
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
		blood->Update(50);
		//色の変更
		ChangeColor();
		//アニメーション再生時間をセット
		anim->Play(&modelHandle, animPlayTime[anim->GetAnim()]);
	}
	spawnParticle->Init(spawnPos, isSpawn);
	spawnParticle->Update();
}
const void StrongEnemy::DrawAttackRange()
{
	if (isAttack)
	{
		switch (attackType)
		{
			//ホーミング
		case static_cast<int>(AttackType::HOMING_MAGIC):
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
			DrawPolygonIndexed3D(magicCircleVertex2, MAGIC_CIRCLE_VERTEX_NUM, MAGIC_CIRCLE_INDEX, MAGIC_CIRCLE_POLYGON_NUM, magicCircleTexture2, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			break;
			//爆発
		case static_cast<int>(AttackType::EXPROSION_MAGIC):
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
			DrawPolygonIndexed3D(magicCircleVertex, MAGIC_CIRCLE_VERTEX_NUM, MAGIC_CIRCLE_INDEX, MAGIC_CIRCLE_POLYGON_NUM, magicCircleTexture, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			break;
		}
	}
}
void StrongEnemy::Attack(const VECTOR _playerPos)
{
	VECTOR spherePos = ORIGIN_POS;
	int sphereColor = 0;
	float sphereRadius = 0.0f;
	//攻撃フラグが立っていたら
	if (isAttack)
	{
		magicWaitFrameCount++;
		switch (attackType)
		{
			//ホーミング
		case static_cast<int>(AttackType::HOMING_MAGIC):
			if (magicWaitFrameCount <= BEFORE_HOMING_MAGIC_WAIT_FRAME_COUNT)
			{
				for (int i = 0; i < HOMING_MAGIC_VERTEX_NUM; i++)
				{
					homingMagicVertex[i].pos = VAdd(_playerPos, VERTEX_OFFSET_FOR_HOMING_MAGIC[i]);
				}
				for (int i = 0; i < MAGIC_CIRCLE_VERTEX_NUM; i++)
				{
					magicCircleVertex2[i].pos = VAdd(_playerPos, MAGIC_CIRCLE_VERTEX_OFFSET_2[i]);
				}
				isInitMagicExp = true;
			}
			else if (magicWaitFrameCount > AFTER_HOMING_MAGIC_WAIT_FRAME_COUNT)
			{
				//現在のアニメーションが終了していたら
				if (anim->GetAnim() == static_cast<int>(AnimationType::HOMING) && anim->GetPlayTime() == 0.0f)
				{
					//必要な変数を初期化する
					magicWaitFrameCount = 0;
					spherePos = VGet(0.0f, 500.0f, 0.0f);
					isAttack = false;
					restTimeAfterAttack->StartTimer();
					isRestTime = true;
				}

				spherePos = homingMagicVertex[0].pos;
				spherePos.y = 5.0f;
			}
			sphereColor = HOMING_MAGIC_COLOR;
			sphereRadius = SPHERE_RADIUS;
			break;
			//爆発
		case static_cast<int>(AttackType::EXPROSION_MAGIC):
			if (magicWaitFrameCount <= BEFORE_EXPLOSION_MAGIC_WAIT_FRAME_COUNT)
			{
				if (!isInitMagicExp)
				{
					for (int i = 0; i < MAGIC_CIRCLE_VERTEX_NUM; i++)
					{
						magicCircleVertex[i].pos = VAdd(pos, MAGIC_CIRCLE_VERTEX_OFFSET[i]);
					}
					isInitMagicExp = true;
				}
			}
			else
			{

				//スフィアの中心座標を決める
				spherePos = explosion->GetSphereInfo().centerPos;
				sphereColor = EXPLOSION_MAGIC_COLOR;
				sphereRadius = explosion->GetSphereInfo().radius;

				//現在のアニメーションをやられたアニメーションにする
				if (anim->GetAnim() == static_cast<int>(AnimationType::EXPLOSION) && anim->GetPlayTime() == 0.0f)
				{
					//必要な変数を初期化する
					magicWaitFrameCount = 0;
					spherePos = VGet(0.0f, 500.0f, 0.0f);
					isAttack = false;
					explosionMagicRadius = 0.0f;
					sphereRadius = explosionMagicRadius;
					restTimeAfterAttack->StartTimer();
					isRestTime = true;
					isInitMagicExp = false;
				}
				explosion->Update(isInitMagicExp, pos);
			}
			break;
		}
	}
	SetUpSphere(spherePos, sphereRadius, sphereColor, true);
}
const void StrongEnemy::DrawMagicSphere()
{
	if (attackType == static_cast<int>(AttackType::EXPROSION_MAGIC))
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
		DrawSphere(sphereInfo);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		explosion->Draw();
	}
	else
	{
		if (magicWaitFrameCount > AFTER_HOMING_MAGIC_WAIT_FRAME_COUNT)
		{
			DrawSphere(sphereInfo);
			DrawPolygonIndexed3D(homingMagicVertex, HOMING_MAGIC_VERTEX_NUM, HOMING_MAGIC_INDEX, HOMING_MAGIC_POLYGON_NUM, DX_NONE_GRAPH, TRUE);
		}
	}
}
/// <summary>
/// 移動
/// </summary>
const void StrongEnemy::Move(VECTOR _playerPos)
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
	targetPos = VSub(_playerPos,pos);
	//そのベクトルの大きさを求める
	vectorSize = VSize(targetPos);
	//目標までのベクトルを正規化する
	normalizePos = VNorm(targetPos);
		//すでに攻撃していない、休憩中ではない
	if (!isAttack && !isRestTime)
	{
		//もしベクトルサイズが定数以下だったら攻撃する
		if (vectorSize <= 50.0f)
		{
			attackType = static_cast<int>(AttackType::EXPROSION_MAGIC);
			attackNum++;
			isAttack = true;
			isMove = false;
			isRandomWalk = false;
			isRandomRest = false;
		}
		else if (vectorSize <= 100.0f)
		{
			attackType = static_cast<int>(AttackType::HOMING_MAGIC);
			isAttack = true;
			isMove = false;
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
	//攻撃アニメーション中かつアニメーション変更フラグが立っていたら
	if (isAttack)
	{
		Attack(_playerPos);
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
	if (isMove && vectorSize >= 20)
	{
		// もし攻撃中に正規化した値がーになっていたら正規化した値に移動スピードをかけて移動量を返す
		moveVec = VScale(normalizePos, status->GetAgi() * -1);
		//角度を変える
		rotate = VGet(0.0f, (float)ChangeRotate(_playerPos), 0.0f);
	}
	else if (isAttack && vectorSize >= 20)
	{
		//角度を変える
		rotate = VGet(0.0f, (float)ChangeRotate(_playerPos), 0.0f);
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
		sphereInfo.centerPos = VGet(0.0f,500.0f,0.0f);
	}
	//攻撃中だったら
	else if (isAttack && !isMove && !isRestTime)
	{
		if (attackType == static_cast<int>(AttackType::HOMING_MAGIC))
		{
			anim->SetAnim(static_cast<int>(AnimationType::HOMING));
		}
		else if (attackType == static_cast<int>(AttackType::EXPROSION_MAGIC))
		{
			anim->SetAnim(static_cast<int>(AnimationType::EXPLOSION));
		}
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
