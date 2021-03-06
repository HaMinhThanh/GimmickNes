#include "LoadingStar.h"

CLoadingStar::CLoadingStar(float x, float y)
{
	backupX = x;
	backupY = y;

	TurnToBegin(x, y);
}

CLoadingStar::~CLoadingStar()
{
}

void CLoadingStar::TurnToBegin(float x, float y)
{
	// reset star position above the gimmick head

	x1 = x - 32;
	x2 = x + 8;
	x3 = x + 40;
	x4 = x + 40;
	x5 = x - 24;

	y1 = y + 10;
	y2 = y + 32;
	y3 = y + 10;
	y4 = y - 32;
	y5 = y - 32;
}

void CLoadingStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	x += dx;
	y += dy;

	x1 += LOADING_SPEED_X1 * dt;
	x2 += LOADING_SPEED_X2 * dt;
	x3 += LOADING_SPEED_X3 * dt;
	x4 += LOADING_SPEED_X4 * dt;
	x5 += LOADING_SPEED_X5 * dt;

	y1 += LOADING_SPEED_Y1 * dt;
	y1 += LOADING_SPEED_Y2 * dt;
	y1 += LOADING_SPEED_Y3 * dt;
	y1 += LOADING_SPEED_Y4 * dt;
	y1 += LOADING_SPEED_Y5 * dt;

}

void CLoadingStar::Render()
{
	CAnimationSets* ani = CAnimationSets::GetInstance();

	ani->Get(LOADING_STAR_ANIMATION)->at(0)->Render(x1, y1);
	ani->Get(LOADING_STAR_ANIMATION)->at(0)->Render(x2, y2);
	ani->Get(LOADING_STAR_ANIMATION)->at(0)->Render(x3, y3);
	ani->Get(LOADING_STAR_ANIMATION)->at(0)->Render(x4, y4);
	ani->Get(LOADING_STAR_ANIMATION)->at(0)->Render(x5, y5);

}

void CLoadingStar::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}
