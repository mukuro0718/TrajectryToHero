//===========================================================================
//@brief タイトルシーンクラス
// タイトルクラスの実行をシーンベースクラスをもとに実行
//===========================================================================

#pragma once
#include"SceneBase.h"
#include"DxLib.h"

class Title;

class TitleScene:public SceneBase
{
public:
    TitleScene();					//コンストラクタ
    virtual ~TitleScene();			//デストラクタ

	void Create() override;	//シーンの生成
	void Final()  override;	//シーンの削除
	void Update() override;	//更新
	void Draw()	  override;	//描画

private:
	/*内部処理関数*/
	void ChangeNextScene();	//次のシーンへ
	void Delete();			//最終的な処分
	/*クラス*/
	Title* title;	//タイトルクラス
	/*変数*/
	int padInput;	//キーとパッドの入力状態
};

