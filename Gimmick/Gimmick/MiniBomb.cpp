#include "MiniBomb.h"
#include "Gimmick.h"
#include "Brick.h"
#include "Slide.h"

CMiniBomb::CMiniBomb()
{
	isFalling = false;
	isFinish = false;
}

CMiniBomb::~CMiniBomb()
{
}

void CMiniBomb::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isFalling) {

		vx = 0;
		vy = 0;
	}
	else {

		vy = -MINIBOMB_FALLING_SPEED;
	}

	if (ending == 1) {

		isFinish = true;
		isFalling = false;

		if (GetTickCount() - time_end > 500) {

			ending = 0;
			time_end = 0;
		}
	}

	CGimmick* gimmick = CGimmick::GetInstance(0, 0);

	if (abs(gimmick->GetX() - (x + 7)) <= 9 && gimmick->GetY() < y)
		if (!isFalling && !isFinish)
			isFalling = true;

	CGameObject::Update(dt);

	x += dx;
	y += dy;

	vector<LPGAMEOBJECT> Bricks;
	Bricks.clear();

	if (isFalling) {

		for (UINT i = 0; i < coObjects->size(); i++) {

			if (dynamic_cast<CBrick*>(coObjects->at(i))
				|| dynamic_cast<CScrollBar*>(coObjects->at(i))
				|| dynamic_cast<CSlide*>(coObjects->at(i))) {

				Bricks.push_back(coObjects->at(i));
			}
		}


		vector<LPCOLLISIONEVENT>  coEvents;
		vector<LPCOLLISIONEVENT>  coEventsResult;

		coEvents.clear();

		CalcPotentialCollisions(&Bricks, coEvents);

		if (coEvents.size() > 0) {

			StarEnding();
		}
	}
}

void CMiniBomb::Render()
{
	if (!isFinish)
		animation_set->at(0)->Render(x, y);
	else if (ending)
		animation_set->at(1)->Render(x, y);
}

void CMiniBomb::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isFinish) {

		left = x;
		top = y;
		right = x + MINIBOMB_BBOX_WIDTH;
		bottom = y - MINIBOMB_BBOX_HEIGHT;

	}
}
