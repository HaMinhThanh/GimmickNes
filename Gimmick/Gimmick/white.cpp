#include "white.h"
#include "Brick.h"
#include "Gimmick.h"
#include"PlayScene.h"


CWhite::CWhite(int t)
{
	type = t;
	if (type ==2)
	{
		SetState(WHITE_STATE_IDLE);
	}
	else if(type==1)
	{
		SetState(WHITE_STATE_WALKING_RIGHT);
	}
	else
		SetState(WHITE_STATE_WALKING_LEFT);
	
}
void CWhite::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
		left = x;
		top = y;
		right = x + BOMB_ITEM_BBOX_WIDTH;
		bottom = y - BOMB_ITEM_BBOX_HEIGHT;
}

void CWhite::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (GetTickCount() - idle_start > 500)
	{
		idle_start = 0;
		idle = 0;
	}
	if (GetTickCount() - idleBack_start > 800)
	{
		idleBack_start = 0;
		idleBack = 0;
	}

	if (GetTickCount() - back_start > 800)
	{
		back_start = 0;
		back = 0;
	}


	if (idleBack == 1)
	{
		if(back==1)
		SetState(WHITE_STATE_WALKING_LEFT_BACK);
		/*else if(back==0)
		{
			SetState(WHITE_STATE_IDLE);
		}*/
	}
	else
	{
		if (type == 2)
		{
			SetState(WHITE_STATE_IDLE_LEFT);
		}
	}
	
	if (idle == 1)
	{
		SetState(WHITE_STATE_IDLE);
	}
	else
	{
		if (nx > 0 && ( type==1 || type==3))
			SetState(WHITE_STATE_WALKING_RIGHT);

		else if(nx<0 && (type==1 || type == 3))
		{
			SetState(WHITE_STATE_WALKING_LEFT);
		}

	}

	if (GetTickCount() - delay_start > 500)
	{
		delay_start = 0;
		delay = 0;
	}
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

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;


		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
}

void CWhite::Render()
{
	int ani;
	if (state == WHITE_STATE_WALKING_RIGHT) {
		ani = WHITE_ANI_WALKING_LEFT;

	}
	else if(state == WHITE_STATE_WALKING_LEFT)
		ani = WHITE_ANI_WALKING_RIGHT;
	else if (state == WHITE_STATE_WALKING_LEFT_BACK)
		ani = WHITE_ANI_WALKING_LEFT;
	
	
	else if (state==WHITE_STATE_IDLE_LEFT)
	{
		ani = WHITE_ANI_IDLE_RIGHT;
	}
	/*else if (state == WHITE_STATE_IDLE)
	{
		if(nx<0)
		ani = WHITE_ANI_IDLE_RIGHT;
		else
			ani = WHITE_ANI_IDLE_LEFT;
	}*/
	else if(nx<0)
	{
		ani = WHITE_ANI_IDLE_LEFT;
	}
	else
		ani = WHITE_ANI_IDLE_RIGHT;
	animation_set->at(ani)->Render(x, y);
}

void CWhite::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case WHITE_STATE_WALKING_RIGHT:
		//y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE + 1;
		vx = WHITE_WALKING_SPEED;
		vy = 0;
		nx = 1;
		break;
	case WHITE_STATE_WALKING_LEFT:
		vx = -WHITE_WALKING_SPEED;
		vy = 0;
		nx = -1;
		break;

	case WHITE_STATE_WALKING_LEFT_BACK:
		vx = -WHITE_WALKING_SPEED;
		vy = 0;
		nx = -1;
		break;
	case WHITE_STATE_IDLE_LEFT:
		vx = 0;
		vy = 0;
		break;
	case WHITE_STATE_IDLE:
		vx = 0;
		vy = 0;
	}
}

