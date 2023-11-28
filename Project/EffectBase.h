//===========================================================================
//@brief �G�t�F�N�g�x�[�X�N���X
// �e�G�t�F�N�g�N���X�K�v�Ȋ֐��̒�`���s��
//===========================================================================
#pragma once
#include<DxLib.h>

class EffectBase
{
public:
	EffectBase(){}					//�R���X�g���N�^
	EffectBase(int _modelHandle);	//��������R���X�g���N�^
	virtual ~EffectBase();			//�f�X�g���N�^

	void Delete();	//�폜
	void Draw();	//������

	virtual void Init(VECTOR _pos,VECTOR _direction) = 0;	//������
	virtual void Update() = 0;								//�X�V

	//���W��getter
	const VECTOR GetPos()		const { return pos; }
	//������getter
	const VECTOR GetDirection() const { return direction; }
protected:
	/*�ϐ�*/
	VECTOR pos;			//�g�U����G�t�F�N�g�̍��W
	VECTOR direction;	//�g�U�������
	int	   modelHandle;	//�g�U����G�t�F�N�g�̃��f��
};