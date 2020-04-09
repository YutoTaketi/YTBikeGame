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
	//���x���̏�����
	//coursepath = new CoursePath();
	level.Init(L"Assets/level/CourseLevelDemo2.tkl", [&]( LevelObjectData& objData) {
		//�p�X�ړ��p�̃|�C���g���X�g���쐬
		if (wcsncmp(L"point", objData.name, 5) == 0) {
			int number = _wtoi(&objData.name[5]);
			Point* point = new Point();
			point->s_position = objData.position;
			point->s_number = number;
			m_pointList[number] = point;
			return true;
		}
		//�R�[�X���쐬
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
	//�o�C�N�̑I�����
	bikeselect = g_goMgr.NewGO<BikeSelect>();
	bikeselect->SetBikeMaster(bikemaster);
	//�n�ʂ��V���h�E���V�[�o�[�ɂ���B
	//m_stageModelDraw.SetShadowReciever(true);

	//�����_�����O�^�[�Q�b�g�̍쐬
	//m_renderTarget.Create(FRAME_BUFFER_W, FRAME_BUFFER_H, DXGI_FORMAT_R8G8B8A8_UNORM);
	//���C���ƂȂ郌���_�[�^�[�Q�b�g���쐬�B
	/*m_mainRenderTarget.Create(
	    FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R8G8B8A8_UNORM
	);

	//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G��
	//�t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g������������B
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
	//�����_�����O�^�[�Q�b�g�̐؂�ւ��B
	d3dDeviceContext->OMSetRenderTargets(1, rtTbl, depthStensil);
	if (viewport != nullptr) {
		//�r���[�|�[�g���w�肳��Ă�����A�r���[�|�[�g���ύX����B
		d3dDeviceContext->RSSetViewports(1, viewport);
	}
}

void Game::Update()
{
	//���x���̕`��
	//if (bikemaster->GetbikesetFlag() == true)
	//{
		level.Draw();
		//goal->Update();
		/*if (course != nullptr)
		{
			course->Update();
		}*/
	//}
	
	//�A�C�e���g�̕`��
	//itemwaku->Update();
	//bikeselect->Update();
	

	//bikeselect->Update();
	//�J����
	
	bikemaster->Update();
   
	
	//�V���h�E�L���X�^�[��o�^
	//m_shadowMap.RegistShadowCaster(&m_playerModelDraw);
	//m_shadowMap.RegistShadowCaster(&m_enemyModelDraw);
	//m_shadowMap.RegistShadowCaster(&m_stageModelDraw);
	///�V���h�E�}�b�v���X�V
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
	//�V���h�E�}�b�v�Ƀ����_�����O
	//m_shadowMap.RenderToShadowMap();
}

void Game::ForwordRender()
{
	/*
	//�����_�����O�^�[�Q�b�g�����C���ɕύX����B
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ChangeRenderTarget(d3dDeviceContext, &m_mainRenderTarget, &m_frameBufferViewports);
	//���C�������_�����O�^�[�Q�b�g���N���A����B
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_mainRenderTarget.ClearRenderTarget(clearColor);
	*/
	
	g_goMgr.Draw();
}

void Game::PostRender()
{
	//�����_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɖ߂��B
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ChangeRenderTarget(
		d3dDeviceContext,
		m_frameBufferRenderTargetView,
		m_frameBufferDepthStencilView,
		&m_frameBufferViewports
	);
	//�h���h��
	//m_copyMainRtToFrameBufferSprite.Draw();

	m_frameBufferRenderTargetView->Release();
	m_frameBufferDepthStencilView->Release();
}

void Game::Render()
{
	//�`��J�n�B
	//g_graphicsEngine->BegineRender();


	/*
	//�`��J�n�B
	g_graphicsEngine->BegineRender();
	//�t���[���o�@�t�@�̃����_�����O�^�[�Q�b�g��
	//�o�b�N�A�b�v���Ă����B
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	d3dDeviceContext->OMGetRenderTargets(
		1,
		&m_frameBufferRenderTargetView,
		&m_frameBufferDepthStencilView
	);
	//�r���[�|�[�g���o�b�N�A�b�v������Ă����B
	unsigned int numViewport = 1;
	d3dDeviceContext->RSGetViewports(&numViewport, &m_frameBufferViewports);

	//�v�������_�����O
	PreRender();

	//�t�H���[�h�����_�����O
	ForwordRender();

	//�|�X�g�����_�����O
	PostRender();
	
	//�`��I��
	g_graphicsEngine->EndRender();
	*/
}