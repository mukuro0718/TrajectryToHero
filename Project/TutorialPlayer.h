//================================
// チュートリアルプレイヤークラス
// ゲームシーンのSwordGirlクラスをもとに
// チュートリアル独自の改良を加える
//================================
#pragma once
#include<DxLib.h>
class TutorialPlayer final
{
public:
	TutorialPlayer(const int _model);//コンストラクタ
	~TutorialPlayer();//デストラクタ
	void Update();				//更新
	void Init();				//初期化
	const VECTOR GetPos()const { return pos; }//座標のgetter
	const bool GetIsAttack()const { return isAttack; }//攻撃フラグのgetter
	const bool GetIsMove()const { return isMove; }//移動フラグのgetter
	void DrawMenu();//ステータスメニューの表示
	const bool GetIsShowStatusMenu();//ステータスクラスのisShowMenuを返す
	void FixMoveVec(const VECTOR _fixVec);//移動修正
	void DrawUI();//UIの描画
private:
	/*メンバ変数*/
	VECTOR pos;
	bool isAttack;
	bool isMove;
	/*内部処理関数*/
	void Move(const VECTOR cameraToPlayer);//移動処理
	void Attack();//攻撃処理
	void Death();//死亡処理
	void AnimChange();//アニメーションの変更
	void CountInvincibleTimer();//無敵時間の計測
	void StatusUpdate(const VECTOR _bonfirePos);//ステータスの更新
	void UpdateUI();//UIの更新
	void ChangeColor();//色の変更
};


