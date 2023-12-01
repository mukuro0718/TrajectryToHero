//===========================================================================
//@brief �G�l�~�[�x�[�X�N���X / ���
//===========================================================================
#include"EnemyBase.h"
#include"Common.h"
//#include"EffectManager.h"
const VECTOR EnemyBase::DESTROY_POS = VGet(500.0f, 500.0f, 500.0f);
const int EnemyBase::CAPSULE_COLOR = GetColor(0,255,0);
const int EnemyBase::SPHERE_COLOR = GetColor(0, 200, 0);
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="humanModelHandle">�R�s�[���郂�f���n���h��</param>
EnemyBase::EnemyBase(int _modelHandle)
{
	status = new CharacterStatus();
	//effectManager = new EffectManager();
	maxHP = 0;
	//���f���̃R�s�[
	modelHandle = MV1DuplicateModel(_modelHandle);
	if (modelHandle < 0)
	{
		printfDx("Enemy�f�[�^�ǂݍ��݂Ɏ��s");
	}
	isFarmBossEnemyPos = true;
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyBase::~EnemyBase()
{
	Final();
}
/// <summary>
/// �폜
/// </summary>
void EnemyBase::Final()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(modelHandle);
	//if (effectManager)
	//{
	//	delete(effectManager);
	//	effectManager = NULL;
	//}
}
/// <summary>
/// �`��
/// </summary>
void EnemyBase::Draw(VECTOR playerPos)
{
#ifdef _DEBUG
	SetUpCapsule(pos, HEIGHT, RADIUS,CAPSULE_COLOR,false);
	DrawCapsule(capsuleInfo);
	VECTOR enemyLeftFootPos = MV1GetFramePosition(modelHandle,57);
	SetUpSphere(enemyLeftFootPos,SPHERE_RADIUS,SPHERE_COLOR,false);
	DrawSphere(sphereInfo);
#endif // _DEBUG
	//�v���C���[�ƃG�l�~�[�̋���
	float distance = VSize(VSub(playerPos, pos));
	//�G�t�F�N�g�̕`��
	//effectManager->SpreadEffectManager(pos, isInvincible);
	MV1DrawModel(modelHandle);
	//printfDx("X:%f Y:%f Z:%f\n", MV1GetPosition(modelHandle).x, MV1GetPosition(modelHandle).y, MV1GetPosition(modelHandle).z);
}
