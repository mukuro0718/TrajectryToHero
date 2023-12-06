//===========================================================================
//@brief シーンマネージャークラス
// シーンの各処理を実行する
//===========================================================================
#include"SceneManager.h"
#include"SceneBase.h"
#include"OpeningScene.h"
#include"TitleScene.h"
#include"GameScene.h"
#include"GameClearScene.h"
#include"GameOverScene.h"
#include"SceneChanger.h"
#include"FPSController.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneManager::SceneManager()
{
	Create();
}
/// <summary>
/// デストラクタ
/// </summary>
SceneManager::~SceneManager()
{
}
/// <summary>
/// 作成
/// </summary>
void SceneManager::Create()
{
	//シーンチェンジャーのインスタンスの生成
	SceneChanger::CreateInstance();
	// 初めのシーンの作成（オープニングから）
	scene = new OpeningScene();
	scene->Create();
	//fpsコントローラーの作成
	fpsController = new FPSController();
}
void SceneManager::Final()
{
	//シーンチェンジャーのインスタンスの削除
	SceneChanger::DeleteInstance();
	// 最後に使ったシーンの解放
	if (scene)
	{
		scene->Final();
		delete(scene);
		scene = NULL;
	}
	//fpsコントローラーの削除
	if (fpsController)
	{
		delete(fpsController);
		fpsController = NULL;
	}
}
void SceneManager::ChangeScene()
{
	//インスタンスを取得
	 auto &sceneChange = SceneChanger::GetInstance();
	//現在のシーンが前のシーンと同じタイプなら切り替えない
    if (sceneChange.GetPrevSceneType() == sceneChange.GetNowSceneType()) { return; }

	//シーンの切り替え
	switch (sceneChange.GetNowSceneType())
	{
	case SceneType::TITLE:
		scene->Final();//前に使ったシーンの開放
		scene = new TitleScene();//新しいシーンの取得（NULLで初期化）
		scene->Create();//シーンの生成
		break;
	case SceneType::GAME:
		scene->Final();//前に使ったシーンの開放
		scene = new GameScene();//新しいシーンの取得（NULLで初期化）
		scene->Create();//シーンの生成
		break;
	case SceneType::GAMECLEAR:
		scene->Final();//前に使ったシーンの開放
		scene = new GameClearScene();//新しいシーンの取得（NULLで初期化）
		scene->Create();//シーンの生成
		break;
	case SceneType::GAMEOVER:
		scene->Final();//前に使ったシーンの開放
		scene = new GameOverScene();//新しいシーンの取得（NULLで初期化）
		scene->Create();//シーンの生成
		break;
	default:
		break;
	}
}
/// <summary>
/// ゲーム本編
/// </summary>
void SceneManager::mainGame()
{
	//インスタンスを取得
	auto &sceneChange = SceneChanger::GetInstance();
	//画面の初期化
	ClearDrawScreen();
	//更新
	Update();
	//描画
	Draw();
	//FPSの平均を算出
	fpsController->Ave();
	//FPSの描画
	fpsController->Draw();
	//裏画面の内容を表画面に反映させる
	ScreenFlip();
	//FPSの処理
	fpsController->Wait();
	//シーン切り替え
	ChangeScene();
	//現在のシーンの保存
	sceneChange.SetPrevSceneType(sceneChange.GetNowSceneType());
}
/// <summary>
/// 更新
/// </summary>
void SceneManager::Update()
{
	if (scene)
	{
		//各シーンごとの更新処理
		scene->Update();
	}
}

void SceneManager::Draw()
{
	if (scene)
	{
		//各シーンごとの描画処理
		scene->Draw();
	}
}