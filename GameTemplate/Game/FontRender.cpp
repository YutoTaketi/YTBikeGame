#include "stdafx.h"
#include "FontRender.h"
#include "Font.h"

FontRender::FontRender()
{

}

FontRender::~FontRender()
{

}

void FontRender::SetText(const wchar_t * text)
{
	m_font.DrawScreenPos(
		text,
		pos,
		color,
		scale,
		pivot,
		effects
	);
}


