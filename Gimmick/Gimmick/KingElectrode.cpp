#include "KingElectrode.h"
#include "Bomb.h"
#include "Camera.h"
#include "Define.h"
#include "Gimmick.h"
#include "Sound.h"
#include "Map.h"

CKingElectrode::CKingElectrode(float _x, float _y)
{
	x = _x;
	y = _y;

	backupX = _x;
	backupY = _y;

	vx = KING_SPEED_X;
	vy = 0;

	live = KING_MAX_LIVE;

	for (int i = 0; i < BOMB_NUMBER; i++) {

		CBomb* bomb = new CBomb(x, y, BOMB_ITEM_NON);

		CAnimationSets* ani = CAnimationSets::GetInstance();
		LPANIMATION_SET ani_set = ani->Get(3);
		bomb->SetAnimationSet(ani_set);
		ListBomb.push_back(bomb);

		CMap::GetInstance()->quadTree->insertEntity(bomb);
	}

	isFinish = false;
}

CKingElectrode::~CKingElectrode()
{
	for (int i = 0; i < BOMB_NUMBER; i++)
		delete ListBomb[i];

	ListBomb.clear();
}

void CKingElectrode::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isFinish) {

		left = x;
		top = y + KING_BBOX_BULB;
		right = x + KING_BBOX_WIDTH;
		bottom = y - KING_BBOX_HEIGHT;
	}
}

void CKingElectrode::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	x += dx;
	y += dy;

	if ((x >= POS_MAX_X && vx > 0) && shoting == 0 && vx > 0) {

		isShotBomb = true;
		vx = 0;
		StartShot();
	}

	if (shoting == 1) {

		if (GetTickCount() - time_shot > TIME_SHOT) {

			shoting = 0;
			time_shot = 0;
			isShotBomb = false;
			vx = -KING_SPEED_X;

			for (int i = 0; i < BOMB_NUMBER; i++)
				if (!ListBomb[i]->isFinish) {

					ListBomb[i]->SetPosition(x + KING_BBOX_WIDTH, y - i * 3);

					ListBomb[i]->vx = BOMB_SPEED_VX*(i+1);
					ListBomb[i]->vy = BOMB_SPEED_VY * (i+1);
				}					
		}
	}

	if ((x <= POS_MIN_X && vx < 0) || ((x >= POS_MAX_X && vx > 0) && !isShotBomb))
		vx *= -1;

	if (live <= 0 && !isFinish) {
		isFinish = true;
		isDie = true;
	}

	if (isDie) {

		isDie = false;
		vy = -KING_SPEED_Y;
	}

	/*for (int i = 0; i < BOMB_NUMBER; i++)
		if (!ListBomb[i]->isFinish) {

			float camx, camy;
			CCamera::GetInstance()->GetCamPos(camx, camy);

			if (!(ListBomb[i]->x< camx || ListBomb[i]->x> camx + SCREEN_WIDTH || ListBomb[i]->y< camy || ListBomb[i]->y> camy + SCREEN_HEIGHT_MAP)) {

				ListBomb[i]->Update(dt, coObjects);

				CGimmick* gimmick = CGimmick::GetInstance(0, 0);
				if (gimmick->isCollisionWithObject(ListBomb[i])) {
					if (gimmick->untouchable == 0)
					{
						if (gimmick->GetState() != GIMMICK_STATE_DIE)
						{
							if (gimmick->energy > 0)
							{
								Sound::GetInstance()->Play("Collision", 0, 1);
								gimmick->energy -= 1;
								gimmick->StartUntouchable();

							}
							else
							{
								gimmick->SetState(GIMMICK_STATE_DIE);
							}
						}
					}
				}

				if (gimmick->star->isCollisionWithObject(ListBomb[i])) {

					ListBomb[i]->isFinish = true;
					gimmick->star->Reset();
				}
			}
		}*/
}

void CKingElectrode::Render()
{
	if (!isFinish) {

		animation_set->at(0)->Render(x, y);
		CAnimations::GetInstance()->Get(327)->Render(x + 6, y + KING_BBOX_BULB * 2 );
	}
	else {

		animation_set->at(1)->Render(x, y + KING_BBOX_BULB);
	}
}
