#include "LightSword.h"
#include "Common.h"
#include "BloomEffect.h"

const VERTEX3D LightSword::INIT_VERTEX =
{
	ORIGIN_POS				 ,//座標pos
	VGet(0.0f,1.0f,0.0f)	 ,//法線norm
	GetColorU8(255,255,255,255),//ディフューズカラーdif
	GetColorU8(255,255,255,255)		 ,//スペキュラカラーspc
	0.0f					 ,//テクスチャ座標u,v
	0.0f					 ,
	0.0f					 ,//補助テクスチャ座標su,sv
	0.0f
};
const VECTOR LightSword::VERTEX_FOR_ROTATE[VERTEX_FOR_ROTATE_NUM] =
{
	VGet(100.0f, 200.0f, 0.0f),
	VGet(100.0f, 300.0f, 0.0f),
	VGet(200.0f, 200.0f, 0.0f),
};

/// <summary>
/// コンストラクタ
/// </summary>
LightSword::LightSword()
	:bladeVertex{ INIT_VERTEX,INIT_VERTEX, INIT_VERTEX, INIT_VERTEX, INIT_VERTEX }
{
	MakeRotateMatrix();//回転行列を出す
}
/// <summary>
/// デストラクタ
/// </summary>
LightSword::~LightSword()
{

}
/// <summary>
/// 更新
/// </summary>
const void LightSword::Update(const VECTOR _bladeUnderPos, const VECTOR _bladeMiddlePos,const VECTOR _bladeTopPos)
{
	//刃のベクトルを出す
	VECTOR bladeVec = VSub(_bladeTopPos,_bladeUnderPos);
	//刃のベクトルを正規化する
	bladeVec = VNorm(bladeVec);
	//firstRotateを使って、正規化したベクトルを回し、鎺のベクトルを出す
	VECTOR sickleVec = VTransform(bladeVec, rotateMatrix);
	MakeBladeVertex(bladeVec,sickleVec);
	for (int i = 0; i < BLADE_VERTEX_NUM; i++)
	{
		if (i == 0)
		{
			bladeVertex[i].pos = VAdd(bladeVertex[i].pos, _bladeTopPos);
		}
		else if (i <= 4)
		{
			bladeVertex[i].pos = VAdd(bladeVertex[i].pos, _bladeMiddlePos);
		}
		else
		{
			bladeVertex[i].pos = VAdd(bladeVertex[i].pos, _bladeUnderPos);
		}
	}
}
/// <summary>
/// 描画
/// </summary>
const void LightSword::Draw()
{
	DrawPolygonIndexed3D(bladeVertex, BLADE_VERTEX_NUM, BLADE_VERTEX_INDEX, POLYGON_NUM, DX_NONE_GRAPH, TRUE);
}
/// <summary>
/// 刃のベクトルを９０度回すベクトルを出す
/// </summary>
const void LightSword::MakeRotateMatrix()
{
	//0=1のベクトルを出す
	VECTOR zTo = VSub(VERTEX_FOR_ROTATE[1], VERTEX_FOR_ROTATE[0]);
	//正規化する
	zTo = VNorm(zTo);

	//1=2のベクトルを出す
	VECTOR zTt = VSub(VERTEX_FOR_ROTATE[2], VERTEX_FOR_ROTATE[0]);
	//正規化する
	zTt = VNorm(zTt);

	//bladeベクトルを90度回転させてsickleベクトルにするための行列
	rotateMatrix = MGetRotVec2(zTo, zTt);
}
/// <summary>
/// 刃の描画に必要な頂点を作る
/// </summary>
const void LightSword::MakeBladeVertex(const VECTOR _bladeVec,const VECTOR _sickleVec)
{
	//刃の先端の座標を出す
	bladeVertex[0].pos = VScale(_bladeVec, BLADE_SCALE);

	//sickleベクトルをbladeベクトルを軸に90,180,-90回し、各頂点の座標を出す
	bladeVertex[1].pos = VScale(_sickleVec,2.0f);
	bladeVertex[2].pos = VScale(VTransform(_sickleVec, MGetRotAxis(_bladeVec, DegToRad(90.0f))), 3.0f);
	bladeVertex[3].pos = VScale(VTransform(_sickleVec, MGetRotAxis(_bladeVec, DegToRad(180.0f))), 2.0f);
	bladeVertex[4].pos = VScale(VTransform(_sickleVec, MGetRotAxis(_bladeVec, DegToRad(-90.0f))), 3.0f);

	//sickleベクトルをbladeベクトルを軸に90,180,-90回し、各頂点の座標を出す
	bladeVertex[5].pos = VScale(_sickleVec, 3.0f);
	bladeVertex[6].pos = VScale(VTransform(_sickleVec, MGetRotAxis(_bladeVec, DegToRad(90.0f))), 2.0f);
	bladeVertex[7].pos = VScale(VTransform(_sickleVec, MGetRotAxis(_bladeVec, DegToRad(180.0f))), 3.0f);
	bladeVertex[8].pos = VScale(VTransform(_sickleVec, MGetRotAxis(_bladeVec, DegToRad(-90.0f))), 2.0f);

}
