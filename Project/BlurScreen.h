//===========================================================================
//@brief ��ʃu���[�N���X
// �Q�lURL:https://qiita.com/himego/items/c043ca5d58912b9a58d2
//===========================================================================
#pragma once
#include<DxLib.h>
#include<vector>
class BlurScreen
{
public:
	BlurScreen();//�R���X�g���N�^
	~BlurScreen();//�f�X�g���N�^

	void Init(const int _alpha, const int _offsetX1, const int _offsetY1, const int _offsetX2, const int _offsetY2);
	void ReplayInit();
	void Delete();

	void PreRenderBlurScreen();

	void PostRenderBlurScreen();
private:
	static constexpr int SCREEN_INDEX = 2;//�X�N���[���ϐ��̓Y����
	static constexpr int SCREEN_INIT_VALUE = -1;//�X�N���[���ϐ��������l
	int screen[SCREEN_INDEX];//�X�N���[���ϐ�
	int current;
	int alpha;
	int screenWidth, screenHeight;
	int offsetX1, offsetX2, offsetY1, offsetY2;
	int notBlendDraw;
};
