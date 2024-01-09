//===========================================================================
//@brief ストロングエネミークラス/継承
//===========================================================================

#pragma once
#include"DxLib.h"
#include"EnemyBase.h"
class Timer;
class Animation;
class StrongEnemy :public EnemyBase
{
public:
	StrongEnemy(const VECTOR _spawnPos,const int modelHandle);	//引数ありコンストラクタ
	~StrongEnemy();					//デストラクタ

	void Update()override;	//更新
	void Init()override;	//初期化
	void Move(const VECTOR playerPos)override;	//移動

private:
	//定数
	enum class AnimationType
	{
		RUN,        //走りアニメーション
		ATTACK,		//攻撃アニメーション
		IDLE,       //待機アニメーション
		DEATH,      //死亡アニメーション
	};
	static constexpr float  RADIUS		   = 10.0f;	//半径
	static constexpr int    RANDOM_X_RANGE = -100;	//敵の生成時に決めるX座標の範囲
	static const	 VECTOR MODEL_SCALE;				//モデルの拡大率
	static const	 VECTOR MODEL_ROTATE;				//モデルの回転値
	//クラス
	Animation* anim;								//アニメーションクラス
	Timer* restTimeAfterAttack;						//攻撃後休憩時間
	Timer* invincibleTimer;							//無敵時間
	//内部処理関数
	float ChangeRotate(VECTOR playerPos);			//角度の変更
	void Final();									//最終処理
	//変数
	int attackAnimLoopCount;//攻撃回数
	bool isRestTime;		//休憩に入るかどうか
};


