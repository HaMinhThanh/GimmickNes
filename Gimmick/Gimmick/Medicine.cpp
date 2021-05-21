#include "Medicine.h"
#include "Brick.h"
#include "ScrollBar.h"
#include "Slide.h"

CMedicine::CMedicine(float _x, float _y, int _type)
{
	x = _x;
	y = _y;
	type = _type;
}

CMedicine::~CMedicine()
{
}

void CMedicine::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isFinish) {

		left = x;
		top = y;
		right = x + MEDICINE_BBOX_WIDTH;
		bottom = y + MEDICINE_BBOX_HEIGHT;
	}
}

void CMedicine::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isFinish)
		return;

	CGameObject::Update(dt, coObjects);

	vy += ITEM_GRAVITY * dt;

	vector<LPGAMEOBJECT> Bricks;
	Bricks.clear();

	for (UINT i = 0; i < coObjects->size(); i++)
		if (dynamic_cast<CBrick*>(coObjects->at(i))
			|| dynamic_cast<CScrollBar*>(coObjects->at(i))
			|| dynamic_cast<CSlide*>(coObjects->at(i))) {

			Bricks.push_back(coObjects->at(i));
		}

	vector<LPCOLLISIONEVENT>  coEvents;
	vector<LPCOLLISIONEVENT>  coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(&Bricks, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx, rdy;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		for (UINT i = 0; i < coEventsResult.size(); i++) {

			LPCOLLISIONEVENT e = coEventsResult[i];

		}

		x += min_tx * dx + nx * 0.04f;
		y += min_ty * dy + ny * 0.04f;

		if (ny != 0) {
			vy = 0;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void CMedicine::Render()
{
	if (!isFinish) {
		if (type == 1)
			CSprites::GetInstance()->Get(MEDICINE_SPRITE_1)->Draw(x, y);
		else
			CSprites::GetInstance()->Get(MEDICINE_SPRITE_2)->Draw(x, y);
	}
}
