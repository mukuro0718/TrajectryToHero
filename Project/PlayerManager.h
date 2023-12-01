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

private:
	int model;

	SwordGirl* player;
	bool isDrawImg;
};

