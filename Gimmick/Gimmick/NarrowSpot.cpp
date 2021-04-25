#include "NarrowSpot.h"

CNarrowSpot::CNarrowSpot(float _x, float _y)
{
	x = _x;
	y = _y;
}

CNarrowSpot::~CNarrowSpot()
{
}

void CNarrowSpot::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CNarrowSpot::Render()
{
	animation_set->at(0)->Render(x, y);
}

void CNarrowSpot::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}
