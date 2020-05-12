#pragma once
#include "RenderTarget.h"
#include "level/Level.h"
#include "GameObjectManager.h"
#include "GameCamera.h"
#include "ItemWaku.h"
#include "BikeMove_Enemy.h"
#include "Goal.h"
#include "Result.h"

//ポストエフェクト関連
#include "RenderTarget.h"
#include "ShadowMap.h"
#include "graphics/Sprite.h"
#include "graphics/SkinModel.h"
#include "BikeMove_Enemy.h"

class ItemWaku;
class CoursePath;
class BikeMove_Enemy;
class BetaBike;
class Goal;
class BikeSelect;
class BikeMaster;
class Course;
class LapCount;
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
	
	bool LapCountUp()
	{
		lapcheck += 1;
		return true;
	}
	
	bool GetLapCheck()
	{
		return lapcheck;
	}
	

	void ChangeFinishFlag()
	{
		finishFlag = true;
	}

	bool GetFinishFlag()
	{
		return finishFlag;
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
	
	ItemWaku* itemwaku = nullptr;  //アイテム表示の枠
	Goal* goal = nullptr;
	BikeSelect* bikeselect = nullptr;   //バイクの選択画面
	BikeMaster* bikemaster = nullptr;   //バイクの生成を担当
	Course* course = nullptr;           //コース
	LapCount* lapcount = nullptr;       //周回カウント
	
	int lapcheck = 0;
	
	bool finishFlag = false;
	bool bikesentakuFlag = false;

	std::map<int , Point*> m_pointList;
	
};

//extern Game &g_game;