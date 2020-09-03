#pragma once
#include "graphics/RenderTarget.h"
#include "level/Level.h"
#include "GameObjectManager.h"
#include "GameCamera.h"
#include "ItemWaku.h"
#include "BikeMove_Enemy.h"
#include "Goal.h"
#include "Result.h"
#include "graphics/ShadowMap.h"
#include "SoundEngine.h"

//ポストエフェクト関連
#include "graphics/RenderTarget.h"
#include "graphics/ShadowMap.h"
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
class Kyakuseki;
class Road;
class Jimen;
class Signal;
class Guest;
//class Sky;
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
	/// <summary>
	/// パス移動のポイントを返す
	/// </summary>
	/// <returns></returns>
	Point* GetGorlPoint()
	{
		return m_pointList[1];
	}
	/// <summary>
	/// ラップカウント
	/// </summary>
	/// <returns></returns>
	bool LapCountUp()
	{
		lapcheck += 1;
		return true;
	}
	/// <summary>
	/// ラップチェック
	/// </summary>
	/// <returns></returns>
	bool GetLapCheck()
	{
		return lapcheck;
	}
	
	/// <summary>
	/// フィニッシュフラグの更新
	/// </summary>
	void ChangeFinishFlag()
	{
		finishFlag = true;
	}
	/// <summary>
	/// フィニッシュフラグを返す
	/// </summary>
	/// <returns></returns>
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
	/// シャドウマップを取得。
	/// </summary>
	/// <returns></returns>
	/*ShadowMap* GetShadowMap()
	{
		return &m_shadowMap;
	}*/
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

	SoundEngine m_soundEngine;    //サウンドエンジン

	//オブジェクトのポインタ
	Level level;	//レベル
	
	ItemWaku* itemwaku = nullptr;  //アイテム表示の枠
	Goal* goal = nullptr;
	BikeSelect* bikeselect = nullptr;   //バイクの選択画面
	BikeMaster* bikemaster = nullptr;   //バイクの生成を担当
	Course* course = nullptr;           //コース
	Kyakuseki* kyakuseki = nullptr;     //客席
	Road* road = nullptr;               //コース
	Jimen* jimen = nullptr;             //地面
	Signal* signal = nullptr;           //シグナル
	Guest* guest = nullptr;
	//Sky* sky = nullptr;

	LapCount* lapcount = nullptr;       //周回カウント
	ShadowMap m_shadowMap;              //シャドウマップ
	int lapcheck = 0;  //ラップチェック
	
	bool finishFlag = false;       //フィニッシュフラグ
	bool bikesentakuFlag = false;  //バイク選択フラグ

	std::map<int , Point*> m_pointList;  //パスのリスト
	
};

//extern Game &g_game;