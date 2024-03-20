//===========================================================================
//@brief ベースシーンクラス
//===========================================================================
#pragma once

class SceneBase
{
public:
	SceneBase();			//コンストラクタ
	virtual ~SceneBase();	//デストラクタ

	virtual const void Create()	= 0;//生成
	virtual const void Final()	= 0;//削除
	virtual const void Update()	= 0;//更新
	virtual const void Draw()		= 0;//描画
};

