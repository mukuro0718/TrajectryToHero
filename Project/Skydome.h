//===========================================================================
//@brief �X�J�C�h�[���N���X
// �X�J�C�h�[���̕`����s��
// 3�p�`�|���S�����u���[�����ʂ�^���ĕ`�悷��
//===========================================================================

#pragma once
#include"DxLib.h"
#include"Common.h"
#include<vector>

class BloomEffect;

using namespace std;
class Skydome
{
public:
	Skydome();	//�R���X�g���N�^
	~Skydome();	//�f�X�g���N�^

	const void Init();										//������
	const void Draw();										//�`��
	const void SetDrawScreenType(const float _angleX);	//�`�悷��X�N���[���̕ύX
	const void BloomProg();								//�`�挋�ʂ�`��
private:
	/*�\���́E�񋓑�*/
	enum class ModelType
	{
		NIGNT,//��
		CLOUD_1,//�_�P
		CLOUD_2,//�_�Q
	};
	/*�ÓI�萔*/
	static constexpr int MODEL_NUM = 2;//���f���̐�

	static const VECTOR SCALE[MODEL_NUM];		//�傫��
	static const VECTOR ADD_ROTATE[MODEL_NUM];	//�ǉ���]��

	/*�����o�ϐ�*/
	BloomEffect* bloom;//�u���[��

	vector<int> modelHandle;	//���f���n���h��

	VECTOR rotate[MODEL_NUM];	//��]��
	VECTOR pos;					//���W

};

