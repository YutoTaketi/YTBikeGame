#include "stdafx.h"
#include "RaceTimer.h"
#include "Font.h"

RaceTimer::RaceTimer()
{
	m_font = new Font();
}


RaceTimer::~RaceTimer()
{
}

void RaceTimer::Update()
{
	m_font->DrawScreenPos(
		L"Bike Operation",
		m_Fontpos,
		m_color,
		m_Fontscale,
		pivot,
		rot,
		DirectX::SpriteEffects_None
	);
}

void RaceTimer::Render()
{

}

void RaceTimer::Draw()
{

}