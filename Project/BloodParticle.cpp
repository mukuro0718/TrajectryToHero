//===========================================================================
//@brief 拡散するエフェクトクラス
// エフェクトの初期化と位置更新と描画を行う
//===========================================================================
#include"BloodParticle.h"
#include"Common.h"
#include"BloodParticleBase.h"
#include"Load.h"
/// <summary>
/// コンストラクタ
/// </summary>
BloodParticle::BloodParticle(const int _imageHandle)
	:initPos(ORIGIN_POS)
	, imageHandle(0)
	, frameCount(0)
	, isDraw(false)
{
	//定数分クラスのインスタンスを作成する
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		particle.push_back(new BloodParticleBase(_imageHandle));
	}
}
/// <summary>
/// デストラクタ
/// </summary>
BloodParticle::~BloodParticle()
{
	particle.clear();
}

/// <summary>
/// 初期化
/// </summary>
const void BloodParticle::Init(const VECTOR _targetDir, const VECTOR _targetPos)
{
	if (!isDraw)
	{
		for (int i = 0; i < PARTICLE_NUM; i++)
		{
			particle[i]->Init(_targetDir,_targetPos);
		}
		isDraw = true;
		frameCount = 0;
	}
}
/// <summary>
/// 更新
/// </summary>
const void BloodParticle::Update(const int _maxFrameNum)
{
	if (isDraw)
	{
		for (int i = 0; i < PARTICLE_NUM; i++)
		{
			particle[i]->Update();
		}
	}
	if (frameCount > _maxFrameNum)
	{
		isDraw = false;
	}
	else
	{
		frameCount++;
	}
}
/// <summary>
/// 描画
/// </summary>
const void BloodParticle::Draw()
{
	if (isDraw)
	{
		for (int i = 0; i < PARTICLE_NUM; i++)
		{
			particle[i]->Draw();
		}
	}
}