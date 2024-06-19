//===========================================================================
//@brief 地面クラス/継承
//===========================================================================
#include"FarmStage.h"
#include"Common.h"
const VECTOR FarmStage::SCALE = VGet(0.3f, 0.3f, 0.3f);
const VECTOR FarmStage::INIT_STAGE_POS = VGet(0.0f, 0.0f, -150.0f);
/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="humanModelHandle">モデルハンドル</param>
FarmStage::FarmStage(std::vector<int> _data)
	:portalRotate(0.0f)
	,isShowGate(false)
{
	//モデルのロード
	for (int i = 0; i < MODEL_NUM; i++)
	{
		model.push_back(MV1DuplicateModel(_data[i]));
	}
	Init();
}
const void FarmStage::Init()
{
	//座標の初期化
	for (int i = 0; i < MODEL_NUM; i++)
	{
		rotate.push_back(ORIGIN_POS);
		scale.push_back(SCALE);
		pos.push_back(INIT_STAGE_POS);
	}

	//座標のセット
	pos[static_cast<int>(FARM::GATE)] = VGet(0.0f, -20.0f, 500.0f);
	pos[static_cast<int>(FARM::PORTAL)] = VGet(0.0f, 40.0f, 550.0f);
	for (int i = 0; i < MODEL_NUM; i++)
	{
		MV1SetPosition(model[i], pos[i]);
		MV1SetRotationXYZ(model[i], rotate[i]);
		MV1SetScale(model[i], scale[i]);
	}

}
/// <summary>
/// デストラクタ
/// </summary>
FarmStage::~FarmStage()
{
	Delete();
}
/// <summary>
/// 最終処理
/// </summary>
const void FarmStage::Delete()
{
	pos.clear();
	model.clear();
	// モデルのアンロード.
	//MV1DeleteModel(model[static_cast<int>(FARM::GROUND)]);
	//MV1DeleteModel(model[static_cast<int>(FARM::GATE)]);
	//MV1DeleteModel(model[static_cast<int>(FARM::PORTAL)]);
}
/// <summary>
/// 描画
/// </summary>
const void FarmStage::Update(const int _playerLv)
{
	if (_playerLv > 5)
	{
		isShowGate = true;
	}
	portalRotate += 1.0f;
	rotate[static_cast<int>(FARM::PORTAL)] = VGet( 0.0f, 0.0f,portalRotate * (DX_PI_F / 180.0f));
	MV1SetRotationXYZ(model[static_cast<int>(FARM::PORTAL)], rotate[static_cast<int>(FARM::PORTAL)]);
}
/// <summary>
/// 描画
/// </summary>
const void FarmStage::Draw(const bool _isFarm)
{
	MV1DrawModel(model[static_cast<int>(FARM::GROUND)]);
	if (_isFarm)
	{
		if (isShowGate)
		{
			MV1DrawModel(model[static_cast<int>(FARM::GATE)]);
			MV1DrawModel(model[static_cast<int>(FARM::PORTAL)]);
		}
	}
}

