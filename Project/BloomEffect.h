//===========================================
// @brief �u���[����������N���X
// Dxlib�̋@�\���g���Ă��邽�߁A
// �I���W�i���V�F�[�_�͎g�p���Ă��Ȃ�
//===========================================
#pragma once
#include<DxLib.h>
class BloomEffect
{
public:
	BloomEffect();	//
	~BloomEffect();	//

	const void MakeBloomScreen();		//�u���[���������邽�߂̃X�N���[�������
	const void Update();				//�X�V
	const void SetDrawScreenType();		//�X�N���[���^�C�v��ύX����
	const void GetImage();				//�摜�𓾂�
	const void DrawNormalGraph();		//�ʏ�摜��`��
	const void DrawGaussBlendGraph();	//�u���[���������摜��`��
private:
	/*�ÓI�萔*/
	static constexpr int SCREEN_WIDTH				= 1920;							//��ʂ̉��T�C�Y
	static constexpr int SCREEN_HEIGHT				= 1080;							//��ʂ̏c�T�C�Y
	static constexpr int DOWN_SCALE					= 8;							// �K�E�X�t�B���^���|����摜����ʂ̃T�C�Y�̉����̂P��
	static constexpr int DOWN_SCALE_SCREEN_WIDTH	= SCREEN_WIDTH / DOWN_SCALE;	// �K�E�X�t�B���^���|����摜�̉���
	static constexpr int DOWN_SCALE_SCREEN_HEIGHT	= SCREEN_HEIGHT / DOWN_SCALE;	// �K�E�X�t�B���^���|����摜�̏c��
	/*�����o�ϐ�*/
	int colorScreen;		// ���ʂ̕`�挋�ʂ��������ރX�N���[��
	int highBrightScreen;	// ���ʂ̕`�挋�ʂ��獂�P�x�����𔲂��o�������ʂ��������ރX�N���[��
	int downScaleScreen;	// ���P�x�������k���������ʂ��������ރX�N���[��
	int gaussScreen;		// �k���摜���K�E�X�t�B���^�łڂ��������ʂ��������ރX�N���[��
	int GaussRatio;			// �K�E�X�t�B���^�̂ڂ����x����
};

