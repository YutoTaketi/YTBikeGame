#include "stdafx.h"
#include "LapCount.h"
#include "Font.h"
#include "graphics/GraphicsEngine.h"

LapCount::LapCount()
{
	m_font = new Font();
	m_Fontpos = { 1.0f, 0.0f };
}


LapCount::~LapCount()
{
}

void LapCount::Update()
{
	m_font->DrawScreenPos(
		L"/3",
		m_Fontpos,
		m_color,
		m_Fontscale,
		pivot,
		rot,
		DirectX::SpriteEffects_None
	);
	
}

void LapCount::Render()
{

}

void LapCount::Draw()
{

}