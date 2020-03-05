#include "stdafx.h"
#include "BikeMove_Player.h"


BikeMove_Player::BikeMove_Player()
{
	m_bikecontroller = new BikeController();
}


BikeMove_Player::~BikeMove_Player()
{
}

void BikeMove_Player::Execute(CVector3& position, CQuaternion& rotation, CVector3& movespeed, CVector3& accel, float& accelnum, float& friction)
{
	//カメラの前方方向を取得
	CVector3 cameraForward = g_camera3D.GetForward();

	//XZ平面での前方方向、右方向に変換する。
	cameraForward.y = 0.0f;
	cameraForward.Normalize();

	if (g_pad[0].IsPress(enButtonA))
	{
		//加速度を計算
		m_moveDirectionF = cameraForward;

		accel = m_bikecontroller->BikeAccel(m_moveDirectionF, accelnum);

	}
	else {
		accel = CVector3::Zero();
	}

	movespeed += accel;
	//摩擦係数を乗算
	movespeed *= friction;
	//移動速度を計算
	position += movespeed;
	if (movespeed.LengthSq() >= 300.0f * 300.0f) {
		movespeed.Normalize();
		movespeed *= 300.0f;
	}

	//回転処理

}