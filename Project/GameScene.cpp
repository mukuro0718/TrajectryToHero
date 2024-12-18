#include"GameScene.h"
#include"SceneChanger.h"
#include"Game.h"
#include"Common.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene()
{
	game = nullptr;
}
/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene()
{
	Final();
}
/// <summary>
/// 作成
/// </summary>
const void GameScene::Create()
{
	game = new Game();
}
/// <summary>
/// 削除
/// </summary>
const void GameScene::Final()
{
	if (game)
	{
		delete(game);
		game = NULL;
	}
}
/// <summary>
/// 更新
/// </summary>
const void GameScene::Update()
{
	//更新
	game->Update();
	//シーン切り替え（フラグが立った時）
	ChangeNextScene();
}
/// <summary>
/// 描画
/// </summary>
const void GameScene::Draw()
{
	//描画
	game->Draw();
}

/// <summary>
/// 次のシーンへ
/// </summary>
const void GameScene::ChangeNextScene()
{
	//インスタンスを取得
	auto& sceneChange = SceneChanger::GetInstance();
	bool isGameClear = game->GetIsGameClear();

	//もしオープニングが終了していたら
	if (isGameClear)
	{
		//シーンチェンジを稼働させる
		sceneChange.SetIsSceneChanger(true);
		sceneChange.ChangeSceneFromNowToNext(SceneType::GAME, SceneType::TITLE);
	}
}
