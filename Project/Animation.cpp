//===========================================================================
//@brief �A�j���[�V�����N���X
//===========================================================================

#include"Animation.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Animation::Animation()
{
	animAttachIndex = 0;
	animTotalTime = 0.0f;
	animPlayTime = 0.0f;
	prevAnim = 0;
	nowAnim = 0;
	isChangeAnim = false;

}
/// <summary>
/// �f�X�g���N�^
/// </summary>
Animation::~Animation()
{

}
/// <summary>
/// �A�j���[�V�����̒ǉ�
/// </summary>
/// <param name="animModelHandle">�A�^�b�`�������A�j���[�V�����������Ă��郂�f���̃n���h��</param>
/// <param name="useAnimIndex">�A�^�b�`�������A�j���[�V�����̃C���f�b�N�X�ԍ�</param>
void Animation::Add(int _animModelHandle,int _AnimIndex)
{
	animModelHandle.push_back(_animModelHandle);
	useAnimIndex.push_back(_AnimIndex);
}
/// <summary>
/// �A�j���[�V�����̃A�^�b�`
/// </summary>
/// <param name="animKind">�A�j���[�V�������A�^�b�`���������f���̃n���h��</param>
void Animation::Attach(int *_modelHandle)
{
	//�A�j���[�V�����̃A�^�b�`
	animAttachIndex = MV1AttachAnim(*_modelHandle,useAnimIndex[nowAnim], animModelHandle[nowAnim], FALSE);
	//�A�j���[�V�����̑��Đ����Ԃ�ݒ�
	animTotalTime = MV1GetAttachAnimTotalTime(*_modelHandle,animAttachIndex);
}
/// <summary>
/// �A�j���[�V�����̍Đ�
/// </summary>
void Animation::Play(int *_modelHandle)
{
	//�������܂ŃA�^�b�`���Ă����A�j���[�V�����Ǝ��̃A�j���[�V�������Ⴄ�Ȃ�
	if (nowAnim != prevAnim)
	{
		isChangeAnim = false;
		animPlayTime = 0.0f;
		//���܂ŃA�^�b�`���Ă����A�j���[�V�������Ń^�b�`����
		MV1DetachAnim(*_modelHandle, animAttachIndex);
		//�A�j���[�V�����̃A�^�b�`
		Attach(_modelHandle);
		prevAnim = nowAnim;
	}
	//�A�j���[�V�����Đ����Ԃ�ݒ�
	MV1SetAttachAnimTime(*_modelHandle, animAttachIndex, animPlayTime);
	//�A�j���[�V����
	animPlayTime += 0.8f;//�Đ����Ԃ�i�߂�
	//�Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
	if (animPlayTime >= animTotalTime)
	{
		animPlayTime = 0.0f;
		isChangeAnim = true;
	}
}
