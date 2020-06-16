#pragma once
#include "GameObjectManager.h"

class AiRotPath
{	
public:
	AiRotPath();
	~AiRotPath();
	/// <summary>
	/// çXêVä÷êî
	/// </summary>
	void Update();

private:
	void Render();
	void Draw();

	CVector3 m_position = CVector3::Zero(); //ç¿ïW
	//CVector3 m_ro
};

