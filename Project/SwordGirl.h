//===========================================================================
//@brief プレイヤークラス / 継承
// 
//===========================================================================
#pragma once

#include<DxLib.h>
#include<vector>
#include"PlayerBase.h"

class Animation;
class Timer;
class SwordGirl :public PlayerBase
{
public:
	SwordGirl(const int _modelHandle,const int _frameImage,const int _hpImage,const int _expImage, const int _font);	//引数ありコンストラクタ
	~SwordGirl();						//デストラクタ
	//基本動作
	const void Update()override;	//更新
	const void Init()override;		//初期化

	const void Move(const VECTOR _cameraToPlayer);		//移動処理
	const void Attack();								//攻撃処理
	const void Death();									//死亡処理
	const void AnimChange();							//アニメーションの変更
	const void UpdateUI();								//UIの更新
	const void DrawUI();								//UIの描画
	const void ChangeColor();							//色の変更
	const void ReSpawn();								//リスポーン
	const void PhysicalRecovery();						//体力回復
	const void DrawMenu();								//ステータスメニューの表示
	const void StatusUpdate(const VECTOR _bonfirePos);	//ステータスの更新
	const void FixMoveVec(const VECTOR _fixVec);		//移動修正
	const void KnockBack();								//のけぞり
	//ノックバックの開始
	const void CountInvincibleTimer();					//無敵時間の計測
	/*getter/setter*/
	const void	 SetIsInvincible	()		{ isInvincible = false; }
	const VECTOR GetPos				()const { return pos;		}//座標のgetter
	const void   InitPos			()		{ pos = ORIGIN_POS; }//座標の初期化
	const bool	 GetIsAttack		()const { return isAttack;  }//攻撃フラグのgetter
	const bool   GetIsMove			()const { return isMove;	}//移動フラグのgetter
	const bool   GetIsHit			()const {return isHit; }	 //攻撃ヒットフラグのgetter
	const bool   GetIsBonfireMenu	()const;	//ステータスクラスの焚火メニュー表示フラグのgetter
	const bool   GetIsShowStatusMenu();			//ステータスクラスのisShowMenuのgetter
	const int	 GetAtkUpCount		()const;	//ステータスクラスの焚火メニュー表示フラグのgetter
	const int	 GetAgiUpCount		()const;	//ステータスクラスの焚火メニュー表示フラグのgetter
	const int	 GetDefUpCount		()const;	//ステータスクラスの焚火メニュー表示フラグのgetter
	const void	 OnKnockBack(const VECTOR _targetPos);
private:
	/*構造体・列挙体*/
	struct CollisionSetUpInfo//コリジョン構築用情報
	{
		int frameIndex = 0;	//コリジョン情報を構築したいフレームの番号
		int xDivNum = 0;	//Xコリジョン分割数
		int yDivNum = 0;	//yコリジョン分割数
		int zDivNum = 0;	//zコリジョン分割数
	};
	struct RangeOfAction//行動可能範囲
	{
		float LX = 0;
		float LZ = 0;
		float RX = 0;
		float RZ = 0;
	};
	enum class AnimationType//アニメーションの種類
	{
		RUN,        //走りアニメーション
		ATTACK,		//攻撃アニメーション
		FRIGHTENING,//怯みアニメーション
		AVOIDANCE,	//回避アニメーション
		IDLE,       //待機アニメーション
		DEATH,      //死亡アニメーション
	};
	enum class ComboType
	{
		NONE,
		ONE,
		TWO,
		FINISH,
	};
	/*静的定数*/
	static constexpr RangeOfAction		HP_FRAME_POS				 = { 90,60,390,90 }		;//HPフレーム座標
	static constexpr RangeOfAction		EXP_FRAME_POS				 = { 90,100,390,130 }	;//EXPフレーム座標
	static constexpr CollisionSetUpInfo PLAYER_COLL_INFO			 = { 66,1,1,1 }			;//プレイヤーコリジョン情報
	static constexpr RangeOfAction		PLAYER_RANGE_OF_ACTION		 = { 451,510, -450,-840};//プレイヤー行動可能範囲
	static constexpr InputAnalogStick	NONE_INPUT_VALUE			 = { 0,0 }				;//スティック入力がない
	static constexpr VEC2D				HP_BAR_POS					 = { 90,60 }			;//HPフレーム座標
	static constexpr VEC2D				EXP_BAR_POS					 = { 90,100, }			;//EXPフレーム座標
	static constexpr float				ANGLE_VALUE					 = 30.0f				;//角度の増加量
	static constexpr float				PLAYER_RADIUS				 = 8.0f					;//無敵時間
	static constexpr float				PLAYETR_Y_POS				 = 10.0f				;//プレイヤーY座標
	static constexpr float				LV_MULT_VALUE				 = 10.0f				;//レベル倍率
	static constexpr float				FIRST_ANIM_PLAY_TIME		 = 0.0f					;//アニメーション初期再生時間
	static constexpr int				STAY_TIMER_TARGET_TIME		 = 3000					;//待機時間
	static constexpr int				INVINCIBLE_TIMER_TARGET_TIME = 2					;//無敵時間
	static constexpr int				TOTAL_ANIM_NUM				 = 6					;//アニメーション数
	static const VECTOR  FIRST_MODEL_SCALE;	//モデルの初期拡大率
	static const VECTOR  FIRST_MODEL_ROTATE;//モデルの初期回転値
	static const VECTOR  FIRST_POS;			//プレイヤー初期化座標
	static const COLOR_F CHANGE_DIF_COLOR;	//ディフューズカラー
	static const COLOR_F CHANGE_SPC_COLOR;	//スペキュラカラー
	static const COLOR_F CHANGE_EMI_COLOR;	//エミッシブカラー
	static const COLOR_F CHANGE_AMB_COLOR;	//アンビエントカラー
	static const int	 FONT_COLOR;		//フォントカラー
	
	/*内部処理関数*/
	void Create();	//生成
	
	/*メンバ変数*/
	Animation*		 anim;				//アニメーションクラス
	Timer*			 stayTimer;			//待ち時間クラス
	Timer*			 invincibleTimer;	//無敵時間

	std::vector<COLOR_F> difColorInfo;	//ディフューズカラー情報
	std::vector<COLOR_F> spcColorInfo;	//スペキュラカラー情報
	std::vector<COLOR_F> emiColorInfo;	//エミッシブカラー情報
	std::vector<COLOR_F> ambColorInfo;	//アンビエントカラー情報
	
	InputAnalogStick inputLeftStick;	//左スティック入力構造体
	VECTOR playerDir;					//プレイヤーの向いている方向（移動したときのみ保存）
	VECTOR prevPos;						//前回の座標
	VECTOR knockBackMoveVec;			//移動ベクトルの逆行列
	VEC2D nowHP;						//現在の体力
	VEC2D prevHP;						//前回の体力
	VEC2D nowEXP;						//現在の経験値
	float multSpeed;					//スピードにかける値
	float avoidSpeed;					//回避中のスピード
	float animPlayTime[TOTAL_ANIM_NUM];	//アニメーション再生時間
	bool isMove;						//移動しているかどうか
	bool isAvoidance;					//回避フラグ
	bool isKnockBack;					//のけぞりフラグ
	bool isChangeColor;					//色の変更をしているかどうか
	int materialNum;					//マテリアルの数
	int font;							//フォントデータ
	int frameImage;						//フレーム画像
	int hpImage;						//体力画像
	int expImage;						//経験値画像
	int knockBackFrameCount;			//ノックバック時のフレーム数
};
