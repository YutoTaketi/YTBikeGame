/*!
 * @brief    �X�v���C�g�����_�[
*/

#pragma once
class SpriteRender : public IGameObject
{
public:
	//SpriteRender();
	/*!
	* @brief   ������
	*@param[in] texFilePath    �e�N�X�`���t�@�C���p�X
	*@param[in] w        ���B
	*@param[in] h       �����B
	*@param[in] isDraw3D       3D��Ԃŕ`�悷��?
	*/
	//~SpriteRender();

	//void Init(const wchar_t* texFilePath, float w, float h, bool isDraw3D = false);

	/*!
	* @brief     ���W��ݒ�
	*/
	/*void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}*/

	/*!
	* @brief     ���W���擾
	*/
	/*const CVector3& GetPosition()
	{
		return m_position;
	}*/
	/*!
	* @brief     ��]��ݒ�
	*/
	/*void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}*/
	/*!
	* @brief     ��]���擾
	*/
	/*const CQuaternion& GetRotation() const
	{
		return m_rotation;
	}*/
	/*!
     * @brief	�s�{�b�g��ݒ�B
	 *@param[in] pivot		��_�B
	 *						0.5, 0.5�ŉ摜�̒��S����_�B
     *						0.0, 0.0�ŉ摜�̍����B
	 *						1.0, 1.0�ŉ摜�̉E��B
	 *						Unity��uGUI�ɏ����B
	 */
	/*void SetPivot(const CVector2& pivot)
	{
		m_pivot = piovot;
	}*/
	/*!
	* @brief	��Z�J���[��ݒ�B
	*@param[in]	mulColor	��Z�J���[�B
	*/
	/*void SetMulColor(const CVector4& mulColor)
	{
		m_sprite.SetMulColor(mulColor);
	}*/
public:
	//void Update() override final;
	//void ForwardRender(CRenderContext& rc)override final;
	//void PostRender(CRenderContext& rc) override final;
private:
	//bool m_isDraw3D = false;          //!<3D��Ԃŕ`�悷��H
	//ShaderResourceView m_texture;  //!<�e�N�X�`���B
	//Sprite m_sprite;                  //!<�X�v���C�g�B
	//CVector3 m_position;              //!<���W�B
	//CQuaternion m_rotation;           //!<��]�B
	//CVector3 m_scale = CVector3::One();          //!<�g�嗦�B
	//CVector2 m_pivot = Sprite::DEFAULT_PIVOT;    //!<�s�{�b�g�B

};

