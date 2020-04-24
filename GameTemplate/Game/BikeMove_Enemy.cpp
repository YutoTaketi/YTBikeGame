#include "stdafx.h"
#include "BikeMove_Enemy.h"
#include "Game.h"
#include "character/CharacterController.h"
#include "GameTime.h"

BikeMove_Enemy::BikeMove_Enemy()
{
	m_bikecontroller = new BikeController();
}


BikeMove_Enemy::~BikeMove_Enemy()
{
	
}

void BikeMove_Enemy::Execute(CVector3& position, CQuaternion& rotation, CVector3& movespeed, CVector3& accel, float& accelnum, float& friction)
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

	//移動ポイントの番号を取得
	CVector3 diff = m_point->s_position - position;
	//if (m_game->GetFinishFlag() == false) 
	//{
		if (diff.LengthSq() <= 1000.0f) {
			m_point = m_game->GetNextNumber(m_point->s_number);
		}
	//}
	movespeed = m_point->s_position - position;
	movespeed.Normalize();
	accel = movespeed * accelnum;
	movespeed += accel;
	//摩擦係数を乗算
	movespeed *= friction;
	//移動速度を計算
	position += movespeed;
	

	//回転処理
	//ポイントとの距離
	CVector3 pointLen = m_point->s_position - position;
	//バイクの前方向
	CVector3 bikemae = { 0, 0, 1 };
	//バイクの進行方向
	CVector3 sinkouhoukou = pointLen;
	CQuaternion qRot = CQuaternion::Identity();  //Y軸回転用
	//内積のθを求める
	float angle = m_bikecontroller->NaisekiTheata(bikemae, sinkouhoukou);
	//Z軸回転の軸を求める
	CVector3 jiku;
	jiku = m_bikecontroller->KatamukiJiku(bikemae, sinkouhoukou);

	//バイクを進行方向に向けるクォータニオンと
	//傾けるクォータニオンを混ぜ混ぜする。
	if (jiku.Length() > 0.001f)
	{
		//バイクを進行方向に向けるための回転クォータニオンを計算する。
		qRot.SetRotation(jiku, angle);
		//バイクを傾けるための条件
		CVector3 TiltConditions = position - m_point->s_position;
		//右傾き
		if (m_point->s_number == 04    || m_point->s_number == 07
			|| m_point->s_number == 8  || m_point->s_number == 13
			|| m_point->s_number == 14 || m_point->s_number == 15
			|| m_point->s_number == 16 || m_point->s_number == 17
			|| m_point->s_number == 18 || m_point->s_number == 21
			|| m_point->s_number == 22) {
			//バイクを傾けるための回転クォータニオンを計算する。
			rotation.SetRotation(CVector3::AxisZ(), -0.5f);
		}
		//左傾き
		else if (m_point->s_number == 03 || m_point->s_number == 10
			  || m_point->s_number == 11 || m_point->s_number == 12
			  || m_point->s_number == 20 || m_point->s_number == 23
			  || m_point->s_number == 24)
		{
			rotation.SetRotation(CVector3::AxisZ(), -5.5f);
		}
		else {
			rotation.SetRotation(CVector3::AxisZ(), 0.0f);
		}
	}
	rotation.Multiply(qRot, rotation);

	//キャラクターコントローラーの更新
	if (m_CharaConInitFlag == true)
	{
		 position = m_charaCon.Execute(movespeed,
			//1.0f / 60.0f 
			GameTimeIns().GetFrameDeltaTime()
		);
	}
}
