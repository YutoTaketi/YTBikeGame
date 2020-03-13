#pragma once

#include "BikeMove.h"
#include "BikeController.h"
#include "Game.h"
/// <summary>
/// プレイヤーのバイクを動かす。
/// </summary>
class Game;
class BikeMove_Player : public BikeMove
{
public:
	BikeMove_Player();
	~BikeMove_Player();

	

	/// <summary>
	/// プレイヤーが使用するバイクの更新関数
	/// </summary>
	/// <param name="position"></param>
	/// <param name="rotation"></param>
	/// <param name="movespeed"></param>
	/// <param name="accel"></param>
	/// <param name="accelnum"></param>
	/// <param name="friction"></param>
	void Execute(CVector3& position, CQuaternion& rotation, CVector3& movespeed, CVector3& accel, float& accelnum,float& friction);
	CVector3 m_moveDirectionF = CVector3::Zero();     //移動方向
	CVector3 playermae = { 0, 0, 1 };                 //バイクの前方向
	CVector3 sinkouhoukou = g_camera3D.GetForward();  //進行方向
	BikeController* m_bikecontroller;                 //バイクの内積外積計算をする。

	Game* m_game;
	
};

