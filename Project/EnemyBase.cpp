//===========================================================================
//@brief エネミーベースクラス / 基底
//===========================================================================
#include"EnemyBase.h"
#include"Common.h"
//#include"EffectManager.h"
const VECTOR EnemyBase::DESTROY_POS = VGet(500.0f, 500.0f, 500.0f);
const int EnemyBase::CAPSULE_COLOR = GetColor(0,255,0);
const int EnemyBase::SPHERE_COLOR = GetColor(0, 200, 0);
/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="humanModelHandle">コピーするモデルハンドル</param>
EnemyBase::EnemyBase(int _modelHandle)
{
	status = new CharacterStatus();
	//effectManager = new EffectManager();
	maxHP = 0;
	//モデルのコピー
	modelHandle = MV1DuplicateModel(_modelHandle);
	if (modelHandle < 0)
	{
		printfDx("Enemyデータ読み込みに失敗");
	}
	isFarmBossEnemyPos = true;
}
/// <summary>
/// デストラクタ
/// </summary>
EnemyBase::~EnemyBase()
{
	Final();
}
/// <summary>
/// 削除
/// </summary>
void EnemyBase::Final()
{
	// モデルのアンロード.
	MV1DeleteModel(modelHandle);
	//if (effectManager)
	//{
	//	delete(effectManager);
	//	effectManager = NULL;
	//}
}
/// <summary>
/// 描画
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
	//プレイヤーとエネミーの距離
	float distance = VSize(VSub(playerPos, pos));
	//エフェクトの描画
	//effectManager->SpreadEffectManager(pos, isInvincible);
	MV1DrawModel(modelHandle);
	//printfDx("X:%f Y:%f Z:%f\n", MV1GetPosition(modelHandle).x, MV1GetPosition(modelHandle).y, MV1GetPosition(modelHandle).z);
}
