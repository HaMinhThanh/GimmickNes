#include "Shadow.h"

CShadow::CShadow(float _x, float _y)
{
	x = _x;
	y = _y;

	backupX = x;
	backupY = y;
}

CShadow::~CShadow()
{
}

void CShadow::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

void CShadow::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CShadow::Render()
{
}
