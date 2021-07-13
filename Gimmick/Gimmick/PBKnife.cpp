#include "PBKnife.h"
#include "Brick.h"
#include "Slide.h"
#include "Gimmick.h"
#include "ScrollBar.h"
#include "Water.h"
#include "Sound.h"

CPBKnife::CPBKnife(float _x, float _y, int _index)
{
	x = _x;
	y = _y;

	index = _index;

	backupX = _x;
	backupY = _y;

	vx = 0;
	vy = 0;

	isFinish = false;

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(228);

	this->SetAnimationSet(ani_set);
}

CPBKnife::~CPBKnife()
{
}

void CPBKnife::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt);

	vy += BOMB_GRAVITY * dt;

	vector<LPGAMEOBJECT> Bricks;
	Bricks.clear();

	for (UINT i = 0; i < coObjects->size(); i++) {

		if (dynamic_cast<CBrick*>(coObjects->at(i))
			|| dynamic_cast<CScrollBar*>(coObjects->at(i))
			|| dynamic_cast<CSlide*>(coObjects->at(i))
			|| dynamic_cast<CWater*>(coObjects->at(i))) {

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

		x += dx;
		y += min_ty * dy + ny * 0.04f;

		for (UINT i = 0; i < coEventsResult.size(); i++) {

			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj)) {

				vx = vy = 0;
				isFinish = true;
				ending = 1;
			}
		}
		if (nx != 0 && ny == 0)
			vx *= -1;

		if (ny != 0) {
			vy = 0;
		}
	}

}

void CPBKnife::Render()
{
	if (!isFinish)
		animation_set->at(0)->Render(x, y - 1);
	else if (ending)
		animation_set->at(1)->Render(x, y - 1);

}

void CPBKnife::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + 1;
	top = y;
	right = x + 12;
	bottom = y - 24;
}