////===========================================================================
////@brief ボスエネミークラス/継承
////===========================================================================
//
//#include"Boss.h"
//#include<math.h>
//#include"Animation.h"
//#include"CharacterStatus.h"
//#include"Timer.h"
////モデル設定
//const VECTOR Boss::MODEL_SCALE = VGet(0.4f, 0.4f, 0.4f);//モデルの拡大率
//const VECTOR Boss::MODEL_ROTATE = VGet(0.0f, 90 * DX_PI_F / 180.0f, 0.0f);//モデルの回転値
//const VECTOR Boss::INIT_POS = VGet(0.0f, 0.0f, 500.0f);//モデルの回転値
//
///// <summary>
///// コンストラクタ
///// </summary>
//Boss::Boss(int modelHandle)
//	:EnemyBase(modelHandle)
//{
//	//インスタンスの初期化
//	statusInit			= NULL;
//	invincibleTimer		= NULL;
//	restTimeAfterAttack = NULL;
//	anim				= NULL;
//	//インスタンスの生成
//	statusInit			= new StatusInit();
//	invincibleTimer		= new Timer();
//	restTimeAfterAttack = new Timer();
//	anim				= new Animation();
//	//モデル設定
//	MV1SetScale(base.modelHandle, base.scale);
//	//回転値のセット
//	MV1SetRotationXYZ(base.modelHandle, base.rotate);
//	//コリジョン情報を構築
//	MV1SetupCollInfo(base.modelHandle, -1, 1, 1, 1);
//	//アニメーションの追加
//	anim->Add(MV1LoadModel("Data/Animation/Boss_Walk.mv1"), 0);
//	anim->Add(MV1LoadModel("Data/Animation/Boss_StronglAttackAnim.mv1"), 0);	//通常攻撃アニメーション
//	anim->Add(MV1LoadModel("Data/Animation/Boss_RotateAttackAnim.mv1"), 0);	//回転攻撃アニメーション
//	anim->Add(MV1LoadModel("Data/Animation/Boss_JumpAttackAnim.mv1"), 0);		//ジャンプ攻撃アニメーション
//	anim->Add(MV1LoadModel("Data/Animation/Boss_JumpIdleAnim.mv1"), 0);			//待機アニメーション
//	anim->Add(MV1LoadModel("Data/Animation/Boss_IdleAnim.mv1"), 0);			//待機アニメーション
//	anim->Add(MV1LoadModel("Data/Animation/Boss_DeathAnim.mv1"), 0);			//死亡アニメーション
//	//アタッチするアニメーション
//	anim->SetAnim(static_cast<int>(AnimationType::IDLE));
//	//アニメーションのアタッチ（最初は明示的に呼び出してアニメーションをアタッチする必要がある）
//	anim->Attach(&base.modelHandle);
//}
///// <summary>
///// デストラクタ
///// </summary>
//Boss::~Boss()
//{
//	Final();
//}
///// <summary>
///// 初期化
///// </summary>
//void Boss::Init()
//{
//	attackType = 0;
//	jumpAttackTargetPos = ORIGIN_POS;
//	waitBeforeJunpAttack = new Timer();
//	waitBeforeJunpAttack->Init(10);
//	waitBeforeRotateAttack = new Timer();
//	waitBeforeRotateAttack->Init(10);
//	rotateAttackLoopTime = new Timer();
//	rotateAttackLoopTime->Init(50);
//	isJumpAttack = false;
//	isJumpIdle = false;
//	//必要なInitクラスの呼び出し
//	invincibleTimer->Init(9);	
//	restTimeAfterAttack->Init(20);
//	status = statusInit->InitBossStatus();
//	//新しい座標の生成
//	base.pos		= INIT_POS;
//	base.rotate		= MODEL_ROTATE;
//	base.scale		= MODEL_SCALE;
//	base.radius		= 20.0f;
//	base.isAttack	= false;
//	base.isDeath	= false;
//	base.isHit		= false;
//	isRestTime		= false;
//	attackAnimLoopCount = 0;
//	//最大HPの設定
//	maxHP = status.HP;
//}
///// <summary>
///// 最終処理
///// </summary>
//void Boss::Final()
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
///// <summary>
///// 更新
///// </summary>
//void Boss::Update(VECTOR playerPos)
//{
//
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
//	//もしプレイヤーに当たっていたら
//	if (status.HP < 0)
//	{
//		//現在のアニメーションをやられたアニメーションにする
//		if (!base.isDeath)
//		{
//			anim->SetAnim(static_cast<int>(AnimationType::DEATH));
//		}
//		if (anim->GetAnim() == static_cast<int>(AnimationType::DEATH) && anim->GetPlayTime() == 0.0f)
//		{
//			base.isDeath = true;
//			base.pos = DESTROY_POS;
//		}
//	}
//	else
//	{
//		playerPos.y = 0.0f;
//		base.pos = VAdd(base.pos, Move(playerPos));//移動
//		MV1SetRotationXYZ(base.modelHandle, base.rotate);//回転値の設定
//	}
//	base.pos = VGet(base.pos.x, 0.0f, base.pos.z);
//	MV1SetPosition(base.modelHandle, base.pos);//位置の設定
//	//アニメーション再生時間をセット
//	anim->Play(&base.modelHandle);
//}
///// <summary>
///// 移動
///// </summary>
//VECTOR Boss::Move(VECTOR playerPos)
//{
//	//目標までのベクトル
//	VECTOR targetPos = ORIGIN_POS;
//	//正規化したベクトル
//	VECTOR normalizePos = ORIGIN_POS;
//	//返り値として返す移動後座標（角度有）
//	VECTOR outPutPos = ORIGIN_POS;
//	float vectorSize = 0.0f;
//	//もし攻撃中ではなかったら攻撃をする
//	if (!base.isAttack)
//	{
//		//もし休憩中ではなければ攻撃パターンを決めなおす
//		if (!isRestTime)
//		{
//			//プレイヤーと自分の座標のベクトルの差を求める(目標までのベクトル)
//			targetPos = VSub(base.pos, playerPos);
//			//そのベクトルの大きさを求める
//			vectorSize = VSize(targetPos);
//			if (vectorSize <= 11)
//			{
//				attackType = 1;
//			}
//			else
//			{
//				attackType = GetRand(1) + 2;
//			}
//			switch (attackType)
//			{
//			case 1://通常
//				anim->SetAnim(static_cast<int>(AnimationType::NORMAL_ATTACK));
//				attackAnimLoopCount = 1;
//				break;
//			case 2://回転
//				anim->SetAnim(static_cast<int>(AnimationType::ROTATE_ATTACK));
//				waitBeforeRotateAttack->StartTimer();
//				isRotateAttack = false;
//				break;
//			case 3://ジャンプ
//				anim->SetAnim(static_cast<int>(AnimationType::JUMP_ATTACK));
//				jumpAttackTargetPos = playerPos;//目標座標を設定
//				waitBeforeJunpAttack->StartTimer();
//				isJumpAttack = false;
//				break;
//			default:
//				break;
//			}
//			base.isAttack = true;
//		}
//	}
//	//攻撃中だったら
//	else
//	{
//		//ジャンプアタック処理
//		/*ジャンプアタック中
//		攻撃開始時に目標座標を設定し、その座標に向かって飛ぶ
//		追尾なしの代わりに、移動速度が速い*/
//		if (attackType == static_cast<int>(AnimationType::JUMP_ATTACK))
//		{
//			//タイマーがスタートしていて、目標時間に達していたら
//			if (waitBeforeJunpAttack->getIsStartTimer() && waitBeforeJunpAttack->CountTimer())
//			{
//				//ジャンプアタックを許可する
//				isJumpAttack = true;
//				//タイマーを終了させる
//				waitBeforeJunpAttack->EndTimer();
//			}
//			//許可されていたら
//			if (isJumpAttack)
//			{
//				//プレイヤーと自分の座標のベクトルの差を求める(目標までのベクトル)
//				targetPos = VSub(base.pos, jumpAttackTargetPos);
//				//そのベクトルの大きさを求める
//				vectorSize = VSize(targetPos);
//				//サイズが定数よりも小さくなったら
//				if (vectorSize <= 5)
//				{
//					//休憩フラグを立てる
//					isRestTime = true;
//					//攻撃フラグを下す
//					base.isAttack = false;
//				}
//				else
//				{
//					//目標までのベクトルを正規化する
//					normalizePos = VNorm(targetPos);
//					// もし攻撃中に正規化した値がーになっていたら正規化した値に移動スピードをかけて移動量を返す
//					outPutPos = VScale(normalizePos, status.AGI * -3);
//					//角度を変える
//					base.rotate = VGet(0.0f, (float)ChangeRotate(jumpAttackTargetPos), 0.0f);
//				}
//			}
//		}
//		else
//		{
//			/*回転攻撃*/
//			if (attackType == static_cast<int>(AnimationType::ROTATE_ATTACK))
//			{
//				//タイマーがスタートしていて、目標時間に達していたら
//				if (waitBeforeRotateAttack->getIsStartTimer() && waitBeforeRotateAttack->CountTimer())
//				{
//					//回転アタックを許可する
//					isRotateAttack = true;
//					//タイマーを終了させる
//					waitBeforeRotateAttack->EndTimer();
//				}
//				//許可されていたら
//				if (isRotateAttack)
//				{
//					//回転攻撃継続時間がスタートしていなかったら
//					if (!rotateAttackLoopTime->getIsStartTimer())
//					{
//						//タイマーをスタートする
//						rotateAttackLoopTime->StartTimer();
//					}
//					//スタートしていたら
//					else
//					{
//						//もしタイマーが目標時間に達したら
//						if (rotateAttackLoopTime->CountTimer())
//						{
//							//休憩フラグを立てる
//							isRestTime = true;
//							//攻撃フラグを下す
//							base.isAttack = false;
//						}
//					}
//				}
//				//プレイヤーと自分の座標のベクトルの差を求める(目標までのベクトル)
//				targetPos = VSub(base.pos, playerPos);
//				//そのベクトルの大きさを求める
//				vectorSize = VSize(targetPos);
//				//目標までのベクトルを正規化する
//				normalizePos = VNorm(targetPos);
//				outPutPos = VScale(normalizePos, status.AGI * -1);
//			}
//			//もし通常攻撃中かつアニメーション変更フラグがたったら
//			if (attackType == static_cast<int>(AnimationType::NORMAL_ATTACK) && anim->GetIsChangeAnim())
//			{
//				//休憩フラグを立てる
//				isRestTime = true;
//				//攻撃フラグを下す
//				base.isAttack = false;
//			}
//			//角度を変える
//			base.rotate = VGet(0.0f, (float)ChangeRotate(playerPos), 0.0f);
//
//		}
//	}
//	//休憩フラグが立っていて、タイマーがスタートしていなかったらスタートする
//	if (isRestTime && !restTimeAfterAttack->getIsStartTimer())
//	{
//		//タイマーをスタート
//		restTimeAfterAttack->StartTimer();
//		//アニメーションがジャンプアタックだったら
//		if (attackType == static_cast<int>(AnimationType::JUMP_ATTACK))
//		{
//			anim->SetAnim(static_cast<int>(AnimationType::JUMP_IDLE));
//		}
//		else
//		{
//			anim->SetAnim(static_cast<int>(AnimationType::IDLE));
//		}
//	}
//	//スタートしているなら
//	else
//	{
//		//もしタイマーが目標時間に達したら
//		if (restTimeAfterAttack->CountTimer())
//		{
//			isRestTime = false;
//			restTimeAfterAttack->EndTimer();
//		}
//	}
//
//	return outPutPos;
//}
///// <summary>
/////	角度の変更
///// </summary>
//float Boss::ChangeRotate(VECTOR playerPos)
//{
//	//2点間のベクトルを出す(エネミーからプレイヤー)
//	VECTOR EP_Vector = VSub(base.pos, playerPos);
//	return static_cast<float>(atan2(static_cast<double>(EP_Vector.x), static_cast<double>(EP_Vector.z)));
//}
//
/////// <summary>
/////// 球と球の当たり判定
/////// </summary>
/////// <param name="isAttack">攻撃しているかどうかの判定</param>
/////// <param name="playerAttackPos">攻撃時当たり判定座標</param>
/////// <param name="attackRadius">攻撃時当たり判定半径</param>
/////// <returns>当たったかどうか</returns>
////bool Boss::SphereAndSphere(bool isAttack, VECTOR playerAttackPos, float attackRadius)
////{
////	// 距離の計算(二つのベクトルを引いたベクトルを取得)
////	VECTOR playerToEnemy = VSub(playerAttackPos, base.pos);
////	// 上で求めたベクトルの大きさよりも、二つの半径を足したものが大きければ当たっていると判定
////	if (VSize(playerToEnemy) < attackRadius + RADIUS)
////	{
////		base.isHit = true;
////		return true;
////	}
////	return false;
////}