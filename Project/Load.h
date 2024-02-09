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
	void GetTitleData		(vector<int>* _title, vector<int>* _font, vector<int>* _player, vector<int>* _enemy, vector<int>* _stage );	//タイトルデータのgetter
	void GetStageChangeData	(vector<int>* _image,int* _gate);	//ステージデータのgetter
	void GetEnemyData		(vector<int>* _model, int* _frameImage, int* _hpImage, int* _font);	//エネミーデータのgetter
	
	void GetPlayerData		 (int* _model,int* _frameImage,int* _hpImage,int* _expImage,int* _font);	//プレイヤーデータのgetter
	void GetStageData		 (vector<int>* _farmData);	//ステージデータのgetter
	void GetCharacterStatusData(vector<int>* _data);	//メニューデータのgetter
	void GetShadowData		 (int* _image);	//シャドウデータのgetter
	void GetSkydomeData		 (int* _skydomeModel);	//スカイドームデータのgetter
	void GetGameClearData	 (int* _image);//ゲームクリアデータのgetter
	void GetGameOverData	 (int* _image);//ゲームクリアデータのgetter

	void GetEnemyParticleData(int* _image, int* _animModel);//パーティクルデータのgetter
	void GetPlayerParticleData(int* _image);//パーティクルデータのgetter

	void GetStatusUIData(int* _atkImage, int* _defImage, int* _agiImage, int* font);//ステータスUIデータのgetter
	void GetOpeUIData(int* _moveImage, int* _menuImage, int* _attackImage, int* _cameraImage);//操作説明UIデータのgetter
	void GetBonfireData(vector<int>* _bonfireData);
	void GetStrongerUIData(int* _imageHandle);
	void GetVictoryData(int* _victoryData);
	void GetDiedData(int* _diedData);
private:
	Load();//コンストラクタ
	static Load* load;

	/// <summary>
	/// 強敵マーク
	/// </summary>
	int strongerUIData;
	int animModel;

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
	static constexpr int TITLE_DATA_NUM = 8;		//タイトルロゴ
	static constexpr int TITLE_FONT_DATA_NUM = 4;	//フォント
	static constexpr int TITLE_PLAYER_DATA_NUM = 4;	//プレイヤー
	static constexpr int TITLE_ENEMY_DATA_NUM = 1;	//エネミー
	static constexpr int TITLE_STAGE_DATA_NUM = 6;	//ステージ
	vector<int>titleData;
	vector<int>titleFontData;
	vector<int>titleplayerData;
	vector<int>titleEnemyData;
	vector<int>titleStageData;
	/// <summary>
	/// エネミー
	/// </summary>
	static constexpr int ENEMY_MODEL_NUM = 3;		//総エネミーモデル数
	vector<int>enemyModel;			//エネミーモデルハンドル
	int enemyFont;
	/// <summary>
	/// プレイヤー
	/// </summary>
	int playerModel;	//プレイヤーモデルハンドル
	int playerFont;		//プレイヤーフォント
	/// <summary>
	/// ステージ
	/// </summary>
	static constexpr int FARM_STAGE_MODEL_NUM = 3;
	vector<int> farmStageData;
	/// <summary>
	/// かがり火
	/// </summary>
	static constexpr int BONFIRE_DATA_NUM = 2;
	vector<int> bonfireData;
	/// <summary>
	/// 勝利ロゴ
	/// </summary>
	int victoryImage;
	/// <summary>
	/// 死亡ロゴ
	/// </summary>
	int diedImage;
	/// <summary>
	/// ステージチェンジ
	/// </summary>
	static constexpr int STAGE_CHANGE_IMAGE_NUM = 3;//総ステージチェンジ画像数
	vector<int>stageChangeImage;	//ステージチェンジ画像
	int gateImage;
	/// <summary>
	/// ステータス
	/// </summary>
	static constexpr int STATUS_DATA = 9;
	vector<int>statusData;
	/// <summary>
	/// 影
	/// </summary>
	int shadowImage;				//影画像
	/// <summary>
	/// スカイドーム
	/// </summary>
	int skydomeModel;				//スカイドーム
	/// <summary>
	/// UI
	/// </summary>
	int hpBarGraph;					//HPバー画像
	int prevBarGraph;				//以前のバー位置描画画像
	int expBarGraph;				//経験値バー画像
	int barFrameGraph;				//バーフレーム画像
	int enemyBloodParticleImage;//血液パーティクル画像
	int playerBloodParticleImage;//血液パーティクル画像
	int atkUIImage;//攻撃力UI画像
	int defUIImage;//防御力UI画像
	int agiUIImage;//素早さUI画像
	int statusUIFont;//ステータスUI用フォント
	int moveOpeUIImage;//移動操作UI画像
	int menuOpeUIImage;//メニュー操作UI画像
	int attackOpeUIImage;//攻撃操作UI画像
	int cameraOpeUIImage;//カメラ操作UI画像
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
