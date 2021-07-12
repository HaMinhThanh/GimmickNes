#include "Driller.h"
#include "Brick.h"
#include "Gimmick.h"


CDriller::CDriller(int t)
{
	type = t;
	if (type == 1)
	{
		SetState(WHITE_STATE_WALKING_LEFT);

	}
	else
	{
		SetState(WHITE_STATE_WALKING_RIGHT);
	}
}
void CDriller::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BOMB_ITEM_BBOX_WIDTH;
	bottom = y - BOMB_ITEM_BBOX_HEIGHT;
}

void CDriller::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	// Simple fall down


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);


	// No collision occured, proceed normally
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

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		/*if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;*/


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];


			if (dynamic_cast<CBrick*>(e->obj)) // if e->obj is Goomba 
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				if (nx != 0 && type == 1)
				{
					if (nx > 0)
					{
						nx = -1;
						vx = -vx;
					}
					else
					{
						nx = 1;
						vx = -vx;
					}
				}
			}

		}


	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];



}


void CDriller::Render()
{
	int ani;
	if (vx > 0) {
		ani = WHITE_ANI_WALKING_RIGHT;
	}
	else if (vx < 0)
		ani = WHITE_ANI_WALKING_LEFT;

	animation_set->at(ani)->Render(x, y);
}

void CDriller::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case WHITE_STATE_WALKING_RIGHT:
		vx = WHITE_WALKING_SPEED;
		nx = 1;
		break;
	case WHITE_STATE_WALKING_LEFT:
		vx = -WHITE_WALKING_SPEED;
		nx = -1;
		break;
	case WHITE_STATE_IDLE:
		vx = 0;
		vy = 0;
	}
}
