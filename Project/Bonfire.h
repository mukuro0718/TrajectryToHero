//======================================================
// @brief ������΃N���X
//======================================================
#pragma once
#include<DxLib.h>
#include<vector>
class FireParticle;
class Bonfire
{
public:
	Bonfire();//�R���X�g���N�^
	~Bonfire();//�f�X�g���N�^
	void Draw();//�`��

	const VECTOR GetPos() const { return POS; }
private:
	/*�ÓI�萔*/
	static constexpr int FIRE_PARTICLE_NUM = 150;
	static const VECTOR POS;//���W
	static const VECTOR SCALE;//�g�嗦
	static const VECTOR ROTATE;//��]��
	//�����o�ϐ�
	enum class DataType
	{
		BONFIRE_MODEL,
		FLAME,
	};
	int modelHandle;
	std::vector<int> particleData;
	std::vector<int> bonfireData;
	std::vector<FireParticle*> fire;
};

