#pragma once
#include "GameObjectManager.h"
#include "graphics/Camera.h"

class Player;
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	
	void Update();
	void Render();

	/// <summary>
	/// �`��֐�
	/// </summary>
	void Draw();
	//�v���C���[�̃|�C���^���Z�b�g����
	void SetPlayer(Player* player)
	{
		m_player = player;
	}

	
    
	
private:
	
	Player* m_player = nullptr;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_target = CVector3::Zero();
	CVector3 m_toCameraPos = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	
	
};

