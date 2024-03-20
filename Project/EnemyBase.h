//===========================================================================
//@brief エネミーベースクラス
//===========================================================================
#pragma once
#include"CharacterBase.h"
#include"CharacterStatus.h"
#include"Common.h"
class Timer;
class BloodParticle;
class StrongerUI;
class SpawnParticle;

class EnemyBase:public CharacterBase 
{
public:
	EnemyBase(const int _modelHandle);	// 引数ありコンストラクタ
	virtual ~EnemyBase();				// デストラクタ

	const void Draw(const VECTOR _playerPos);	//描画
	const void Final();					//削除
	const void FixMoveVec(const VECTOR _fixVec);

	//仮想関数（継承先で実装）
	virtual const void Update() = 0;	//更新
	virtual const void Init() = 0;					//初期化
	virtual const void Move(const VECTOR _playerPos) = 0;	//移動

	const float CalcHP(const float _atk, const VECTOR _attackerPos);//HP計算
	const void InitExpToGive();//経験値の初期化
	const void ChangeColor();//色の変更
	const void DrawStrongerUI(const float _playerLv,const int _modelHandle, const int _frameNum);//強敵マークの描画

	//getter/setter
	const VECTOR GetPos			()const { return pos;				}//座標のgetter
	const float  GetHp			()const { return status->GetHp();	}//ステータスクラスの体力のgetter
	const float  GetAtk			()const { return status->GetAtk();	}//ステータスクラスの攻撃力のgetter
	const bool	 GetIsDeath		()const { return isDeath;			}//死亡フラグのgetter
	const bool	 GetIsAttack	()const { return isAttack;			}//攻撃フラグのgetter
	const bool   GetIsHit		()const { return isHit;				}//攻撃ヒットフラグのgetter
	const int	 GetModelHandle	()const { return modelHandle;		}//モデルハンドルのgetter
	const void SetIsHit(const bool _isHitPlayer);
protected:
	enum class RandomSign
	{
		PLUS,//＋
		MINUS,//ー
	};
	/*静的定数*/
	static constexpr int RANDOM_RANGE = 7;//ランダムで生成する値の範囲
	static const VECTOR  DESTROY_POS;			//HPが０になったときこの座標に行く
	/*メンバ変数*/
	BloodParticle*	 blood;			//血しぶきパーティクル
	CharacterStatus* status;		//ステータス
	StrongerUI*		 strongerUI;	//強敵マーク
	SpawnParticle*	 spawnParticle;	//スポーンパーティクル

	VECTOR	spawnPos;				//スポーン位置
	VECTOR	bloodBaseDir;			//血しぶきパーティクルを飛ばす方向のもとになる方向
	float	maxHP;					//最大体力
	int		frameCount;				//フレームカウント
	bool	isFarmBossEnemyPos;		//ファーム時ボス座標をセットするかどうか
	bool	isAttackReadying;		//攻撃準備
	int		waitAttackFrameCount;	//攻撃待機フレームカウント数
	int		spawnFrameCount;		//スポーンしてからのフレーム数
	bool	isSpawn;				//スポーンしたか
private:
	/*定数*/
	static const COLOR_F CHANGE_DIF_COLOR;//ディフューズカラー
	static const COLOR_F CHANGE_SPC_COLOR;//スペキュラカラー
	static const COLOR_F CHANGE_EMI_COLOR;//エミッシブカラー
	static const COLOR_F CHANGE_AMB_COLOR;//アンビエントカラー

	static constexpr int RANDOM_X_RANGE = 300;		//ｘ座標
	static constexpr int RANDOM_Z_RANGE = 300;		//ｚ座標
	static constexpr int RANDOM_SIGN_RANGE = 1;		//符号

	/*メンバ変数*/
	bool isPrevColorChange;	//前に色を変更したか
	bool isChangeColor;		//色の変更をしているかどうか
	int materialNum;		//マテリアルの数
	Timer* changeColorTimer;//色変更タイマー
	std::vector<COLOR_F> difColorInfo;//ディフューズカラー情報
	std::vector<COLOR_F> spcColorInfo;//スペキュラカラー情報
	std::vector<COLOR_F> emiColorInfo;//エミッシブカラー情報
	std::vector<COLOR_F> ambColorInfo;//アンビエントカラー情報
};

