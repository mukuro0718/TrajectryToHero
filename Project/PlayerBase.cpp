//===========================================================================
//@brief オブジェクトベースクラス / 基底
//===========================================================================
#include"PlayerBase.h"
#include"CharacterStatus.h"
#include"math.h"
#include"Timer.h"
const int PlayerBase::CAPSULE_COLOR = GetColor(255, 0, 0);
const int PlayerBase::SPHERE_COLOR = GetColor(200, 0, 0);
const VECTOR PlayerBase::SPHERE_POS_OFFSET = VGet(-10.0f,30.0f,0.0f);
const VECTOR PlayerBase::CENTER_POS_OFFSET = VGet(0.0f, 20.0f, 0.0f);
/// <summary>
/// 引数ありコンストラクタ
/// </summary>
/// <param name="modelHandle">プレイヤーモデルハンドル</param>
PlayerBase::PlayerBase(const int _modelHandle)
	:status(nullptr)
	,attackLatency(nullptr)
	, cameraToPlayer(ORIGIN_POS)
	, degrees(INIT_DEGREES)
	, centerPos(ORIGIN_POS)
{
	status = new CharacterStatus();
	attackLatency = new Timer();
	attackLatency->Init(5);
	//モデルのロード
	modelHandle = MV1DuplicateModel(_modelHandle);
	if (modelHandle < INIT_MODELHANDLE)
	{
		printfDx("Playerデータ読み込みに失敗");
	}
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
	// ３Ｄモデルの描画
	MV1DrawModel(modelHandle);
#ifdef _DEBUG
	SetUpCapsule(pos, CAPSULE_HEIGHT, CAPSULE_RADIUS, CAPSULE_COLOR,false);
	DrawCapsule(capsuleInfo);

	
	//攻撃中であれば当たり判定用スフィアを描画する
	if (isAttack)
	{
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
			//スフィアの描画
			DrawSphere(sphereInfo);
		}
	}
	else
	{
		attackLatency->EndTimer();
	}
#endif // _DEBUG

	
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
/// レベルアップメニューが表示されていたらほかの更新処理を止める
/// </summary>
/// <returns>true/false</returns>
//bool PlayerBase::IsStoppingUpdate()
//{
//	if (statusManager->GetIsShowMenu())
//	{
//		return true;
//	}
//	return false;
//}
/// <summary>
/// HP計算
/// </summary>
void PlayerBase::CalcHP( const float _atk)
{
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