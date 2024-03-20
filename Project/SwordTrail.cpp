#include "SwordTrail.h"
#include "Timer.h"
#include "Common.h"
const VERTEX3D SwordTrail::INIT_VERTEX =
{
	ORIGIN_POS,	//座標
	ORIGIN_POS,	//法線
	0,			//ディフューズカラー
	0,			//スペキュラカラー
	0.0f,		//テクスチャ座標
	0.0f,		//テクスチャ座標
	0.0f,		//補助テクスチャ座標
	0.0f		//補助テクスチャ座標
};
const VECTOR SwordTrail::VERTEX_NORM = VGet(0.0f, 0.0f, -1.0f);
const COLOR_U8 SwordTrail::TRAIL_COLOR = GetColorU8(255, 255, 255, MAX_ALPHA_VALUE);
/// <summary>
/// コンストラクタ
/// </summary>
SwordTrail::SwordTrail()
	:holdVertexNum(0)
	,vertexInfo{INIT_VERTEX}
	,assignAd(0)
	,vertexSetWaitFrameCount(0)
	,frameCount(0)
	,drawTimer(nullptr)
	,isDraw(false)
{
	drawTimer = new Timer();
	drawTimer->Init(8);
	Init();
}
/// <summary>
/// デストラクタ
/// </summary>
SwordTrail::~SwordTrail()
{
	//処理なし
}
/// <summary>
/// 初期化
/// </summary>
const void SwordTrail::Init()
{
	for (int i = 0; i < 2; i++)
	{
		vertexInfo.push_back(INIT_VERTEX);
		alphaValue.push_back(MAX_ALPHA_VALUE);
	}
}
/// <summary>
/// 更新
/// </summary>
const void SwordTrail::Update(const VECTOR _topPos, const VECTOR _underPos)
{
	if (drawTimer->getIsStartTimer())
	{
		if (drawTimer->CountTimer())
		{
			drawTimer->EndTimer();
			isDraw = false;
			Delete();
		}
		else
		{
			isDraw = true;
			vertexInfo[holdVertexNum] = SetVertexInfo(_topPos);
			vertexInfo[holdVertexNum + 1] = SetVertexInfo(_underPos);
			//もしフレームカウントが４の倍数だったらベクターに要素を追加する
			if (vertexSetWaitFrameCount % 4 == 0)
			{
				//要素の追加（上下で２つの頂点を保存するため２つ）
				vertexInfo.push_back(SetVertexInfo(_topPos));
				vertexInfo.push_back(SetVertexInfo(_underPos));
				alphaValue.push_back(MAX_ALPHA_VALUE);
				alphaValue.push_back(MAX_ALPHA_VALUE);
				holdVertexNum += 2;
				//アドレスの追加
				SetVertexAd();
			}
			SetAlpha();
			++vertexSetWaitFrameCount;
		}
	}
}
/// <summary>
/// 頂点情報の設定
/// </summary>
const VERTEX3D SwordTrail::SetVertexInfo(const VECTOR _pos)
{
	VERTEX3D vertex;
	vertex.pos  = _pos			; //座標
	vertex.norm = VERTEX_NORM	; //法線
	vertex.dif  = TRAIL_COLOR	; //ディフューズカラー
	vertex.spc  = TRAIL_COLOR	; //スペキュラカラー
	vertex.u    = 0.0f			; //テクスチャ座標
	vertex.v	= 0.0f			; //テクスチャ座標
	vertex.su   = 0.0f			; //補助テクスチャ座標
	vertex.sv   = 0.0f			; //補助テクスチャ座標
	return vertex;
}
/// <summary>
/// 使用する頂点の設定
/// </summary>
const void SwordTrail::SetVertexAd()
{
		//頂点が３つで一つのポリゴンが作れるため、３つをセットする
		for (int i = 0; i < 3; i++)
		{
			vertexIndexAd.push_back(assignAd);//2,3,4
			++assignAd;//3,4,5
		}
		//頂点が３つで一つのポリゴンが作れるため、３つをセットする
		for (int i = 0; i < 3; i++)
		{
			vertexIndexAd.push_back(assignAd);//5,4,3
			--assignAd;//4,3,2
		}
		assignAd += 2;
}
/// <summary>
/// 描画
/// </summary>
const void SwordTrail::Draw()
{
	if (isDraw)
	{
		DrawPolygonIndexed3D(&vertexInfo[0], vertexInfo.size(), &vertexIndexAd[0], vertexIndexAd.size() / 3, DX_NONE_GRAPH, TRUE);
	}
}
/// <summary>
/// 削除
/// </summary>
const void SwordTrail::Delete()
{
	vertexInfo.clear();
	vertexIndexAd.clear();
	alphaValue.clear();
	vertexSetWaitFrameCount = 0;
	holdVertexNum = 0;
	assignAd = 0;
	Init();
}
/// <summary>
/// タイマーのスタート
/// </summary>
const void SwordTrail::StartTimer()
{
	drawTimer->StartTimer();
}
/// <summary>
/// タイマークラスのスタートフラグのゲッター
/// </summary>
const bool SwordTrail::GetIsStartTimer() 
{
	return drawTimer->getIsStartTimer();
}
/// <summary>
/// アルファ値の設定
/// </summary>
const void SwordTrail::SetAlpha()
{
	for (int i = 0; i < holdVertexNum; i++)
	{
		vertexInfo[i].dif.a = alphaValue[i];
		vertexInfo[i].spc.a = alphaValue[i];
		alphaValue[i] -= ADD_ALPHA_VALUE;
		if (alphaValue[i] < 0)
		{
			alphaValue[i] = 0;
		}
	}
}