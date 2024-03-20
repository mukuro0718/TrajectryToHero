//===========================================================================
//@brief ストロングエネミークラス/継承
// 魔法で攻撃をする
//===========================================================================

#pragma once
#include"DxLib.h"
#include"EnemyBase.h"
class Timer;
class Animation;
class Explosion;

class StrongEnemy :public EnemyBase
{
public:
	StrongEnemy(const VECTOR _spawnPos,const int modelHandle);	//引数ありコンストラクタ
	~StrongEnemy();												//デストラクタ

	const void Update()override;						//更新
	const void Init()override;							//初期化
	const void Move(const VECTOR playerPos)override;	//移動

	const void DrawAttackRange();				//攻撃範囲の描画
	const void NewStatus(const float _playerLv);//新しいステータスの設定
	const void DrawMagicSphere();				//魔法陣の描画
	/*getter/setter*/
	const float GetRadius()const { return RADIUS; }
	void SetSpawnPos(const VECTOR _spawnPos) { spawnPos = _spawnPos; }
private:
	/*定数*/
	enum class AnimationType
	{
		RUN,        //走りアニメーション
		HOMING,		//ホーミング魔法
		EXPLOSION,  //爆発魔法
		IDLE,       //待機アニメーション
		DEATH,      //死亡アニメーション
	};
	enum class AttackType
	{
		HOMING_MAGIC,
		EXPROSION_MAGIC
	};
	/*静的定数*/
	static constexpr int			MAGIC_CIRCLE_VERTEX_NUM					= 4;		//魔法陣用ポリゴン頂点数
	static constexpr int			MAGIC_CIRCLE_POLYGON_NUM				= 2;		//魔法陣用ポリゴン数
	static constexpr int			TOTAL_ANIM_NUM							= 5;		//アニメーション数
	static constexpr int			HOMING_MAGIC_VERTEX_NUM					= 9;		//ホーミング魔法用頂点数
	static constexpr int			HOMING_MAGIC_POLYGON_NUM				= 12;		//ポリゴン数
	static constexpr int			BEFORE_HOMING_MAGIC_WAIT_FRAME_COUNT	= 80;		//攻撃前待機時間
	static constexpr int			AFTER_HOMING_MAGIC_WAIT_FRAME_COUNT		= 120;		//攻撃後待機時間
	static constexpr float			MAX_EXPLOSION_MAGIC_RADIUS				= 50.0f;	//爆発魔法最大半径
	static constexpr float			BEFORE_EXPLOSION_MAGIC_WAIT_FRAME_COUNT = 100;		//攻撃前待機カウント
	static constexpr float			RADIUS									= 8.0f;		//半径
	static constexpr float			HEIGHT									= 30.0f;	//カプセルの高さ
	static constexpr float			SPHERE_RADIUS							= 10.0f;	//球の半径
	static constexpr unsigned short MAGIC_CIRCLE_INDEX[MAGIC_CIRCLE_POLYGON_NUM * 3] =	//ポリゴンインデックス
	{
		0, 1, 2,
		0, 2, 3,
	};
	static constexpr unsigned short HOMING_MAGIC_INDEX[HOMING_MAGIC_POLYGON_NUM * 3] =	//ポリゴンインデックス
	{
		0,1,2,
		0,2,3,
		0,3,4,
		0,4,1,
		1,4,8,
		1,8,5,
		2,1,5,
		2,5,6,
		3,2,6,
		3,6,7,
		4,3,7,
		4,7,8,
	};
	static const VERTEX3D INIT_MAGIC_CIRCLE_VERTEX;									//初期化用頂点
	static const VERTEX3D INIT_VERTEX_FOR_HOMING_MAGIC;								//初期化用頂点
	static const VECTOR	  VERTEX_OFFSET_FOR_HOMING_MAGIC[HOMING_MAGIC_VERTEX_NUM];	//魔法を表示するための頂点補正値
	static const VECTOR	  MODEL_SCALE;												//初期モデルの拡大率
	static const VECTOR   MODEL_ROTATE;												//初期モデルの回転値
	static const VECTOR   MAGIC_CIRCLE_VERTEX_OFFSET[MAGIC_CIRCLE_VERTEX_NUM];		//魔法陣頂点補正値
	static const VECTOR   MAGIC_CIRCLE_VERTEX_OFFSET_2[MAGIC_CIRCLE_VERTEX_NUM];	//魔法陣頂点補正値
	static const int	  CAPSULE_COLOR;											//カプセルの色
	static const int	  HOMING_MAGIC_COLOR;										//ホーミング魔法の色
	static const int	  EXPLOSION_MAGIC_COLOR;									//爆発魔法の色
	/*内部処理関数*/
	void	Create();						//作成
	void	Final();						//最終処理
	void	ChangeAnim();					//アニメーションの変更
	double	ChangeRotate(VECTOR playerPos);	//角度の変更
	void	RandomWalk();					//ランダムに歩く
	void	Attack(const VECTOR _playerPos);//攻撃
	/*メンバ変数*/
	Animation*	anim;				//アニメーションクラス
	Explosion*	explosion;			//爆発魔法
	Timer*		restTimeAfterAttack;//攻撃後休憩時間
	Timer*		invincibleTimer;	//無敵時間
	Timer*		randomRest;			//放浪休憩時間

	VERTEX3D magicCircleVertex[MAGIC_CIRCLE_VERTEX_NUM];	//頂点情報
	VERTEX3D magicCircleVertex2[MAGIC_CIRCLE_VERTEX_NUM];	//頂点情報
	VERTEX3D homingMagicVertex[HOMING_MAGIC_POLYGON_NUM];	//頂点情報

	VECTOR randomWalkTargetPos;			//放浪先目標座標
	VECTOR homingMoveVec;				//ホーミング移動ベクトル
	float animPlayTime[TOTAL_ANIM_NUM];	//アニメーション再生時間
	float explosionMagicRadius;			//爆発魔法半径
	bool isRestTime;					//休憩に入るかどうか
	bool isRandomWalk;					//放浪しているかどうか
	bool isRandomRest;					//放浪後、休憩しているかどうか
	bool isInitMagicExp;				//爆発魔法を初期化したか
	int magicCircleTexture;				//魔法陣テクスチャ
	int attackType;						//攻撃の種類
	int attackAnimLoopCount;			//攻撃回数
	int magicCircleTexture2;			//魔法陣テクスチャ
	int magicWaitFrameCount;			//魔法待機フレーム数
};


