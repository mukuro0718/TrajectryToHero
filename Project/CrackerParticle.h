#pragma once
#include<DxLib.h>
#include<vector>
class CrackerParticleBase;

class CrackerParticle
{
public:
	CrackerParticle();	//コンストラクタ
	~CrackerParticle();	//デストラクタ

	const void Init(const bool _isDrawRed, const bool _isDrawBlue, const bool _isDrawYellow);//初期化
	const void Update();	//更新
	const void Draw();		//描画
	const void OffIsDraw();	//フラグを下す
private:
	/*静的定数*/
	static constexpr VECTOR INIT_POS				= { 550.0f,800.0f,0.0f };	//初期化座標
	static constexpr int	MAX_RED_PARTICLE_NUM	= 50;						//赤のパーティクルの数
	static constexpr int	MAX_BLUE_PARTICLE_NUM	= 50;						//青のパーティクルの数
	static constexpr int	MAX_YELLOW_PARTICLE_NUM = 50;						//黄色のパーティクルの数
	static constexpr int	FLAG_NUM				= 3;						//フラグの数
	static const int COLOR_RED;		//赤色
	static const int COLOR_BLUE;	//青色
	static const int COLOR_YELLOW;	//黄色
	/*メンバ変数*/
	std::vector<CrackerParticleBase*> redParticle;		//赤パーティクル
	std::vector<CrackerParticleBase*> blueParticle;		//青パーティクル
	std::vector<CrackerParticleBase*> yellowParticle;	//黄色パーティクル
};

