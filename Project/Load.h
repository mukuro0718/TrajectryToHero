//===========================================================================
//@brief ���[�h�N���X
//===========================================================================
/*�ŏ��ɕK�v�Ȃ��̂��ׂĂ����[�h��
�K�v�ɉ����Ĉ����n��*/
#pragma once
#include<DxLib.h>
#include<cassert>
#include<vector>

using namespace std;
class Load final
{
public:
	virtual ~Load();//�f�X�g���N�^

	//�C���X�^���X�̐���
	static void CreateInstance()
	{
		load = new Load();
	}
	//�C���X�^���X�̎擾
	static Load& GetInstance()
	{
		//HACK:assert(���̃v���O������ʂ������A��O�𔭐�������)
		assert(load != NULL);
		return *load;
	}
	//�C���X�^���X�̍폜
	static void DeleteInstance()
	{
		delete(load);
	}
	void LoadingData();

	
	void GetOpeningData		(vector<int>* _image);	//�I�[�v�j���O�f�[�^��getter
	void GetTitleData		(vector<int>* _image);	//�^�C�g���f�[�^��getter
	void GetStageChangeData	(vector<int>* _image);	//�X�e�[�W�f�[�^��getter
	void GetEnemyData		(vector<int>* _model);	//�G�l�~�[�f�[�^��getter
	
	void GetPlayerData		 (int* _model);	//�v���C���[�f�[�^��getter
	void GetStageData		 (int* _model);	//�X�e�[�W�f�[�^��getter
	void GetStatusManagerData(int* _image);	//���j���[�f�[�^��getter
	void GetShadowData		 (int* _image);	//�V���h�E�f�[�^��getter

	void GetGameClearData	 (int* _image);//�Q�[���N���A�f�[�^��getter
	void GetGameOverData	 (int* _image);//�Q�[���N���A�f�[�^��getter
private:
	Load();//�R���X�g���N�^
	static Load* load;

	/// <summary>
	/// �I�[�v�j���O
	/// </summary>
	/*�ÓI�萔*/
	static constexpr int OPENING_IMAGE_NUM = 4;	//���I�[�v�j���O�摜��
	/*�����o�ϐ�*/
	vector<int>openingImage;					//�I�[�v�j���O�摜

	/// <summary>
	/// �^�C�g��
	/// </summary>
	/*�ÓI�萔*/
	static constexpr int TITLE_IMAGE_NUM = 14;	//���^�C�g���摜��
	/*�����o�ϐ�*/
	vector<int>titleImage;						//�^�C�g���摜

	/// <summary>
	/// �Q�[��
	/// </summary>
	/*�ÓI�萔*/
	static constexpr int ENEMY_MODEL_NUM = 3;		//���G�l�~�[���f����
	static constexpr int STAGE_CHANGE_IMAGE_NUM = 3;//���X�e�[�W�`�F���W�摜��
	/*�����o�ϐ�*/
	vector<int>enemyModel;			//�G�l�~�[���f���n���h��
	vector<int>stageChangeImage;	//�X�e�[�W�`�F���W�摜
	int playerModel;				//�v���C���[���f���n���h��
	int stageModel;					//�X�e�[�W���f���n���h��
	int statusManagerImage;			//�X�e�[�^�X�}�l�[�W���[�摜
	int shadowImage;				//�e�摜

	/// <summary>
	/// �Q�[���N���A
	/// </summary>
	/*�ÓI�萔*/
	static constexpr int GAME_CLEAR_MODEL_NUM = 2;	//���Q�[���N���A���f����
	/*�����o�ϐ�*/
	int gameClearImage;		//�Q�[���N���A�摜
	
	/// <summary>
	/// �Q�[���I�[�o�[
	/// </summary>
	/*�����o�ϐ�*/
	int gameOverImage;		//�Q�[���I�[�o�[�摜
};
