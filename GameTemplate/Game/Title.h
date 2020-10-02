#pragma once
#include "GameObjectManager.h"
#include "graphics/Sprite.h"
#include "Font.h"
#include "FontRender.h"
//class Font;

class FontRender;
class Title : public IGameObject
{
public:
	Title();
	~Title();
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();
private:
	void Render();
	void Draw();
	CVector3 m_position = CVector3::Zero();            //���W
	CVector3 m_scale = CVector3::One();                //�g�嗦
	CQuaternion m_rotation = CQuaternion::Identity();  //��]

	CVector2 m_Fontpos = CVector2::Zero();             //�t�H���g���W
	CVector4 m_color = CVector4::White();              //�J���[
	CVector2 m_Fontscale = CVector2::One();            //�t�H���g�g�嗦
	CVector2 pivot = CVector2::Zero();                 //�s�{�b�g
	float rot = 0.0f;                                  //��]

	
	Sprite m_sprite;  //�X�v���C�g
	
	Font* m_font;     //�t�H���g
	FontRender m_fontrender;
};

