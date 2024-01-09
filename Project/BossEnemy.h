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

	void Update()override;		//更新
	void Init  ()override;	//初期化
	void Move  (const VECTOR _playerPos)override;		//移動
	void UpdateUI();//UIの更新
	void DrawUI();//UIの描画

	const float GetRadius()const { return RADIUS; }

private:
	struct RangeOfAction//行動可能範囲
	{
		float LX = 0;
		float LZ = 0;
		float RX = 0;
		float RZ = 0;
	};
	/*定数*/
	enum class AnimationType//アニメーション
	{
		WALK,
		NORMAL_ATTACK,	//通常攻撃アニメーション
		ROTATE_ATTACK,	//通常攻撃アニメーション
		JUMP_ATTACK,	//ジャンプ攻撃アニメーション
		JUMP_IDLE,		//ジャンプ後待機アニメーション
		IDLE,			//待機アニメーション
		DEATH,			//死亡アニメーション
	};
	/*静的定数*/
	static constexpr float	RADIUS		   = 15.0f;	//半径
	static constexpr int	RANDOM_X_RANGE = -100;	//敵の生成時に決めるX座標の範囲
	static constexpr float HEIGHT = 30.0f;//Bossの高さ
	static constexpr RangeOfAction HP_FRAME_POS = { 100,990,1100,1010 };//HPフレーム座標
	static constexpr VEC2D HP_BAR_POS = { 100,990 };//HPフレーム座標
	static const	 VECTOR MODEL_SCALE;			//モデルの拡大率
	static const	 VECTOR MODEL_ROTATE;			//モデルの回転値
	static const	 VECTOR INIT_POS;				//初期座標
	static const	 int FONT_COLOR;//フォントカラー
	static const	 int CAPSULE_COLOR;//当たり判定用カプセルの色
	/*クラス*/
	Animation*	anim;					//アニメーションクラス
	Timer*		invincibleTimer;		//無敵時間クラス
	Timer*		restTimeAfterAttack;	//攻撃後休憩時間クラス
	Timer*		waitBeforeJumpAttack;	//ジャンプ攻撃待機時間
	Timer*		waitBeforeRotateAttack;	//回転攻撃待機時間
	Timer*		rotateAttackLoopTime;	//回転攻撃ループ時間
	/*内部処理関数*/
	void Create();//作成
	float ChangeRotate(VECTOR _playerPos);	//角度の変更
	void ChangeAnim();//アニメーションの変更
	void  Final();							//最終処理
	/*メンバ変数*/
	int  attackAnimLoopCount;	//攻撃アニメーションループ時間
	bool isRestTime;			//休憩に入るかどうか
	bool isJumpAttack;//ジャンプアタックを許可するかどうか（true:許可する false:許可しない）
	bool isRotateAttack;//ジャンプアタックを許可するかどうか（true:許可する false:許可しない
	int attackType;//攻撃のタイプ
	bool isJumpIdle;//ジャンプアイドルアニメーションを再生しているかどうか(true:再生している false:再生していない)
	VECTOR jumpAttackTargetPos;
	VECTOR spherePos;
	VEC2D nowHP;
	VEC2D prevHP;
	int font;	//フォントハンドル
	int frameImage;
	int hpImage;

};


