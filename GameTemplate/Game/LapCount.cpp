#include "stdafx.h"
#include "LapCount.h"
#include "Font.h"
#include "graphics/GraphicsEngine.h"
#include "BikeSelect.h"

LapCount::LapCount()
{
	m_font = new Font();
	m_Fontpos = { 200.0f, 0.0f };
	m_font2 = new Font();
	m_Fontpos2 = { 160.0f, 0.0f };
}


LapCount::~LapCount()
{
}

void LapCount::Update()
{
	m_font2->DrawScreenPos(
		L"1",
		m_Fontpos2,
		m_color2,
		m_Fontscale2,
		pivot2,
		rot2,
		DirectX::SpriteEffects_None
	);
	
	/*m_font2->DrawScreenPos(
		L"2",
		m_Fontpos2,
		m_color2,
		m_Fontscale2,
		pivot2,
		rot2,
		DirectX::SpriteEffects_None
	);*/

	/*
	m_font2->DrawScreenPos(
		L"3",
		m_Fontpos2,
		m_color2,
		m_Fontscale2,
		pivot2,
		rot2,
		DirectX::SpriteEffects_None
	);*/
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