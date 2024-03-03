#include "Skydome.h"
#include"Load.h"
#include"Star.h"
#include"Common.h"
#include "BloomEffect.h"
const VECTOR Skydome::SCALE = VGet(1.5f,1.5f,1.5f);
const COLOR_U8 Skydome::STAR_COLOR = GetColorU8(255, 255, 255, 255);
const VERTEX3D Skydome::ORIGIN_VERTEX =
{
	ORIGIN_POS,	//座標
	VGet(0.0f, 0.0f, -1.0f),	//法線
	STAR_COLOR,			//ディフューズカラー
	STAR_COLOR,			//スペキュラカラー
	0.0f,		//テクスチャ座標
	0.0f,		//テクスチャ座標
	0.0f,		//補助テクスチャ座標
	0.0f		//補助テクスチャ座標
};

/// <summary>
/// コンストラクタ
/// </summary>
Skydome::Skydome()
	:vertexIndex(0)
	, bloom(nullptr)
{
	bloom = new BloomEffect();
	Init();
	//for (int i = 0; i < POLYGON_NUM * 3; i++)
	//{
	//	vertexPos[i] = ORIGIN_VERTEX;
	//}
	//for (int i = 0; i < POLYGON_NUM; i++)
	//{
	//	star[i] = new Star();
	//	for (int j = 0; j < 3; j++)
	//	{
	//		vertexPos[vertexIndex].pos = star[i]->GetVertex(j);
	//		vertexIndex++;
	//	}
	//}
	bloom->MakeBloomScreen();
}
/// <summary>
/// デストラクタ
/// </summary>
Skydome::~Skydome()
{

}
/// <summary>
/// 初期化
/// </summary>
void Skydome::Init()
{
	pos = ORIGIN_POS;
	modelHandle = 0;
	auto& load = Load::GetInstance();
	load.GetSkydomeData(&modelHandle);
	MV1SetPosition(modelHandle, pos);
	MV1SetScale(modelHandle,SCALE);
}
/// <summary>
/// 描画
/// </summary>
void Skydome::Draw()
{
	MV1DrawModel(modelHandle);

	//DrawPolygon3D(vertexPos, POLYGON_NUM, DX_NONE_GRAPH, TRUE);
}