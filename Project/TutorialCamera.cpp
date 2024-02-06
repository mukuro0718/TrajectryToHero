#include "TutorialCamera.h"
#include "Common.h"
#include <math.h>

//�����_����̋���
const VECTOR TutorialCamera::DISTANCE_TO_POINT = VGet(0.0f, 40.0f, 0.0f);
//Y���{����ɂȂ�悤�J������ݒ肷��p�̃x�N�g��
const VECTOR TutorialCamera::UP_VECTOR_Y = VGet(0.0f, 1.0f, 0.0f);
/// <summary>
/// �R���X�g���N�^
/// </summary>
TutorialCamera::TutorialCamera()
	:pos(ORIGIN_POS)
	,targetPos(ORIGIN_POS)
	,cameraToPlayer(ORIGIN_POS)
	,angleX(INIT_ANGLE)
{
	// ���s0.1f�`1000.0f�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);
	pos = ORIGIN_POS;
	cameraToPlayer = ORIGIN_POS;
	angleX = INIT_ANGLE;
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
TutorialCamera::~TutorialCamera()
{
	// �����Ȃ�
}
/// <summary>
/// ������
/// </summary>
void TutorialCamera::Init(const VECTOR _playerPos)
{
	angleX = INIT_ANGLE;
	targetPos = _playerPos;
	ChangeRotate(targetPos);
}
/// <summary>
/// �X�V
/// </summary>
void TutorialCamera::Update(const VECTOR _playerPos)
{
	targetPos = _playerPos;
	// �J�����̈ʒu�̐ݒ�
	ChangeRotate(targetPos);
	targetPos.y += ADJUST_Y_POS;
	SetCameraPositionAndTargetAndUpVec(pos, targetPos, UP_VECTOR_Y);
}
/// <summary>
/// �p�x�̕ύX
/// </summary>
/// <param name="playerPos"></param>
void TutorialCamera::ChangeRotate(const VECTOR _playerPos)
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
	pos = VAdd(_playerPos, cameraOffset);
	cameraToPlayer = VNorm(VSub(_playerPos, pos));
}

