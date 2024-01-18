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

	void Init();
	void Draw();						//�`��
	void Delete();						//�ŏI����
	void Update();						//�X�V

	const int GetModelHandle()const { return model[static_cast<int>(FARM::GROUND)]; }
protected:
	enum class FARM
	{
		GROUND,
		VILLAGE,
		GATE,
		PORTAL
	};
	static constexpr int MODEL_NUM = 4;
	//�萔
	static const VECTOR SCALE;			//�g�嗦
	static const VECTOR INIT_STAGE_POS;//�����v���C���[���W
	static const VECTOR ROTATE_VILLAGE;
	//�ϐ�
	std::vector<VECTOR> scale;
	std::vector<VECTOR> rotate;
	std::vector<VECTOR> pos;							//�|�W�V����
	std::vector<int> model;					//���f���n���h��
	float portalRotate;
};

