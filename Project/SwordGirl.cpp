//===========================================================================
//@brief プレイヤークラス / 継承
//===========================================================================
#include"SwordGirl.h"
#include"Common.h"
#include"Timer.h"
#include"Animation.h"
#include"StatusManager.h"
#include"CharacterStatus.h"
#include"BlurScreen.h"
#include<math.h>
const VECTOR SwordGirl::FIRST_MODEL_SCALE	= VGet(0.2f, 0.2f, 0.2f);//モデルの拡大率
const VECTOR SwordGirl::FIRST_POS = VGet(-50.0f, 0.0f, 0.0f);

/// <summary>
/// 引数ありコンストラクタ
/// </summary>
/// <param name="modelHandle">モデルハンドル</param>
SwordGirl::SwordGirl(const int _modelHandle)
	: PlayerBase(_modelHandle)
	, anim(nullptr)
	, stayTimer(nullptr)
	, invincibleTimer(nullptr)
	, isMove(false)
{
	//生成
	Create();
	//初期化
	Init();
	//スケールのセット
	MV1SetScale(modelHandle, scale);
	//回転値のセット
	MV1SetRotationXYZ(modelHandle, rotate);
	//コリジョン情報を構築
	MV1SetupCollInfo(modelHandle, PLAYER_COLL_INFO.frameIndex, PLAYER_COLL_INFO.xDivNum, PLAYER_COLL_INFO.yDivNum, PLAYER_COLL_INFO.zDivNum);
	//アニメーションの追加
	anim->Add(MV1LoadModel("Data/Animation/Player/RunAnim.mv1"), 3);			//走りアニメーション
	anim->Add(MV1LoadModel("Data/Animation/Player/AttackAnim.mv1"), 3);	//攻撃アニメーション
	anim->Add(MV1LoadModel("Data/Animation/Player/IdleAnim.mv1"), 3);		//待機アニメーション
	anim->Add(MV1LoadModel("Data/Animation/Player/DeathAnim.mv1"), 3);		//死亡アニメーション
	//アタッチするアニメーション
	anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	//アニメーションのアタッチ
	anim->Attach(&modelHandle);
}
/// <summary>
/// デストラクタ
/// </summary>
SwordGirl::~SwordGirl()
{
}
/// <summary>
/// 生成
/// </summary>
void SwordGirl::Create()
{
	anim			= new Animation();
	stayTimer		= new Timer();
	invincibleTimer = new Timer();
	scale = FIRST_MODEL_SCALE;
}
/// <summary>
/// 初期化
/// </summary>
void SwordGirl::Init()
{
	stayTimer->Init(STAY_TIMER_TARGET_TIME);
	invincibleTimer->Init(INVINCIBLE_TIMER_TARGET_TIME);
	status->InitPlayerStatus();
	prevLv = static_cast<int>(status->GetLv());
}
/// <summary>
/// 移動量の補正
/// </summary>
void SwordGirl::FixMoveVec(const VECTOR _fixVec)
{
	//移動量を補正する
	moveVec = VAdd(moveVec, _fixVec);
}
/// <summary>
/// 更新
/// </summary>
void SwordGirl::Update()
{
	//移動量を座標に足す
	pos = VAdd(pos, moveVec);
	//ステージの範囲をもとに位置を補正する
	/*pos.y = PLAYETR_Y_POS;*/
	if (pos.x >= PLAYER_RANGE_OF_ACTION.LX)
	{
		pos.x = PLAYER_RANGE_OF_ACTION.LX;
	}
	if (pos.x <= PLAYER_RANGE_OF_ACTION.LZ)
	{
		pos.x = PLAYER_RANGE_OF_ACTION.LZ;
	}
	if (pos.z >= PLAYER_RANGE_OF_ACTION.RX)
	{
		pos.z = PLAYER_RANGE_OF_ACTION.RX;
	}
	if (pos.z <= PLAYER_RANGE_OF_ACTION.RZ)
	{
		pos.z = PLAYER_RANGE_OF_ACTION.RZ;
	}
	//clsDx();
	//printfDx("HP:%f", status->GetHp());
	Death();
	//コリジョン情報を更新
	MV1RefreshCollInfo(modelHandle, PLAYER_COLL_INFO.frameIndex);
	//モデルの設定
	MV1SetRotationXYZ(modelHandle, rotate);
	MV1SetPosition(modelHandle, pos);
	//アニメーションの再生
	anim->Play(&modelHandle);
}
/// <summary>
/// ステータス更新
/// </summary>
void SwordGirl::StatusUpdate()
{
	status->Update();
	status->ShowInfo();
}
/// <summary>
/// 無敵フラグの計測
/// </summary>
void SwordGirl::CountInvincibleTimer()
{
	//無敵フラグが立っていたら
	if (isInvincible)
	{
		//まだタイマーが始まっていなかったら
		if (!invincibleTimer->getIsStartTimer())
		{
			invincibleTimer->StartTimer();
		}
		if (invincibleTimer->CountTimer())
		{
			isInvincible = false;
			invincibleTimer->EndTimer();
		}
	}
}
/// <summary>
/// 移動
/// </summary>
void SwordGirl::Move(const VECTOR _cameraToPlayer)
{
	cameraToPlayer = _cameraToPlayer;
	moveVec = ORIGIN_POS;
	/////////////////////////////////////////////////////////
	// 回転と移動
	/////////////////////////////////////////////////////////
	// 攻撃をしていなかったら
	if (!isAttack)
	{
		//左スティックの傾きを取得
		GetJoypadAnalogInput(&inputLeftStick.XBuf, &inputLeftStick.YBuf, DX_INPUT_KEY_PAD1);
		//変数に入れる
		VECTOR stickDirection = ORIGIN_POS;
		stickDirection.x = static_cast<float>(-inputLeftStick.XBuf);
		stickDirection.z = static_cast<float>(inputLeftStick.YBuf);
		//スティック入力があればこの後の処理を行う
		if (inputLeftStick.YBuf != NONE_INPUT_VALUE.XBuf || inputLeftStick.XBuf != NONE_INPUT_VALUE.YBuf)
		{
			//ムーブフラグを立てる
			isMove = true;
			//正規化する
			const VECTOR stickDirectionNormalize = VNorm(stickDirection);
			//モデル角度の計算
			rotate.y = (-atan2(cameraToPlayer.z, cameraToPlayer.x) - atan2(stickDirectionNormalize.z, stickDirectionNormalize.x)) - DX_PI_F;
			//座標計算
			moveVec.x += -sinf(rotate.y) * status->GetAgi();
			moveVec.z += -cosf(rotate.y) * status->GetAgi();
		}
		else
		{
			isMove = false;
		}
	}
}

