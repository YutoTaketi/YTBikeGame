#pragma once
#include "GameObjectManager.h"
#include "graphics/SkinModel.h"
#include "BikeController.h"

class Game;
class BikeMove;
class GameTime;
class PhysicsWorld;
class CharacterController;
class Goal;
class PhysicsGhostObject;
class EpsilonBike : public IGameObject
{
public:
	EpsilonBike();
	~EpsilonBike();
	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();


	CVector3 GetPosition() const
	{
		return m_position;
	}


	/// <summary>
	/// Gameクラスで作ったパスの情報を取得する。
	/// </summary>
	/// <param name="List"></param>
	void GetPassObject(const std::map<int, Point*>& List)
	{
		m_bikeMove->GetPassObject(List);
	}

	/// <summary>
	/// Gameのポインタを渡す。
	/// </summary>
	/// <param name="game"></param>
	void SetGame(Game* game)
	{
		m_game = game;
		m_bikeMove->SetGame(game);
	}

	CharacterController GetCharaCon()
	{
		return m_charaCon;
	}
private:
	void Render();
	void Draw();

	CVector3 m_position = { 0.0f, 0.0f, 0.0f };      //座標
	CVector3 m_moveSpeed = CVector3::Zero();          //移動速度
	CQuaternion m_rotation = CQuaternion::Identity(); //回転
	CVector3 m_pointOnePos = CVector3::Zero();
	SkinModel* m_model;                               //スキンモデル。
	CharacterController m_charaCon;
	PhysicsWorld m_physics;
	Goal goal;
	//GameTime m_gameTime;
	Game* m_game = nullptr;

	CVector3 m_accel = CVector3::Zero();    //加速度
	CVector3 m_forward = CVector3::AxisZ();   //エネミーの前方方向

	float m_accelNum = 1.8f;        //加速数値
	float m_friction = 0.98f;        //摩擦係数

	BikeController* m_bikecontroller;
	
	std::map<int, Point*> m_pointList;  //ポイント構造体の配列
	Point* m_point;                  //ポイントの構造体のポインタ、現在の目的地
	
	BikeMove* m_bikeMove = nullptr;

	CVector3 m_goalpos = { 0.0f, 0.0f, 1150.0f };
	PhysicsGhostObject m_ghostObject;     //ゴーストオブジェクト
};

