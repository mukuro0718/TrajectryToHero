#include "CharacterBase.h"
/// <summary>
/// コンストラクタ
/// </summary>
CharacterBase::CharacterBase()
{
	Init();
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
/// <param name="pos">座標</param>
/// <param name="height">高さ</param>
/// <param name="radius">半径</param>
/// <param name="color">色</param>
/// <param name="flag">フラグ</param>
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