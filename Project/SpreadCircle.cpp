#include "SpreadCircle.h"
#include "Common.h"

const VERTEX3D SpreadCircle::INIT_VERTEX =
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
SpreadCircle::SpreadCircle(const int _graphHandle)
	:scale(INIT_SCALE)
	,isDrawStart(false)
	,centerPos(ORIGIN_POS)
	,handle(_graphHandle)
	,alpha(INIT_ALPHA)
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

}
/// <summary>
/// デストラクタ
/// </summary>
SpreadCircle::~SpreadCircle()
{

}
/// <summary>
/// 初期化
/// </summary>
const void SpreadCircle::Init(const VECTOR _targetPos)
{
	scale = INIT_SCALE;
	centerPos = _targetPos;
	alpha = INIT_ALPHA;
}
/// <summary>
/// 頂点とアルファ値の設定
/// </summary>
const void SpreadCircle::SetPosAndAlpha()
{
	vertex[0].pos = VGet( scale, 1.0f, scale);
	vertex[1].pos = VGet(-scale, 1.0f, scale);
	vertex[2].pos = VGet(-scale, 1.0f,-scale);
	vertex[3].pos = VGet( scale, 1.0f,-scale);
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		vertex[i].pos = VAdd(vertex[i].pos, centerPos);
		vertex[0].dif = GetColorU8(255, 255, 150, alpha);
		vertex[0].spc = GetColorU8(255, 255, 150, alpha);
	}
}
/// <summary>
/// 更新
/// </summary>
const void SpreadCircle::Update()
{
	scale += ADD_SCALE;
	alpha += REMOVE_ALPHA;
	SetPosAndAlpha();
	if (alpha <= MIN_ALPHA)
	{
		Init(centerPos);
	}
}
/// <summary>
/// 描画
/// </summary>
const void SpreadCircle::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawPolygonIndexed3D(vertex, VERTEX_NUM, INDEX, POLYGON_NUM, handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, INIT_ALPHA);
}
