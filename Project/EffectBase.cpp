//===========================================================================
//@brief �G�t�F�N�g�x�[�X�N���X
// �e�G�t�F�N�g�N���X�K�v�Ȋ֐��̒�`���s��
//===========================================================================
#include"EffectBase.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
EffectBase::EffectBase(int _modelHandle)
{
	modelHandle = 0;
	modelHandle = MV1DuplicateModel(_modelHandle);
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
EffectBase::~EffectBase()
{
	Delete();
}
/// <summary>
/// �`��
/// </summary>
void EffectBase::Draw()
{
	MV1DrawModel(modelHandle);
}
/// <summary>
/// �폜
/// </summary>
void EffectBase::Delete()
{
	MV1DeleteModel(modelHandle);
}