#include "stdafx.h"
#include "UnionBike.h"
#include "Game.h"

UnionBike::UnionBike()
{
	m_model = new  SkinModel();
	//cmoファイルの読み込み。
	m_model->Init(L"Assets/modelData/Bike3.cmo");
}


UnionBike::~UnionBike()
{
}

void UnionBike::Move()
{
	//移動ポイントの番号を取得
	CVector3 diff = m_point->s_position - m_position;
	if (diff.LengthSq() <= 1000.0f) {
		m_point = m_game->GetNextNumber(m_point->s_number);
	}

	m_moveSpeed = m_point->s_position - m_position;
	m_moveSpeed.Normalize();
	m_accel = m_moveSpeed * m_accelNum;
	m_moveSpeed += m_accel;
	//摩擦係数を乗算
	m_moveSpeed *= m_friction;
	//移動速度を計算
	m_position += m_moveSpeed;
}

void UnionBike::Turn()
{
	//ポイントとの距離
	CVector3 pointLen = m_point->s_position - m_position;
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
		CVector3 TiltConditions = m_position - m_point->s_position;
		if (m_point->s_number == 04 || m_point->s_number == 07
			|| m_point->s_number == 8 || m_point->s_number == 13
			|| m_point->s_number == 16 || m_point->s_number == 18
			|| m_point->s_number == 22) {
			//バイクを傾けるための回転クォータニオンを計算する。
			m_rotation.SetRotation(CVector3::AxisZ(), -0.5f);
		}
		else if (m_point->s_number == 03 || m_point->s_number == 10
			|| m_point->s_number == 12 || m_point->s_number == 20
			|| m_point->s_number == 24)
		{
			m_rotation.SetRotation(CVector3::AxisZ(), -5.5f);
		}
		else {
			m_rotation.SetRotation(CVector3::AxisZ(), 0.0f);
		}
	}
	m_rotation.Multiply(qRot, m_rotation);
}


void UnionBike::Update()
{
	Move();
	Turn();
}

void UnionBike::Render()
{

}

void UnionBike::Draw()
{

}