//===========================================================================
//@brief ウィークエネミークラス/継承
//===========================================================================

#pragma once
#include"DxLib.h"
#include"EnemyBase.h"

class Timer;
class Animation;

class WeakEnemy :public EnemyBase
{
public:
	WeakEnemy(const VECTOR _spawnPos,const int _modelHandle);				//引数ありコンストラクタ
	~WeakEnemy();							//デストラクタ

	void Update()override;	//更新
	void Init()override;	//初期化
	void Move(const VECTOR _playerPos)override;	//移動
	void SetSpawnPos(const VECTOR _spawnPos) { spawnPos = _spawnPos; }
	const float GetRadius()const { return RADIUS; }

private:
	/*定数*/
	enum class AnimationType
	{
		RUN,        //走りアニメーション
		ATTACK,		//攻撃アニメーション
		IDLE,       //待機アニメーション
		DEATH,      //死亡アニメーション
	};
	/*静的定数*/
	static constexpr float	RADIUS		   = 10.0f;	//半径
	static constexpr int	RANDOM_X_RANGE = -100;	//敵の生成時に決めるX座標の範囲
	static constexpr float	HEIGHT		   = 30.0f;	//カプセルの高さ
	static constexpr float	SPHERE_RADIUS  = 3.0f;	//球の半径
	static const	 VECTOR MODEL_SCALE;			//初期モデルの拡大率
	static const	 VECTOR MODEL_ROTATE;			//初期モデルの回転値
	static const	 int	CAPSULE_COLOR;			//カプセルの色
	static const	 int	SPHERE_COLOR;			//球の色

	/*内部処理関数*/
	void   Create();						//作成
	void   Final();							//最終処理
	void   ChangeAnim();					//アニメーションの変更
	double ChangeRotate(VECTOR playerPos);	//角度の変更
	void   RandomWalk();//ランダムに歩く

	/*メンバ変数*/
	Animation*	anim;					//アニメーションクラス
	Timer*		invincibleTimer;		//無敵時間
	Timer*		restTimeAfterAttack;	//攻撃後休憩時間

	int  attackAnimLoopCount;	//攻撃追従可能時間
	bool isRestTime;			//休憩に入るかどうか

	bool isRandomWalk;
	bool isRandomRest;
	VECTOR randomWalkTargetPos;
	Timer* randomRest;

};


