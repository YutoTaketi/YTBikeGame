#include "stdafx.h"
#include "BikeMaster.h"
#include <iostream>
using namespace std;

BikeMaster::BikeMaster()
{
	
}


BikeMaster::~BikeMaster()
{
}

void BikeMaster::Update()
{
	//�o�C�N�̔ԍ������
	if (GetAsyncKeyState('0'))
	{
		m_select = true;
	}
	
}

void BikeMaster::Render()
{

}
void BikeMaster::Draw()
{

}