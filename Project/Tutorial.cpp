#include "Tutorial.h"
/// <summary>
/// コンストラクタ
/// </summary>
Tutorial::Tutorial()
	:isTutorialEnd(false)
	,isOperation(false)
	,isPurpose(false)
	,isFightBoss(false)
	,isChangeScene(false)
{

}
/// <summary>
/// デストラクタ
/// </summary>
Tutorial::~Tutorial()
{

}
/// <summary>
/// 操作の説明
/// </summary>
void Tutorial::ExplanationOfOperation()
{
	/*移動方法*/
	//ファームステージ、プレイヤー、スカイドームの描画

	/*カメラ操作*/

	/*攻撃*/

	//ゲーム中も左下に操作説明が表示されることの説明
}
/// <summary>
/// 目的の説明
/// </summary>
void Tutorial::ExplanationOfPurpose()
{
	//敵を描画・カメラを敵の位置まで移動

	//敵を倒す

	//EXPUIの説明

	//ダメージを受ける

	//HPUIの説明

	//回復

	//レベルアップ方法の説明

	//レベルアップ・ステータスアップに伴うUIの説明

}
/// <summary>
/// ボス戦の説明
/// </summary>
void Tutorial::ExplanationOfFightingBoss()
{
	//ボス戦へ移行するためのゲートを描画・カメラをゲートの位置まで移動

	//操作説明が十分かどうかを確認

	/*yes*/
	//ゲームステージへ移動

	/*no*/
	//最初からチュートリアルを説明
}