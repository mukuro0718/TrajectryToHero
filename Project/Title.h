//===========================================================================
//@brief タイトルクラス
//===========================================================================
#pragma once
#include"DxLib.h"
#include<vector>
#include"Common.h"
using namespace std;
class Title final
{
public:
	Title();	//コンストラクタ
	~Title();	//デストラクタ

	void Init();	//初期化
	void Update();	//更新
	void Draw();	//描画
	
	//タイトル終了フラグのgetter
	const bool GetIsTitleEnd()const { return isTitleEnd; }
	//シーン変更フラグのgetter
	const bool GetIsChangeScene()const { return isChangeScene; }
private:
	/*定数*/
	enum class CursorType//カーソルタイプ
	{
		ESCAPE,		//逃走アイコン
		GO,			//進むアイコン
		BRIEFING,	//状況説明アイコン
	};
	enum class ImageType//画像タイプ
	{
		ESCAPE_ICON,	//逃走アイコン
		GO_ICON,		//進むアイコン
		BRIEFING_ICON,	//説明アイコン
		TITLE_TEXT,		//タイトル文字
		CURSOR,			//カーソル
		BACKGROUND,		//背景
		BRIEFING_DATA,	//説明内容
		MOVE_BACKGROUND1,//背景画像
		MOVE_BACKGROUND2,
		MOVE_BACKGROUND3,
		MOVE_BACKGROUND4,
		MOVE_BACKGROUND5,
		MOVE_BACKGROUND6,
		MOVE_BACKGROUND7,
	};
	enum class MoveBackGround//背景画像
	{
		MOVE_BACKGROUND1,
		MOVE_BACKGROUND2,
		MOVE_BACKGROUND3,
		MOVE_BACKGROUND4,
		MOVE_BACKGROUND5,
		MOVE_BACKGROUND6,
		MOVE_BACKGROUND7,
	};
	/*静的定数*/
	static constexpr VEC2D	INIT_ESCAPE_ICON_POS						= { 148 ,880 }	 ;	//逃走アイコン初期化座標
	static constexpr VEC2D	INIT_GO_ICON_POS							= { 795 ,880 }	 ;	//ゲームスタートアイコン初期化座標
	static constexpr VEC2D	INIT_BRIEFING_ICON_POS						= { 1129,880 }	 ;	//説明アイコン初期化座標
	static constexpr VEC2D	INIT_BRIEFING_DATA_POS						= { 500 ,-50 }	 ;	//説明内容画像座標
	static constexpr VEC2D	INIT_TITLE_POS								= { 349 ,46	 }	 ;	//タイトル文字初期化座標
	static constexpr VEC2D	INIT_CURSOR_POS_OF_ESCAPE					= { 398 ,880 }	 ;	//逃走アイコン初期化座標
	static constexpr VEC2D	INIT_CURSOR_POS_OF_GO						= { 860 ,880 }	 ;	//ゲームスタートアイコン初期化座標
	static constexpr VEC2D	INIT_CURSOR_POS_OF_BRIEFING					= { 1450,880 }	 ;	//説明アイコン初期化座標
	static constexpr VEC2D	ORIGIN_POS_2D								= { 0	,0	 }	 ;	//2Dベクトル初期化座標
	static constexpr int	ADD_ALPHA_VALUE								= 2				 ;	//アルファ増加量
	static constexpr int	MAX_ALPHA_VALUE								= 200			 ;	//最大アルファ量
	static constexpr int	MIN_ALPHA_VALUE								= 0				 ;	//最小アルファ量
	static constexpr int	MAX_WAIT_COUNT								= 10			 ;	 //最大待機数
	static constexpr int	INIT_WAIT_COUNT								= 0				 ;	//初期化待機数
	static constexpr int	MAX_BACKGROUND_NUM							= 7				 ;	//背景画像数
	static constexpr int	MOVE_BACKGROUND_SPEED[MAX_BACKGROUND_NUM]	= {1,2,3,4,5,6,7};	//動く背景のスピード
	static constexpr int	MAX_BACKGROUND_POS							= 1920			 ;	//動く背景の最大座標
	static constexpr int	INIT_X_POS									= 0				 ;	//初期化Y座標
	static constexpr int	INIT_Y_POS									= 0				 ;	//初期化Y座標
	static constexpr int	MAX_Y_POS									= 5				 ;	//最大Y座標
	static constexpr int	MIN_Y_POS									= -20			 ;	//最小Y座標
	static constexpr int	MAX_Y_VALUE									= 1				 ;	//Y座標増加量
	static constexpr int	MIN_Y_VALUE									= -1			 ;	//Y座標増加量
	/*内部処理関数*/
	void ChangeCursor();		//カーソル座標の変更
	void DrawMoveBackGround();	//動く背景の描画
	void FloatCursor();			//カーソルの上下移動処理
	/*メンバ変数*/
	vector<int> image;									//画像ハンドル
	VEC2D		escapeIconPos;							//逃走アイコン座標
	VEC2D		goIconPos;								//ゲームスタートアイコン座標
	VEC2D		briefingIconPos;						//説明アイコン座標
	VEC2D		briefingDataImgPos;						//説明内容画像
	VEC2D		titlePos;								//タイトル文字座標
	VEC2D		cursorPos;								//カーソル座標
	VEC2D		moveBackGroundPos[MAX_BACKGROUND_NUM];	//動く背景1の座標
	bool		isInputState;							//入力状態フラグ（入力されている：trueそれ以外：false）
	bool		isSelectIcon;							//アイコンを選択しているかどうか
	bool		isShowBriefing;							//説明を表示しているかどうか
	bool		isTitleEnd;								//タイトル終了フラグ
	bool		isChangeScene;							//シーン切り替えフラグ
	int			alpha;									//アルファ値
	int			nowWaitCount;							//現在の待機カウント
	int			nowSelectIconType;						//選択しているアイコンの種類（0:escape 1:go 2:briefing）
	int			floatY;									//Y座標
	int			floatYAddValue;							//Y座標増加量
};
