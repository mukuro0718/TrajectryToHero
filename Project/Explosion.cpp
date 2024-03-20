#include "Explosion.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
Explosion::Explosion()
	: isDraw(false)
	, scale(ORIGIN_POS)
	, rotate(ORIGIN_POS)
{
	modelHandle = MV1LoadModel("Data/Model/Enemy/flame.mv1");
	Init();
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
Explosion::~Explosion()
{

}
/// <summary>
/// ������
/// </summary>
const void Explosion::Init()
{
	isDraw = false;
	rotate = ORIGIN_POS;
	scale = ORIGIN_POS;
	sphere.centerPos = ORIGIN_POS;
	sphere.radius = 0.0f;
}
/// <summary>
/// �X�V
/// </summary>
const void Explosion::Update(const bool _isDraw,const VECTOR _targetPos)
{
	if (_isDraw)
	{
		//�����O�t���[���ŕ`��t���O�������Ă��Ȃ�������`�撆�S���W��ڕW�̍��W�ɐݒ肵�AY���W���O�ɂ��A�t���O�𗧂Ă�
		if (!isDraw)
		{
			sphere.centerPos = _targetPos;
			isDraw = true;
			MV1SetPosition(modelHandle, sphere.centerPos);
		}
		//�g�嗦�̐ݒ�
		SetScale(ADD_SCALE);
		SetRotate(ADD_ROTATE);
	}
	else
	{
		Init();
	}
}
/// <summary>
/// �`��
/// </summary>
const void Explosion::Draw()
{
	if (isDraw)
	{
		MV1DrawModel(modelHandle);
	}
}
/// <summary>
/// �g�嗦�̐ݒ�
/// </summary>
const void Explosion::SetScale(const float _scale)
{
	if (scale.x <= MAX_SCALE)
	{
		float prevScale = scale.x;
		float addScale = prevScale + _scale;
		scale = VGet(addScale, addScale, addScale);
		MV1SetScale(modelHandle, scale);
		if (sphere.radius <= MAX_RADIUS)
		{
			sphere.radius += 0.25;
		}
	}
}
/// <summary>
/// ��]���̐ݒ�
/// </summary>
const void Explosion::SetRotate(const float _rotate)
{
	/*
	���̃N���X���ł́AY�������ƂɃ��f������]�����邽�߁A
	Y���W�̂ݐݒ肷��
	�܂����̊֐����ŁA��]���̑������s��
	*/
	float rotateY = rotate.y;
	rotate = VGet(0.0f, rotateY + _rotate, 0.0f);
	MV1SetRotationXYZ(modelHandle, rotate);
}