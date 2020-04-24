#pragma once
#include "GameObjectManager.h"
#include "graphics/SkinModel.h"
#include "BikeController.h"

class Game;
class BikeMove;

class DeltaBike : public IGameObject
{
public:
	DeltaBike();
	~DeltaBike();
	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();
	
	CVector3 GetPosition() const
	{
		return m_position;
	}


	/// <summary>
	/// パス移動に関する関数と配列
	/// </summary>
	const std::map<int, Point*>& GetPassObject(const std::map<int, Point*>& List)
	{

		m_pointList = List;
		m_point = m_pointList[1];
		return m_pointList;
	}

	/// <summary>
	/// Gameのポインタを渡す。
	/// </summary>
	/// <param name="game"></param>
	void SetGame(Game* game)
	{
		m_game = game;
	}

	//プレイヤーなら切り替える。
	void ChangePlayerBikeFlag()
	{
		m_playerBikeFlag = true;
	}

private:
	void Render();
	void Draw();

	CVector3 m_position = { -100.0f, 0.0f, 0.0f };      //座標
	CVector3 m_moveSpeed = CVector3::Zero();           //移動速度
	CQuaternion m_rotation = CQuaternion::Identity();  //回転
	SkinModel* m_model;                                //スキンモデル。
	Game* m_game;

	CVector3 m_accel = CVector3::Zero();                //加速度
	CVector3 m_forward = CVector3::AxisZ();             //エネミーの前方方向

	float m_accelNum = 85.0f;                           //加速数値
	float m_friction = 0.98f;                           //摩擦係数

	BikeController* m_bikecontroller;

	std::map<int, Point*> m_pointList;  //ポイント構造体の配列
	Point* m_point;                  //ポイントの構造体のポインタ、現在の目的地
	BikeMove* m_bikeMove = nullptr;
	bool m_playerBikeFlag = false;    //プレイヤーバイクかどうかのフラグ
	bool m_bikeMoveDecision = false;   //バイクを動かす処理が決定したかのフラグ。

};

