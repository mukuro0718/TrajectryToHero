//=============================================================================
// @brief �`���[�g���A���J�����N���X
// �Q�[���V�[���̃J�����N���X�����ƂɁA�`���[�g���A���p�̕ύX��������i�p���͂��Ȃ��j
//=============================================================================
#include "Camera.h"

#pragma once
#include<DxLib.h>
class TutorialCamera final
{
public:
	TutorialCamera();							// �R���X�g���N�^
	~TutorialCamera();							// �f�X�g���N�^

	const void Init(const VECTOR _playerPos);		//������
	const void Update(const VECTOR _playerPos);		// �X�V

	const float  GetAngleX() { return angleX; };		//�J�����A���O����getter
	const VECTOR GetCameraToPlayer() { return cameraToPlayer; }	//�J��������v���C���[�ւ̃x�N�g����getter
private:
	//�E�X�e�B�b�N���͍\����
	struct InputRightStick
	{
		int XBuf = 0;
		int YBuf = 0;
	};

	/*�ÓI�萔*/
	static constexpr InputRightStick NONE_INPUT		  = { 0,0 };	//�X�e�B�b�N���͂��Ȃ�
	static constexpr float			 CAMERA_NEAR	  = 0.1f;		//�J�����̋ߕ`��͈�
	static constexpr float			 CAMERA_FAR		  = 2600.0f;	//�J�����̉��`��͈�
	static constexpr float			 INIT_ANGLE		  = 0.0f;		//�����p�x
	static constexpr float			 ADD_ANGLE		  = 0.1f;		//�p�x������
	static constexpr float			 OFFSET_VALUE	  = 100.0f;		//�I�t�Z�b�g�l
	static constexpr float			 ADJUST_Y_POS	  = 40.0f;		//Y���W����

	static const VECTOR	DISTANCE_TO_POINT;	//�����_�܂ł̋���
	static const VECTOR	UP_VECTOR_Y;		//Y���{����ɂȂ�悤�J������ݒ肷��p�̃x�N�g��
	/*���������֐�*/
	void ChangeRotate(const VECTOR _playerPos);	//�p�x�̕ύX
	/*�����o�ϐ�*/
	InputRightStick inputRightStick;	//�E�X�e�B�b�N���͍\����
	VECTOR			pos;				//���W
	VECTOR			targetPos;			//�ڕW�̍��W
	VECTOR			cameraToPlayer;		//�J��������v���C���[�ւ̃x�N�g��
	float			angleX;				//X�J�����A���O��
};

