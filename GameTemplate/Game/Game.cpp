#include "stdafx.h"
#include "Game.h"
#include "level/Level.h"
#include "Player.h"
#include "Goal.h"
#include "ItemWaku.h"
#include "AlphaBike.h"
#include "BetaBike.h"
#include "GammaBike.h"
#include "DeltaBike.h"
#include "EpsilonBike.h"
#include "EpsilonBike.h"
#include "BikeSelect.h"
#include "BikeMaster.h"
//#include "StageDemo.h"



Game::Game()
{
	//レベルの初期化
	//coursepath = new CoursePath();
	level.Init(L"Assets/level/CourseLevelDemo2.tkl", [&]( const LevelObjectData objData) {
		
		if (wcsncmp(L"point", objData.name, 5) == 0) {
			int number = _wtoi(&objData.name[5]);
			Point* point = new Point();
			point->s_position = objData.position;
			point->s_number = number;
			m_pointList[number] = point;
			return true;
		}
		
		
		
		
		return false;
    });
	
	

	//player = g_goMgr.NewGO<Player>();
	//alphabike = g_goMgr.NewGO<AlphaBike>();
	//betabike = g_goMgr.NewGO<BetaBike>();
	//gammabike = g_goMgr.NewGO<GammaBike>();
	//deltabike = g_goMgr.NewGO<DeltaBike>();
	//epsilonbike = g_goMgr.NewGO<EpsilonBike>();
	//gamecamera = g_goMgr.NewGO<GameCamera>();
	bikemaster = g_goMgr.NewGO<BikeMaster>();
	bikemaster->SetGame(this);
	//bikemove_enemy = new BikeMove_Enemy();
	
	//gamecamera->SetBike(epsilonbike);
	//gamecamera->SetGame(this);
	//goal = g_goMgr.NewGO<Goal>();
	//goal->SetGame(this);
	//goal->SetBike(epsilonbike);
	/*m_bikemove_enemy.GetPassObject(m_pointList);
	m_bikemove_enemy.SetGame(this);*/
	
	
	
	//alphabike->SetGame(this);
	//alphabike->GetPassObject(m_pointList);
	//betabike->SetGame(this);
	//betabike->GetPassObject(m_pointList);
	//gammabike->SetGame(this);
	//gammabike->GetPassObject(m_pointList);
	//deltabike->SetGame(this);
	//deltabike->GetPassObject(m_pointList);

	//epsilonbike->SetGame(this);
	//epsilonbike->GetPassObject(m_pointList);
	
	//itemwaku = g_goMgr.NewGO<ItemWaku>();
	//バイクの選択画面
	bikeselect = g_goMgr.NewGO<BikeSelect>();
	bikeselect->SetBikeMaster(bikemaster);
	//地面をシャドウレシーバーにする。
	//m_stageModelDraw.SetShadowReciever(true);

	//レンダリングターゲットの作成
	//m_renderTarget.Create(FRAME_BUFFER_W, FRAME_BUFFER_H, DXGI_FORMAT_R8G8B8A8_UNORM);
	//メインとなるレンダーターゲットを作成。
	/*m_mainRenderTarget.Create(
	    FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R8G8B8A8_UNORM
	);

	//メインレンダリングターゲットに描かれた絵を
	//フレームバッファにコピーするためのスプライトを初期化する。
	m_copyMainRtToFrameBufferSprite.Init(
	     m_mainRenderTarget.GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);*/
	

}


Game::~Game()
{
	if (m_frameBufferRenderTargetView != nullptr) {
		m_frameBufferRenderTargetView->Release();
	}
	if (m_frameBufferDepthStencilView != nullptr) {
		m_frameBufferDepthStencilView->Release();
	}

	g_goMgr.DeleteGameObject(alphabike);
	g_goMgr.DeleteGameObject(betabike);
	g_goMgr.DeleteGameObject(gammabike);
	g_goMgr.DeleteGameObject(deltabike);
	g_goMgr.DeleteGameObject(epsilonbike);
	//g_goMgr.DeleteGameObject(itemwaku);
	g_goMgr.DeleteGameObject(gamecamera);
	g_goMgr.DeleteGameObject(goal);
	g_goMgr.DeleteGameObject(bikeselect);
	g_goMgr.DeleteGameObject(bikemaster);
}

