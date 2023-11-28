//=============================================================================
// @brief  �J�����N���X
//=============================================================================
#pragma once
#include "DxLib.h"
//�E�X�e�B�b�N���͍\����
struct InputRightStick
{
	int XBuf = 0;
	int YBuf = 0;
};
class Camera final
{
public:
	Camera();							// �R���X�g���N�^
	~Camera();							// �f�X�g���N�^

	void Init  (VECTOR _playerPos);		//������
	void Update(VECTOR _playerPos);		// �X�V

	const float  GetAngleX()		 { return angleX; };		//�J�����A���O����getter
	const VECTOR GetCameraToPlayer() { return cameraToPlayer; }	//�J��������v���C���[�ւ̃x�N�g����getter
private:
	/*�ÓI�萔*/
	static const	 VECTOR			 DISTANCE_TO_POINT;				//�����_�܂ł̋���
	static const	 VECTOR			 UP_VECTOR_Y;					//Y���{����ɂȂ�悤�J������ݒ肷��p�̃x�N�g��
	static constexpr InputRightStick NONE_INPUT_VALUE	= { 0,0 };	//�X�e�B�b�N���͂��Ȃ�
	static constexpr float			 CAMERA_NEAR		= 1.0f;		//�J�����̋ߕ`��͈�
	static constexpr float			 CAMERA_FAR			= 2000.0f;	//�J�����̉��`��͈�
	static constexpr float			 INIT_ANGLE			= 0.0f;		//�����p�x
	static constexpr float			 ADD_ANGLE_VALUE	= 0.1f;		//�p�x������
	static constexpr float			 OFFSET_VALUE		= 100.0f;	//�I�t�Z�b�g�l
	static constexpr float			 ADJUST_Y_POS		= 40.0f;	//Y���W����
	/*���������֐�*/
	void ChangeRotate(VECTOR _playerPos);	//�p�x�̕ύX
	/*�����o�ϐ�*/
	InputRightStick inputRightStick;	//�E�X�e�B�b�N���͍\����
	VECTOR			pos;				// �|�W�V����
	VECTOR			cameraToPlayer;		//�J��������v���C���[�ւ̃x�N�g��
	float			angleX;				//X�J�����A���O��
};