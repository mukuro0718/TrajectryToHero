#pragma once
#include<DxLib.h>
#include<vector>


class FireParticle;
class TutorialStage
{
public:
	TutorialStage(const std::vector<int> _data);
	~TutorialStage();

	void Init();
	void Draw();						//�`��
	void Delete();						//�ŏI����
	void Update();						//�X�V
	const int GetIsShowGate() const { return isShowGate; }
	const void OnIsShowGate() { isShowGate = true; }
	const VECTOR GetBonfirePos() { return pos[static_cast<int>(DataType::BONFIRE)]; }
	const int GetGroundModelHandle() { return data[static_cast<int>(DataType::STAGE)]; }
	const VECTOR GetGatePos() { return pos[static_cast<int>(DataType::GATE)]; }
private:
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
	static constexpr int MAX_DATA_NUM = 6;//���[�h�����f�[�^�̍ő吔
	static constexpr int MODEL_DATA_NUM = 5;
	static const VECTOR SCALE;			//�g�嗦
	static const VECTOR INIT_STAGE_POS;//�����v���C���[���W
	/*�����o�ϐ�*/
	std::vector<int> data;//���[�h�����f�[�^
	std::vector<VECTOR> scale;//���W
	std::vector<VECTOR> pos;//���W
	float portalRotate;
	bool isShowGate;

	/*���p�[�e�B�N��*/
	static constexpr int FIRE_PARTICLE_NUM = 150;
	std::vector<int> fireData;
	std::vector< FireParticle*> fire;
};

