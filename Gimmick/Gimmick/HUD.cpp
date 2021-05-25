#include "HUD.h"
#include "Game.h"
#include <string>
#include "Utils.h"

CHUD* CHUD::instance = NULL;

CHUD* CHUD::GetInstance()
{
	if (instance == NULL)
		instance = new CHUD();

	return instance;
}

void CHUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	CGimmick* gimmick = CGimmick::GetInstance(0, 0);

	if (gimmick->numItem == 1)
	{
		it1 = gimmick->GetItem();
	}
	else if (gimmick->numItem == 2)
	{
		it2 = gimmick->GetItem();
	}
	else if (gimmick->numItem == 3)
	{
		it3 = gimmick->GetItem();
	}
	else if (gimmick->numItem > 3)
	{
		it1 = it2 = it3 = -1;
		gimmick->numItem -= 3;
	}
}

void CHUD::Render()
{
	CGame* game = CGame::GetInstance();
	CGimmick* gimmick = CGimmick::GetInstance(0, 0);

	float cx, cy;
	game->cam->GetCamPos(cx, cy);

	CSprites* sprite = CSprites::GetInstance();
	//sprite->Get(80020)->Draw(cx, cy + game->GetScreenHeight() - 32);
	//sprite->Get(80010)->Draw(cx, cy + game->GetScreenHeight() - 32);

	/*CHANGE HUD POSITION*/
	sprite->Get(80020)->Draw(cx, cy + 16);
	sprite->Get(80010)->Draw(cx, cy + 16);



	/*
	// Draw score
	event->DrawNumber(8, cx + 15, (int) cy + game->GetScreenHeight() - 16, gimmick->GetScore());

	// Draw rest
	event->DrawNumber(2, cx + 95, (int)cy + game->GetScreenHeight() - 16, gimmick->GetRest());

	// Draw energy
	event->DrawEnergy(cx + 126, (int)cy + game->GetScreenHeight() - 21, gimmick->GetEnergy());

	// Draw item
	if (gimmick->item != 0)
		DebugOut(L"Item = %d\n", gimmick->numItem);

	if (it1 != -1) {
		event->DrawItem(cx + 177, cy + game->GetScreenHeight() - 27, it1);
	}
	if (it2 != -1) {
		event->DrawItem(cx + 201, cy + game->GetScreenHeight() - 27, it2);
	}
	if (it3 != -1) {
		event->DrawItem(cx + 225, cy + game->GetScreenHeight() - 27, it3);
	}
	*/


	/*CHANGE DRAWING IN HUD*/
	// Draw score
	event->DrawNumber(8, cx + 15, (int)cy + 0, gimmick->GetScore());

	// Draw rest
	event->DrawNumber(2, cx + 95, (int)cy + 0, gimmick->GetRest());

	// Draw energy
	event->DrawEnergy(cx + 126, (int)cy + 5, gimmick->GetEnergy());

	// Draw item
	if (gimmick->item != 0)
		DebugOut(L"Item = %d\n", gimmick->numItem);

	if (it1 != -1) {
		event->DrawItem(cx + 177, cy + 9, it1);
	}
	if (it2 != -1) {
		event->DrawItem(cx + 201, cy + 9, it2);
	}
	if (it3 != -1) {
		event->DrawItem(cx + 225, cy + 9, it3);
	}
}
