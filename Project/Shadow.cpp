#include"Shadow.h"
#include"Load.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Shadow::Shadow()
{
	auto& load = Load::GetInstance();
	load.GetShadowData(&shadowHandle);
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
Shadow::~Shadow()
{
	Final();
}
/// <summary>
/// �ŏI����
/// </summary>
void Shadow::Final()
{
	DeleteGraph(shadowHandle);
}
/// <summary>
/// �`��
/// </summary>
void Shadow::Draw(const int _stageModelHandle,const VECTOR _targetPos,const float _shadowHeight,const float _shadowSize)
{
	MV1_COLL_RESULT_POLY_DIM groundPoly;//�v���C���[�����̒n�ʃ|���S��
	MV1_COLL_RESULT_POLY* spherePolyNum;//�������̃|���S���̐�
	VERTEX3D Vertex[3];//���_�f�[�^
	VECTOR pushBackVector;//�����߂���
	int stageModelHandle = _stageModelHandle;//�X�e�[�W���f���n���h��
	VECTOR targetPos = _targetPos;//�e���������ڕW�̍��W
	float shadowHeight = _shadowHeight;//�e�̍���
	float shadowSize = _shadowSize;//�e�̃T�C�Y

	// ���C�e�B���O�𖳌��ɂ���
	SetUseLighting(FALSE);

	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �e�N�X�`���A�h���X���[�h�� CLAMP �ɂ���( �e�N�X�`���̒[����͒[�̃h�b�g�����X���� )
	SetTextureAddressMode(DX_TEXADDRESS_CLAMP);

	// �v���C���[�̒����ɑ��݂���n�ʂ̃|���S�����擾
	groundPoly = MV1CollCheck_Capsule(_stageModelHandle, -1, _targetPos, VAdd(_targetPos, VGet(0.0f, -shadowHeight, 0.0f)), shadowSize);

	// ���_�f�[�^�ŕω��������������Z�b�g
	Vertex[0].dif = GetColorU8(255, 255, 255, 255);
	Vertex[0].spc = GetColorU8(0, 0, 0, 0);
	Vertex[0].su = 0.0f;
	Vertex[0].sv = 0.0f;
	Vertex[1] = Vertex[0];
	Vertex[2] = Vertex[0];

	// ���̒����ɑ��݂���|���S���̐������J��Ԃ�
	spherePolyNum = groundPoly.Dim;
	for (int i = 0; i < groundPoly.HitNum; i++, spherePolyNum++)
	{
		// �|���S���̍��W�͒n�ʃ|���S���̍��W
		Vertex[0].pos = spherePolyNum->Position[0];
		Vertex[1].pos = spherePolyNum->Position[1];
		Vertex[2].pos = spherePolyNum->Position[2];

		// ������Ǝ����グ�ďd�Ȃ�Ȃ��悤�ɂ���
		pushBackVector = VScale(spherePolyNum->Normal, 0.5f);
		Vertex[0].pos = VAdd(Vertex[0].pos, pushBackVector);
		Vertex[1].pos = VAdd(Vertex[1].pos, pushBackVector);
		Vertex[2].pos = VAdd(Vertex[2].pos, pushBackVector);

		// �|���S���̕s�����x��ݒ肷��
		Vertex[0].dif.a = 0;
		Vertex[1].dif.a = 0;
		Vertex[2].dif.a = 0;
		if (spherePolyNum->Position[0].y > targetPos.y - shadowHeight)
			Vertex[0].dif.a = 128 * (1.0f - fabs(spherePolyNum->Position[0].y - targetPos.y) / shadowHeight);

		if (spherePolyNum->Position[1].y > targetPos.y - shadowHeight)
			Vertex[1].dif.a = 128 * (1.0f - fabs(spherePolyNum->Position[1].y - targetPos.y) / shadowHeight);

		if (spherePolyNum->Position[2].y > targetPos.y - shadowHeight)
			Vertex[2].dif.a = 128 * (1.0f - fabs(spherePolyNum->Position[2].y - targetPos.y) / shadowHeight);

		// �t�u�l�͒n�ʃ|���S���ƃv���C���[�̑��΍��W���犄��o��
		Vertex[0].u = (spherePolyNum->Position[0].x - targetPos.x) / (shadowSize * 2.0f) + 0.5f;
		Vertex[0].v = (spherePolyNum->Position[0].z - targetPos.z) / (shadowSize * 2.0f) + 0.5f;
		Vertex[1].u = (spherePolyNum->Position[1].x - targetPos.x) / (shadowSize * 2.0f) + 0.5f;
		Vertex[1].v = (spherePolyNum->Position[1].z - targetPos.z) / (shadowSize * 2.0f) + 0.5f;
		Vertex[2].u = (spherePolyNum->Position[2].x - targetPos.x) / (shadowSize * 2.0f) + 0.5f;
		Vertex[2].v = (spherePolyNum->Position[2].z - targetPos.z) / (shadowSize * 2.0f) + 0.5f;

		// �e�|���S����`��
		DrawPolygon3D(Vertex, 1, shadowHandle, TRUE);
	}

	// ���o�����n�ʃ|���S�����̌�n��
	MV1CollResultPolyDimTerminate(groundPoly);

	// ���C�e�B���O��L���ɂ���
	SetUseLighting(TRUE);

	// �y�o�b�t�@�𖳌��ɂ���
	SetUseZBuffer3D(FALSE);

}