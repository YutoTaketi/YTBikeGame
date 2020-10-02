#pragma once
class FontRender
{
public:
	FontRender();
	~FontRender();
	
	void SetText(const wchar_t * text);

	CVector2& pos = CVector2::Zero();
	CVector4& color = CVector4::White();
	CVector2& scale = CVector2::One();
	CVector2& pivot = CVector2::Zero();
	float rotation = 0.0f;
	DirectX::SpriteEffects effects = DirectX::SpriteEffects_None;

	Font m_font;
};

