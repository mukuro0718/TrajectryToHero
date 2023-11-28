////===========================================================================
////@brief ウィークエネミークラス/継承
////===========================================================================
//
//#include"WeakEnemy.h"
//#include<math.h>
//#include"Animation.h"
//#include"CharacterStatus.h"
//#include"Timer.h"
////モデル設定
// const VECTOR WeakEnemy::MODEL_SCALE = VGet(0.2f, 0.2f, 0.2f);//モデルの拡大率
// const VECTOR WeakEnemy::MODEL_ROTATE = VGet(0.0f, 90 * DX_PI_F / 180.0f, 0.0f);//モデルの回転値
// 
///// <summary>
///// コンストラクタ
///// </summary>
//WeakEnemy::WeakEnemy(int modelHandle)
// :EnemyBase(modelHandle)
//{
//	//インスタンスの初期化
//	statusInit = NULL;
//	invincibleTimer = NULL;
//	restTimeAfterAttack = NULL;
//	anim = NULL;
//	//インスタンスの生成
//	statusInit = new StatusInit();
//	invincibleTimer = new Timer();
//	restTimeAfterAttack = new Timer();
//	anim = new Animation();
//	Init();
//	//スケールのセット
//	MV1SetScale(base.modelHandle, base.scale);
//	//回転値のセット
//	MV1SetRotationXYZ(base.modelHandle, base.rotate);
//	//コリジョン情報を構築
//	MV1SetupCollInfo(base.modelHandle, -1, 1, 1, 1);
//	//アニメーションの追加
//	anim->Add(MV1LoadModel("Data/Animation/WeakEnemy_RunAnim.mv1"), 1);				//走りアニメーション
//	anim->Add(MV1LoadModel("Data/Animation/WeakEnemy_StrongAttack.mv1"), 1);		//攻撃アニメーション
//	anim->Add(MV1LoadModel("Data/Animation/Enemy_IdleAnim_publi.mv1"), 1);			//待機アニメーション
//	anim->Add(MV1LoadModel("Data/Animation/Enemy_DeathAnim_public.mv1"), 1);		//死亡アニメーション
//	//アタッチするアニメーション
//	anim->SetAnim(static_cast<int>(AnimationType::IDLE));
//	//アニメーションのアタッチ
//	anim->Attach(&base.modelHandle);
//}
///// <summary>
///// デストラクタ
///// </summary>
//WeakEnemy::~WeakEnemy()
//{
//	Final();
//}
///// <summary>
///// 初期化
///// </summary>
//void WeakEnemy::Init()
//{
//	//必要なInitクラスの呼び出し
//	invincibleTimer->Init(9);
//	restTimeAfterAttack->Init(20);
//	status = statusInit->InitWeakEnemyStatus();
//	//新しい座標の生成
//	base.pos = NewRandomPos();
//	base.rotate		  = MODEL_ROTATE;
//	base.scale		  = MODEL_SCALE;
//	base.radius		  = 8.0f;
//	base.isAttack	  = false;
//	base.isDeath	  = false;
//	base.isHit		  = false;
//	isRestTime		  = false;
//	//最大HPの設定
//	maxHP = status.HP;
//	base.pos.y = 10.0f;
//}
///// <summary>
///// 更新
///// </summary>
//void WeakEnemy::Update(VECTOR playerPos)
//{
//	//無敵フラグが立っていたら
//	if (status.isInvincible)
//	{
//		//タイマーを始める
//		invincibleTimer->StartTimer();
//		if (invincibleTimer->CountTimer())
//		{
//			invincibleTimer->EndTimer();
//			status.isInvincible = false;
//		}
//	}
//	//コリジョン情報を更新
//	MV1RefreshCollInfo(base.modelHandle, -1);
//	
//	//もしHPをつけてHPが０になったら
//	if (status.HP <0)
//	{
//		//現在のアニメーションをやられたアニメーションにする
//		if (!base.isDeath)
//		{
//			anim->SetAnim(static_cast<int>(AnimationType::DEATH));
//		}
//		if(anim->GetAnim() == static_cast<int>(AnimationType::DEATH) && anim->GetPlayTime() == 0.0f)
//		{
//			base.isDeath = true;
//			base.pos = DESTROY_POS;
//		}
//	}
//	else
//	{
//		base.pos = VAdd(base.pos, Move(playerPos));//移動
//		MV1SetRotationXYZ(base.modelHandle, base.rotate);//回転値の設定
//	}
//	base.pos.y = 10.0f;
//	MV1SetPosition(base.modelHandle, base.pos);//位置の設定
//	//アニメーション再生時間をセット
//	anim->Play(&base.modelHandle);
//
//}
///// <summary>
///// 移動
///// </summary>
//VECTOR WeakEnemy::Move(VECTOR playerPos)
//{
//	//目標までのベクトル
//	VECTOR targetPos = ORIGIN_POS;
//	//正規化したベクトル
//	VECTOR normalizePos = ORIGIN_POS;
//	//返り値として返す移動後座標（角度有）
//	VECTOR outPutPos = ORIGIN_POS;
//	float vectorSize = 0.0f;
//	//プレイヤーと自分の座標のベクトルの差を求める(目標までのベクトル)
//	targetPos = VSub(base.pos, playerPos);
//	//そのベクトルの大きさを求める
//	vectorSize = VSize(targetPos);
//	//目標までのベクトルを正規化する
//	normalizePos = VNorm(targetPos);
//	//もしベクトルサイズが80以下だったら攻撃する
//	if (vectorSize <= 80.0f)
//	{
//		if (!base.isAttack && !isRestTime)
//		{
//			anim->SetAnim(static_cast<int>(AnimationType::ATTACK));
//			attackAnimLoopCount = 100;
//			base.isAttack = true;
//		}
//	}
//	else
//	{
//		if (!base.isAttack && !isRestTime)
//		{
//			//もしベクトルサイズが200以下だったらプレイヤーに向けて走る
//			if (vectorSize <= 100.0f)
//			{
//				anim->SetAnim(static_cast<int>(AnimationType::RUN));
//			}
//			//それより離れていたら
//			else
//			{
//				anim->SetAnim(static_cast<int>(AnimationType::IDLE));
//			}
//		}
//	}
//	//攻撃アニメーション中かつアニメーション変更フラグが立っていたら
//	if (base.isAttack)
//	{
//		//攻撃回数が０になったら休憩する
//		if (attackAnimLoopCount == 0 || vectorSize <= 0)
//		{
//			attackAnimLoopCount = 0;
//			restTimeAfterAttack->StartTimer();
//			base.isAttack = false;
//			isRestTime = true;
//			anim->SetAnim(static_cast<int>(AnimationType::IDLE));
//		}
//		//0じゃなければ攻撃回数を減らす
//		else
//		{
//			attackAnimLoopCount--;
//		}
//	}
//	//もし休憩中だったら
//	else if (isRestTime)
//	{
//		anim->SetAnim(static_cast<int>(AnimationType::IDLE));
//		//タイマーが終了していたら
//		if (restTimeAfterAttack->CountTimer())
//		{
//			isRestTime = false;
//			restTimeAfterAttack->EndTimer();
//		}
//	}
//	if (anim->GetAnim() != static_cast<int>(AnimationType::IDLE) && vectorSize >=20 &&!isRestTime)
//	{
//		// もし攻撃中に正規化した値がーになっていたら正規化した値に移動スピードをかけて移動量を返す
//		outPutPos = VScale(normalizePos, status.AGI * -1);
//		//角度を変える
//		base.rotate = VGet(0.0f, (float)ChangeRotate(playerPos), 0.0f);
//	}
//	return outPutPos;
//}
///// <summary>
/////	角度の変更(モデルが向いている初期方向がz＝０)
///// </summary>
//double WeakEnemy::ChangeRotate(VECTOR playerPos)
//{
//	//2点間のベクトルを出す(エネミーからプレイヤー)
//	VECTOR EP_Vector = VSub(base.pos, playerPos);
//	//2点の座標からラジアンを求める
//	return static_cast<float>(atan2(static_cast<double>(EP_Vector.x), static_cast<double>(EP_Vector.z)));
//}
//
///// <summary>
///// ノックバック処理
///// </summary>
//void WeakEnemy::Final()
//{
//	if (statusInit)
//	{
//		delete(statusInit);
//		statusInit = NULL;
//	}
//	if (invincibleTimer)
//	{
//		delete(invincibleTimer);
//		invincibleTimer = NULL;
//	}
//	if (restTimeAfterAttack)
//	{
//		delete(restTimeAfterAttack);
//		restTimeAfterAttack = NULL;
//	}
//	if (anim)
//	{
//		delete(anim);
//		anim = NULL;
//	}
//}
