#pragma once

#include "GameObject.h"

#define ITEM_GRAVITY		-0.0007f

#define MEDICINE_TYPE_1		1
#define MEDICINE_TYPE_2		2

#define MEDICINE_SPRITE_1		70001
#define MEDICINE_SPRITE_2		70002

#define MEDICINE_BBOX_WIDTH		13
#define MEDICINE_BBOX_HEIGHT	14

class CMedicine: public CGameObject
{
public:
	int type;
public:

	CMedicine(float x, float y, int type);
	~CMedicine();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};

