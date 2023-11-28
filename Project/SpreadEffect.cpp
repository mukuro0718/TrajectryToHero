//===========================================================================
//@brief �g�U����G�t�F�N�g�N���X
// �G�t�F�N�g�̏������ƈʒu�X�V�ƕ`����s��
//===========================================================================
#include"SpreadEffect.h"
#include"Common.h"

const int SpreadEffect::SPHERE_COLOR = GetColor(255, 0, 0);
constexpr VECTOR SpreadEffect::SPHERE_SCALE = VGet(0.01f, 0.01f, 0.01f);
/// <summary>
/// �R���X�g���N�^
/// </summary>
SpreadEffect::SpreadEffect(int _modelHandle):EffectBase(_modelHandle)
{
	initPos = ORIGIN_POS;
	//�X�P�[���̃Z�b�g
	MV1SetScale(_modelHandle, SPHERE_SCALE);
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
SpreadEffect::~SpreadEffect()
{

}
/// <summary>
/// ������
/// </summary>
void SpreadEffect::Init(VECTOR _pos, VECTOR _direction)
{
	pos = _pos;
	direction = _direction;
}
/// <summary>
/// ������
/// </summary>
void SpreadEffect::Update()
{
	pos = VAdd(pos, direction);
	MV1SetPosition(modelHandle,pos);
}
