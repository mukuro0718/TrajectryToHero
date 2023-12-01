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
void EnemyManager::Update(const VECTOR playerPos,const bool isFarm, const bool isBoss)
{
	if (isFarm && !isBoss)
	{
		for (int i = 0; i < MAX_WEAK_ENEMY_NUM; i++)
		{
			//もし死亡フラグが立っていなかったらUpdate処理を行う
			if (!weakEnemy[i]->GetIsDeath())
			{
				weakEnemy[i]->Update(playerPos);
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
						//SpawnInfo spawnInfo = NewRandomPos();
						strongEnemy->Init();
					}
					else
					{
						//SpawnInfo spawnInfo = NewRandomPos();
						weakEnemy[i]->Init();
					}
				}
				else
				{
					//SpawnInfo spawnInfo = NewRandomPos();
					weakEnemy[i]->Init();
				}
			}
			//もしプレイヤーが攻撃していなかったら
		}
		if (isStrongEnemy)
		{
			//もし死亡フラグが立っていなかったらUpdate処理を行う
			if (!strongEnemy->GetIsDeath())
			{
				strongEnemy->Update(playerPos);
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
			bossEnemy->Update(playerPos);
		}
	}
}
/// <summary>
/// 描画
/// </summary>
void EnemyManager::Draw(VECTOR playerPos, const bool isFarm, const bool isBoss)
{
	if (isFarm && !isBoss)
	{
		for (int i = 0; i < MAX_WEAK_ENEMY_NUM; i++)
		{
			if (!weakEnemy[i]->GetIsDeath())
			{
				weakEnemy[i]->Draw(playerPos);
			}
		}
		if (isStrongEnemy)
		{
			if (!strongEnemy->GetIsDeath())
			{
				strongEnemy->Draw(playerPos);
			}
		}
	}
	else
	{
		if (!bossEnemy->GetIsDeath())
		{
			bossEnemy->Draw(playerPos);
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

///// <summary>
///// ランダムで生成した新しい座標を返す
///// </summary>
///// <returns>新しい座標</returns>
//EnemyManager::SpawnInfo EnemyManager::NewRandomPos()
//{
//	SpawnInfo spawn;
//	//ダブりチェック
//	while (1)
//	{
//		//新しいスポーン場所を決める
//		spawn.num = GetRand(RANDOM_RANGE);
//		//まだ誰もその場所にスポーンしていなかったら
//		if (isAlreadySpawn[spawn.num] == false)
//		{
//			isAlreadySpawn[spawn.num] = true;
//			break;
//		}
//	}
//	spawn.pos = SPAWN_POINT [spawn.num];
//	/*HACK:マップの範囲は中心0,0,0の半径500*/
//	return spawn;
//}