#include "Electrode.h"
#include "Gimmick.h"
#include "Brick.h"

CElectrode::CElectrode(float _x, float _y)
{
	x = _x;
	y = _y;

	vx = 0;
	vy = 0;

	backupX = _x;
	backupY = _y;
}

CElectrode::~CElectrode()
{
}

void CElectrode::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isFinish) {
		left = x;
		top = y;
		right = x + ELECTRODE_BBOX_WIDTH;

		if (vx != 0)
			bottom = y - ELECTRODE_BBOX_HEIGHT;
		else
			bottom = y - 15;
	}
}

void CElectrode::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (abs(x - CGimmick::GetInstance(0, 0)->GetX()) < 8 && !isActive) {

		isActive = true;
		vx = ELECTRODE_SPEED_X;
	}

	if (((x > CGimmick::GetInstance(0, 0)->GetX() && x - CGimmick::GetInstance(0, 0)->GetX() > 64 && vx > 0)
		|| (x < CGimmick::GetInstance(0, 0)->GetX() && CGimmick::GetInstance(0, 0)->GetX() - x > 64 && vx<0))
		&& isActive) {

		vx *= -1;
	}

	if (isIdle) {

		vx = 0;

		if (CGimmick::GetInstance(0, 0)->GetState() != GIMMICK_STATE_IDLE) {
			isIdle = false;
			vx = ELECTRODE_SPEED_X;
			y += 6;
		}
	}

	if (isDie) {
		isDie = false;
		vy = -ELECTRODE_SPEED_Y;
	}

	CGameObject::Update(dt);

	if (isActive || isIdle)
		vy += ELECTRODE_GRAVITY;

	vector<LPGAMEOBJECT> Bricks;
	Bricks.clear();

	for (UINT i = 0; i < coObjects->size(); i++)
		if (dynamic_cast<CBrick*>(coObjects->at(i))) {

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

		if (ny != 0)
			vy = 0;
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void CElectrode::Render()
{
	if (!isFinish) {

		if (vx == 0) {

			if (nx > 0)
				animation_set->at(0)->Render(x, y);
			else
				animation_set->at(1)->Render(x, y);
		}
		else if (vx > 0)
			animation_set->at(2)->Render(x, y);
		else
			animation_set->at(3)->Render(x, y);
	}
	else
		animation_set->at(4)->Render(x, y);
}
