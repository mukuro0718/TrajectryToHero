//===========================================================================
//@brief ロードクラス
//===========================================================================
#include"Load.h"
Load* Load::load = NULL;

/// <summary>
/// コンストラクタ
/// </summary>
Load::Load()
{
	LoadingData();
}
/// <summary>
/// デストラクタ
/// </summary>
Load::~Load()
{
}
/// <summary>
/// データのロード
/// </summary>
void Load::LoadingData()
{
	/*オープニング*/
	openingImage.push_back(LoadGraph("Data/Img/Opening/Img1.png"));
	openingImage.push_back(LoadGraph("Data/Img/Opening/Img2.png"));
	openingImage.push_back(LoadGraph("Data/Img/Opening/Img3.png"));
	openingImage.push_back(LoadGraph("Data/Img/Opening/Img4.png"));

	/*タイトル*/
	titleImage.push_back(LoadGraph("Data/Img/Title/Icon1.png"));
	titleImage.push_back(LoadGraph("Data/Img/Title/Icon2.png"));
	titleImage.push_back(LoadGraph("Data/Img/Title/Icon3.png"));
	titleImage.push_back(LoadGraph("Data/Img/Title/Title.png"));
	titleImage.push_back(LoadGraph("Data/Img/Title/Cursor.png"));
	titleImage.push_back(LoadGraph("Data/Img/Title/BackGround.png"));
	titleImage.push_back(LoadGraph("Data/Img/Title/BriefingData.png"));
	titleImage.push_back(LoadGraph("Data/Img/Title/7.png"));
	titleImage.push_back(LoadGraph("Data/Img/Title/6.png"));
	titleImage.push_back(LoadGraph("Data/Img/Title/5.png"));
	titleImage.push_back(LoadGraph("Data/Img/Title/4.png"));
	titleImage.push_back(LoadGraph("Data/Img/Title/3.png"));
	titleImage.push_back(LoadGraph("Data/Img/Title/2.png"));
	titleImage.push_back(LoadGraph("Data/Img/Title/1.png"));
	/*ゲーム*/
	//プレイヤーモデル
	playerModel = MV1LoadModel("Data/Model/Player/Player.mv1");
	//エネミーモデル
	enemyModel.push_back(MV1LoadModel("Data/Model/Enemy/WeakEnemy.mv1"));
	enemyModel.push_back(MV1LoadModel("Data/Model/Enemy/StrongEnemy.mv1"));
	enemyModel.push_back(MV1LoadModel("Data/Model/Enemy/Mutant.mv1"));
	//ステージモデル
	stageModel = MV1LoadModel("Data/Model/Map/stage.mv1");
	//メニュー画像
	statusManagerImage = LoadGraph("Data/Img/Game/Menu/backGround.png");
	//ステージチェンジ画像
	stageChangeImage.push_back(LoadGraph("Data/Img/Game/StageChange/Farm_ロゴ.png"));
	stageChangeImage.push_back(LoadGraph("Data/Img/Game/StageChange/Boss_ロゴ.png"));
	stageChangeImage.push_back(LoadGraph("Data/Img/Game/StageChange/警告.png"));
	//影画像
	shadowImage = LoadGraph("Data/Img/Game/Shadow/Shadow.tga");
	//ゲームクリア画像
	gameClearImage = LoadGraph("Data/Img/Result/Gameclear.png");
	//ゲームクリア画像
	gameOverImage = LoadGraph("Data/Img/Result/Gameover.png");
}
/// <summary>
/// オープニングデータのgetter
/// </summary>
/// <param name="image">画像ハンドルを格納するvectorのポインタ</param>
void Load::GetOpeningData(vector<int>* _image)
{
	for (int i = 0; i < OPENING_IMAGE_NUM; i++)
	{
		_image->push_back(openingImage[i]);
	}
}
/// <summary>
/// タイトルデータのgetter
/// </summary>
/// <param name="image">画像ハンドルを格納するvectorのポインタ</param>
void Load::GetTitleData(vector<int>* _image)
{
	for (int i = 0; i < TITLE_IMAGE_NUM; i++)
	{
		_image->push_back(titleImage[i]);
	}
}
/// <summary>
/// プレイヤーデータのgetter
/// </summary>
/// <param name="model">モデルハンドルを格納するvectorのポインタ</param>
void Load::GetPlayerData(int* _model)
{
	*_model = playerModel;
}
/// <summary>
/// エネミーデータのgetter
/// </summary>
/// <param name="model">モデルハンドルを格納するvectorのポインタ</param>
void Load::GetEnemyData(vector<int>* _model)
{
	for (int i = 0; i < ENEMY_MODEL_NUM; i++)
	{
		_model->push_back(enemyModel[i]);
	}
}
/// <summary>
/// ステージデータのgetter
/// </summary>
/// <param name="image">モデルハンドルを格納するvectorのポインタ</param>
void Load::GetStageData(int* _model)
{
	*_model = stageModel;
}
/// <summary>
/// ウェーブデータのgetter
/// </summary>
/// <param name="image">画像ハンドルを格納するvectorのポインタ</param>
void Load::GetStageChangeData(vector<int>* _image)
{
	for (int i = 0; i < STAGE_CHANGE_IMAGE_NUM; i++)
	{
		_image->push_back(stageChangeImage[i]);
	}
}
/// <summary>
/// メニューデータのgetter
/// </summary>
/// <param name="image">画像ハンドルを格納するvectorのポインタ</param>
void Load::GetStatusManagerData(int* _image)
{
	*_image = statusManagerImage;
}
/// <summary>
/// 影データのgetter
/// </summary>
/// <param name="shadowImage"></param>
void Load::GetShadowData(int* _shadowImage)
{
	*_shadowImage = shadowImage;
}
/// <summary>
/// ゲームクリアデータのgetter
/// </summary>
/// <param name="_image">ゲームクリア画像</param>
/// <param name="_model">ゲームクリアモデル</param>
void Load::GetGameClearData(int* _image)
{
	*_image = gameClearImage;
}
void Load::GetGameOverData(int* _image)
{
	*_image = gameOverImage;	
}