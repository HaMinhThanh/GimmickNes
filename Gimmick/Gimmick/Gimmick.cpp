#include "Gimmick.h"
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Gimmick.h"
#include "Game.h"

#include "Portal.h"
#include "Bomb.h"
#include "Slide.h"
#include "Brick.h"
#include "HiddenObject.h"
#include "Pipes.h"
#include "MiniBomb.h"
#include "NarrowSpot.h"
#include "Electrode.h"
#include "KingElectrode.h"
#include "Cannon.h"
#include "CannonBall.h"
#include "Water.h"
#include "Worm.h"
#include "Sound.h"
#include "Medicine.h"
#include "BombItem.h"
#include "Fireball.h"
#include "Treasures.h"

CGimmick* CGimmick::_instance = NULL;

CGimmick* CGimmick::GetInstance(float x, float y)
{
	if (_instance == NULL)
		_instance = new CGimmick(x, y);

	return _instance;
}

CGimmick::CGimmick(float x, float y) : CGameObject()
{
	untouchable = 0;
	SetState(GIMMICK_STATE_IDLE);

	star = new CStar();

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;

	backupX = x;
	backupY = y;

	score = 0;
	rest = 7;
	energy = 3;
	item = 0;
}

void CGimmick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetState() != GIMMICK_STATE_IDLE) {

		isFollow = false;
	}

	if (isFollow) {

		FollowObject(obj);
	}
	else {
		obj = NULL;
	}

	if (GetState() == GIMMICK_STATE_DIE && waitToReset == 0) {

		StartReset();
		SetAniDie();
	}

	if (waitToReset == 1) {

		die_effect->Update(dt, coObjects);

		if (GetTickCount() - time_reset > GIMMICK_TIME_WAIT_RESET) {

			waitToReset = 0;
			time_reset = 0;

			Reset();

			if (rest <= 0)
				return;
		}
	}

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > GIMMiCK_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (jump == true && doubleJump_start != 0)
	{
		if (GetTickCount() - doubleJump_start > 100)
		{
			vy = GIMMICK_DOUBLE_JUMP_SPEED;
			doubleJump_start = 0;
		}
	}

	if (maxjumping == 1)
	{
		if (GetTickCount() - time_maxjumping >= 200)
		{
			maxjumping = 0;
			time_maxjumping = 0;
		}
	}
	else
	{
		maxjumping = 0;
		time_maxjumping = 0;
	}

	if (loading == 1) {

		if (GetTickCount() - time_load >= GIMMICK_TIME_LOADING_STAR) {

			loading = 2;
			time_load = 0;

			isCanShot = true;
		}
		else {

			load_star->TurnToBegin(x - LOADING_STAR_ALIGN, y - LOADING_STAR_ALIGN);
		}
	}

	if (isCanShot) {

		star->SetPosition(x, y + STAR_BBOX_HEIGHT - 4);
		star->isFinish = false;
	}

	if (star != NULL)
		star->Update(dt, coObjects);

	if (loading == 1)
		load_star->Update(dt, coObjects);

	if (!isSlide && !isFollow && !isPiping)
		vy += GIMMICK_GRAVITY * dt;

	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	//vy += GIMMICK_GRAVITY * dt;	

	vector<LPCOLLISIONEVENT>  coEvents;
	vector<LPCOLLISIONEVENT>  coEventsResult;

	coEvents.clear();

	coObjects->push_back(star);

	CalcPotentialCollisions(coObjects, coEvents);

	float min_tx, min_ty, nx = 0, ny;
	float rdx = 0;
	float rdy = 0;

	// No collision occured, proceed normally
	if (coEvents.size() == 0 && !isFollow)
	{
		x += dx;
		y += dy;

		isSlide = false;
		//isScrollBar = false;
	}
	else
	{


		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		//mario touches ground
		if (ny != 0 && nx == 0)
		{
			if (GetJumping() == 1)
			{
				jump = 0;
				doubleJump_start = 0;

			}

			//CanFall = 0;
		}

		if (nx != 0 && ny == 0) {
			SetState(GIMMICK_STATE_IDLE);
		}

		//
		// Collision logic with other objects
		//		

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBomb*>(e->obj) && !isSlide) {

				CBomb* bomb = dynamic_cast<CBomb*>(e->obj);

				if (e->t > 0 && e->t <= 1 && bomb->GetState() != BOMB_STATE_DIE) {

					if (e->ny > 0)
					{
						//if (vx==0 && vy==0) {							
						isFollow = true;
						obj = bomb;
						SetState(GIMMICK_STATE_IDLE);

						//}
					}
					else //if (e->nx != 0)
					{
						//isNotCollide = true;
						isFollow = false;
						isGoThrough = true;

						if (untouchable == 0)
						{
							if (GetState() != GIMMICK_STATE_DIE)
							{
								if (energy > 0)
								{
									Sound::GetInstance()->Play("Collision", 0, 1);
									energy -= 1;
									StartUntouchable();

								}
								else
								{
									SetState(GIMMICK_STATE_DIE);
								}
							}
						}
					}
				}
			}

			if (dynamic_cast<CMiniBomb*>(e->obj)) {

				CMiniBomb* mn = dynamic_cast<CMiniBomb*>(e->obj);

				mn->StarEnding();

				isGoThrough = true;
				if (e->t > 0 && e->t <= 1) {

					if (untouchable == 0)
					{
						if (GetState() != GIMMICK_STATE_DIE)
						{
							if (energy > 0)
							{
								Sound::GetInstance()->Play("Collision", 0, 1);
								energy -= 1;
								StartUntouchable();
							}
							else
							{
								SetState(GIMMICK_STATE_DIE);
							}
						}
					}
				}
			}

			if (dynamic_cast<CKingElectrode*>(e->obj) || dynamic_cast<CWorm*>(e->obj) || dynamic_cast<CElectrode*>(e->obj)) {

				if (e->t > 0 && e->t <= 1) {

					if (e->ny > 0) {

						if (dynamic_cast<CElectrode*>(e->obj)) {

							CElectrode* elec = dynamic_cast<CElectrode*>(e->obj);

							elec->isIdle = true;

							/*isFollow = true;
							obj = elec;*/
						}
					}
					else {
						if (untouchable == 0)
						{
							if (GetState() != GIMMICK_STATE_DIE)
							{
								if (energy > 0)
								{
									Sound::GetInstance()->Play("Collision", 0, 1);
									energy -= 1;
									StartUntouchable();

								}
								else
								{
									SetState(GIMMICK_STATE_DIE);
								}
							}
						}
					}
				}
			}
			else {


			}

			if (dynamic_cast<CNarrowSpot*>(e->obj)) {

				CNarrowSpot* nr = dynamic_cast<CNarrowSpot*>(e->obj);

				if (nr->moving == 0)
					nr->StarMoving();

				if (nr->isMoving) {
					isAutoGo = true;
					addVx = NARROWSPOT_SPEED_X;
				}
				else {

					isAutoGo = false;
				}
			}
			else {

				isAutoGo = false;
			}

			if (dynamic_cast<CStar*>(e->obj)) {

				CStar* st = dynamic_cast<CStar*>(e->obj);

				if (e->t > 0 && e->t <= 1 && st->acting == 1) {

					if (e->ny > 0)
					{
						//if (vx==0 && vy==0) {							
						isFollow = true;
						obj = st;
						SetState(GIMMICK_STATE_IDLE);

						//}
					}
					else
					{
						isFollow = false;
						isGoThrough = true;
					}
				}
				else {

					isFollow = false;
				}
			}

			isScrollBar = false;
			if (dynamic_cast<CScrollBar*>(e->obj)) {

				/*if (isScrollBar)
					break;*/

				isScrollBar = true;

				CScrollBar* scrollbar = dynamic_cast<CScrollBar*>(e->obj);

				if (scrollbar->GetType() == SCROLLBAR_TYPE_INCREASE) {

					if (CGame::GetInstance()->IsKeyDown(DIK_RIGHT)) {

						addVx = SCROLLBAR_SPEED;
					}
					else if (CGame::GetInstance()->IsKeyDown(DIK_LEFT)) {

						addVx = -GIMMICK_AUTO_GO_SPEED;

						/*trendScrollBar = scrollbar->GetType();
						addVx = SCROLLBAR_SPEED;*/
					}
					else {
						addVx = GIMMICK_AUTO_GO_SPEED;
					}
				}
				else
				{
					if (CGame::GetInstance()->IsKeyDown(DIK_LEFT)) {

						addVx = -SCROLLBAR_SPEED;
					}
					else if (CGame::GetInstance()->IsKeyDown(DIK_RIGHT)) {

						addVx = GIMMICK_AUTO_GO_SPEED;

						/*trendScrollBar = scrollbar->GetType();
						addVx = SCROLLBAR_SPEED;*/
					}
					else {
						addVx = -GIMMICK_AUTO_GO_SPEED;
					}
				}
			}
			else {

				isScrollBar = false;
			}

			if (dynamic_cast<CSlide*>(e->obj)) {

				isSlide = true;

				float tran_y = 1;

				CSlide* slide = dynamic_cast<CSlide*>(e->obj);

				if (slide->size == 1)
					slide_size = 1;
				else
					slide_size = 2;

				if (( /*GetState() != GIMMICK_STATE_JUMP &&*/ CGame::GetInstance()->IsKeyDown(DIK_RIGHT))
					|| GetState() == GIMMICK_STATE_WALKING_RIGHT) {

					direct_go = 1;

					if (slide->direct == 1) {

						direct_slide = 1;

					}
					else {
						direct_slide = -1;
					}
				}
				else if (( /*GetState() != GIMMICK_STATE_JUMP &&*/ CGame::GetInstance()->IsKeyDown(DIK_LEFT))
					|| GetState() == GIMMICK_STATE_WALKING_LEFT) {

					direct_go = -1;

					if (slide->direct == 1) {

						direct_slide = 1;
					}
					else {
						direct_slide = -1;
					}
				}
				else /*if (GetState() != GIMMICK_STATE_JUMP)*/ {

					if (slide->direct == 1) {

						if (slide->size == 1) {

							slide_vx = -GIMMICK_SLIDE_DOWN_SPEED_X_1;
							slide_vy = -GIMMICK_SLIDE_DOWN_SPEED_Y_1;
						}
						else {

							slide_vx = -GIMMICK_SLIDE_DOWN_SPEED_X_2;
							slide_vy = -GIMMICK_SLIDE_DOWN_SPEED_Y_2;
						}
					}

					else {

						if (slide->size == 1) {

							slide_vx = GIMMICK_SLIDE_DOWN_SPEED_X_1;
							slide_vy = -GIMMICK_SLIDE_DOWN_SPEED_Y_1;
						}
						else {

							slide_vx = GIMMICK_SLIDE_DOWN_SPEED_X_2;
							slide_vy = -GIMMICK_SLIDE_DOWN_SPEED_Y_2;
						}
					}

				}

				if (slide->direct == 1) {

					tran_y = isOnTriangle(slide->x, slide->y - 1, slide->x + slide->size, slide->y, slide->x + slide->size, slide->y - 1, x, y);
					if (tran_y <= 0)
						y += 1.0f;			// discount y to fall through slide
				}
				else {

					tran_y = isOnTriangle(slide->x, slide->y, slide->x, slide->y - 1, slide->x + slide->size, slide->y - 1, x, y);
					if (tran_y <= 0)
						y += 1.0f;			// discount y to fall through slide
				}
			}
			else {
				isSlide = false;
			}

			if (dynamic_cast<CWater*>(e->obj)) {

				if (e->t > 0 && e->t <= 1) {

					SetState(GIMMICK_STATE_DIE);
				}
			}

			if (dynamic_cast<CPipes*>(e->obj)) {

				CPipes* pipe = dynamic_cast<CPipes*>(e->obj);

				isPiping = true;
				//isGoThrough = true;

				if (e->t > 0 && e->t <= 1) {

					if (pipe->type == PIPE_TYPE_HORIZONTAL) {

						if (vx > 0 || CGame::GetInstance()->IsKeyDown(DIK_RIGHT)) x += 0.1f;
						else if(vx > 0 && CGame::GetInstance()->IsKeyDown(DIK_LEFT))x -= 0.1f;
					}
					else if (pipe->type == PIPE_TYPE_VERTICAL) {

						x = pipe->x;

						if (vy > 0) y += 0.1f;
						else if (vy < 0)y -= 0.1f;
					}

				}

			}
			else {
				isPiping = false;
			}

			// collide with item
			if (dynamic_cast<CMedicine*>(e->obj)) {

				CMedicine* med = dynamic_cast<CMedicine*>(e->obj);

				if (e->t > 0 && e->t <= 1) {

					med->isFinish = true;

					if (med->type == 2) {

						energy = MAX_ENERGY;
					}
					else if (med->type == 1) {

						e->obj->isFinish = true;
						score += 200;

						item = MEDICINE_ITEM_INDEX;
						numItem += 1;

					}
				}
			}
			else if (dynamic_cast<CBombItem*>(e->obj)) {

				e->obj->isFinish = true;
				score += 200;

				item = BOMB_ITEM_INDEX;
				numItem += 1;

			}
			else if (dynamic_cast<CFireBall*>(e->obj)) {

				e->obj->isFinish = true;
				score += 200;

				item = FIREBALL_ITEM_INDEX;
				numItem += 1;

			}
			else if (dynamic_cast<CTreasures*>(e->obj)) {
				e->obj->isFinish = true;
				score += 2000;

			}

			if (dynamic_cast<CHiddenObject*>(e->obj)) {

				isGoThrough = true;

				CHiddenObject* hidden = dynamic_cast<CHiddenObject*>(e->obj);

				CCamera* camera = CCamera::GetInstance();

				camera->SetCamBoundary(hidden->cam_left, hidden->cam_right, camera->_yTop);
			}

			if (dynamic_cast<CPortal*>(e->obj)) {

				CPortal* p = dynamic_cast<CPortal*>(e->obj);

				if (e->t > 0 && e->t <= 1) {
					DebugOut(L"SceneId %d", p->scene_id);

					CGame::GetInstance()->isSwitchScene = true;
					//SetPosition(0,0);

					CCamera::GetInstance()->SetOldBound(p->oLeft, p->oRight);

					CGame::GetInstance()->SwitchScene(p->GetSceneId());

					return;
				}

			}
		}

		if (!isSlide && !isGoThrough && !isPiping) {

			x += min_tx * dx + nx * 0.4f;

			if (isNotCollide)
				isNotCollide = false;

			else
				y += min_ty * dy + ny * 0.4f;

			if (nx != 0 && !isScrollBar) vx = 0;
			if (ny != 0) vy = 0;
		}
		else {

			x += dx;

			if (isSlide) {
				y += min_ty * dy + ny * 0.4f;
			}
			else if (isGoThrough) {
				//y += dy;

				isGoThrough = false;
			}
			else if (isPiping) {

				y += dy;
			}

		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CGimmick::Render()
{
	int ani = -1;

	if (jump == 1)
	{
		if (nx > 0)
			ani = GIMMICK_ANI_JUMPING_RIGHT;
		else
			ani = GIMMICK_ANI_JUMPING_LEFT;
	}
	else if (state == GIMMICK_STATE_WALKING_RIGHT || state == GIMMICK_STATE_INCREASE)
	{
		ani = GIMMICK_ANI_WALKING_RIGHT;
	}
	else if (state == GIMMICK_STATE_WALKING_LEFT || state == GIMMICK_STATE_DECREASE)
	{
		ani = GIMMICK_ANI_WALKING_LEFT;
	}
	else if (state == GIMMICK_STATE_SLIDE_UP)
	{
		if (vx > 0)
			ani = GIMMICK_ANI_WALKING_RIGHT;
		else
			ani = GIMMICK_ANI_WALKING_LEFT;
	}
	else if (state == GIMMICK_STATE_SLIDE_DOWN)
	{
		if (vx > 0)
			ani = GIMMICK_ANI_WALKING_RIGHT;
		else
			ani = GIMMICK_ANI_WALKING_LEFT;
	}
	else if (state == GIMMICK_STATE_DIE)
	{
		if (waitToReset)
			die_effect->Render();

		return;
	}
	else if (state == GIMMICK_STATE_IDLE)
	{
		if (nx > 0)
			ani = GIMMICK_ANI_IDLE_RIGHT;
		else
			ani = GIMMICK_ANI_IDLE_LEFT;
	}
	else //if (state == GIMMICK_STATE_AUTO_GO)
	{
		if (key_down == 1)
			ani = GIMMICK_ANI_IDLE_RIGHT;
		else
			ani = GIMMICK_ANI_IDLE_LEFT;
	}

	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(x, y - 1, alpha);

	if (star != NULL)
		star->Render();

	if (loading == 1)
		load_star->Render();

	//RenderBoundingBox();
}

void CGimmick::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case GIMMICK_STATE_WALKING_RIGHT:

		vx = GIMMICK_WALKING_SPEED;
		nx = 1;
		break;

	case GIMMICK_STATE_WALKING_LEFT:
		vx = -GIMMICK_WALKING_SPEED;
		nx = -1;
		break;

	case GIMMICK_STATE_JUMP:
		Sound::GetInstance()->Play("CarSplash", 0, 1);
		vy = GIMMICK_JUMP_SPEED_Y;
		isScrollBar = false;
		Slide_reset();

		break;

	case GIMMICK_STATE_IDLE:
		vx = 0;
		break;

	case GIMMICK_STATE_INCREASE:
		vx = addVx;
		break;

	case GIMMICK_STATE_DECREASE:
		vx = addVx;
		break;

	case GIMMICK_STATE_SLIDE_UP:
	{
		if (direct_go == 1)
		{
			if (slide_size == 1) {

				vx = GIMMICK_SLIDE_UP_SPEED_X_1;
				vy = GIMMICK_SLIDE_UP_SPEED_Y_1;
			}
			else {

				vx = GIMMICK_SLIDE_UP_SPEED_X_2;
				vy = GIMMICK_SLIDE_UP_SPEED_Y_2;
			}
		}
		else //if (direct_go == -1)
		{
			if (slide_size == 1) {

				vx = -GIMMICK_SLIDE_UP_SPEED_X_1;
				vy = GIMMICK_SLIDE_UP_SPEED_Y_1;
			}
			else {

				vx = -GIMMICK_SLIDE_UP_SPEED_X_2;
				vy = GIMMICK_SLIDE_UP_SPEED_Y_2;
			}
		}
	}
	break;

	case GIMMICK_STATE_SLIDE_DOWN:
	{
		if (direct_go == 1)
		{
			if (slide_size == 1) {

				vx = GIMMICK_SLIDE_DOWN_SPEED_X_1;
				vy = -GIMMICK_SLIDE_DOWN_SPEED_Y_1;
			}
			else {

				vx = GIMMICK_SLIDE_DOWN_SPEED_X_2;
				vy = -GIMMICK_SLIDE_DOWN_SPEED_Y_2;
			}
		}
		else //if (direct_go == -1)
		{
			if (slide_size == 1) {

				vx = -GIMMICK_SLIDE_DOWN_SPEED_X_1;
				vy = -GIMMICK_SLIDE_DOWN_SPEED_Y_1;
			}
			else {

				vx = -GIMMICK_SLIDE_DOWN_SPEED_X_2;
				vy = -GIMMICK_SLIDE_DOWN_SPEED_Y_2;
			}
		}
	}
	break;

	case GIMMICK_STATE_AUTO_GO:
		if (isSlide) {

			vx = slide_vx;
			vy = slide_vy;
		}
		else if (isScrollBar) {
			vx = addVx;
		}
		else if (isAutoGo) {
			vx = addVx;
		}
		break;

	case GIMMICK_STATE_PIPING:
	{
		vx = 0;
		vy = 0;

		break;
	}

	case GIMMICK_STATE_DIE:
		Sound::GetInstance()->Play("Die", 0, 1);
		break;

	case MARIO_STATE_JUMP_HIGH_SPEED:
		vy = GIMMICK_JUMP_HIGHT_SPEED_Y;
		isSlide = false;
		isScrollBar = false;
		Sound::GetInstance()->Play("Opening", 0, 1);
		break;

	}
}

