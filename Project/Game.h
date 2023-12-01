//===========================================================================
//@brief �Q�[���V�[���N���X
// �Q�[���V�[���̏������s��
//===========================================================================
#pragma once
#include"DxLib.h"
class Camera;
class PlayerManager;
class Skydome;
class StageManager;
class StageChanger;
class EnemyManager;
class Collision;

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
	void OnDamage();//�_���[�W����
	void GameEnd(const bool _playerIsDeath/*,const float _bossHP*/);//�Q�[���I������
	const bool GetIsGameOver()const { return isGameOver; }//�Q�[���I���t���O��getter
	const bool GetIsGameClear()const { return isGameClear; }
private:
	/*���������֐�*/
    void Init();                                //������
	/*�����o�ϐ�*/
	bool isGameOver;//�v���C���[�̎��S
	bool isGameClear;//�{�X�̎��S
	Camera* camera;//�J����
	PlayerManager* playerManager;//�v���C���[
	Skydome* skydome;//�X�J�C�h�[��
	StageManager* stageManager;//�X�e�[�W
	StageChanger* stageChanger;//�X�e�[�W�؂�ւ�
	EnemyManager* enemyManager;//�G�l�~�[
	Collision* collision;
};

