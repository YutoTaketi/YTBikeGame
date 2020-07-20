#include "stdafx.h"
#include "GameObjectManager.h"
#include <iostream>
#include <Windows.h>

GameObjectManager g_goMgr;

void GameObjectManager::Draw()
{
	for (auto go : m_goList)
	{
		go->Draw();
	}
}

void GameObjectManager::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport)
{
	ChangeRenderTarget(
		d3dDeviceContext,
		renderTarget->GetRenderTargetView(),
		renderTarget->GetDepthStensilView(),
		viewport
	);
}
void GameObjectManager::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport)
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
void GameObjectManager::Update()
{
	

	{
		//登録されているゲームオブジェクトの
		//更新関数を呼び出す
		for (auto go : m_goList) {
			go->Update();
		}

		
		ShadowMap::GetInstance().Draw();
		
		
	
		//登録されているゲームオブジェクトの
		//3D描画関数を呼び出す
		static bool isDraw3D = true;
		if (isDraw3D) {
			for (auto go : m_goList) {
				go->Render();
			}
		}
		//登録されているゲームオブジェクト
		//2D描画関数を呼び出す
		for (auto go : m_goList) {
			go->Render2D();
		}
	}

	for (auto it = m_goList.begin(); it != m_goList.end();
		) {
		if ((*it)->IsRequestDelete()) {
			delete* it; //インスタンスの削除
			it = m_goList.erase(it);  //登録解除
		}
		else {
			it++;
		}
	}

	

	
}

void GameObjectManager::PreRender()
{
	//シャドウマップにレンダリング
}

void GameObjectManager::ForwordRender()
{
	//レンダリングターゲットをメインに変更する。
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ChangeRenderTarget(d3dDeviceContext, &m_mainRenderTarget, &m_frameBufferViewports);
	//メインレンダリングターゲットをクリアする。
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_mainRenderTarget.ClearRenderTarget(clearColor);

	
}

void GameObjectManager::PostRender()
{
	//レンダリングターゲットをフレームバッファに戻す。
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ChangeRenderTarget(
		d3dDeviceContext,
		m_frameBufferRenderTargetView,
		m_frameBufferDepthStencilView,
		&m_frameBufferViewports
	);

	m_copyMainRtToFrameBufferSprite.Draw();

	m_frameBufferRenderTargetView->Release();
	m_frameBufferDepthStencilView->Release();
}

void GameObjectManager::Render()
{
	g_graphicsEngine->BegineRender();
	
	//プリレンダリング
	//PreRender();

	//フォワードレンダリング

	//ポストレンダリング
	//PostRender();

	//描画終了
	g_graphicsEngine->EndRender();
}
/*GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
}*/
