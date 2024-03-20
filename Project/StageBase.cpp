#include"StageBase.h"
#include"Common.h"
const VECTOR StageBase::SCALE = VGet(0.3f, 0.2f, 0.3f);
const VECTOR StageBase::INIT_STAGE_POS = VGet(0.0f,0.0f,-150.0f);
/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="humanModelHandle">モデルハンドル</param>
StageBase::StageBase(std::vector<int> _data)
{
	//モデルのロード
	model.push_back(MV1DuplicateModel(_data[static_cast<int>(FARM::GROUND)]));
	model.push_back(MV1DuplicateModel(_data[static_cast<int>(FARM::VILLAGE)]));
	model.push_back(MV1DuplicateModel(_data[static_cast<int>(FARM::GATE)]));
	model.push_back(MV1DuplicateModel(_data[static_cast<int>(FARM::PORTAL)]));
	//モデルの拡大率の大きさ
	MV1SetScale(model[static_cast<int>(FARM::GROUND)], SCALE);
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
const void StageBase::Delete()
{
	// モデルのアンロード.
	MV1DeleteModel(model[static_cast<int>(FARM::GROUND)]);
}
/// <summary>
/// 描画
/// </summary>
const void StageBase::Update()
{
	MV1SetPosition(model[static_cast<int>(FARM::GROUND)], pos);
}
/// <summary>
/// 描画
/// </summary>
const void StageBase::Draw()
{
	MV1DrawModel(model[static_cast<int>(FARM::GROUND)]);
}

