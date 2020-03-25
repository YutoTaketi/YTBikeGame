#pragma once
#include "GameObjectManager.h"
#include "graphics/Camera.h"

class Player;
class BikeMove_Player;
class EpsilonBike;
class Game;
class BikeMaster;
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	/// <summary>
	/// 更新関数
	/// </summary>
	
	void Update();
	void Render();

	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw();
	
	void SetBike(EpsilonBike* epsilon)
	{
		m_epsilonbike = epsilon;
	}
	/// <summary>
	/// Gameのポインタを渡す。
	/// </summary>
	/// <param name="game"></param>
	void SetGame(Game* game)
	{
		m_game = game;
		///m_bikeMove->SetGame(game);
	}
	/// <summary>
	/// BikeMasterのポインタを渡す。
	/// </summary>
	void SetBikeMaster(BikeMaster* bikemaster)
	{
		m_bikemaster = bikemaster;	
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
	
	Game* m_game;
	BikeMaster* m_bikemaster;
	bool m_PlayerBikeSetFlag = false;
};

