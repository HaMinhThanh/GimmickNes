#include "MovingBrick.h"

CMovingBrick::CMovingBrick(int _min, int _max, int _direct)
{
	max = _max;
	min = _min;
	direct = _direct;

	if (direct == 1) {
		vx = MOVING_BRICK_SPEED_X;
		vy = 0;
	}
	else {
		vx = 0;
		vy = MOVING_BRICK_SPEED_Y;
	}
}

CMovingBrick::~CMovingBrick()
{
}

void CMovingBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + MOVINGBRICK_BBOX_WIDTH;
	bottom = y - MOVINGBRICK_BBOX_HEIGHT;
}

void CMovingBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	x += dx;
	y += dy;

	if (direct == 1) {
		if ((x <= min && vx < 0) || (x >= max && vx > 0))
			vx *= -1.0f;
		vy = 0;
	}
	else {
		if ((y <= min && vy < 0) || (y >= max && vy > 0))
			vy *= -1.0f;
		vx = 0;
	}
}

void CMovingBrick::Render()
{
	animation_set->at(0)->Render(x, y);
}
