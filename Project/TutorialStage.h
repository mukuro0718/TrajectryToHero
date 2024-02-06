#pragma once
#include<DxLib.h>
#include<vector>


class FireParticle;
class TutorialStage
{
public:
	TutorialStage(const std::vector<int> _data);
	~TutorialStage();

	void Init();
	void Draw();						//描画
	void Delete();						//最終処理
	void Update();						//更新
	const int GetIsShowGate() const { return isShowGate; }
	const void OnIsShowGate() { isShowGate = true; }
	const VECTOR GetBonfirePos() { return pos[static_cast<int>(DataType::BONFIRE)]; }
	const int GetGroundModelHandle() { return data[static_cast<int>(DataType::STAGE)]; }
	const VECTOR GetGatePos() { return pos[static_cast<int>(DataType::GATE)]; }
private:
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
	static constexpr int MAX_DATA_NUM = 6;//ロードしたデータの最大数
	static constexpr int MODEL_DATA_NUM = 5;
	static const VECTOR SCALE;			//拡大率
	static const VECTOR INIT_STAGE_POS;//初期プレイヤー座標
	/*メンバ変数*/
	std::vector<int> data;//ロードしたデータ
	std::vector<VECTOR> scale;//座標
	std::vector<VECTOR> pos;//座標
	float portalRotate;
	bool isShowGate;

	/*炎パーティクル*/
	static constexpr int FIRE_PARTICLE_NUM = 150;
	std::vector<int> fireData;
	std::vector< FireParticle*> fire;
};

