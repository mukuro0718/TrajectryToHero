//===========================================================================
//@brief �x�[�X�V�[���N���X
//===========================================================================
#pragma once

class SceneBase
{
public:
	SceneBase();			//�R���X�g���N�^
	virtual ~SceneBase();	//�f�X�g���N�^

	virtual const void Create()	= 0;//����
	virtual const void Final()	= 0;//�폜
	virtual const void Update()	= 0;//�X�V
	virtual const void Draw()		= 0;//�`��
};

