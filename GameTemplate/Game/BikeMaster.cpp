#include "stdafx.h"
#include "BikeMaster.h"
#include <iostream>
#include "Game.h"
#include "GameCamera.h"
#include "EpsilonBike.h"
using namespace std;


BikeMaster::BikeMaster()
{
	
}


BikeMaster::~BikeMaster()
{
	g_goMgr.DeleteGameObject(epsilonbike);
	g_goMgr.DeleteGameObject(gamecamera);
}

void BikeMaster::Update()
{
	if (m_bikesentakuNo == 0 && m_bikeSetFlag == false)
	{
		epsilonbike = g_goMgr.NewGO<EpsilonBike>();
		epsilonbike->SetGame(m_game);
		gamecamera = g_goMgr.NewGO<GameCamera>();
		gamecamera->SetBike(epsilonbike);
		gamecamera->SetGame(m_game);
		m_bikeSetFlag = true;
	}
	if (m_bikeSetFlag == true) {
		epsilonbike->Update();
		gamecamera->Update();
	}
	
	
}

void BikeMaster::Render()
{

}
void BikeMaster::Draw()
{

}