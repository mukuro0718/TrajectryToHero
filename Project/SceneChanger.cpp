//===========================================================================
//@brief シーンチェンジクラス
// 各シーンの切り替えを行う
//===========================================================================
#include"SceneChanger.h"

SceneChanger* SceneChanger::sceneChange = NULL;

/// <summary>
/// コンストラクタ
/// </summary>
SceneChanger::SceneChanger()
{
	nowSceneType	 = SceneType::OPENING;		//現在のシーンの種類
	//nowSceneType = GAMEOVER;		//現在のシーンの種類
	isSceneChanger	 = false;		//切り替えフラグ
	sceneChangeTimer = FIRST_TIMER;	//シーン切り替え時間
}
/// <summary>
/// デストラクタ
/// </summary>
SceneChanger::~SceneChanger()
{
	//処理なし
}
/// <summary>
/// 次のシーンに切り替える
/// </summary>
/// <param name="nowSceneType">現在のシーン</param>
/// <param name="nextSceneType">次のシーン</param>
void SceneChanger::ChangeSceneFromNowToNext(SceneType _nowSceneType, SceneType _nextSceneType)
{
	//シーンを切り替える
	if (isSceneChanger == true)
	{
		//シーンが同じだったら（即座に切り替えないように待機時間を設ける）
		if (this->nowSceneType == _nowSceneType)
		{
			sceneChangeTimer++;//タイマー計測
			if (sceneChangeTimer >= LAST_TIMER)//もしタイマーが２０以上だったら
			{
				//次のシーンに切り替える
				this->nowSceneType = _nextSceneType;
				isSceneChanger = false;
				sceneChangeTimer = FIRST_TIMER;
			}
		}
	}
}