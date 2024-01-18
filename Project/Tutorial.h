//=====================================
// @brief チュートリアルクラス
// 操作説明
// すること・目的（レベルアップ）の説明
// ボスと戦う方法
//=====================================
#pragma once
class Tutorial
{
public:
	Tutorial();//コンストラクタ
	~Tutorial();//デストラクタ

	void ExplanationOfOperation();//操作の説明
	void ExplanationOfPurpose();//目的の説明
	void ExplanationOfFightingBoss();//ボス戦の説明

	//チュートリアル終了フラグのgetter
	const bool GetIsTitleEnd()const { return isTutorialEnd; }
	//シーン変更フラグのgetter
	const bool GetIsChangeScene()const { return isChangeScene; }

private:
	bool isTutorialEnd;//チュートリアル終了フラグ
	bool isOperation;//操作フラグ
	bool isPurpose;//目的フラグ
	bool isFightBoss;//ボス戦フラグ
	bool isChangeScene;//シーン変更フラグ

};

