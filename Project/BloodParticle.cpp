//===========================================================================
//@brief �g�U����G�t�F�N�g�N���X
// �G�t�F�N�g�̏������ƈʒu�X�V�ƕ`����s��
//===========================================================================
#include"BloodParticle.h"
#include"Common.h"

const int BloodParticle::SPHERE_COLOR = GetColor(255, 0, 0);
constexpr VECTOR BloodParticle::SPHERE_SCALE = VGet(0.01f, 0.01f, 0.01f);
/// <summary>
/// �R���X�g���N�^
/// </summary>
BloodParticle::BloodParticle()
	:initPos(ORIGIN_POS)
{
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
BloodParticle::~BloodParticle()
{

}
