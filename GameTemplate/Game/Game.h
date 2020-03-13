#pragma once
#include "RenderTarget.h"
#include "level/Level.h"
#include "Player.h"
#include "GameObjectManager.h"
#include "GameCamera.h"
#include "ItemWaku.h"
#include "BikeMove_Enemy.h"
#include "Goal.h"
#include "Result.h"
//バイク
#include "AlphaBike.h"
#include "BetaBike.h"
#include "GammaBike.h"
#include "DeltaBike.h"
#include "EpsilonBike.h"
//ポストエフェクト関連
#include "RenderTarget.h"
#include "ShadowMap.h"
#include "graphics/Sprite.h"
#include "graphics/SkinModel.h"
#include "BikeMove_Enemy.h"
class Player;
class ItemWaku;
class CoursePath;
class BikeMove_Enemy;
class BetaBike;
class Goal;
//class StageDemo;
//class AlphaBike;
/// <summary>

/// ゲームクラス
/// </summary>
/// 
/*struct Point {
	CVector3 s_position;
	int s_number;
};*/
class Game : public IGameObject
{
	
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Game();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Game();


public:
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Render();
	/// <summary>
	/// シングルトンパターン
	/// </summary>
	
	/// <summary>
	/// シャドウマップを取得
	/// </summary>
	/// <returns></returns>
	ShadowMap* GetShadowMap()
	{
		//return &m_shadowMap;
	}
	//次のポイントを返す
	Point* GetNextNumber(int number)
	{
		if (m_pointList.count(number + 1) == 0) {
			return m_pointList[1];
		}
		else {
			return m_pointList[number + 1];
		}
	}

	Point* GetGorlPoint()
	{
		return m_pointList[1];
	}
	
private:
	/// <summary>
	/// プリレンダリング
	/// </summary>
	void PreRender();
	/// <summary>
	/// フォワードレンダリング
	/// </summary>
	void ForwordRender();
	/// <summary>
	/// ポストレンダリング
	/// </summary>
	void PostRender();

	/// <summary>
	/// レンダリングターゲットの切り替え
	/// </summary>
	/// <param name="d3dDeviceContext">D3Dデバイスコンテキスト</param>
	/// <param name="renderTarget">レンダリングターゲット</param>
	/// <param name="viewport">ビューポート</param>
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);
	/// <summary>
private:
	//オフスクリーンレンダリング
	//SkinModel m_playerModelDraw;       //プレイヤーの描画処理
	//SkinModel m_enemyModelDraw;        //敵バイクの描画処理
	//SkinModel m_stageModelDraw;        //ステージの描画処理
	//RenderTarget m_mainRenderTarget;
	//ShadowMap m_shadowMap;

	//Sprite m_copyMainRtToFrameBufferSprite;         //メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト。
	D3D11_VIEWPORT m_frameBufferViewports;          //フレームバッファのビューポート。
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;   //フレームバァファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;   //フレームバァファのデプスステンシルビュー。

	//オブジェクトのポインタ
	Level level;	//レベル
	Player* player = nullptr;	//プレイヤー
	GameCamera* gamecamera = nullptr;
	AlphaBike* alphabike = nullptr;  //バイク１
	BetaBike*  betabike = nullptr;   //バイク2
	GammaBike* gammabike = nullptr;  //バイク3
	DeltaBike* deltabike = nullptr;  //バイク4
	EpsilonBike* epsilonbike = nullptr;
	ItemWaku* itemwaku = nullptr;  //アイテム表示の枠
	Goal* goal = nullptr;
	//BikeMove_Enemy m_bikemove_enemy;
	
	//CoursePath* coursepath;
	
	
	int finishhantei = 0;
	std::map<int , Point*> m_pointList;
	
};

//extern Game &g_game;