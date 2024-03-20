#include "SwordTrail.h"
#include "Timer.h"
#include "Common.h"
const VERTEX3D SwordTrail::INIT_VERTEX =
{
	ORIGIN_POS,	//���W
	ORIGIN_POS,	//�@��
	0,			//�f�B�t���[�Y�J���[
	0,			//�X�y�L�����J���[
	0.0f,		//�e�N�X�`�����W
	0.0f,		//�e�N�X�`�����W
	0.0f,		//�⏕�e�N�X�`�����W
	0.0f		//�⏕�e�N�X�`�����W
};
const VECTOR SwordTrail::VERTEX_NORM = VGet(0.0f, 0.0f, -1.0f);
const COLOR_U8 SwordTrail::TRAIL_COLOR = GetColorU8(255, 255, 255, MAX_ALPHA_VALUE);
/// <summary>
/// �R���X�g���N�^
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
/// �f�X�g���N�^
/// </summary>
SwordTrail::~SwordTrail()
{
	//�����Ȃ�
}
/// <summary>
/// ������
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
/// �X�V
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
			//�����t���[���J�E���g���S�̔{����������x�N�^�[�ɗv�f��ǉ�����
			if (vertexSetWaitFrameCount % 4 == 0)
			{
				//�v�f�̒ǉ��i�㉺�łQ�̒��_��ۑ����邽�߂Q�j
				vertexInfo.push_back(SetVertexInfo(_topPos));
				vertexInfo.push_back(SetVertexInfo(_underPos));
				alphaValue.push_back(MAX_ALPHA_VALUE);
				alphaValue.push_back(MAX_ALPHA_VALUE);
				holdVertexNum += 2;
				//�A�h���X�̒ǉ�
				SetVertexAd();
			}
			SetAlpha();
			++vertexSetWaitFrameCount;
		}
	}
}
/// <summary>
/// ���_���̐ݒ�
/// </summary>
const VERTEX3D SwordTrail::SetVertexInfo(const VECTOR _pos)
{
	VERTEX3D vertex;
	vertex.pos  = _pos			; //���W
	vertex.norm = VERTEX_NORM	; //�@��
	vertex.dif  = TRAIL_COLOR	; //�f�B�t���[�Y�J���[
	vertex.spc  = TRAIL_COLOR	; //�X�y�L�����J���[
	vertex.u    = 0.0f			; //�e�N�X�`�����W
	vertex.v	= 0.0f			; //�e�N�X�`�����W
	vertex.su   = 0.0f			; //�⏕�e�N�X�`�����W
	vertex.sv   = 0.0f			; //�⏕�e�N�X�`�����W
	return vertex;
}
/// <summary>
/// �g�p���钸�_�̐ݒ�
/// </summary>
const void SwordTrail::SetVertexAd()
{
		//���_���R�ň�̃|���S�������邽�߁A�R���Z�b�g����
		for (int i = 0; i < 3; i++)
		{
			vertexIndexAd.push_back(assignAd);//2,3,4
			++assignAd;//3,4,5
		}
		//���_���R�ň�̃|���S�������邽�߁A�R���Z�b�g����
		for (int i = 0; i < 3; i++)
		{
			vertexIndexAd.push_back(assignAd);//5,4,3
			--assignAd;//4,3,2
		}
		assignAd += 2;
}
/// <summary>
/// �`��
/// </summary>
const void SwordTrail::Draw()
{
	if (isDraw)
	{
		DrawPolygonIndexed3D(&vertexInfo[0], vertexInfo.size(), &vertexIndexAd[0], vertexIndexAd.size() / 3, DX_NONE_GRAPH, TRUE);
	}
}
/// <summary>
/// �폜
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
/// �^�C�}�[�̃X�^�[�g
/// </summary>
const void SwordTrail::StartTimer()
{
	drawTimer->StartTimer();
}
/// <summary>
/// �^�C�}�[�N���X�̃X�^�[�g�t���O�̃Q�b�^�[
/// </summary>
const bool SwordTrail::GetIsStartTimer() 
{
	return drawTimer->getIsStartTimer();
}
/// <summary>
/// �A���t�@�l�̐ݒ�
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