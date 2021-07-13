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

	vx = 0.05f;
	vy = 0;

	isFinish = false;
	isRolling = false;

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(10);

	this->SetAnimationSet(ani_set);
}

CPBKnife::~CPBKnife()
{
}

void CPBKnife::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (ending == 1) {

		isFinish = true;
		isRolling = false;

		SetSpeed(0, 0);

		if (GetTickCount() - time_end > 500) {

			ending = 0;
			time_end = 0;

			isFinish = false;

			SetPosition(backupX, backupY);
			SetSpeed(CANNONBALL_SPEED_X, 0);

		}
	}

	if (isRolling) {

		CGimmick* gimmick = CGimmick::GetInstance(0, 0);

		if (isCollisionWithObject(gimmick)) {

			if (gimmick->untouchable == 0)
			{
				if (GetState() != GIMMICK_STATE_DIE)
				{
					if (gimmick->energy > 0)
					{
						gimmick->energy -= 1;
						Sound::GetInstance()->Play("Collision", 0, 1);
						gimmick->StartUntouchable();
					}
					else
					{
						gimmick->SetState(GIMMICK_STATE_DIE);
					}
				}
			}
		}

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

void CPBKnife::Render()
{
	if (!isFinish)
		animation_set->at(0)->Render(x, y - 1);
	else if (ending)
		animation_set->at(1)->Render(x, y - 1);

}

void CPBKnife::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isFinish)
	{
		left = x + 1;
		top = y;
		right = x + 15;
		bottom = y - 15;
	}
}