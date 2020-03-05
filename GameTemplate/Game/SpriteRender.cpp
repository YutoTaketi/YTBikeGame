#include "stdafx.h"
#include "SpriteRender.h"


/*SpriteRender::SpriteRender()
{
}


SpriteRender::~SpriteRender()
{
}*/

/*void SpriteRender::Init(const wchar_t* texFilePath, float w, float h, bool isDraw3D)
{
	m_isDraw3D = isDraw3D;
	m_testure.CrearteFromDDSTextureFromFile(texFilePath);
	m_sprite.Init(m_texture, w, h);
}

void SpriteRender::Update()
{
	m_sprite.SetTexture(m_texture);
	m_sprite.Update(m_position, m_rotation, m_scale, m_pivot);
}

/*void SpriteRender::ForwardRender(RenderContext& rc)
{
	if (m_isDraw3D == true) {
		m_sprite.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	}
}*/