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

void Player::Move()
{
	/*
	//カメラの前方方向を取得
	CVector3 cameraForward = g_camera3D.GetForward();
	
	//XZ平面での前方方向、右方向に変換する。
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	
	
	 if (g_pad[0].IsPress(enButtonA))
	 {
		 //加速度を計算
		 m_moveDirectionF = cameraForward;
		 
		 m_accel = m_bikecontroller->BikeAccel(m_moveDirectionF, m_accelNum);
		 
	 }
	 else {
		 m_accel = CVector3::Zero();
	 }
	
	 m_moveSpeed += m_accel;
	 //摩擦係数を乗算
	 m_moveSpeed *= m_friction;  
	 //移動速度を計算
	 m_position += m_moveSpeed;
	 if (m_moveSpeed.LengthSq() >= 300.0f * 300.0f) {
		 m_moveSpeed.Normalize();
		 m_moveSpeed *= 300.0f;
	 }
	 
	*/
	 //敵とぶつかったらはじかれる。*/
}
void Player::Turn()
{
	//左スティックでプレイヤーを回転
	CVector3 stick; //Y軸回転用
	CVector3 stickyokokaitenn; //Z軸回転用
	CQuaternion qRot = CQuaternion::Identity();  //Y軸回転用
	
	stick.x = g_pad[0].GetLStickXF();
	stickyokokaitenn.x = g_pad[0].GetLStickXF();
	//プレイヤーの前ベクトルと進行方向の内積を求める
	CVector3 playermae = { 0, 0, 1 };
	CVector3 sinkouhoukou = g_camera3D.GetForward();
	
	//内積を計算
	
	float angle = m_bikecontroller->NaisekiTheata(playermae, sinkouhoukou);
	//外積を計算
	
	CVector3 playerjiku;
	playerjiku = m_bikecontroller->KatamukiJiku(playermae, sinkouhoukou);
	
	if (playerjiku.Length() > 0.001f)
	{
		//バイクを進行方向に向けるための回転クォータニオンを計算する。
		qRot.SetRotation(playerjiku, angle);
		//バイクを傾けるための回転クォータニオンを計算する。
		m_rotation.SetRotation(CVector3::AxisZ(), stickyokokaitenn.x * -1.0f);
	}
	//バイクを進行方向に向けるクォータニオンと
	//傾けるクォータニオンを混ぜ混ぜする。
	m_rotation.Multiply(qRot, m_rotation);
	//m_rotation.Multiply(qRot2);
	

}


void Player::Update()
{
	//バイクの移動処理を実行する。
	m_bikeMove->Execute(m_position, m_rotation, m_moveSpeed, m_accel, m_accelNum, m_friction);
	Turn();
	
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