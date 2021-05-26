#include "Star.h"
#include "Gimmick.h"
#include "PlayScene.h"
#include "Game.h"
#include "Camera.h"
#include "Define.h"
#include "Worm.h"
#include "KingElectrode.h"
#include "Electrode.h"

#define STAR_ANIMATION_SET		2


CStar::CStar()
{
	//SetState(STAR_STATE_ACTIVITY);

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(STAR_ANIMATION_SET);

	this->SetAnimationSet(ani_set);

	isFinish = false;
	isActive = false;
	isBubble = false;

	x = y = 0;

	vy = 0;
	vx = 0;
}

CStar::~CStar()
{
}

void CStar::Reset()
{
	time_acting = 0;
	acting = 0;

	isActive = false;
	isFinish = true;
	isBubble = false;
}

void CStar::Render()
{
	if (isFinish == true) return;

	if (isBubble)
		animation_set->at(1)->Render(x, y);		// star bubble in the end
	else 
		animation_set->at(0)->Render(x, y);		// normal

	//RenderBoundingBox();
}

void CStar::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case STAR_GOING_RIGHT:

		vx = STAR_SPEED_X;
		vy = STAR_SPEED_Y;

		if (acting == 0)
			StartActive();

		break;

	case STAR_GOING_LEFT:

		vx = -STAR_SPEED_X;
		vy = STAR_SPEED_Y;

		if (acting == 0)
			StartActive();

		break;

	case STAR_STATE_IDLE:

		vx = vy = 0;
		//isActive = false;

		break;
	}
}

void CStar::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isActive == false) {

		l = t = r = b = 0;
		return;
	}

	l = x;
	t = y;
	r = x + STAR_BBOX_WIDTH;
	b = y - STAR_BBOX_HEIGHT;
}

void CStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	

	if (isActive) {

		float camx, camy;
		CCamera::GetInstance()->GetCamPos(camx, camy);

		if (x< camx || x> camx + SCREEN_WIDTH || y< camy || y> camy + SCREEN_HEIGHT_MAP) {

			Reset();

		}

		CGameObject::Update(dt, coObjects);

		vy += STAR_GRAVITY * dt;

		if (acting == 1) {

			if (GetTickCount() - time_acting > STAR_BUBBLE_TIME) {
				
				time_acting = 0;
				acting = 0;

				isActive = false;
				isFinish = true;
				isBubble = false;
			}
			else if (GetTickCount() - time_acting > STAR_ACTING_TIME 
				&& GetTickCount() - time_acting < STAR_BUBBLE_TIME)
			{				
				isBubble = true;				
			}
		}

		if (isBubble) {

			SetState(STAR_STATE_IDLE);
		}

		vector<LPGAMEOBJECT> Bricks;
		Bricks.clear();

		for (UINT i = 0; i < coObjects->size(); i++)
			if (dynamic_cast<CBrick*>(coObjects->at(i))
				|| dynamic_cast<CScrollBar*>(coObjects->at(i))
				|| dynamic_cast<CBomb*>(coObjects->at(i))
				|| dynamic_cast<CKingElectrode*>(coObjects->at(i))
				|| dynamic_cast<CElectrode*>(coObjects->at(i))
				|| dynamic_cast<CWorm*>(coObjects->at(i))) {

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

				if (dynamic_cast<CBomb*>(e->obj)) {

					if (e->t > 0 && e->t <= 1) {

						CBomb* bomb = dynamic_cast<CBomb*>(e->obj);
						bomb->SetState(BOMB_STATE_DIE);

						CGimmick::GetInstance(0, 0)->score += 100;

						nx = ny = 0;
					}
				}

				if (dynamic_cast<CElectrode*>(e->obj)) {

					if (e->t > 0 && e->t <= 1) {

						CElectrode* elec = dynamic_cast<CElectrode*>(e->obj);
						
						if (elec->isIdle) {
							elec->isFinish = true;
							CGimmick::GetInstance(0, 0)->score += 100;
						}
						else
							Reset();

						nx = ny = 0;
					}
				}
				else if (dynamic_cast<CWorm*>(e->obj)) {

					if (e->t > 0 && e->t <= 1) {

						CWorm* worm = dynamic_cast<CWorm*>(e->obj);

						worm->isFinish = true;
						CGimmick::GetInstance(0, 0)->score += 100;

						Reset();
					}
				}

				if (dynamic_cast<CKingElectrode*>(e->obj)) {

					if (e->t > 0 && e->t <= 1) {

						CKingElectrode* king = dynamic_cast<CKingElectrode*>(e->obj);

						king->live -= 1;
						CGimmick::GetInstance(0, 0)->score += 100;

						if(king->live<=0)
							CGimmick::GetInstance(0, 0)->score += 1000;

						Reset();
					}
				}
			}

			x += min_tx * dx + nx * 0.04f;
			y += min_ty * dy + ny * 0.04f;

			if (nx != 0 && ny == 0) vx *= STAR_SPEED_AFTER_COLLISION;
			if (ny != 0) {

				vy *= STAR_SPEED_AFTER_COLLISION;
			}

			//vy *= -1;

		//if (vy < -FIREBALL_SPEED_MAX_Y) vy = -FIREBALL_SPEED_MAX_Y;

		}
		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
	}
}