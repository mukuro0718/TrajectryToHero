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
/// コンストラクタ
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
	//モデルのロード
	auto& load = Load::GetInstance();
	load.GetEnemyData(&model,&frameImage,&hpImage,&font);
	CreateAndInit();
}
/// <summary>
/// デストラクタ
/// </summary>
EnemyManager::~EnemyManager()
{
	AllDestroy();
}
/// <summary>
/// 初期化
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
/// インスタンスの生成と初期化を行う
/// </summary>
void EnemyManager::CreateAndInit()
{
	//インスタンスのNULL初期化
	bossEnemy = nullptr;
	//インスタンスの作成
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
/// 更新
/// </summary>
/// <param name="isDrawImg">画像を描画していたら処理を止める</param>
void EnemyManager::Update(const VECTOR _playerPos, const float _playerLv,const bool _isFarm, const bool _isBoss)
{
	if (_isFarm && !_isBoss)
	{
		for (int i = 0; i < nowWeakEnemyNum; i++)
		{			
			//もし死亡フラグが立っていなかったらUpdate処理を行う
			if (!weakEnemy[i]->GetIsDeath())
			{
				weakEnemy[i]->Update();
			}
			//死亡していたら
			else
			{
				VECTOR spawnPos = RandomSpawnPos();
				//スポーン地点とプレイヤーとの距離を測る
				float playerToSpawnPoint = VSize(VSub(_playerPos, spawnPos));
				//もし距離が定数以上離れていたらスポーンさせる
				if (playerToSpawnPoint >= 200.0f)
				{
					weakEnemy[i]->SetSpawnPos(spawnPos);
					weakEnemy[i]->NewStatus(_playerLv);
					weakEnemy[i]->Init();
				}
			}
			//もしプレイヤーが攻撃していなかったら
		}
		for (int i = 0; i < nowStrongEnemyNum; i++)
		{
			//もし死亡フラグが立っていなかったらUpdate処理を行う
			if (!strongEnemy[i]->GetIsDeath())
			{
				strongEnemy[i]->Update();
			}
			//もし死亡フラグが立っていたら
			else
			{
				VECTOR spawnPos = RandomSpawnPos();
				//スポーン地点とプレイヤーとの距離を測る
				float playerToSpawnPoint = VSize(VSub(_playerPos, spawnPos));
				//もし距離が定数以上離れていたらスポーンさせる
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
/// 移動
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
/// 描画
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
/// 削除
/// </summary>
void EnemyManager::AllDestroy()
{
	//コンテナ中のインスタンスを削除する
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
/// HP計算
/// </summary>
float EnemyManager::CalcHPWeakEnemy(const int _enemyNum, const float _atk, const VECTOR _attackerPos)
{
	//HP計算
	return weakEnemy[_enemyNum]->CalcHP(_atk, _attackerPos);
}
///<summary>
/// HP計算
/// </summary>
float EnemyManager::CalcHPStrongEnemy(const int _enemyNum, const float _atk, const VECTOR _attackerPos)
{
	//HP計算
	return strongEnemy[_enemyNum]->CalcHP(_atk, _attackerPos);
}
///<summary>
/// HP計算
/// </summary>
float EnemyManager::CalcHPBossEnemy(const float _atk, const VECTOR _attackerPos)
{
	//HP計算
	return bossEnemy->CalcHP(_atk, _attackerPos);
}
/// <summary>
/// 必要な経験値の初期化
/// </summary>
void EnemyManager::InitExpToGive(const int _enemyNum)
{
	weakEnemy[_enemyNum]->InitExpToGive();
}
/// <summary>
/// 移動量補正
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
