//========================================================
// @brief チュートリアルステージクラス
// 必要なモデル以外は描画しないようにする
//========================================================
#pragma once
#include<DxLib.h>
#include<vector>


class FireParticle;
class TutorialStage final
{
public:
	TutorialStage(const std::vector<int> _data);
	~TutorialStage();

	const void Init(const std::vector<int> _data);		//初期化
	const void Draw();		//描画
	const void Delete();	//最終処理
	const void Update();	//更新

	const void OnIsShowGate() { isShowGate = true; }//表示フラグを立てる
	
	/*getter*/
	const int GetIsShowGate()		const { return isShowGate; }
	const VECTOR GetBonfirePos()	const{ return pos[static_cast<int>(DataType::BONFIRE)]; }
	const int GetGroundModelHandle()const { return data[static_cast<int>(DataType::STAGE)]; }
	const VECTOR GetGatePos()		const { return pos[static_cast<int>(DataType::GATE)]; }
private:
	/*構造体・列挙体*/
	enum class DataType
	{
		STAGE,
		GATE,
		PORTAL,
		SKYDOME,
		BONFIRE,
		FLAME,
	};
	/*静的定数*/
	static constexpr int MAX_DATA_NUM = 6;			//ロードしたデータの数
	static constexpr int MODEL_DATA_NUM = 5;		//ロードしたモデルの数
	static constexpr int FIRE_PARTICLE_NUM = 150;	//パーティクルの数

	static const VECTOR SCALE;			//拡大率
	static const VECTOR INIT_STAGE_POS;	//初期プレイヤー座標
	/*メンバ変数*/
	std::vector< FireParticle*> fire;	//ファイアクラスインスタンス
	std::vector<int> fireData;			//炎画像
	std::vector<int> data;				//ロードしたデータ
	std::vector<VECTOR> scale;			//座標
	std::vector<VECTOR> pos;			//座標
	float portalRotate;					//ポータルの回転値
	bool isShowGate;					//ゲートの表示
};

