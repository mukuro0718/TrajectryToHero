//===========================================================================
//@brief �I�[�v�j���O�N���X
// �g�p��������A�T�C�g�Ȃǂ̉摜��`��
//===========================================================================
#pragma once
#include"DxLib.h"
#include<vector>
#include"Common.h"
using namespace std;

class Opening final
{
public:
	Opening();	//�R���X�g���N�^
	~Opening();	//�f�X�g���N�^

	void Init();	//������
	void Update();	//�X�V
	void Draw();	//�`��

	// �I�[�v�j���O�I���t���O�� getter
	const bool& GetIsEndOpening() const { return isEndOpening; }
private:
	/*�萔*/
	enum class ImageType//�摜�^�C�v
	{
		SE_SITE,	//SE�T�C�g
		MODEL_SITE,	//���f���T�C�g
		MUSIC_SITE,	//�g�p�������y�T�C�g
		LANGUAGE,	//�g�p����i�J�����j
	};
	static constexpr float LAST_TIMER	= 60.0f;	//�^�C�}�[�ő�l
	static constexpr float FIRST_TIMER	= 0.0f;		//�^�C�}�[�������l
	static constexpr int   MAX_ALPHA	= 255;		//�ő�A���t�@�l
	static constexpr int   MIN_ALPHA	= 0;		//�ŏ��A���t�@�l
	static constexpr int   ALPHA_COUNT	= 5;		//�A���t�@�l������
	static constexpr VEC2D IMAGE_POS	= { 0,0 };	//�摜�`����W
	/*���������֐�*/
	void CountProcess();	//�J�E���g����
	void EndOpening();		//�I�[�v�j���O�I��
	/*�����o�ϐ�*/
	vector<int> image;				//�摜�n���h��
	int			nowShowImageType;	//�`�悷��摜�̎��
	int			alpha;				//�u�����h����A���t�@�l
	bool		isChangeAlpha;		//�A���t�@�l�ύX�t���O
	bool		isEndOpening;		//�I�[�v�j���O�I���t���O
	float		changeTimer;		//�\���摜�؂�ւ��^�C�}�[
};
