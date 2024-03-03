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

	void SetSpawnPos(const VECTOR _spawnPos) { spawnPos = _spawnPos; }
	const float GetRadius()const { return RADIUS; }
	const void NewStatus(const float _playerLv);

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
	static constexpr float	RADIUS		  = 10.0f;	//半径
	static constexpr float	HEIGHT		  = 30.0f;	//カプセルの高さ
	static constexpr float	SPHERE_RADIUS = 3.0f;	//球の半径
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
	Animation* anim;								//アニメーションクラス
	Timer* restTimeAfterAttack;						//攻撃後休憩時間
	Timer* invincibleTimer;							//無敵時間
	Timer* preliminaryOperation;
	static constexpr int TOTAL_ANIM_NUM = 4;
	float animPlayTime[TOTAL_ANIM_NUM];
	int attackAnimLoopCount;//攻撃回数
	bool isRestTime;		//休憩に入るかどうか
	bool isPreliminaryOperation;
	bool isRandomWalk;			//放浪しているかどうか
	bool isRandomRest;			//放浪後、休憩しているかどうか
	VECTOR randomWalkTargetPos;	//放浪先目標座標
	Timer* randomRest;			//放浪休憩時間

};


