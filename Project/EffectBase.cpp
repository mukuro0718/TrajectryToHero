//===========================================================================
//@brief エフェクトベースクラス
// 各エフェクトクラス必要な関数の定義を行う
//===========================================================================
#include"EffectBase.h"
/// <summary>
/// コンストラクタ
/// </summary>
EffectBase::EffectBase(int _modelHandle)
{
	modelHandle = 0;
	modelHandle = MV1DuplicateModel(_modelHandle);
}
/// <summary>
/// デストラクタ
/// </summary>
EffectBase::~EffectBase()
{
	Delete();
}
/// <summary>
/// 描画
/// </summary>
void EffectBase::Draw()
{
	MV1DrawModel(modelHandle);
}
/// <summary>
/// 削除
/// </summary>
void EffectBase::Delete()
{
	MV1DeleteModel(modelHandle);
}