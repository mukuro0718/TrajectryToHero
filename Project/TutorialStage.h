//========================================================
// @brief �`���[�g���A���X�e�[�W�N���X
// �K�v�ȃ��f���ȊO�͕`�悵�Ȃ��悤�ɂ���
//========================================================
#pragma once
#include<DxLib.h>
#include<vector>


class FireParticle;
class TutorialStage final
{
public:
	TutorialStage(const std::vector<int> _data);
	~TutorialStage();

	const void Init(const std::vector<int> _data);		//������
	const void Draw();		//�`��
	const void Delete();	//�ŏI����
	const void Update();	//�X�V

	const void OnIsShowGate() { isShowGate = true; }//�\���t���O�𗧂Ă�
	
	/*getter*/
	const int GetIsShowGate()		const { return isShowGate; }
	const VECTOR GetBonfirePos()	const{ return pos[static_cast<int>(DataType::BONFIRE)]; }
	const int GetGroundModelHandle()const { return data[static_cast<int>(DataType::STAGE)]; }
	const VECTOR GetGatePos()		const { return pos[static_cast<int>(DataType::GATE)]; }
private:
	/*�\���́E�񋓑�*/
	enum class DataType
	{
		STAGE,
		GATE,
		PORTAL,
		SKYDOME,
		BONFIRE,
		FLAME,
	};
	/*�ÓI�萔*/
	static constexpr int MAX_DATA_NUM = 6;			//���[�h�����f�[�^�̐�
	static constexpr int MODEL_DATA_NUM = 5;		//���[�h�������f���̐�
	static constexpr int FIRE_PARTICLE_NUM = 150;	//�p�[�e�B�N���̐�

	static const VECTOR SCALE;			//�g�嗦
	static const VECTOR INIT_STAGE_POS;	//�����v���C���[���W
	/*�����o�ϐ�*/
	std::vector< FireParticle*> fire;	//�t�@�C�A�N���X�C���X�^���X
	std::vector<int> fireData;			//���摜
	std::vector<int> data;				//���[�h�����f�[�^
	std::vector<VECTOR> scale;			//���W
	std::vector<VECTOR> pos;			//���W
	float portalRotate;					//�|�[�^���̉�]�l
	bool isShowGate;					//�Q�[�g�̕\��
};

