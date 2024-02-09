#pragma once
#include<DxLib.h>
class CrackerParticleBase
{
public:
	CrackerParticleBase(const int _color);
	~CrackerParticleBase();
	void Init(const VECTOR _initPos);
	void Update();
	void Draw();
	void OffIsDraw() { isDraw = false; }
private:
	/*�ÓI�萔*/
	static constexpr int SIGN_RANGE = 1;
	static constexpr int SIZE_RANGE = 10;
	static constexpr int POS_RANGE = 5;
	static constexpr int SPEED_RANGE = 10;
	static constexpr float Y_LIMIT = 800.0f;
	static constexpr int X_LIMIT = 900;
	static constexpr int MAX_FRAME_COUNT = 10;
	/*�����o�ϐ�*/
	int color;//�F
	bool isDraw;//�`�悵�Ă��邩
	VECTOR initPos;
	VECTOR vertexPos1;
	VECTOR vertexPos2;
	VECTOR vertexPos3;
	VECTOR vertexPos2Offset;
	VECTOR vertexPos3Offset;
	VECTOR moveVec;
	float speed;
	float size;
	float count;
	/*���������֐�*/
	float ReturnRandomFloatValue(const bool _sign, const int _range);//�����_����Float�^�̒l��Ԃ�
};

