//===========================================================================
//@brief ���ʃN���X
// �e�N���X�ŋ��ʂ��Ďg���萔��֐����`
//===========================================================================

#include"Common.h"
// ���V�A����x��
float RadToDeg(float _rad) { return _rad * (180 / DX_PI_F); }

// �x�����W�A����
float DegToRad(float _deg) { return _deg * (DX_PI_F / 180); }

bool operator ==(VECTOR _vector1, VECTOR _vector2)
{
    if (_vector1.x == _vector2.x &&
        _vector1.y == _vector2.y &&
        _vector1.z == _vector2.z)
    {
        return true;
    }
    return false;
}