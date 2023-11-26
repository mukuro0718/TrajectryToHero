//===========================================================================
//@brief ���C������
// �V�[���}�l�[�W���[��main�֐������s����
//===========================================================================
#include"DxLib.h"
#include"SceneManager.h"
#include"Common.h"
#include"FPSController.h"
#include"Load.h"

/// <summary>
/// ���C���֐�
/// </summary>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    //DX���C�u��������������
    if (DxLib_Init() == -1) { return -1; }

    //��ʂ̍쐬
    SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, COLOR_BIT);
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

    //���[�h�C���X�^���X�̐���
    Load::CreateInstance();
    //�V�[���}�l�[�W���[�̍쐬
    SceneManager* sceneManager = new SceneManager();

    //�Q�[���{��
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        sceneManager->mainGame();
    }
    //�V�[���Ǘ��N���X�̊J��
    delete(sceneManager);
    sceneManager = NULL;

    //DX���C�u�����̌�n��
    DxLib_End();
    //�\�t�g�̏I��
    return 0;
}
