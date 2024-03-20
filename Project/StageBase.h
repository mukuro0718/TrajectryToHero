//===========================================================================
//@brief �X�e�[�W�x�[�X�N���X
//===========================================================================
#pragma once
#include "DxLib.h"
#include<vector>
class StageBase
{
public:
	StageBase(std::vector<int> _data);			// ��������R���X�g���N�^
	virtual ~StageBase();				// �f�X�g���N�^

	const void Draw();						//�`��
	const void Delete();						//�ŏI����
	const void Update();						//�X�V
protected:
	/*�\���́E�񋓑�*/
	enum class FARM
	{
		GROUND,
		VILLAGE,
		GATE,
		PORTAL
	};
	/*�ÓI�萔*/
	static const VECTOR SCALE;			//�g�嗦
	static const VECTOR INIT_STAGE_POS;	//�����v���C���[���W
	/*�ϐ�*/
	std::vector<int> model;	//���f���n���h��
	VECTOR pos;				//�|�W�V����
};

