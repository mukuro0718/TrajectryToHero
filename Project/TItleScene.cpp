//===========================================================================
//@brief タイトルシーンクラス / 派生
//===========================================================================
#include"TitleScene.h"
#include"SceneChanger.h"
#include"Title.h"
/// <summary>
/// コンストラクタ
/// </summary>
TitleScene::TitleScene()
{
	title = NULL;
	padInput = 0;
}
/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
	Final();
}
/// <summary>
/// 作成
/// </summary>
void TitleScene::Create()
{
	title = new Title();
}
/// <summary>
/// 削除
/// </summary>
void TitleScene::Final()
{
	if (title)
	{
		delete(title);
		title = NULL;
	}
}
/// <summary>
/// 更新
/// </summary>
void TitleScene::Update()
{
	//更新
	title->Update();
	//シーンの変更
	ChangeNextScene();
}
/// <summary>
/// 描画
/// </summary>
void TitleScene::Draw()
{
	title->Draw();
}

/// <summary>
/// 次のシーンへ
/// </summary>
void TitleScene::ChangeNextScene()
{
	//インスタンスを取得
	auto& sceneChange = SceneChanger::GetInstance();

	const bool isNextScene = title->GetIsChangeScene();
	const bool isGameEnd = title->GetIsTitleEnd();
	//スペースが入力されたらエンドフラグON
	if (isNextScene)
	{
		//シーンチェンジを稼働させる
		sceneChange.SetIsSceneChanger(true);
		sceneChange.ChangeSceneFromNowToNext(SceneType::TITLE, SceneType::GAME);
	}
	//スペースが入力されたらエンドフラグON
	if (isGameEnd)
	{
		//シーンチェンジを稼働させる
		sceneChange.SetIsSceneChanger(true);
		sceneChange.ChangeSceneFromNowToNext(SceneType::TITLE, SceneType::OPENING);
	}
}