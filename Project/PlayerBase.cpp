//===========================================================================
//@brief オブジェクトベースクラス / 基底
//===========================================================================
#include"PlayerBase.h"
#include"CharacterStatus.h"
#include"math.h"
#include"Timer.h"
#include"SwordTrail.h"
#include"BloodParticle.h"
#include"StatusUI.h"
#include"Load.h"
const int	 PlayerBase::CAPSULE_COLOR		= GetColor(255, 0, 0);
const int	 PlayerBase::SPHERE_COLOR		= GetColor(200, 0, 0);
const VECTOR PlayerBase::SPHERE_POS_OFFSET	= VGet(-10.0f,30.0f,0.0f);
const VECTOR PlayerBase::CENTER_POS_OFFSET	= VGet(0.0f, 20.0f, 0.0f);
/// <summary>
/// 引数ありコンストラクタ
/// </summary>
/// <param name="modelHandle">プレイヤーモデルハンドル</param>
PlayerBase::PlayerBase(const int _modelHandle)
	: status(nullptr)
	, attackLatency(nullptr)
	, swordTrail(nullptr)
	, blood(nullptr)
	, statusUI(nullptr)
	, cameraToPlayer(ORIGIN_POS)
	, degrees(INIT_DEGREES)
	, centerPos(ORIGIN_POS)
	, bloodBaseDir(ORIGIN_POS)
{
	int bloodParticle = 0;
	auto& load = Load::GetInstance();
	load.GetPlayerParticleData(&bloodParticle);
	blood		  = new BloodParticle(bloodParticle);
	status		  = new CharacterStatus();
	statusUI	  = new StatusUI();
	swordTrail	  = new SwordTrail();
	attackLatency = new Timer();
	attackLatency->Init(5);
	//モデルのロード
	modelHandle = MV1DuplicateModel(_modelHandle);
	if (modelHandle < INIT_MODELHANDLE)
	{
		printfDx("Playerデータ読み込みに失敗");
	}
	SetUpCapsule(pos, CAPSULE_HEIGHT, CAPSULE_RADIUS, CAPSULE_COLOR, false);
	SetUpSphere(pos, SPHERE_RADIUS, SPHERE_COLOR, false);
}
/// <summary>
/// デストラクタ
/// </summary>
PlayerBase::~PlayerBase()
{
	Delete();
}
/// <summary>
/// 描画
/// </summary>
void PlayerBase::Draw()
{
	if (!isDeath)
	{
		// ３Ｄモデルの描画
		MV1DrawModel(modelHandle);
	}
	if (status->GetHp() > 0)
	{
		blood->Draw();
	}
	SetUpCapsule(pos, CAPSULE_HEIGHT, CAPSULE_RADIUS, CAPSULE_COLOR, false);
	VECTOR swordTopPos = MV1GetFramePosition(modelHandle, 67);
#ifdef _DEBUG
	//DrawCapsule(capsuleInfo);
	////VECTOR swordTopPos = MV1GetFramePosition(modelHandle, 69);
	//DrawSphere3D(swordTopPos, 2.0f, 16, SPHERE_COLOR, SPHERE_COLOR, false);
#endif // _DEBUG
	//攻撃中であれば当たり判定用スフィアを描画する
	if (isAttack)
	{
		if (!swordTrail->GetIsStartTimer())
		{
			swordTrail->StartTimer();
		}
		if (!attackLatency->getIsStartTimer())
		{
			attackLatency->StartTimer();
		}
		if (attackLatency->CountTimer())
		{
			VECTOR spherePos = pos;

			spherePos.x += -sinf(rotate.y) * 15.0f;
			spherePos.z += -cosf(rotate.y) * 15.0f;
			spherePos.y = 30.0f;
			//スフィア情報の構築
			SetUpSphere(spherePos, SPHERE_RADIUS, SPHERE_COLOR, false);
#ifdef _DEBUG
			////スフィアの描画
			//DrawSphere(sphereInfo);
#endif
		}
	}
	else
	{
		attackLatency->EndTimer();
	}
	
	statusUI->Draw(status->GetAtkUpCount(), status->GetDefUpCount(), status->GetAgiUpCount());
	swordTrail->Update(MV1GetFramePosition(modelHandle, 69), MV1GetFramePosition(modelHandle, 67));
	swordTrail->Draw();
}
/// <summary>
/// 最終処理
/// </summary>
void PlayerBase::Delete()
{
	// モデルのアンロード.
	MV1DeleteModel(modelHandle);
}
/// <summary>
/// HP計算
/// </summary>
void PlayerBase::CalcHP(const float _atk, const VECTOR _attackerPos)
{
	bloodBaseDir = VSub(pos, _attackerPos);
	//HP計算
	status->CalcHP(_atk);
	isInvincible = true;
}
/// <summary>
/// レベルアップ処理
/// </summary>
void PlayerBase::CalcExp(const float _expToGive)
{
	status->CalcExp(_expToGive);
}
const float PlayerBase::GetAtk()
{
	return status->GetAtk();
}
const float PlayerBase::GetHp()
{
	return status->GetHp();
}
const float PlayerBase::GetLv()
{
	return status->GetLv();
}
void PlayerBase::TutorialStatusReset()
{
	status->TutorialStatusReset();
}