#include"EnemyManager.h"
#include"WeakEnemy.h"
#include"StrongEnemy.h"
#include"Boss.h"
#include"Collision.h"
#include"Common.h"
#include"Load.h"
const int EnemyManager::FONT_COLOR_GREEN = GetColor(50, 255, 50);//���f���̉�]�l
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
{
	isStrongEnemy = false;
	isBossEnemy = false;
	isHitCheckSetUp = false;
	deathStrongEnemyNum = 0;
	//���f���̃��[�h
	auto& load = Load::GetInstance();
	load.GetEnemyData(&model);
	CreateAndInit();
	//Init();
	hpFontHandle = CreateFontToHandle("Data/Img/Font/HelpMe.ttf", HP_FONT_SIZE, HP_FONT_THICK, DX_FONTTYPE_NORMAL);
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
	for (int i = 0; i < MAX_WEAK_ENEMY_NUM; i++)
	{
		weakEnemy[i]->Init();
	}
}
/// <summary>
/// �C���X�^���X�̐����Ə��������s��
/// </summary>
void EnemyManager::CreateAndInit()
{
	//�C���X�^���X��NULL������
	for (int i = 0; i < MAX_WEAK_ENEMY_NUM; i++)
	{
		weakEnemy[i] = NULL;
	}
	bossEnemy = NULL;
	strongEnemy = NULL;
	//�C���X�^���X�̍쐬
	for (int i = 0; i < MAX_WEAK_ENEMY_NUM; i++)
	{
		weakEnemy[i] = new WeakEnemy(SPAWN_POINT[i],model[static_cast<int>(ModelType::WEAK_MODEL)]);
	}
	strongEnemy = new StrongEnemy(SPAWN_POINT[0],model[static_cast<int>(ModelType::STRONG_MODEL)]);
	bossEnemy = new Boss(SPAWN_POINT[0],model[static_cast<int>(ModelType::BOSS_MODEL)]);
}
/// <summary>
/// �X�V
/// </summary>
/// <param name="isDrawImg">�摜��`�悵�Ă����珈�����~�߂�</param>
void EnemyManager::Update(const VECTOR _playerPos,const bool _isFarm, const bool _isBoss)
{
	if (_isFarm && !_isBoss)
	{
		for (int i = 0; i < MAX_WEAK_ENEMY_NUM; i++)
		{			
			//�������S�t���O�������Ă��Ȃ�������Update�������s��
			if (!weakEnemy[i]->GetIsDeath())
			{
				weakEnemy[i]->Update();
			}
			//���S���Ă�����
			else
			{
				//�����_���łO���o����
				if (GetRand(10) == 0)
				{
					if (isStrongEnemy)
					{
						//���{�X���X�|�[��������
						isStrongEnemy = true;
						//������
						strongEnemy->Init();
					}
					else
					{
						float playerToSpawnPoint = VSize(VSub(_playerPos, SPAWN_POINT[i]));
						if (playerToSpawnPoint >= 200.0f)
						{
							weakEnemy[i]->Init();
						}
					}
				}
				else
				{
					float playerToSpawnPoint = VSize(VSub(_playerPos, SPAWN_POINT[i]));
					if (playerToSpawnPoint >= 100.0f)
					{
						weakEnemy[i]->Init();
					}
				}
			}
			//�����v���C���[���U�����Ă��Ȃ�������
		}
		if (isStrongEnemy)
		{
			//�������S�t���O�������Ă��Ȃ�������Update�������s��
			if (!strongEnemy->GetIsDeath())
			{
				strongEnemy->Update();
			}
			//�������S�t���O�������Ă�����
			else
			{
				isStrongEnemy = false;
			}
		}
	}
	else
	{
		if (!bossEnemy->GetIsDeath())
		{
			bossEnemy->Update();
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
		for (int i = 0; i < MAX_WEAK_ENEMY_NUM; i++)
		{
			if (!weakEnemy[i]->GetIsDeath())
			{
				weakEnemy[i]->Move(_playerPos);
			}
		}
		if (isStrongEnemy)
		{
			if (!strongEnemy->GetIsDeath())
			{
				strongEnemy->Move(_playerPos);
			}
		}
	}
	else
	{
		if (!bossEnemy->GetIsDeath())
		{
			bossEnemy->Move(_playerPos);
			VECTOR framePos = MV1GetFramePosition(bossEnemy->GetModelHandle(), 6);
			framePos.y += 30.0f;
			VECTOR screenPos = ConvWorldPosToScreenPos(framePos);

			DrawFormatStringToHandle(screenPos.x, screenPos.y, FONT_COLOR_GREEN, hpFontHandle, "HP:%d\n", static_cast<int>(bossEnemy->GetHp()) + 1);
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
		for (int i = 0; i < MAX_WEAK_ENEMY_NUM; i++)
		{
			if (!weakEnemy[i]->GetIsDeath())
			{
				weakEnemy[i]->Draw(_playerPos);
			}
		}
		if (isStrongEnemy)
		{
			if (!strongEnemy->GetIsDeath())
			{
				strongEnemy->Draw(_playerPos);
			}
		}
	}
	else
	{
		if (!bossEnemy->GetIsDeath())
		{
			bossEnemy->Draw(_playerPos);
			VECTOR framePos = MV1GetFramePosition(bossEnemy->GetModelHandle(), 6);
			framePos.y += 30.0f;
			VECTOR screenPos = ConvWorldPosToScreenPos(framePos);

			DrawFormatStringToHandle(screenPos.x, screenPos.y, FONT_COLOR_GREEN, hpFontHandle, "HP:%d\n",static_cast<int>(bossEnemy->GetHp()) + 1);
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
	delete(strongEnemy);
	delete(bossEnemy);
}

bool EnemyManager::CountDestroyEnemy()
{
	if (destroyEnemy >= nowEnemyIndex)
	{
		return true;
	}
	return false;
}

///<summary>
/// HP�v�Z
/// </summary>
float EnemyManager::CalcHPWeakEnemy(const int _enemyNum, const float _atk)
{
	//HP�v�Z
	return weakEnemy[_enemyNum]->CalcHP(_atk);
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
void EnemyManager::FixMoveVecStrongEnemy(const VECTOR _fixVec)
{
	strongEnemy->FixMoveVec(_fixVec);
}
void EnemyManager::FixMoveVecBossEnemy(const VECTOR _fixVec)
{
	bossEnemy->FixMoveVec(_fixVec);
}