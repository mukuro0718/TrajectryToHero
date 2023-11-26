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
	playerModel = MV1LoadModel("Data/Model/Player/Player.mv1");
	//�G�l�~�[���f��
	enemyModel.push_back(MV1LoadModel("Data/Model/Enemy/WeakEnemy.mv1"));
	enemyModel.push_back(MV1LoadModel("Data/Model/Enemy/StrongEnemy.mv1"));
	enemyModel.push_back(MV1LoadModel("Data/Model/Enemy/Mutant.mv1"));
	//�X�e�[�W���f��
	stageModel = MV1LoadModel("Data/Model/Map/stage.mv1");
	//���j���[�摜
	statusManagerImage = LoadGraph("Data/Img/Game/Menu/backGround.png");
	//�X�e�[�W�`�F���W�摜
	stageChangeImage.push_back(LoadGraph("Data/Img/Game/StageChange/Farm_���S.png"));
	stageChangeImage.push_back(LoadGraph("Data/Img/Game/StageChange/Boss_���S.png"));
	stageChangeImage.push_back(LoadGraph("Data/Img/Game/StageChange/�x��.png"));
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
void Load::GetPlayerData(int* _model)
{
	*_model = playerModel;
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
void Load::GetStageChangeData(vector<int>* _image)
{
	for (int i = 0; i < STAGE_CHANGE_IMAGE_NUM; i++)
	{
		_image->push_back(stageChangeImage[i]);
	}
}
/// <summary>
/// ���j���[�f�[�^��getter
/// </summary>
/// <param name="image">�摜�n���h�����i�[����vector�̃|�C���^</param>
void Load::GetStatusManagerData(int* _image)
{
	*_image = statusManagerImage;
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
/// <param name="_image">�Q�[���N���A�摜</param>
/// <param name="_model">�Q�[���N���A���f��</param>
void Load::GetGameClearData(int* _image)
{
	*_image = gameClearImage;
}
void Load::GetGameOverData(int* _image)
{
	*_image = gameOverImage;	
}