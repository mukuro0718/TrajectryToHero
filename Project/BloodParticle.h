//===========================================================================
//@brief 拡散するエフェクトクラス
// 血しぶきを出す
//===========================================================================
#pragma once
#include<DxLib.h>
#include<vector>

class BloodParticleBase;

class BloodParticle
{
public:
	BloodParticle(const int _imageHandle);	//コンストラクタ
	~BloodParticle();						//デストラクタ

	const void Init(const VECTOR _targetDir, const VECTOR _targetPos);	//初期化
	const void Update(const int _maxFrameNum);							//更新
	const void Draw();													//描画
private:
	/*静的定数*/
	static constexpr int PARTICLE_NUM = 100;//パーティクル数
	/*メンバ変数*/
	std::vector<BloodParticleBase*> particle;//パーティクル

	VECTOR	initPos;	//初期描画座標
	bool	isDraw;		//描画しているか
	int		imageHandle;//画像ハンドル
	int		frameCount;	//フレームカウント
};