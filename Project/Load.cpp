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
	/*オープニング*/
	openingImage.clear();
	/*タイトル*/
	titleData.clear();
	titleFontData.clear();
	titleplayerData.clear();
	titleEnemyData.clear();
	titleStageData.clear();
	//プレイヤーモデル
	playerModel = 0;
	playerFont = 0;
	//エネミーモデル
	enemyModel.clear();
	enemyFont = 0;
	//ステージモデル
	farmStageData.clear();
	//スカイドームモデル
	skydomeModel = 0;
	//ステージチェンジ画像
	stageChangeImage.clear();
	gateImage = 0;
	//UI画像
	hpBarGraph = 0;
	expBarGraph = 0;
	prevBarGraph = 0;
	barFrameGraph = 0;
	atkUIImage = 0;
	defUIImage = 0;
	agiUIImage = 0;
	statusUIFont = 0;
	moveOpeUIImage = 0;
	menuOpeUIImage = 0;
	attackOpeUIImage = 0;
	cameraOpeUIImage = 0;
	//パーティクル画像
	playerBloodParticleImage = 0;
	enemyBloodParticleImage = 0;
	//影画像
	shadowImage = 0;
	//ゲームクリア画像
	gameClearImage = 0;
	//ゲームクリア画像
	gameOverImage = 0;

	victoryImage = 0;
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
	//タイトルデータ
	titleData.push_back(LoadGraph("Data/Img/Title/Title.png"));
	titleData.push_back(LoadGraph("Data/Img/Game/Menu/backGround.png"));
	titleData.push_back(LoadGraph("Data/Img/Game/UI/リザルトGreenButton.png"));
	titleData.push_back(LoadGraph("Data/Img/Game/UI/リザルトRedButton.png"));
	titleData.push_back(LoadGraph("Data/Img/Game/UI/AttackButton.png"));
	titleData.push_back(LoadGraph("Data/Img/Game/UI/CameraButton.png"));
	titleData.push_back(LoadGraph("Data/Img/Game/UI/MoveButton.png"));
	titleData.push_back(LoadGraph("Data/Img/Game/UI/GoBossStage.png"));
	//フォントデータ
	titleFontData.push_back(CreateFontToHandle("Data/Img/Font/HelpMe.ttf", 70, 32, DX_FONTTYPE_NORMAL));
	titleFontData.push_back(CreateFontToHandle("Data/Font/Honoka_Shin_Mincho_L.otf", 200, 24, DX_FONTTYPE_NORMAL));
	titleFontData.push_back(CreateFontToHandle("Data/Font/Honoka_Shin_Mincho_L.otf", 40, 32, DX_FONTTYPE_NORMAL));
	//プレイヤー
	titleplayerData.push_back(MV1LoadModel("Data/Model/Player/Player_test2.mv1"));
	titleplayerData.push_back(LoadGraph("Data/Img/Game/UI/HPBar.png"));
	titleplayerData.push_back(LoadGraph("Data/Img/Game/UI/EXPBar.png"));
	titleplayerData.push_back(LoadGraph("Data/Img/Game/UI/UIBar.png"));
	//エネミー
	titleEnemyData.push_back(MV1LoadModel("Data/Model/Enemy/WeakEnemy.mv1"));
	strongerUIData = LoadGraph("Data/Img/Game/UI/StrongerEnemy.png");
	//ステージ
	titleStageData.push_back(MV1LoadModel("Data/Model/Map/Ground.mv1"));
	titleStageData.push_back(MV1LoadModel("Data/Model/Map/Gate.mv1"));
	titleStageData.push_back(MV1LoadModel("Data/Model/Map/Portal.mv1"));
	titleStageData.push_back(MV1LoadModel("Data/Model/Skydome/Skydome.mv1"));
	titleStageData.push_back(MV1LoadModel("Data/Model/Map/Campfire.mv1"));
	titleStageData.push_back(LoadGraph("Data/Img/Game/Particle/Flame.png"));

	/*ゲーム*/
	//プレイヤーモデル
	playerModel = MV1LoadModel("Data/Model/Player/Player_test2.mv1");
	playerFont = CreateFontToHandle("Data/Img/Font/HelpMe.ttf", 35, 32, DX_FONTTYPE_NORMAL);
	//エネミーモデル
	enemyModel.push_back(MV1LoadModel("Data/Model/Enemy/WeakEnemy.mv1"));
	enemyModel.push_back(MV1LoadModel("Data/Model/Enemy/StrongEnemy.mv1"));
	enemyModel.push_back(MV1LoadModel("Data/Model/Enemy/Mutant.mv1"));
	enemyFont = CreateFontToHandle("Data/Img/Font/HelpMe.ttf", 35, 32, DX_FONTTYPE_NORMAL);
	//ステージモデル
	farmStageData.push_back(MV1LoadModel("Data/Model/Map/Ground.mv1"));
	farmStageData.push_back(MV1LoadModel("Data/Model/Map/Village.mv1"));
	farmStageData.push_back(MV1LoadModel("Data/Model/Map/Gate.mv1"));
	farmStageData.push_back(MV1LoadModel("Data/Model/Map/Portal.mv1"));
	//かがり火
	bonfireData.push_back(MV1LoadModel("Data/Model/Map/Campfire.mv1"));
	bonfireData.push_back(LoadGraph("Data/Img/Game/Particle/Flame.png"));
	//スカイドームモデル
	skydomeModel = MV1LoadModel("Data/Model/Skydome/Skydome.mv1");
	//メニュー画像
	statusData.push_back(LoadGraph("Data/Img/Game/Menu/backGround.png"));
	statusData.push_back(LoadGraph("Data/Img/Game/Menu/BonfireMenu.png"));
	statusData.push_back(LoadGraph("Data/Img/Game/Menu/Cursor.png"));
	statusData.push_back(LoadGraph("Data/Img/Game/Menu/SelectRect.png"));
	statusData.push_back(LoadGraph("Data/Img/Game/Menu/ATK.png"));
	statusData.push_back(LoadGraph("Data/Img/Game/Menu/AGI.png"));
	statusData.push_back(LoadGraph("Data/Img/Game/Menu/DEF.png"));
	statusData.push_back(LoadGraph("Data/Img/Game/UI/リザルトGreenButton.png"));
	statusData.push_back(LoadGraph("Data/Img/Game/UI/リザルトRedButton.png"));
	//ステージチェンジ画像
	stageChangeImage.push_back(LoadGraph("Data/Img/Game/StageChange/Farm_ロゴ.png"));
	stageChangeImage.push_back(LoadGraph("Data/Img/Game/StageChange/Boss_ロゴ.png"));
	stageChangeImage.push_back(LoadGraph("Data/Img/Game/UI/GoBossStage.png"));
	gateImage = LoadGraph("Data/Img/Game/StageChange/Gate.png");
	//UI画像
	hpBarGraph	  = LoadGraph("Data/Img/Game/UI/HPBar.png");
	expBarGraph   = LoadGraph("Data/Img/Game/UI/EXPBar.png");
	prevBarGraph  = LoadGraph("Data/Img/Game/UI/PrevBar.png");
	barFrameGraph = LoadGraph("Data/Img/Game/UI/UIBar.png");
	atkUIImage = LoadGraph("Data/Img/Game/UI/ATK.png");
	defUIImage = LoadGraph("Data/Img/Game/UI/DEF.png");
	agiUIImage = LoadGraph("Data/Img/Game/UI/AGI.png");
	statusUIFont = CreateFontToHandle("Data/Img/Font/HelpMe.ttf", 60, 16, DX_FONTTYPE_NORMAL);
	moveOpeUIImage	 = LoadGraph("Data/Img/Game/UI/MoveUI.png");
	menuOpeUIImage   = LoadGraph("Data/Img/Game/UI/リザルトBonfireMenuButton.png");
	attackOpeUIImage = LoadGraph("Data/Img/Game/UI/AttackUI.png");
	cameraOpeUIImage = LoadGraph("Data/Img/Game/UI/CameraUI.png");
	//パーティクル画像
	enemyBloodParticleImage = LoadGraph("Data/Img/Game/Particle/BloodEnemy.png");
	playerBloodParticleImage = LoadGraph("Data/Img/Game/Particle/Blood.png");
	//影画像
	shadowImage = LoadGraph("Data/Img/Game/Shadow/Shadow.tga");
	//ゲームクリア画像
	gameClearImage = LoadGraph("Data/Img/GameClear/Gameclear.png");
	//ゲームクリア画像
	gameOverImage = LoadGraph("Data/Img/GameOver/Gameover.png");
	victoryImage = LoadGraph("Data/Img/Game/StageChange/VICTORY.png");
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
void Load::GetTitleData(vector<int>* _title, vector<int>* _font, vector<int>* _player, vector<int>* _enemy, vector<int>* _stage)
{
	for (int i = 0; i < TITLE_DATA_NUM; i++)
	{
		_title->push_back(titleData[i]);
	}
	for (int i = 0; i < TITLE_FONT_DATA_NUM; i++)
	{
		_font->push_back(titleFontData[i]);
	}
	for (int i = 0; i < TITLE_PLAYER_DATA_NUM; i++)
	{
		_player->push_back(titleplayerData[i]);
	}
	for (int i = 0; i < TITLE_ENEMY_DATA_NUM; i++)
	{
		_enemy->push_back(titleEnemyData[i]);
	}
	for (int i = 0; i < TITLE_STAGE_DATA_NUM; i++)
	{
		_stage->push_back(titleStageData[i]);
	}
}
/// <summary>
/// プレイヤーデータのgetter
/// </summary>
/// <param name="model">モデルハンドルを格納するvectorのポインタ</param>
void Load::GetPlayerData(int* _model, int* _frameImage, int* _hpImage, int* _expImage,int* _font)
{
	*_font = playerFont;
	*_model = playerModel;
	*_frameImage = barFrameGraph;
	*_hpImage = hpBarGraph;
	*_expImage = expBarGraph;
}
/// <summary>
/// エネミーデータのgetter
/// </summary>
/// <param name="model">モデルハンドルを格納するvectorのポインタ</param>
void Load::GetEnemyData(vector<int>* _model, int* _frameImage, int* _hpImage, int* _font)
{
	for (int i = 0; i < ENEMY_MODEL_NUM; i++)
	{
		_model->push_back(enemyModel[i]);
	}
	*_font = enemyFont;
	*_frameImage = barFrameGraph;
	*_hpImage = hpBarGraph;
}
/// <summary>
/// ステージデータのgetter
/// </summary>
/// <param name="image">モデルハンドルを格納するvectorのポインタ</param>
void Load::GetStageData(vector<int>* _farmData)
{
	for (int i = 0; i < FARM_STAGE_MODEL_NUM; i++)
	{
		_farmData->push_back(farmStageData[i]);
	}
}
/// <summary>
/// ウェーブデータのgetter
/// </summary>
/// <param name="image">画像ハンドルを格納するvectorのポインタ</param>
void Load::GetStageChangeData(vector<int>* _image, int* _gate)
{
	for (int i = 0; i < STAGE_CHANGE_IMAGE_NUM; i++)
	{
		_image->push_back(stageChangeImage[i]);
	}
	*_gate = gateImage;
}
/// <summary>
/// メニューデータのgetter
/// </summary>
/// <param name="image">画像ハンドルを格納するvectorのポインタ</param>
void Load::GetCharacterStatusData(vector<int>* _data)
{
	for (int i = 0; i < STATUS_DATA; i++)
	{
		_data->push_back(statusData[i]);
	}
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
void Load::GetGameClearData(int* _image)
{
	*_image = gameClearImage;
}
/// <summary>
/// ゲームオーバーデータのgetter
/// </summary>
void Load::GetGameOverData(int* _image)
{
	*_image = gameOverImage;	
}
/// <summary>
/// パーティクルデータのgetter
/// </summary>
void Load::GetEnemyParticleData(int* _image)
{
	*_image = enemyBloodParticleImage;
}
/// <summary>
/// パーティクルデータのgetter
/// </summary>
void Load::GetPlayerParticleData(int* _image)
{
	*_image = playerBloodParticleImage;
}
/// <summary>
/// ステータスUIデータのgetter
/// </summary>
void Load::GetStatusUIData(int* _atkImage, int* _defImage, int* _agiImage, int* _font)
{
	*_atkImage = atkUIImage;
	*_defImage = defUIImage;
	*_agiImage = agiUIImage;
	*_font = statusUIFont;
}
/// <summary>
/// 操作説明UIデータのgetter
/// </summary>
void Load::GetOpeUIData(int* _moveImage, int* _menuImage, int* _attackImage, int* _cameraImage)
{
	*_moveImage = moveOpeUIImage;
	*_menuImage = menuOpeUIImage;
	*_attackImage = attackOpeUIImage;
	*_cameraImage = cameraOpeUIImage;
}
void Load::GetBonfireData(vector<int>* _bonfireData)
{
	for (int i = 0; i < BONFIRE_DATA_NUM; i++)
	{
		_bonfireData->push_back(bonfireData[i]);
	}
}
void Load::GetStrongerUIData(int* _data)
{
	*_data = strongerUIData;
}
void Load::GetVictoryData(int* _victoryData)
{
	*_victoryData = victoryImage;
}