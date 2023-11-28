////===========================================================================
////@brief �G�l�~�[�x�[�X�N���X / ���
////===========================================================================
//#pragma once
//#include "DxLib.h"
//#include"Common.h"
//enum RandomSign
//{
//	PLUS,//�{
//	MINUS,//�[
//};
//class EffectManager;
//class EnemyBase 
//{
//public:
//	EnemyBase(){}						// �R���X�g���N�^
//	EnemyBase(int _humanModelHandle);	// ��������R���X�g���N�^
//	virtual ~EnemyBase();				// �f�X�g���N�^
//
//	void Draw(VECTOR _playerPos);	//�`��
//	void Final();					//�폜
//	VECTOR NewRandomPos();				//�V�������W�������_���ŕԂ�
//
//	//���z�֐��i�p����Ŏ����j
//	virtual void Update(VECTOR _playerPos) = 0;	//�X�V
//	virtual void Init() = 0;					//������
//	virtual VECTOR Move(VECTOR _playerPos) = 0;	//�ړ�
//
//	//���ʃx�[�X��getter/Setter
//	const CharacterBase& GetBase() const { return base; }
//	void SetBase(const CharacterBase _set) { base = _set; }
//	//�X�e�[�^�X��getter/Setter
//	const CharacterStatus& GetStatus() const { return status; }
//	void SetStatus(const CharacterStatus _set) { status = _set; }
//	//�|�W�V������getter/setter
//	const VECTOR& GetPos() const { return base.pos; }
//	void SetPos(const VECTOR _set) { base.pos = _set; }
//	////�����蔻���setter
//	const bool GetIsDeath()const { return base.isDeath; }
//	//���a��setter
//	const int GetRadius()const { return RADIUS; }
//protected:
//	/*�ÓI�萔*/
//	static constexpr int SPAWN_POINT_NUM = 8;			//�X�|�[���|�C���g��
//	static constexpr int RANDOM_RANGE = 7;//�����_���Ő�������l�͈̔�
//	static const VECTOR  DESTROY_POS;			//HP���O�ɂȂ����Ƃ����̍��W�ɍs��
//	
//	//���������֐�
//	void RandomWalk();
//	/*�����o�ϐ�*/
//
//	CharacterBase   base;
//	CharacterStatus status;
//	float maxHP;						//�ő�̗�
//	bool isFarmBossEnemyPos;//�t�@�[�����{�X���W���Z�b�g���邩�ǂ���
//	VECTOR spawnPoint[SPAWN_POINT_NUM];	//�X�|�[���|�C���g
//private:
//	/*�萔*/
//	static constexpr int RANDOM_X_RANGE = 300;		//�����W
//	static constexpr int RANDOM_Z_RANGE = 300;		//�����W
//	static constexpr int RANDOM_SIGN_RANGE = 1;		//����
//	static constexpr int RADIUS = 5;	//���a
//	/*�����o�ϐ�*/
//	EffectManager* effectManager;//�G�t�F�N�g
//};
//
