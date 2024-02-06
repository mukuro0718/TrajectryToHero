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
	BloodParticle(const int _imageHandle);				//コンストラクタ
	~BloodParticle();				//デストラクタ
	void Init(const VECTOR _targetDir, const VECTOR _targetPos);//初期化
	void Update(const int _maxFrameNum);//更新
	void Draw();//描画
	void UpdateGravity();
private:
	/*静的定数*/
	static constexpr int PARTICLE_NUM = 100;//パーティクル数
	/*メンバ変数*/
	VECTOR initPos;	//初期描画座標
	std::vector<BloodParticleBase*> particle;
	int imageHandle;//画像ハンドル
	int frameCount;//フレームカウント
	bool isDraw;//描画しているか
};