#include "Star.h"
#include "Gimmick.h"
#include "PlayScene.h"
#include "Game.h"
#include "Camera.h"
#include "Define.h"
#include "Worm.h"
#include "KingElectrode.h"
#include "Electrode.h"
#include "Slide.h"
#include "Shadow.h"
#include "BombItem.h"
#include "Medicine.h"
#include "Fireball.h"

#include "GreenTurtle.h"
#include "GreenFattie.h"
#include "BossPirate.h"

#define STAR_ANIMATION_SET		2

CStar::CStar()
{
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
			if (dynamic_cast<CBossPirate*>(coObjects->at(i))
				||dynamic_cast<CBrick*>(coObjects->at(i))
				|| dynamic_cast<CScrollBar*>(coObjects->at(i))
				|| dynamic_cast<CSlide*>(coObjects->at(i))
				|| dynamic_cast<CBomb*>(coObjects->at(i))
				|| dynamic_cast<CGreenFattie*>(coObjects->at(i))
				|| dynamic_cast<CKingElectrode*>(coObjects->at(i))
				|| dynamic_cast<CElectrode*>(coObjects->at(i))
				|| dynamic_cast<CWorm*>(coObjects->at(i))
				|| dynamic_cast<CGreenTurtle*>(coObjects->at(i))
				|| dynamic_cast<CShadow*>(coObjects->at(i))) {

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

						switch (bomb->item) {

						case BOMB_ITEM_NON:
							break;

						case BOMB_ITEM_BOMB:
						{
							CBombItem* item = new CBombItem(bomb->x, bomb->y + BOMB_BBOX_HEIGHT);
							item->SetPosition(bomb->x, bomb->y + BOMB_BBOX_HEIGHT);
							CMap::GetInstance()->quadTree->insertEntity(item);				
						}
						break;

						case BOMB_ITEM_MEDICINE:
						{
							CMedicine* item = new CMedicine(bomb->x, bomb->y + BOMB_BBOX_HEIGHT, MEDICINE_TYPE_1);
							item->SetPosition(bomb->x, bomb->y + BOMB_BBOX_HEIGHT);
							CMap::GetInstance()->quadTree->insertEntity(item);
						}
						break;

						case BOMB_ITEM_FIREBALL:
						{
							CFireBall* item = new CFireBall(bomb->x, bomb->y + BOMB_BBOX_HEIGHT);
							item->SetPosition(bomb->x, bomb->y + BOMB_BBOX_HEIGHT);
							CMap::GetInstance()->quadTree->insertEntity(item);
						}
						break;

						}

						CGimmick::GetInstance(0, 0)->score += 100;

						nx = ny = 0;
					}
				}

				if (dynamic_cast<CGreenFattie*>(e->obj)) {

					if (e->t > 0 && e->t <= 1) {

						CGreenFattie* fattie = dynamic_cast<CGreenFattie*>(e->obj);
						if (fattie->damaged < 3)
						{
							fattie->damaged++;							
							fattie->SetState(BOMB_STATE_DAMAGED);
						}
						else
						{
							fattie->SetState(BOMB_STATE_DIE);

							switch (fattie->item) {

							case BOMB_ITEM_NON:
								break;

							case BOMB_ITEM_BOMB:
							{
								CBombItem* item = new CBombItem(fattie->x, fattie->y + BOMB_BBOX_HEIGHT);
								item->SetPosition(fattie->x, fattie->y + BOMB_BBOX_HEIGHT);
								CMap::GetInstance()->quadTree->insertEntity(item);
							}
							break;

							case BOMB_ITEM_MEDICINE:
							{
								CMedicine* item = new CMedicine(fattie->x, fattie->y + BOMB_BBOX_HEIGHT, MEDICINE_TYPE_1);
								item->SetPosition(fattie->x, fattie->y + BOMB_BBOX_HEIGHT);
								CMap::GetInstance()->quadTree->insertEntity(item);
							}
							break;

							case BOMB_ITEM_FIREBALL:
							{
								CFireBall* item = new CFireBall(fattie->x, fattie->y + BOMB_BBOX_HEIGHT);
								item->SetPosition(fattie->x, fattie->y + BOMB_BBOX_HEIGHT);
								CMap::GetInstance()->quadTree->insertEntity(item);
							}
							break;

							}
						}
						CGimmick::GetInstance(0, 0)->score += 100;

						nx = ny = 0;
					}
				}


				if (dynamic_cast<CBossPirate*>(e->obj)) {

					if (e->t > 0 && e->t <= 1) {

						CBossPirate* pboss = dynamic_cast<CBossPirate*>(e->obj);
						if (pboss->damaged < 5)
						{
							pboss->damaged++;
							pboss->SetState(BOMB_STATE_DAMAGED);
						}
						else
						{
							pboss->SetState(BOMB_STATE_DIE);

							switch (pboss->item) {

							case BOMB_ITEM_NON:
								break;

							case BOMB_ITEM_BOMB:
							{
								CBombItem* item = new CBombItem(pboss->x, pboss->y + BOMB_BBOX_HEIGHT);
								item->SetPosition(pboss->x, pboss->y + BOMB_BBOX_HEIGHT);
								CMap::GetInstance()->quadTree->insertEntity(item);
							}
							break;

							case BOMB_ITEM_MEDICINE:
							{
								CMedicine* item = new CMedicine(pboss->x, pboss->y + BOMB_BBOX_HEIGHT, MEDICINE_TYPE_1);
								item->SetPosition(pboss->x, pboss->y + BOMB_BBOX_HEIGHT);
								CMap::GetInstance()->quadTree->insertEntity(item);
							}
							break;

							case BOMB_ITEM_FIREBALL:
							{
								CFireBall* item = new CFireBall(pboss->x, pboss->y + BOMB_BBOX_HEIGHT);
								item->SetPosition(pboss->x, pboss->y + BOMB_BBOX_HEIGHT);
								CMap::GetInstance()->quadTree->insertEntity(item);
							}
							break;

							}
						}
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
				else if (dynamic_cast<CGreenTurtle*>(e->obj)) {

					if (e->t > 0 && e->t <= 1) {

						CGreenTurtle* turtle = dynamic_cast<CGreenTurtle*>(e->obj);

						turtle->isFinish = true;
						CGimmick::GetInstance(0, 0)->score += 100;

						Reset();
					}
				}

				else if (dynamic_cast<CKingElectrode*>(e->obj)) {

					if (e->t > 0 && e->t <= 1) {

						CKingElectrode* king = dynamic_cast<CKingElectrode*>(e->obj);

						king->live -= 1;
						CGimmick::GetInstance(0, 0)->score += 100;

						if (king->live <= 0)
							CGimmick::GetInstance(0, 0)->score += 1000;

						Reset();
					}
				}
				else if (dynamic_cast<CShadow*>(e->obj)) {

					if (e->t > 0 && e->t <= 1) {

						CShadow* shadow = dynamic_cast<CShadow*>(e->obj);

						shadow->live -= 1;
						CGimmick::GetInstance(0, 0)->score += 200;

						if (shadow->live <= 0) {
							if (shadow->isCloak) {
								shadow->isCloak = false;
								shadow->isLanky = true;
								shadow->x = SHADOW_POS_MAX;
								shadow->wall->vx = -WALL_SPEED_X;
								shadow->wall->BackUpPos(SHADOW_POS_MAX, WALL_POS_Y_FIXED);
								shadow->live = SHADOW_NINJA_LIVE;
							}
							else {
								shadow->isFinish = true;
								CGimmick::GetInstance(0, 0)->score += 10000;
							}
						}

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