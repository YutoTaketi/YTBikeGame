#pragma once
#include "character/CharacterController.h"
#include "GameObjectManager.h"
#include "BikeController.h"
//#include "graphics/SkinModel.h"
//#include "graphics/Camera.h"
class BikeMove;
class Game;

class Player : public IGameObject
{
public:
	Player();
	~Player();
	
	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();
	/// <summary>
	/// 座標を返す
	/// </summary>
	/// <returns></returns>
    CVector3 GetPosition() const
	{
		return m_position;
	}
	
	
private:
	
	void Render();
	void Draw();
private:
	CVector3 m_position = CVector3::Zero();            //座標
	CQuaternion m_rotation = CQuaternion::Identity();  //回転
	CVector3 m_moveSpeed = CVector3::Zero();           //移動速度
	CVector3 m_accel = CVector3::Zero();               //加速度
	SkinModel* m_model;								   //スキンモデル。
	CVector3 m_playermae = CVector3::Zero();           //プレイヤーの前ベクトル
	CVector3 m_sinkouhouku = CVector3::Zero();         //進行方向
	CVector3 m_moveDirectionF = CVector3::Zero();      //カメラの前方向

	float m_accelNum = 1.8f;     //加速数値
	float m_friction = 0.97f;    //摩擦係数
	double SyukaihanteiOn = false; //周回判定
	int syukaicount = 0;          //周回カウント

	BikeController* m_bikecontroller = nullptr;       //バイクコントローラーのポインタ
	BikeMove* m_bikeMove = nullptr;                   //バイクムーブのポインタ
	Game* m_game = nullptr;                           //Gameのポインタ

	
};

