#pragma once

#include "BikeMove.h"
#include "BikeController.h"
#include "Game.h"
#include "character/CharacterController.h"
#include "GameTime.h"
/// <summary>
/// プレイヤーのバイクを動かす。
/// </summary>
class Game;
class CharacterController;
class GameTime;
class Goal;
class BikeMove_Player : public BikeMove
{
public:
	BikeMove_Player();
	~BikeMove_Player();

	/// <summary>
	/// キャラコンを返す
	/// </summary>
	/// <returns></returns>
	CharacterController& GetCharaCon()
	{
		return m_charaCon;
	}


	/// <summary>
	/// プレイヤーが使用するバイクの更新関数
	/// </summary>
	/// <param name="position"></param>
	/// <param name="rotation"></param>
	/// <param name="movespeed"></param>
	/// <param name="accel"></param>
	/// <param name="accelnum"></param>
	/// <param name="friction"></param>
	void Execute(CVector3& m_position, CQuaternion& rotation, CVector3& movespeed, CVector3& accel, float& accelnum,float& friction);
	CVector3 m_position = CVector3::Zero();
	CVector3 m_moveDirectionF = CVector3::Zero();     //移動方向
	CVector3 playermae = { 0, 0, 1 };                 //バイクの前方向
	CVector3 sinkouhoukou = g_camera3D.GetForward();  //進行方向
	BikeController* m_bikecontroller;                 //バイクの内積外積計算をする。
	
	
	CharacterController m_charaCon;       //キャラクターコントローラー
	PhysicsGhostObject m_ghostObject;     //ゴーストオブジェクト

	int timer = 0;                        //ゴーストオブジェクトとの当たり判定用タイマー
	bool m_CharaConInitFlag = false;     //キャラクターコントローラーが初期化されているかのフラグ
};

