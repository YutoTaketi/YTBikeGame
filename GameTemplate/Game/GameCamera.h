#pragma once
#include "GameObjectManager.h"
#include "graphics/Camera.h"

class Player;
class BikeMove_Player;
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	/// <summary>
	/// 更新関数
	/// </summary>
	
	void Update();
	void Render();

	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw();
	//プレイヤーのポインタをセットする
	void SetPlayer(Player* player)
	{
		m_player = player;
	}

	
    
	
private:
	
	Player* m_player = nullptr;
	BikeMove_Player* m_bikemove_Player = nullptr;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_target = CVector3::Zero();
	CVector3 m_toCameraPos = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_finishposition = CVector3::Zero();
	
	
};

