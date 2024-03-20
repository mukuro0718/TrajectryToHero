#include"BloodParticleBase.h"
#include"Common.h"
/// <summary>
/// コンストラクタ
/// </summary>
BloodParticleBase::BloodParticleBase(const int _imageHandle)
	: moveDir(ORIGIN_POS)
	, pos	 (ORIGIN_POS)
	, scale	 (0.0f)
	, speed	 (0.0f)
	, alpha	 (0)
	, isUpdateGrav(false)
	, imageHandle(_imageHandle)
	, framecount(0)
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
const void BloodParticleBase::Init(const VECTOR _targetDir, const VECTOR _targetPos)
{
	pos = _targetPos;
	pos.y += 20.0f;
	alpha = 255;
	SetScale();
	SetSpeed();
	SetMoveDir();
}
/// <summary>
/// 更新
/// </summary>
const void BloodParticleBase::Update()
{
	//座標の更新
	pos = VAdd(pos, moveDir);
	
	moveDir.y -= GRAVITY;
}
/// <summary>
/// スケールの設定
/// </summary>
const void BloodParticleBase::SetScale()
{
	scale = ReturnRandomFloatValue(RANDOM_SCALE_RANGE, false);
}
/// <summary>
/// 速さの設定
/// </summary>
const void BloodParticleBase::SetSpeed()
{
	speed = ReturnRandomFloatValue(RANDOM_SPEED_RANGE, false) / 5;
}
/// <summary>
/// 方向の設定
/// </summary>
const void BloodParticleBase::SetMoveDir()
{
	/*移動方向を決める(単位ベクトルにする)*/
	//ランダムでXYZの値を決める
	
	moveDir.x = ReturnRandomFloatValue(RANDOM_DIR_RANGE,true);
	moveDir.y = ReturnRandomFloatValue(RANDOM_DIR_RANGE, true);
	moveDir.z = ReturnRandomFloatValue(RANDOM_DIR_RANGE, true);
	//出したベクトルを正規化して方向ベクトルにする
	moveDir = VNorm(moveDir);
	//方向ベクトルにスピードをかけて移動ベクトルにする
	moveDir = VScale(moveDir, speed);
}
/// <summary>
/// 描画
/// </summary>
const void BloodParticleBase::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBillboard3D(pos, 0.0f, 0.0f, scale, 0.0f, imageHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	alpha -= ALPHA_REDUCED_VALUE;
	if (alpha < 0)
	{
		alpha = 0;
	}
}
/// <summary>
/// 指定した範囲のランダム値を返す
/// </summary>
const float BloodParticleBase::ReturnRandomFloatValue(const int _range, const bool _useSign)
{
	if (_useSign)
	{
		if (static_cast<int>(Sign::MINUS) == GetRand(RANDOM_SCALE_RANGE))
		{
			return static_cast<float>(-GetRand(_range));
		}
	}
	return static_cast<float>(GetRand(_range));
}










///// <summary>
///// コンストラクタ
///// </summary>
//BloodParticleBase::BloodParticleBase(const int _imageHandle)
//	:particleDir(ORIGIN_POS)
//	,moveDir(ORIGIN_POS)
//	,pos(ORIGIN_POS)
//	,scale(0.0f)
//	,speed(0.0f)
//	,alpha(0)
//	,imageHandle(_imageHandle)
//{
//
//}
///// <summary>
///// デストラクタ
///// </summary>
//BloodParticleBase::~BloodParticleBase()
//{
//
//}
///// <summary>
///// 初期化
///// </summary>
//void BloodParticleBase::Init(const VECTOR _targetDir , const VECTOR _targetPos)
//{
//	pos = _targetPos;
//	pos.y += 20.0f;
//	alpha = 255;
//	SetDir(_targetDir);
//	SetScale();
//	SetSpeed();
//}
///// <summary>
///// 更新
///// </summary>
//void BloodParticleBase::Update()
//{
//
//	//座標の更新
//	pos = VAdd(pos, moveDir);
//	pos.y -= GRAVITY;
//}
///// <summary>
///// スケールの設定
///// </summary>
//void BloodParticleBase::SetScale()
//{
//	scale = ReturnRandomFloatValue(RANDOM_SCALE_RANGE, false);
//}
///// <summary>
///// 速さの設定
///// </summary>
//void BloodParticleBase::SetSpeed()
//{
//	speed = ReturnRandomFloatValue(RANDOM_SPEED_RANGE,false) / 10;
//}
///// <summary>
///// 方向の設定
///// </summary>
//void BloodParticleBase::SetDir(const VECTOR _targetDir)
//{
//	/*パーティクルを出す方向を決める*/
//	//パーティクルを出す目標の方向ベクトルを代入
//	particleDir = _targetDir;
//	//正規化する
//	particleDir = VNorm(particleDir);
//	//Y軸をもとに-90回す行列を取得する
//	MATRIX yMatrix = MGetRotY(Y_DEG * (DX_PI_F / 180));
//	//Z軸をもとに-45回す行列を取得する
//	MATRIX zMatrix = MGetRotZ(Z_DEG * (DX_PI_F / 180));
//	//求めた行列をもとに、ベクトルを回転させる
//	particleDir = VTransform(particleDir, yMatrix);
//	particleDir = VTransform(particleDir, zMatrix);
//	
//	/*移動方向を決める(単位ベクトルにする)*/
//	//ランダムでXYZの傾きを決める
//	MATRIX xRot = MGetRotX(ReturnRandomFloatValue(RANDOM_DEG_RANGE, true) * (DX_PI_F / 180));
//	MATRIX yRot = MGetRotY(ReturnRandomFloatValue(RANDOM_DEG_RANGE, true) * (DX_PI_F / 180));
//	MATRIX zRot = MGetRotZ(ReturnRandomFloatValue(RANDOM_DEG_RANGE, true) * (DX_PI_F / 180));
//	//目標の方向ベクトルにオフセットベクトルを足す
//	moveDir = VTransform(particleDir, xRot);
//	moveDir = VTransform(particleDir, yRot);
//	moveDir = VTransform(particleDir, zRot);
//	//出したベクトルを正規化して方向ベクトルにする
//	moveDir = VNorm(moveDir);
//	moveDir = VScale(moveDir, speed);
//}
///// <summary>
///// 描画
///// </summary>
//void BloodParticleBase::Draw()
//{
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
//	DrawBillboard3D(pos, 0.0f, 0.0f, scale, 0.0f, imageHandle, TRUE);
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
//	alpha -= ALPHA_REDUCED_VALUE;
//	if (alpha < 0)
//	{
//		alpha = 0;
//	}
//}
///// <summary>
///// 指定した範囲のランダム値を返す
///// </summary>
//float BloodParticleBase::ReturnRandomFloatValue(const int _range, const bool _useSign)
//{
//	if (_useSign)
//	{
//		if (static_cast<int>(Sign::MINUS) == GetRand(RANDOM_SCALE_RANGE))
//		{
//			return static_cast<float>(-GetRand(_range) - 2);
//		}
//	}
//	return static_cast<float>(GetRand(_range) + 2);
//}