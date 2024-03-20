//=======================================================
// @brief　レベルアップ・HP回復時パーティクル
//=======================================================
#pragma once
#include<DxLib.h>
#include<vector>
class StatusUpParticleBase;
class StatusUpParticle
{
public:
	StatusUpParticle(const float _prevPlayerLv);//コンストラクタ
	~StatusUpParticle();//デストラクタ

	const void Update(const VECTOR _targetPos,const bool _isBonfireMenu, const float _playerLv);//更新

	const void Draw(const bool _isBonfireMenu);//描画

private:
	/*静的定数*/
	static constexpr int MAX_FRAME_COUNT = 60;//最大フレーム
	/*メンバ変数*/
	std::vector<StatusUpParticleBase*> hpParticle;	//hpパーティクル
	std::vector<StatusUpParticleBase*> lvUpParticle;//レベルアップ時パーティクル

	VECTOR	targetPos;			//目標座標
	float	prevPlayerLv;		//前のプレイヤーレベル
	bool	isDrawLvupParticle;	//パーティクルを描画するか
	int		hpParticleImage;	//hpパーティクル画像ハンドル
	int		LvUPParticleImage;	//レベルアップパーティクル画像ハンドル
	int		lvUpFrameCount;		//パーティクル表示フレームカウント
	int		textImageHandle;	//レベルアップテキストパーティクル画像ハンドル
};

