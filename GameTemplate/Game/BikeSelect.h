#pragma once
#include "GameObjectManager.h"
#include "graphics/Sprite.h"
class BikeMaster;
class BikeSelect : public  IGameObject
{
public:
	BikeSelect();
	~BikeSelect();

	/// <summary>
	/// BikeMaster�̃|�C���^��n���B
	/// </summary>
	/// <param name="game"></param>
	void SetBikeMaster(BikeMaster* bikemaster)
	{
		m_bikemaster = bikemaster;
		
	}
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();
private:
	void Render();
	void Draw();
	CVector3 m_position = CVector3::Zero();   //���W
	CVector3 m_scale = CVector3::One();       //�X�P�[��
	CQuaternion m_rotation = CQuaternion::Identity(); //��]
	Sprite m_sprite;
	BikeMaster* m_bikemaster = nullptr;
};

