
//=============================================================================
// @brief  �J�����N���X
//=============================================================================
#include "Camera.h"
#include "Common.h"
#include <math.h>

//�����_����̋���
const VECTOR Camera::DISTANCE_TO_POINT = VGet(0.0f, 40.0f, 0.0f);
//Y���{����ɂȂ�悤�J������ݒ肷��p�̃x�N�g��
const VECTOR Camera::UP_VECTOR_Y = VGet(0.0f, 1.0f, 0.0f);
/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera()
{
	// ���s0.1f�`1000.0f�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);
	// �|�W�V�����̏�����
	pos = ORIGIN_POS;
	cameraToPlayer = ORIGIN_POS;
	angleX = INIT_ANGLE;
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{
	// �����Ȃ�
}
/// <summary>
/// ������
/// </summary>
void Camera::Init(VECTOR _playerPos)
{
	angleX = INIT_ANGLE;
	ChangeRotate(_playerPos);
}
/// <summary>
/// �X�V
/// </summary>
/// <param name="playerPos">�����_</param>
void Camera::Update(VECTOR _playerPos)
{
	//// �J�����̈ʒu�̐ݒ�
	ChangeRotate(_playerPos);
	_playerPos.y += ADJUST_Y_POS;
	SetCameraPositionAndTargetAndUpVec(pos,_playerPos, UP_VECTOR_Y);
}
/// <summary>
/// �p�x�̕ύX
/// </summary>
/// <param name="playerPos"></param>
void Camera::ChangeRotate(VECTOR _playerPos)
{
	VECTOR cameraOffset = DISTANCE_TO_POINT;
	//XBuf +:�E -:��  YBuf +:�� -:��
	GetJoypadAnalogInputRight(&inputRightStick.XBuf, &inputRightStick.YBuf, DX_INPUT_PAD1);
	//���E��]
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

