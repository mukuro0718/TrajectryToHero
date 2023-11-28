//===========================================================================
//@brief プレイヤークラス / 継承
//===========================================================================
#include"SwordGirl.h"
#include"Common.h"
#include"Timer.h"
#include"Animation.h"
#include"StatusManager.h"
#include"CharacterStatus.h"
#include<math.h>
const VECTOR SwordGirl::FIRST_MODEL_SCALE	= VGet(0.2f, 0.2f, 0.2f);//モデルの拡大率
const VECTOR SwordGirl::FIRST_POS = VGet(-50.0f, 0.0f, 0.0f);

/// <summary>
/// 引数ありコンストラクタ
/// </summary>
/// <param name="modelHandle">モデルハンドル</param>
SwordGirl::SwordGirl(const int _modelHandle)
	: PlayerBase(_modelHandle)
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
	anim->Add(MV1LoadModel("Data/Animation/Player_RunAnim.mv1"), 0);			//走りアニメーション
	anim->Add(MV1LoadModel("Data/Animation/Player_StrongAttackAnim.mv1"), 0);	//攻撃アニメーション
	anim->Add(MV1LoadModel("Data/Animation/Player_StayIdleAnim.mv1"), 0);		//待機アニメーション
	anim->Add(MV1LoadModel("Data/Animation/1_DeathAnim_public.mv1"), 0);		//死亡アニメーション
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
	anim			= NULL;
	stayTimer		= NULL;
	invincibleTimer = NULL;
	anim			= new Animation();
	stayTimer		= new Timer();
	invincibleTimer = new Timer();
}
/// <summary>
/// 初期化
/// </summary>
void SwordGirl::Init()
{
	stayTimer->Init(STAY_TIMER_TARGET_TIME);
	invincibleTimer->Init(INVINCIBLE_TIMER_TARGET_TIME);
	pos		= ORIGIN_POS;
	rotate		= ORIGIN_POS;
	scale		= FIRST_MODEL_SCALE;
	status->InitPlayerStatus();
	prevLv = static_cast<int>(status->GetLv());
	isMove = false;//移動しているかどうか

}

/// <summary>
/// 更新
/// </summary>
/// <param name="cameraToPlayer">カメラからプレイヤーの向きベクトル</param>
void SwordGirl::Update()
{
	//コリジョン情報を更新
	MV1RefreshCollInfo(modelHandle, PLAYER_COLL_INFO.frameIndex);
	//モデルの設定
	MV1SetRotationXYZ(modelHandle, rotate);
	MV1SetPosition(modelHandle, pos);
	//アニメーションの再生
	anim->Play(&modelHandle);
}
void SwordGirl::Move(const VECTOR cameraToPlayer)
{
	/////////////////////////////////////////////////////////
	// 回転と移動
	/////////////////////////////////////////////////////////
	// 攻撃をしていなかったら
	if (!isAttack)
	{
		//左スティックの傾きを取得
		GetJoypadAnalogInput(&inputLeftStick.XBuf, &inputLeftStick.YBuf, DX_INPUT_KEY_PAD1);
		//アナログスティックの傾きをベクトルに入れる
		//const VECTOR stickDirection = VGet((float)-inputLeftStick.XBuf, 0.0f, (float)inputLeftStick.YBuf);
		VECTOR stickDirection = ORIGIN_POS;
		stickDirection.x = static_cast<float>(-inputLeftStick.XBuf);
		stickDirection.z = static_cast<float>(inputLeftStick.YBuf);
		//スティック入力があればこの後の処理を行う
		if (inputLeftStick.YBuf != NONE_INPUT_VALUE.XBuf || inputLeftStick.XBuf != NONE_INPUT_VALUE.YBuf)
		{
			isMove = true;
			//正規化する
			const VECTOR stickDirectionNormalize = VNorm(stickDirection);
			//モデル角度の計算
			rotate.y = (-atan2(cameraToPlayer.z, cameraToPlayer.x) - atan2(stickDirectionNormalize.z, stickDirectionNormalize.x)) - 180.0f * DX_PI_F / 180.0f;
			//座標計算
			pos.x += -sinf(rotate.y) * status->GetAgi();
			pos.z += -cosf(rotate.y) * status->GetAgi();
		}
		else
		{
			isMove = false;
		}
		pos.y = PLAYETR_Y_POS;
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
			anim->SetAnim(static_cast<int>(AnimationType::ATTACK));
			isAttack = true;
		}
		else
		{
			isMove = false;
		}
	}
	//攻撃アニメーションが終了したらフラグを下す
	else if (isAttack && anim->GetPlayTime() == FIRST_ANIM_PLAY_TIME)
	{
		isAttack = false;
	}
}

void SwordGirl::AnimChange()
{
	/////////////////////////////////////////////////////////
	// アニメーションの変化
	/////////////////////////////////////////////////////////
	//移動していたら
	if (isMove && !isAttack)
	{
		anim->SetAnim(static_cast<int>(AnimationType::RUN));
	}
	//待機中だったら
	else if (!isMove && !isAttack)
	{
		anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	}
	//HPが０だったら
	if (status->GetHp() < 0)
	{
		anim->SetAnim(static_cast<int>(AnimationType::DEATH));
	}

}