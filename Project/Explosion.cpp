#include "Explosion.h"
const int Explosion::COLOR = GetColor(60, 10, 10);
/// <summary>
/// �R���X�g���N�^
/// </summary>
Explosion::Explosion()
	: alpha(MIN_ALPHA_VALUE)
	, isDraw(false)
{
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
void Explosion::Init()
{
	sphereInfo.centerPos = ORIGIN_POS;
	sphereInfo.radius = MIN_RADIUS_RANGE;
	sphereInfo.divNum = DIV_NUM;
	sphereInfo.fillFlag = FILL_FLAG;
	sphereInfo.difColor = COLOR;
	sphereInfo.spcColor = COLOR;
	alpha = MAX_ALPHA_VALUE;
	isDraw = false;
	isInit = false;
}
/// <summary>
/// �X�V
/// </summary>
void Explosion::Update(const bool _isDraw,const VECTOR _targetPos)
{
	if (_isDraw)
	{
		//�����O�t���[���ŕ`��t���O�������Ă��Ȃ�������`�撆�S���W��ڕW�̍��W�ɐݒ肵�AY���W���O�ɂ��A�t���O�𗧂Ă�
		if (!isDraw)
		{
			sphereInfo.centerPos = _targetPos;
			sphereInfo.centerPos.y = 0.0f;
			isDraw = true;
		}
		//���a�𑝉�������
		sphereInfo.radius += ADD_RADIUS_VALUE;
		//���a���ő�l�𒴂��Ȃ��悤�ɂ���
		if (sphereInfo.radius >= MAX_RADIUS_RANGE)
		{
			sphereInfo.radius = MAX_RADIUS_RANGE;
		}
	}
	else
	{
		//�A���t�@�l������������
		alpha -= ADD_ALPHA_VALUE;
		//�A���t�@�l���ŏ��l�������Ȃ��悤�ɂ���
		if (alpha <= MIN_ALPHA_VALUE)
		{
			alpha = MIN_ALPHA_VALUE;
			isInit = false;
		}

		if (!isInit)
		{
			Init();
			isInit = true;
		}
	}
}
/// <summary>
/// �`��
/// </summary>
void Explosion::Draw()
{
	if (isDraw)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawSphere3D(sphereInfo.centerPos,sphereInfo.radius,sphereInfo.divNum, sphereInfo.difColor, sphereInfo.spcColor, sphereInfo.fillFlag);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,MAX_ALPHA_VALUE);
	}
}