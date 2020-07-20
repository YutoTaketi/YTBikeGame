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
	//�����_�����O�^�[�Q�b�g�̐؂�ւ��B
	d3dDeviceContext->OMSetRenderTargets(1, rtTbl, depthStensil);
	if (viewport != nullptr) {
		//�r���[�|�[�g���w�肳��Ă�����A�r���[�|�[�g���ύX����B
		d3dDeviceContext->RSSetViewports(1, viewport);
	}
}
void GameObjectManager::Update()
{
	

	{
		//�o�^����Ă���Q�[���I�u�W�F�N�g��
		//�X�V�֐����Ăяo��
		for (auto go : m_goList) {
			go->Update();
		}

		
		ShadowMap::GetInstance().Draw();
		
		
	
		//�o�^����Ă���Q�[���I�u�W�F�N�g��
		//3D�`��֐����Ăяo��
		static bool isDraw3D = true;
		if (isDraw3D) {
			for (auto go : m_goList) {
				go->Render();
			}
		}
		//�o�^����Ă���Q�[���I�u�W�F�N�g
		//2D�`��֐����Ăяo��
		for (auto go : m_goList) {
			go->Render2D();
		}
	}

	for (auto it = m_goList.begin(); it != m_goList.end();
		) {
		if ((*it)->IsRequestDelete()) {
			delete* it; //�C���X�^���X�̍폜
			it = m_goList.erase(it);  //�o�^����
		}
		else {
			it++;
		}
	}

	

	
}

void GameObjectManager::PreRender()
{
	//�V���h�E�}�b�v�Ƀ����_�����O
}

void GameObjectManager::ForwordRender()
{
	//�����_�����O�^�[�Q�b�g�����C���ɕύX����B
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ChangeRenderTarget(d3dDeviceContext, &m_mainRenderTarget, &m_frameBufferViewports);
	//���C�������_�����O�^�[�Q�b�g���N���A����B
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_mainRenderTarget.ClearRenderTarget(clearColor);

	
}

void GameObjectManager::PostRender()
{
	//�����_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɖ߂��B
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
	
	//�v�������_�����O
	//PreRender();

	//�t�H���[�h�����_�����O

	//�|�X�g�����_�����O
	//PostRender();

	//�`��I��
	g_graphicsEngine->EndRender();
}
/*GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
}*/
