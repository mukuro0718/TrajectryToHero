#pragma once
#include<DxLib.h>
#include<vector>
class StatusUpParticleBase;
class StatusUpParticle
{
public:
	StatusUpParticle();//�R���X�g���N�^
	~StatusUpParticle();//�f�X�g���N�^

	//void Update(const VECTOR _targetPos,const int _atkUpCount, const int _agiUpCount, const int _defUpCount);//�X�V
	void Update(const VECTOR _targetPos,const bool _isBonfireMenu);//�X�V

	//void Draw();//�`��
	void Draw(const bool _isBonfireMenu);//�`��

private:
	/*�ÓI�萔*/
	static const int COLOR_RED;
	static const int COLOR_BLUE;
	static const int COLOR_YELLOW;
	static const int COLOR_GREEN;
	int redNum;
	int blueNum;
	int yellowNum;
	/*�����o�ϐ�*/

	std::vector<StatusUpParticleBase*> particle;
};

