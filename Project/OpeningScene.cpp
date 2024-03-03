//===========================================================================
//@brief �I�[�v�j���O�V�[���N���X
// �I�[�v�j���O�N���X�̎��s���V�[���x�[�X�N���X�����Ƃɍs��
//===========================================================================
#include"OpeningScene.h"
#include"SceneChanger.h"
#include"Opening.h"
#include"Common.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
OpeningScene::OpeningScene()
{
	opening = NULL;
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
OpeningScene::~OpeningScene()
{
	Final();
}
/// <summary>
/// �쐬
/// </summary>
void OpeningScene::Create()
{
	opening = new Opening();
}
/// <summary>
/// �폜
/// </summary>
void OpeningScene::Final()
{
	if (opening)
	{
		delete(opening);
		opening = NULL;
	}
}
/// <summary>
/// �X�V
/// </summary>
void OpeningScene::Update()
{
	//�X�V
	opening->Update();
	//�V�[���؂�ւ��i�t���O�����������j
	ChangeNextScene();
}
/// <summary>
/// �`��
/// </summary>
void OpeningScene::Draw()
{
	//�`��
	opening->Draw();
}

/// <summary>
/// ���̃V�[����
/// </summary>
void OpeningScene::ChangeNextScene()
{
	//�C���X�^���X���擾
	 auto &sceneChange = SceneChanger::GetInstance();

	//�����I�[�v�j���O���I�����Ă�����
	if (opening->GetIsEndOpening())
	{
		//�V�[���`�F���W���ғ�������
		sceneChange.SetIsSceneChanger(true);
		/*sceneChange.ChangeSceneFromNowToNext(SceneType::OPENING, SceneType::TITLE);*/
		sceneChange.ChangeSceneFromNowToNext(SceneType::OPENING, SceneType::GAME);
	}
}
