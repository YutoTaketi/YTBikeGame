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
	//�o�C�N�̑I��ԍ���0�̎�
	if (m_bikesentakuNo == 0 && m_bikeSetFlag == false)
	{
		//�v���C���[�o�C�N
		alphabike = g_goMgr.NewGO<AlphaBike>();
		alphabike->SetGame(m_game);
		alphabike->ChangePlayerBikeFlag();
		//�J����
		gamecamera = g_goMgr.NewGO<GameCamera>();
		gamecamera->SetBike(alphabike);
		gamecamera->SetGame(m_game);
		gamecamera->SetBikeMaster(this);
		//COM�o�C�N�̐���
		betabike = g_goMgr.NewGO<BetaBike>(); //BetaBike
		betabike->SetGame(m_game);
		betabike->GetPassObject(m_pointList);

		gammabike = g_goMgr.NewGO<GammaBike>();  //GammaBike
		gammabike->SetGame(m_game);
		gammabike->GetPassObject(m_pointList);

		deltabike = g_goMgr.NewGO<DeltaBike>();  //DeltaBike
		deltabike->SetGame(m_game);
		deltabike->GetPassObject(m_pointList);

		epsilonbike = g_goMgr.NewGO<EpsilonBike>(); //EpsilonBike
		epsilonbike->SetGame(m_game);
		epsilonbike->GetPassObject(m_pointList);

		m_bikeSetFlag = true;
	}
	//�o�C�N�̑I��ԍ���1�̎�
	if (m_bikesentakuNo == 1 && m_bikeSetFlag == false)
	{
		//�v���C���[�o�C�N
		betabike = g_goMgr.NewGO<BetaBike>();
		betabike->SetGame(m_game);
		betabike->ChangePlayerBikeFlag();
		//�J����
		gamecamera = g_goMgr.NewGO<GameCamera>();
		gamecamera->SetBike(betabike);
		gamecamera->SetGame(m_game);
		gamecamera->SetBikeMaster(this);

		//COM�o�C�N�̐���
		alphabike = g_goMgr.NewGO<AlphaBike>();  //AlphaBike
		alphabike->SetGame(m_game);
		alphabike->GetPassObject(m_pointList);

		gammabike = g_goMgr.NewGO<GammaBike>();  //GammaBike
		gammabike->SetGame(m_game);
		gammabike->GetPassObject(m_pointList);

		deltabike = g_goMgr.NewGO<DeltaBike>();  //DeltaBike
		deltabike->SetGame(m_game);
		deltabike->GetPassObject(m_pointList);

		epsilonbike = g_goMgr.NewGO<EpsilonBike>(); //EpsilonBike
		epsilonbike->SetGame(m_game);
		epsilonbike->GetPassObject(m_pointList);
		m_bikeSetFlag = true;
	}
	//�o�C�N�̑I��ԍ���2�̎�
	if (m_bikesentakuNo == 2 && m_bikeSetFlag == false)
	{
		//�v���C���[�o�C�N
		gammabike = g_goMgr.NewGO<GammaBike>();
		gammabike->SetGame(m_game);
		gammabike->ChangePlayerBikeFlag();
		//�J����
		gamecamera = g_goMgr.NewGO<GameCamera>();
		gamecamera->SetBike(gammabike);
		gamecamera->SetGame(m_game);
		gamecamera->SetBikeMaster(this);
		//COM�o�C�N�̐���
		alphabike = g_goMgr.NewGO<AlphaBike>();  //AlphaBike
		alphabike->SetGame(m_game);
		alphabike->GetPassObject(m_pointList);

		betabike = g_goMgr.NewGO<BetaBike>(); //BetaBike
		betabike->SetGame(m_game);
		betabike->GetPassObject(m_pointList);

		deltabike = g_goMgr.NewGO<DeltaBike>();  //DeltaBike
		deltabike->SetGame(m_game);
		deltabike->GetPassObject(m_pointList);

		epsilonbike = g_goMgr.NewGO<EpsilonBike>(); //EpsilonBike
		epsilonbike->SetGame(m_game);
		epsilonbike->GetPassObject(m_pointList);
		m_bikeSetFlag = true;

	}
	//�o�C�N�̑I��ԍ���3�̎�
	if (m_bikesentakuNo == 3 && m_bikeSetFlag == false)
	{
		//�v���C���[�o�C�N
		deltabike = g_goMgr.NewGO<DeltaBike>();
		deltabike->SetGame(m_game);
		deltabike->ChangePlayerBikeFlag();
		//�J����
		gamecamera = g_goMgr.NewGO<GameCamera>();
		gamecamera->SetBike(deltabike);
		gamecamera->SetGame(m_game);
		gamecamera->SetBikeMaster(this);
		//COM�o�C�N�̐���
		alphabike = g_goMgr.NewGO<AlphaBike>();  //AlphaBike
		alphabike->SetGame(m_game);
		alphabike->GetPassObject(m_pointList);

		betabike = g_goMgr.NewGO<BetaBike>(); //BetaBike
		betabike->SetGame(m_game);
		betabike->GetPassObject(m_pointList);

		gammabike = g_goMgr.NewGO<GammaBike>();  //GammaBike
		gammabike->SetGame(m_game);
		gammabike->GetPassObject(m_pointList);

		epsilonbike = g_goMgr.NewGO<EpsilonBike>(); //EpsilonBike
		epsilonbike->SetGame(m_game);
		epsilonbike->GetPassObject(m_pointList);
		m_bikeSetFlag = true;
	}
	//�o�C�N�̑I��ԍ���4�̎�
	if (m_bikesentakuNo == 4 && m_bikeSetFlag == false)
	{
		//�v���C���[�o�C�N
		epsilonbike = g_goMgr.NewGO<EpsilonBike>();
		epsilonbike->SetGame(m_game);
		epsilonbike->ChangePlayerBikeFlag();
		//�J����
		gamecamera = g_goMgr.NewGO<GameCamera>();
		gamecamera->SetBike(epsilonbike);
		gamecamera->SetGame(m_game);
		gamecamera->SetBikeMaster(this);
		//COM�o�C�N�̐���
		alphabike = g_goMgr.NewGO<AlphaBike>();  //AlphaBike
		alphabike->SetGame(m_game);
		alphabike->GetPassObject(m_pointList);

		betabike = g_goMgr.NewGO<BetaBike>(); //BetaBike
		betabike->SetGame(m_game);
		betabike->GetPassObject(m_pointList);

		gammabike = g_goMgr.NewGO<GammaBike>();  //GammaBike
		gammabike->SetGame(m_game);
		gammabike->GetPassObject(m_pointList);

		deltabike = g_goMgr.NewGO<DeltaBike>();  //DeltaBike
		deltabike->SetGame(m_game);
		deltabike->GetPassObject(m_pointList);
		m_bikeSetFlag = true;
	}

	//�o�C�N�ƃJ�����̍X�V
	if (m_bikeSetFlag == true) {
		
		alphabike->Update();
		betabike->Update();
		//gammabike->Update();
		//deltabike->Update();
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