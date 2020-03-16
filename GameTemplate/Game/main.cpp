#include "stdafx.h"
#include "system/system.h"
#include "Player.h"
#include "StageDemo.h"
#include "level/Level.h"
#include "GameObjectManager.h"
#include <iostream>
#include "Game.h"
#include "Title.h"
#include "Result.h"
//Game* g_game = nullptr;
///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//カメラを初期化。
	/*g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);*/
	
	
	//Game *game;
   // game = g_goMgr.NewGO<Game>();

	Title *title;
	title = g_goMgr.NewGO<Title>();

	//Result *result;
	//result = g_goMgr.NewGO<Result>();
	//g_game = &Game::GetInstance();
	//g_game = g_goMgr.NewGO<Game>();
     
	
	

	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//描画開始。
		g_graphicsEngine->BegineRender();
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//物理エンジンの更新。
		g_physics.Update();
		
		//ゲームの更新処理
		//game->Update();
		//title->Update();
		g_goMgr.Update();
		
		
		//描画終了。
		g_graphicsEngine->EndRender();
	}
}