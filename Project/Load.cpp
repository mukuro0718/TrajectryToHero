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
	//playerModel = MV1LoadModel("Data/Model/Player/Player.mv1");
	playerModel = MV1LoadModel("Data/Model/Player/Player_test2.mv1");
	//エネミーモデル
	enemyModel.push_back(MV1LoadModel("Data/Model/Enemy/WeakEnemy.mv1"));
	enemyModel.push_back(MV1LoadModel("Data/Model/Enemy/StrongEnemy.mv1"));
	enemyModel.push_back(MV1LoadModel("Data/Model/Enemy/Mutant.mv1"));
	//ステージモデル
	stageModel = MV1LoadModel("Data/Model/Map/stage.mv1");
	//スカイドームモデル
	skydomeModel = MV1LoadModel("Data/Model/Skydome/Skydome.mv1");
	//メニュー画像
	characterStatusImage = LoadGraph("Data/Img/Game/Menu/backGround.png");
	characterStatusFont = CreateFontToHandle("Data/Img/Font/HelpMe.ttf", 128, 64, DX_FONTTYPE_NORMAL);
	//ステージチェンジ画像
	stageChangeImage.push_back(LoadGraph("Data/Img/Game/StageChange/Farm_ロゴ.png"));
	stageChangeImage.push_back(LoadGraph("Data/Img/Game/StageChange/Boss_ロゴ.png"));
	stageChangeImage.push_back(LoadGraph("Data/Img/Game/StageChange/警告.png"));
	//UI画像
	hpBarGraph = LoadGraph("Data/Img/Game/UI/RectArea.png");
	expBarGraph = LoadGraph("Data/Img/Game/UI/EXPBar.png");
	prevBarGraph = LoadGraph("Data/Img/Game/UI/PrevBar.png");
	barFrameGraph = LoadGraph("Data/Img/Game/UI/UIBar.png");
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
void Load::GetPlayerData(int* _model, int* _frameImage, int* _hpImage, int* _expImage)
{
	*_model = playerModel;
	*_frameImage = barFrameGraph;
	*_hpImage = hpBarGraph;
	*_expImage = expBarGraph;
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
void Load::GetCharacterStatusData(int* _image, int* _font)
{
	*_image = characterStatusImage;
	*_font = characterStatusFont;
}
/// <summary>
/// スカイドームデータのgetter
/// </summary>
/// <param name="skydomeModel"></param>
void Load::GetSkydomeData(int* _skydomeModel)
{
	*_skydomeModel = skydomeModel;
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

