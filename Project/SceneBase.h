//===========================================================================
//@brief ベースシーンクラス
//===========================================================================
#pragma once

class SceneBase
{
public:
	SceneBase();			//コンストラクタ
	virtual ~SceneBase();	//デストラクタ

	virtual void Create()	= 0;//生成
	virtual void Final()	= 0;//削除
	virtual void Update()	= 0;//更新
	virtual void Draw()		= 0;//描画
};

