//===========================================================================
//@brief オープニングシーンクラス
// オープニングクラスの実行をシーンベースクラスをもとに行う
//===========================================================================

#pragma once
#include"SceneBase.h"
class Opening;

class OpeningScene :public SceneBase
{
public:
	OpeningScene();			//コンストラクタ
	virtual ~OpeningScene();//デストラクタ

	const void Create()	override;	//生成
	const void Final()	override;	//最終処理
	const void Update()	override;	//更新
	const void Draw()	override;	//描画
private:
	/*内部処理関数*/
	const void ChangeNextScene();	//次のシーンへ
	/*メンバ変数*/
	Opening* opening;	//オープニングクラス
};