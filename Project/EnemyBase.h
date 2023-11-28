////===========================================================================
////@brief エネミーベースクラス / 基底
////===========================================================================
//#pragma once
//#include "DxLib.h"
//#include"Common.h"
//enum RandomSign
//{
//	PLUS,//＋
//	MINUS,//ー
//};
//class EffectManager;
//class EnemyBase 
//{
//public:
//	EnemyBase(){}						// コンストラクタ
//	EnemyBase(int _humanModelHandle);	// 引数ありコンストラクタ
//	virtual ~EnemyBase();				// デストラクタ
//
//	void Draw(VECTOR _playerPos);	//描画
//	void Final();					//削除
//	VECTOR NewRandomPos();				//新しい座標をランダムで返す
//
//	//仮想関数（継承先で実装）
//	virtual void Update(VECTOR _playerPos) = 0;	//更新
//	virtual void Init() = 0;					//初期化
//	virtual VECTOR Move(VECTOR _playerPos) = 0;	//移動
//
//	//共通ベースのgetter/Setter
//	const CharacterBase& GetBase() const { return base; }
//	void SetBase(const CharacterBase _set) { base = _set; }
//	//ステータスのgetter/Setter
//	const CharacterStatus& GetStatus() const { return status; }
//	void SetStatus(const CharacterStatus _set) { status = _set; }
//	//ポジションのgetter/setter
//	const VECTOR& GetPos() const { return base.pos; }
//	void SetPos(const VECTOR _set) { base.pos = _set; }
//	////当たり判定のsetter
//	const bool GetIsDeath()const { return base.isDeath; }
//	//半径のsetter
//	const int GetRadius()const { return RADIUS; }
//protected:
//	/*静的定数*/
//	static constexpr int SPAWN_POINT_NUM = 8;			//スポーンポイント数
//	static constexpr int RANDOM_RANGE = 7;//ランダムで生成する値の範囲
//	static const VECTOR  DESTROY_POS;			//HPが０になったときこの座標に行く
//	
//	//内部処理関数
//	void RandomWalk();
//	/*メンバ変数*/
//
//	CharacterBase   base;
//	CharacterStatus status;
//	float maxHP;						//最大体力
//	bool isFarmBossEnemyPos;//ファーム時ボス座標をセットするかどうか
//	VECTOR spawnPoint[SPAWN_POINT_NUM];	//スポーンポイント
//private:
//	/*定数*/
//	static constexpr int RANDOM_X_RANGE = 300;		//ｘ座標
//	static constexpr int RANDOM_Z_RANGE = 300;		//ｚ座標
//	static constexpr int RANDOM_SIGN_RANGE = 1;		//符号
//	static constexpr int RADIUS = 5;	//半径
//	/*メンバ変数*/
//	EffectManager* effectManager;//エフェクト
//};
//
