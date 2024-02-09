//===========================================================================
//@brief エネミーベースクラス / 基底
//===========================================================================
#pragma once
#include"CharacterBase.h"
#include"CharacterStatus.h"
#include"Common.h"
class Timer;
class BloodParticle;
class StrongerUI;

class EnemyBase:public CharacterBase 
{
public:
	EnemyBase(int _modelHandle);	// 引数ありコンストラクタ
	virtual ~EnemyBase();				// デストラクタ

	void Draw(VECTOR _playerPos);	//描画
	void Final();					//削除
	void FixMoveVec(const VECTOR _fixVec);

	//仮想関数（継承先で実装）
	virtual void Update() = 0;	//更新
	virtual void Init() = 0;					//初期化
	virtual void Move(const VECTOR _playerPos) = 0;	//移動

	//ポジションのgetter/setter
	const VECTOR& GetPos() const { return pos; }
	////当たり判定のsetter
	const bool GetIsDeath()const { return isDeath; }
	const bool GetIsAttack()const { return isAttack; }
	//半径のsetter
	const int GetModelHandle()const { return modelHandle; }

	const float GetHp()const { return status->GetHp(); }
	const float GetAtk()const { return status->GetAtk(); }
	float CalcHP(const float _atk, const VECTOR _attackerPos);//HP計算
	void InitExpToGive();
	void ChangeColor();//色の変更

	const void DrawStrongerUI(const float _playerLv,const int _modelHandle, const int _frameNum);
protected:
	enum class RandomSign
	{
		PLUS,//＋
		MINUS,//ー
	};
	/*静的定数*/
	static constexpr int RANDOM_RANGE = 7;//ランダムで生成する値の範囲
	static const VECTOR  DESTROY_POS;			//HPが０になったときこの座標に行く
	VECTOR spawnPos;
	//内部処理関数
	void RandomWalk();
	/*メンバ変数*/
	BloodParticle* blood;//血しぶきパーティクル
	CharacterStatus* status;
	StrongerUI* strongerUI;
	float maxHP;						//最大体力
	bool isFarmBossEnemyPos;//ファーム時ボス座標をセットするかどうか
	VECTOR bloodBaseDir;//血しぶきパーティクルを飛ばす方向のもとになる方向
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
	bool isPrevColorChange;
	bool isChangeColor;//色の変更をしているかどうか
	int materialNum;//マテリアルの数
	Timer* changeColorTimer;//色変更タイマー
	std::vector<COLOR_F> difColorInfo;//ディフューズカラー情報
	std::vector<COLOR_F> spcColorInfo;//スペキュラカラー情報
	std::vector<COLOR_F> emiColorInfo;//エミッシブカラー情報
	std::vector<COLOR_F> ambColorInfo;//アンビエントカラー情報
	//EffectManager* effectManager;//エフェクト
};

