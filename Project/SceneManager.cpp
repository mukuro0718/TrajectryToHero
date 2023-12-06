//===========================================================================
//@brief �V�[���}�l�[�W���[�N���X
// �V�[���̊e���������s����
//===========================================================================
#include"SceneManager.h"
#include"SceneBase.h"
#include"OpeningScene.h"
#include"TitleScene.h"
#include"GameScene.h"
#include"GameClearScene.h"
#include"GameOverScene.h"
#include"SceneChanger.h"
#include"FPSController.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneManager::SceneManager()
{
	Create();
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneManager::~SceneManager()
{
}
/// <summary>
/// �쐬
/// </summary>
void SceneManager::Create()
{
	//�V�[���`�F���W���[�̃C���X�^���X�̐���
	SceneChanger::CreateInstance();
	// ���߂̃V�[���̍쐬�i�I�[�v�j���O����j
	scene = new OpeningScene();
	scene->Create();
	//fps�R���g���[���[�̍쐬
	fpsController = new FPSController();
}
void SceneManager::Final()
{
	//�V�[���`�F���W���[�̃C���X�^���X�̍폜
	SceneChanger::DeleteInstance();
	// �Ō�Ɏg�����V�[���̉��
	if (scene)
	{
		scene->Final();
		delete(scene);
		scene = NULL;
	}
	//fps�R���g���[���[�̍폜
	if (fpsController)
	{
		delete(fpsController);
		fpsController = NULL;
	}
}
void SceneManager::ChangeScene()
{
	//�C���X�^���X���擾
	 auto &sceneChange = SceneChanger::GetInstance();
	//���݂̃V�[�����O�̃V�[���Ɠ����^�C�v�Ȃ�؂�ւ��Ȃ�
    if (sceneChange.GetPrevSceneType() == sceneChange.GetNowSceneType()) { return; }

	//�V�[���̐؂�ւ�
	switch (sceneChange.GetNowSceneType())
	{
	case SceneType::TITLE:
		scene->Final();//�O�Ɏg�����V�[���̊J��
		scene = new TitleScene();//�V�����V�[���̎擾�iNULL�ŏ������j
		scene->Create();//�V�[���̐���
		break;
	case SceneType::GAME:
		scene->Final();//�O�Ɏg�����V�[���̊J��
		scene = new GameScene();//�V�����V�[���̎擾�iNULL�ŏ������j
		scene->Create();//�V�[���̐���
		break;
	case SceneType::GAMECLEAR:
		scene->Final();//�O�Ɏg�����V�[���̊J��
		scene = new GameClearScene();//�V�����V�[���̎擾�iNULL�ŏ������j
		scene->Create();//�V�[���̐���
		break;
	case SceneType::GAMEOVER:
		scene->Final();//�O�Ɏg�����V�[���̊J��
		scene = new GameOverScene();//�V�����V�[���̎擾�iNULL�ŏ������j
		scene->Create();//�V�[���̐���
		break;
	default:
		break;
	}
}
/// <summary>
/// �Q�[���{��
/// </summary>
void SceneManager::mainGame()
{
	//�C���X�^���X���擾
	auto &sceneChange = SceneChanger::GetInstance();
	//��ʂ̏�����
	ClearDrawScreen();
	//�X�V
	Update();
	//�`��
	Draw();
	//FPS�̕��ς��Z�o
	fpsController->Ave();
	//FPS�̕`��
	fpsController->Draw();
	//����ʂ̓��e��\��ʂɔ��f������
	ScreenFlip();
	//FPS�̏���
	fpsController->Wait();
	//�V�[���؂�ւ�
	ChangeScene();
	//���݂̃V�[���̕ۑ�
	sceneChange.SetPrevSceneType(sceneChange.GetNowSceneType());
}
/// <summary>
/// �X�V
/// </summary>
void SceneManager::Update()
{
	if (scene)
	{
		//�e�V�[�����Ƃ̍X�V����
		scene->Update();
	}
}

void SceneManager::Draw()
{
	if (scene)
	{
		//�e�V�[�����Ƃ̕`�揈��
		scene->Draw();
	}
}