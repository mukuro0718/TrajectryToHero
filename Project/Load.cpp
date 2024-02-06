//===========================================================================
//@brief ���[�h�N���X
//===========================================================================
#include"Load.h"
Load* Load::load = NULL;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Load::Load()
{
	LoadingData();
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
Load::~Load()
{
	/*�I�[�v�j���O*/
	openingImage.clear();
	/*�^�C�g��*/
	titleData.clear();
	titleFontData.clear();
	titleplayerData.clear();
	titleEnemyData.clear();
	titleStageData.clear();
	//�v���C���[���f��
	playerModel = 0;
	playerFont = 0;
	//�G�l�~�[���f��
	enemyModel.clear();
	enemyFont = 0;
	//�X�e�[�W���f��
	farmStageData.clear();
	//�X�J�C�h�[�����f��
	skydomeModel = 0;
	//�X�e�[�W�`�F���W�摜
	stageChangeImage.clear();
	gateImage = 0;
	//UI�摜
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
	//�p�[�e�B�N���摜
	playerBloodParticleImage = 0;
	enemyBloodParticleImage = 0;
	//�e�摜
	shadowImage = 0;
	//�Q�[���N���A�摜
	gameClearImage = 0;
	//�Q�[���N���A�摜
	gameOverImage = 0;

	victoryImage = 0;
}
/// <summary>
/// �f�[�^�̃��[�h
/// </summary>
void Load::LoadingData()
{
	/*�I�[�v�j���O*/
	openingImage.push_back(LoadGraph("Data/Img/Opening/Img1.png"));
	openingImage.push_back(LoadGraph("Data/Img/Opening/Img2.png"));
	openingImage.push_back(LoadGraph("Data/Img/Opening/Img3.png"));
	openingImage.push_back(LoadGraph("Data/Img/Opening/Img4.png"));

	/*�^�C�g��*/
	//�^�C�g���f�[�^
	titleData.push_back(LoadGraph("Data/Img/Title/Title.png"));
	titleData.push_back(LoadGraph("Data/Img/Game/Menu/backGround.png"));
	titleData.push_back(LoadGraph("Data/Img/Game/UI/���U���gGreenButton.png"));
	titleData.push_back(LoadGraph("Data/Img/Game/UI/���U���gRedButton.png"));
	titleData.push_back(LoadGraph("Data/Img/Game/UI/AttackButton.png"));
	titleData.push_back(LoadGraph("Data/Img/Game/UI/CameraButton.png"));
	titleData.push_back(LoadGraph("Data/Img/Game/UI/MoveButton.png"));
	titleData.push_back(LoadGraph("Data/Img/Game/UI/GoBossStage.png"));
	//�t�H���g�f�[�^
	titleFontData.push_back(CreateFontToHandle("Data/Img/Font/HelpMe.ttf", 70, 32, DX_FONTTYPE_NORMAL));
	titleFontData.push_back(CreateFontToHandle("Data/Font/Honoka_Shin_Mincho_L.otf", 200, 24, DX_FONTTYPE_NORMAL));
	titleFontData.push_back(CreateFontToHandle("Data/Font/Honoka_Shin_Mincho_L.otf", 40, 32, DX_FONTTYPE_NORMAL));
	//�v���C���[
	titleplayerData.push_back(MV1LoadModel("Data/Model/Player/Player_test2.mv1"));
	titleplayerData.push_back(LoadGraph("Data/Img/Game/UI/HPBar.png"));
	titleplayerData.push_back(LoadGraph("Data/Img/Game/UI/EXPBar.png"));
	titleplayerData.push_back(LoadGraph("Data/Img/Game/UI/UIBar.png"));
	//�G�l�~�[
	titleEnemyData.push_back(MV1LoadModel("Data/Model/Enemy/WeakEnemy.mv1"));
	strongerUIData = LoadGraph("Data/Img/Game/UI/StrongerEnemy.png");
	//�X�e�[�W
	titleStageData.push_back(MV1LoadModel("Data/Model/Map/Ground.mv1"));
	titleStageData.push_back(MV1LoadModel("Data/Model/Map/Gate.mv1"));
	titleStageData.push_back(MV1LoadModel("Data/Model/Map/Portal.mv1"));
	titleStageData.push_back(MV1LoadModel("Data/Model/Skydome/Skydome.mv1"));
	titleStageData.push_back(MV1LoadModel("Data/Model/Map/Campfire.mv1"));
	titleStageData.push_back(LoadGraph("Data/Img/Game/Particle/Flame.png"));

	/*�Q�[��*/
	//�v���C���[���f��
	playerModel = MV1LoadModel("Data/Model/Player/Player_test2.mv1");
	playerFont = CreateFontToHandle("Data/Img/Font/HelpMe.ttf", 35, 32, DX_FONTTYPE_NORMAL);
	//�G�l�~�[���f��
	enemyModel.push_back(MV1LoadModel("Data/Model/Enemy/WeakEnemy.mv1"));
	enemyModel.push_back(MV1LoadModel("Data/Model/Enemy/StrongEnemy.mv1"));
	enemyModel.push_back(MV1LoadModel("Data/Model/Enemy/Mutant.mv1"));
	enemyFont = CreateFontToHandle("Data/Img/Font/HelpMe.ttf", 35, 32, DX_FONTTYPE_NORMAL);
	//�X�e�[�W���f��
	farmStageData.push_back(MV1LoadModel("Data/Model/Map/Ground.mv1"));
	farmStageData.push_back(MV1LoadModel("Data/Model/Map/Village.mv1"));
	farmStageData.push_back(MV1LoadModel("Data/Model/Map/Gate.mv1"));
	farmStageData.push_back(MV1LoadModel("Data/Model/Map/Portal.mv1"));
	//�������
	bonfireData.push_back(MV1LoadModel("Data/Model/Map/Campfire.mv1"));
	bonfireData.push_back(LoadGraph("Data/Img/Game/Particle/Flame.png"));
	//�X�J�C�h�[�����f��
	skydomeModel = MV1LoadModel("Data/Model/Skydome/Skydome.mv1");
	//���j���[�摜
	statusData.push_back(LoadGraph("Data/Img/Game/Menu/backGround.png"));
	statusData.push_back(LoadGraph("Data/Img/Game/Menu/BonfireMenu.png"));
	statusData.push_back(LoadGraph("Data/Img/Game/Menu/Cursor.png"));
	statusData.push_back(LoadGraph("Data/Img/Game/Menu/SelectRect.png"));
	statusData.push_back(LoadGraph("Data/Img/Game/Menu/ATK.png"));
	statusData.push_back(LoadGraph("Data/Img/Game/Menu/AGI.png"));
	statusData.push_back(LoadGraph("Data/Img/Game/Menu/DEF.png"));
	statusData.push_back(LoadGraph("Data/Img/Game/UI/���U���gGreenButton.png"));
	statusData.push_back(LoadGraph("Data/Img/Game/UI/���U���gRedButton.png"));
	//�X�e�[�W�`�F���W�摜
	stageChangeImage.push_back(LoadGraph("Data/Img/Game/StageChange/Farm_���S.png"));
	stageChangeImage.push_back(LoadGraph("Data/Img/Game/StageChange/Boss_���S.png"));
	stageChangeImage.push_back(LoadGraph("Data/Img/Game/UI/GoBossStage.png"));
	gateImage = LoadGraph("Data/Img/Game/StageChange/Gate.png");
	//UI�摜
	hpBarGraph	  = LoadGraph("Data/Img/Game/UI/HPBar.png");
	expBarGraph   = LoadGraph("Data/Img/Game/UI/EXPBar.png");
	prevBarGraph  = LoadGraph("Data/Img/Game/UI/PrevBar.png");
	barFrameGraph = LoadGraph("Data/Img/Game/UI/UIBar.png");
	atkUIImage = LoadGraph("Data/Img/Game/UI/ATK.png");
	defUIImage = LoadGraph("Data/Img/Game/UI/DEF.png");
	agiUIImage = LoadGraph("Data/Img/Game/UI/AGI.png");
	statusUIFont = CreateFontToHandle("Data/Img/Font/HelpMe.ttf", 60, 16, DX_FONTTYPE_NORMAL);
	moveOpeUIImage	 = LoadGraph("Data/Img/Game/UI/MoveUI.png");
	menuOpeUIImage   = LoadGraph("Data/Img/Game/UI/���U���gBonfireMenuButton.png");
	attackOpeUIImage = LoadGraph("Data/Img/Game/UI/AttackUI.png");
	cameraOpeUIImage = LoadGraph("Data/Img/Game/UI/CameraUI.png");
	//�p�[�e�B�N���摜
	enemyBloodParticleImage = LoadGraph("Data/Img/Game/Particle/BloodEnemy.png");
	playerBloodParticleImage = LoadGraph("Data/Img/Game/Particle/Blood.png");
	//�e�摜
	shadowImage = LoadGraph("Data/Img/Game/Shadow/Shadow.tga");
	//�Q�[���N���A�摜
	gameClearImage = LoadGraph("Data/Img/GameClear/Gameclear.png");
	//�Q�[���N���A�摜
	gameOverImage = LoadGraph("Data/Img/GameOver/Gameover.png");
	victoryImage = LoadGraph("Data/Img/Game/StageChange/VICTORY.png");
}
/// <summary>
/// �I�[�v�j���O�f�[�^��getter
/// </summary>
/// <param name="image">�摜�n���h�����i�[����vector�̃|�C���^</param>
void Load::GetOpeningData(vector<int>* _image)
{
	for (int i = 0; i < OPENING_IMAGE_NUM; i++)
	{
		_image->push_back(openingImage[i]);
	}
}
/// <summary>
/// �^�C�g���f�[�^��getter
/// </summary>
/// <param name="image">�摜�n���h�����i�[����vector�̃|�C���^</param>
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
/// �v���C���[�f�[�^��getter
/// </summary>
/// <param name="model">���f���n���h�����i�[����vector�̃|�C���^</param>
void Load::GetPlayerData(int* _model, int* _frameImage, int* _hpImage, int* _expImage,int* _font)
{
	*_font = playerFont;
	*_model = playerModel;
	*_frameImage = barFrameGraph;
	*_hpImage = hpBarGraph;
	*_expImage = expBarGraph;
}
/// <summary>
/// �G�l�~�[�f�[�^��getter
/// </summary>
/// <param name="model">���f���n���h�����i�[����vector�̃|�C���^</param>
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
/// �X�e�[�W�f�[�^��getter
/// </summary>
/// <param name="image">���f���n���h�����i�[����vector�̃|�C���^</param>
void Load::GetStageData(vector<int>* _farmData)
{
	for (int i = 0; i < FARM_STAGE_MODEL_NUM; i++)
	{
		_farmData->push_back(farmStageData[i]);
	}
}
/// <summary>
/// �E�F�[�u�f�[�^��getter
/// </summary>
/// <param name="image">�摜�n���h�����i�[����vector�̃|�C���^</param>
void Load::GetStageChangeData(vector<int>* _image, int* _gate)
{
	for (int i = 0; i < STAGE_CHANGE_IMAGE_NUM; i++)
	{
		_image->push_back(stageChangeImage[i]);
	}
	*_gate = gateImage;
}
/// <summary>
/// ���j���[�f�[�^��getter
/// </summary>
/// <param name="image">�摜�n���h�����i�[����vector�̃|�C���^</param>
void Load::GetCharacterStatusData(vector<int>* _data)
{
	for (int i = 0; i < STATUS_DATA; i++)
	{
		_data->push_back(statusData[i]);
	}
}
/// <summary>
/// �X�J�C�h�[���f�[�^��getter
/// </summary>
/// <param name="skydomeModel"></param>
void Load::GetSkydomeData(int* _skydomeModel)
{
	*_skydomeModel = skydomeModel;
}
/// <summary>
/// �e�f�[�^��getter
/// </summary>
/// <param name="shadowImage"></param>
void Load::GetShadowData(int* _shadowImage)
{
	*_shadowImage = shadowImage;
}
/// <summary>
/// �Q�[���N���A�f�[�^��getter
/// </summary>
void Load::GetGameClearData(int* _image)
{
	*_image = gameClearImage;
}
/// <summary>
/// �Q�[���I�[�o�[�f�[�^��getter
/// </summary>
void Load::GetGameOverData(int* _image)
{
	*_image = gameOverImage;	
}
/// <summary>
/// �p�[�e�B�N���f�[�^��getter
/// </summary>
void Load::GetEnemyParticleData(int* _image)
{
	*_image = enemyBloodParticleImage;
}
/// <summary>
/// �p�[�e�B�N���f�[�^��getter
/// </summary>
void Load::GetPlayerParticleData(int* _image)
{
	*_image = playerBloodParticleImage;
}
/// <summary>
/// �X�e�[�^�XUI�f�[�^��getter
/// </summary>
void Load::GetStatusUIData(int* _atkImage, int* _defImage, int* _agiImage, int* _font)
{
	*_atkImage = atkUIImage;
	*_defImage = defUIImage;
	*_agiImage = agiUIImage;
	*_font = statusUIFont;
}
/// <summary>
/// �������UI�f�[�^��getter
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