#include "Shadow.h"
#include "Bomb.h"
#include "Brick.h"
#include "KingElectrode.h"
#include "Map.h"

CShadow::CShadow(float _x, float _y)
{
	x = _x;
	y = _y;

	vx = 0;
	vy = 0;

	backupX = x;
	backupY = y;

	isFinish = false;

	isCloak = true;
	live = SHADOW_CLOAK_LIVE;

	isLanky = false;
	isNinja = false;
	isAttack = false;
	isHurt = false;

	wall = new CWindWall(x, WALL_POS_Y_FIXED);
	wall->vx = -WALL_SPEED_X;

	CMap::GetInstance()->ListObjects.push_back(wall);

	for (int i = 0; i < BALL_NUMBER; i++) {

		CWhiteBall* ball = new CWhiteBall(x, y);

		ListBall.push_back(ball);

		CMap::GetInstance()->ListObjects.push_back(ball);
	}
}

CShadow::~CShadow()
{
}

void CShadow::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isFinish) {
		left = x;
		top = y;
		right = x + 40;
		bottom = y - 68;
	}
}

void CShadow::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (x >= SHADOW_POS_MAX && isLanky && !isHurt) {

		x = SHADOW_POS_MAX;

		isLanky = false;
		isNinja = true;

		StartCrazy();
		vx = 0;
	}

	if (crazy == 1) {

		if (GetTickCount() - time_crazy > SHADOW_CRAZY_TIME) {

			time_crazy = 0;
			crazy = 0;

			isNinja = false;
			isAttack = true;

			StartAttack();

			y += 16;
		}
	}

	if (attack == 1) {

		if (GetTickCount() - time_attack > SHADOW_ATTACK_TIME) {

			time_attack = 0;
			attack = 0;

			isAttack = false;
			isLanky = true;

			vx = -SHADOW_SPEED_X;
			vy = 0;

			StartLanky();
		}
		else if (GetTickCount() - time_attack > SHADOW_ATTACK_TIME / 2) {

			//vx = 0;
			vy = -SHADOW_SPEED_Y;
		}
		else {
			vx = -SHADOW_SPEED_X;
			vy = SHADOW_SPEED_Y;
		}
	}

	if (lanky == 1) {

		if (GetTickCount() - time_lanky > SHADOW_LANKY_TIME) {

			time_lanky = 0;
			lanky = 0;

			vx = SHADOW_SPEED_X;
		}
	}

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

		//if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}


	if (wall->x < SHADOW_POS_MIN + 10 && wall->vx < 0 && isCloak) {

		x = SHADOW_POS_MIN;

		wall->vx *= -1;
		wall->BackUpPos(x, WALL_POS_Y_FIXED);
	}
	else if (wall->x >= SHADOW_POS_MAX + 16 && wall->vx > 0 && isCloak) {
		x = SHADOW_POS_MAX;

		wall->vx *= -1;
		wall->BackUpPos(x, WALL_POS_Y_FIXED);
	}
	//wall->Update(dt, coObjects);

	if (isLanky) {
		for (int i = 0; i < BALL_NUMBER; i++) {

			if (!ListBall[i]->isFinish) {

				ListBall[i]->vx = -BALL_SPEED_X * (BALL_NUMBER - i);
				ListBall[i]->vy = -BALL_SPEED_Y * (i + 1);

				ListBall[i]->isShot = true;
				//ListBall[i]->Update(dt, coObjects);
			}
			else {
				ListBall[i]->SetPosition(x, y);
				ListBall[i]->isFinish = false;
			}
		}
	}
}

void CShadow::Render()
{
	if (!isFinish) {

		/*wall->Render();*/

		if (isCloak) {

			animation_set->at(SHADOW_ANI_CLOAK)->Render(x, y);
		}
		else {

			/*for (int i = 0; i < BALL_NUMBER; i++)
				if (!ListBall[i]->isFinish)
					ListBall[i]->Render();*/

			if (isLanky)
				animation_set->at(SHADOW_ANI_LANKY_FELLOW)->Render(x, y);
			else if (isNinja)
				animation_set->at(SHADOW_ANI_CRAZY_NINJA)->Render(x, y);
			else if (isAttack)
				animation_set->at(SHADOW_ANI_ATTACK)->Render(x, y);
			else if (isHurt)
				animation_set->at(SHADOW_ANI_HURT)->Render(x, y);
		}
	}
}
