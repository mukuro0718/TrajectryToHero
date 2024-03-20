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

	const void Update()override;						//更新
	const void Init()override;							//初期化
	const void Move(const VECTOR _playerPos)override;	//移動
	const void NewStatus(const float _playerLv);		//新しいステータスを決める

	const void SetSpawnPos(const VECTOR _spawnPos) { spawnPos = _spawnPos; }//スポーン位置を決める
	/*getter*/
	const float GetRadius()const { return RADIUS; }
private:
	/*定数*/
	enum class AnimationType
	{
		RUN,			//走りアニメーション
		COMBO_ATTACK,	//攻撃アニメーション
		NORMAL_ATTACK,	//攻撃アニメーション
		IDLE,			//待機アニメーション
		DEATH,			//死亡アニメーション
		WALK,			//歩く
		FRIGHTENING,	//怯みアニメーション
	};
	enum class AttackType
	{
		COMBO_ATTACK,		//攻撃アニメーション
		NORMAL_ATTACK,
	};
	/*静的定数*/
	static constexpr int TOTAL_ANIM_NUM	   = 7;		//アニメーションの合計
	static constexpr float	RADIUS		   = 10.0f;	//半径
	static constexpr float	HEIGHT		   = 30.0f;	//カプセルの高さ
	static constexpr float	SPHERE_RADIUS  = 3.0f;	//球の半径

	static const	 VECTOR MODEL_SCALE;	//初期モデルの拡大率
	static const	 VECTOR MODEL_ROTATE;	//初期モデルの回転値
	static const	 int	CAPSULE_COLOR;	//カプセルの色
	static const	 int	SPHERE_COLOR;	//球の色

	/*内部処理関数*/
	void   Create();								//作成
	void   Delete();								//最終処理
	void   ChangeAnim();							//アニメーションの変更
	void   RandomWalk();							//ランダムに歩く
	double ChangeRotate(const VECTOR _playerPos);	//角度の変更

	/*メンバ変数*/
	Animation*	anim;					//アニメーションクラス
	Timer*		invincibleTimer;		//無敵時間
	Timer*		restTimeAfterAttack;	//攻撃後休憩時間

	float animPlayTime[TOTAL_ANIM_NUM];	//アニメーション再生時間
	int  attackAnimLoopCount;			//攻撃追従可能時間
	bool isRestTime;					//休憩に入るかどうか
	bool isWalk;						//歩いているか
	bool isRandomWalk;					//ランダムで移動しているか
	bool isRandomRest;					//ランダム移動後に休憩しているか
	int attackType;						//攻撃の種類
	VECTOR randomWalkTargetPos;			//ランダムで歩く方向
	Timer* randomRest;					//ランダム休憩時間

};


