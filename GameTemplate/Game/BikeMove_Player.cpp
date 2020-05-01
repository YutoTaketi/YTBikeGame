#include "stdafx.h"
#include "BikeMove_Player.h"
#include "character/CharacterController.h"
#include "GameTime.h"
#include "Goal.h"
#include "PhysicsGhostObject.h"

BikeMove_Player::BikeMove_Player()
{
	m_bikecontroller = new BikeController();
	
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

			}
			else {
				accel = CVector3::Zero();
			}
		
		
		movespeed += accel;
		//摩擦係数を乗算
		movespeed *= friction;
		//m_finishspeed = movespeed;
		//移動速度を計算
		
			position += movespeed;
	
		if (movespeed.LengthSq() >= 300.0f * 300.0f) {
			movespeed.Normalize();
			movespeed *= 300.0f;
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
				//1.0f / 60.0f 
				GameTimeIns().GetFrameDeltaTime()
				);
		}
	
	//ゴーストオブジェクトとの当たり判定
		if ( m_goal != nullptr) {

			g_physics.ContactTest(m_charaCon, [&](const btCollisionObject& contactObject)
				{

					if (m_goal->GetGoalPoint().IsSelf(contactObject) == true) {
						Syukaihantei = true;
						if (Syukaihantei == true)
						{
							m_game->SyuukaiCount();
						}
						if (m_game->GetFinishHantei() == 4)
						{
							m_game->ChangeFinishFlag();
						}
					}
				});
		}
}