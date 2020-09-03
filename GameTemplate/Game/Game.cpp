#include "stdafx.h"
#include "Game.h"
#include "level/Level.h"
#include "Goal.h"
#include "ItemWaku.h"
#include "BikeSelect.h"
#include "BikeMaster.h"
#include "Course.h"
#include "LapCount.h"
#include "Kyakuseki.h"
#include "Road.h"
#include "Jimen.h"
#include "Signal.h"
#include "Sky.h"
#include "Guest.h"

Game::Game()
{
	//レベルの初期化
	//coursepath = new CoursePath();
	m_soundEngine.Init();
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
		/*if (objData.EqualObjectName(L"Course01") == true) {
			course = g_goMgr.NewGO<Course>();
			course->SetPosition(objData.position);
			course->SetRotation(objData.rotation);
			course->SetScale(objData.scale);
			return true;

		}*/
		//客席
		if (objData.EqualObjectName(L"Kyakuseki") == true) {
			
			kyakuseki = g_goMgr.NewGO<Kyakuseki>();
			kyakuseki->SetPosition(objData.position);
			kyakuseki->SetRotation(objData.rotation);
			kyakuseki->SetSclae(objData.scale);
			return true;
		}
		
		if (objData.EqualObjectName(L"Course01_Road") == true) {
			road = g_goMgr.NewGO<Road>();
			road->SetPosition(objData.position);
			road->SetRotation(objData.rotation);
			road->SetSclae(objData.scale);
			return true;
		}

		if (objData.EqualObjectName(L"CourseJimen") == true) {
			jimen = g_goMgr.NewGO<Jimen>();
			jimen->SetPosition(objData.position);
			jimen->SetRotation(objData.rotation);
			jimen->SetSclae(objData.scale);
			return true;
		}


		if (objData.EqualObjectName(L"TestGoal") == true) {
			goal = g_goMgr.NewGO<Goal>();
			goal->m_position = objData.position;
			goal->m_rotation = objData.rotation;
			goal->m_scale = objData.scale;
			return true;
		}
		if (objData.EqualObjectName(L"Guest") == true) {
			guest = g_goMgr.NewGO<Guest>();
			guest->SetPosition(objData.position);
			guest->SetRotation(objData.rotation);
			guest->SetSclae(objData.scale);
			return true;
		}
		if (objData.EqualObjectName(L"CourseSky") == true) {
			
			return false;
		}
		
		return false;
    });
	
	//シグナルの
	signal = g_goMgr.NewGO<Signal>();

	//バイクマスター
	bikemaster = g_goMgr.NewGO<BikeMaster>();
	bikemaster->SetGame(this);
	bikemaster->GetPassObject(m_pointList);
	bikemaster->SetGoal(goal);
	
	


	//バイクの選択画面
	bikeselect = g_goMgr.NewGO<BikeSelect>();
	bikeselect->SetBikeMaster(bikemaster);
	bikeselect->SetSignal(signal);


	lapcount = g_goMgr.NewGO<LapCount>();
	lapcount->SetBikeSelect(bikeselect);
	lapcount->SetGame(this);
	
	

}


Game::~Game()
{
	if (m_frameBufferRenderTargetView != nullptr) {
		m_frameBufferRenderTargetView->Release();
	}
	if (m_frameBufferDepthStencilView != nullptr) {
		m_frameBufferDepthStencilView->Release();
	}
	
	//g_goMgr.DeleteGameObject(goal);
	g_goMgr.DeleteGameObject(bikeselect);
	g_goMgr.DeleteGameObject(bikemaster);
	g_goMgr.DeleteGameObject(course);
	g_goMgr.DeleteGameObject(lapcount);
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
	//シャドウキャスターを登録
	//シャドウマップを更新
	
	
	m_soundEngine.Update();
	

	if (finishFlag == true)
	{
		//リザルトへ
		g_goMgr.NewGO<Result>();
	}
}

void Game::PreRender()
{
	
}

void Game::ForwordRender()
{
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
	
	

	m_frameBufferRenderTargetView->Release();
	m_frameBufferDepthStencilView->Release();
}

void Game::Render()
{
	level.Draw();
}