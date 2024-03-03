#include "CharacterBase.h"
#include"Shadow.h"
/// <summary>
/// コンストラクタ
/// </summary>
CharacterBase::CharacterBase()
	:modelHandle(INIT_MODELHANDLE)
	,pos(ORIGIN_POS)
	,rotate(ORIGIN_POS)
	,moveVec(ORIGIN_POS)
	,scale(ORIGIN_POS)
	,isInvincible(false)
	,isHit(false)
	,isMove(false)
	,isAttack(false)
	,isDeath(false)
	,shadow(nullptr)
	,attackNum(0)
{
	shadow = new Shadow();
}
/// <summary>
/// デストラクタ
/// </summary>
CharacterBase::~CharacterBase()
{
	//処理なし
}
/// <summary>
/// 初期化
/// </summary>
void CharacterBase::Init()
{
	pos = ORIGIN_POS;
	rotate = ORIGIN_POS;
	scale = ORIGIN_POS;
	modelHandle = 0;
	isHit = false;
	isInvincible = false;
	isMove = false;
	isAttack = false;
}
/// <summary>
/// カプセル情報の設定
/// </summary>
void CharacterBase::SetUpCapsule(const VECTOR _pos, const float _height, const float _radius, const int _color, const int _flag)
{
	capsuleInfo.topPos = _pos;
	capsuleInfo.topPos.y += _height;
	capsuleInfo.underPos = _pos;
	capsuleInfo.radius = _radius;
	capsuleInfo.difColor = _color;
	capsuleInfo.spcColor = _color;
	capsuleInfo.fillFlag = _flag;
}
/// <summary>
/// カプセルの描画
/// </summary>
void CharacterBase::DrawCapsule(const CapsuleInfo _capsuleInfo)
{
	DrawCapsule3D(_capsuleInfo.topPos, _capsuleInfo.underPos, _capsuleInfo.radius, _capsuleInfo.divNum, _capsuleInfo.difColor, _capsuleInfo.spcColor, _capsuleInfo.fillFlag);
}
/// <summary>
/// カプセル情報の設定
/// </summary>
void CharacterBase::SetUpSphere(const VECTOR _pos,const float _radius, const int _color, const int _flag)
{
	sphereInfo.centerPos= _pos;
	sphereInfo.radius	= _radius;
	sphereInfo.difColor = _color;
	sphereInfo.spcColor = _color;
	sphereInfo.fillFlag = _flag;
}
/// <summary>
/// カプセルの描画
/// </summary>
void CharacterBase::DrawSphere(const SphereInfo _sphereInfo)
{
	DrawSphere3D(_sphereInfo.centerPos, _sphereInfo.radius, _sphereInfo.divNum, _sphereInfo.difColor, _sphereInfo.spcColor, _sphereInfo.fillFlag);
}
void CharacterBase::DrawShadow(const int _stageModelHandle, const VECTOR _targetPos, const float _shadowHeight, const float _shadowSize)
{
	shadow->Draw(_stageModelHandle, pos, _shadowHeight, _shadowSize);
}