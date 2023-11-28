////===========================================================================
////@brief �G�l�~�[�x�[�X�N���X / ���
////===========================================================================
//#include"EnemyBase.h"
//#include"Common.h"
//#include"EffectManager.h"
//const VECTOR EnemyBase::DESTROY_POS = VGet(500.0f, 500.0f, 500.0f);
///// <summary>
///// �R���X�g���N�^
///// </summary>
///// <param name="humanModelHandle">�R�s�[���郂�f���n���h��</param>
//EnemyBase::EnemyBase(int modelHandle)
//{
//	effectManager = new EffectManager();
//	maxHP = 0;
//	//���f���̃R�s�[
//	base.modelHandle = MV1DuplicateModel(modelHandle);
//	if (modelHandle < 0)
//	{
//		printfDx("Enemy�f�[�^�ǂݍ��݂Ɏ��s");
//	}
//	isFarmBossEnemyPos = true;
//	spawnPoint[0] = VGet(-350.0f, 0.0f, 350.0f);
//	spawnPoint[1] = VGet(0.0f, 0.0f, 350.0f);
//	spawnPoint[2] = VGet(350.0f, 0.0f, 350.0f);
//	spawnPoint[3] = VGet(-350.0f, 0.0f, 0.0f);
//	spawnPoint[4] = VGet(350.0f, 0.0f, 0.0f);
//	spawnPoint[5] = VGet(-350.0f, 0.0f, -350.0f);
//	spawnPoint[6] = VGet(0.0f, 0.0f, -350.0f);
//	spawnPoint[7] = VGet(350.0f, 0.0f, -350.0f);
//}
///// <summary>
///// �f�X�g���N�^
///// </summary>
//EnemyBase::~EnemyBase()
//{
//	Final();
//}
///// <summary>
///// �폜
///// </summary>
//void EnemyBase::Final()
//{
//	// ���f���̃A�����[�h.
//	MV1DeleteModel(base.modelHandle);
//	if (effectManager)
//	{
//		delete(effectManager);
//		effectManager = NULL;
//	}
//}
///// <summary>
///// �`��
///// </summary>
//void EnemyBase::Draw(VECTOR playerPos)
//{
//#ifdef _DEBUG
//	VECTOR pos = VGet(base.pos.x, base.pos.y + 20.0f, base.pos.z);
//	DrawSphere3D(pos, base.radius, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);
//#endif // _DEBUG
//	//�v���C���[�ƃG�l�~�[�̋���
//	float distance = VSize(VSub(playerPos, base.pos));
//	//�G�t�F�N�g�̕`��
//	effectManager->SpreadEffectManager(base.pos, status.isInvincible);
//	MV1DrawModel(base.modelHandle);
//	printfDx("X:%f Y:%f Z:%f\n", MV1GetPosition(base.modelHandle).x, MV1GetPosition(base.modelHandle).y, MV1GetPosition(base.modelHandle).z);
//}
///// <summary>
///// �����_���Ő��������V�������W��Ԃ�
///// </summary>
///// <returns>�V�������W</returns>
//VECTOR EnemyBase::NewRandomPos()
//{
//	/*HACK:�}�b�v�͈̔͂͒��S0,0,0�̔��a500*/
//	return 	spawnPoint[GetRand(RANDOM_RANGE)];
//}
