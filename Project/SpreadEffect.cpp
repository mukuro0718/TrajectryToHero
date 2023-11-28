//===========================================================================
//@brief 拡散するエフェクトクラス
// エフェクトの初期化と位置更新と描画を行う
//===========================================================================
#include"SpreadEffect.h"
#include"Common.h"

const int SpreadEffect::SPHERE_COLOR = GetColor(255, 0, 0);
constexpr VECTOR SpreadEffect::SPHERE_SCALE = VGet(0.01f, 0.01f, 0.01f);
/// <summary>
/// コンストラクタ
/// </summary>
SpreadEffect::SpreadEffect(int _modelHandle):EffectBase(_modelHandle)
{
	initPos = ORIGIN_POS;
	//スケールのセット
	MV1SetScale(_modelHandle, SPHERE_SCALE);
}
/// <summary>
/// デストラクタ
/// </summary>
SpreadEffect::~SpreadEffect()
{

}
/// <summary>
/// 初期化
/// </summary>
void SpreadEffect::Init(VECTOR _pos, VECTOR _direction)
{
	pos = _pos;
	direction = _direction;
}
/// <summary>
/// 初期化
/// </summary>
void SpreadEffect::Update()
{
	pos = VAdd(pos, direction);
	MV1SetPosition(modelHandle,pos);
}
