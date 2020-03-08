#include "stdafx.h"
#include "Player.h"
#include "GameObjectManager.h"
#include "BikeMove.h"
#include "BikeMove_Player.h"
Player::Player()
{
	m_model = new SkinModel();
	m_bikecontroller = new BikeController();

	//cmoファイルの読み込み。
	m_model->Init(L"Assets/modelData/playerBike.cmo");
	//バイクの移動処理を初期化
	m_bikeMove = new BikeMove_Player;
}



Player::~Player()
{

}
	

void Player::Update()
{
	//バイクの移動処理を実行する。
	
	m_bikeMove->Execute(m_position, m_rotation, m_moveSpeed, m_accel, m_accelNum, m_friction);
	//Turn();
	
	//ワールド行列の更新。
	m_model->UpdateWorldMatrix(m_position, m_rotation, CVector3{1.0f,1.0f, 1.0f});
	m_model->Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Player::Render()
{
	//m_shadowMap.RegistShadowCaster(m_model);
}
void Player::Draw()
{
	/*m_model->PostEffectDraw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);*/
}