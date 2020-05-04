#include "stdafx.h"
#include "LapCount.h"
#include "Font.h"

LapCount::LapCount()
{
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