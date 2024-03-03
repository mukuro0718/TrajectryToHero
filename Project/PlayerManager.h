//===========================================================================
//@brief プレイヤーマネージャークラス / 管理
//===========================================================================
#pragma once
#include"DxLib.h"
#include"SwordGirl.h"
class OperationUI;

class PlayerManager
{
public:
	PlayerManager();//コンストラクタ
	~PlayerManager();//デストラクタ

	void Init();//初期化（ウェーブ切り替え時に使用する）
	void Move(const VECTOR _cameraToPlayer);//移動
	void Attack();//攻撃
	void Update();//更新
	void Draw(const VECTOR _bonfirePos);//描画
	const void DrawMenu();
	void Final();//削除
	void StatusUpdate(const VECTOR _bonfirePos);//ステータス更新
	void FixMoveVec(const VECTOR _fixVec);
	void DrawShadow(const int _stageModelHandle);

	/*HACK:
	const ~ ~()constは
	最初のconst = 定数値を返す
	最後のconst = このメンバ関数は値をいじらない
	*/
	
	const CapsuleInfo GetCapsuleInfo()		const { return player->GetCapsuleInfo();	  }//カプセル情報のgetter
	const SphereInfo  GetSphereInfo()		const { return player->GetSphereInfo();		  }//カプセル情報のgetter
	const VECTOR	  GetPos()				const { return player->GetPos();			  }//座標のgetter
	const VECTOR	  GetMoveVec()			const { return player->GetMoveVec();		  }//移動量のgetter
	const float		  GetAtk()				const { return player->GetAtk();			  }//攻撃力のgetter
	const float		  GetHp()				const { return player->GetHp();				  }//体力のgetter
	const float		  GetLv()				const { return player->GetLv();				  }//LVのgetter
	const bool		  GetIsInvincible()		const { return player->GetIsInvincible();	  }//無敵フラグのgetter
	const bool		  GetIsAttack()			const { return player->GetIsAttack();		  }//攻撃フラグのgetter
	const bool		  GetIsDeath()			const { return player->GetIsDeath();		  }//死亡フラグのgetter
	const bool		  GetIsShowStatusMenu()	const { return player->GetIsShowStatusMenu(); }//レベルアップメニューの表示フラグのgetter
	const bool		  GetIsBonfireMenu()	const { return player->GetIsBonfireMenu();	  }//かがり火メニューの表示フラグのgetter
	const bool		  GetIsHit()			const { return player->GetIsHit();			  }//攻撃ヒットフラグのgetter
	const void		  SetIsInvincible()			  { player->SetIsInvincible(); }
	const void		  OnKnockBack(const VECTOR _targetVec) { player->OnKnockBack(_targetVec); }//ノックバックの開始
	const int		  GetModelHandle()		const { return player->GetModelHandle();	  }//モデルハンドルのgetter
	const int		  GetAtkUpCount()		const {	return player->GetAtkUpCount();		  }//攻撃力上昇回数のgetter
	const int		  GetAgiUpCount()		const {	return player->GetAgiUpCount();		  }//素早さ上昇回数のgetter
	const int		  GetDefUpCount()		const {	return player->GetDefUpCount();		  }//防御力上昇回数のgetter
	const int GetAttackNum()const { return player->GetAttackNum(); }
	//ステータス処理
	void CalcHP(const float _atk, const VECTOR _attackerPos);//HP計算
	void CalcExp(const float _expToGive);
	void ReSpawn();//体力回復
	void PhysicalRecovery();//体力回復
	const void InitPos() const;
private:
	static constexpr float SHADOW_SIZE = 20.0f;
	static constexpr float SHADOW_HEIGHT = 1000.0f;
	int model;
	int frameImage;
	int hpImage;
	int expImage;
	SwordGirl* player;
	OperationUI* opeUI;
	int font;
	bool isDrawImg;
};

