#include "ScrollBar.h"


void CScrollBar::Render()
{
	if (type == SCROLLBAR_TYPE_INCREASE)
		animation_set->at(SCROLLBAR_ANI_INCREASE)->Render(x, y);
	else
		animation_set->at(SCROLLBAR_ANI_DECREASE)->Render(x, y);

	//RenderBoundingBox();
}

void CScrollBar::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

CScrollBar::CScrollBar(int t)
{
	type = t;

}