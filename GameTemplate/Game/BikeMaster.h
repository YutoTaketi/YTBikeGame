#pragma once
#include "GameObjectManager.h"

class Game;
class BikeMaster : public IGameObject
{
public:
	BikeMaster();
	~BikeMaster();

	void Update();

	int GetBikeNo()
	{
		return m_bikesentakuNo;
	}
	

	/// <summary>
	/// Gameのポインタを渡す。
	/// </summary>
	/// <param name="game"></param>
	void SetGame(Game* game)
	{
		m_game = game;
		
	}

private:
	void Render();
	void Draw();
	GameCamera* gamecamera = nullptr;
	EpsilonBike* epsilonbike = nullptr;

	//バイクの選択番号
	int m_bikesentakuNo = 0;
	
	Game* m_game;
};

