//===========================================================================
//@brief ��ʃu���[�N���X
// �Q�lURL https://haina.hatenablog.com/entry/2016/05/17/230902
// �ŏ��̍��W���Z�b�g���ꂽ��^�C�}�[���X�^�[�g������
// �^�C�}�[���ڕW���ԂɒB�����炻�̎��̍��W���܂��L������
// 
//===========================================================================
#pragma once
#include<DxLib.h>
#include<vector>
class SwordTrail
{
public:
	SwordTrail();//�R���X�g���N�^
	~SwordTrail();//�f�X�g���N�^

	void Init();
	void Delete();

private:
	std::vector < VERTEX3D > vertexTipPos;//��[���_���W
	std::vector < VERTEX3D > vertexEndPos;//���[���_���W

	int vertexInfoCurrentHeldNum;//���ݕێ����Ă��钸�_���
};
