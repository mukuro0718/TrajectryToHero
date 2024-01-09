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
	void GetStageChangeData	(vector<int>* _image,int* _gate);	//�X�e�[�W�f�[�^��getter
	void GetEnemyData		(vector<int>* _model, int* _frameImage, int* _hpImage, int* _font);	//�G�l�~�[�f�[�^��getter
	
	void GetPlayerData		 (int* _model,int* _frameImage,int* _hpImage,int* _expImage,int* _font);	//�v���C���[�f�[�^��getter
	void GetStageData		 (int* _model);	//�X�e�[�W�f�[�^��getter
	void GetCharacterStatusData(int* _image,int* _font);	//���j���[�f�[�^��getter
	void GetShadowData		 (int* _image);	//�V���h�E�f�[�^��getter
	void GetSkydomeData		 (int* _skydomeModel);	//�X�J�C�h�[���f�[�^��getter
	void GetGameClearData	 (int* _image);//�Q�[���N���A�f�[�^��getter
	void GetGameOverData	 (int* _image);//�Q�[���N���A�f�[�^��getter

	void GetParticleData(int* _image);//�p�[�e�B�N���f�[�^��getter

	void GetStatusUIData(int* _atkImage, int* _defImage, int* _agiImage, int* font);//�X�e�[�^�XUI�f�[�^��getter
	void GetOpeUIData(int* _moveImage, int* _menuImage, int* _attackImage, int* _cameraImage);//�������UI�f�[�^��getter
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
	static constexpr int TITLE_IMAGE_NUM = 14;	//���^�C�g���摜��
	vector<int>titleImage;						//�^�C�g���摜
	/// <summary>
	/// �G�l�~�[
	/// </summary>
	static constexpr int ENEMY_MODEL_NUM = 3;		//���G�l�~�[���f����
	vector<int>enemyModel;			//�G�l�~�[���f���n���h��
	int enemyFont;
	/// <summary>
	/// �v���C���[
	/// </summary>
	int playerModel;	//�v���C���[���f���n���h��
	int playerFont;		//�v���C���[�t�H���g
	/// <summary>
	/// �X�e�[�W
	/// </summary>
	int stageModel;					//�X�e�[�W���f���n���h��
	/// <summary>
	/// �X�e�[�W�`�F���W
	/// </summary>
	static constexpr int STAGE_CHANGE_IMAGE_NUM = 3;//���X�e�[�W�`�F���W�摜��
	vector<int>stageChangeImage;	//�X�e�[�W�`�F���W�摜
	int gateImage;
	/// <summary>
	/// �X�e�[�^�X
	/// </summary>
	int characterStatusImage;		//�L�����N�^�[�X�e�[�^�X�摜
	int characterStatusFont;		//�L�����N�^�[�X�e�[�^�X�t�H���g
	/// <summary>
	/// �e
	/// </summary>
	int shadowImage;				//�e�摜
	/// <summary>
	/// �X�J�C�h�[��
	/// </summary>
	int skydomeModel;				//�X�J�C�h�[��
	/// <summary>
	/// UI
	/// </summary>
	int hpBarGraph;					//HP�o�[�摜
	int prevBarGraph;				//�ȑO�̃o�[�ʒu�`��摜
	int expBarGraph;				//�o���l�o�[�摜
	int barFrameGraph;				//�o�[�t���[���摜
	int bloodParticleImage;//���t�p�[�e�B�N���摜
	int atkUIImage;//�U����UI�摜
	int defUIImage;//�h���UI�摜
	int agiUIImage;//�f����UI�摜
	int statusUIFont;//�X�e�[�^�XUI�p�t�H���g
	int moveOpeUIImage;//�ړ�����UI�摜
	int menuOpeUIImage;//���j���[����UI�摜
	int attackOpeUIImage;//�U������UI�摜
	int cameraOpeUIImage;//�J��������UI�摜
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
