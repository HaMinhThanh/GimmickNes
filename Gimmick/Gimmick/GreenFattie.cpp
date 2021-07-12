#include "GreenFattie.h"
#include "Brick.h"
#include "ScrollBar.h"
#include "Gimmick.h"
#include "Slide.h"
#include "Star.h"

CGreenFattie::CGreenFattie(float _x, float _y, int _item)
{
	this->x = _x;
	this->y = _y;

	backupX = _x;
	backupY = _y;

	SetState(BOMB_STATE_WALKING_RIGHT);

	item = _item;
}

CGreenFattie::~CGreenFattie()
{
}

void CGreenFattie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	vy += BOMB_GRAVITY * dt;

	vector<LPGAMEOBJECT> Bricks;
	Bricks.clear();

	if (GetState() != BOMB_STATE_DIE) {

		for (UINT i = 0; i < coObjects->size(); i++) {

			if (dynamic_cast<CStar*>(coObjects->at(i))
				|| dynamic_cast<CBrick*>(coObjects->at(i))
				|| dynamic_cast<CScrollBar*>(coObjects->at(i))
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

			if (dynamic_cast<CScrollBar*>(e->obj)) {

				CScrollBar* sc = dynamic_cast<CScrollBar*>(e->obj);

				if (sc->GetType() == SCROLLBAR_TYPE_INCREASE) {

					if (vx > 0) {
						go_direct = 1;
					}
					else {
						go_direct = -1;
					}
					SetState(BOMB_STATE_SCROLLBAR_IN);
				}
				else if (sc->GetType() == SCROLLBAR_TYPE_DECREASE) {

					if (vx > 0) {
						go_direct = 1;
					}
					else {
						go_direct = -1;
					}
					SetState(BOMB_STATE_SCROLLBAR_DE);
				}
			}
			else {

				if (vx > 0)
					SetState(BOMB_STATE_WALKING_RIGHT);
				else
					SetState(BOMB_STATE_WALKING_LEFT);
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

		if (r1 - BOMB_JUMP_ALIGN > max && vx > 0 || l1 + BOMB_JUMP_ALIGN < min && vx < 0) {

			Jumping();
		}

		if (abs(CGimmick::GetInstance(0, 0)->GetX() - x) >= BOMB_MAX_DISTANCE_WITH_GIMMICK) {
			if (GetState() == BOMB_STATE_DAMAGED && CGimmick::GetInstance(0, 0)->GetX() > x)
				SetState(BOMB_STATE_WALKING_RIGHT);
			if (GetState() == BOMB_STATE_DAMAGED && CGimmick::GetInstance(0, 0)->GetX() < x)
				SetState(BOMB_STATE_WALKING_LEFT);

			if (GetState() == BOMB_STATE_WALKING_LEFT && CGimmick::GetInstance(0, 0)->GetX() > x)
				SetState(BOMB_STATE_WALKING_RIGHT);

			if (GetState() == BOMB_STATE_WALKING_RIGHT && CGimmick::GetInstance(0, 0)->GetX() < x)
				SetState(BOMB_STATE_WALKING_LEFT);
		}

		if (nx != 0 && ny == 0) {

			if ((x < CGimmick::GetInstance(0, 0)->GetX() && vx < 0)
				|| (x > CGimmick::GetInstance(0, 0)->GetX() && vx > 0)) {

				if (GetState() == BOMB_STATE_WALKING_LEFT) {

					SetState(BOMB_STATE_WALKING_RIGHT);
				}
				else {

					SetState(BOMB_STATE_WALKING_LEFT);
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

void CGreenFattie::Render()
{
	int state = GetState();

	if (state == BOMB_STATE_WALKING_RIGHT)
		animation_set->at(0)->Render(x, y - 1);

	else if (state == BOMB_STATE_WALKING_LEFT)
		animation_set->at(1)->Render(x, y - 1);

	else if (state == BOMB_STATE_FLY_RIGHT)
		animation_set->at(2)->Render(x, y);

	else if (state == BOMB_STATE_FLY_LEFT)
		animation_set->at(3)->Render(x, y);

	else if (state == BOMB_STATE_DIE)
		animation_set->at(4)->Render(x, y);
	else if (state == BOMB_STATE_DAMAGED)
	{
		animation_set->at(5)->Render(x, y);
	}
	else if (vx > 0)
		animation_set->at(0)->Render(x, y);
	else
		animation_set->at(1)->Render(x, y);
}

void CGreenFattie::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isFinish) {
		left = x;
		top = y;
		right = x + FATTIE_BBOX_WIDTH;
		bottom = y - FATTIE_BBOX_HEIGHT;
	}
}

void CGreenFattie::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state) {

	case BOMB_STATE_WALKING_RIGHT:
		vx = FATTIE_SPEED_X;
		break;

	case BOMB_STATE_WALKING_LEFT:
		vx = -FATTIE_SPEED_X;
		break;
	case BOMB_STATE_SCROLLBAR_IN:
	{
		if (go_direct == 1)
			vx = 0.075f;
		else if (go_direct == -1)
			vx = -0.025f;
	}
	break;

	case BOMB_STATE_SCROLLBAR_DE:
	{
		if (go_direct == 1)
			vx = 0.025f;
		else if (go_direct == -1)
			vx = -0.075f;
	}
	break;

	case BOMB_STATE_SLIDE_UP:
		break;
	case BOMB_STATE_SLIDE_DOWN:
		break;
	case BOMB_STATE_FLY_RIGHT:
		break;

	case BOMB_STATE_FLY_LEFT:
		break;
	case BOMB_STATE_DAMAGED:
		vx *= -1;
		vy = FATTIE_SPEED_Y_DAMAGED;
		break;

	case BOMB_STATE_DIE:
		vy = FATTIE_SPEED_Y_NORMAL;
		vx *= -1;
		isFinish = true;

		break;
	}
}