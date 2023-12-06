//===========================================================================
//@brief キャラクターベースクラス
// キャラクターオブジェクトに必ず実装しておきたいものを定義
//===========================================================================

#pragma once
#include<DxLib.h>
#include"Common.h"


class CharacterBase
{
public:
	CharacterBase();//コンストラクタ
	virtual ~CharacterBase();//デストラクタ
	void SetUpCapsule(const VECTOR _pos,const float _height,const float _radius,const int _color,const int _flag);//デバッグ用カプセルの位置設定
	void SetUpSphere(const VECTOR _pos, const float _radius, const int _color, const int _flag);//デバッグ用スフィアの位置設定
	void DrawCapsule(const CapsuleInfo _capsuleInfo);//デバッグ用カプセルの描画
	void DrawSphere(const SphereInfo _sphereInfo);//デバッグ用カプセルの描画

	//ポジションのgetter/setter
	const VECTOR& GetPos() const { return pos; }
	//モデルハンドルのgetter
	const int GetModelHandle()const { return modelHandle; }
	//無敵フラグのgetter
	const bool GetIsInvincible()const { return isInvincible; }
	//カプセル情報のgetter
	const CapsuleInfo GetCapsuleInfo()const { return capsuleInfo; }
	//球情報のgetter
	const SphereInfo GetSphereInfo()const { return sphereInfo; }
	//死亡フラグのgetter
	const bool GetIsDeath()const { return isDeath; }
	//移動量のgetter
	const VECTOR GetMoveVec()const { return moveVec; }
protected:
	/*静的定数*/
	static constexpr int INIT_MODELHANDLE = 0;
	/*メンバ変数*/
	int				modelHandle;	//モデルハンドル
	VECTOR			pos;			//座標
	VECTOR			moveVec;		//移動量
	VECTOR			rotate;			//回転率
	VECTOR			scale;			//スケール
	CapsuleInfo		capsuleInfo;	//カプセル情報
	SphereInfo		sphereInfo;		//球情報
	bool			isHit       ;	//当たったか
	bool			isInvincible;   //無敵状態
	bool			isMove;			//移動したか
	bool			isAttack;		//攻撃したか
	bool			isDeath;

private:
	void Init();
};

