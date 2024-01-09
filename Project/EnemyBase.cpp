//===========================================================================
//@brief エネミーベースクラス / 基底
//===========================================================================
#include"EnemyBase.h"
#include"Common.h"
#include"Timer.h"

const VECTOR  EnemyBase::DESTROY_POS = VGet(500.0f, 500.0f, 500.0f);
const COLOR_F EnemyBase::CHANGE_DIF_COLOR = GetColorF(1.0f, 0.0f, 0.0f, 1.0f);//ディフューズカラー
const COLOR_F EnemyBase::CHANGE_SPC_COLOR = GetColorF(1.0f, 0.0f, 0.0f, 1.0f);//スペキュラカラー
const COLOR_F EnemyBase::CHANGE_EMI_COLOR = GetColorF(1.0f, 0.0f, 0.0f, 1.0f);//エミッシブカラー
const COLOR_F EnemyBase::CHANGE_AMB_COLOR = GetColorF(1.0f, 0.0f, 0.0f, 1.0f);//アンビエントカラー

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="humanModelHandle">コピーするモデルハンドル</param>
EnemyBase::EnemyBase(int _modelHandle)
	:changeColorTimer(nullptr)
	, status(nullptr)
	, isChangeColor(false)
	,isPrevColorChange(false)
	,materialNum(0)
	,spawnPos(ORIGIN_POS)
	,bloodBaseDir(ORIGIN_POS)
{
	changeColorTimer = new Timer();
	changeColorTimer->Init(2);
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
/// 移動量の補正
/// </summary>
void EnemyBase::FixMoveVec(const VECTOR _fixVec)
{
	//移動量を補正する
	moveVec = VAdd(moveVec, _fixVec);
}

/// <summary>
/// 削除
/// </summary>
void EnemyBase::Final()
{
	// モデルのアンロード.
	MV1DeleteModel(modelHandle);
}
/// <summary>
/// 描画
/// </summary>
void EnemyBase::Draw(VECTOR playerPos)
{
#ifdef _DEBUG
	DrawCapsule(capsuleInfo);
	DrawSphere(sphereInfo);
#endif // _DEBUG
	//プレイヤーとエネミーの距離
	float distance = VSize(VSub(playerPos, pos));
	//エフェクトの描画
	//effectManager->SpreadEffectManager(pos, isInvincible);
	MV1DrawModel(modelHandle);
	//printfDx("X:%f Y:%f Z:%f\n", MV1GetPosition(modelHandle).x, MV1GetPosition(modelHandle).y, MV1GetPosition(modelHandle).z);
}
float EnemyBase::CalcHP(const float _atk, const VECTOR _attackerPos)
{
	isInvincible = true;
	bloodBaseDir = VSub(pos, _attackerPos);
	//HP計算
	return status->CalcHP(_atk);
}
void EnemyBase::InitExpToGive()
{
	status->InitExpToGive();
}
/// <summary>
/// 色の変更
/// </summary>
void EnemyBase::ChangeColor()
{
	if (isInvincible)
	{
		if (!isChangeColor && status->GetHp() > 0)
		{
			changeColorTimer->StartTimer();
			//マテリアルの数を取得
			materialNum = MV1GetMaterialNum(modelHandle);
			//既存のマテリアルを保存しておく
			for (int i = 0; i < materialNum; i++)
			{
				difColorInfo.push_back(MV1GetMaterialDifColor(modelHandle, i));
				spcColorInfo.push_back(MV1GetMaterialSpcColor(modelHandle, i));
				emiColorInfo.push_back(MV1GetMaterialEmiColor(modelHandle, i));
				ambColorInfo.push_back(MV1GetMaterialAmbColor(modelHandle, i));
			}
			//赤色になるようにマテリアルの色をいじる
			for (int i = 0; i < materialNum; i++)
			{
				MV1SetMaterialDifColor(modelHandle, i, CHANGE_DIF_COLOR);
				MV1SetMaterialSpcColor(modelHandle, i, CHANGE_SPC_COLOR);
				MV1SetMaterialEmiColor(modelHandle, i, CHANGE_EMI_COLOR);
				MV1SetMaterialAmbColor(modelHandle, i, CHANGE_AMB_COLOR);
			}
			//色変更フラグを立てる
			isChangeColor = true;
		}
	}
	else
	{
		//フラグを下す
		isChangeColor = false;
		isPrevColorChange = false;
		changeColorTimer->EndTimer();
	}
	//色を変更していたら
	if (!isPrevColorChange && isChangeColor && changeColorTimer->CountTimer())
	{
		//マテリアルの色をもとに戻す
		for (int i = 0; i < materialNum; i++)
		{
			MV1SetMaterialDifColor(modelHandle, i, difColorInfo[i]);
			MV1SetMaterialSpcColor(modelHandle, i, spcColorInfo[i]);
			MV1SetMaterialEmiColor(modelHandle, i, emiColorInfo[i]);
			MV1SetMaterialAmbColor(modelHandle, i, ambColorInfo[i]);
		}
		//ベクターの要素を０にする
		difColorInfo.clear();
		spcColorInfo.clear();
		emiColorInfo.clear();
		ambColorInfo.clear();
		isPrevColorChange = true;
	}
}
