//===========================================================================
//@brief ステータスクラス
//===========================================================================
#include"CharacterStatus.h"

/// <summary>
/// コンストラクタ
/// </summary>
CharacterStatus::CharacterStatus()
{

}
/// <summary>
/// デストラクタ
/// </summary>
CharacterStatus::~CharacterStatus()
{

}
/// <summary>
/// 雑魚敵ステータスの初期設定
/// </summary>
void CharacterStatus::InitWeakEnemyStatus()
{
	lv = 10.0f;			//レベルのセット
	hp = 50.0f;		//体力のセット
	atk = 10.0f;			//攻撃力のセット
	def = 50.0f;			//防御力のセット
	agi = 1.0f;			//素早さのセット
	expToGive = 50.0f;	//倒されたとき与える経験値のセット
	exp = 0.0f;			//経験値のセット
	needExp = 0.0f;
	maxHp = hp;
}
/// <summary>
/// 中ボスステータスの初期設定
/// </summary>
void CharacterStatus::InitStrongEnemyStatus()
{
	lv = 10.0f;			//レベルのセット
	hp = 100.0f;		//体力のセット
	atk = 20.0f;			//攻撃力のセット
	def = 60.0f;			//防御力のセット
	agi = 2.0f;			//素早さのセット
	expToGive = 150.0f;	//倒されたとき与える経験値のセット
	exp = 0;			//経験値のセット
	needExp = 0.0f;
	maxHp = hp;
}
/// <summary>
/// ボスステータスの初期設定
/// </summary>
void CharacterStatus::InitBossEnemyStatus()
{
	lv			= 10.0f;	//レベルのセット
	hp			= 300.0f;	//体力のセット
	atk			= 30.0f;	//攻撃力のセット
	def			= 70.0f;	//防御力のセット
	agi			=2.0f;		//素早さのセット
	expToGive = 100.0f;		//倒されたとき与える経験値のセット
	exp			= 0.0f;		//経験値のセット
	needExp = 0.0f;
	maxHp = hp;
}

/// <summary>
/// プレイヤーステータスの初期設定
/// </summary>
void CharacterStatus::InitPlayerStatus()
{
	lv			 = 1.0f;	//レベルのセット
	hp			 = 30.0f;	//体力のセット
	atk		 = 3.0f;	//攻撃力のセット
	def		 = 1.0f;	//防御力のセット
	agi		 = 1.5f;	//素早さのセット
	expToGive = 0.0f;	//倒されたとき与える経験値のセット
	exp		 = 0.0f;	//経験値のセット
	needExp = 0.0f;
	maxHp = hp;
}

/// <summary>
/// HP計算
/// </summary>
void CharacterStatus::CalcHP(const float _atk)
{
	hp -= atk * def * 0.05f;
}