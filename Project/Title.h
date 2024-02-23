//===========================================================================
//@brief タイトルクラス
//===========================================================================
#pragma once
#include"DxLib.h"
#include<vector>
#include"Common.h"
using namespace std;

class TutorialStage;
class Camera;
class SwordGirl;
class OperationUI;
class TutorialEnemy;
class Collision;
class StatusUpParticle;

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
	struct Vec2d//2次元ベクトル構造体
	{
		int x = 0;
		int y = 0;
	};
	struct DrawRect//描画範囲構造体
	{
		int lx = 0;
		int ly = 0;
		int rx = 0;
		int ry = 0;
	};
	enum class TitleData//画像タイプ
	{
		LOGO,
		BACKGROUND,
		A_BUTTON,
		B_BUTTON,
		X_BUTTON,
		R_STICK,
		L_STICK,
		BOSS_UI,
	};
	enum class FontType
	{
		PLAYER,
		LOGO,
		TEXT,
		TEXT_2,
	};
	enum class PlayerData//画像タイプ
	{
		MODEL,
		HP,
		EXP,
		FRAME,
	};
	enum class EnemyData//画像タイプ
	{
		MODEL,
		UI,
	};
	enum class StageData//画像タイプ
	{
		GROUND,
		GATE,
		PORTAL,
		SKYDOME,
		CAMPFIRE,
		FLAME,
	};
	static constexpr int TITLE_DATA_NUM = 2;		//タイトルロゴ
	static constexpr int TITLE_FONT_DATA_NUM = 3;	//フォント
	static constexpr int TITLE_PLAYER_DATA_NUM = 4;	//プレイヤー
	static constexpr int TITLE_ENEMY_DATA_NUM = 2;	//エネミー
	static constexpr int TITLE_STAGE_DATA_NUM = 6;	//ステージ
	static constexpr DrawRect TITLE_LOGO_POS = { 200, 200, 1720, 700 };
	static constexpr Vec2d START_ICON_POS = { 700 ,800 };//スタートアイコン座標
	static constexpr int MAX_ALPHA_VALUE = 255;//最大アルファ値
	static constexpr int MIN_ALPHA_VALUE = 0;//最小アルファ値
	static constexpr int ADD_ALPHA_VALUE = 5;//アルファ値増加量
	static constexpr int INIT_FRAME_COUNT = 0;//初期化用フレーム数
	static constexpr int MAX_FRAME_COUNT = 60;//最大フレーム数
	static constexpr Vec2d TUTORIAL_LOGO_POS = { 300, 400};//チュートリアルロゴ描画座標
	static constexpr DrawRect TUTORIAL_LOGO_LINE_POS = { 250, 610, 1720, 610 };//チュートリアルロゴ描画座標
	static const int FONT_COLOR;//フォントの色
	/*メンバ変数*/
	vector<int> titleData;	//画像ハンドル
	vector<int> fontData;
	vector<int> playerData;
	vector<int> enemyData;
	vector<int> stageData;
	int startIconAlpha;//スタートアイコン用アルファ
	int titleAlpha;//タイトルロゴ全体の描画用アルファ
	int stageNameAlpha;//チュートリアルロゴ用アルファ
	int addAlphaValue;//アルファ値増加量
	int frameCount;//フレーム数
	bool isChangeAddAlpha;//アルファ値増加量を変更するか
	bool isFrameCount;//フレーム数をカウントするか
	bool isDrawTitleEnd;//タイトルロゴの描画を完全に終了するか（アルファ値が定数以下になったら立てる）
	bool isDrawTitleFinish;//タイトルの描画を終了するためにアルファ値の値を減らす
	bool isDrawStageName;//ステージ名を描画するか
	bool isChangeScene;//シーンを変更する
	bool isTitleEnd;//タイトルを終了する（ゲームを終わる）
	TutorialStage* stage;
	Camera* camera;
	SwordGirl* player;
	OperationUI* opeUI;
	TutorialEnemy* enemy;
	Collision* collision;
	StatusUpParticle* statusUpParticle;

	enum class TutorialProgress
	{
		MOVE,			//移動
		CAMERA,			//カメラ操作
		ATTACK,			//攻撃
		DESTROY_ENEMY_1,
		CAMPFIRE_2,		//焚火に行く
		STATUS_UP,
		DESTROY_ENEMY_2,//敵を倒す
		GATE_2,
	};
	static constexpr int PROGRESS_NUM = 12;
	vector<bool> isProgress;
	/*内部処理関数*/
	void ChangeTitleAlphaValue();//タイトルのアルファ値の変更
	void DrawTitle();//タイトル描画
	void DrawStageName();//チュートリアルステージの文字を表示する
	void DrawTutorialText();//チュートリアル文字を描画
	void FragChanger();
	void FixMoveVec();
	void OnDamage();
	void DrawDetailedDescription();//チュートリアルの詳細なを描画
	bool isChange;
	int textAlpha;
	int tutorialProgress;
	bool isDrawText;
	int progressFrameCount;
	bool destroyEnemy;
	float prevPlayerAtk;
	static constexpr DrawRect BACKGROUND_POS_FOR_TEXT = { 500,200,1420,300 };
	static constexpr DrawRect BACKGROUND_POS_FOR_DESCRIPTION = { 1400,30,1910,520 };
	bool isDescription;
	static constexpr Vec2d TEXT_POS = { 620,230 };
	static constexpr Vec2d TEXT_POS_FOR_DESCRIPTION = { 1420,50 };
	static constexpr DrawRect BUTTON_POS = { 510,210,590,290 };
	static constexpr DrawRect BOSS_UI_DRAW_RECT = { 500,900,1420,1000 };//移動UI描画範囲
	int strongUI;
};
