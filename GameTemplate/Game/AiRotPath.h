#pragma once
#include "GameObjectManager.h"

class AiRotPath
{	
public:
	AiRotPath();
	~AiRotPath();
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();

private:
	void Render();
	void Draw();

	CVector3 m_position = CVector3::Zero(); //���W
	//CVector3 m_ro
};

