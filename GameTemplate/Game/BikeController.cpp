#include "stdafx.h"
#include "BikeController.h"
#include "Game.h"

BikeController::BikeController()
{
}


BikeController::~BikeController()
{
}

//ƒvƒŒƒCƒ„[‚ð“®‚©‚·ŠÖ”
const CVector3 BikeController::PlayerMove(CVector3 moveSpeed, CVector3 accel, CVector3 pos, float friction)
{
	

	moveSpeed += accel;
	//–€ŽCŒW”‚ðæŽZ
	moveSpeed *= friction;
	//ˆÚ“®‘¬“x‚ðŒvŽZ
	pos += moveSpeed;
	if (moveSpeed.LengthSq() >= 300.0f * 300.0f) {
		moveSpeed.Normalize();
		moveSpeed *= 300.0f;
	}
	return pos;
}
