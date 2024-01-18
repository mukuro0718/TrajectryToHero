//===========================================================================
//@brief タイトルシーンクラス / 派生
//===========================================================================
#include"TutorialScene.h"
#include"SceneChanger.h"
#include"Tutorial.h"
/// <summary>
/// コンストラクタ
/// </summary>
TutorialScene::TutorialScene()
{
	tutorial = NULL;
	padInput = 0;
}
/// <summary>
/// デストラクタ
/// </summary>
TutorialScene::~TutorialScene()
{
	Final();
}
/// <summary>
/// 作成
/// </summary>
void TutorialScene::Create()
{
	tutorial = new Tutorial();
}
/// <summary>
/// 削除
/// </summary>
void TutorialScene::Final()
{
	if (tutorial)
	{
		delete(tutorial);
		tutorial = NULL;
	}
}
/// <summary>
/// 更新
/// </summary>
void TutorialScene::Update()
{
	//更新
	//tutorial->Update();
	//シーンの変更
	ChangeNextScene();
}
/// <summary>
/// 描画
/// </summary>
void TutorialScene::Draw()
{
	//tutorial->Draw();
}

/// <summary>
/// 次のシーンへ
/// </summary>
void TutorialScene::ChangeNextScene()
{
	//インスタンスを取得
	//auto& sceneChange = SceneChanger::GetInstance();

	//const bool isNextScene = tutorial->GetIsChangeScene();
	//const bool isGameEnd = tutorial->GetIstutorialEnd();
	////スペースが入力されたらエンドフラグON
	//if (isNextScene)
	//{
	//	//シーンチェンジを稼働させる
	//	sceneChange.SetIsSceneChanger(true);
	//	sceneChange.ChangeSceneFromNowToNext(SceneType::tutorial, SceneType::GAME);
	//}
	////スペースが入力されたらエンドフラグON
	//if (isGameEnd)
	//{
	//	//シーンチェンジを稼働させる
	//	sceneChange.SetIsSceneChanger(true);
	//	sceneChange.ChangeSceneFromNowToNext(SceneType::tutorial, SceneType::OPENING);
	//}
}