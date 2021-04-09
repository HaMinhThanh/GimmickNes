#include "Pipes.h"

CPipes::CPipes(int left, int right, int top, int w, int h)
{
	xLeft = left;
	xRight = right;
	yTop = top;

	width = w;
	height = h;
}

CPipes::~CPipes()
{
}

void CPipes::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void CPipes::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CPipes::Render()
{
}
