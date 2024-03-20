//===============================================
// 覐΃}�l�[�W���[�N���X
//===============================================
#pragma once
#include<DxLib.h>
#include<vector>
#include "Common.h"
class MeteoriteBase;
class Meteorite
{
public:
	Meteorite();	//�R���X�g���N�^
	~Meteorite();	//�f�X�g���N�^

	const void Update(const bool _isMeteo);			//�X�V
	const void Draw(const int _stageModelHandle);	//�`��
	/*getter*/
	const int GetMeteoNum() { return METEO_NUM; }
	const SphereInfo  GetSphereInfo(const int _meteoNum);
private:
	/*�ÓI�萔*/
	static constexpr int METEO_NUM = 20;

	/*�����o�ϐ�*/
	std::vector<MeteoriteBase*> base;	//覐΃x�[�X
	
	bool isInit;//���������s�������ǂ���
	bool isDraw;//�`�悵�Ă��邩
};

