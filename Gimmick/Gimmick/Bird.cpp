#include "Bird.h"

CBird::CBird(int t)
{
	type = t;
	if (type == 1)
	{
		SetState(BIRD_STATE_IDLE);
	}
	
}

void CBird::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BIRD_BBOX_WIDTH;
	bottom = y - BIRD_BBOX_HEIGHT;

}

void CBird::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	
	CGameObject::Update(dt, coObjects);
	vy -= 0.08 * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

		CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;

	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (ny != 0) vy = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			
			if (nx != 0 /*&& ny == 0*/)
			{
				nx = -nx;
				vx = -vx;
			}


		}
		
		
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];



	}
}

void CBird::Render()
{
	int ani;
	if (state == BIRD_STATE_IDLE)
	{
		if (nx > 0)
		{
			ani = 0;
		}
		else
			ani = 2;
	}
	else if (state = BIRD_STATE_FLY_RIGHT)
	{
		ani = 1;
	}
	else
		ani = 3;

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CBird::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case BIRD_STATE_FLY_RIGHT:
			vx = 0.05;
			vy = 0.05;
			nx = 1;
			break;
		case BIRD_STATE_FLY_LEFT:
			vx = -0.05;
			vy = 0.05;
			nx = -1;
			break;
		case BIRD_STATE_IDLE:
			vy = 0;
			vx = 0;
			break;
	}
}
