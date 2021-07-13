#include "Cannon.h"
#include "Bomb.h"
#include "Brick.h"
#include "ScrollBar.h"
#include "Slide.h"
#include "Water.h"
#include "Gimmick.h"
#include "CannonBall.h"
#include "Map.h"


CPirateCannonBall* pirate_ball = NULL;
CCannon::CCannon(float _x, float _y, int _n)
{
	x = _x;
	y = _y;

	backupX = _x;
	backupY = _y;

	num_ball = _n;

	for (int i = 0; i < num_ball; i++) {

		LPGAMEOBJECT obj = NULL;
		obj = new CCannonBall(x, y, i);
		ListBall.push_back(obj);
	}
}


CCannon::CCannon(float _x, float _y, int ani_id, int _n)
{
	x = _x;
	y = _y;

	render = ani_id;

	backupX = _x;
	backupY = _y;

	num_ball = _n;

	if (render == CANNON_TYPE_PIRATE_BALL) // pirate cannon
	{
		pirate_ball = new CPirateCannonBall(x, y, 1);
		LPGAMEOBJECT obj = pirate_ball;

		//ListBall.push_back(obj);

		CMap::GetInstance()->ListObjects.push_back(obj);
	}
	else
	{
		for (int i = 0; i < num_ball; i++) {
			LPGAMEOBJECT obj = NULL;
			obj = new CCannonBall(x, y, i);

			ListBall.push_back(obj);
		}
	}
}

CCannon::~CCannon()
{
}

void CCannon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (render == CANNON_TYPE_PIRATE_BALL) {

		pirate_ball->BackUpPos(x, y);
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
		y += min_ty * dy + ny * 0.01f;

		for (UINT i = 0; i < coEventsResult.size(); i++) {

			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CSlide*>(e->obj)) {

				CSlide* slide = dynamic_cast<CSlide*>(e->obj);

				isSlide = true;

				if (slide->direct == 1)
					vx = -CANNON_MOVING_SPEED;
				else
					vx = CANNON_MOVING_SPEED;
			}
			else {

				isSlide = false;
				vx = 0;
			}
		}

		if (ny != 0) {

			vy = 0;
		}

		if (nx != 0)
			vx *= -1;
	}

	CGimmick* gm = CGimmick::GetInstance(0, 0);

	if (isMoving && gm->isPushCannon) {

		isMoving = false;

		if (gm->vx > 0)
			vx = CANNON_MOVING_SPEED;
		else if (gm->vx < 0)
			vx = -CANNON_MOVING_SPEED;
	}
	else if (!isSlide)
		vx = 0;

	if (render != CANNON_TYPE_PIRATE_BALL) {
		CCannonBall* cb = (CCannonBall*)ListBall.at(current_ball);

		if (cb->isFinish) {

			current_ball += 1;
			cb->ReturnPosition(x + 16, y);
		}

		if (current_ball >= ListBall.size() - 1)
			current_ball = 0;

		CCannonBall* cb1 = (CCannonBall*)ListBall.at(current_ball);

		if (!cb1->isRolling) {

			cb1->vx = CANNONBALL_SPEED_X;
			cb1->isRolling = true;
		}
		cb1->Update(dt, coObjects);
	}
}

void CCannon::Render()
{
	animation_set->at(0)->Render(x, (int)y);

	if (render != CANNON_TYPE_PIRATE_BALL)
		ListBall.at(current_ball)->Render();
}

void CCannon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (render == CANNON_TYPE_PIRATE_BALL)	// pirate cannon
	{
		left = x;
		top = y;
		right = x + PIRATE_CANNON_BBOX_WIDTH;
		bottom = y - PIRATE_CANNON_BBOX_HEIGHT;
	}
	else
	{
		left = x;
		top = y;
		right = x + CANNON_BBOX_WIDTH - 1;
		bottom = y - CANNON_BBOX_HEIGHT;
	}
}