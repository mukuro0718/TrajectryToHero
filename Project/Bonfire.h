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

	const void Draw();//�`��
	/*getter*/
	const VECTOR GetPos() const { return POS; }
private:
	/*�\���́E�񋓑�*/
	enum class DataType
	{
		BONFIRE_MODEL,
		FLAME,
	};
	/*�ÓI�萔*/
	static constexpr int FIRE_PARTICLE_NUM = 150;//�p�[�e�B�N����
	
	static const VECTOR POS;	//���W
	static const VECTOR SCALE;	//�g�嗦
	static const VECTOR ROTATE;	//��]��
	/*�����o�ϐ�*/
	std::vector<FireParticle*> fire;//�p�[�e�B�N��

	std::vector<int> particleData;	//�p�[�e�B�N���f�[�^
	std::vector<int> bonfireData;	//���΃f�[�^

	int modelHandle;//���f���n���h��
};

