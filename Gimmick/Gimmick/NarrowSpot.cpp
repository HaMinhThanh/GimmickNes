#include "NarrowSpot.h"

CNarrowSpot::CNarrowSpot(float _x, float _y)
{
	x = _x;
	y = _y;

	vx = 0;
	vx = 0;

	isMoving = false;
}

CNarrowSpot::~CNarrowSpot()
{
}

void CNarrowSpot::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isMoving)
		vx = NARROWSPOT_SPEED_X;

	if (moving > 0)
	{
		if (GetTickCount() - time_end >= 3200) {

			moving = 3;
			time_end = 0;
		}
		else if (GetTickCount() - time_end >= 3000 && GetTickCount() - time_end < 3200) {

			isFinish = true;
			moving = 2;
		}
		else if (GetTickCount() - time_end >= 2000 && GetTickCount() - time_end < 3000) {
			
			vx = 0;
			isMoving = false;			
		}
		else if (GetTickCount() - time_end >= 500 && GetTickCount() - time_end < 2000) {

			isMoving = true;
		}
		else if (GetTickCount() - time_end < 1000) {


		}
	}

	CGameObject::Update(dt);

	x += dx;
	y += dy;
}

void CNarrowSpot::Render()
{
	if (moving == 0 || moving == 1)
		animation_set->at(0)->Render(x, y);
	else if (moving == 2)
		animation_set->at(1)->Render(x, y);
	else if (moving == 3)
		animation_set->at(2)->Render(x, y);
}

void CNarrowSpot::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isFinish) {

		left = x;
		top = y - 64;
		right = x + 36;
		bottom = y - 68;
	}
}
