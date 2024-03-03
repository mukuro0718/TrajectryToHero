//===========================================================================
//@brief オープニングシーンクラス
// オープニングクラスの実行をシーンベースクラスをもとに行う
//===========================================================================
#include"OpeningScene.h"
#include"SceneChanger.h"
#include"Opening.h"
#include"Common.h"
/// <summary>
/// コンストラクタ
/// </summary>
OpeningScene::OpeningScene()
{
	opening = NULL;
}
/// <summary>
/// デストラクタ
/// </summary>
OpeningScene::~OpeningScene()
{
	Final();
}
/// <summary>
/// 作成
/// </summary>
void OpeningScene::Create()
{
	opening = new Opening();
}
/// <summary>
/// 削除
/// </summary>
void OpeningScene::Final()
{
	if (opening)
	{
		delete(opening);
		opening = NULL;
	}
}
/// <summary>
/// 更新
/// </summary>
void OpeningScene::Update()
{
	//更新
	opening->Update();
	//シーン切り替え（フラグが立った時）
	ChangeNextScene();
}
/// <summary>
/// 描画
/// </summary>
void OpeningScene::Draw()
{
	//描画
	opening->Draw();
}

/// <summary>
/// 次のシーンへ
/// </summary>
void OpeningScene::ChangeNextScene()
{
	//インスタンスを取得
	 auto &sceneChange = SceneChanger::GetInstance();

	//もしオープニングが終了していたら
	if (opening->GetIsEndOpening())
	{
		//シーンチェンジを稼働させる
		sceneChange.SetIsSceneChanger(true);
		/*sceneChange.ChangeSceneFromNowToNext(SceneType::OPENING, SceneType::TITLE);*/
		sceneChange.ChangeSceneFromNowToNext(SceneType::OPENING, SceneType::GAME);
	}
}
