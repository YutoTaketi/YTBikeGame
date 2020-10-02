/*!
 * @brief	フォント
 */

#pragma once

class Font
{
public:
	Font();
	~Font();

	void DrawScreenPos(
	    const wchar_t * text,
		const CVector2& pos,
		const CVector4& color = CVector4::White(),
		const CVector2& scale = CVector2::One(),
		const CVector2& pivot = CVector2::Zero(),
		float rotation = 0.0f,
		DirectX::SpriteEffects effects = DirectX::SpriteEffects_None
	);
private:
	DirectX::SpriteBatch* m_spriteBatch = nullptr;  //!<スプライトバッチ
	DirectX::SpriteFont*  m_spriteFont = nullptr;   //フォント
	CVector2 m_screenSize;
};

