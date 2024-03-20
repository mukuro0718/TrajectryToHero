//===========================================================================
//@brief �n�ʃN���X/�p��
//===========================================================================

#pragma once
#include"DxLib.h"
#include<vector>

class FarmStage
{
public:
	FarmStage(std::vector<int> _data);	// ��������R���X�g���N�^
	~FarmStage();						// �f�X�g���N�^

	const void Init();						//������
	const void Draw(const bool _isFarm);		//�`��
	const void Delete();						//�ŏI����
	const void Update(const int _playerLv);	//�X�V

	/*getter*/
	const VECTOR GetGatePos()const { return pos[static_cast<int>(FARM::GATE)]; }
	const int	 GetIsShowGate() const { return isShowGate; }
	const int	 GetModelHandle()const { return model[static_cast<int>(FARM::GROUND)]; }
protected:
	/*�\���́E�񋓑�*/
	enum class FARM
	{
		GROUND,
		GATE,
		PORTAL
	};
	/*�ÓI�萔*/
	static constexpr int MODEL_NUM = 3;//���f����

	static const VECTOR SCALE;			//�g�嗦
	static const VECTOR INIT_STAGE_POS;	//�����v���C���[���W
	//�ϐ�
	std::vector<VECTOR> scale;	//�傫��
	std::vector<VECTOR> rotate;	//��]��
	std::vector<VECTOR> pos;	//�|�W�V����
	std::vector<int>	model;	//���f���n���h��

	float portalRotate;	//�Q�[�g��]��
	bool  isShowGate;	//�Q�[�g���\������Ă��邩
};

