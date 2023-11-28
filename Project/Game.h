//===========================================================================
//@brief �Q�[���V�[���N���X
// �Q�[���V�[���̏������s��
//===========================================================================
#pragma once
#include"DxLib.h"
class Camera;
class PlayerManager;

using namespace std;

class Game final
{
public:
	Game();//�R���X�g���N�^
	~Game();//�f�X�g���N�^

	void Create();//����
	void Delete();//�폜
	void Update();//�X�V
	void Draw();//�`��
	const bool GetIsEndgame() { return isEndGame; }//�Q�[���I���t���O��getter
private:
	/*���������֐�*/
    void Init();                                //������
	/*�����o�ϐ�*/
	bool isEndGame;//�Q�[�����I��������
	Camera* camera;
	PlayerManager* playerManager;
};

