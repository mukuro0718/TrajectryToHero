//===========================================================================
//@brief ���C������
// �V�[���}�l�[�W���[��main�֐������s����
//===========================================================================
#include"DxLib.h"
#include"SceneManager.h"
#include"Common.h"
#include"FPSController.h"
#include"Load.h"
#include"LoadScene.h"

/// <summary>
/// ���C���֐�
/// </summary>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    //DX���C�u��������������
    if (DxLib_Init() == -1) { return -1; }

    //��ʂ̍쐬
    SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, COLOR_BIT);
    //�t���O�𗧂Ă邱�ƂŔ񓯊����[�h���\�ɂȂ�
    SetUseASyncLoadFlag(TRUE);
    //ScreenFlip�����s���Ă����������M����҂��Ȃ�
    SetWaitVSyncFlag(FALSE);
    //�`���𗠉�ʂɂ���
    SetDrawScreen(DX_SCREEN_BACK);
    //��ʃ��[�h���E�B���h�E���[�h�ŕ`�悷�邩
#if _DEBUG
    ChangeWindowMode(TRUE);
#else
    ChangeWindowMode(FALSE);
#endif// _DEBUG
    SetUseDirect3DVersion(DX_DIRECT3D_9EX);
    //���[�h�V�[���̍쐬
    LoadScene* loadScene = new LoadScene();
    //���[�h�C���X�^���X�̐���
    Load::CreateInstance();
    //�V�[���}�l�[�W���[�̍쐬
    SceneManager* sceneManager = new SceneManager();
    //�Q�[���{��
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        if (GetASyncLoadNum() == 0)
        {
            sceneManager->mainGame();
        }
        else
        {
            loadScene->Update();
            loadScene->Draw();
        }
    }
    //�V�[���Ǘ��N���X�̊J��
    if (sceneManager)
    {
        delete(sceneManager);
        sceneManager = nullptr;
    }
    if (loadScene)
    {
        delete(loadScene);
        loadScene = nullptr;
    }

    //DX���C�u�����̌�n��
    DxLib_End();
    //�\�t�g�̏I��
    return 0;
}
