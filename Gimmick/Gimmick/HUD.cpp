#include "HUD.h"
#include "Game.h"
#include <string>

CHUD* CHUD::instance = NULL;

CHUD* CHUD::GetInstance()
{
	if (instance == NULL)
		instance = new CHUD();

	return instance;
}

void CHUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
}

void CHUD::Render()
{
	CGame* game = CGame::GetInstance();

	float cx, cy;
	game->GetCamPos(cx, cy);

	CSprites* sprite = CSprites::GetInstance();
	sprite->Get(80020)->Draw(cx, cy + game->GetScreenHeight() - 32);
	sprite->Get(80010)->Draw(cx, cy + game->GetScreenHeight() - 32);

	// Draw score
	event->DrawNumber(8, cx + 15, cy + game->GetScreenHeight() - 16, 987654);

	// Draw rest
	event->DrawNumber(2, cx + 95, cy + game->GetScreenHeight() - 16, 7);

	// Draw energy
	event->DrawEnergy(cx + 126, cy + game->GetScreenHeight() - 21, 3);

	// Draw item
}