void Game::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport)
{
	ChangeRenderTarget(
	   d3dDeviceContext,
		renderTarget->GetRenderTargetView(),
		renderTarget->GetDepthStensilView(),
		viewport
	);
}
void Game::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport)
{
	ID3D11RenderTargetView* rtTbl[] = {
		renderTarget
	};
	//レンダリングターゲットの切り替え。
	d3dDeviceContext->OMSetRenderTargets(1, rtTbl, depthStensil);
	if (viewport != nullptr) {
		//ビューポートが指定されていたら、ビューポートも変更する。
		d3dDeviceContext->RSSetViewports(1, viewport);
	}
}

void Game::Update()
{
	//レベルの描画
	if (bikemaster->GetbikesetFlag() == true)
	{
		level.Draw();
	}
	
	//プレイヤーの描画。
	//player->Update();
	//敵の描画
	//enemybike->Update();
	
	//アイテム枠の描画
	//itemwaku->Update();
	//bikeselect->Update();
	//alphabike->Update();
	//betabike->Update();
	//gammabike->Update();
	//deltabike->Update();
	//epsilonbike->Update();

	//bikeselect->Update();
	//カメラ
	//gamecamera->Update();
	bikemaster->Update();
    //ステージの描画
	//stagedemo->Update();
	
	//シャドウキャスターを登録
	//m_shadowMap.RegistShadowCaster(&m_playerModelDraw);
	//m_shadowMap.RegistShadowCaster(&m_enemyModelDraw);
	//m_shadowMap.RegistShadowCaster(&m_stageModelDraw);
	///シャドウマップを更新
	/**m_shadowMap.UpdateFromLightTarget(
		{ 1000.0f, 1000.0f, 1000.0f },
		{ 0.0f, 0.0f, 0.0f }

	);*/

	if (finishhantei >= 4 )
	{
		
		g_goMgr.NewGO<Result>();
		g_goMgr.DeleteGameObject(this);
		
	}
}

void Game::PreRender()
{
	//シャドウマップにレンダリング
	//m_shadowMap.RenderToShadowMap();
}

void Game::ForwordRender()
{
	/*
	//レンダリングターゲットをメインに変更する。
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ChangeRenderTarget(d3dDeviceContext, &m_mainRenderTarget, &m_frameBufferViewports);
	//メインレンダリングターゲットをクリアする。
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_mainRenderTarget.ClearRenderTarget(clearColor);
	*/
	
	g_goMgr.Draw();
}

void Game::PostRender()
{
	//レンダリングターゲットをフレームバッファに戻す。
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ChangeRenderTarget(
		d3dDeviceContext,
		m_frameBufferRenderTargetView,
		m_frameBufferDepthStencilView,
		&m_frameBufferViewports
	);
	//ドロドロ
	//m_copyMainRtToFrameBufferSprite.Draw();

	m_frameBufferRenderTargetView->Release();
	m_frameBufferDepthStencilView->Release();
}

void Game::Render()
{
	//描画開始。
	//g_graphicsEngine->BegineRender();


	/*
	//描画開始。
	g_graphicsEngine->BegineRender();
	//フレームバァファのレンダリングターゲットを
	//バックアップしておく。
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	d3dDeviceContext->OMGetRenderTargets(
		1,
		&m_frameBufferRenderTargetView,
		&m_frameBufferDepthStencilView
	);
	//ビューポートもバックアップを取っておく。
	unsigned int numViewport = 1;
	d3dDeviceContext->RSGetViewports(&numViewport, &m_frameBufferViewports);

	//プリレンダリング
	PreRender();

	//フォワードレンダリング
	ForwordRender();

	//ポストレンダリング
	PostRender();
	
	//描画終了
	g_graphicsEngine->EndRender();
	*/
}