//===========================================================================
//@brief �x�[�X�V�[���N���X
//===========================================================================
#pragma once

class SceneBase
{
public:
	SceneBase();			//�R���X�g���N�^
	virtual ~SceneBase();	//�f�X�g���N�^

	virtual void Create()	= 0;//����
	virtual void Final()	= 0;//�폜
	virtual void Update()	= 0;//�X�V
	virtual void Draw()		= 0;//�`��
};

