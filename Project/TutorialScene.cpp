//===========================================================================
//@brief �^�C�g���V�[���N���X / �h��
//===========================================================================
#include"TutorialScene.h"
#include"SceneChanger.h"
#include"Tutorial.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
TutorialScene::TutorialScene()
{
	tutorial = NULL;
	padInput = 0;
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
TutorialScene::~TutorialScene()
{
	Final();
}
/// <summary>
/// �쐬
/// </summary>
void TutorialScene::Create()
{
	tutorial = new Tutorial();
}
/// <summary>
/// �폜
/// </summary>
void TutorialScene::Final()
{
	if (tutorial)
	{
		delete(tutorial);
		tutorial = NULL;
	}
}
/// <summary>
/// �X�V
/// </summary>
void TutorialScene::Update()
{
	//�X�V
	//tutorial->Update();
	//�V�[���̕ύX
	ChangeNextScene();
}
/// <summary>
/// �`��
/// </summary>
void TutorialScene::Draw()
{
	//tutorial->Draw();
}

/// <summary>
/// ���̃V�[����
/// </summary>
void TutorialScene::ChangeNextScene()
{
	//�C���X�^���X���擾
	//auto& sceneChange = SceneChanger::GetInstance();

	//const bool isNextScene = tutorial->GetIsChangeScene();
	//const bool isGameEnd = tutorial->GetIstutorialEnd();
	////�X�y�[�X�����͂��ꂽ��G���h�t���OON
	//if (isNextScene)
	//{
	//	//�V�[���`�F���W���ғ�������
	//	sceneChange.SetIsSceneChanger(true);
	//	sceneChange.ChangeSceneFromNowToNext(SceneType::tutorial, SceneType::GAME);
	//}
	////�X�y�[�X�����͂��ꂽ��G���h�t���OON
	//if (isGameEnd)
	//{
	//	//�V�[���`�F���W���ғ�������
	//	sceneChange.SetIsSceneChanger(true);
	//	sceneChange.ChangeSceneFromNowToNext(SceneType::tutorial, SceneType::OPENING);
	//}
}