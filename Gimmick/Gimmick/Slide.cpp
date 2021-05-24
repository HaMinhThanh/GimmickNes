#include "Slide.h"

CSlide::CSlide(float x, float y, int _direct, int _size)
{
	size = _size;
	direct = _direct;
}

CSlide::~CSlide()
{
}

void CSlide::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CSlide::Render()
{
}

void CSlide::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	bottom = y + SLIDE_SIZE_QUAD;

	if (size == 1)
		right = x + SLIDE_SIZE_QUAD;
	else
		right = x + SLIDE_SIZE_REC;
}
