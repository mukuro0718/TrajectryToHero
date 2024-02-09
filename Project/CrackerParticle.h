#pragma once
#include<DxLib.h>
#include<vector>
class CrackerParticleBase;

class CrackerParticle
{
public:
	CrackerParticle();//コンストラクタ
	~CrackerParticle();//デストラクタ
	void Init(const bool _isDrawRed, const bool _isDrawBlue, const bool _isDrawYellow);
	void Update();
	void Draw();
	void OffIsDraw();
private:
	/*静的定数*/
	static const int COLOR_RED;
	static const int COLOR_BLUE;
	static const int COLOR_YELLOW;
	static constexpr int MAX_RED_PARTICLE_NUM = 50;
	static constexpr int MAX_BLUE_PARTICLE_NUM = 50;
	static constexpr int MAX_YELLOW_PARTICLE_NUM = 50;
	static constexpr int FLAG_NUM = 3;
	static constexpr VECTOR INIT_POS = { 550.0f,250.0f,0.0f };
	/*メンバ変数*/
	std::vector<CrackerParticleBase*> redParticle;
	std::vector<CrackerParticleBase*> blueParticle;
	std::vector<CrackerParticleBase*> yellowParticle;
};

