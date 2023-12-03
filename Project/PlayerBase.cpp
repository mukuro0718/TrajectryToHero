//===========================================================================
//@brief オブジェクトベースクラス / 基底
//===========================================================================
#include"PlayerBase.h"
#include"CharacterStatus.h"
#include"math.h"
const int PlayerBase::CAPSULE_COLOR = GetColor(255, 0, 0);
const int PlayerBase::SPHERE_COLOR = GetColor(200, 0, 0);
/// <summary>
/// 引数ありコンストラクタ
/// </summary>
/// <param name="modelHandle">プレイヤーモデルハンドル</param>
PlayerBase::PlayerBase(const int _modelHandle)
	:status(nullptr)
	, cameraToPlayer(ORIGIN_POS)
{
	status = new CharacterStatus();
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
#ifdef _DEBUG
	SetUpCapsule(pos, CAPSULE_HEIGHT, CAPSULE_RADIUS, CAPSULE_COLOR,false);
	DrawCapsule(capsuleInfo);
	VECTOR swordPos = MV1GetFramePosition(modelHandle, 47);
	//swordPos.y += 5.0f;
	//swordPos.x += -sinf(rotate.y) * 18.0f;
	//swordPos.z += -cosf(rotate.y) * 18.0f;
	SetUpSphere(swordPos , SPHERE_RADIUS, SPHERE_COLOR, false);
	DrawSphere(sphereInfo);
#endif // _DEBUG

	// ３Ｄモデルの描画
	MV1DrawModel(modelHandle);
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