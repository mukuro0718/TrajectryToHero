//===========================================================================
//@brief 拡散するエフェクトクラス
// エフェクトの初期化と位置更新と描画を行う
//===========================================================================
#include"BloodParticle.h"
#include"Common.h"

const int BloodParticle::SPHERE_COLOR = GetColor(255, 0, 0);
constexpr VECTOR BloodParticle::SPHERE_SCALE = VGet(0.01f, 0.01f, 0.01f);
/// <summary>
/// コンストラクタ
/// </summary>
BloodParticle::BloodParticle()
	:initPos(ORIGIN_POS)
{
}
/// <summary>
/// デストラクタ
/// </summary>
BloodParticle::~BloodParticle()
{

}
