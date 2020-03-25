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
	
	bool GetbikesetFlag()
	{
		return m_bikeSetFlag;
	}
	/// <summary>
	/// Gameのポインタを渡す。
	/// </summary>
	/// <param name="game"></param>
	void SetGame(Game* game)
	{
		m_game = game;
		
	}
	void SetSentakuNo(int No)
	{
		m_bikesentakuNo = No;
	}
private:
	void Render();
	void Draw();
	GameCamera* gamecamera = nullptr;
	AlphaBike* alphabike = nullptr;
	BetaBike* betabike = nullptr;
	GammaBike* gammabike = nullptr;
	DeltaBike* deltabike = nullptr;
	EpsilonBike* epsilonbike = nullptr;

	//バイクの選択番号
	int m_bikesentakuNo;
	bool m_bikeSetFlag = false;
	Game* m_game;
};

