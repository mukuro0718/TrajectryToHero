
//=============================================================================
// @brief  カメラクラス
//=============================================================================
#include "Camera.h"
#include "Common.h"
#include <math.h>

//注視点からの距離
const VECTOR Camera::DISTANCE_TO_POINT = VGet(0.0f, 40.0f, 0.0f);
//Y軸＋が上になるようカメラを設定する用のベクトル
const VECTOR Camera::UP_VECTOR_Y = VGet(0.0f, 1.0f, 0.0f);
/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
{
	// 奥行0.1f～1000.0fまでをカメラの描画範囲とする
	SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);
	// ポジションの初期化
	pos = ORIGIN_POS;
	cameraToPlayer = ORIGIN_POS;
	angleX = INIT_ANGLE;
}
/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
	// 処理なし
}
/// <summary>
/// 初期化
/// </summary>
void Camera::Init(VECTOR _playerPos)
{
	angleX = INIT_ANGLE;
	ChangeRotate(_playerPos);
}
/// <summary>
/// 更新
/// </summary>
/// <param name="playerPos">注視点</param>
void Camera::Update(VECTOR _playerPos)
{
	//// カメラの位置の設定
	ChangeRotate(_playerPos);
	_playerPos.y += ADJUST_Y_POS;
	SetCameraPositionAndTargetAndUpVec(pos,_playerPos, UP_VECTOR_Y);
}
/// <summary>
/// 角度の変更
/// </summary>
/// <param name="playerPos"></param>
void Camera::ChangeRotate(VECTOR _playerPos)
{
	VECTOR cameraOffset = DISTANCE_TO_POINT;
	//XBuf +:右 -:左  YBuf +:下 -:上
	GetJoypadAnalogInputRight(&inputRightStick.XBuf, &inputRightStick.YBuf, DX_INPUT_PAD1);
	//左右回転
	if (inputRightStick.XBuf > NONE_INPUT_VALUE.XBuf || CheckHitKey(KEY_INPUT_D))
	{
		angleX -= ADD_ANGLE_VALUE;
	}
	if (inputRightStick.XBuf < NONE_INPUT_VALUE.XBuf || CheckHitKey(KEY_INPUT_A))
	{
		angleX += ADD_ANGLE_VALUE;
	}
	
	cameraOffset.x = -OFFSET_VALUE * sinf(angleX);
	cameraOffset.z = OFFSET_VALUE * cosf(angleX);
	//printfDx("cameraOfset X:%f Y:%f Z:%f\n", cameraOfset.x, cameraOfset.y, cameraOfset.z);
	pos = VAdd(_playerPos , cameraOffset);
	cameraToPlayer = VNorm(VSub(_playerPos, pos));
}

