#pragma once
#include "BikeMove.h"
#include "BikeController.h"
#include "character/CharacterController.h"
/// <summary>
/// 敵のバイクを動かす。
/// </summary>

class Game;
class CharacterController;
class BikeMove_Enemy : public BikeMove
{
public:
	BikeMove_Enemy();
	~BikeMove_Enemy();
	/// <summary>
	/// AIで動くバイクの更新関数
	/// </summary>
	/// <param name="position"></param>
	/// <param name="rotation"></param>
	/// <param name="movespeed"></param>
	/// <param name="accel"></param>
	/// <param name="accelnum"></param>
	/// <param name="friction"></param>
	void Execute(CVector3& position, CQuaternion& rotation, CVector3& movespeed, CVector3& accel, float& accelnum, float& friction);
	CVector3 m_moveDirectionF = CVector3::Zero();  //前方向
	BikeController* m_bikecontroller;   //バイクコントローラーのポインタ
	CharacterController m_charaCon;     //キャラクターコントローラー
	bool m_CharaConInitFlag = false;    //キャラクターコントローラーが初期化されているかのフラグ
	bool m_AIStartFlag = false;         //AIが走り出すためのフラグ
	float m_StartTimer = 0.0f;          //AIが走り出すまでのタイマー

};