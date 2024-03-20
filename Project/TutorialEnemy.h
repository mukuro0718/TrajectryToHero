//===================================================
//@brief チュートリアルエネミークラス
// チュートリアルでのエネミーの動きを実装する
//===================================================
#pragma once
#include<DxLib.h>
#include"Common.h"
#include<vector>


class WeakEnemy;
class CharacterStatus;
class Animation;
class Shadow;
class StrongerUI;
class BloodParticle;
class Timer;

class TutorialEnemy final
{
public:
	TutorialEnemy(const int _modelHandle);	//コンストラクタ
	~TutorialEnemy();						//デストラクタ
	
	const void  Create(const int _bloodImage);											//作成（Init関数で行えない処理も行う）
	const void  Init();												//初期化
	const void  Delete();											//削除
	const void  Draw(const float _playerLv);						//描画
	const void  Update();											//更新
	const void  DrawShadow(const int _stageModelHandle);			//影の描画
	const void  InitExpToGive();									//経験値の初期化
	const void  OffIsDamage() { isDamage = false; }					//ダメージフラグを下す
	const float CalcHP(const float _atk, const VECTOR _attackPos);	//HPの計算
	/*各フラグのgetter/setter*/
	const bool GetIsDamage()	const { return isDamage; }
	const bool GetIsRespawn()	const { return isRespawn; }
	const bool GetIsDeath()		const { return isDeath; }
	const float GetRadius()		const { return RADIUS; }
	const VECTOR GetPos()		const { return pos; }
	const CapsuleInfo GetCapsuleInfo()const { return capsule; }

private:
	/*構造体・列挙体*/
	enum class AnimationType
	{
		IDLE,
		DEATH,
	};
	/*静的定数*/
	static constexpr VECTOR  SCALE		= { 0.2f,0.2f,0.2f };						//拡大率
	static constexpr VECTOR  ROTATE		= { 0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f };//回転率
	static constexpr VECTOR  DESTROY_POS = { 500.0f, 500.0f, 500.0f };				//死亡したときの座標
	static constexpr VECTOR  INIT_POS	= { 0.0f,0.0f,-150.0f };					//座標の初期化
	static constexpr float	 RADIUS		= 10.0f;									//半径
	static constexpr int	 MAX_FRAME_COUNT = 60;									//最大フレーム数
	
	static const	 int	 CAPSULE_COLOR;		//カプセルの色
	static const	 COLOR_F CHANGE_DIF_COLOR;	//ディフューズカラー
	static const	 COLOR_F CHANGE_SPC_COLOR;	//スペキュラカラー
	static const	 COLOR_F CHANGE_EMI_COLOR;	//エミッシブカラー
	static const	 COLOR_F CHANGE_AMB_COLOR;	//アンビエントカラー
	/*内部処理関数*/
	const void SetUpCapsule();	//カプセル情報の設定
	const void ChangeAnim();	//アニメーションの変更
	const void ChangeColor();	//色の変更
	/*メンバ変数*/
	CharacterStatus* status;		  //ステータス
	BloodParticle*	 blood;			  //血しぶき
	StrongerUI*		 strongerUI;	  //強敵UI
	Animation*		 anim;			  //アニメーション
	Shadow*			 shadow;		  //影
	Timer*			 changeColorTimer;//色変更タイマー
	
	std::vector<COLOR_F> difColorInfo;	//ディフューズカラー情報
	std::vector<COLOR_F> spcColorInfo;	//スペキュラカラー情報
	std::vector<COLOR_F> emiColorInfo;	//エミッシブカラー情報
	std::vector<COLOR_F> ambColorInfo;	//アンビエントカラー情報

	CapsuleInfo capsule;	//カプセル情報
	VECTOR pos;				//座標
	VECTOR bloodBaseDir;	//血しぶきパーティクルを飛ばす方向のもとになる方向
	bool isDeath;			//死亡フラグ
	bool isInvincible;		//無敵フラグ
	bool isDamage;			//ダメージフラグ
	bool isRespawn;			//リスポーンフラグ
	bool isPrevColorChange;	//前のフレームで色を変更していたか
	bool isChangeColor;		//色の変更をしているかどうか
	int frameCount;			//経過したフレーム
	int modelHandle;		//モデルのハンドル
	int initCount;			//何回初期化したか
	int materialNum;		//マテリアルの数
	int animModel;			//アニメーション用モデル
};

