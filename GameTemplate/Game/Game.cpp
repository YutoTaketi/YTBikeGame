#include "stdafx.h"
#include "Game.h"
#include "level/Level.h"
#include "Goal.h"
#include "ItemWaku.h"
#include "BikeSelect.h"
#include "BikeMaster.h"
#include "Course.h"



Game::Game()
{
	//レベルの初期化
	//coursepath = new CoursePath();
	level.Init(L"Assets/level/CourseLevelDemo2.tkl", [&]( LevelObjectData& objData) {
		//パス移動用のポイントリストを作成
		if (wcsncmp(L"point", objData.name, 5) == 0) {
			int number = _wtoi(&objData.name[5]);
			Point* point = new Point();
			point->s_position = objData.position;
			point->s_number = number;
			m_pointList[number] = point;
			return true;
		}
		//コースを作成
		/*if (wcsncmp(L"Course01", objData.name, 8) == 0)
		{
			course = g_goMgr.NewGO<Course>();
			course->SetPosition(objData.position);
			course->SetRotation(objData.rotation);
			return true;
		}*/
		/*
		if (objData.EqualObjectName(L"Course01") == true) {
			course = g_goMgr.NewGO<Course>();
			course->m_position = objData.position;
			course->m_rotation = objData.rotation;
			course->m_scale = objData.scale;
			return true;
		}*/
		
		if (objData.EqualObjectName(L"GoalPoint") == true) {
			Goal* goal = g_goMgr.NewGO<Goal>();
			goal->m_position = objData.position;
			goal->m_rotation = objData.rotation;
			goal->m_scale = objData.scale;
			return true;
		}

		
		return false;
    });
	
	
	bikemaster = g_goMgr.NewGO<BikeMaster>();
	bikemaster->SetGame(this);
	bikemaster->GetPassObject(m_pointList);
	//bikemaster->SetGoal(goal);
	
	
	
	
	
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

	
	//g_goMgr.DeleteGameObject(itemwaku);
	
	//g_goMgr.DeleteGameObject(goal);
	g_goMgr.DeleteGameObject(bikeselect);
	g_goMgr.DeleteGameObject(bikemaster);
	g_goMgr.DeleteGameObject(course);
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
	//if (bikemaster->GetbikesetFlag() == true)
	//{
		level.Draw();
		//goal->Update();
		/*if (course != nullptr)
		{
			course->Update();
		}*/
	//}
	
	//アイテム枠の描画
	//itemwaku->Update();
	//bikeselect->Update();
	

	//bikeselect->Update();
	//カメラ
	
	bikemaster->Update();
   
	
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