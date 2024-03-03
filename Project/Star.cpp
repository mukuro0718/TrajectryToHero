#include "Star.h"
#include "Common.h"


Star::Star()
{
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		vertex[i] = ORIGIN_POS;
	}
	//0”Ô–Ú‚Ì’¸“_‚ðÝ’è‚·‚é
	vertex[0] = GetRandomFirstPos();
	vertex[1] = GetRandomOtherPos();
	vertex[2] = GetRandomOtherPos();
}
Star::~Star()
{
}
const VECTOR Star::GetRandomFirstPos()
{
	VECTOR outPutPos = ORIGIN_POS;
	outPutPos.x = static_cast<float>(GetRand(POS_RANGE) * (GetRand(SIGN_RANGE) * -1));
	outPutPos.z = static_cast<float>(GetRand(POS_RANGE) * (GetRand(SIGN_RANGE) * -1));
	VECTOR distanceFromTheOriginVec = VSub(outPutPos, ORIGIN_POS);
	float distanceFromTheOriginVecSize = VSize(distanceFromTheOriginVec);
	outPutPos.y = static_cast<float>(POS_RANGE + 10) - distanceFromTheOriginVecSize;
	return outPutPos;
}
const VECTOR Star::GetRandomOtherPos()
{
	VECTOR outPutPos = ORIGIN_POS;
	outPutPos.x = static_cast<float>(SCALE * (GetRand(SIGN_RANGE) * -1));
	outPutPos.z = static_cast<float>(SCALE * (GetRand(SIGN_RANGE) * -1));
	outPutPos = VAdd(outPutPos, vertex[0]);
	return outPutPos;
}