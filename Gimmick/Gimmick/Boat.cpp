#include "Boat.h"
#include "Camera.h"
#include "Define.h"

CBoat::CBoat(float _x, float _y)
{
	x = _x;
	y = _y;

	vx = 0;
	vx = 0;

	backupX = _x;
	backupY = _y;

	isMoving = false;
	isFinish = false;
}

CBoat::~CBoat()
{
}

void CBoat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isMoving)
	{
		vx = BOAT_SPEED_X;

	}

	if (isFinish) {

		float camx, camy;
		CCamera::GetInstance()->GetCamPos(camx, camy);

		if (x< camx || x> camx + SCREEN_WIDTH || y< camy || y> camy + SCREEN_HEIGHT_MAP) {

			isFinish = false;
			isMoving = false;
			moving = 0;

			SetPosition(backupX, backupY);

		}
	}

	if (moving > 0)
	{
		if (GetTickCount() - time_end >= 19200) {

			moving = 3;
			time_end = 0;
		}
		else if (GetTickCount() - time_end >= 19000 && GetTickCount() - time_end < 19200) {

			isFinish = true;
			moving = 2;
		}
		else if (GetTickCount() - time_end >= 18000 && GetTickCount() - time_end < 19000) {

			vx = 0;
			isMoving = false;
		}
		else if (GetTickCount() - time_end >= 500 && GetTickCount() - time_end < 18000) {

			isMoving = true;
		}

		CGameObject::Update(dt);

		x += dx;
		y += dy;

	}
}

void CBoat::Render()
{
	if (moving == 0 || moving == 1)
		animation_set->at(0)->Render(x, y);
	else if (moving == 2)
		animation_set->at(1)->Render(x, y);
	else if (moving == 3)
		animation_set->at(2)->Render(x, y);
}

void CBoat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isFinish) {

		left = x;
		top = y;
		right = x + 36;
		bottom = y - 200;
	}
	else
	{
		left = x;
		top = y;
		right = x + 36;
		bottom = y - 200;
	}
}