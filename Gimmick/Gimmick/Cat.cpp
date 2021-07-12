#include "Cat.h"
#include "Brick.h"
#include "ScrollBar.h"
#include "Gimmick.h"
#include "Slide.h"
#include "Star.h"
#include "White.h"


CCat::CCat(int t)
{
	type = t;
	if (type == 1)
	{
		SetState(CAT_STATE_IDLE_LEFT);
	}
	else
		SetState(CAT_STATE_IDLE_RIGHT);
}


void CCat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	vy += CAT_GRAVITY * dt;


	vector<LPGAMEOBJECT> Bricks;
	Bricks.clear();

	if (GetState() != CAT_STATE_DIE) {

		for (UINT i = 0; i < coObjects->size(); i++) {

			if (dynamic_cast<CBrick*>(coObjects->at(i))
				|| dynamic_cast<CScrollBar*>(coObjects->at(i))
				|| dynamic_cast<CWhite*>(coObjects->at(i))
				|| dynamic_cast<CSlide*>(coObjects->at(i))) {

				Bricks.push_back(coObjects->at(i));
			}
		}
	}

	vector<LPCOLLISIONEVENT>  coEvents;
	vector<LPCOLLISIONEVENT>  coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(&Bricks, coEvents);

	if (coEvents.size() == 0) {

		x += dx;
		y += dy;
	}
	else {

		float min_tx, min_ty, nx = 0, ny;
		float rdx, rdy;

		float max = 0, min = 999999999;

		float l, t, r, b;
		float l1, t1, r1, b1;
		GetBoundingBox(l1, t1, r1, b1);

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.04f;
		y += min_ty * dy + ny * 0.04f;

		for (UINT i = 0; i < coEventsResult.size(); i++) {
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CWhite*>(e->obj)) // if e->obj is Goomba 
			{
				CWhite* white = dynamic_cast<CWhite*>(e->obj);
				// jump on top 
				if (e->ny > 0 && shoot != 1)
				{
					x = white->x;
				}
			}

		}
		for (UINT i = 0; i < coEvents.size(); i++) {

			coEvents[i]->obj->GetBoundingBox(l, t, r, b);

			if (r > max /*&& t1 < t*/)
			{
				max = r;
			}
			if (l < min /*&& t1 < t*/)
			{
				min = l;
			}
		}

		if (r1 - CAT_JUMP_ALIGN > max && vx > 0 || l1 + CAT_JUMP_ALIGN < min && vx < 0) {

			Jumping();
		}

		if (abs(CGimmick::GetInstance(0, 0)->GetX() - x) >= CAT_MAX_DISTANCE_WITH_GIMMICK) {

			if (GetState() == CAT_STATE_WALKING_LEFT && CGimmick::GetInstance(0, 0)->GetX() > x)
				SetState(CAT_STATE_WALKING_RIGHT);

			if (GetState() == CAT_STATE_WALKING_RIGHT && CGimmick::GetInstance(0, 0)->GetX() < x)
				SetState(CAT_STATE_WALKING_LEFT);
		}

		if (nx != 0 && ny == 0) {

			if ((x < CGimmick::GetInstance(0, 0)->GetX() && vx < 0)
				|| (x > CGimmick::GetInstance(0, 0)->GetX() && vx > 0)) {

				if (GetState() == CAT_STATE_WALKING_LEFT) {

					SetState(CAT_STATE_WALKING_RIGHT);
				}
				else {

					SetState(CAT_STATE_WALKING_LEFT);
				}
			}

			Jumping();
		}

		if (ny != 0) {

			vy = 0;
		}

		min = 0;
		max = 9999999;
	}
}

void CCat::Render()
{
	int state = GetState();

	if (state == CAT_STATE_WALKING_RIGHT)
		animation_set->at(3)->Render(x, y - 1);

	else if (state == CAT_STATE_WALKING_LEFT)
		animation_set->at(2)->Render(x, y - 1);

	else if (state == CAT_STATE_IDLE_RIGHT)
		animation_set->at(1)->Render(x, y);
	else if (state == CAT_STATE_IDLE_LEFT)
		animation_set->at(0)->Render(x, y);

}

void CCat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + CAT_BBOX_WIDTH;
	bottom = y - CAT_BBOX_HEIGHT;
}

void CCat::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state) {

	case CAT_STATE_WALKING_RIGHT:
		vx = CAT_SPEED_X;
		nx = 1;
		break;

	case CAT_STATE_WALKING_LEFT:
		vx = -CAT_SPEED_X;
		nx = -1;
		break;
		break;

	case CAT_STATE_IDLE_LEFT:
		vx = 0;
		vy = 0;
		nx = -1;
		break;
	case CAT_STATE_IDLE_RIGHT:
		vx = 0;
		vy = 0;
		nx = 1;
		break;

	}
}