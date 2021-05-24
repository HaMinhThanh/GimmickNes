
#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

#define SCROLLBAR_TYPE_INCREASE 1
#define SCROLLBAR_TYPE_DECREASE 0

#define SCROLLBAR_ANI_INCREASE 1
#define SCROLLBAR_ANI_DECREASE 0

#define SCROLLBAR_SPEED 0.01f

class CScrollBar : public CGameObject
{
	int type;
public:

	CScrollBar(int type);
	~CScrollBar();

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	int GetType() { return type; };
};


