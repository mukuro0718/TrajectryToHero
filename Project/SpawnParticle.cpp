#include "SpawnParticle.h"
#include "SpreadCircle.h"
#include "RisingCircle.h"
#include "SmokeOnCircle.h"
#include "Common.h"

const VERTEX3D SpawnParticle::INIT_VERTEX =
{
	VGet(0.0f,1.0f,0.0f),//pos
	VGet(0.0f,1.0f,0.0f),//norm
	GetColorU8(150,255,150,255),//dif
	GetColorU8(150,255,150,255),//spc
	0.0f,//u
	0.0f,//v
	0.0f,//su
	0.0f,//sv
};

/// <summary>
/// コンストラクタ
/// </summary>
SpawnParticle::SpawnParticle()
	:spreadCircle{nullptr,nullptr}
	, risingCircle{nullptr,nullptr}
	, nowStartSpreadCircle(1)
	, spreadFrameCount(0)
	, nowStartRisingCircle(1)
	, risingFrameCount(0)
	, handle(0)
	, alpha(0)
	, centerPos(ORIGIN_POS)
	,isDrawStart(false)
{
	int baseModelHandle = LoadGraph("Data/Texture/Circle.png");
	handle = LoadGraph("Data/Texture/Enemy/magicCircle3.png");
	int smokeHandle = LoadGraph("Data/Texture/smoke.png");

	Create(baseModelHandle,smokeHandle);

	SetPosAndUV();
}
/// <summary>
/// デストラクタ
/// </summary>
SpawnParticle::~SpawnParticle()
{

}
const void SpawnParticle::SetPosAndUV()
{
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		vertex[i] = INIT_VERTEX;
	}
	vertex[0].u = 0.0f;
	vertex[0].v = 0.0f;
	vertex[1].u = 1.0f;
	vertex[1].v = 0.0f;
	vertex[2].u = 1.0f;
	vertex[2].v = 1.0f;
	vertex[3].u = 0.0f;
	vertex[3].v = 1.0f;
	vertex[0].pos = VGet(INIT_SCALE, 1.0f, INIT_SCALE);
	vertex[1].pos = VGet(-INIT_SCALE, 1.0f, INIT_SCALE);
	vertex[2].pos = VGet(-INIT_SCALE, 1.0f, -INIT_SCALE);
	vertex[3].pos = VGet(INIT_SCALE, 1.0f, -INIT_SCALE);
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		vertex[i].pos = VAdd(vertex[i].pos, centerPos);
	}
}
/// <summary>
/// 作成
/// </summary>
const void SpawnParticle::Create(const int _modelHandle, const int _smokeHandle)
{
	for (int i = 0; i < SPREAD_CIRCLE_NUM; i++)
	{
		spreadCircle[i] = new SpreadCircle(_modelHandle);
	}
	for (int i = 0; i < RISING_CIRCLE_NUM; i++)
	{
		risingCircle[i] = new RisingCircle(_modelHandle);
	}
	for (int i = 0; i < SMOKE_NUM; i++)
	{
		smokeOnCircle[i] = new SmokeOnCircle(_smokeHandle);
	}
}
/// <summary>
/// 初期化
/// </summary>
const void SpawnParticle::Init(const VECTOR _targetPos, const bool _isSpawn)
{
	if (_isSpawn && !isDrawStart)
	{
		centerPos = _targetPos;
		centerPos.y = 1.0f;
		alpha = INIT_ALPHA;
		isDrawStart = true;
		for (int i = 0; i < SPREAD_CIRCLE_NUM; i++)
		{
			spreadCircle[i]->Init(centerPos);
		}
		for (int i = 0; i < RISING_CIRCLE_NUM; i++)
		{
			risingCircle[i]->Init(centerPos);
		}
		for (int i = 0; i < SMOKE_NUM; i++)
		{
			smokeOnCircle[i]->Init(centerPos);
		}
		SetPosAndUV();
	}
	if (!_isSpawn)
	{
		isDrawStart = false;
	}
}
/// <summary>
/// 更新
/// </summary>
const void SpawnParticle::Update()
{
	//描画する円の数を決める
	if (spreadFrameCount != 30)
	{
		spreadFrameCount++;
	}
	else
	{
		if (nowStartSpreadCircle < SPREAD_CIRCLE_NUM)
		{
			spreadFrameCount = 0;
			nowStartSpreadCircle++;
		}
	}
	if (risingFrameCount != 60)
	{
		risingFrameCount++;
	}
	else
	{
		if (nowStartRisingCircle < RISING_CIRCLE_NUM)
		{
			risingFrameCount = 0;
			nowStartRisingCircle++;
		}
	}

	for (int i = 0; i < nowStartSpreadCircle; i++)
	{
		//spreadCircle[i]->Init(centerPos);
		spreadCircle[i]->Update();
	}
	for (int i = 0; i < nowStartRisingCircle; i++)
	{
		//risingCircle[i]->Init(centerPos);
		risingCircle[i]->Update();
	}
	for (int i = 0; i < SMOKE_NUM; i++)
	{
		//smokeOnCircle[i]->Init(centerPos);
		smokeOnCircle[i]->Update();
	}
}
/// <summary>
/// 描画
/// </summary>
const void SpawnParticle::Draw()
{
	DrawPolygonIndexed3D(vertex, VERTEX_NUM, INDEX, POLYGON_NUM, handle, TRUE);
	for (int i = 0; i < nowStartSpreadCircle; i++)
	{
		spreadCircle[i]->Draw();
	}
	for (int i = 0; i < nowStartRisingCircle; i++)
	{
		risingCircle[i]->Draw();
	}
	for (int i = 0; i < SMOKE_NUM; i++)
	{
		smokeOnCircle[i]->Draw();
	}
}
