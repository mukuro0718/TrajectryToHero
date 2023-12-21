#include"BloodParticleBase.h"
#include"Common.h"
/// <summary>
/// コンストラクタ
/// </summary>
BloodParticleBase::BloodParticleBase()
	:particleDir(ORIGIN_POS)
	,moveDir(ORIGIN_POS)
	,pos(ORIGIN_POS)
	,speed(0.0f)
{

}
/// <summary>
/// デストラクタ
/// </summary>
BloodParticleBase::~BloodParticleBase()
{

}
/// <summary>
/// 初期化
/// </summary>
void BloodParticleBase::Init(const VECTOR _targetDir)
{
	SetDir(_targetDir);
	SetScale();
	SetSpeed();
}
/// <summary>
/// 更新
/// </summary>
void BloodParticleBase::Update()
{
	//移動サイズを求める
	VECTOR moveSize = VScale(moveDir, speed);
	//座標の更新
	pos = VAdd(pos, moveSize);
}
/// <summary>
/// スケールの設定
/// </summary>
void BloodParticleBase::SetScale()
{
	scale.x = static_cast<float>(GetRand(RANDOM_OFFSET_RANGE));
	scale.y = static_cast<float>(GetRand(RANDOM_OFFSET_RANGE));
	scale.z = static_cast<float>(GetRand(RANDOM_OFFSET_RANGE));
}
/// <summary>
/// 速さの設定
/// </summary>
void BloodParticleBase::SetSpeed()
{
	speed = static_cast<float>(GetRand(RANDOM_SPEED_RANGE));
}
/// <summary>
/// 方向の設定
/// </summary>
void BloodParticleBase::SetDir(const VECTOR _targetDir)
{
	/*パーティクルを出す方向を決める*/
	//パーティクルを出す目標の方向ベクトルを代入
	particleDir = _targetDir;
	//正規化する
	particleDir = VNorm(particleDir);
	//Y軸をもとに-90回す行列を取得する
	MATRIX yMatrix = MGetRotY(Y_DEG * (DX_PI_F / 180));
	//Z軸をもとに-45回す行列を取得する
	MATRIX zMatrix = MGetRotZ(Z_DEG * (DX_PI_F / 180));
	//求めた行列をもとに、ベクトルを回転させる
	particleDir = VTransform(particleDir, yMatrix);
	particleDir = VTransform(particleDir, zMatrix);
	
	/*移動方向を決める(単位ベクトルにする)*/
	//ランダムでXYZの増加量を決める
	VECTOR offset = ORIGIN_POS;
	offset.x = static_cast<float>(GetRand(RANDOM_OFFSET_RANGE));
	offset.y = static_cast<float>(GetRand(RANDOM_OFFSET_RANGE));
	offset.z = static_cast<float>(GetRand(RANDOM_OFFSET_RANGE));
	//目標の方向ベクトルにオフセットベクトルを足す
	moveDir = VAdd(particleDir, offset);
	//出したベクトルを正規化して方向ベクトルにする
	moveDir = VNorm(moveDir);
}