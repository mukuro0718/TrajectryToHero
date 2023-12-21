//===========================================================================
//@brief プレイヤーマネージャークラス / 管理
//===========================================================================
#pragma once
#include"DxLib.h"
#include"SwordGirl.h"
class BlurScreen;

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
	void StatusUpdate();//ステータス更新
	void FixMoveVec(const VECTOR _fixVec);
	void DrawShadow(const int _stageModelHandle);
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
	//攻撃フラグのgetter
	const bool GetIsAttack()const { return player->GetIsAttack(); }
	//死亡フラグのgetter
	const bool GetIsDeath()const { return player->GetIsDeath(); }
	//攻撃力のgetter
	const float GetAtk()const { return player->GetAtk(); }
	const float GetHp()const { return player->GetHp(); }
	const bool GetIsShowStatusMenu() { return player->GetIsShowStatusMenu(); }
	//移動量のgetter
	const VECTOR GetMoveVec()const { return player->GetMoveVec(); }
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
	static constexpr float SHADOW_SIZE = 20.0f;
	static constexpr float SHADOW_HEIGHT = 1000.0f;
	int model;
	int frameImage;
	int hpImage;
	int expImage;
	SwordGirl* player;

	bool isDrawImg;
};

