//===========================================================================
//@brief オブジェクトベースクラス / 基底
//===========================================================================
#include"PlayerBase.h"
#include"CharacterStatus.h"

const int PlayerBase::CAPSULE_COLOR = GetColor(255, 0, 0);

/// <summary>
/// 引数ありコンストラクタ
/// </summary>
/// <param name="modelHandle">プレイヤーモデルハンドル</param>
PlayerBase::PlayerBase(const int _modelHandle)
{
	status = NULL;
	status = new CharacterStatus();
	modelHandle = INIT_MODELHANDLE;	//モデルハンドルの初期化
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