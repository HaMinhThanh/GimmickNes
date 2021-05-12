#include "RenderImage.h"


void CRenderImage::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CRenderImage::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}

