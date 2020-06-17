#include "stdafx.h"
#include "LapCount.h"
#include "Font.h"
#include "graphics/GraphicsEngine.h"
#include "BikeSelect.h"
#include "Game.h"

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
	/*
	if (m_game->GetLapCheck() == 0 || m_game->GetLapCheck() == 1)
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
	}
	
	if (m_game->GetLapCheck() == 2)
	{
		m_font2->DrawScreenPos(
			L"2",
			m_Fontpos2,
			m_color2,
			m_Fontscale2,
			pivot2,
			rot2,
			DirectX::SpriteEffects_None
		);
	}
	if (m_game->GetLapCheck() == 3)
	{
		m_font2->DrawScreenPos(
			L"3",
			m_Fontpos2,
			m_color2,
			m_Fontscale2,
			pivot2,
			rot2,
			DirectX::SpriteEffects_None
		);
	}
	m_font->DrawScreenPos(
			L"/3",
			m_Fontpos,
			m_color,
			m_Fontscale,
			pivot,
			rot,
			DirectX::SpriteEffects_None
	);
	*/
}

void LapCount::Render()
{
	if (m_game->GetLapCheck() == 0 || m_game->GetLapCheck() == 1)
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
	}

	if (m_game->GetLapCheck() == 2)
	{
		m_font2->DrawScreenPos(
			L"2",
			m_Fontpos2,
			m_color2,
			m_Fontscale2,
			pivot2,
			rot2,
			DirectX::SpriteEffects_None
		);
	}
	if (m_game->GetLapCheck() == 3)
	{
		m_font2->DrawScreenPos(
			L"3",
			m_Fontpos2,
			m_color2,
			m_Fontscale2,
			pivot2,
			rot2,
			DirectX::SpriteEffects_None
		);
	}
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

void LapCount::Draw()
{

}