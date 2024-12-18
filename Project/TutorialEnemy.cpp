#include "TutorialEnemy.h"
#include"CharacterStatus.h"
#include"Animation.h"
#include"Common.h"
#include"StrongerUI.h"
#include"Shadow.h"
#include"BloodParticle.h"
#include"Load.h"
#include"Timer.h"
const int TutorialEnemy::CAPSULE_COLOR = GetColor(255, 0, 0);
const COLOR_F TutorialEnemy::CHANGE_DIF_COLOR = GetColorF(1.0f, 0.0f, 0.0f, 1.0f);//ディフューズカラー
const COLOR_F TutorialEnemy::CHANGE_SPC_COLOR = GetColorF(1.0f, 0.0f, 0.0f, 1.0f);//スペキュラカラー
const COLOR_F TutorialEnemy::CHANGE_EMI_COLOR = GetColorF(1.0f, 0.0f, 0.0f, 1.0f);//エミッシブカラー
const COLOR_F TutorialEnemy::CHANGE_AMB_COLOR = GetColorF(1.0f, 0.0f, 0.0f, 1.0f);//アンビエントカラー

/// <summary>
/// コンストラクタ
/// </summary>
TutorialEnemy::TutorialEnemy(const int _modelHandle)
	:pos(INIT_POS)
	, modelHandle(_modelHandle)
	, status(nullptr)
	, anim(nullptr)
	, shadow(nullptr)
	, blood(nullptr)
	, strongerUI(nullptr)
	, isDeath(false)
	, isInvincible(false)
	, frameCount(0)
	, isDamage(false)
	, initCount(0)
	, isRespawn(false)
	,changeColorTimer(nullptr)
	, bloodBaseDir(ORIGIN_POS)
	, isChangeColor(false)
	, isPrevColorChange(false)
	, materialNum(0)
	,animModel(0)
{
	int bloodParticle = 0;
	auto& load = Load::GetInstance();
	load.GetEnemyParticleData(&bloodParticle,&animModel);
	Create(bloodParticle);
}
/// <summary>
/// 作成（Init関数で行えない処理も行う）
/// </summary>
const void TutorialEnemy::Create(const int _bloodImage)
{
	blood = new BloodParticle(_bloodImage);
	status = new CharacterStatus();
	anim = new Animation();
	shadow = new Shadow();
	strongerUI = new StrongerUI();
	changeColorTimer = new Timer();
	MV1SetScale(modelHandle, SCALE);
	MV1SetRotationXYZ(modelHandle, ROTATE);
	MV1SetPosition(modelHandle, pos);
	changeColorTimer->Init(2);
	//アニメーションの追加
	anim->Add(animModel, 1);												//待機アニメーション
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/DeathAnim.mv1"), 1);	//死亡アニメーション
	//アタッチするアニメーション
	anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	//アニメーションのアタッチ
	anim->Attach(&modelHandle);
	SetUpCapsule();
}

/// <summary>
/// 初期化
/// </summary>
const void TutorialEnemy::Init()
{
	//必要なInitクラスの呼び出し
	changeColorTimer->Init(2);
	status->InitTutorialStatus(initCount);
	initCount++;
	//新しい座標の生成
	pos = INIT_POS;
	isDeath = false;
	//最大HPの設定
	status->InitWeakEnemyStatus(1.0f);
}
/// <summary>
/// 削除
/// </summary>
const void TutorialEnemy::Delete()
{
	if (status)
	{
		delete(status);
	}
	if (blood)
	{
		delete(blood);
	}
	if (strongerUI)
	{
		delete(strongerUI);
	}
	if (anim)
	{
		delete(anim);
	}

	if (shadow)
	{
		delete(shadow);
	}
	if (changeColorTimer)
	{
		delete(changeColorTimer);
	}

	modelHandle = 0;
}
/// <summary>
/// デストラクタ
/// </summary>
TutorialEnemy::~TutorialEnemy()
{
	Delete();
}
/// <summary>
/// 更新
/// </summary>
const void TutorialEnemy::Update()
{
	if (isInvincible)
	{
		blood->Init(bloodBaseDir, pos);
	}
	//もしHPをつけてHPが０になったら
	if (status->GetHp() <= 0)
	{
		//現在のアニメーションをやられたアニメーションにする
		if (anim->GetAnim() == static_cast<int>(AnimationType::DEATH) && anim->GetPlayTime() == 0.0f)
		{
			isDeath = true;
			pos = DESTROY_POS;
		}
		isDamage = true;
	}
	ChangeAnim();
	anim->Play(&modelHandle, 0.8f);
	if (isDeath)
	{
		if (!isRespawn)
		{
			frameCount++;
			if (frameCount > MAX_FRAME_COUNT)
			{
				pos = INIT_POS;
				isDeath = false;
				status->InitTutorialStatus(initCount);
				SetUpCapsule();
				isRespawn = true;
			}
		}
	}
	strongerUI->Update(pos, modelHandle, 6);
	blood->Update(60);
	ChangeColor();
	MV1SetPosition(modelHandle, pos);
}
/// <summary>
/// 描画
/// </summary>
const void TutorialEnemy::Draw(const float _playerLv)
{
	MV1DrawModel(modelHandle);
	if (isDamage)
	{
		strongerUI->Draw(_playerLv, status->GetLv());
	}
	if (status->GetHp() >= 0 && !isDamage)
	{
		blood->Draw();
	}
}
const void TutorialEnemy::DrawShadow(const int _stageModelHandle)
{
	shadow->Draw(_stageModelHandle,pos,1000.0f,20.0f);
}
/// <summary>
/// カプセル情報の構築
/// </summary>
const void TutorialEnemy::SetUpCapsule()
{
	capsule.topPos = pos;
	capsule.topPos.y += 30.0f;
	capsule.underPos = pos;
	capsule.radius = RADIUS;
	capsule.divNum = 16;
	capsule.difColor = CAPSULE_COLOR;
	capsule.spcColor = CAPSULE_COLOR;
	capsule.fillFlag = false;
}
/// <summary>
/// HPの計算
/// </summary>
const float TutorialEnemy::CalcHP(const float _atk, const VECTOR _attackPos)
{
	isInvincible = true;
	bloodBaseDir = VSub(pos, _attackPos);
	return status->CalcHP(_atk);
}
const void TutorialEnemy::InitExpToGive()
{
	status->InitExpToGive();
}
/// <summary>
///	アニメーションの変更
/// </summary>
const void TutorialEnemy::ChangeAnim()
{
	//もしHPが0以下になったら
	if (status->GetHp() <= 0)
	{
		anim->SetAnim(static_cast<int>(AnimationType::DEATH));
	}
	else
	{
		anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	}
}
/// <summary>
/// 色の変更
/// </summary>
const void TutorialEnemy::ChangeColor()
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
