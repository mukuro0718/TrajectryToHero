////===========================================================================
////@brief ステータス管理クラス
//// ステータス計算(変更)、ステータス画像の描画
////===========================================================================
//
//#pragma once
//
//#include"DxLib.h"
//#include<vector>
//#include<string>
//#include"CharacterStatus.h"
//
//using namespace std;
//class Timer;
//class StatusManager final
//{
//public:
//
//	StatusManager();										// コンストラクタ
//	~StatusManager();										// デストラクタ
//	void CreateInstance();									// 作成
//	void Init();											// 初期化
//	void Delete();											// 画像ハンドル、クラスインスタンスの削除
//	void Update(CharacterStatus* status);	// 更新
//	void Draw();								// 描画
//	//レベルアップしたかのgetter/setter(プレイヤー側で設定)
//	const bool GetIsLvUP()const { return isLvUP; }
//	void SetIsLvUP(const bool isLvUP) { this->isLvUP = isLvUP; }
//	//メニューを開いているか
//	const bool GetIsShowMenu()const { return isShowMenu; }
//
//private:
//	//クラス・構造体
//	struct VEC2D
//	{
//		int x = 0;
//		int y = 0;
//	};
//	//定数
//	enum class SelectStatus//選択しているステータスの種類
//	{
//		ATK,//攻撃力
//		DEF,//防御力
//		AGI,//素早さ
//	};
//	static constexpr float	IMG_SIZE				 = 5.0f;			//画像サイズ
//	static constexpr float	IMG_ANGLE				 = 0.0f;			//回転率
//	static constexpr float	LV_UP_ADD_VALUE			 = 1.0f;			//レベルアップ時ステータス増加量
//	static constexpr int	MODIFIABLE_STATUS_COUNT  = 3;				//変更可能なステータスの数
//	static constexpr int	FONT_SIZE				 = 128;				//フォントのサイズ
//	static constexpr int	FONT_THICK				 = 64;				//フォントの太さ
//	static constexpr int	BACKGROUND_WIDTH		 = 900;				//背景画像の横
//	static constexpr int	BACKGROUND_HEIGHT		 = 980;				//背景画像の縦
//	static const	 int	FONT_COLOR_RED;								//フォントの色
//	static const	 int	FONT_COLOR_WHITE;							//フォントの色
//	static const	 VECTOR SET_DRAW_POS;								//描画座標
//	static constexpr VEC2D	BACKGROUND_POS			 = { 510,50 };		//メニュー背景座標
//	static constexpr VEC2D	STATUS_UP_TEXT_POS		 = { 650,100 };		//ステータスアップテキスト座標
//	static constexpr VEC2D	STATUS_TEXT_POS[MODIFIABLE_STATUS_COUNT] =	//ボタン座標
//	{
//		{850,300},
//		{850,500},
//		{850,700},
//	};
//	//内部処理関数
//	void ChangeSelectStatus();//選択しているステータスの変更
//	void UpSelectStatus(CharacterStatus* status);//選択しているステータスの上昇
//	void ChangeBlendRateDrawText(const int nowSelectStatus, const int statusType);//ブレンド率を変えて描画
//	//変数
//	float  prevLv;				//前回のレベル
//	bool   isShowMenu;			//メニューを表示しているか
//	bool   isLvUP;				//レベルアップしたか
//	bool   isFinalSelectStatus;	//最終的に選択したステータス
//	bool   isInputPad;			//スティック入力しているか（連続入力の防止）
//	int    lvUpCount;			//現在のレベルアップ数（今のレベルから前のレベルを引く）
//	int    nowSelectStatus;		//現在選択しているステータス
//	int	   backGroundImage;		//背景画像ハンドル
//	Timer* inputWaitTimer;		//入力待機時間
//	int	   statusFontHandle;	//LvUp時メニュー用フォントハンドル
//};
//
//
