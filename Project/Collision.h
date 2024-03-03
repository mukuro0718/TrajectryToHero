//===========================================================================
//@brief �����蔻��N���X
// �U���̓����蔻��ƈړ����̃L�����N�^�[���m�̂߂荞�݂̔��������B
//===========================================================================
#pragma once
#include<DxLib.h>
#include<vector>
#include"Common.h"

using namespace std;
class Collision
{
public:
	Collision(const int _maxWeakEnemyNum,const int _maxStrongEnemyNum);//�R���X�g���N�^
	void Init();//������
	~Collision();//�f�X�g���N�^
	void Delete(int modelHandle);//�폜
	//�v���C���[�ƃG�l�~�[�̍U���������蔻��
	bool OnDamage(const bool _isDeath, const CapsuleInfo _capsuleInfo, const SphereInfo _sphereInfo);
	
	VECTOR CapsuleToCapsuleCollision(const VECTOR _myMoveVec, const VECTOR _myVec, const VECTOR _otherVec, const float _myRadius, const float _otherRadius);//�J�v�Z�����m�̂߂荞�ݔ���
	VECTOR NearestPointOfSegmentPointCalc(const VECTOR _startPos,const VECTOR _endPos,const VECTOR _targetPos);//�����Ɠ_�̍ŋߐړ_
	bool SphereCapsuleCalc(const VECTOR _capsuleStartPos, const VECTOR _capsuleEndPos, const float _capsuleRadius, const VECTOR _spherePos, const float sphereRadius);//���ƃJ�v�Z���̓����蔻��
	bool TwoCapsuleHitCollision(const VECTOR _topPos1, const VECTOR _underPos1, const float _radius1, const VECTOR _topPos2, const VECTOR _underPos2, const float _radius2);//�J�v�Z�����m�̓����蔻��
	
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
	/*�G�l�~�[�p�q�b�g�ԍ�*/
	vector<int> weakEnemyHitNum;
	vector<int> strongEnemyHitNum;
	int bossEnemyHitNum;
	/*�v���C���[�p�q�b�g�ԍ�*/
	vector<int> playerHitNumForWeakEnemy;
	vector<int> playerHitNumForStrongEnemy;
	int playerHitNumForBossEnemy;
};