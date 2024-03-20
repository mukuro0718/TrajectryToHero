//===========================================================================
//@brief ボスエネミークラス/継承
//===========================================================================
#pragma once
#include"DxLib.h"
#include"EnemyBase.h"
class Timer;
class Animation;

class BossEnemy :public EnemyBase
{
public:
	BossEnemy(const VECTOR _spawnPos,const int _modelHandle,const int _frameImage, const int _hpImage,const int _font);//引数ありコンストラクタ
	~BossEnemy();				//デストラクタ

	const void Update()override;						//更新
	const void Init  ()override;						//初期化
	const void Move  (const VECTOR _playerPos)override;	//移動

	const void Attack(const float _targetVecSize,const VECTOR _targetPos);	//攻撃
	const void Rest();														//休憩
	const void UpdateUI();													//UIの更新
	const void DrawUI();													//UIの描画
	const void Flagging() { isInvincible = false; }							//フラグを下す
	const void PhysicalRecovery();											//体力の回復
	/*getter*/
	const float GetRadius()const { return RADIUS; }
	const bool GetIsMeteoAttack() { return isMeteoAttack; }
	const bool GetIsExplosionAttack() { return isExplosionAttack; }
private:
	/*構造体・列挙体*/
	struct RangeOfAction//行動可能範囲
	{
		float LX = 0;
		float LZ = 0;
		float RX = 0;
		float RZ = 0;
	};
	enum class AnimationType//アニメーション
	{
		WALK,			//歩きアニメーション
		NORMAL_ATTACK,	//通常攻撃アニメーション
		STRONG_ATTACK,	//強い攻撃アニメーション
		ROTATE_ATTACK,	//回転攻撃アニメーション
		JUMP_ATTACK,	//ジャンプ攻撃アニメーション
		METEO_ATTACK,	//隕石攻撃
		EXPLOSION_ATTACK,//爆発攻撃
		IDLE,			//待機アニメーション
		DEATH,			//死亡アニメーション
	};
	enum class AttackType//攻撃の種類
	{
		NORMAL,
		STRONG,
		ROTATE,
		JUMP,
		METEO,
		EXPLOSION,
	};
	/*静的定数*/
	static constexpr RangeOfAction	HP_FRAME_POS			   = { 100,990,1100,1010 };	//HPフレーム座標
	static constexpr VEC2D			HP_BAR_POS				   = { 100,990 };			//HPフレーム座標
	static constexpr float			CLOSE_ATTACK_RANGE		   = 50.0f;					//近距離攻撃範囲
	static constexpr float			MIDDLE_ATTACK_RANGE		   = 150.0f;				//中距離攻撃範囲
	static constexpr float			RADIUS					   = 15.0f;					//半径
	static constexpr float			LONG_ATTACK_RANGE		   = 300.0f;				//遠距離攻撃範囲
	static constexpr float			HEIGHT					   = 30.0f;					//Bossの高さ
	static constexpr int			RANDOM_RANGE_CLOSE_ATTACK  = 10;					//近距離攻撃用ランダム範囲
	static constexpr int			NORMAL_ATTACK_RANGE		   = 5;						//通常攻撃の範囲
	static constexpr int			STRONG_ATTACK_RANGE		   = 8;						//強い攻撃の範囲
	static constexpr int			RANDOM_RANGE_MIDDLE_ATTACK = 1;						//中距離攻撃用ランダム範囲
	static constexpr int			RANDOM_X_RANGE			   = -100;					//敵の生成時に決めるX座標の範囲
	static constexpr int			TOTAL_ANIM_NUM			   = 9;						//アニメーション合計数

	static const VECTOR MODEL_ROTATE;	//モデルの回転値
	static const VECTOR INIT_POS;		//初期座標
	static const VECTOR MODEL_SCALE;	//モデルの拡大率
	static const int FONT_COLOR;		//フォントカラー
	static const int CAPSULE_COLOR;		//当たり判定用カプセルの色
	/*クラス*/
	Animation*	anim;					//アニメーションクラス
	Timer*		invincibleTimer;		//無敵時間クラス
	Timer*		restTimeAfterAttack;	//攻撃後休憩時間クラス
	Timer*		rotateAttackLoopTime;	//回転攻撃ループ時間

	/*内部処理関数*/
	void Create();								//作成
	float ChangeRotate(const VECTOR _playerPos);//角度の変更
	void ChangeAnim();							//アニメーションの変更
	void Delete();								//最終処理
	/*メンバ変数*/
	bool isJumpAttack;					//ジャンプアタックを許可するかどうか（true:許可する false:許可しない）
	bool isRotateAttack;				//ジャンプアタックを許可するかどうか（true:許可する false:許可しない
	bool isMeteoAttack;					//隕石攻撃をするか
	bool isExplosionAttack;				//爆発攻撃をするか
	bool isNormalAttack;				//通常攻撃
	bool isStrongAttack;				//強い攻撃
	bool isFly;							//ジャンプ攻撃で飛ぶ
	bool isOnGround;					//着地しているか
	int flyFrameCount;					//何フレーム空を飛ぶか
	float attackRadius;					//攻撃半径
	float jumpAtttackFlySpeed;			//ジャンプ攻撃の飛ぶ速さ
	float animPlayTime[TOTAL_ANIM_NUM];	//アニメーション再生時間
	int  attackAnimLoopCount;			//攻撃アニメーションループ時間
	bool isRestTime;					//休憩に入るかどうか
	int attackType;						//攻撃のタイプ
	bool isJumpIdle;					//ジャンプアイドルアニメーションを再生しているかどうか(true:再生している false:再生していない)
	VECTOR jumpAttackTargetPos;			//ジャンプ攻撃座標
	VECTOR spherePos;					//球座標
	VEC2D nowHP;						//現在のHP
	VEC2D prevHP;						//前のHP
	int font;							//フォントハンドル
	int frameImage;						//フレーム画像
	int hpImage;						//HP画像
};


