#include"EnemyManager.h"
#include"WeakEnemy.h"
#include"StrongEnemy.h"
#include"BossEnemy.h"
#include"Collision.h"
#include"Common.h"
#include"Load.h"
const VECTOR EnemyManager::SPAWN_POINT[] =
{
	VGet(-350.0f, 0.0f, 350.0f),
	VGet(0.0f, 0.0f, 350.0f),
	VGet(350.0f, 0.0f, 350.0f),
	VGet(-350.0f, 0.0f, 0.0f),
	VGet(350.0f, 0.0f, 0.0f),
	VGet(-350.0f, 0.0f, -350.0f),
	VGet(0.0f, 0.0f, -350.0f),
	VGet(350.0f, 0.0f, -350.0f)
};
/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyManager::EnemyManager()
	:font				(0)
	,frameImage			(0)
	,hpImage			(0)
	,nowWeakEnemyNum	(0)
	,nowStrongEnemyNum	(0)
	,isHitCheckSetUp	(false)
	,isDrawImg			(false)
	,isBossEnemy		(false)
	,isStrongEnemy		(false)
{
	//���f���̃��[�h
	auto& load = Load::GetInstance();
	load.GetEnemyData(&model,&frameImage,&hpImage,&font);
	CreateAndInit();
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyManager::~EnemyManager()
{
	AllDestroy();
}
/// <summary>
/// ������
/// </summary>
void EnemyManager::Init()
{
	for (int i = 0; i < nowWeakEnemyNum; i++)
	{
		weakEnemy[i]->Init();
	}
	for (int i = 0; i < nowStrongEnemyNum; i++)
	{
		strongEnemy[i]->Init();
	}
}
/// <summary>
/// �C���X�^���X�̐����Ə��������s��
/// </summary>
void EnemyManager::CreateAndInit()
{
	//�C���X�^���X��NULL������
	bossEnemy = nullptr;
	//�C���X�^���X�̍쐬
	for (int i = 0; i < MAX_WEAK_ENEMY_NUM; i++)
	{
		weakEnemy.push_back(new WeakEnemy(SPAWN_POINT[i], model[static_cast<int>(ModelType::WEAK_MODEL)]));
	}
	for (int i = 0; i < MAX_STRONG_ENEMY_NUM; i++)
	{
		strongEnemy.push_back(new StrongEnemy(SPAWN_POINT[i], model[static_cast<int>(ModelType::STRONG_MODEL)]));
	}
	bossEnemy = new BossEnemy(SPAWN_POINT[1],model[static_cast<int>(ModelType::BOSS_MODEL)],frameImage,hpImage,font);
}
/// <summary>
/// �X�V
/// </summary>
/// <param name="isDrawImg">�摜��`�悵�Ă����珈�����~�߂�</param>
void EnemyManager::Update(const VECTOR _playerPos, const float _playerLv,const bool _isFarm, const bool _isBoss)
{
	if (_isFarm && !_isBoss)
	{
		for (int i = 0; i < nowWeakEnemyNum; i++)
		{			
			//�������S�t���O�������Ă��Ȃ�������Update�������s��
			if (!weakEnemy[i]->GetIsDeath())
			{
				weakEnemy[i]->Update();
			}
			//���S���Ă�����
			else
			{
				VECTOR spawnPos = RandomSpawnPos();
				//�X�|�[���n�_�ƃv���C���[�Ƃ̋����𑪂�
				float playerToSpawnPoint = VSize(VSub(_playerPos, spawnPos));
				//�����������萔�ȏ㗣��Ă�����X�|�[��������
				if (playerToSpawnPoint >= 200.0f)
				{
					weakEnemy[i]->SetSpawnPos(spawnPos);
					weakEnemy[i]->NewStatus(_playerLv);
					weakEnemy[i]->Init();
				}
			}
			//�����v���C���[���U�����Ă��Ȃ�������
		}
		for (int i = 0; i < nowStrongEnemyNum; i++)
		{
			//�������S�t���O�������Ă��Ȃ�������Update�������s��
			if (!strongEnemy[i]->GetIsDeath())
			{
				strongEnemy[i]->Update();
			}
			//�������S�t���O�������Ă�����
			else
			{
				VECTOR spawnPos = RandomSpawnPos();
				//�X�|�[���n�_�ƃv���C���[�Ƃ̋����𑪂�
				float playerToSpawnPoint = VSize(VSub(_playerPos, spawnPos));
				//�����������萔�ȏ㗣��Ă�����X�|�[��������
				if (playerToSpawnPoint >= 200.0f)
				{
					strongEnemy[i]->SetSpawnPos(spawnPos);
					strongEnemy[i]->NewStatus(_playerLv);
					strongEnemy[i]->Init();
				}
			}
		}
	}
	else
	{
		if (!isBossEnemy)
		{
			bossEnemy->Init();
			isBossEnemy = true;
		}
		if (!bossEnemy->GetIsDeath())
		{
			bossEnemy->Update();
			bossEnemy->UpdateUI();
		}
	}
}
/// <summary>
/// �ړ�
/// </summary>
void EnemyManager::Move(const VECTOR _playerPos, const bool _isFarm, const bool _isBoss)
{
	if (_isFarm && !_isBoss)
	{
		for (int i = 0; i < nowWeakEnemyNum; i++)
		{
			if (!weakEnemy[i]->GetIsDeath())
			{
				weakEnemy[i]->Move(_playerPos);
			}
		}
		for (int i = 0; i < nowStrongEnemyNum; i++)
		{
			if (!strongEnemy[i]->GetIsDeath())
			{
				strongEnemy[i]->Move(_playerPos);
			}
		}
	}
	else
	{
		if (!bossEnemy->GetIsDeath())
		{
			bossEnemy->Move(_playerPos);
		}
	}

}
/// <summary>
/// �`��
/// </summary>
void EnemyManager::Draw(VECTOR _playerPos, const bool _isFarm, const bool _isBoss)
{
	if (_isFarm && !_isBoss)
	{
		for (int i = 0; i < nowWeakEnemyNum; i++)
		{
			if (!weakEnemy[i]->GetIsDeath())
			{
				weakEnemy[i]->Draw(_playerPos);
			}
		}
		for (int i = 0; i < nowStrongEnemyNum; i++)
		{
			if (!strongEnemy[i]->GetIsDeath())
			{
				strongEnemy[i]->Draw(_playerPos);
			}
		}
	}
	else
	{
		if (!bossEnemy->GetIsDeath())
		{
			bossEnemy->Draw(_playerPos);
			bossEnemy->DrawUI();
		}
	}
}
/// <summary>
/// �폜
/// </summary>
void EnemyManager::AllDestroy()
{
	//�R���e�i���̃C���X�^���X���폜����
	for (int i = 0; i < MAX_WEAK_ENEMY_NUM; i++)
	{
		delete(weakEnemy[i]);
	}
	for (int i = 0; i < MAX_STRONG_ENEMY_NUM; i++)
	{
		delete(strongEnemy[i]);
	}
	delete(bossEnemy);
	weakEnemy.clear();
	strongEnemy.clear();
}
void EnemyManager::FlaggingBossEnemy()
{
	bossEnemy->Flagging();
}
///<summary>
/// HP�v�Z
/// </summary>
float EnemyManager::CalcHPWeakEnemy(const int _enemyNum, const float _atk, const VECTOR _attackerPos)
{
	//HP�v�Z
	return weakEnemy[_enemyNum]->CalcHP(_atk, _attackerPos);
}
///<summary>
/// HP�v�Z
/// </summary>
float EnemyManager::CalcHPStrongEnemy(const int _enemyNum, const float _atk, const VECTOR _attackerPos)
{
	//HP�v�Z
	return strongEnemy[_enemyNum]->CalcHP(_atk, _attackerPos);
}
///<summary>
/// HP�v�Z
/// </summary>
float EnemyManager::CalcHPBossEnemy(const float _atk, const VECTOR _attackerPos)
{
	//HP�v�Z
	return bossEnemy->CalcHP(_atk, _attackerPos);
}
/// <summary>
/// �K�v�Ȍo���l�̏�����
/// </summary>
void EnemyManager::InitExpToGive(const int _enemyNum)
{
	weakEnemy[_enemyNum]->InitExpToGive();
}
/// <summary>
/// �ړ��ʕ␳
/// </summary>
void EnemyManager::FixMoveVecWeakEnemy(const int _enemyNum,const VECTOR _fixVec)
{
	weakEnemy[_enemyNum]->FixMoveVec(_fixVec);
}
void EnemyManager::FixMoveVecStrongEnemy(const int _enemyNum, const VECTOR _fixVec)
{
	strongEnemy[_enemyNum]->FixMoveVec(_fixVec);
}
void EnemyManager::FixMoveVecBossEnemy(const VECTOR _fixVec)
{
	bossEnemy->FixMoveVec(_fixVec);
}
void EnemyManager::DrawShadow(const int _stageModelHandle, const bool _isFarm, const bool _isBoss)
{
	if (_isFarm && !_isBoss)
	{
		for (int i = 0; i < nowWeakEnemyNum; i++)
		{
			if (!weakEnemy[i]->GetIsDeath())
			{
				weakEnemy[i]->DrawShadow(_stageModelHandle, weakEnemy[i]->GetPos(), NORMAL_ENEMY_SHADOW_HEIGHT, NORMAL_ENEMY_SHADOW_SIZE);
			}
		}
		for (int i = 0; i < nowStrongEnemyNum; i++)
		{
			strongEnemy[i]->DrawShadow(_stageModelHandle, strongEnemy[i]->GetPos(), NORMAL_ENEMY_SHADOW_HEIGHT, NORMAL_ENEMY_SHADOW_SIZE);
		}
	}
	else
	{
		if (!bossEnemy->GetIsDeath())
		{
			bossEnemy->DrawShadow(_stageModelHandle, bossEnemy->GetPos(), BOSS_ENEMY_SHADOW_HEIGHT, BOSS_ENEMY_SHADOW_SIZE);
		}
	}
}
void EnemyManager::AdjustTheNumberOfEnemy(const int _playerLv)
{
	switch (_playerLv)
	{
	case 1:
		nowWeakEnemyNum = 2;
		nowStrongEnemyNum = 0;
		break;
	case 3:
		nowWeakEnemyNum = 4;
		nowStrongEnemyNum = 1;
		break;
	case 5:
		nowWeakEnemyNum = 6;
		nowStrongEnemyNum = 2;
		break;
	case 7:
		nowWeakEnemyNum = 4;
		nowStrongEnemyNum = 4;
		break;
	case 9:
		nowWeakEnemyNum = 2;
		nowStrongEnemyNum = 6;
		break;
	case 12:
		nowWeakEnemyNum = 1;
		nowStrongEnemyNum = 7;
		break;
	default:
		break;
	}
}
VECTOR EnemyManager::RandomSpawnPos()
{
	VECTOR outPutPos = ORIGIN_POS;

	outPutPos.x = static_cast<float>(GetRand(150));
	if (GetRand(1) == 0)
	{
		outPutPos.x *= -1;
	}
	outPutPos.z = static_cast<float>(GetRand(150));
	if (GetRand(1) == 0)
	{
		outPutPos.z *= -1;
	}

	return outPutPos;
}
const void EnemyManager::PhysicalRecoveryBossEnemy()
{
	bossEnemy->PhysicalRecovery();
}
const void EnemyManager::DrawStrongerUI(const float _playerLv, const bool _isFarm)
{
	if (_isFarm)
	{
		for (int i = 0; i < nowWeakEnemyNum; i++)
		{
			weakEnemy[i]->DrawStrongerUI(_playerLv,weakEnemy[i]->GetModelHandle(),6);
		}
		for (int i = 0; i < nowStrongEnemyNum; i++)
		{
			strongEnemy[i]->DrawStrongerUI(_playerLv,strongEnemy[i]->GetModelHandle(),6);
		}
	}
	else
	{
		bossEnemy->DrawStrongerUI(_playerLv,bossEnemy->GetModelHandle(),7);
	}
}
