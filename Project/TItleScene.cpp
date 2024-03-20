//===========================================================================
//@brief �^�C�g���V�[���N���X / �h��
//===========================================================================
#include"TitleScene.h"
#include"SceneChanger.h"
#include"Title.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleScene::TitleScene()
{
	title = NULL;
	padInput = 0;
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleScene::~TitleScene()
{
	Final();
}
/// <summary>
/// �쐬
/// </summary>
const void TitleScene::Create()
{
	title = new Title();
}
/// <summary>
/// �폜
/// </summary>
const void TitleScene::Final()
{
	if (title)
	{
		delete(title);
		title = NULL;
	}
}
/// <summary>
/// �X�V
/// </summary>
const void TitleScene::Update()
{
	//�X�V
	title->Update();
	//�V�[���̕ύX
	ChangeNextScene();
}
/// <summary>
/// �`��
/// </summary>
const void TitleScene::Draw()
{
	title->Draw();
}

/// <summary>
/// ���̃V�[����
/// </summary>
const void TitleScene::ChangeNextScene()
{
	//�C���X�^���X���擾
	auto& sceneChange = SceneChanger::GetInstance();

	const bool isNextScene = title->GetIsChangeScene();
	const bool isGameEnd = title->GetIsTitleEnd();
	//�X�y�[�X�����͂��ꂽ��G���h�t���OON
	if (isNextScene)
	{
		//�V�[���`�F���W���ғ�������
		sceneChange.SetIsSceneChanger(true);
		sceneChange.ChangeSceneFromNowToNext(SceneType::TITLE, SceneType::GAME);
	}
	//�X�y�[�X�����͂��ꂽ��G���h�t���OON
	if (isGameEnd)
	{
		//�V�[���`�F���W���ғ�������
		sceneChange.SetIsSceneChanger(true);
		sceneChange.ChangeSceneFromNowToNext(SceneType::TITLE, SceneType::OPENING);
	}
}