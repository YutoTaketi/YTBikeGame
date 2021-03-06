#include "stdafx.h"
#include "BikeMove_Player.h"
#include "character/CharacterController.h"
#include "GameTime.h"
#include "Goal.h"
#include "PhysicsGhostObject.h"

BikeMove_Player::BikeMove_Player()
{
	m_bikecontroller = new BikeController();
	BikeSE_Idle.Init(L"Assets/sound/BikeIdle2.wav");
	BikeSE_Soukou.Init(L"Assets/sound/BikeSoukou.wav");

}


BikeMove_Player::~BikeMove_Player()
{
	delete m_bikecontroller;
}

void BikeMove_Player::Execute(CVector3& position, CQuaternion& rotation, CVector3& movespeed, CVector3& accel, float& accelnum, float& friction)
{

	if (m_CharaConInitFlag == false)
	{
		//キャラクターコントローラーの初期化
		m_charaCon.Init(
		   45.0f,           //半径
		   100.0f,          //高さ
		   position
		);
		m_CharaConInitFlag = true;
	}
	
	
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
				BikeSE_Soukou.Play(false);

			}
			else {
				
				BikeSE_Idle.Play(false);
				accel = CVector3::Zero();
			}
		
		movespeed += accel;
		if (!g_pad[0].IsPressAnyKey()) {
			movespeed *= 1.0f;
		}
		//摩擦係数を乗算
		movespeed *= friction;
		//m_finishspeed = movespeed;
		//移動速度を計算
		
			position += movespeed;
			
			//ブレーキ
			if (g_pad[0].IsPress(enButtonB))
			{
				accel *= 0.8f;
			}
		
	
		if (movespeed.Length() >= 6000.0f) {
			movespeed.Normalize();
			movespeed *= 6000.0f;
		}






		//回転処理
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
			rotation.SetRotation(CVector3::AxisZ(), stickyokokaitenn.x * -1.0f);
		}
		rotation.Multiply(qRot, rotation);

	
		//キャラクターコントローラーの更新
		if (m_CharaConInitFlag == true)
		{
			position =  m_charaCon.Execute( movespeed, 
				
				GameTimeIns().GetFrameDeltaTime()
				);
		}
		timer++;
		if (timer >= 300) {


			//ゴーストオブジェクトとの当たり判定
			if (m_goal != nullptr) {

				g_physics.ContactTest(m_charaCon, [&](const btCollisionObject& contactObject)
					{

						if (m_goal->GetGoalPoint().IsSelf(contactObject) == true) {
							Syukaihantei = true;
							/*if (Syukaihantei == true)
							{
								m_game->LapCountUp();
							}
							if (m_game->GetLapCheck() == 2)
							{
								m_game->ChangeFinishFlag();
							}*/
							if (Syukaihantei == true)
							{
								m_game->ChangeFinishFlag();
							}
						}

					});
			}
		}
}