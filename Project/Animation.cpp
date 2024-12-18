//===========================================================================
//@brief アニメーションクラス
//===========================================================================

#include"Animation.h"

/// <summary>
/// コンストラクタ
/// </summary>
Animation::Animation()
	: animAttachIndex(0)
	, prevAnim(0)
	, nowAnim(0)
	, animTotalTime(0.0f)
	, animPlayTime(0.0f)
	, isChangeAnim(false)
{
}
/// <summary>
/// デストラクタ
/// </summary>
Animation::~Animation()
{
	animModelHandle.clear();
	useAnimIndex.clear();
}
/// <summary>
/// アニメーションの追加
/// </summary>
/// <param name="animModelHandle">アタッチしたいアニメーションを持っているモデルのハンドル</param>
/// <param name="useAnimIndex">アタッチしたいアニメーションのインデックス番号</param>
void Animation::Add(int _animModelHandle,int _AnimIndex)
{
	animModelHandle.push_back(_animModelHandle);
	useAnimIndex.push_back(_AnimIndex);
}
/// <summary>
/// アニメーションのアタッチ
/// </summary>
/// <param name="animKind">アニメーションをアタッチしたいモデルのハンドル</param>
void Animation::Attach(int *_modelHandle)
{
	//アニメーションのアタッチ
	animAttachIndex = MV1AttachAnim(*_modelHandle,useAnimIndex[nowAnim], animModelHandle[nowAnim], FALSE);
	//アニメーションの総再生時間を設定
	animTotalTime = MV1GetAttachAnimTotalTime(*_modelHandle,animAttachIndex);
}
/// <summary>
/// アニメーションの再生
/// </summary>
void Animation::Play(int *_modelHandle,const float _addAnimPlayTime)
{
	//もし今までアタッチしていたアニメーションと次のアニメーションが違うなら
	if (nowAnim != prevAnim)
	{
		isChangeAnim = false;
		animPlayTime = 0.0f;
		//今までアタッチしていたアニメーションをでタッチする
		MV1DetachAnim(*_modelHandle, animAttachIndex);
		//アニメーションのアタッチ
		Attach(_modelHandle);
		prevAnim = nowAnim;
	}
	//アニメーション再生時間を設定
	MV1SetAttachAnimTime(*_modelHandle, animAttachIndex, animPlayTime);
	//アニメーション
	animPlayTime += _addAnimPlayTime;//再生時間を進める
	//再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
	if (animPlayTime >= animTotalTime)
	{
		animPlayTime = 0.0f;
		isChangeAnim = true;
	}
}
