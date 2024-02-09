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
	TutorialEnemy(const int _modelHandle);//コンストラクタ
	~TutorialEnemy();//デストラクタ
	void Init();
	void Draw(const float _playerLv);//描画
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
	void ChangeColor();//色の変更

private:
	enum class AnimationType
	{
		IDLE,
		DEATH,
	};
	static constexpr VECTOR SCALE = { 0.2f,0.2f,0.2f };//拡大率
	static constexpr VECTOR ROTATE = { 0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f };//回転率
	static constexpr VECTOR DESTROY_POS = { 500.0f, 500.0f, 500.0f };//死亡したときの座標
	static constexpr VECTOR INIT_POS = { 0.0f,0.0f,-150.0f };
	static const int CAPSULE_COLOR;
	static constexpr float RADIUS = 10.0f;
	static constexpr int MAX_FRAME_COUNT = 60;
	VECTOR pos;//座標
	int modelHandle;
	BloodParticle* blood;//血しぶきパーティクル
	CharacterStatus* status;
	Animation* anim;
	Shadow* shadow;
	StrongerUI* strongerUI;
	bool isDeath;
	bool isInvincible;
	int frameCount;
	CapsuleInfo capsule;
	VECTOR bloodBaseDir;//血しぶきパーティクルを飛ばす方向のもとになる方向

	void SetUpCapsule();
	void   ChangeAnim();					//アニメーションの変更
	bool isDamage;
	int initCount;
	bool isRespawn;
	bool isPrevColorChange;
	bool isChangeColor;//色の変更をしているかどうか
	int materialNum;//マテリアルの数
	Timer* changeColorTimer;//色変更タイマー
	std::vector<COLOR_F> difColorInfo;//ディフューズカラー情報
	std::vector<COLOR_F> spcColorInfo;//スペキュラカラー情報
	std::vector<COLOR_F> emiColorInfo;//エミッシブカラー情報
	std::vector<COLOR_F> ambColorInfo;//アンビエントカラー情報
		/*定数*/
	static const COLOR_F CHANGE_DIF_COLOR;//ディフューズカラー
	static const COLOR_F CHANGE_SPC_COLOR;//スペキュラカラー
	static const COLOR_F CHANGE_EMI_COLOR;//エミッシブカラー
	static const COLOR_F CHANGE_AMB_COLOR;//アンビエントカラー
	int animModel;
};

