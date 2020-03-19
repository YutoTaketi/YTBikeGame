#pragma once
#include "GameObjectManager.h"
#include "PhysicsGhostObject.h"
#include "physics/Physics.h"
class Game;
class EpsilonBike;
class Goal : public IGameObject
{
public:
	Goal();
	~Goal();

	void Update();

	void SetGame(Game* game)
	{
		m_game = game;
		//m_bikeMove->SetGame(game);
	}
	/// <summary>
	/// 配置したゴールポイントの座標を取得
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 配置したゴールポイントのスケールを取得
	/// </summary>
	/// <param name="sale"></param>
	void SetScale(CVector3 sale)
	{
		m_scale = sale;
	}
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	PhysicsGhostObject* GetGoalPoint()
	{
		return &m_ghostObject;
	}

	
private:
	void Render();
	void Draw();
	
	CVector3 m_position = CVector3::Zero();  //座標
	CVector3 m_scale = CVector3::One();      //スケール
	CQuaternion m_rotation = CQuaternion::Identity();  //回転
	PhysicsGhostObject m_ghostObject;     //ゴーストオブジェクト
	
	Game* m_game;
	EpsilonBike m_epsilonbike;
};

