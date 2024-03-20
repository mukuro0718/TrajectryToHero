//===============================================
// @brief �X�|�[���G�t�F�N�g�N���X
// �G�̃X�|�[���ʒu�ɕ`��
//===============================================
#pragma once
#include<DxLib.h>

class SpreadCircle;
class RisingCircle;
class SmokeOnCircle;

class SpawnParticle
{
public:
	SpawnParticle();//�R���X�g���N�^
	~SpawnParticle();//�f�X�g���N�^

	const void Create(const int _modelHandle, const int _smokeHandle);	//�쐬
	const void Init(const VECTOR _targetPos,const bool _isSpawn);		//������
	const void Update();												//�X�V
	const void Draw();													//�`��
private:
	/*�ÓI�萔*/
	static constexpr float			INIT_SCALE				= 15.0f;			//�������p�X�P�[��
	static constexpr float			ADD_Y					= 0.2f;				//Y������
	static constexpr int			INIT_ALPHA				= 255;				//�������p�A���t�@
	static constexpr int			REMOVE_ALPHA			= -3;				//�����A���t�@
	static constexpr int			MIN_ALPHA				= 0;				//�ŏ��A���t�@
	static constexpr int			VERTEX_NUM				= 4;				//���_��
	static constexpr int			POLYGON_NUM				= 2;				//�|���S����
	static constexpr int			SPREAD_CIRCLE_NUM		= 3;				//�L����~�̐�
	static constexpr int			RISING_CIRCLE_NUM		= 3;				//�㏸����~�̐�
	static constexpr int			SMOKE_NUM				= 50;				//���̐�
	static constexpr unsigned short INDEX[POLYGON_NUM * 3]	= { 0,1,2,0,2,3 };	//�C���f�b�N�X
	
	static const VERTEX3D INIT_VERTEX;//�������p���_
	/*���������֐�*/
	const void SetPosAndUV();
	/*�ÓI�萔*/
	SpreadCircle*	spreadCircle[SPREAD_CIRCLE_NUM];//�L����~
	RisingCircle*	risingCircle[RISING_CIRCLE_NUM];//�㏸����~
	SmokeOnCircle*	smokeOnCircle[SMOKE_NUM];		//��

	VERTEX3D	vertex[VERTEX_NUM];	 //���_
	VECTOR		centerPos;			 //���S���W
	float		yPos;				 //Y���W
	bool		isDrawStart;		 //�`�悪�n�܂��Ă��邩
	int			alpha;				 //�A���t�@
	int			handle;				 //�摜�n���h��
	int			nowStartSpreadCircle;//���݂̃p�[�e�B�N���̐�
	int			spreadFrameCount;	 //�L����~�p�t���[���J�E���g
	int			nowStartRisingCircle;//���݂̃p�[�e�B�N���̐�
	int			risingFrameCount;	 //���~�p�t���[���J�E���g
};

