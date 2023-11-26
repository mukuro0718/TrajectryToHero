//===========================================================================
//@brief �V�[���`�F���W�N���X
// �e�V�[���̐؂�ւ����s��
//===========================================================================
#pragma once

#include"Dxlib.h"
#include <cassert>
#include"Common.h"
class SceneChanger final
{
public:
	virtual ~SceneChanger();//�f�X�g���N�^

	void ChangeSceneFromNowToNext(SceneType _nowSceneType, SceneType _nextSceneType);//���̃V�[�����玟�̃V�[���֐؂�ւ���

	//�C���X�^���X�̍쐬
	static void CreateInstance()
	{
		sceneChange = new SceneChanger();
	}
	// �V���O���g���C���X�^���X�̎擾
	static SceneChanger& GetInstance()
	{
		//HACK:assert(���̃v���O������ʂ������A��O�𔭐�������)
		assert (sceneChange != NULL);
		return *sceneChange;
	}
	//�C���X�^���X�̍폜
	static void DeleteInstance()
	{
		delete(sceneChange);
	}

	// �ғ������ǂ����� setter/getter
	const bool& GetIsSceneChanger() const { return isSceneChanger; }
	void SetIsSceneChanger(const bool _set) { isSceneChanger = _set; }

	//�V�[���^�C�v��setter/getter
	const SceneType& GetNowSceneType()  const { return nowSceneType; }		//���݂̃V�[���̎�ނ��擾
	const SceneType& GetPrevSceneType() const { return prevSceneType; }		//�O�̃V�[���^�C�v���擾
	void SetPrevSceneType(const SceneType _set) { prevSceneType = _set; }	//�O�̃V�[���^�C�v���Z�b�g

private:
	//�V���O���g��
	SceneChanger();//�R���X�g���N�^
	static SceneChanger* sceneChange;

	/*�����o�ϐ�*/
	SceneType nowSceneType;		//���݂̃V�[���^�C�v
	SceneType prevSceneType;	//�O�̃V�[���^�C�v
	bool isSceneChanger;		//�؂�ւ��t���O
	float sceneChangeTimer;		//�V�[���؂�ւ�����

	static constexpr float LAST_TIMER = 20.0f;	//�^�C�}�[�ő�l
	static constexpr float FIRST_TIMER = 0.0f;	//�^�C�}�[�������l
};
