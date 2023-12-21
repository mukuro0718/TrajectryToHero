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
	SwordGirl(){};						//コンストラクタ
	SwordGirl(const int _modelHandle,const int _frameImage,const int _hpImage,const int _expImage);	//引数ありコンストラクタ
	~SwordGirl();						//デストラクタ
	void Update()override;				//更新
	void Init()override;				//初期化
	void Move(const VECTOR cameraToPlayer);//移動処理
	void Attack();//攻撃処理
	void Death();//死亡処理
	void AnimChange();//アニメーションの変更
	void CountInvincibleTimer();//無敵時間の計測
	const VECTOR GetPos()const { return pos; }//座標のgetter
	const bool GetIsAttack()const { return isAttack; }//攻撃フラグのgetter
	void DrawMenu();//ステータスメニューの表示
	const bool GetIsShowStatusMenu();//ステータスクラスのisShowMenuを返す
	void StatusUpdate();//ステータスの更新
	void FixMoveVec(const VECTOR _fixVec);//移動修正
	void UpdateUI();//UIの更新
	void DrawUI();//UIの描画
	void ChangeColor();//色の変更
private:
	/*定数*/
	enum class AnimationType//アニメーションの種類
	{
		RUN,        //走りアニメーション
		ATTACK,		//攻撃アニメーション
		IDLE,       //待機アニメーション
		DEATH,      //死亡アニメーション
	};
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
	static const	 VECTOR FIRST_MODEL_SCALE;	//モデルの初期拡大率
	static const	 VECTOR FIRST_MODEL_ROTATE;	//モデルの初期回転値
	static const	 VECTOR FIRST_POS;//プレイヤー初期化座標
	static const COLOR_F CHANGE_DIF_COLOR;//ディフューズカラー
	static const COLOR_F CHANGE_SPC_COLOR;//スペキュラカラー
	static const COLOR_F CHANGE_EMI_COLOR;//エミッシブカラー
	static const COLOR_F CHANGE_AMB_COLOR;//アンビエントカラー
	static constexpr VEC2D HP_FRAME_POS = { 0,0 };//HPフレーム座標
	static constexpr VEC2D EXP_FRAME_POS = { 0,0 };//EXPフレーム座標
	static constexpr CollisionSetUpInfo PLAYER_COLL_INFO			 = { 66,1,1,1 }			;//プレイヤーコリジョン情報
	static constexpr RangeOfAction		PLAYER_RANGE_OF_ACTION		 = { 451,-450,510,-400 };//プレイヤー行動可能範囲
	static constexpr InputAnalogStick	NONE_INPUT_VALUE			 = { 0,0 }				;//スティック入力がない
	static constexpr int				STAY_TIMER_TARGET_TIME		 = 3000					;//待機時間
	static constexpr int				INVINCIBLE_TIMER_TARGET_TIME = 2					;//無敵時間
	static constexpr float				ANGLE_VALUE					 = 30.0f				;//角度の増加量
	static constexpr float				PLAYER_RADIUS				 = 8.0f					;//無敵時間
	static constexpr float				PLAYETR_Y_POS				 = 10.0f				;//プレイヤーY座標
	static constexpr float				LV_MULT_VALUE				 = 10.0f				;//レベル倍率
	static constexpr float				FIRST_ANIM_PLAY_TIME		 = 0.0f					;//アニメーション初期再生時間
	/*内部処理関数*/
	void Create();	//生成
	/*メンバ変数*/
	Animation*		anim;			//アニメーションクラス
	Timer*			stayTimer;		//待ち時間クラス
	Timer*			invincibleTimer;//無敵時間
	InputAnalogStick inputLeftStick;	//左スティック入力構造体
	int prevLv;
	bool isMove;//移動しているかどうか
	bool isChangeColor;//色の変更をしているかどうか
	int materialNum;//マテリアルの数
	std::vector<COLOR_F> difColorInfo;//ディフューズカラー情報
	std::vector<COLOR_F> spcColorInfo;//スペキュラカラー情報
	std::vector<COLOR_F> emiColorInfo;//エミッシブカラー情報
	std::vector<COLOR_F> ambColorInfo;//アンビエントカラー情報
	int frameImage;
	int hpImage;
	int expImage;
};
