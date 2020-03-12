#pragma once
#include "GameObjectManager.h"
#include "PhysicsGhostObject.h"
class Goal : public IGameObject
{
public:
	Goal();
	~Goal();

	void Update();
private:
	void Render();
	void Draw();
	
	CVector3 m_position = CVector3::Zero();
	PhysicsGhostObject m_ghostObject;     //ゴーストオブジェクト
};

