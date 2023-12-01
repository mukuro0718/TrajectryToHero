//===========================================================================
//@brief プレイヤーマネージャークラス / 管理
//===========================================================================
#pragma once
#include"DxLib.h"
#include"SwordGirl.h"
class PlayerManager
{
public:
	PlayerManager();//コンストラクタ
	~PlayerManager();//デストラクタ

	void Init();//初期化（ウェーブ切り替え時に使用する）
	void Move(const VECTOR _cameraToPlayer);//移動
	void Attack();//攻撃
	void Update();//更新
	void Draw();//描画
	void Final();//削除
	void LvUP();
	//bool IsStoppingUpdate();
	//座標のgetter
	const VECTOR GetPos() { return player->GetPos(); }
	//モデルハンドルのgetter
	const int GetModelHandle()const { return player->GetModelHandle(); }
	//無敵フラグのgetter
	const bool GetIsInvincible()const { return player->GetIsInvincible(); }
	//カプセル情報のgetter
	const CapsuleInfo GetCapsuleInfo()const { return player->GetCapsuleInfo(); }
	//球情報のgetter
	const SphereInfo GetSphereInfo()const { return player->GetSphereInfo(); }
	//死亡フラグのgetter
	const bool GetIsDeath()const { return player->GetIsDeath(); }
	//攻撃力のgetter
	const float GetAtk()const { return player->GetAtk(); }
	const float GetHp()const { return player->GetHp(); }
	/*HACK:
	const ~ ~()constは
	最初のconst = 定数値を返す
	最後のconst = このメンバ関数は値をいじらない
	*/
	//HP計算
	void CalcHP(const float _atk);
	//レベルアップ処理
	void CalcExp(const float _expToGive);
private:
	int model;

	SwordGirl* player;
	bool isDrawImg;
};

