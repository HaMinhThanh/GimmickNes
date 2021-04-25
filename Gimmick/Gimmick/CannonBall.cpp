#include "CannonBall.h"
#include "Brick.h"
#include "Slide.h"
#include "Gimmick.h"
#include "ScrollBar.h"
#include "Water.h"

CCannonBall::CCannonBall(float _x, float _y, int _index)
{
	x = _x;
	y = _y;
	index = _index;

	vx = 0.05f;
	vy = 0;

	isFinish = false;
	isRolling = false;

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(10);

	this->SetAnimationSet(ani_set);
}

CCannonBall::~CCannonBall()
{
}

void CCannonBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (ending == 1) {

		isFinish = true;

		if (GetTickCount() - time_end > 500) {

			ending = 0;
			time_end = 0;

			isRolling = false;
			isFinish = false;
		}
	}

	if (isRolling) {

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

				if (dynamic_cast<CWater*>(e->obj)) {

					StarEnding();
				}
				if (dynamic_cast<CSlide*>(e->obj)) {

					CSlide* slide = dynamic_cast<CSlide*>(e->obj);

					/*if (slide->direct == 1)
						vx = CANNONBALL_SPEED_X;
					else
						vx = -CANNONBALL_SPEED_X;*/
				}
			}
			if (nx != 0 && ny == 0)
				vx *= -1;

			if (ny != 0) {
				vy = 0;
			}
		}
	}
}

void CCannonBall::Render()
{
	if (isRolling) {

		if (!isFinish)
			animation_set->at(0)->Render(x, y);
		else if (ending)
			animation_set->at(1)->Render(x, y);
	}
}

void CCannonBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isFinish)
	{
		left = x + 1;
		top = y;
		right = x + 15;
		bottom = y + 15;
	}
}
