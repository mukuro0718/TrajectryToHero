//===========================================================================
//@brief エネミーベースクラス / 基底
//===========================================================================
#pragma once
#include"CharacterBase.h"
#include"CharacterStatus.h"
#include"Common.h"

//class EffectManager;
//class CharacterStatus;

class EnemyBase:public CharacterBase 
{
public:
	EnemyBase(){}						// コンストラクタ
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
	const float GetRadius()const { return RADIUS; }
	const int GetModelHandle()const { return modelHandle; }

	const float GetHp()const { return status->GetHp(); }
	const float GetAtk()const { return status->GetAtk(); }
	float CalcHP(const float _atk);//HP計算
	void InitExpToGive();
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

	CharacterStatus* status;
	float maxHP;						//最大体力
	bool isFarmBossEnemyPos;//ファーム時ボス座標をセットするかどうか
private:
	/*定数*/
	static constexpr int RANDOM_X_RANGE = 300;		//ｘ座標
	static constexpr int RANDOM_Z_RANGE = 300;		//ｚ座標
	static constexpr int RANDOM_SIGN_RANGE = 1;		//符号
	static constexpr float RADIUS = 5.0f;	//カプセルの半径
	static constexpr float HEIGHT = 30.0f;	//カプセルの高さ
	static const int CAPSULE_COLOR;			//カプセルの色
	static constexpr float SPHERE_RADIUS = 3.0f;	//球の半径
	static const int SPHERE_COLOR;					//球の色

	/*メンバ変数*/
	//EffectManager* effectManager;//エフェクト
};

