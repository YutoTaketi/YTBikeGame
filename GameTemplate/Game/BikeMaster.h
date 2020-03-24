#pragma once
#include "GameObjectManager.h"
class BikeMaster : public IGameObject
{
public:
	BikeMaster();
	~BikeMaster();

	void Update();

	int GetBikeNo()
	{
		return m_bikesentakuNo;
	}
	bool GetSelectFlag()
	{
		return m_select;
	}
private:
	void Render();
	void Draw();

	//バイクの選択番号
	int m_bikesentakuNo = 0;
	bool m_select = false;
};

