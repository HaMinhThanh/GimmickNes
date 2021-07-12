#include "Bird.h"
#include "Camera.h"
#include "Define.h"

CBird::CBird(float _x, float _y)
{
	x = _x;
	y = _y;

	if (_x == 320)
		type = 1;
	else
		type = 2;

	vx = 0;
	vy = 0;

	backupX = _x;
	backupY = _y;

	isMoving = false;
	isFinish = false;
}

CBird::~CBird()
{
}

void CBird::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isMoving)
	{
		if (type==1)
			vx = BIRD_SPEED_X;
		else if (type == 2)
			vx = -BIRD_SPEED_X;


	}

	if (isFinish) {

		float camx, camy;
		CCamera::GetInstance()->GetCamPos(camx, camy);

		if (x+50< camx || x-10> camx + SCREEN_WIDTH || y< camy || y> camy + SCREEN_HEIGHT_MAP) {

			isFinish = false;
			isMoving = false;
			moving = 0;

			//SetPosition(backupX, backupY);

		}
	}

	if (type == 1)
	{
		if (moving > 0)
		{
			if (GetTickCount() - time_end >= 19200) {

				moving = 3;
				time_end = 0;

				vy = 0.04;
				if (type == 1)
					vx += 0.04;
			}
			else if (GetTickCount() - time_end >= 19000 && GetTickCount() - time_end < 19200) {

				isFinish = true;
				moving = 2;
				vy = 0.04;
				if (type == 1)
					vx += 0.04;

			}
			else if (GetTickCount() - time_end >= 18000 && GetTickCount() - time_end < 19000) {

				if (type == 1)
					vx = 0.02;


			}
			else if (GetTickCount() - time_end >= 800 && GetTickCount() - time_end < 18000) {

				isMoving = true;
			}

			CGameObject::Update(dt);

			x += dx;
			y += dy;

		}
	}
	else if (type==2)
	{
		if (moving > 0)
		{
			if (GetTickCount() - time_end >= 4700) {

				moving = 3;
				time_end = 0;

				vy = 0.04;
				vx = -0.08;
			}
			else if (GetTickCount() - time_end >= 3500 && GetTickCount() - time_end < 4700) {

				isFinish = true;
				moving = 2;
				vy = 0.08;
				vx = -0.08;

			}
			else if (GetTickCount() - time_end >= 2500 && GetTickCount() - time_end < 3500) {

				vx = 0;


			}
			else if (GetTickCount() - time_end >= 800 && GetTickCount() - time_end < 2500) {

				isMoving = true;
			}

			CGameObject::Update(dt);

			x += dx;
			y += dy;

		}
	}

}

void CBird::Render()
{
	if (type == 1)
	{
		if (moving == 0 || isMoving == false)
			animation_set->at(0)->Render(x, y);
		else if (moving == 1)
		{
			animation_set->at(2)->Render(x, y);
		}
		else if (moving == 2)
			animation_set->at(2)->Render(x, y);
		else if (moving == 3)
			animation_set->at(2)->Render(x, y);
	}
	else if (type == 2)
	{
		if (moving == 0 || isMoving == false)
			animation_set->at(1)->Render(x, y);
		else if (moving == 1)
		{
			animation_set->at(3)->Render(x, y);
		}
		else if (moving == 2)
			animation_set->at(3)->Render(x, y);
		else if (moving == 3)
			animation_set->at(3)->Render(x, y);
	}
}

void CBird::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (moving == 0)
	{
		left = x-72;
		top = y - 12 -32 ;
		right = x + 36 -60;
		bottom = y - 24 -32 ;
	}		
	else if(!isFinish) {

		left = x;
		top = y-12;
		right = x + 36;
		bottom = y - 24 ;
	}

}