void CGimmick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (GetState() == GIMMICK_STATE_DIE) return;

	if (isScrollBar)
		left = x + 7;
	else
		left = x + 1;


	if (isScrollBar)
		right = x + 9;
	else
		right = x + GIMMICK_BBOX_WIDTH - 1;

	top = y - GIMMICK_BBOX_HORN;
	bottom = y - GIMMICK_BBOX_HEIGHT;

}

float CGimmick::isOnTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float x, float y)
{
	float q, w, e;
	q = (x - x1) / (x2 - x1) - (y - y1) / (y2 - y1);
	w = (x - x2) / (x3 - x2) - (y - y2) / (y3 - y2);
	e = (x - x3) / (x1 - x3) - (y - y3) / (y1 - y3);

	float tich = q * w * e;

	/*if (tich > 0)
		cout << "diem khong thuoc tam giac! " << endl;

	else
		cout << "diem thuoc tam giac! " << endl;*/

	return tich;
}

void CGimmick::Slide_reset()
{
	isSlide = false;
	direct_go = 0;
}

void CGimmick::ShotStar()
{
	if (isCanShot) {

		isCanShot = false;
		star->isActive = true;
		loading = 0;

		if (nx > 0) {

			star->SetState(STAR_GOING_RIGHT);
		}
		else {

			star->SetState(STAR_GOING_LEFT);
		}
	}
}

