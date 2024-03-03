//===========================================================================
//@brief �Q�[���V�[���N���X
// �Q�[���V�[���̏������s��
//===========================================================================
#pragma once
#include"DxLib.h"
#include"Common.h"
class Camera;
class PlayerManager;
class Skydome;
class StageManager;
class StageChanger;
class EnemyManager;
class Collision;
class StatusUpParticle;
class Meteorite;
class Explosion;
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
	void FixMoveVec();//�ړ��ʕ␳
	void GameEnd(const bool _playerIsDeath_, const bool _bossIsDeath);//�Q�[���I������
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
	StatusUpParticle* statusUpParticle;
	Meteorite* meteo;
	Explosion* explosion;
	static constexpr DrawRect VICTORY_LOGO_POS = { 200, 200, 1720, 700 };
	int victoryImage;
	int alpha;
	int frameCount;
	bool isFrameCount;
	static constexpr int MAX_FRAME_COUNT = 180;
	static constexpr int MAX_ALPHA_VALUE = 155;
	static constexpr int ADD_ALPHA_VALUE = 5;
	static constexpr int MIN_ALPHA_VALUE = 0;
	static constexpr VECTOR MOVE_RANGE_POS_LTB = {  451,0  ,-840 };//���㉺
	static constexpr VECTOR MOVE_RANGE_POS_LBB = { -450,0  ,-840 };//������
	static constexpr VECTOR MOVE_RANGE_POS_RTB = {  451,0  , 510 };//�E�㉺
	static constexpr VECTOR MOVE_RANGE_POS_RBB = { -450,0  , 510 };//�E����
	static constexpr VECTOR MOVE_RANGE_POS_LTT = {  451,10 ,-840 };//�����
	static constexpr VECTOR MOVE_RANGE_POS_LBT = { -450,10 ,-840 };//������
	static constexpr VECTOR MOVE_RANGE_POS_RTT = {  451,10 , 510 };//�E���
	static constexpr VECTOR MOVE_RANGE_POS_RBT = { -450,10 , 510 };//�E����
	static const int MOVE_RANGE_COLOR;
	const void DrawMoveRange()const;
	const void DrawYouDied()const;
	int youDiedImage;
	static constexpr DrawRect YOU_DIED_BACKGROUND = { 0, 0, 1920, 1080 };
	static constexpr DrawRect YOU_DIED_LOGO = { 200, 700, 1720, 1000 };
	int youDiedFont;
	int textFont;
	static const int FONT_COLOR;//�t�H���g�̐F

	static constexpr DrawRect BACKGROUND_POS_FOR_DESCRIPTION = { 1400,30,1910,520 };
	static constexpr VEC2D TEXT_POS_FOR_DESCRIPTION = { 1420,50 };
	int strongUI;
};

