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
class LightSword;



using namespace std;
class Game final
{
public:
	Game();//�R���X�g���N�^
	~Game();//�f�X�g���N�^

	const void Create();	//����
	const void Delete();	//�폜
	const void Update();	//�X�V
	const void Draw();		//�`��
	const void OnDamage();	//�_���[�W����
	const void FixMoveVec();//�ړ��ʕ␳

	const void GameEnd(const bool _playerIsDeath_, const bool _bossIsDeath);//�Q�[���I������
	
	/*getter*/
	const bool GetIsGameOver()const { return isGameOver; }	//�Q�[���I���t���O��getter
	const bool GetIsGameClear()const { return isGameClear; }
private:
	/*�ÓI�萔*/
	static constexpr DrawRect VICTORY_LOGO_POS				 = { 200, 200, 1720, 700 };	//�������S�w�i
	static constexpr DrawRect YOU_DIED_BACKGROUND			 = { 0, 0, 1920, 1080 };	//���S���S�w�i���W
	static constexpr DrawRect YOU_DIED_LOGO					 = { 200, 700, 1720, 1000 };//���S���S���W
	static constexpr DrawRect BACKGROUND_POS_FOR_DESCRIPTION = { 1400,30,1910,520 };	//�r�����W
	static constexpr VECTOR	  MOVE_RANGE_POS_LBB			 = { -450,0  ,-840 };		//������
	static constexpr VECTOR   MOVE_RANGE_POS_RTB			 = {  451,0  , 510 };		//�E�㉺
	static constexpr VECTOR   MOVE_RANGE_POS_RBB			 = { -450,0  , 510 };		//�E����
	static constexpr VECTOR   MOVE_RANGE_POS_LTT			 = {  451,10 ,-840 };		//�����
	static constexpr VECTOR   MOVE_RANGE_POS_LBT			 = { -450,10 ,-840 };		//������
	static constexpr VECTOR   MOVE_RANGE_POS_RTT			 = {  451,10 , 510 };		//�E���
	static constexpr VECTOR   MOVE_RANGE_POS_RBT			 = { -450,10 , 510 };		//�E����
	static constexpr VECTOR   MOVE_RANGE_POS_LTB			 = {  451,0  ,-840 };		//���㉺
	static constexpr VEC2D    TEXT_POS_FOR_DESCRIPTION		 = { 1420,50 };				//�e�L�X�g���W
	static constexpr int	  MAX_FRAME_COUNT				 = 180;						//�ő�t���[��
	static constexpr int	  MAX_ALPHA_VALUE				 = 155;						//�ő�A���t�@
	static constexpr int	  ADD_ALPHA_VALUE				 = 5;						//�ǉ��A���t�@
	static constexpr int	  MIN_ALPHA_VALUE				 = 0;						//�ŏ��A���t�@

	static const	 int	  MOVE_RANGE_COLOR;	//�ړ��͈͕\���J���[
	static const	 int	  FONT_COLOR;		//�t�H���g�̐F

	/*���������֐�*/
    const void Init();	//������
	const void DrawMoveRange()const;

	/*�����o�ϐ�*/
	StatusUpParticle*	statusUpParticle;	//�X�e�[�^�X�֘A�̃p�[�e�B�N��
	PlayerManager*		playerManager;		//�v���C���[
	StageManager*		stageManager;		//�X�e�[�W
	StageChanger*		stageChanger;		//�X�e�[�W�؂�ւ�
	EnemyManager*		enemyManager;		//�G�l�~�[
	LightSword*			lightSword;			//���̌�
	Collision*			collision;			//�R���W����
	Meteorite*			meteo;				//覐�
	Explosion*			explosion;			//����
	Skydome*			skydome;			//�X�J�C�h�[��
	Camera*				camera;				//�J����

	bool isGameOver;	//�v���C���[�̎��S
	bool isGameClear;	//�{�X�̎��S
	bool isFrameCount;	//�t���[���J�E���g���s����
	int  victoryImage;	//�����摜
	int  alpha;			//�A���t�@
	int  frameCount;	//�t���[���J�E���g
	int  youDiedImage;	//���S�摜
	int  youDiedFont;	//���S�t�H���g
	int  textFont;		//�e�L�X�g
	int  strongUI;		//���G�}�[�N�摜
};

