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
	/*�Q�[��*/
	//�v���C���[���f��
	//playerModel = MV1LoadModel("Data/Model/Player/Player.mv1");
	playerModel = MV1LoadModel("Data/Model/Player/Player_test2.mv1");
	playerFont = CreateFontToHandle("Data/Img/Font/HelpMe.ttf", 35, 32, DX_FONTTYPE_NORMAL);
	//�G�l�~�[���f��
	enemyModel.push_back(MV1LoadModel("Data/Model/Enemy/WeakEnemy.mv1"));
	enemyModel.push_back(MV1LoadModel("Data/Model/Enemy/StrongEnemy.mv1"));
	enemyModel.push_back(MV1LoadModel("Data/Model/Enemy/Mutant.mv1"));
	//�X�e�[�W���f��
	stageModel = MV1LoadModel("Data/Model/Map/stage.mv1");
	//�X�J�C�h�[�����f��
	skydomeModel = MV1LoadModel("Data/Model/Skydome/Skydome.mv1");
	//���j���[�摜
	characterStatusImage = LoadGraph("Data/Img/Game/Menu/backGround.png");
	characterStatusFont = CreateFontToHandle("Data/Img/Font/HelpMe.ttf", 128, 64, DX_FONTTYPE_NORMAL);
	//�X�e�[�W�`�F���W�摜
	stageChangeImage.push_back(LoadGraph("Data/Img/Game/StageChange/Farm_���S.png"));
	stageChangeImage.push_back(LoadGraph("Data/Img/Game/StageChange/Boss_���S.png"));
	stageChangeImage.push_back(LoadGraph("Data/Img/Game/StageChange/�x��.png"));
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
	menuOpeUIImage   = LoadGraph("Data/Img/Game/UI/MenuUI.png");
	attackOpeUIImage = LoadGraph("Data/Img/Game/UI/AttackUI.png");
	cameraOpeUIImage = LoadGraph("Data/Img/Game/UI/CameraUI.png");
	//�p�[�e�B�N���摜
	bloodParticleImage = LoadGraph("Data/Img/Game/Particle/Blood.png");
	//�e�摜
	shadowImage = LoadGraph("Data/Img/Game/Shadow/Shadow.tga");
	//�Q�[���N���A�摜
	gameClearImage = LoadGraph("Data/Img/Result/Gameclear.png");
	//�Q�[���N���A�摜
	gameOverImage = LoadGraph("Data/Img/Result/Gameover.png");
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
void Load::GetTitleData(vector<int>* _image)
{
	for (int i = 0; i < TITLE_IMAGE_NUM; i++)
	{
		_image->push_back(titleImage[i]);
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
void Load::GetEnemyData(vector<int>* _model)
{
	for (int i = 0; i < ENEMY_MODEL_NUM; i++)
	{
		_model->push_back(enemyModel[i]);
	}
}
/// <summary>
/// �X�e�[�W�f�[�^��getter
/// </summary>
/// <param name="image">���f���n���h�����i�[����vector�̃|�C���^</param>
void Load::GetStageData(int* _model)
{
	*_model = stageModel;
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
void Load::GetCharacterStatusData(int* _image, int* _font)
{
	*_image = characterStatusImage;
	*_font = characterStatusFont;
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
void Load::GetParticleData(int* _image)
{
	*_image = bloodParticleImage;
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