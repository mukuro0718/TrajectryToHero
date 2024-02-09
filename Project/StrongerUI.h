#pragma once
#include<DxLib.h>
class StrongerUI
{
public:
	StrongerUI();
	~StrongerUI();

	void Update(const VECTOR _enemyPos, const int _modelHandle, const int _frameNum);
	const void Draw(const float playerLv, const float enemyLv) const;
private:
	int imageHandle;
	VECTOR pos;
	float size;
	float angle;
};

