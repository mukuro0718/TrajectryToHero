//===========================================================================
//@brief ロードクラス
//===========================================================================
/*最初に必要なものすべてをロードし
必要に応じて引き渡す*/
#pragma once
#include<DxLib.h>
#include<cassert>
#include<vector>

using namespace std;
class Load final
{
public:
	virtual ~Load();//デストラクタ

	//インスタンスの生成
	static void CreateInstance()
	{
		load = new Load();
	}
	//インスタンスの取得
	static Load& GetInstance()
	{
		//HACK:assert(このプログラムを通った時、例外を発生させる)
		assert(load != NULL);
		return *load;
	}
	//インスタンスの削除
	static void DeleteInstance()
	{
		delete(load);
	}
	void LoadingData();

	
	void GetOpeningData		(vector<int>* _image);	//オープニングデータのgetter
	void GetTitleData		(vector<int>* _image);	//タイトルデータのgetter
	void GetStageChangeData	(vector<int>* _image);	//ステージデータのgetter
	void GetEnemyData		(vector<int>* _model);	//エネミーデータのgetter
	
	void GetPlayerData		 (int* _model);	//プレイヤーデータのgetter
	void GetStageData		 (int* _model);	//ステージデータのgetter
	void GetStatusManagerData(int* _image);	//メニューデータのgetter
	void GetShadowData		 (int* _image);	//シャドウデータのgetter

	void GetGameClearData	 (int* _image);//ゲームクリアデータのgetter
	void GetGameOverData	 (int* _image);//ゲームクリアデータのgetter
private:
	Load();//コンストラクタ
	static Load* load;

	/// <summary>
	/// オープニング
	/// </summary>
	/*静的定数*/
	static constexpr int OPENING_IMAGE_NUM = 4;	//総オープニング画像数
	/*メンバ変数*/
	vector<int>openingImage;					//オープニング画像

	/// <summary>
	/// タイトル
	/// </summary>
	/*静的定数*/
	static constexpr int TITLE_IMAGE_NUM = 14;	//総タイトル画像数
	/*メンバ変数*/
	vector<int>titleImage;						//タイトル画像

	/// <summary>
	/// ゲーム
	/// </summary>
	/*静的定数*/
	static constexpr int ENEMY_MODEL_NUM = 3;		//総エネミーモデル数
	static constexpr int STAGE_CHANGE_IMAGE_NUM = 3;//総ステージチェンジ画像数
	/*メンバ変数*/
	vector<int>enemyModel;			//エネミーモデルハンドル
	vector<int>stageChangeImage;	//ステージチェンジ画像
	int playerModel;				//プレイヤーモデルハンドル
	int stageModel;					//ステージモデルハンドル
	int statusManagerImage;			//ステータスマネージャー画像
	int shadowImage;				//影画像

	/// <summary>
	/// ゲームクリア
	/// </summary>
	/*静的定数*/
	static constexpr int GAME_CLEAR_MODEL_NUM = 2;	//総ゲームクリアモデル数
	/*メンバ変数*/
	int gameClearImage;		//ゲームクリア画像
	
	/// <summary>
	/// ゲームオーバー
	/// </summary>
	/*メンバ変数*/
	int gameOverImage;		//ゲームオーバー画像
};