/// <summary>
/// 攻撃
/// </summary>
/// <param name="_isAttack">攻撃をしているか</param>
void SwordGirl::Attack()
{
	//攻撃をしていない
	if (!isAttack)
	{
		int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		//Bが押されていたら攻撃
		if (input & PAD_INPUT_3)
		{
			isAttack = true;
		}
	}
	//攻撃アニメーションが終了したらフラグを下す
	else if (isAttack && anim->GetPlayTime() == FIRST_ANIM_PLAY_TIME)
	{
		isAttack = false;
	}
}
/// <summary>
/// 死亡判定
/// </summary>
void SwordGirl::Death()
{
	//死亡アニメーションが終了したら
	if (anim->GetAnim() == static_cast<int>(AnimationType::DEATH))
	{
		if (anim->GetPlayTime() == 0.0f)
		{
			isDeath = true;
		}
	}
}
/// <summary>
/// アニメーションの変更
/// </summary>
void SwordGirl::AnimChange()
{
	/////////////////////////////////////////////////////////
	// アニメーションの変化
	/////////////////////////////////////////////////////////
	//移動していたら
	if (isAttack)
	{
		anim->SetAnim(static_cast<int>(AnimationType::ATTACK));
	}
	else if (isMove && !isAttack)
	{
		anim->SetAnim(static_cast<int>(AnimationType::RUN));
	}
	//待機中だったら
	else if (!isMove && !isAttack)
	{
		anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	}
	//HPが０だったら
	if (status->GetHp() <= 0)
	{
		anim->SetAnim(static_cast<int>(AnimationType::DEATH));
	}
}
/// <summary>
/// メニューの描画
/// </summary>
void SwordGirl::DrawMenu()
{
	status->Draw();
}
/// <summary>
/// ステータスクラスのisShowMenuを返す
/// </summary>
/// <returns></returns>
const bool SwordGirl::GetIsShowStatusMenu()
{
	return status->GetIsShowMenu();
}