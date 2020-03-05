#pragma once
#include "GameObjectManager.h"
#include "graphics/SkinModel.h"
#include "BikeController.h"
#include "graphics/SkinModel.h"

//敵バイク１のクラス
class UnionBike : public IGameObject
{
public:
	UnionBike();
	~UnionBike();
	
	void Update();


	const std::map<int, Point*>& GetPassObject(const std::map<int, Point*>& List)
	{
		m_pointList = List;
		m_point = m_pointList[1];
		return m_pointList;
	}

	//Gameのポインタを渡す
	void SetGame(Game* game)
	{
		m_game = game;
	}

private:
	void Move();
	void Turn();
	void Render();
	void Draw();

	CVector3 m_position = { 5.0f, 0.0f, 0.0f };  //座標
	CVector3 m_moveSpeed = CVector3::Zero(); //移動速度
	CQuaternion m_rotation = CQuaternion::Identity(); //回転
	SkinModel* m_model;          //スキンモデル。
	Game* m_game;

	CVector3 m_accel = CVector3::Zero();    //加速度
	CVector3 m_forward = CVector3::AxisZ();   //エネミーの前方方向

	float m_accelNum = 30.0f;        //加速数値
	float m_friction = 0.98f;        //摩擦係数

	BikeController* m_bikecontroller;

	std::map<int, Point*> m_pointList;  //ポイント構造体の配列
	Point* m_point;                  //ポイントの構造体のポインタ、現在の目的地

};

