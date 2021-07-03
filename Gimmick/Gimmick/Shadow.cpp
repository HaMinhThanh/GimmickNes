#include "Shadow.h"
#include "Bomb.h"
#include "Brick.h"
#include "KingElectrode.h"

CShadow::CShadow(float _x, float _y)
{
	x = _x;
	y = _y;

	backupX = x;
	backupY = y;

	isFinish = false;

	wall = new CWindWall(x, WALL_POS_Y_FIXED);
	wall->vx = -0.05f;

	for (int i = 0; i < BALL_NUMBER; i++) {

		CWhiteBall* ball = new CWhiteBall(x, y);

		ListBall.push_back(ball);
	}
}

CShadow::~CShadow()
{
}

void CShadow::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 40;
	bottom = y - 70;
}

void CShadow::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

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

		float max = 0, min = 999999999;

		float l, t, r, b;
		float l1, t1, r1, b1;
		GetBoundingBox(l1, t1, r1, b1);

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.04f;
		y += min_ty * dy + ny * 0.04f;

		for (UINT i = 0; i < coEventsResult.size(); i++) {

			LPCOLLISIONEVENT e = coEventsResult[i];


		}
	}


	wall->Update(dt, coObjects);

	for (int i = 0; i < BALL_NUMBER; i++) {

		if (!ListBall[i]->isFinish) {

			ListBall[i]->vx = -BOMB_SPEED_VX * (BALL_NUMBER - i);
			ListBall[i]->vy = -BOMB_SPEED_VY * (i + 1);

			ListBall[i]->Update(dt, coObjects);
		}
		else {
			ListBall[i]->SetPosition(x , y);
			ListBall[i]->isFinish = false;
		}
	}
}

void CShadow::Render()
{
	wall->Render();

	for (int i = 0; i < BALL_NUMBER; i++)
		if (!ListBall[i]->isFinish)
			ListBall[i]->Render();

	animation_set->at(0)->Render(x, y);
}