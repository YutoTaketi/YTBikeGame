#include "stdafx.h"
#include "BikeMaster.h"
#include <iostream>
#include "Game.h"
#include "GameCamera.h"
#include "AlphaBike.h"
#include "BetaBike.h"
#include "GammaBike.h"
#include "DeltaBike.h"
#include "EpsilonBike.h"

using namespace std;


BikeMaster::BikeMaster()
{
	
}


BikeMaster::~BikeMaster()
{
	g_goMgr.DeleteGameObject(alphabike);
	g_goMgr.DeleteGameObject(betabike);
	g_goMgr.DeleteGameObject(gammabike);
	g_goMgr.DeleteGameObject(deltabike);
	g_goMgr.DeleteGameObject(epsilonbike);
	g_goMgr.DeleteGameObject(gamecamera);
}

void BikeMaster::Update()
{
	//バイクの選択番号が0の時
	if (m_bikesentakuNo == 0 && m_bikeSetFlag == false)
	{
		alphabike = g_goMgr.NewGO<AlphaBike>();
		alphabike->SetGame(m_game);
		gamecamera = g_goMgr.NewGO<GameCamera>();
		gamecamera->SetBike(alphabike);
		gamecamera->SetGame(m_game);
		gamecamera->SetBikeMaster(this);
		m_bikeSetFlag = true;
	}
	//バイクの選択番号が1の時
	if (m_bikesentakuNo == 1 && m_bikeSetFlag == false)
	{
		betabike = g_goMgr.NewGO<BetaBike>();
		betabike->SetGame(m_game);
		gamecamera = g_goMgr.NewGO<GameCamera>();
		gamecamera->SetBike(betabike);
		gamecamera->SetGame(m_game);
		gamecamera->SetBikeMaster(this);
		m_bikeSetFlag = true;
	}
	//バイクの選択番号が2の時
	if (m_bikesentakuNo == 2 && m_bikeSetFlag == false)
	{
		gammabike = g_goMgr.NewGO<GammaBike>();
		gammabike->SetGame(m_game);
		gamecamera = g_goMgr.NewGO<GameCamera>();
		gamecamera->SetBike(gammabike);
		gamecamera->SetGame(m_game);
		gamecamera->SetBikeMaster(this);
		m_bikeSetFlag = true;

	}
	//バイクの選択番号が3の時
	if (m_bikesentakuNo == 3 && m_bikeSetFlag == false)
	{
		deltabike = g_goMgr.NewGO<DeltaBike>();
		deltabike->SetGame(m_game);
		gamecamera = g_goMgr.NewGO<GameCamera>();
		gamecamera->SetBike(deltabike);
		gamecamera->SetGame(m_game);
		gamecamera->SetBikeMaster(this);
		m_bikeSetFlag = true;
	}
	//バイクの選択番号が4の時
	if (m_bikesentakuNo == 4 && m_bikeSetFlag == false)
	{
		epsilonbike = g_goMgr.NewGO<EpsilonBike>();
		epsilonbike->SetGame(m_game);
		gamecamera = g_goMgr.NewGO<GameCamera>();
		gamecamera->SetBike(epsilonbike);
		gamecamera->SetGame(m_game);
		gamecamera->SetBikeMaster(this);
		m_bikeSetFlag = true;
	}

	//バイクとカメラの更新
	if (m_bikeSetFlag == true) {
		
		//alphabike->Update();
		//betabike->Update();
		//gammabike->Update();
		deltabike->Update();
		//epsilonbike->Update();

		gamecamera->Update();
	}
	
	
}

void BikeMaster::Render()
{

}
void BikeMaster::Draw()
{

}