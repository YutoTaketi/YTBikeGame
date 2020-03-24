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
	/// Game�̃|�C���^��n���B
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

	//�o�C�N�̑I��ԍ�
	int m_bikesentakuNo = 0;
	
	Game* m_game;
};

