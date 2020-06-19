#pragma once
#include "GameObjectManager.h"
#include "PhysicsGhostObject.h"
#include "physics/Physics.h"
#include "graphics/SkinModel.h"
class Game;
class EpsilonBike;
class BikeMaster;
class SkinModel;
class Goal : public IGameObject
{
public:
	Goal();
	~Goal();
	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();
	/// <summary>
	/// Gameのポインタをセットする
	/// </summary>
	/// <param name="game"></param>
	void SetGame(Game* game)
	{
		m_game = game;
		
	}
	
	/// <summary>
	/// 配置したゴールポイントの座標を取得
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 配置したゴールポイントのスケールを取得
	/// </summary>
	/// <param name="sale"></param>
	void SetScale(CVector3 scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// 回転を返す
	/// </summary>
	/// <param name="rot"></param>
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// ゴーストオブジェクトを返す
	/// </summary>
	/// <returns></returns>
	PhysicsGhostObject& GetGoalPoint()
	{
		return m_ghostObject;
	}

	CVector3 m_position = CVector3::Zero();  //座標
	CVector3 m_scale = CVector3::One();      //スケール
	CQuaternion m_rotation = CQuaternion::Identity();  //回転
private:
	void Render();
	void Draw();
	
	
	PhysicsGhostObject m_ghostObject;     //ゴーストオブジェクト
	SkinModel* m_model;                   //座標
	Game* m_game;                         //Gameポインタ
	
	BikeMaster* m_bikemaster;             //バイクマスターのポインタ
	bool MakeGoalFlag = false;            //ゴール作成フラグ
};