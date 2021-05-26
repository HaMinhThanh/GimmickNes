#include "Treasures.h"

CTreasures::CTreasures(int _width, int _height)
{
	width = _width;
	height = _height;
}

CTreasures::~CTreasures()
{
}

void CTreasures::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isFinish) {
		left = x;
		top = y;
		right = x + width;
		bottom = y - height;
	}
}

void CTreasures::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CTreasures::Render()
{
	if (!isFinish) {
		animation_set->at(0)->Render(x, y);
	}
}
