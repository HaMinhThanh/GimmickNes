#include "PirateCannonBall.h"
#include "Brick.h"
#include "Slide.h"
#include "Gimmick.h"
#include "ScrollBar.h"
#include "Water.h"
#include "Sound.h"
#include "Define.h"

CPirateCannonBall::CPirateCannonBall(float _x, float _y, int _index)
{
	x = _x;
	y = _y;

	index = _index;

	backupX = _x;
	backupY = _y;

	vx = -PIRATE_CANNONBALL_SPEED_X;
	vy = 0;

	isFinish = false;
	isRolling = false;
	isMoving = true;

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(10);

	this->SetAnimationSet(ani_set);
}

CPirateCannonBall::~CPirateCannonBall()
{
}

void CPirateCannonBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	/*if (ending == 1) {

		isRolling = false;

		SetSpeed(0, 0);

		if (GetTickCount() - time_end > 500) {

			ending = 0;
			time_end = 0;

			isFinish = false;

			SetPosition(backupX, backupY);

			SetSpeed(PIRATE_CANNONBALL_SPEED_X, 0);

		}
	}*/


	float camx, camy;
	CCamera::GetInstance()->GetCamPos(camx, camy);
	if (x + 16 < camx || x + 16 > camx + SCREEN_WIDTH) {

		SetPosition(backupX, backupY);
	}

	//if (isRolling) {


	CGameObject::Update(dt);

	/*x += dx;
	y += dy;*/

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


			}
		}
		if (nx != 0 && ny == 0)
			vx *= -1;

		if (ny != 0) {
			vy = 0;
		}
	}
	
}

void CPirateCannonBall::Render()
{
	if (!isFinish)
		animation_set->at(0)->Render(x, y - 1);
	else if (ending)
		animation_set->at(1)->Render(x, y - 1);
}

void CPirateCannonBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isFinish)
	{
		left = x;
		top = y;
		right = x + 15;
		bottom = y - 15;
	}
}