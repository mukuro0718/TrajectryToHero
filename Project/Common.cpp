//===========================================================================
//@brief 共通クラス
// 各クラスで共通して使う定数や関数を定義
//===========================================================================

#include"Common.h"
// ラシアンを度に
float RadToDeg(float _rad) { return _rad * (180 / DX_PI_F); }

// 度をラジアンに
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