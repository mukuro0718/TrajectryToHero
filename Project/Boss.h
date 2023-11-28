////===========================================================================
////@brief ボスエネミークラス/継承
////===========================================================================
//#pragma once
//#include"DxLib.h"
//#include"EnemyBase.h"
//class Timer;
//class Animation;
//class StatusInit;
//
//class Boss :public EnemyBase
//{
//public:
//	Boss() {};				//コンストラクタ
//	Boss(int _modelHandle);//引数ありコンストラクタ
//	~Boss();				//デストラクタ
//
//	void   Update(VECTOR _playerPos)override;		//更新
//	void   Init  ()override;	//初期化
//	VECTOR Move  (VECTOR _playerPos)override;		//移動
//private:
//	//定数
//	enum class AnimationType//アニメーション
//	{
//		WALK,
//		NORMAL_ATTACK,	//通常攻撃アニメーション
//		ROTATE_ATTACK,	//通常攻撃アニメーション
//		JUMP_ATTACK,	//ジャンプ攻撃アニメーション
//		JUMP_IDLE,		//ジャンプ後待機アニメーション
//		IDLE,			//待機アニメーション
//		DEATH,			//死亡アニメーション
//	};
//	static constexpr float	RADIUS		   = 10.0f;	//半径
//	static constexpr int	RANDOM_X_RANGE = -100;	//敵の生成時に決めるX座標の範囲
//	static const	 VECTOR MODEL_SCALE;			//モデルの拡大率
//	static const	 VECTOR MODEL_ROTATE;			//モデルの回転値
//	static const	 VECTOR INIT_POS;				//初期座標
//	//クラス
//	Animation*	anim;						//アニメーションクラス
//	Timer*		invincibleTimer;			//無敵時間クラス
//	Timer*		restTimeAfterAttack;		//攻撃後休憩時間クラス
//	StatusInit* statusInit;					//ステータス初期化クラス
//	//内部処理関数
//	float ChangeRotate(VECTOR _playerPos);	//角度の変更
//	void  Final();							//最終処理
//	//変数
//	int  attackAnimLoopCount;	//攻撃アニメーションループ時間
//	bool isRestTime;			//休憩に入るかどうか
//	VECTOR jumpAttackTargetPos;//ジャンプアタック中の目標座標
//	Timer* waitBeforeJunpAttack;//ジャンプ攻撃待機時間
//	Timer* waitBeforeRotateAttack;//回転攻撃待機時間
//	Timer* rotateAttackLoopTime;//回転攻撃ループ時間
//	bool isJumpAttack;//ジャンプアタックを許可するかどうか（true:許可する false:許可しない）
//	bool isRotateAttack;//ジャンプアタックを許可するかどうか（true:許可する false:許可しない
//	int attackType;//攻撃のタイプ
//	bool isJumpIdle;//ジャンプアイドルアニメーションを再生しているかどうか(true:再生している false:再生していない)
//
//
//};
//
//
