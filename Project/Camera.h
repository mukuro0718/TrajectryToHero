//=============================================================================
// @brief  カメラクラス
//=============================================================================
#pragma once
#include "DxLib.h"
//右スティック入力構造体
struct InputRightStick
{
	int XBuf = 0;
	int YBuf = 0;
};
class Camera final
{
public:
	Camera();							// コンストラクタ
	~Camera();							// デストラクタ

	void Init  (VECTOR _playerPos);		//初期化
	void Update(VECTOR _playerPos);		// 更新

	const float  GetAngleX()		 { return angleX; };		//カメラアングルのgetter
	const VECTOR GetCameraToPlayer() { return cameraToPlayer; }	//カメラからプレイヤーへのベクトルのgetter
private:
	/*静的定数*/
	static const	 VECTOR			 DISTANCE_TO_POINT;				//注視点までの距離
	static const	 VECTOR			 UP_VECTOR_Y;					//Y軸＋が上になるようカメラを設定する用のベクトル
	static constexpr InputRightStick NONE_INPUT_VALUE	= { 0,0 };	//スティック入力がない
	static constexpr float			 CAMERA_NEAR		= 1.0f;		//カメラの近描画範囲
	static constexpr float			 CAMERA_FAR			= 2000.0f;	//カメラの遠描画範囲
	static constexpr float			 INIT_ANGLE			= 0.0f;		//初期角度
	static constexpr float			 ADD_ANGLE_VALUE	= 0.1f;		//角度増加量
	static constexpr float			 OFFSET_VALUE		= 100.0f;	//オフセット値
	static constexpr float			 ADJUST_Y_POS		= 40.0f;	//Y座標調整
	/*内部処理関数*/
	void ChangeRotate(VECTOR _playerPos);	//角度の変更
	/*メンバ変数*/
	InputRightStick inputRightStick;	//右スティック入力構造体
	VECTOR			pos;				// ポジション
	VECTOR			cameraToPlayer;		//カメラからプレイヤーへのベクトル
	float			angleX;				//Xカメラアングル
};