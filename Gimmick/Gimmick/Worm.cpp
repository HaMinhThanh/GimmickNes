#include "Worm.h"
#include "Bomb.h"
#include "Brick.h"

CWorm::CWorm(float _x, float _y)
{
	x = _x;
	y = _y;

	vx = WORM_SPEED_X;
	vy = 0;

	isFinish = false;
}

CWorm::~CWorm()
{
}

void CWorm::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isFinish) {

		left = x;
		top = y;
		right = x + WORM_BBOX_WIDTH;
		bottom = y - WORM_BBOX_HEIGHT;
	}
}

void CWorm::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	vy += BOMB_GRAVITY * dt;

	vector<LPGAMEOBJECT> Bricks;
	Bricks.clear();

	for (UINT i = 0; i < coObjects->size(); i++) {

		if (dynamic_cast<CBrick*>(coObjects->at(i))) {

			Bricks.push_back(coObjects->at(i));
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

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += dx /*+ nx * 0.04f*/;
		y += min_ty * dy + ny * 0.04f;

		if (ny != 0)vy = 0;
	}

	if (!isFinish) {
		if (x <= MIN_POS_X || x + WORM_BBOX_WIDTH >= MAX_POS_X)
			vx *= -1;
	}
	else {

		vy = -WORM_SPEED_Y;
	}
}

void CWorm::Render()
{
	if (isFinish)
		animation_set->at(2)->Render(x, y);
	else {

		if (vx > 0)
			animation_set->at(0)->Render(x, y);
		else
			animation_set->at(1)->Render(x, y);
	}
}
