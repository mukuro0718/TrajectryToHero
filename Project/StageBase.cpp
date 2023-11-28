#include"StageBase.h"
#include"Common.h"
const VECTOR StageBase::SCALE = VGet(0.3f, 0.2f, 0.3f);
const VECTOR StageBase::INIT_STAGE_POS = VGet(0.0f,-9.0f,-150.0f);
/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="humanModelHandle">モデルハンドル</param>
StageBase::StageBase(int _modelHandle)
{
	//モデルハンドルの初期化
	modelHandle = 0;
	//モデルのロード
	modelHandle = MV1DuplicateModel(_modelHandle);
	if (modelHandle < 0)
	{
		printfDx("stageデータ読み込みに失敗");
	}
	//モデルの拡大率の大きさ
	MV1SetScale(modelHandle, SCALE);
	//座標の初期化
	pos = INIT_STAGE_POS;
}
/// <summary>
/// デストラクタ
/// </summary>
StageBase::~StageBase()
{
	Delete();
}
/// <summary>
/// 最終処理
/// </summary>
void StageBase::Delete()
{
	// モデルのアンロード.
	MV1DeleteModel(modelHandle);
}
/// <summary>
/// 描画
/// </summary>
void StageBase::Update()
{
	MV1SetPosition(modelHandle, pos);
}
/// <summary>
/// 描画
/// </summary>
void StageBase::Draw()
{
	MV1DrawModel(modelHandle);
}

