//===============================================
// @brief �L����~�N���X
// �G�̃X�|�[���ʒu�ɕ`��
//===============================================
#pragma once
#include<DxLib.h>
class SpreadCircle
{
public:
	SpreadCircle(const int _graphHandle);	//�R���X�g���N�^
	~SpreadCircle();						//�f�X�g���N�^
	
	const void Init(const VECTOR _targetPos);	//������
	const void Update();						//�X�V
	const void Draw();							//�`��
private:
	/*�ÓI�萔*/
	static constexpr float			INIT_SCALE				= 10.0f;		//�������p�X�P�[��
	static constexpr float			ADD_SCALE				= 0.2f;			//�����X�P�[��
	static constexpr int			INIT_ALPHA				= 255;			//�������p�A���t�@
	static constexpr int			REMOVE_ALPHA			= -3;			//�����A���t�@
	static constexpr int			MIN_ALPHA				= 0;			//�ŏ��A���t�@
	static constexpr int			VERTEX_NUM				= 4;			//���_��
	static constexpr int			POLYGON_NUM				= 2;			//�|���S����
	static constexpr unsigned short INDEX[POLYGON_NUM * 3]	= {0,1,2,0,2,3};//�C���f�b�N�X
	
	static const VERTEX3D INIT_VERTEX;//�������p���_
	/*���������֐�*/
	const void SetPosAndAlpha();//���W�ƃA���t�@�̐ݒ�

	/*�����o�ϐ�*/
	VERTEX3D vertex[VERTEX_NUM];//���_
	VECTOR	 centerPos;			//���S���W
	float	 scale;				//�X�P�[��
	bool	 isDrawStart;		//�`�悪�n�܂��Ă��邩
	int		 alpha;				//�A���t�@
	int		 handle;			//�摜�n���h��
};

