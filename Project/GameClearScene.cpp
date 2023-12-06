//===========================================================================
//@brief ゲームクリアシーンクラス
// ゲームクリアクラスの実行をシーンベースクラスをもとに行う
//===========================================================================
#include"GameClearScene.h"
#include"SceneChanger.h"
#include"GameClear.h"
/// <summary>
/// コンストラクタ
/// </summary>
GameClearScene::GameClearScene()
{
	gameClear = NULL;
}
/// <summary>
/// デストラクタ
/// </summary>
GameClearScene::~GameClearScene()
{
	Final();
}
/// <summary>
/// 作成
/// </summary>
void GameClearScene::Create()
{
	gameClear = new GameClear();
}
/// <summary>
/// 削除
/// </summary>
void GameClearScene::Final()
{
	if (gameClear)
	{
		delete(gameClear);
		gameClear = NULL;
	}
}
/// <summary>
/// 更新
/// </summary>
void GameClearScene::Update()
{
	//更新
	gameClear->Update();
	//シーン切り替え（フラグが立った時）
	ChangeNextScene();
}
/// <summary>
/// 描画
/// </summary>
void GameClearScene::Draw()
{
	gameClear->Draw();
}

/// <summary>
/// 次のシーンへ
/// </summary>
void GameClearScene::ChangeNextScene()
{
	//インスタンスを取得
	auto& sceneChange = SceneChanger::GetInstance();

	//もしオープニングが終了していたら
	if (gameClear->GetIsEndGameClearImage())
	{
		//シーンチェンジを稼働させる
		sceneChange.SetIsSceneChanger(true);
		//現在のシーンからタイトルシーンへ
		sceneChange.ChangeSceneFromNowToNext(SceneType::GAMECLEAR, SceneType::TITLE);
	}
}
