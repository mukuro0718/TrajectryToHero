//===========================================================================
//@brief ゲームオーバーシーンクラス
// ゲームオーバークラスの実行をシーンベースクラスをもとに行う
//===========================================================================
#include"GameOverScene.h"
#include"SceneChanger.h"
#include"GameOver.h"
/// <summary>
/// コンストラクタ
/// </summary>
GameOverScene::GameOverScene()
{
	gameOver = NULL;
}
/// <summary>
/// デストラクタ
/// </summary>
GameOverScene::~GameOverScene()
{
	Final();
}
/// <summary>
/// 作成
/// </summary>
void GameOverScene::Create()
{
	gameOver = new GameOver();
}
/// <summary>
/// 削除
/// </summary>
void GameOverScene::Final()
{
	if (gameOver)
	{
		delete(gameOver);
		gameOver = NULL;
	}
}
/// <summary>
/// 更新
/// </summary>
void GameOverScene::Update()
{
	//更新
	gameOver->Update();
	//シーン切り替え（フラグが立った時）
	ChangeNextScene();
}
/// <summary>
/// 描画
/// </summary>
void GameOverScene::Draw()
{
	gameOver->Draw();
}

/// <summary>
/// 次のシーンへ
/// </summary>
void GameOverScene::ChangeNextScene()
{
	//インスタンスを取得
	auto& sceneChange = SceneChanger::GetInstance();

	//もしオープニングが終了していたら
	if (gameOver->GetIsEndGameOverImage())
	{
		//シーンチェンジを稼働させる
		sceneChange.SetIsSceneChanger(true);
		//現在のシーンからタイトルシーンへ
		sceneChange.ChangeSceneFromNowToNext(SceneType::GAMEOVER, SceneType::TITLE);
	}
}
