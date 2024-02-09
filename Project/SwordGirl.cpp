//===========================================================================
//@brief プレイヤークラス / 継承
//===========================================================================
#include"SwordGirl.h"
#include"Common.h"
#include"Timer.h"
#include"Animation.h"
#include"StatusManager.h"
#include"CharacterStatus.h"
#include"BloodParticle.h"
#include<math.h>
const VECTOR  SwordGirl::FIRST_MODEL_SCALE	= VGet(0.2f, 0.2f, 0.2f);//モデルの拡大率
const VECTOR  SwordGirl::FIRST_POS			= VGet(-50.0f, 0.0f, 0.0f);
const COLOR_F SwordGirl::CHANGE_DIF_COLOR	= GetColorF(1.0f, 0.0f, 0.0f, 1.0f);//ディフューズカラー
const COLOR_F SwordGirl::CHANGE_SPC_COLOR	= GetColorF(1.0f, 0.0f, 0.0f, 1.0f);//スペキュラカラー
const COLOR_F SwordGirl::CHANGE_EMI_COLOR	= GetColorF(1.0f, 0.0f, 0.0f, 1.0f);//エミッシブカラー
const COLOR_F SwordGirl::CHANGE_AMB_COLOR	= GetColorF(1.0f, 0.0f, 0.0f, 1.0f);//アンビエントカラー
const int SwordGirl::FONT_COLOR = GetColor(150, 150, 150);
/// <summary>
/// 引数ありコンストラクタ
/// </summary>
/// <param name="modelHandle">モデルハンドル</param>
SwordGirl::SwordGirl(const int _modelHandle, const int _frameImage, const int _hpImage, const int _expImage,const int _font)
	: PlayerBase(_modelHandle)
	, anim(nullptr)
	, stayTimer(nullptr)
	, invincibleTimer(nullptr)
	, isMove(false)
	, isChangeColor(false)
	, prevLv(0)
	, frameImage(_frameImage)
	, hpImage(_hpImage)
	, expImage(_expImage)
	, materialNum(0)
	, playerDir(ORIGIN_POS)
	, font(_font)
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
	nowHP.y = 30;
	prevHP.y = 30;
	prevHP.x = 300;
	nowEXP.y = 30;
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
	blood->UpdateGravity();
	if (isInvincible)
	{
		blood->Init(bloodBaseDir,pos);
	}
	if (status->GetHp() > 0)
	{
		//移動量を座標に足す
		pos = VAdd(pos, moveVec);
	}
	//ステージの範囲をもとに位置を補正する
	/*pos.y = PLAYETR_Y_POS;*/
	if (pos.x >= PLAYER_RANGE_OF_ACTION.LX)
	{
		pos.x = PLAYER_RANGE_OF_ACTION.LX;
	}
	if (pos.x <= PLAYER_RANGE_OF_ACTION.RX)
	{
		pos.x = PLAYER_RANGE_OF_ACTION.RX;
	}
	if (pos.z >= PLAYER_RANGE_OF_ACTION.LZ)
	{
		pos.z = PLAYER_RANGE_OF_ACTION.LZ;
	}
	if (pos.z <= PLAYER_RANGE_OF_ACTION.RZ)
	{
		pos.z = PLAYER_RANGE_OF_ACTION.RZ;
	}
	//体力の回復
	//status->CalcExp
	//死亡判定
	Death();
	//コリジョン情報を更新
	MV1RefreshCollInfo(modelHandle, PLAYER_COLL_INFO.frameIndex);
	//モデルの設定
	MV1SetRotationXYZ(modelHandle, rotate);
	MV1SetPosition(modelHandle, pos);
	blood->Update(15);
	ChangeColor();//モデルの色を変える
	//アニメーションの再生
	anim->Play(&modelHandle);
}
/// <summary>
/// ステータス更新
/// </summary>
void SwordGirl::StatusUpdate(const VECTOR _bonfirePos)
{
	VECTOR fireToPlayer = VSub(_bonfirePos,pos);
	float vecSize = VSize(fireToPlayer);
	bool isShowMenu = false;
	if(vecSize < 30.0f)
	{
		isShowMenu = true;
	}
	status->Update(isShowMenu);
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
/// 色の変更
/// </summary>
void SwordGirl::ChangeColor()
{
	if (isInvincible)
	{
		if (!isChangeColor)
		{
			//マテリアルの数を取得
			materialNum = MV1GetMaterialNum(modelHandle);
			//既存のマテリアルを保存しておく
			for (int i = 0; i < materialNum; i++)
			{
				difColorInfo.push_back(MV1GetMaterialDifColor(modelHandle, i));
				spcColorInfo.push_back(MV1GetMaterialSpcColor(modelHandle, i));
				emiColorInfo.push_back(MV1GetMaterialEmiColor(modelHandle, i));
				ambColorInfo.push_back(MV1GetMaterialAmbColor(modelHandle, i));
			}
			//赤色になるようにマテリアルの色をいじる
			for (int i = 0; i < materialNum; i++)
			{
				MV1SetMaterialDifColor(modelHandle, i, CHANGE_DIF_COLOR);
				MV1SetMaterialSpcColor(modelHandle, i, CHANGE_SPC_COLOR);
				MV1SetMaterialEmiColor(modelHandle, i, CHANGE_EMI_COLOR);
				MV1SetMaterialAmbColor(modelHandle, i, CHANGE_AMB_COLOR);
			}
			//色変更フラグを立てる
			isChangeColor = true;
		}
	}
	else
	{
		//色を変更していたら
		if (isChangeColor)
		{
			//マテリアルの色をもとに戻す
			for (int i = 0; i < materialNum; i++)
			{
				MV1SetMaterialDifColor(modelHandle, i, difColorInfo[i]);
				MV1SetMaterialSpcColor(modelHandle, i, spcColorInfo[i]);
				MV1SetMaterialEmiColor(modelHandle, i, emiColorInfo[i]);
				MV1SetMaterialAmbColor(modelHandle, i, ambColorInfo[i]);
			}
			//ベクターの要素を０にする
			difColorInfo.clear();
			spcColorInfo.clear();
			emiColorInfo.clear();
			ambColorInfo.clear();
			//フラグを下す
			isChangeColor = false;
		}
	}
}
/// <summary>
/// 移動
/// </summary>
void SwordGirl::Move(const VECTOR _cameraToPlayer)
{
	if (status->GetHp() > 0)
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
				playerDir = VNorm(playerDir);
			}
			else
			{
				isMove = false;
			}
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
/// <summary>
/// UIの更新
/// </summary>
void SwordGirl::UpdateUI()
{
	//最大HPを求める
	//現在のHPを求める
	//指数化する（式：現在のHP/最大HP * 100）
	nowHP.x = static_cast<int>(status->GetHp()/ status->GetMaxHP() * 300.0f);
	nowEXP.x = static_cast<int>(status->GetExp() / status->GetNeedExp() * 300.0f);
	if (nowHP.x < 0)
	{
		nowHP.x = 0;
	}

}
/// <summary>
/// UIの描画
/// </summary>
void SwordGirl::DrawUI()
{
	//テキストの表示
	DrawFormatStringToHandle(25, 20, FONT_COLOR, font, "LV %d", static_cast<int>(status->GetLv()));
	DrawStringToHandle(20, 60, "HP", FONT_COLOR, font);
	DrawStringToHandle(20, 100, "EXP", FONT_COLOR, font);
	//フレームの描画
	DrawExtendGraph(static_cast<int>(HP_FRAME_POS.LX),  static_cast<int>(HP_FRAME_POS.LZ),  static_cast<int>(HP_FRAME_POS.RX),  static_cast<int>(HP_FRAME_POS.RZ),  frameImage, TRUE);
	DrawExtendGraph(static_cast<int>(EXP_FRAME_POS.LX), static_cast<int>(EXP_FRAME_POS.LZ), static_cast<int>(EXP_FRAME_POS.RX), static_cast<int>(EXP_FRAME_POS.RZ), frameImage, TRUE);
	//HPバーの表示
	DrawExtendGraph(HP_BAR_POS.x, HP_BAR_POS.y, HP_BAR_POS.x + nowHP.x, HP_BAR_POS.y + nowHP.y, hpImage, TRUE);
	DrawExtendGraph(EXP_BAR_POS.x, EXP_BAR_POS.y, EXP_BAR_POS.x + nowEXP.x, EXP_BAR_POS.y + nowEXP.y, expImage, TRUE);
}
void SwordGirl::ReSpawn()
{
	pos = ORIGIN_POS;
	status->PhysicalRecovery();
	isDeath = false;
}
void SwordGirl::PhysicalRecovery()
{
	status->PhysicalRecovery();
}
const int SwordGirl::GetAtkUpCount()const
{
	return status->GetAtkUpCount();
}
const int SwordGirl::GetAgiUpCount()const
{
	return status->GetAgiUpCount();
}
const int SwordGirl::GetDefUpCount()const
{
	return status->GetDefUpCount();
}
const bool SwordGirl::GetIsBonfireMenu()const
{
	return status->GetIsBonfireMenu();
}
