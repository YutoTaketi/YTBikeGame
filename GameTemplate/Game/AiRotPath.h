#pragma once
#include "GameObjectManager.h"

class AiRotPath
{	
public:
	AiRotPath();
	~AiRotPath();
	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();

private:
	void Render();
	void Draw();

	CVector3 m_position = CVector3::Zero(); //座標
	//CVector3 m_ro
};

