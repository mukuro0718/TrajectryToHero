//===========================================================================
//@brief 当たり判定クラス
// 攻撃の当たり判定と移動時のキャラクター同士のめり込みの判定をする。
//===========================================================================
#pragma once
#include<DxLib.h>
#include<vector>
#include"Common.h"

using namespace std;
class Collision
{
public:
	Collision(const int _maxWeakEnemyNum,const int _maxStrongEnemyNum);//コンストラクタ
	void Init();//初期化
	~Collision();//デストラクタ
	void Delete(int modelHandle);//削除
	//プレイヤーとエネミーの攻撃時当たり判定
	bool OnDamage(const bool _isDeath, const CapsuleInfo _capsuleInfo, const SphereInfo _sphereInfo);
	
	VECTOR CapsuleToCapsuleCollision(const VECTOR _myMoveVec, const VECTOR _myVec, const VECTOR _otherVec, const float _myRadius, const float _otherRadius);//カプセル同士のめり込み判定
	VECTOR NearestPointOfSegmentPointCalc(const VECTOR _startPos,const VECTOR _endPos,const VECTOR _targetPos);//線分と点の最近接点
	bool SphereCapsuleCalc(const VECTOR _capsuleStartPos, const VECTOR _capsuleEndPos, const float _capsuleRadius, const VECTOR _spherePos, const float sphereRadius);//球とカプセルの当たり判定
	bool TwoCapsuleHitCollision(const VECTOR _topPos1, const VECTOR _underPos1, const float _radius1, const VECTOR _topPos2, const VECTOR _underPos2, const float _radius2);//カプセル同士の当たり判定
	
	const int GetHitNumPlayerForWeakEnemy(const int _enemyNum) { return playerHitNumForWeakEnemy[_enemyNum]; }
	const int GetHitNumPlayerForStrongEnemy(const int _enemyNum) { return playerHitNumForStrongEnemy[_enemyNum]; }
	const int GetHitNumPlayerForBossEnemy() { return playerHitNumForBossEnemy; }

	const int GetHitNumWeakEnemy(const int _enemyNum) { return weakEnemyHitNum[_enemyNum]; }
	const int GetHitNumStrongEnemy(const int _enemyNum) { return strongEnemyHitNum[_enemyNum]; }
	const int GetHitNumBossEnemy() { return bossEnemyHitNum; }

	const void AddHitNumPlayerForWeakEnemy(const int _enemyNum) { playerHitNumForWeakEnemy[_enemyNum]++; }
	const void AddHitNumPlayerForStrongEnemy(const int _enemyNum) { playerHitNumForStrongEnemy[_enemyNum]++; }
	const void AddHitNumPlayerForBossEnemy() { playerHitNumForBossEnemy++; }

	const void AddHitNumWeakEnemy(const int _enemyNum) { weakEnemyHitNum[_enemyNum]++; }
	const void AddHitNumStrongEnemy(const int _enemyNum) { strongEnemyHitNum[_enemyNum]++; }
	const void AddHitNumBossEnemy() { bossEnemyHitNum++; }
private:
	/*エネミー用ヒット番号*/
	vector<int> weakEnemyHitNum;
	vector<int> strongEnemyHitNum;
	int bossEnemyHitNum;
	/*プレイヤー用ヒット番号*/
	vector<int> playerHitNumForWeakEnemy;
	vector<int> playerHitNumForStrongEnemy;
	int playerHitNumForBossEnemy;
};