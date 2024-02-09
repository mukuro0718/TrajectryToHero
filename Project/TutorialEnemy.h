#pragma once
#include<DxLib.h>
#include"Common.h"
#include<vector>
class WeakEnemy;
class CharacterStatus;
class Animation;
class Shadow;
class StrongerUI;
class BloodParticle;
class Timer;

class TutorialEnemy
{
public:
	TutorialEnemy(const int _modelHandle);//�R���X�g���N�^
	~TutorialEnemy();//�f�X�g���N�^
	void Init();
	void Draw(const float _playerLv);//�`��
	void Update();
	float CalcHP(const float _atk, const VECTOR _attackPos);
	const bool GetIsDeath()const { return isDeath; }
	const VECTOR GetPos()const { return pos; }
	const float GetRadius()const { return RADIUS; }
	const CapsuleInfo GetCapsuleInfo()const { return capsule; }
	const void InitExpToGive();
	const void DrawShadow(const int _stageModelHandle);
	const bool GetIsDamage()const { return isDamage; }
	const void OnIsDamage() { isDamage = false; }
	const bool GetIsRespawn() { return isRespawn; }
	void ChangeColor();//�F�̕ύX

private:
	enum class AnimationType
	{
		IDLE,
		DEATH,
	};
	static constexpr VECTOR SCALE = { 0.2f,0.2f,0.2f };//�g�嗦
	static constexpr VECTOR ROTATE = { 0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f };//��]��
	static constexpr VECTOR DESTROY_POS = { 500.0f, 500.0f, 500.0f };//���S�����Ƃ��̍��W
	static constexpr VECTOR INIT_POS = { 0.0f,0.0f,-150.0f };
	static const int CAPSULE_COLOR;
	static constexpr float RADIUS = 10.0f;
	static constexpr int MAX_FRAME_COUNT = 60;
	VECTOR pos;//���W
	int modelHandle;
	BloodParticle* blood;//�����Ԃ��p�[�e�B�N��
	CharacterStatus* status;
	Animation* anim;
	Shadow* shadow;
	StrongerUI* strongerUI;
	bool isDeath;
	bool isInvincible;
	int frameCount;
	CapsuleInfo capsule;
	VECTOR bloodBaseDir;//�����Ԃ��p�[�e�B�N�����΂������̂��ƂɂȂ����

	void SetUpCapsule();
	void   ChangeAnim();					//�A�j���[�V�����̕ύX
	bool isDamage;
	int initCount;
	bool isRespawn;
	bool isPrevColorChange;
	bool isChangeColor;//�F�̕ύX�����Ă��邩�ǂ���
	int materialNum;//�}�e���A���̐�
	Timer* changeColorTimer;//�F�ύX�^�C�}�[
	std::vector<COLOR_F> difColorInfo;//�f�B�t���[�Y�J���[���
	std::vector<COLOR_F> spcColorInfo;//�X�y�L�����J���[���
	std::vector<COLOR_F> emiColorInfo;//�G�~�b�V�u�J���[���
	std::vector<COLOR_F> ambColorInfo;//�A���r�G���g�J���[���
		/*�萔*/
	static const COLOR_F CHANGE_DIF_COLOR;//�f�B�t���[�Y�J���[
	static const COLOR_F CHANGE_SPC_COLOR;//�X�y�L�����J���[
	static const COLOR_F CHANGE_EMI_COLOR;//�G�~�b�V�u�J���[
	static const COLOR_F CHANGE_AMB_COLOR;//�A���r�G���g�J���[
	int animModel;
};

