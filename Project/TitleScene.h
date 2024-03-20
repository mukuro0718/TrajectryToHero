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

	const void Create() override;	//シーンの生成
	const void Final()  override;	//シーンの削除
	const void Update() override;	//更新
	const void Draw()	override;	//描画

private:
	/*内部処理関数*/
	const void ChangeNextScene();	//次のシーンへ
	const void Delete();			//最終的な処分
	/*クラス*/
	Title* title;	//タイトルクラス
	/*変数*/
	int padInput;	//キーとパッドの入力状態
};

