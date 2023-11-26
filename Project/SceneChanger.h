//===========================================================================
//@brief シーンチェンジクラス
// 各シーンの切り替えを行う
//===========================================================================
#pragma once

#include"Dxlib.h"
#include <cassert>
#include"Common.h"
class SceneChanger final
{
public:
	virtual ~SceneChanger();//デストラクタ

	void ChangeSceneFromNowToNext(SceneType _nowSceneType, SceneType _nextSceneType);//今のシーンから次のシーンへ切り替える

	//インスタンスの作成
	static void CreateInstance()
	{
		sceneChange = new SceneChanger();
	}
	// シングルトンインスタンスの取得
	static SceneChanger& GetInstance()
	{
		//HACK:assert(このプログラムを通った時、例外を発生させる)
		assert (sceneChange != NULL);
		return *sceneChange;
	}
	//インスタンスの削除
	static void DeleteInstance()
	{
		delete(sceneChange);
	}

	// 稼働中かどうかの setter/getter
	const bool& GetIsSceneChanger() const { return isSceneChanger; }
	void SetIsSceneChanger(const bool _set) { isSceneChanger = _set; }

	//シーンタイプのsetter/getter
	const SceneType& GetNowSceneType()  const { return nowSceneType; }		//現在のシーンの種類を取得
	const SceneType& GetPrevSceneType() const { return prevSceneType; }		//前のシーンタイプを取得
	void SetPrevSceneType(const SceneType _set) { prevSceneType = _set; }	//前のシーンタイプをセット

private:
	//シングルトン
	SceneChanger();//コンストラクタ
	static SceneChanger* sceneChange;

	/*メンバ変数*/
	SceneType nowSceneType;		//現在のシーンタイプ
	SceneType prevSceneType;	//前のシーンタイプ
	bool isSceneChanger;		//切り替えフラグ
	float sceneChangeTimer;		//シーン切り替え時間

	static constexpr float LAST_TIMER = 20.0f;	//タイマー最大値
	static constexpr float FIRST_TIMER = 0.0f;	//タイマー初期化値
};
