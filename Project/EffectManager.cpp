//===========================================================================
//@brief エフェクト管理クラス
// エフェクトの管理と関数の実行を行う
//===========================================================================
#include"EffectManager.h"
#include"SpreadEffect.h"
#include"Common.h"
const VECTOR EffectManager::DIRECTION[DIRECTION_NUM] =
{
	{VGet( 0.9f, 0.0f, 0.0f) },//X+
	{VGet( 0.6f, 0.6f, 0.0f) },//X+ Y+
	{VGet( 0.6f,-0.6f, 0.0f) },//X+ Y-
	{VGet( 0.6f, 0.0f, 0.6f) },//X+ Z+
	{VGet( 0.6f, 0.0f,-0.6f) },//X+ Z-
	{VGet( 0.6f, 0.6f, 0.6f) },//X+ Y+ Z+
	{VGet( 0.6f, 0.6f,-0.6f) },//X+ Y+ Z-
	{VGet( 0.6f,-0.6f, 0.6f) },//X+ Y- Z+
	{VGet( 0.6f,-0.6f,-0.6f) },//X+ Y- Z-
	
	{VGet(-0.9f, 0.0f, 0.0f) },//X-
	{VGet(-0.6f, 0.6f, 0.0f) },//X- Y+
	{VGet(-0.6f,-0.6f, 0.0f) },//X- Y-
	{VGet(-0.6f, 0.0f, 0.6f) },//X- Z+
	{VGet(-0.6f, 0.0f,-0.6f) },//X- Z-
	{VGet(-0.6f, 0.6f, 0.6f) },//X- Y+ Z+
	{VGet(-0.6f, 0.6f,-0.6f) },//X- Y+ Z-
	{VGet(-0.6f,-0.6f, 0.6f) },//X- Y- Z+
	{VGet(-0.6f,-0.6f,-0.6f) },//X- Y- Z-

	{VGet( 0.0f, 0.9f, 0.0f) },//Y+
	{VGet( 0.0f, 0.6f, 0.6f) },//Y+ Z+
	{VGet( 0.0f, 0.6f,-0.6f) },//Y+ Z-

	{VGet( 0.0f,-0.9f, 0.0f) },//Y-
	{VGet( 0.0f,-0.6f, 0.6f) },//Y- Z+
	{VGet( 0.0f,-0.6f,-0.6f) },//Y- Z-
	
	{VGet( 0.0f, 0.0f, 0.9f) },//Z+
	{VGet( 0.0f, 0.0f,-0.9f) },//Z-
};
constexpr int EffectManager::SPREAD_CIRCLE_COLOR = GetColor(255, 0, 0);
/// <summary>
/// コンストラクタ
/// </summary>
EffectManager::EffectManager()
{
	Init();
	Create();
}
/// <summary>
/// デストラクタ
/// </summary>
EffectManager::~EffectManager()
{
	Final();
}
void EffectManager::Create()
{
	for (int i = 0; i < DIRECTION_NUM; i++)
	{
		spreadEffect[i] = new SpreadEffect(MV1LoadModel("Data/Model/Effect/SpreadEffect_Sphere.mv1"));
	}
}
/// <summary>
/// 初期化
/// </summary>
void EffectManager::Init()
{
	isShowSpreadEffect = false;
}
/// <summary>
/// 拡散するするエフェクト
/// </summary>
/// <param name="_EffectDisplayPos">エフェクトを表示したい座標</param>
/// /// <param name="isInvicible">無敵時間かどうか</param>
void EffectManager::SpreadEffectManager(VECTOR _pos,bool isInvicible)
{
	isShowSpreadEffect = isInvicible;
	//もしもエフェクトが表示されていなかったら
	if (!isShowSpreadEffect)
	{
		VECTOR pos = VGet(_pos.x, _pos.y + 30.0f, _pos.z);
		for (int i = 0; i < DIRECTION_NUM; i++)
		{
			spreadEffect[i]->Init(pos, DIRECTION[i]);
		}
	}
	else
	{
		for (int i = 0; i < DIRECTION_NUM; i++)
		{
			spreadEffect[i]->Update();
			spreadEffect[i]->Draw();
		}
	}
}
void EffectManager::Final()
{
	for (int i = 0; i < DIRECTION_NUM; i++)
	{
		if (spreadEffect[i])
		{
			delete(spreadEffect[i]);
			spreadEffect[i] = NULL;
		}
	}

}