/*!
 * @brief	�t�H���g
 */

#pragma once

class Font
{
public:
	Font();
	~Font();

	/*!
	* @brief	�t�H���g��ݒ�B
	* @details	�f�t�H���g�t�H���g����ύX�������ꍇ��
	*  DirectX::SpriteFont���g�p���āA�t�H���g�����[�h���č����ւ����s���Ă��������B
	*/
	void SetFont(DirectX::SpriteFont* font)
	{
		m_spriteFont = font;
	}

	/*!
     * @brief	�`��J�n�B
	 */
	void Begin();
	/*!
     * @brief	�`��I���B
	 */
	void End();

	/*!
	 * @brief	�`��B
	 *@param[in]	text		�\���������e�L�X�g�B
	 *@param[in]	trans		���s�ړ��B
	 *@param[in]	color		�J���[�B
	 *@param[in]	rot			��]�B
	 *@param[in]	scale		�g��B
	 *@param[in]	pivot		��_�B
	 *						0.5, 0.5�ŉ摜�̒��S����_�B
	 *						0.0, 0.0�ŉ摜�̍����B
	 *						1.0, 1.0�ŉ摜�̉E��B
	 *						Unity��uGUI�ɏ����B
	 */
	void Draw(
		wchar_t const* text,
		const CVector2& position,
		const CVector4& color = CVector4::White(),
		float rotation = 0.0f,
		float scale = 1.0f,
		CVector2 pivot = { 0.5f, 0.5f }
	);
	
private:
	DirectX::SpriteBatch*  m_spriteBatch = nullptr;
	DirectX::SpriteFont*   m_spriteFont = nullptr;
	bool m_isDrawShadow = false;
	float m_shadowOffset = 0.0f;
	CVector4 m_shadowColor = CVector4::White();
	CMatrix m_scaleMat;

};