void CGimmick::isPrepareShot()
{
	if (loading == 0) {

		StarLoading();
	}
}

void CGimmick::SetLoadingStar()
{
	if (load_star == NULL)
		load_star = new CLoadingStar(x + 8, y - 8);

	load_star->TurnToBegin(x + 8, y - 8);
}

void CGimmick::KeyState(BYTE* state)
{
	CGame* game = CGame::GetInstance();

	// disable control key when Mario die 
	if (GetState() == GIMMICK_STATE_DIE || isPiping) return;

	if (game->IsKeyDown(DIK_RIGHT)) {

		key_down = 1;

		if (!isScrollBar && !isSlide) {

			SetState(GIMMICK_STATE_WALKING_RIGHT);
		}

		else if (isSlide && !isScrollBar) {

			if (direct_slide == GIMMICK_TREND_SLIDE_RIGHT)

				SetState(GIMMICK_STATE_SLIDE_UP);

			else
				SetState(GIMMICK_STATE_SLIDE_DOWN);
		}
		else if (!isSlide && isScrollBar) {

			if (trendScrollBar == GIMMICK_TREND_SCROLLBAR_INCREASE)

				SetState(GIMMICK_STATE_INCREASE);

			else
				SetState(GIMMICK_STATE_DECREASE);
		}
	}
	else if (game->IsKeyDown(DIK_LEFT)) {

		key_down = -1;

		if (!isScrollBar && !isSlide) {

			SetState(GIMMICK_STATE_WALKING_LEFT);
		}

		else if (isSlide && !isScrollBar) {

			if (direct_slide == GIMMICK_TREND_SLIDE_LEFT)

				SetState(GIMMICK_STATE_SLIDE_UP);

			else
				SetState(GIMMICK_STATE_SLIDE_DOWN);
		}
		else if (!isSlide && isScrollBar) {

			if (trendScrollBar == GIMMICK_TREND_SCROLLBAR_DECREASE)

				SetState(GIMMICK_STATE_INCREASE);

			else
				SetState(GIMMICK_STATE_DECREASE);
		}
	}
	else if (isScrollBar || isSlide || isAutoGo) {

		//gimmick->key_down = 0;

		SetState(GIMMICK_STATE_AUTO_GO);
	}
	else if (isPiping) {

		SetState(GIMMICK_STATE_PIPING);
	}
	else if (vy == 0 /*&& gimmick->vx != 0*/) {

		//gimmick->key_down = 0;

		SetState(GIMMICK_STATE_IDLE);
	}


	if (game->IsKeyDown(DIK_A)) {

		if (loading == 0 && star->isActive == false) {

			SetLoadingStar();
			StarLoading();
			Sound::GetInstance()->Play("Shot", 0, 1);
		}
	}
	else {

		if (loading == 2 && isCanShot) {

			ShotStar();
		}
		else {

			ReSetLoading();
		}
	}
}

void CGimmick::OnKeyDown(int keyCode)
{
}

void CGimmick::OnKeyUp(int keyCode)
{
}

void CGimmick::collideWithEnemies(vector<LPCOLLISIONEVENT> coEvents, float& min_tx, float& min_ty, float& nx, float& ny, float& rdx, float& rdy)
{

}

/*
	Reset Mario status to the beginning state of a scene
*/
void CGimmick::Reset()
{
	SetState(GIMMICK_STATE_IDLE);
	SetPosition(backupX, backupY);

	rest -= 1;
	energy = 3;
}

void CGimmick::SetAniDie()
{
	if (die_effect == NULL)
		die_effect = new CDie(x, y);

	die_effect->StarRender();
	die_effect->TurnToBegin(x, y);
}

void CGimmick::FollowObject(LPGAMEOBJECT obj)
{
	//vx = obj->GetVx();
	x = obj->GetX();
	y = obj->GetY() + GIMMICK_BBOX_HEIGHT + 0.4f;
}

