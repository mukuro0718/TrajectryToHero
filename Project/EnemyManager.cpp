#include"EnemyManager.h"
#include"WeakEnemy.h"
#include"StrongEnemy.h"
#include"Boss.h"
#include"Collision.h"
#include"Common.h"
#include"Load.h"
const int EnemyManager::FONT_COLOR_GREEN = GetColor(50, 255, 50);//モデルの回転値
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
{
	isStrongEnemy = false;
	isBossEnemy = false;
	isHitCheckSetUp = false;
	deathStrongEnemyNum = 0;
	//モデルのロード
	auto& load = Load::GetInstance();
	load.GetEnemyData(&model);
	CreateAndInit();
	//Init();
	hpFontHandle = CreateFontToHandle("Data/Img/Font/HelpMe.ttf", HP_FONT_SIZE, HP_FONT_THICK, DX_FONTTYPE_NORMAL);
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
	for (int i = 0; i < MAX_WEAK_ENEMY_NUM; i++)
	{
		weakEnemy[i]->Init();
	}
}
/// <summary>
/// インスタンスの生成と初期化を行う
/// </summary>
void EnemyManager::CreateAndInit()
{
	//インスタンスのNULL初期化
	for (int i = 0; i < MAX_WEAK_ENEMY_NUM; i++)
	{
		weakEnemy[i] = NULL;
	}
	bossEnemy = NULL;
	strongEnemy = NULL;
	//インスタンスの作成
	for (int i = 0; i < MAX_WEAK_ENEMY_NUM; i++)
	{
		weakEnemy[i] = new WeakEnemy(SPAWN_POINT[i],model[static_cast<int>(ModelType::WEAK_MODEL)]);
	}
	strongEnemy = new StrongEnemy(SPAWN_POINT[0],model[static_cast<int>(ModelType::STRONG_MODEL)]);
	bossEnemy = new Boss(SPAWN_POINT[0],model[static_cast<int>(ModelType::BOSS_MODEL)]);
}
/// <summary>
/// 更新
/// </summary>
/// <param name="isDrawImg">画像を描画していたら処理を止める</param>
void EnemyManager::Update(const VECTOR _playerPos,const bool _isFarm, const bool _isBoss)
{
	if (_isFarm && !_isBoss)
	{
		for (int i = 0; i < MAX_WEAK_ENEMY_NUM; i++)
		{			
			//もし死亡フラグが立っていなかったらUpdate処理を行う
			if (!weakEnemy[i]->GetIsDeath())
			{
				weakEnemy[i]->Update();
			}
			//死亡していたら
			else
			{
				//ランダムで０が出た時
				if (GetRand(10) == 0)
				{
					if (isStrongEnemy)
					{
						//中ボスをスポーンさせる
						isStrongEnemy = true;
						//初期化
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
			//もしプレイヤーが攻撃していなかったら
		}
		if (isStrongEnemy)
		{
			//もし死亡フラグが立っていなかったらUpdate処理を行う
			if (!strongEnemy->GetIsDeath())
			{
				strongEnemy->Update();
			}
			//もし死亡フラグが立っていたら
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
/// 移動
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
/// 描画
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
/// 削除
/// </summary>
void EnemyManager::AllDestroy()
{
	//コンテナ中のインスタンスを削除する
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
/// HP計算
/// </summary>
float EnemyManager::CalcHPWeakEnemy(const int _enemyNum, const float _atk)
{
	//HP計算
	return weakEnemy[_enemyNum]->CalcHP(_atk);
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
void EnemyManager::FixMoveVecStrongEnemy(const VECTOR _fixVec)
{
	strongEnemy->FixMoveVec(_fixVec);
}
void EnemyManager::FixMoveVecBossEnemy(const VECTOR _fixVec)
{
	bossEnemy->FixMoveVec(_fixVec);
}