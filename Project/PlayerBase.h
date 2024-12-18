//===========================================================================
//@brief プレイヤーベースクラス
//モデルの描画とコピーしたモデルのアンロードを行う
//===========================================================================
#pragma once
#include"DxLib.h"
#include"CharacterBase.h"
class StatusManager;
class EffectManager;
class CharacterStatus;
class Timer;
class SwordTrail;
class BloodParticle;
class StatusUI;

class PlayerBase :public CharacterBase
{
public:
	PlayerBase(const int _modelHandle);	// 引数ありコンストラクタ
	virtual ~PlayerBase();				// デストラクタ
	const void Draw();						//描画
	const void Delete();						//削除
	//仮想関数（継承先で実装）
	virtual const void Update() = 0;			//更新
	virtual const void Init() = 0;			//初期化

	const void CalcHP(const float _atk, const VECTOR _attackerPos);//HP計算
	const void CalcExp(const float _expToGive);//レベルアップ処理
	const float GetAtk();
	const float GetHp();
	const float GetLv();
	const void TutorialStatusReset();
protected:
	/*静的定数*/
	static constexpr float WALK_SPEED = 5.0f;	//歩く速さ
	/*メンバ変数*/
	CharacterStatus*	status;		//ステータス
	BloodParticle*		blood;		//血しぶきパーティクル
	SwordTrail*			swordTrail;	//剣の軌跡

	VECTOR	cameraToPlayer;			//カメラからプレイヤーへのベクトル
	VECTOR	bloodBaseDir;			//血しぶきパーティクルの方向のもとになる方向
	bool	isAttackReadying;		//攻撃準備
	int		waitAttackFrameCount;	//攻撃待機フレームカウント数
private:
	/*静的定数*/
	static constexpr float	CAPSULE_HEIGHT		= 30.0f;//カプセルの高さ
	static constexpr float	CAPSULE_RADIUS		= 10.0f;//カプセルの半径
	static constexpr float	SPHERE_RADIUS		= 20.0f;//スフィアの半径
	static constexpr float	INIT_DEGREES		= 0.0f;	//初期度数
	static constexpr float	ADD_DEGREES_VALUE	= 1.6f;	//X度数増加量

	static const	 int	SPHERE_COLOR;				//スフィアの色
	static const	 int	CAPSULE_COLOR;				//カプセルの色
	static const	 VECTOR SPHERE_POS_OFFSET;			//スフィアオフセット
	static const	 VECTOR CENTER_POS_OFFSET;			//中心座標オフセット
	/*メンバ変数*/
	StatusUI* statusUI;	//ステータスUI

	VECTOR	centerPos;	//中心座標
	float	degrees;	//度数
};

