#include "CharacterBase.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
CharacterBase::CharacterBase()
{
	Init();
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
CharacterBase::~CharacterBase()
{
	//�����Ȃ�
}
/// <summary>
/// ������
/// </summary>
void CharacterBase::Init()
{
	pos = ORIGIN_POS;
	rotate = ORIGIN_POS;
	scale = ORIGIN_POS;
	modelHandle = 0;
	isHit = false;
	isInvincible = false;
	isMove = false;
	isAttack = false;
}
/// <summary>
/// �J�v�Z�����̐ݒ�
/// </summary>
/// <param name="pos">���W</param>
/// <param name="height">����</param>
/// <param name="radius">���a</param>
/// <param name="color">�F</param>
/// <param name="flag">�t���O</param>
void CharacterBase::SetUpCapsule(const VECTOR _pos, const float _height, const float _radius, const int _color, const int _flag)
{
	capsuleInfo.topPos = _pos;
	capsuleInfo.topPos.y += _height;
	capsuleInfo.underPos = _pos;
	capsuleInfo.radius = _radius;
	capsuleInfo.difColor = _color;
	capsuleInfo.spcColor = _color;
	capsuleInfo.fillFlag = _flag;
}
/// <summary>
/// �J�v�Z���̕`��
/// </summary>
void CharacterBase::DrawCapsule(const CapsuleInfo _capsuleInfo)
{
	DrawCapsule3D(_capsuleInfo.topPos, _capsuleInfo.underPos, _capsuleInfo.radius, _capsuleInfo.divNum, _capsuleInfo.difColor, _capsuleInfo.spcColor, _capsuleInfo.fillFlag);
}