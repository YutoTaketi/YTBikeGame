#pragma once
#include "GameObjectManager.h"
#include "graphics/Camera.h"

class Player;
class BikeMove_Player;
class EpsilonBike;
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	/// <summary>
	/// çXêVä÷êî
	/// </summary>
	
	void Update();
	void Render();

	/// <summary>
	/// ï`âÊä÷êî
	/// </summary>
	void Draw();
	
	void SetBike(EpsilonBike* epsilon)
	{
		m_epsilonbike = epsilon;
	}
    
	
private:
	
	Player* m_player = nullptr;
	EpsilonBike* m_epsilonbike = nullptr;
	BikeMove_Player* m_bikemove_Player = nullptr;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_target = CVector3::Zero();
	CVector3 m_toCameraPos = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_finishposition = CVector3::Zero();
	
	
};

