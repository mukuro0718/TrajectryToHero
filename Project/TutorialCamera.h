//=============================================================================
// @brief チュートリアルカメラクラス
// ゲームシーンのカメラクラスをもとに、チュートリアル用の変更を加える（継承はしない）
//=============================================================================
#include "Camera.h"

#pragma once
#include<DxLib.h>
class TutorialCamera final
{
public:
	TutorialCamera();							// コンストラクタ
	~TutorialCamera();							// デストラクタ

	const void Init(const VECTOR _playerPos);		//初期化
	const void Update(const VECTOR _playerPos);		// 更新

	const float  GetAngleX() { return angleX; };		//カメラアングルのgetter
	const VECTOR GetCameraToPlayer() { return cameraToPlayer; }	//カメラからプレイヤーへのベクトルのgetter
private:
	//右スティック入力構造体
	struct InputRightStick
	{
		int XBuf = 0;
		int YBuf = 0;
	};

	/*静的定数*/
	static constexpr InputRightStick NONE_INPUT		  = { 0,0 };	//スティック入力がない
	static constexpr float			 CAMERA_NEAR	  = 0.1f;		//カメラの近描画範囲
	static constexpr float			 CAMERA_FAR		  = 2600.0f;	//カメラの遠描画範囲
	static constexpr float			 INIT_ANGLE		  = 0.0f;		//初期角度
	static constexpr float			 ADD_ANGLE		  = 0.1f;		//角度増加量
	static constexpr float			 OFFSET_VALUE	  = 100.0f;		//オフセット値
	static constexpr float			 ADJUST_Y_POS	  = 40.0f;		//Y座標調整

	static const VECTOR	DISTANCE_TO_POINT;	//注視点までの距離
	static const VECTOR	UP_VECTOR_Y;		//Y軸＋が上になるようカメラを設定する用のベクトル
	/*内部処理関数*/
	void ChangeRotate(const VECTOR _playerPos);	//角度の変更
	/*メンバ変数*/
	InputRightStick inputRightStick;	//右スティック入力構造体
	VECTOR			pos;				//座標
	VECTOR			targetPos;			//目標の座標
	VECTOR			cameraToPlayer;		//カメラからプレイヤーへのベクトル
	float			angleX;				//Xカメラアングル
};

