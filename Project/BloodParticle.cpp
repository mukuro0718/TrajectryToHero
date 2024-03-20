//===========================================================================
//@brief �g�U����G�t�F�N�g�N���X
// �G�t�F�N�g�̏������ƈʒu�X�V�ƕ`����s��
//===========================================================================
#include"BloodParticle.h"
#include"Common.h"
#include"BloodParticleBase.h"
#include"Load.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
BloodParticle::BloodParticle(const int _imageHandle)
	:initPos(ORIGIN_POS)
	, imageHandle(0)
	, frameCount(0)
	, isDraw(false)
{
	//�萔���N���X�̃C���X�^���X���쐬����
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		particle.push_back(new BloodParticleBase(_imageHandle));
	}
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
BloodParticle::~BloodParticle()
{
	particle.clear();
}

/// <summary>
/// ������
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
/// �X�V
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
/// �`��
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