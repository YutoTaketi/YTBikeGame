#pragma once
#include "GameObjectManager.h"
#include "PhysicsGhostObject.h"
#include "physics/Physics.h"
class Game;
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
private:
	void Render();
	void Draw();
	
	CVector3 m_position = CVector3::Zero();
	PhysicsGhostObject m_ghostObject;     //ゴーストオブジェクト
	PhysicsWorld m_physics;
	Game* m_game;
};

