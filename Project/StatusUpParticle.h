#pragma once
#include<DxLib.h>
#include<vector>
class StatusUpParticleBase;
class StatusUpParticle
{
public:
	StatusUpParticle(const float _prevPlayerLv);//�R���X�g���N�^
	~StatusUpParticle();//�f�X�g���N�^

	//void Update(const VECTOR _targetPos,const int _atkUpCount, const int _agiUpCount, const int _defUpCount);//�X�V
	void Update(const VECTOR _targetPos,const bool _isBonfireMenu, const float _playerLv);//�X�V

	//void Draw();//�`��
	void Draw(const bool _isBonfireMenu);//�`��

private:
	/*�ÓI�萔*/
	static constexpr int MAX_FRAME_COUNT = 60;
	/*�����o�ϐ�*/
	int hpParticleImage;
	int LvUPParticleImage;
	float prevPlayerLv;
	int lvUpFrameCount;
	bool isDrawLvupParticle;
	int textImageHandle;
	VECTOR targetPos;
	std::vector<StatusUpParticleBase*> hpParticle;
	std::vector<StatusUpParticleBase*> lvUpParticle;
};

