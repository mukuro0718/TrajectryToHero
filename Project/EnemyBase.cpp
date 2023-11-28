////===========================================================================
////@brief エネミーベースクラス / 基底
////===========================================================================
//#include"EnemyBase.h"
//#include"Common.h"
//#include"EffectManager.h"
//const VECTOR EnemyBase::DESTROY_POS = VGet(500.0f, 500.0f, 500.0f);
///// <summary>
///// コンストラクタ
///// </summary>
///// <param name="humanModelHandle">コピーするモデルハンドル</param>
//EnemyBase::EnemyBase(int modelHandle)
//{
//	effectManager = new EffectManager();
//	maxHP = 0;
//	//モデルのコピー
//	base.modelHandle = MV1DuplicateModel(modelHandle);
//	if (modelHandle < 0)
//	{
//		printfDx("Enemyデータ読み込みに失敗");
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
///// デストラクタ
///// </summary>
//EnemyBase::~EnemyBase()
//{
//	Final();
//}
///// <summary>
///// 削除
///// </summary>
//void EnemyBase::Final()
//{
//	// モデルのアンロード.
//	MV1DeleteModel(base.modelHandle);
//	if (effectManager)
//	{
//		delete(effectManager);
//		effectManager = NULL;
//	}
//}
///// <summary>
///// 描画
///// </summary>
//void EnemyBase::Draw(VECTOR playerPos)
//{
//#ifdef _DEBUG
//	VECTOR pos = VGet(base.pos.x, base.pos.y + 20.0f, base.pos.z);
//	DrawSphere3D(pos, base.radius, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);
//#endif // _DEBUG
//	//プレイヤーとエネミーの距離
//	float distance = VSize(VSub(playerPos, base.pos));
//	//エフェクトの描画
//	effectManager->SpreadEffectManager(base.pos, status.isInvincible);
//	MV1DrawModel(base.modelHandle);
//	printfDx("X:%f Y:%f Z:%f\n", MV1GetPosition(base.modelHandle).x, MV1GetPosition(base.modelHandle).y, MV1GetPosition(base.modelHandle).z);
//}
///// <summary>
///// ランダムで生成した新しい座標を返す
///// </summary>
///// <returns>新しい座標</returns>
//VECTOR EnemyBase::NewRandomPos()
//{
//	/*HACK:マップの範囲は中心0,0,0の半径500*/
//	return 	spawnPoint[GetRand(RANDOM_RANGE)];
//}
