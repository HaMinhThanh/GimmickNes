#include "KingElectrode.h"
#include "Bomb.h"

CKingElectrode::CKingElectrode(float _x, float _y)
{
	x = _x;
	y = _y;

	vx = KING_SPEED_X;
	vy = 0;

	live = KING_MAX_LIVE;

	for (int i = 0; i < BOMB_NUMBER; i++) {

		CBomb* bomb = new CBomb(x, y);

		CAnimationSets* ani = CAnimationSets::GetInstance();
		LPANIMATION_SET ani_set = ani->Get(3);
		bomb->SetAnimationSet(ani_set);
		ListBomb.push_back(bomb);
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
		top = y - KING_BBOX_BULB;
		right = x + KING_BBOX_WIDTH;
		bottom = y + KING_BBOX_HEIGHT;
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
					ListBomb[i]->vy = -BOMB_SPEED_VY * (i+1);
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
		vy = KING_SPEED_Y;
	}

	for (int i = 0; i < BOMB_NUMBER; i++)
		if (!ListBomb[i]->isFinish)
			ListBomb[i]->Update(dt, coObjects);
}

void CKingElectrode::Render()
{
	if (!isFinish) {
		animation_set->at(0)->Render(x, y);
		CAnimations::GetInstance()->Get(327)->Render(x + 6, y - KING_BBOX_BULB * 2 );

		for (int i = 0; i < BOMB_NUMBER; i++)
			if (!ListBomb[i]->isFinish)
				ListBomb[i]->Render();
	}
	else
		animation_set->at(1)->Render(x, y - KING_BBOX_BULB);
}
